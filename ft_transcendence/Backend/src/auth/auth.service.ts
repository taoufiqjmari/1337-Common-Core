import { ForbiddenException, Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { JwtService } from '@nestjs/jwt';
import Authenticator from 'api42client';
import { Response } from 'express';
import { PrismaService } from 'src/prisma/prisma.service';
import * as argon2 from 'argon2';

@Injectable()
export class AuthService {
	constructor(
		private prisma: PrismaService,
		private jwtService: JwtService,
		private configService: ConfigService,
	) {}

	// Authenticator is a package made by ibaali, it does the go and back handshake of OAuth2.0.
	async authCallback(res: Response, code: string) {
		const UID = this.configService.get('42_UID');
		const SECRET = this.configService.get('42_SECRET');
		const REDIRECT_URI = this.configService.get('42_REDIRECT_URI');

		const auth = new Authenticator(UID, SECRET, REDIRECT_URI);
		const auth_data = await auth.get_Access_token(code);
		const auth_user = await auth.get_user_data(auth_data.access_token);

		// Find or create users if they don't exist and send access tokens
		let user = await this.prisma.user.findUnique({
			where: { id: auth_user.id },
		});
		if (user && user.tfa) {
			const tokens = await this.getTokens(user.id);
			res.cookie('access-token', tokens.accessToken, {
				httpOnly: true,
			}).cookie('userId', user.id, { httpOnly: true });
			res.redirect(this.configService.get('AUTH_TFA_PAGE'));
			return true;
		} else if (!user) {
			let name = 'user';
			name += this.randomNum(5);
			user = await this.prisma.user.create({
				data: {
					id: auth_user.id,
					name,
					email: auth_user.email,
				},
			});
		}
		const tokens = await this.getTokens(user.id, true);
		const hashedRefreshToken = await argon2.hash(tokens.refreshToken);
		await this.prisma.user.update({
			where: { id: user.id },
			data: { hashedRefreshToken },
		});
		res.cookie('access-token', tokens.accessToken, {
			httpOnly: true,
		}).cookie('refresh-token', tokens.refreshToken, { httpOnly: true });
		return false;
	}

	async refreshTokens(res, user) {
		if (!user.hashedRefreshToken)
			throw new ForbiddenException("Refresh token wasn't set before");
		const tokens = await this.getTokens(user.id, true);
		const hashedRefreshToken = await argon2.hash(tokens.refreshToken);
		await this.prisma.user.update({
			where: { id: user.id },
			data: { hashedRefreshToken },
		});
		res.cookie('access-token', tokens.accessToken, {
			httpOnly: true,
		}).cookie('refresh-token', tokens.refreshToken, { httpOnly: true });
		res.send();
	}

	// The second parameter is for TFA, if the user logs in with TFA enabled, it will only give access to the tfa/authenticate route to enter the token, and only then it gives full access tokens.
	async getTokens(userId: number, isSecondFactorAuthenticated = false) {
		const payload = { userId, isSecondFactorAuthenticated };
		const [accessToken, refreshToken] = await Promise.all([
			this.jwtService.signAsync(payload, {
				secret: this.configService.get<string>('JWT_ACCESS_SECRET'),
				expiresIn: '3h',
			}),
			this.jwtService.signAsync(payload, {
				secret: this.configService.get<string>('JWT_REFRESH_SECRET'),
				expiresIn: '7d',
			}),
		]);

		return {
			accessToken,
			refreshToken,
		};
	}

	randomNum(length): string {
		let result = '';
		let characters = '0123456789';
		for (let i = 0; i < length; i++)
			result += characters.charAt(
				Math.floor(Math.random() * characters.length),
			);
		return result;
	}
}
