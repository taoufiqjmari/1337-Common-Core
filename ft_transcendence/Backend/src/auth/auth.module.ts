import { Module } from '@nestjs/common';
import { JwtModule } from '@nestjs/jwt';
import { UserService } from 'src/user/user.service';
import { AuthController } from './auth.controller';
import { AuthService } from './auth.service';
import { AccessTokenStrategy, RefreshTokenStrategy } from './strategy';

@Module({
	imports: [JwtModule.register({})],
	controllers: [AuthController],
	providers: [
		AuthService,
		UserService,
		AccessTokenStrategy,
		RefreshTokenStrategy,
	],
	exports: [AuthService],
})
export class AuthModule {}
