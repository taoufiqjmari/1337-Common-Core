import { Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { UserService } from 'src/user/user.service';
import { authenticator } from 'otplib';
import { toFileStream } from 'qrcode';

@Injectable()
export class TfaService {
	constructor(
		private readonly userService: UserService,
		private readonly configService: ConfigService,
	) {}

	async generateTFASecret(user) {
		const secret = authenticator.generateSecret();
		const otpauthUrl = authenticator.keyuri(
			user.email,
			this.configService.get('TWO_FACTOR_AUTHENTICATION_APP_NAME'),
			secret,
		);
		await this.userService.editUser(user.id, { tfaSecret: secret });
		return {
			secret,
			otpauthUrl,
		};
	}

	async pipeQrCodeStream(stream: Response, otpauthUrl: string) {
		return toFileStream(stream, otpauthUrl);
	}

	isTFACodeValid(token, user) {
		return authenticator.verify({
			token,
			secret: user.tfaSecret,
		});
	}
}
