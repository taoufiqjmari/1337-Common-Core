import {
	Body,
	Controller,
	Get,
	Param,
	Post,
	UseGuards,
} from '@nestjs/common/decorators';
import { AccessTokenGuard } from 'src/auth/guard';
import { DataService } from './data.service';
import { AddGameDTO } from './dto';
import { ParseIntPipe } from '@nestjs/common';

@UseGuards(AccessTokenGuard)
@Controller('game')
export class GameController {
	constructor(private dataService: DataService) {}
	@Post()
	addGame(@Body() gameData: AddGameDTO) {
		return this.dataService.addGame(gameData);
	}

	@Get('/:userId')
	getPlayerGames(@Param('userId', ParseIntPipe) userId: number) {
		return this.dataService.getPlayerGames(userId);
	}
}
