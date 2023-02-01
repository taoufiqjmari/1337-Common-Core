import {
	BadRequestException,
	Body,
	Controller,
	HttpCode,
	Get,
	Post,
	Req,
	Res,
	UnauthorizedException,
	UseGuards,
} from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { AuthService } from 'src/auth/auth.service';
import { AccessTokenGuard } from 'src/auth/guard';
import { PrismaService } from 'src/prisma/prisma.service';
import { UserService } from 'src/user/user.service';
import { TokenDto } from './dto';
import { TfaService } from './tfa.service';

@Controller('tfa')
export class TfaController {
	constructor(
		private readonly tfaService: TfaService,
		private readonly userService: UserService,
		private readonly authService: AuthService,
		private readonly prisma: PrismaService,
		private readonly configService: ConfigService,
	) {}

	// It only generates the QR code for the user to scan.
	@UseGuards(AccessTokenGuard)
	@Get('generate')
	async register(@Res() response, @Req() req) {
		if (req.user.tfa)
			throw new BadRequestException('TFA is already enabled');
		const { otpauthUrl } = await this.tfaService.generateTFASecret(
			req.user,
		);
		return this.tfaService.pipeQrCodeStream(response, otpauthUrl);
	}

	// It enables TFA when the user enters the correct code from the Google Authenticator application.
	@UseGuards(AccessTokenGuard)
	@HttpCode(200)
	@Post('enable')
	async enableTFA(@Req() req, @Body() token: TokenDto) {
		const isCodeValid = this.tfaService.isTFACodeValid(
			token.token,
			req.user,
		);
		if (!isCodeValid)
			throw new UnauthorizedException('Wrong authentication code');
		await this.userService.editUser(req.user.id, { tfa: true });
	}

	// When the user logs in while TFA is enabled, he has to enter the code from Google Authentication, and if it is correct, the user gets full access tokens.
	@Post('authenticate')
	@HttpCode(200)
	async authenticate(@Req() req, @Res() res, @Body() token: TokenDto) {
		const user = await this.prisma.user.findUnique({
			where: { id: parseInt(req.cookies['userId']) },
		});
		const isCodeValid = this.tfaService.isTFACodeValid(token.token, user);
		if (!isCodeValid) {
			throw new UnauthorizedException('Wrong authentication code');
		}
		const tokens = await this.authService.getTokens(user.id, true);
		res.cookie('access-token', tokens.accessToken, {
			httpOnly: true,
		}).cookie('refresh-token', tokens.refreshToken, {
			httpOnly: true,
		});
		res.send();
	}

	// To disable TFA, the user must enter the code in the Google Authenticator application.
	@UseGuards(AccessTokenGuard)
	@HttpCode(200)
	@Post('disable')
	async disableTFA(@Req() req, @Body() token: TokenDto) {
		if (!req.user.tfa)
			throw new BadRequestException('TFA is already disabled');
		const isCodeValid = this.tfaService.isTFACodeValid(
			token.token,
			req.user,
		);
		if (!isCodeValid)
			throw new UnauthorizedException('Wrong authentication code');

		await this.userService.editUser(req.user.id, {
			tfa: false,
			tfaSecret: null,
		});
	}
}
