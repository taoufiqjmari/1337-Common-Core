import { Module } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { AuthService } from 'src/auth/auth.service';
import { UserService } from 'src/user/user.service';
import { TfaController } from './tfa.controller';
import { TfaService } from './tfa.service';

@Module({
	imports: [],
	controllers: [TfaController],
	providers: [UserService, TfaService, AuthService, JwtService],
})
export class TfaModule {}
