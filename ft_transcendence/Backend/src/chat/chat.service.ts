import { Injectable, Inject, forwardRef, Res, HttpStatus, Logger, Redirect } from '@nestjs/common';
import { PrismaService } from 'src/prisma/prisma.service';
import { BadRequestException, UnauthorizedException, ForbiddenException, NotFoundException, ConflictException } from '@nestjs/common/exceptions';
import { 
	ChangeChannelNameDto, 
	ChangeChannelPasswordDto, 
	CreateChannelDto, JoinChannelDto, 
	LeaveChannelDto, LeaveDto, 
	ListenDto, MessageDto, 
	SwitchChannelTypeDto,
	InviteToGameDto, 
	ChannelSettingDto,
	PasswordDto} from './dto/channel.dto';
import { 
	BanMemberDto, 
	UnbanMemberDto, 
	MuteMemberDto, 
	UnmuteMemberDto, 
	AddMemberDto, 
	KickMemberDto,
	PromoteMemberDto,
	DemoteMemberDto,
	EmitMessageDto} from './dto/member.dto';
import { Prisma, UserStatus } from '@prisma/client';
import { ConfigService } from '@nestjs/config';
import * as argon from 'argon2'
import { ChatGateway } from './chat.gateway';
import { Socket } from 'socket.io';
import { parse } from 'cookie';
import { JwtService } from '@nestjs/jwt';
import { validate } from 'class-validator';
import { Cron, CronExpression } from '@nestjs/schedule';
import { GameGateway } from 'src/game/game.gateway';

@Injectable()
export class ChatService {
    constructor(
        private config: ConfigService,
        private prisma : PrismaService,
        private jwt: JwtService,
        @Inject(forwardRef(() => ChatGateway))
        private chatGateway : ChatGateway,
        private gameGateway : GameGateway
		) {}
		private logger: Logger = new Logger('ChatService');
		public socketsDictionary: Record<number, Array<string>> = {};

    async getChannels(userId : number) {

        const channels = await this.prisma.user.findUnique({
            where:{
                id: userId,
            },
            select:{
                member:{
                    where:{
                        NOT: [ {status: "BANNED"} ]
                    },
                    select:{
                        channel:{
							include:{
								members:{
									where:{
										NOT:{ userId: userId },
										channel:{
											type: "DM",
										}
									},
									select:{
										user:{
											select:{
												name: true,
												avatar: true,
											}
										}
									}
								}
							}
						},
                    }
                }
            }
        });

		let new_channels = []
		for (const channel of channels.member)
		{
			let new_channel = {
				id: channel.channel.id,
				name: channel.channel.name,
				type: channel.channel.type
			}

			if (channel.channel.type === 'DM')
			{
				new_channel.name = channel.channel.members[0].user.name;
				new_channel['avatar'] = channel.channel.members[0].user.avatar;
			}
			new_channels.push(new_channel);
		}

        return (new_channels);
    }

    async searchChannel(userId : number, channel_name?: string, ) {
		let search_result = [];

		if (!channel_name)
			return (search_result);
		let channels = await this.prisma.channel.findMany({
            where:{
                name: {contains: channel_name},
                NOT: {type: 'DM'}
            },
			include:{
				members: true
			}
        });

		for (let channel of channels)
		{
			const isMember = channel.members.find(member => member.userId === userId)
			if (!isMember && channel.type === 'PRIVATE')
				continue;
			let result = {
				id: channel.id,
				name: channel.name,
				type: channel.type,
				isMember: isMember ? true : false,
			}
			search_result.push(result);
		}

		let users = await this.prisma.user.findMany({
			where:{
				name:{ contains: channel_name},
				NOT: {id: userId},
			}
        });
		
		for (let user of users)
		{
			const isfriend = await this.prisma.channel.findFirst({
				where:{
					type: 'DM',
					AND:[{ members:{ some: {userId : userId} }},
						 { members:{ some: {userId : user.id} }}]
				}
			})
			let result = {
				id: isfriend ? isfriend.id : user.id ,
				name: user.name,
				type: 'DM',
				isMember: isfriend ? true : false,
			}
			search_result.push(result);
		}

		if (!search_result || !search_result.length)
			throw new NotFoundException(['Nothing found']);
        return (search_result);
    }

	async searchUsers(channelId: number, userId : number, user_name?: string)
	{
		let search_result = [];

		if (!user_name)
			return (search_result);
		const users = await this.prisma.user.findMany({
			where:{
				name:{ contains: user_name},
				NOT: {id: userId},
				OR: [{ friends:{ some:{ userId: userId } } },
					 { friendOf:{ some:{ userId: userId } }}],
				member:{
					none:{channelId: channelId}
				}
			},
			select:{
				id: true,
				name: true,
				member:{
					where:{
						channel:{
							type: 'DM',
							members:{ some: {userId: userId} }
						}
					}
				}
			}
		});

		for (let user of users)
		{
			if (user.member[0].status !== 'ACTIVE')
				continue ;
			const new_user = {
				id: user.id,
				name: user.name,
			}
			search_result.push(new_user);
		}
		return (search_result);
    }

    async getMessages(channelId : number, userId : number)
    {    
        const channel = await this.prisma.channel.findUnique({
            where:{
                id: channelId
            },
            select:{
				name: true,
				type: true,
				members:{
					select:{
						userId: true,
						status: true,
						role: true,
						banExpiration: true,
						muteExpiration: true,
						user:{
							select:{
								name: true,
							}
						}
					}
				},
                messages:{
                    orderBy:{
                        sendAt: 'desc',
                    },
					select:{
						from: true,
						message: true,
						isGameInvite: true,
						sendAt: true,
						user:{
							select:{
								name: true
							}
						}
					}
                },
            }
        });
		if (!channel)
			throw new ForbiddenException(['Sorry, you are not authorized to perform this action']);
		const member = channel.members.find(member => member.userId === userId)
		if (!member || member.status === 'BANNED')
			throw new ForbiddenException(['Sorry, you are not authorized to perform this action']);
		
		let result = {channel: {},
					  user: {},
					  members:[],
					  messages:[]};

		if (channel.type === 'DM')
			channel.name = channel.members.find((member)=> member.userId !== userId).user.name;
		result.channel = {name: channel.name,
						  type: channel.type,}

		for (let member of channel.members)
		{
			let new_member = {
				userId: member.userId,
				name: member.user.name,
				status: member.status,
				role: member.role,
				banExpiration: member.banExpiration,
				muteExpiration: member.muteExpiration,
			}
			if (member.userId === userId)
				result.user = new_member;
			else
				result.members.push(new_member);
		}

		for (let message of channel.messages)
		{
			let new_message = {
				username: message.user.name,
				message: message.message,
				isGameInvite: message.isGameInvite, 
				mine: false
			}
			if (message.from === userId)
				new_message.mine = true;
			result.messages.push(new_message);	
		}

		return (result);
    }

    async joinChannel(dto : JoinChannelDto)
    {
        const channel = await this.prisma.channel.findUnique({
            where:{
                id: dto.channelId,
            },
            include:{
                members:{
                    where:{
                        userId: dto.userId,
						NOT:{status: 'BANNED'}
                    }
                }
            }
        });

        if (!channel)
			throw new ForbiddenException(['Sorry, you are not authorized to perform this action']);
        if (channel.members.length)
			throw new ForbiddenException(['Sorry, you are not authorized to perform this action']);
        if (channel.type === 'DM' || channel.type === 'PRIVATE')
			throw new ForbiddenException(['Sorry, you are not authorized to perform this action']);
    
        if (channel.type === 'PROTECTED')
        {
			const errors = await validate(dto);
			if (errors.length)
				throw new BadRequestException(['Invalid Password']);
            const pwMatches = await argon.verify(channel.password, dto.password);
            if (!pwMatches)
              throw new UnauthorizedException(['Wrong Password']);
        }
        
        await this.prisma.member.create({
            data:{
                channelId: dto.channelId,
                userId: dto.userId
            }
        });
    }

    async leaveChannel(dto : LeaveChannelDto)
    {
		const member = await this.prisma.member.findUnique({
			where:{
				userId_channelId:{
					channelId: dto.channelId,
					userId: dto.userId,
				}
			},
			include:{
				channel: true
			}
		});

		if (!member || member.status === 'BANNED')
			throw new ForbiddenException(['Sorry, you are not authorized to perform this action']);
		if (member.channel.type === 'DM' || member.status === 'MUTED')
			throw new ForbiddenException(['Sorry, you are not authorized to perform this action']);

        if (member.role === 'OWNER')
		{
			let next_owner = await this.prisma.member.findFirst({
				where:{
					channelId: dto.channelId,
					NOT:{userId: dto.userId}
				}
			});

			if (!next_owner)
			{
				await this.deleteChannel(dto.channelId);
				return;
			}

			await this.prisma.member.update({
				data:{
					status:'ACTIVE',
					role: 'OWNER',
					banExpiration: null,
					muteExpiration: null,
				},
				where:{
					userId_channelId:{
						channelId: next_owner.channelId,
						userId: next_owner.userId,
					}
				}
			});
        }

		await this.prisma.member.delete({
			where:{
				userId_channelId:{
					channelId: dto.channelId,
					userId: dto.userId,
				}
			}
		});

		const socketIds = this.socketsDictionary[dto.userId];
		if (socketIds)
		{
			for (let socketId of socketIds)
			{
				const socket =  this.chatGateway.server.sockets.sockets.get(socketId);
				await this.leave(socket, {
					channelId: dto.channelId, 
					roomId: String(dto.channelId),
					userId: dto.userId
				});
			}
		}
    }

    async banMember(dto: BanMemberDto)
    {
		const errors = await validate(dto);
		if (errors.length)
			throw new BadRequestException(['Invalid Input']);

		const channel = await this.prisma.channel.findUnique({
			where:{
				id: dto.channelId,
			},
			include: {
				members:{
					where:{
						OR:[{userId: dto.userId}, 
							{userId: dto.targetId}]
					}
				}
			}
		});

		if (!channel || channel.type === 'DM')
			throw new ForbiddenException(['You do not have permission to perform this action']);
		if (channel.members.length != 2)
			throw new ForbiddenException(['You do not have permission to perform this action']);

		const user = channel.members[0].userId === dto.userId ? channel.members[0] : channel.members[1];
		const target = channel.members[0].userId === dto.targetId ? channel.members[0] : channel.members[1];

		if (user.status !== 'ACTIVE' || user.role === 'MEMBER' || target.role === 'OWNER' || user.role === target.role)
			throw new ForbiddenException(['You do not have permission to perform this action']);

		let banExpiration = new Date();
		banExpiration.setMinutes( banExpiration.getMinutes() + 15 );
        const member = await this.prisma.member.update({
            data:{
                status: 'BANNED',
                banExpiration: banExpiration,
                muteExpiration: null
            },
            where:{
                userId_channelId:{
                    channelId: dto.channelId,
                    userId: dto.targetId
                }
            }
        });

		const socketIds = this.socketsDictionary[dto.targetId];
		if (socketIds)
		{
			for (let socketId of socketIds)
			{
				const socket = this.chatGateway.server.sockets.sockets.get(socketId);
				await this.leave(socket, {
					channelId: dto.channelId, 
					roomId: String(dto.channelId),
					userId: dto.targetId
				});
			}
		}
		this.emitMessage({
			to: String(dto.channelId),
			event: 'update-member',
			message: member
		});
    }

    async unbanMember(dto: UnbanMemberDto)
    {
		const errors = await validate(dto);
		if (errors.length)
			throw new BadRequestException(['Invalid Input']);

		const channel = await this.prisma.channel.findUnique({
			where:{
				id: dto.channelId,
			},
			include: {
				members:{
					where:{
						OR:[{userId: dto.userId}, 
							{userId: dto.targetId}]
					}
				}
			}
		});
	
		if (!channel || channel.type == 'DM')
			throw new ForbiddenException(['Forbidden']);
		if (channel.members.length != 2)
			throw new ForbiddenException(['Forbidden']);

		const user = channel.members[0].userId === dto.userId ? channel.members[0] : channel.members[1];
		const target = channel.members[0].userId === dto.targetId ? channel.members[0] : channel.members[1];

		if (user.status !== 'ACTIVE' || user.role === 'MEMBER' || target.status !== 'BANNED' || target.role === 'OWNER' || user.role === target.role)
			throw new ForbiddenException(['Forbidden']);

        const member = await this.prisma.member.update({
            data:{
                status: 'ACTIVE',
                banExpiration: null,
            },
            where:{
                userId_channelId:{
                    channelId: dto.channelId,
                    userId: dto.targetId
                }
            }
        });

		this.emitMessage({
			to: String(dto.channelId),
			event: 'update-member',
			message: member
		});
    }

    async muteMember(dto: MuteMemberDto)
    {
		const errors = await validate(dto);
		if (errors.length)
			throw new BadRequestException(['Invalid Input']);

		const channel = await this.prisma.channel.findUnique({
			where:{
				id: dto.channelId,
			},
			include: {
				members:{
					where:{
						OR:[{userId: dto.userId}, 
							{userId: dto.targetId}]
					}
				}
			}
		});

		if (!channel || channel.type == 'DM')
			throw new ForbiddenException(['Forbidden']);
		if (channel.members.length != 2)
			throw new ForbiddenException(['Forbidden']);

		const user = channel.members[0].userId === dto.userId ? channel.members[0] : channel.members[1];
		const target = channel.members[0].userId === dto.targetId ? channel.members[0] : channel.members[1];

		if (user.status !== 'ACTIVE' || user.role === 'MEMBER' || target.role === 'OWNER' || user.role === target.role)
			throw new ForbiddenException(['Forbidden']);

		let muteExpiration = new Date();
		muteExpiration.setMinutes( muteExpiration.getMinutes() + 15 );
        const member = await this.prisma.member.update({
            data:{
                status: 'MUTED',
                muteExpiration: muteExpiration,
                banExpiration: null,
            },
            where:{
                userId_channelId:{
                    channelId: dto.channelId,
                    userId: dto.targetId
                }
            }
        });

		this.emitMessage({
			to: String(dto.channelId),
			event: 'update-member',
			message: member
		});
    }

    async unmuteMember(dto: UnmuteMemberDto)
    {
		const errors = await validate(dto);
		if (errors.length)
			throw new BadRequestException(['Invalid Input']);

		const channel = await this.prisma.channel.findUnique({
			where:{
				id: dto.channelId,
			},
			include: {
				members:{
					where:{
						OR:[{userId: dto.userId}, 
							{userId: dto.targetId}]
					}
				}
			}
		});

		if (!channel || channel.type === 'DM')
			throw new ForbiddenException(['Forbidden']);
		if (channel.members.length != 2)
			throw new ForbiddenException(['Forbidden']);

		const user = channel.members[0].userId === dto.userId ? channel.members[0] : channel.members[1];
		const target = channel.members[0].userId === dto.targetId ? channel.members[0] : channel.members[1];

		if (user.status !== 'ACTIVE' || user.role === 'MEMBER' || target.status !== 'MUTED' || target.role === 'OWNER' || user.role === target.role)
			throw new ForbiddenException(['Forbidden']);

        const member = await this.prisma.member.update({
            data:{
                status: 'ACTIVE',
                muteExpiration: null,
            },
            where:{
                userId_channelId:{
                    channelId: dto.channelId,
                    userId: dto.targetId
                }
            }
        });

		this.emitMessage({
			to: String(dto.channelId),
			event: 'update-member',
			message: member
		});
    }

    async blockFriend(channelId: number, userId: number)
    {
		const channel = await this.prisma.channel.findUnique({
			where:{
				id: channelId,
			},
			include:{
				members: true,
			}
		});

		if (!channel || channel.type !== 'DM')
			throw new ForbiddenException(['Forbidden']);

		const user = channel.members[0].userId === userId ? channel.members[0] : channel.members[1];
		const friend = channel.members[0].userId === userId ? channel.members[1] : channel.members[0];

		if (user.userId !== userId || user.status !== 'ACTIVE')
			throw new ForbiddenException(['Forbidden']);

        const user_update = await this.prisma.member.update({
            data:{
                status: 'BLOCKER',
            },
            where:{
                userId_channelId:{
                    channelId: channelId,
                    userId: userId
                }
            }
        });

        const friend_update = await this.prisma.member.update({
            data:{
                status: 'BLOCKED',
            },
            where:{
                userId_channelId:{
					channelId: channelId,
					userId: friend.userId,
				}
            }
        });

		this.emitMessage({
			to: String(channelId),
			event: 'update-member',
			message: user_update
		});

		this.emitMessage({
			to: String(channelId),
			event: 'update-member',
			message: friend_update
		});
    }
    
    async unblockFriend(channelId: number, userId: number)
    {
		const channel = await this.prisma.channel.findUnique({
			where:{
				id: channelId,
			},
			include:{
				members: true,
			}
		});

		if (!channel || channel.type !== 'DM')
			throw new ForbiddenException(['Forbidden']);

		const user = channel.members[0].userId === userId ? channel.members[0] : channel.members[1];
		const friend = channel.members[0].userId === userId ? channel.members[1] : channel.members[0];

		if (user.userId !== userId || user.status !== 'BLOCKER')
			throw new ForbiddenException(['Forbidden']);

        const user_update = await this.prisma.member.update({
            data:{
                status: 'ACTIVE',
            },
            where:{
                userId_channelId:{
                    channelId: channelId,
                    userId: userId
                }
            }
        });

        const friend_update = await this.prisma.member.update({
            data:{
                status: 'ACTIVE',
            },
            where:{
				userId_channelId:{
					channelId: channelId,
					userId: friend.userId
				}
            }
        });

		this.emitMessage({
			to: String(channelId),
			event: 'update-member',
			message: user_update
		});

		this.emitMessage({
			to: String(channelId),
			event: 'update-member',
			message: friend_update
		});
    }

	async addMember(dto: AddMemberDto)
	{
		const errors = await validate(dto);
		if (errors.length)
			throw new BadRequestException(['Invalid Input']);
		
		const user = await this.prisma.member.findUnique({
			where:{
				userId_channelId:{
					channelId: dto.channelId,
					userId: dto.userId
				}
			}
		});

		if (!user || user.role !== 'OWNER')
			throw new ForbiddenException(['Forbidden']);

		const target_user = await this.prisma.user.findFirst({
			where:{
				name: dto.username,
				OR: [{ friends:{ some:{ friendId: dto.userId } } },
					{ friendOf:{ some:{ userId: dto.userId } }}],
				member:{
					none:{channelId: dto.channelId}
				}
			},
			include:{
				member:{
					where:{
						channel:{
							type: 'DM',
							members:{ some: {userId: dto.userId} }
						}
					}
				}
			}
		});

		if (!target_user || target_user.member[0].status !== 'ACTIVE')
			throw new ForbiddenException(['Forbidden']);

		try 
		{
			const new_member = await this.prisma.member.create({
				data:{
					channelId: dto.channelId,
					userId: target_user.id,
				}
			});
		}
		catch (error)
		{
			if (error instanceof Prisma.PrismaClientKnownRequestError && error.code === 'P2002')
				throw new ForbiddenException(['Action Forbidden']); 
			throw (error)
		}
	}

	async promoteMember(dto: PromoteMemberDto)
	{
		const errors = await validate(dto);
		if (errors.length)
			throw new BadRequestException(['Invalid Input']);
		
		const channel = await this.prisma.channel.findUnique({
			where:{
				id: dto.channelId,
			},
			include: {
				members:{
					where:{
						OR:[{userId: dto.userId}, 
							{userId: dto.targetId}]
					}
				}
			}
		});
	
		if (!channel || channel.type === 'DM')
			throw new ForbiddenException(['Forbidden']);
		if (channel.members.length != 2)
			throw new ForbiddenException(['Forbidden']);

		const user = channel.members[0].userId === dto.userId ? channel.members[0] : channel.members[1];
		const target = channel.members[0].userId === dto.targetId ? channel.members[0] : channel.members[1];

		if (user.role !== 'OWNER' || target.role !== 'MEMBER')
			throw new ForbiddenException(['Forbidden']);

		const member = await this.prisma.member.update({
			data:{
				role: 'ADMIN'
			},
			where:{
				userId_channelId:{
					channelId: dto.channelId,
					userId: dto.targetId
				}
			}
		});
		
		this.emitMessage({
			to: String(dto.channelId),
			event: 'update-member',
			message: member
		});
	}

	async demoteMember(dto: DemoteMemberDto)
	{
		const errors = await validate(dto);
		if (errors.length)
			throw new BadRequestException(['Invalid Input']);
		
		const channel = await this.prisma.channel.findUnique({
			where:{
				id: dto.channelId,
			},
			include: {
				members:{
					where:{
						OR:[{userId: dto.userId}, 
							{userId: dto.targetId}]
					}
				}
			}
		});
	
		if (!channel || channel.type === 'DM')
			throw new ForbiddenException(['Forbidden']);
		if (channel.members.length != 2)
			throw new ForbiddenException(['Forbidden']);

		const user = channel.members[0].userId === dto.userId ? channel.members[0] : channel.members[1];
		const target = channel.members[0].userId === dto.targetId ? channel.members[0] : channel.members[1];

		if (user.role !== 'OWNER' || target.role !== 'ADMIN')
			throw new ForbiddenException(['Forbidden']);

		const member = await this.prisma.member.update({
			data:{
				role: 'MEMBER'
			},
			where:{
				userId_channelId:{
					channelId: dto.channelId,
					userId: dto.targetId
				}
			}
		});

		this.emitMessage({
			to: String(dto.channelId),
			event: 'update-member',
			message: member
		});
	}

	async kickMember(dto: KickMemberDto)
	{
		const errors = await validate(dto);
		if (errors.length)
			throw new BadRequestException(['Invalid Input']);
		
		const channel = await this.prisma.channel.findUnique({
			where:{
				id: dto.channelId,
			},
			include: {
				members:{
					where:{
						OR:[{userId: dto.userId}, 
							{userId: dto.targetId}]
					}
				}
			}
		});
	
		if (!channel || channel.type === 'DM')
			throw new ForbiddenException(['Forbidden']);
		if (channel.members.length != 2)
			throw new ForbiddenException(['Forbidden']);

		const user = channel.members[0].userId === dto.userId ? channel.members[0] : channel.members[1];
		const target = channel.members[0].userId === dto.targetId ? channel.members[0] : channel.members[1];

		if (user.status !== 'ACTIVE' || user.role === 'MEMBER' || target.role === 'OWNER' || user.role === target.role)
			throw new ForbiddenException(['Forbidden']);
	
		await this.prisma.member.delete({
			where:{
				userId_channelId:{
					channelId: dto.channelId,
					userId: dto.targetId,
				}
			}
		});

		const socketIds = this.socketsDictionary[dto.targetId];
		if (socketIds)
		{
			for (let socketId of socketIds)
			{
				const socket = this.chatGateway.server.sockets.sockets.get(socketId);
				await this.leave(socket, {
					channelId: dto.channelId, 
					roomId: String(dto.channelId),
					userId: dto.targetId
				});
			}
		}

		this.emitMessage({
			to: String(dto.channelId),
			event: 'delete-member',
			message: dto.targetId
		});
	}

	async changeChannelName(dto: ChangeChannelNameDto)
	{
		const user = await this.prisma.member.findUnique({
			where:{
				userId_channelId:{
					channelId: dto.channelId,
					userId: dto.userId
				}
			}
		});

		if (!user || user.role !== 'OWNER')
			throw new ForbiddenException(['You do not have permission to perform this action']);
	
		try 
		{
			await this.prisma.channel.update({
				data:{
					name: dto.newName
				},
				where:{
					id: dto.channelId
				}
			})
		}
		catch (error)
		{
			if (error instanceof Prisma.PrismaClientKnownRequestError && error.code === 'P2002')
				throw new ConflictException(["Channel With This Name Already Exist"]); 
			throw (error)
		}
	}

	async changeChannelPassword(dto: ChangeChannelPasswordDto)
	{
		const user = await this.prisma.member.findUnique({
			where:{
				userId_channelId:{
					channelId: dto.channelId,
					userId: dto.userId
				}
			}
		});

		if (!user || user.role !== 'OWNER')
			throw new ForbiddenException(['You do not have permission to perform this action']);

		const hash = await argon.hash(dto.newPassword);
		await this.prisma.channel.update({
			data:{
				password: hash,
			},
			where:{
				id: dto.channelId
			}
		});
	}

	async switchChannelType(dto: SwitchChannelTypeDto)
	{
		const user = await this.prisma.member.findUnique({
			where:{
				userId_channelId:{
					channelId: dto.channelId,
					userId: dto.userId
				}
			}
		});

		if (!user || user.role !== 'OWNER')
			throw new ForbiddenException(['You do not have permission to perform this action']);


		let hash: string;

		if (dto.type === 'PROTECTED')
			hash = await argon.hash(dto.password);
		await this.prisma.channel.update({
			data:{
				type: dto.type,
				password: hash,
			},
			where:{
				id: dto.channelId
			}
		});
	}

	async deleteChannel(channelId: number)
	{
		await this.prisma.channel.delete({
			where:{
				id: channelId
			}
		});

		const room = this.chatGateway.server.sockets.adapter.rooms.get(String(channelId));
		if (room)
		{
			for (let socketId of room)
			{
				const socket = this.chatGateway.server.sockets.sockets.get(socketId);
				socket.leave(room);
			}
		};
	}

    async createChannel(dto : CreateChannelDto)
    {
        let hash : string;

        if (dto.type === 'PROTECTED')
            hash = await argon.hash(dto.password);
        try
        {
            const channel = await this.prisma.channel.create({
                data:{
                    name: dto.name,
                    type: dto.type,
                    password: hash,
                    members:{
                        create:{
                            userId: dto.userId,
                            role:   'OWNER'
                        }
                    }
                },
				select:{
					id: true,
					name: true,
					type: true
				}
            });
            return (channel);
        }
        catch(error)
        {
            if (error instanceof Prisma.PrismaClientKnownRequestError)
            {
                if (error.code === 'P2002')
                    throw new ConflictException( ["Channel With This Name Already Exist"] );
            }
			throw (error);
        }
        
    }

    async createDmChannel(userId : number, friendId : number)
    {
        const channel = await this.prisma.channel.findFirst({
            where:{
                type: 'DM',
                AND:[ 
                    { members: { some:{userId: userId} } }, 
                    { members: {some:{userId: friendId}} }
                ]
            },
            include:{
                members:true
            }
            
        });

        if (channel) {
            return;
        }

		const new_channel = await this.prisma.channel.create({
			data:{
				type: 'DM',
				members:{
					create:[{
						userId: userId,
					},{
						userId: friendId,
					}],
				}
			},
			include:{
				members: true
			}
		});
    }

	async deleteDmChannel(userId: number, friendId: number)
	{
        const channel = await this.prisma.channel.findFirst({
            where:{
                type: 'DM',
                AND:[ 
                    { members: { some:{userId: userId} } }, 
                    { members: {some:{userId: friendId}} }
                ]
            },
            include:{
                members:true
            }
            
        });

		if (!channel || channel.members[0].status !== 'ACTIVE') {
            throw new ForbiddenException( ['Forbidden Action'] );
        }

		await this.prisma.channel.delete({
			where:{
				id: channel.id,
			}
		});

		const room = this.chatGateway.server.sockets.adapter.rooms.get(String(channel.id));
		if (room)
		{
			for (let socketId of room)
			{
				const socket = this.chatGateway.server.sockets.sockets.get(socketId);
				socket.leave(room);
			}
		};
	}

    async wsAuth(socket: Socket) {
        const {'access-token' : access_token} = parse(socket.handshake.headers.cookie || '');
    
        try {
            const payload = await this.jwt.verify(access_token, {
                secret: this.config.get('JWT_ACCESS_SECRET')
            });
            return (payload.userId);
        }
        catch (error) 
		{
            socket.emit('must-login');
			socket.disconnect();
        }
    }

	async sendMessage(client: Socket, dto: MessageDto)
	{
		const errors = await validate(dto);
		if (errors.length)
			return;
		
		const member = await this.prisma.member.findUnique({
			where:{
				userId_channelId:{
					channelId: dto.channelId,
					userId: dto.userId
				}
			}
		});

		if (!member || member.status !== 'ACTIVE')
			return;

		const message = await this.prisma.message.create({
			data:{
				channelId: dto.channelId,
				from: dto.userId,
				message: dto.message,
			},
			include:{
				user:{
					select:{
						name: true,
					}
				},
			}
		});

		let result = {
			username: message.user.name,
			message: message.message,
			isGameInvite: message.isGameInvite, 
			mine: false
		}

		client.to(dto.roomId).emit('message', result);
		result.mine = true;
		this.chatGateway.server.to(client.id).emit('message', result);
	}

	async join(client: Socket, dto: ListenDto)
	{
		const errors = await validate(dto);
		if (errors.length)
			return;

		const member = await this.prisma.member.findUnique({
			where:{
				userId_channelId:{
					channelId: dto.channelId,
					userId: dto.userId
				}
			}
		});

		if (!member || member.status === 'BANNED')
			return;

		client.join(dto.roomId);
	}

	async leave(client: Socket, dto: LeaveDto)
	{
		const errors = await validate(dto);
		if (errors.length)
			return;

		if (client.rooms.has(dto.roomId))
			client.leave(dto.roomId);
	}

	async inviteToGame(client: Socket, dto: InviteToGameDto)
	{
		const errors = await validate(dto);
		if (errors.length)
		{
			client.emit('toHome');
			return;
		}
		const channel = await this.prisma.channel.findUnique({
			where:{
				id: dto.channelId
			},
			include:{
				members:{
					include:{
						user: true
					}
				},
			}
		});

		if (!channel || channel.type !== 'DM')
		{
			client.emit('toHome');
			return;
		}
		const member = channel.members.find(member => member.userId === dto.userId);
		const other_member = channel.members.find(member => member.userId !== dto.userId);
		
		if (!member || member.status !== 'ACTIVE' || member.user.status === 'PLAYING')
		{
			client.emit('toHome');
			return;
		}

		const inviteId = `${member.userId}${other_member.userId}`;
		const message = await this.prisma.message.create({
			data:{
				channelId: dto.channelId,
				from: dto.userId,
				isGameInvite: true,
				message: `/play?mode=invite&id=${inviteId}`
			},
			include:{
				user:{
					select:{
						name: true,
					}
				}
			}
		});

		this.gameGateway.setInviteList(member.userId, other_member.userId);

		let result = {
			username: message.user.name,
			message: message.message,
			isGameInvite: message.isGameInvite, 
			mine: false
		}
		client.to(dto.roomId).emit('message', result);
		result.mine = true;
		this.chatGateway.server.to(client.id).emit('message', result);
		this.chatGateway.server.to(client.id).emit('toGameInterface', inviteId);
	}

	async disconnect(socket: Socket) 
	{	
		for (let key in this.socketsDictionary)
		{
			const index = this.socketsDictionary[key].indexOf(socket.id);
			if (index >= 0)
			{
				this.socketsDictionary[key].splice(index, 1);
				if (!this.socketsDictionary[key].length)
				{
					this.updateUserStatus(Number(key), 'OFFLINE');
					delete this.socketsDictionary[key];
				}
				return;
			}
		}

	}

	async changeSettings(dto: ChannelSettingDto)
	{
		const user = await this.prisma.member.findUnique({
			where:{
				userId_channelId:{
					channelId: dto.channelId,
					userId: dto.userId
				}
			},
			include:{
				channel: true
			}
		});

		if (!user || user.role !== 'OWNER')
			throw new ForbiddenException(['You do not have permission to perform this action']);

		let new_name = dto.name ? dto.name : user.channel.name;
		let hash = user.channel.password;
		if (dto.type === 'PROTECTED' || (user.channel.type === 'PROTECTED' && dto.password))
		{
			let passDto = new PasswordDto();
			passDto.password = dto.password;
			const errors = await validate(passDto);
			if (errors.length)
				return;
			hash = await argon.hash(dto.password);
		}
		try
		{
			const channel = await this.prisma.channel.update({
				data:{
					name: new_name,
					type: dto.type,
					password: hash,
				},
				where:{
					id: dto.channelId
				}
			});
			return (channel);
		}
		catch(error)
		{
			if (error instanceof Prisma.PrismaClientKnownRequestError && error.code === 'P2002')
				throw new ConflictException(["Channel With This Name Already Exist"]); 
			throw (error)
		}
	}

	async emitMessage(dto: EmitMessageDto)
	{
		const to : string = dto.to
		this.chatGateway.server.to(to).emit(dto.event, dto.message);
	}

	async updateUserStatus(userId: number, status: UserStatus)
	{
		await this.prisma.user.update({
			data:{
				status: status
			},
			where:{
				id: userId
			}
		});
	}

	@Cron(CronExpression.EVERY_MINUTE)
	async handleCron()
	{
		const current_date = new Date();
		await this.prisma.member.updateMany({
			data:{
				status: 'ACTIVE',
				muteExpiration: null,
				banExpiration: null,
			},
			where:{
				OR:[ 
					{banExpiration: { lte: current_date }}, 
					{muteExpiration:{ lte: current_date }}
				]
			}
		});
	}
}
