import { Controller, UseGuards, Get, Post, Redirect, Req, Res, Param, Query, Body, ParseIntPipe, Delete, HttpCode } from '@nestjs/common';
import { IsDateString } from 'class-validator';
import { Response } from 'express';
import { AccessTokenGuard } from 'src/auth/guard';
import { ChatService } from './chat.service';
import { 
    ChangeChannelNameDto, 
    ChangeChannelPasswordDto, 
    ChannelSettingDto, 
    CreateChannelDto, 
    JoinChannelDto, 
    LeaveChannelDto, 
    SwitchChannelTypeDto } from './dto/channel.dto';
import { 
    AddMemberDto, 
    BanMemberDto, 
    DemoteMemberDto, 
    KickMemberDto, 
    MuteMemberDto, 
    PromoteMemberDto, 
    UnbanMemberDto, 
    UnmuteMemberDto } from './dto/member.dto';

@UseGuards(AccessTokenGuard)
@Controller('chat')
export class ChatController {

    constructor(
        private chatService : ChatService
    ) {}

    @Get()
    async getChannels(
        @Req() req )
    {
        const userId = req.user.id;  
        return (await this.chatService.getChannels(userId));    
    }

    @Get('search')
    async searchChannel(
        @Req() req, 
        @Query('name') channel_name?: string) 
    {
        const userId = req.user.id;
        return (await this.chatService.searchChannel(userId, channel_name) );
    }

    @Get(':channelId')
    async getMessages(
        @Req() req, 
        @Param('channelId', ParseIntPipe) channelId : number, 
        @Res({passthrough: true}) res: Response)
    {
        const userId = req.user.id;
        return (await this.chatService.getMessages(channelId, userId) );
    }

    @Get('/:channelId/search')
    async searchUsers(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Query('name') user_name?: string) 
    {
        const userId = req.user.id;
        return (await this.chatService.searchUsers(channelId, userId, user_name));
    }

    @Post('/:channelId/join')
    async joinChannel(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId,
        @Body() payload)
    {
        const userId = req.user.id;
        const dto = new JoinChannelDto();

        dto.channelId = channelId;
        dto.userId = userId;
        dto.password = payload.password || '';
        
        return (await this.chatService.joinChannel(dto));
    }

    @Post('/:channelId/leave')
    async leaveChannel(
		@Req() req, 
		@Param('channelId', ParseIntPipe) channelId, 
		@Body() payload)
	{
        const userId = req.user.id;
        const dto = new LeaveChannelDto();
        
        dto.channelId = channelId;
        dto.userId = userId;
        dto.nextOwnerId = Number(payload.nextOwnerId); 

        return (await this.chatService.leaveChannel(dto));
    }

    @Post('/:channelId/ban')
    async banMember(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Body() payload) 
    {
        const userId = req.user.id;
        const dto = new BanMemberDto();
        
        dto.channelId = channelId;
        dto.userId = userId;
        dto.targetId = Number(payload.targetId);

        return (await this.chatService.banMember(dto));
    }
 
    @Post('/:channelId/unban')
    async unbanMember(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Body() payload) 
    {
        const userId = req.user.id;
        const dto = new UnbanMemberDto();
        
        dto.channelId = channelId;
        dto.userId = userId;
        dto.targetId = Number(payload.targetId);
        
        return (await this.chatService.unbanMember(dto));
    }

    @Post('/:channelId/mute')
    async muteMember(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Body() payload) 
    {
        const userId = req.user.id;
        const dto = new MuteMemberDto();

        dto.channelId = channelId;
        dto.userId = userId;
        dto.targetId = Number(payload.targetId);
        
        return (await this.chatService.muteMember(dto));
    }

    @Post('/:channelId/unmute')
    async unmuteMember(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Body() payload) 
    {
        const userId = req.user.id;
        const dto = new UnmuteMemberDto();

        dto.channelId = channelId;
        dto.userId = userId;
        dto.targetId = Number(payload.targetId);

        return (await this.chatService.unmuteMember(dto));
    }

    @Post('/:channelId/block')
    async blockfriend(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,) 
    {
        const userId = req.user.id;
        return (await this.chatService.blockFriend(channelId, userId) );
    }

    @Post('/:channelId/unblock')
    async unblockfriend(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,) 
    {
        const userId = req.user.id;
        return (await this.chatService.unblockFriend(channelId, userId) );
    }

    @Post('/:channelId/add')
    async addMember(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Body() payload)
    {
        const userId = req.user.id;
        const dto = new AddMemberDto();
        
        dto.channelId = channelId;
        dto.userId = userId;
        dto.username = payload.username;
        return (await this.chatService.addMember(dto));
    }

    @Post('/:channelId/promote')
    async promoteMember(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Body() payload)
    {
        const userId = req.user.id;
        const dto = new PromoteMemberDto();
        
        dto.channelId = channelId;
        dto.userId = userId;
        dto.targetId = Number(payload.targetId);
        return (await this.chatService.promoteMember(dto));
    }

    @Post('/:channelId/demote')
    async demoteMember(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Body() payload)
    {
        const userId = req.user.id;
        const dto = new DemoteMemberDto();
        
        dto.channelId = channelId;
        dto.userId = userId;
        dto.targetId = Number(payload.targetId);
        return (await this.chatService.demoteMember(dto));
    }

    @Post('/:channelId/kick')
    async kickMember(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Body() payload)
    {
        const userId = req.user.id;
        const dto = new KickMemberDto();
        
        dto.channelId = channelId;
        dto.userId = userId;
        dto.targetId = Number(payload.targetId);
        return (await this.chatService.kickMember(dto));
    }

    @HttpCode(200)
    @Post('/:channelId/changeName')
    async changeChannelName(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Body() dto: ChangeChannelNameDto) 
    {
        const userId = req.user.id;

        dto.channelId = channelId;
        dto.userId = userId;
        return (await this.chatService.changeChannelName(dto));
    }

    @HttpCode(200)
    @Post('/:channelId/changePassword')
    async changeChannelPassword(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Body() dto: ChangeChannelPasswordDto ) 
    {
        const userId = req.user.id;

        dto.channelId = channelId;
        dto.userId = userId;
        return (await this.chatService.changeChannelPassword(dto));
    }


    @HttpCode(200)
    @Post('/:channelId/switchType')
    async switchChannelType(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Body() dto: SwitchChannelTypeDto) 
    {
        const userId = req.user.id;

        dto.channelId = channelId;
        dto.userId = userId;
        return (await this.chatService.switchChannelType(dto));
    }

    @Post('/:channelId/changeSettings')
    async changeSettings(
        @Req() req,
        @Param('channelId', ParseIntPipe) channelId : number,
        @Body() dto : ChannelSettingDto)
    {
        const userId = req.user.id;

        dto.channelId = channelId;
        dto.userId = userId;
        return (await this.chatService.changeSettings(dto));
    }

    @Post('createChannel')
    async createChannel(
        @Req() req, 
        @Body() dto : CreateChannelDto) 
    {
        const userId = req.user.id;
        
        dto.userId = userId
        return (await this.chatService.createChannel(dto));
    }
}
