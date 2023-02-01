import { Global, Module } from '@nestjs/common';
import { GameGateway } from './game.gateway';
import { GameService } from './game.service';
import { GameController } from './game.controller';
import { DataService } from './data.service';
import { JwtModule } from '@nestjs/jwt';

@Global()
@Module({
	imports: [JwtModule],
	providers: [GameGateway, GameService, DataService],
	controllers: [GameController],
	exports: [GameGateway],
})
export class GameModule {}
