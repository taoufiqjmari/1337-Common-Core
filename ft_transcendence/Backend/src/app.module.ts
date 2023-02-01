import { Module } from '@nestjs/common';
import { ScheduleModule } from '@nestjs/schedule';
import { UserModule } from './user/user.module';
import { AuthModule } from './auth/auth.module';
import { PrismaModule } from './prisma/prisma.module';
import { ConfigModule } from '@nestjs/config';
import { GameModule } from './game/game.module';
import { ChatModule } from './chat/chat.module';
import { TfaModule } from './tfa/tfa.module';

@Module({
	imports: [
		ScheduleModule.forRoot(),
		ConfigModule.forRoot({ isGlobal: true }),
		UserModule,
		AuthModule,
		PrismaModule,
		GameModule,
		ChatModule,
		TfaModule,
	],
})
export class AppModule {}
