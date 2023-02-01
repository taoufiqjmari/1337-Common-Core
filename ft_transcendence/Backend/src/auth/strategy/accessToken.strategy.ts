import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { PassportStrategy } from '@nestjs/passport';
import { PrismaService } from 'src/prisma/prisma.service';
import { ExtractJwt, Strategy } from 'passport-jwt';
import { Request } from 'express';

@Injectable()
export class AccessTokenStrategy extends PassportStrategy(Strategy, 'jwt') {
	constructor(config: ConfigService, private readonly prisma: PrismaService) {
		super({
			ignoreExpiration: false,
			secretOrKey: config.get('JWT_ACCESS_SECRET'),
			jwtFromRequest: ExtractJwt.fromExtractors([
				(request: Request) => {
					let data = request?.cookies['access-token'];
					if (!data) return null;
					return data;
				},
			]),
		});
	}

	async validate(payload: {
		userId: number;
		isSecondFactorAuthenticated: boolean;
	}) {
		const user = await this.prisma.user.findUnique({
			where: { id: payload.userId },
		});
		if (!user.tfa || payload.isSecondFactorAuthenticated) {
			return user;
		}
	}
}
