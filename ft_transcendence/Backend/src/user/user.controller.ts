import {
	Body,
	Controller,
	Get,
	Param,
	ParseIntPipe,
	Post,
	Put,
	Req,
	Res,
	UploadedFile,
	UseGuards,
	UseInterceptors,
} from '@nestjs/common';
import { HttpStatus } from '@nestjs/common/enums';
import { HttpException } from '@nestjs/common/exceptions';
import { FileInterceptor } from '@nestjs/platform-express';
import { diskStorage } from 'multer';
import { AccessTokenGuard } from 'src/auth/guard';
import { EditUserDto } from './dto';
import { UserService } from './user.service';

function generateRandomFileName(req, file, callback) {
	const possibleCharacters = '0123456789';
	let fileName = 'avatar';
	for (let i = 0; i < 5; i++) {
		fileName += possibleCharacters.charAt(
			Math.floor(Math.random() * possibleCharacters.length),
		);
	}
	callback(null, fileName + '.jpeg');
}

@UseGuards(AccessTokenGuard)
@Controller('users')
export class UserController {
	constructor(private userService: UserService) {}
	@Get()
	getAll() {
		return this.userService.getAll();
	}

	@Get('me')
	getMe(@Req() req) {
		delete req.user.hashedRefreshToken;
		delete req.user.tfaSecret;
		return req.user;
	}

	// useful
	@Post('seeds')
	seeds() {
		return this.userService.seeds();
	}
	// useful

	@Put('edit')
	editUser(@Req() req, @Body() dto: EditUserDto) {
		return this.userService.editUser(req.user.id, dto);
	}

	// Friends
	@Post('addfriend')
	addFriend(
		@Req() req,
		@Body('friendId', ParseIntPipe) friendId: number,
	) {
		return this.userService.addFriend(req.user.id, friendId);
	}

	@Get('friends')
	getFriends(@Req() req) {
		return this.userService.getFriends(req.user.id);
	}

	@Post('unfriend')
	unfriend(@Req() req, @Body('friendId', ParseIntPipe) friendId: number) {
		return this.userService.unfriend(req.user.id, friendId);
	}

	@Post('avatar')
	@UseInterceptors(
		FileInterceptor('avatar', {
			storage: diskStorage({
				destination: './public/avatars',
				filename: generateRandomFileName,
			}),
			fileFilter: function (req, file, callback) {
				if (!file.originalname.match(/.(jpg|jpeg|png)$/)) {
					return callback(undefined, false);
				}
				callback(undefined, true);
			},
			limits: {
				fileSize: 1000000,
			},
		}),
	)
	setAvatar(@Req() req, @UploadedFile() avatar: Express.Multer.File) {
		if (!avatar) {
			throw new HttpException(
				'Invalid file',
				HttpStatus.UNPROCESSABLE_ENTITY,
			);
		}
		return this.userService.setAvatar(req.user.id, avatar.path);
	}

	@Get('avatar/:userId')
	getAvatarById(@Param('userId', ParseIntPipe) userId: number, @Res() res) {
		return this.userService.getAvatar(userId, res);
	}

	@Get(':userId')
	getById(@Req() req, @Param('userId', ParseIntPipe) userId: number) {
		return this.userService.getById(req.user.id, userId);
	}
}
