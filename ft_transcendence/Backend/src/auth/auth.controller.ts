import { Controller, Get, Query, Res, Req, UseGuards } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { AuthService } from './auth.service';
import { Response } from 'express';
import { UserService } from 'src/user/user.service';
import { AccessTokenGuard, RefreshTokenGuard } from './guard';

@Controller('auth')
export class AuthController {
	constructor(
		private readonly authService: AuthService,
		private readonly configService: ConfigService,
		private readonly userService: UserService,
	) {}

	@Get('login')
	login(@Res() res: Response) {
		res.redirect(this.configService.get('42_OAUTH_URI'));
	}

	@Get('callback')
	async authCallback(@Query('code') code: string, @Res() res: Response) {
		// Redirect to ROOT_PAGE if user does not authenticate
		if (!code) {
			res.redirect(this.configService.get('ROOT_PAGE'));
		} else {
			const ret = await this.authService.authCallback(res, code);
			if (ret === false)
				res.redirect(this.configService.get('PROFILE_PAGE'));
		}
	}

	@UseGuards(RefreshTokenGuard)
	@Get('refresh')
	async refreshTokens(@Req() req, @Res() res) {
		await this.authService.refreshTokens(res, req.user);
	}

	@UseGuards(AccessTokenGuard)
	@Get('logout')
	async logout(@Req() req, @Res() res) {
		await this.userService.editUser(req.user.id, {
			hashedRefreshToken: null,
		});
		res.clearCookie('access-token').clearCookie('refresh-token');
		res.redirect(this.configService.get('ROOT_PAGE'));
	}
}
