import { ChannelType, ChannelRole } from "@prisma/client"
import { IsNotEmpty, IsString, IsIn, ValidateIf, IsInt, IsPositive, IsDate } from "class-validator"

export class BanMemberDto {

    channelId:      number;
    userId:         number;
    
    @IsInt()
    @IsPositive()
    targetId:       number;
}

export class UnbanMemberDto {
    
    channelId:      number;
    userId:         number;
    
    @IsInt()
    @IsPositive()
    targetId:       number;
}

export class MuteMemberDto {
    
    channelId:      number;
    userId:         number;

    @IsInt()
    @IsPositive()
    targetId:       number;
    
}

export class UnmuteMemberDto {
    channelId:      number;
    userId:         number;

    @IsInt()
    @IsPositive()
    targetId:       number;
}

export class AddMemberDto {
    channelId: number;
    userId: number;

    @IsString()
    username: string;
}

export class KickMemberDto {
    channelId: number;
    userId: number;

    @IsInt()
    @IsPositive()
    targetId:       number;
}

export class PromoteMemberDto {
    channelId: number;
    userId: number;

    @IsInt()
    @IsPositive()
    targetId:       number;
}

export class DemoteMemberDto {
    channelId: number;
    userId: number;

    @IsInt()
    @IsPositive()
    targetId:       number;
}

export class EmitMessageDto
{
    to: string
    event: string
    message: any
}