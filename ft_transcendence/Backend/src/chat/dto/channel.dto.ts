import { ChannelType } from "@prisma/client"
import { IsNotEmpty, IsString, IsIn, ValidateIf, IsOptional, IsInt, IsPositive, IsNumber, IsStrongPassword, Length } from "class-validator"

export class CreateChannelDto {

    userId: number;

    @Length(4, 20)
    @IsString()
    @IsNotEmpty()
    name: string;

    @IsIn(['PUBLIC', 'PRIVATE', 'PROTECTED'])
    type: ChannelType;

    @ValidateIf(o => o.type === 'PROTECTED')
    @Length(6, 30)
    @IsString()
    @IsNotEmpty()
    password: string;
}

export class PasswordDto {
    @Length(6, 30)
    @IsString()
    password: string;
}

export class ChannelSettingDto {
    
    channelId: number;
    userId: number;

    @IsOptional()
    @Length(4, 20)
    @IsString()
    name: string;

    @IsOptional()
    @IsIn(['PUBLIC', 'PRIVATE', 'PROTECTED'])
    type: ChannelType;

    @ValidateIf(o => o.type === 'PROTECTED')
    @Length(6, 30)
    @IsString()
    @IsNotEmpty()
    password: string;

}

export class ChangeChannelNameDto {

    channelId: number;
    userId: number;

    @Length(4, 20)
    @IsString()
    newName: string;
}

export class ChangeChannelPasswordDto {

    channelId: number;
    userId: number;

    @Length(6, 30)
    @IsString()
    newPassword: string;
}

export class SwitchChannelTypeDto {

    channelId: number;
    userId: number;

    @IsIn(['PUBLIC', 'PRIVATE', 'PROTECTED'])
    type: ChannelType;

    @ValidateIf(o => o.type === 'PROTECTED')
    @Length(6, 30)
    @IsString()
    password: string;
}

export class JoinChannelDto {
    
    channelId:	number;
    userId:		number;
    
    @IsOptional()
    @IsString()
    password:	string;
}

export class LeaveChannelDto {
    
    channelId: number;
    userId: number;

    @IsInt()
    @IsPositive()
    nextOwnerId: number;
}

export class MessageDto {

    @IsInt()
    @IsPositive()
    channelId: number;

    roomId: string;

    userId: number;

    @Length(1, 300)
    @IsString()
    message: string;
}

export class ListenDto {

    @IsInt()
    @IsPositive()
    channelId: number;

    roomId: string;

    userId: number;
}

export class LeaveDto {

    @IsInt()
    @IsPositive()
    channelId: number;

    roomId: string;

    userId: number;
}

export class InviteToGameDto {

    @IsInt()
    @IsPositive()
    channelId: number;

    roomId: string;

    userId: number;
}