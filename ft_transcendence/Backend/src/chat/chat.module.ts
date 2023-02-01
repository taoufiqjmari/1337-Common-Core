import { Module } from '@nestjs/common';
import { ChatService } from './chat.service';
import { ChatController } from './chat.controller';
import { ChatGateway } from './chat.gateway';
import { Global } from '@nestjs/common/decorators';
import { JwtModule } from '@nestjs/jwt';

@Global()
@Module({
  imports: [JwtModule],
  providers: [ChatService, ChatGateway],
  controllers: [ChatController],
  exports: [ChatService]
})
export class ChatModule {}
