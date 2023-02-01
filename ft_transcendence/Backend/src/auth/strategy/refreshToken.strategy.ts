import { Injectable, UnauthorizedException } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { PassportStrategy } from '@nestjs/passport';
import { PrismaService } from 'src/prisma/prisma.service';
import { ExtractJwt, Strategy } from 'passport-jwt';
import { Request } from 'express';

@Injectable()
export class RefreshTokenStrategy extends PassportStrategy(
	Strategy,
	'jwt-refresh',
) {
	constructor(config: ConfigService, private prisma: PrismaService) {
		super({
			secretOrKey: config.get('JWT_REFRESH_SECRET'),
			jwtFromRequest: ExtractJwt.fromExtractors([
				(request: Request) => {
					let data = request?.cookies['refresh-token'];
					if (!data) return null;
					return data;
				},
			]),
			ignoreExpiration: false,
		});
	}

	async validate(payload: { userId: number }) {
		if (!payload.userId) {
			throw new UnauthorizedException();
		}
		const user = await this.prisma.user.findUnique({
			where: { id: payload.userId },
		});
		if (!user) {
			throw new UnauthorizedException();
		}
		return user;
	}
}
