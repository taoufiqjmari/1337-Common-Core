import {
	OnGatewayConnection,
	SubscribeMessage,
	WebSocketGateway,
	WebSocketServer,
} from '@nestjs/websockets';
import { OnGatewayDisconnect } from '@nestjs/websockets/interfaces';
import { Socket } from 'socket.io';
import { ChatService } from './chat.service';
import { Inject, forwardRef } from '@nestjs/common';
import {
	InviteToGameDto,
	LeaveDto,
	ListenDto,
	MessageDto,
} from './dto/channel.dto';
import { Logger } from '@nestjs/common';

@WebSocketGateway(5500, {
	cors: { origin: `http://${process.env.APPNAME}:3001`, credentials: true },
})
export class ChatGateway implements OnGatewayConnection, OnGatewayDisconnect {
	constructor(
		@Inject(forwardRef(() => ChatService))
		private chatService: ChatService,
	) {}
	private logger: Logger = new Logger('ChatGateway');

	@WebSocketServer()
	server;

	async handleConnection(client: Socket) {
		const userId = await this.chatService.wsAuth(client);
		if (!userId) return;
		if (this.chatService.socketsDictionary[userId])
			this.chatService.socketsDictionary[userId].push(client.id);
		else {
			this.chatService.socketsDictionary[userId] = [client.id];
			this.chatService.updateUserStatus(userId, 'ONLINE');
		}
	}

	async handleDisconnect(client: any) {
		this.chatService.disconnect(client);
	}

	@SubscribeMessage('message')
	async handleMessage(client, payload) {
		const userId = await this.chatService.wsAuth(client);
		if (!userId) return;

		const dto = new MessageDto();
		dto.channelId = Number(payload.channelId);
		dto.roomId = String(payload.channelId);
		dto.userId = userId;
		dto.message = payload.message;

		return await this.chatService.sendMessage(client, dto);
	}

	@SubscribeMessage('join')
	async handleListen(client, payload) {
		const userId = await this.chatService.wsAuth(client);
		if (!userId) return;

		const dto = new ListenDto();
		dto.channelId = Number(payload.channelId);
		dto.roomId = String(payload.channelId);
		dto.userId = userId;

		await this.chatService.join(client, dto);
	}

	@SubscribeMessage('leave')
	async handleLeave(client, payload) {
		const userId = await this.chatService.wsAuth(client);
		if (!userId) return;

		const dto = new LeaveDto();
		dto.channelId = Number(payload.channelId);
		dto.roomId = String(payload.channelId);
		dto.userId = userId;

		await this.chatService.leave(client, dto);
	}

	@SubscribeMessage('inviteToGame')
	async handleInviteToGame(client, payload) {
		const userId = await this.chatService.wsAuth(client);
		if (!userId) return;

		const dto = new InviteToGameDto();
		dto.channelId = Number(payload.channelId);
		dto.roomId = String(payload.channelId);
		dto.userId = userId;

		await this.chatService.inviteToGame(client, dto);
	}
}
