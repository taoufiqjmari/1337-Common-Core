import { IsNumber, Max, Min } from 'class-validator';

export class AddGameDTO {
	@IsNumber()
	player1?: number;

	@IsNumber()
	player2?: number;

	@IsNumber()
	@Min(0)
	@Max(11)
	player1score?: number;

	@IsNumber()
	@Min(0)
	@Max(11)
	player2score?: number;
}
