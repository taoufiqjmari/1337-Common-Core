import {
	IsString,
	MaxLength,
	MinLength,
	Matches,
} from 'class-validator';

export class TokenDto {
	@IsString()
	@MinLength(6, { message: 'token must be 6 characters long' })
	@MaxLength(6, { message: 'token must be 6 characters long' })
	@Matches(/^[0-9]*$/, { message: 'token must only contain numbers' })
	token: string;
}
