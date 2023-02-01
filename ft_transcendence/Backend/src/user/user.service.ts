import { Injectable, BadRequestException } from '@nestjs/common';
import { PrismaService } from 'src/prisma/prisma.service';
import { join } from 'path';
import { Prisma } from '@prisma/client';
import { ChatService } from 'src/chat/chat.service';
import { NotFoundException } from '@nestjs/common/exceptions';

const select = {
	id: true,
	name: true,
	status: true,
	achievements: true,
	wins: true,
	losses: true,
	ladder: true,
	email: true,
	tfa: true,
};

@Injectable()
export class UserService {
	constructor(
		private prisma: PrismaService,
		private chatService: ChatService,
	) {}
	async getAll() {
		const users = await this.prisma.user.findMany({ select });
		return users;
	}

	async getById(myId, userId) {
		const user = await this.prisma.user.findUnique({
			where: { id: userId },
			select,
		});
		if (!user)
			throw new NotFoundException(`User with id ${userId} not found`);

		const myFriends = await this.prisma.friend.findMany({
			where: { OR: [{ userId: myId }, { friendId: myId }] },
		});
		const friends = myFriends.map((friendship) =>
			friendship.userId === myId
				? friendship.friendId
				: friendship.userId,
		);
		user['isFriend'] = friends.includes(userId)
			? 'YES'
			: myId === userId
			? 'ME'
			: 'NO';

		return user;
	}

	async editUser(id, dto) {
		// check if user with id exists
		const userExist = await this.prisma.user.findUnique({ where: { id } });
		if (!userExist)
			throw new NotFoundException(`User with id ${id} not found`);

		// Limit the name property to the first 10 characters, and ensure that it is only alphanumeric
		if (dto.name)
			dto.name = dto.name.substring(0, 10).replace(/[^a-zA-Z0-9]/g, '');

		let updatedUser;
		try {
			updatedUser = await this.prisma.user.update({
				where: { id },
				data: { ...dto },
				select,
			});
		} catch (e) {
			if (e instanceof Prisma.PrismaClientKnownRequestError) {
				if (e.code === 'P2002') {
					throw new BadRequestException(
						'User with same credentials already exists',
					);
				}
			}
		}
		return updatedUser;
	}

	// Avatar
	async setAvatar(id, path) {
		const user = await this.prisma.user.update({
			where: { id },
			data: { avatar: path },
		});
		return user;
	}

	async getAvatar(id, res) {
		const user = await this.prisma.user.findUnique({
			where: { id },
		});
		if (!user) throw new BadRequestException("User doesn't exist");

		const filePath = join(process.cwd(), user.avatar);
		res.sendFile(filePath);
	}

	// Friends
	async addFriend(userId, friendId) {
		try {
			// Check if the friendship already exists
			let friendship = await this.prisma.friend.findFirst({
				where: {
					userId,
					friendId,
				},
			});
			if (!friendship) {
				friendship = await this.prisma.friend.findFirst({
					where: {
						userId: friendId,
						friendId: userId,
					},
				});
			}
			// if friendship does not exist, create it
			if (!friendship) {
				await this.prisma.friend.create({
					data: {
						userId,
						friendId,
					},
				});
			}
		} catch (e) {
			if (e instanceof Prisma.PrismaClientKnownRequestError) {
				if (e.code === 'P2002')
					throw new BadRequestException(
						'Friendship with same credentials already exists',
					);
			}
		}
		this.chatService.createDmChannel(userId, friendId);
	}

	// Requests all friendships and selects only the field with the friendId value (it can be userId or friendId).
	async getFriends(userId) {
		const friends = await this.prisma.friend.findMany({
			where: {
				OR: [{ userId: userId }, { friendId: userId }],
			},
		});
		const selectFriendId = friends.map((friend) => {
			return friend.userId === userId
				? { friendId: friend.friendId }
				: { friendId: friend.userId };
		});
		return selectFriendId;
	}

	async unfriend(userId, friendId) {
		// This function is to stop the deleting in case one of the users is blocking the other
		this.chatService.deleteDmChannel(userId, friendId);

		try {
			await this.prisma.friend.delete({
				where: { userId_friendId: { userId, friendId } },
			});
		} catch (e) {
			try {
				await this.prisma.friend.delete({
					where: {
						userId_friendId: { userId: friendId, friendId: userId },
					},
				});
			} catch (e) {
				if (
					e instanceof Prisma.PrismaClientKnownRequestError &&
					e.code === 'P2025'
				) {
					throw new BadRequestException("Friendship doesn't exist");
				}
			}
		}
	}

	// useful
	async seeds() {
		try {
			let data = [];
			for (let i = 0; i < 10; i++) {
				data.push({
					name: `User${i + 1}`,
					email: `user${i + 1}@email.com`,
					wins: Math.floor(Math.random() * 10),
					losses: Math.floor(Math.random() * 10),
					ladder: Math.floor(Math.random() * 10),
				});
			}
			const addedUsers = await this.prisma.user.createMany({
				data: data,
			});

			return { created: addedUsers };
		} catch (e) {
			if (
				e instanceof Prisma.PrismaClientKnownRequestError &&
				e.code === 'P2002'
			) {
				throw new BadRequestException(
					'Users with same credentials already exists',
				);
			} else {
				throw e;
			}
		}
	}
}
