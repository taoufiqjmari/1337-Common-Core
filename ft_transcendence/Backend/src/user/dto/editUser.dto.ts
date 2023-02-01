import {
	IsOptional,
	IsString,
	IsEnum,
	IsBoolean,
	MinLength,
	MaxLength,
} from 'class-validator';
import { UserStatus } from '@prisma/client';

export class EditUserDto {
	@IsString()
	@IsOptional()
	@MinLength(3)
	@MaxLength(10)
	name?: string;

	@IsString()
	@IsOptional()
	avatar?: string;

	@IsString()
	@IsOptional()
	hashedRefreshToken?: string;

	@IsEnum(UserStatus)
	@IsOptional()
	status?: UserStatus;

	@IsBoolean()
	@IsOptional()
	tfa?: boolean;

	@IsString()
	@IsOptional()
	tfaSecret?: string;
}
