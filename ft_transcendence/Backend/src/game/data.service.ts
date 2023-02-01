import { BadRequestException, Injectable } from '@nestjs/common';
import { UserAchievement, UserStatus } from '@prisma/client';
import { PrismaService } from 'src/prisma/prisma.service';
import { AddGameDTO } from './dto';

@Injectable()
export class DataService {
	constructor(private readonly prisma: PrismaService) {}

	async getUser(userId: number) {
		const user = await this.prisma.user.findUnique({
			where: { id: userId },
		});
		return user;
	}

	async updateUserStatus(userId: number, status: UserStatus)
	{
		await this.prisma.user.update({
			data:{
				status: status
			},
			where:{
				id: userId
			}
		});
	}

	async addGame(gameData: AddGameDTO) {
		const { player1, player2, player1score, player2score } = gameData;

		const game = await this.prisma.game.create({
			data: {
				player1,
				player2,
				player1score,
				player2score,
			},
		});

		// Check users exist
		try {
			const user1 = await this.prisma.user.findUnique({
				where: { id: player1 },
			});
			const user2 = await this.prisma.user.findUnique({
				where: { id: player2 },
			});
			if (!user1 || !user2) throw new Error();
		} catch (e) {
			throw new BadRequestException('Users not found');
		}

		// Update users
		const [winner, loser] =
			player1score > player2score
				? [player1, player2]
				: [player2, player1];

		await this.prisma.user.update({
			where: { id: winner },
			data: { wins: { increment: 1 }, ladder: { increment: 10 } },
		});
		await this.prisma.user.update({
			where: { id: loser },
			data: { losses: { increment: 1 } },
		});

		const user1 = await this.prisma.user.findUnique({
			where: { id: player1 },
		});
		const user2 = await this.prisma.user.findUnique({
			where: { id: player2 },
		});

		await this.updateAchievements(user1, player2score === 0);
		await this.updateAchievements(user2, player1score === 0);

		return game;
	}

	async updateAchievements(user, denial: boolean) {
		const userId = user.id;
		const wins = user.wins;

		if (
			wins === 1 &&
			!user.achievements.includes(UserAchievement.WIN_A_GAME)
		) {
			await this.prisma.user.update({
				where: { id: userId },
				data: { achievements: { push: UserAchievement.WIN_A_GAME } },
			});
		} else if (
			wins === 3 &&
			!user.achievements.includes(UserAchievement.WIN_THREE_GAMES)
		) {
			await this.prisma.user.update({
				where: { id: userId },
				data: {
					achievements: { push: UserAchievement.WIN_THREE_GAMES },
				},
			});
		}
		if (denial && !user.achievements.includes(UserAchievement.DENIAL)) {
			await this.prisma.user.update({
				where: { id: userId },
				data: { achievements: { push: UserAchievement.DENIAL } },
			});
		}
	}

	async getPlayerGames(userId: number) {
		// Check users exist
		try {
			const user = await this.prisma.user.findUnique({
				where: { id: userId },
			});
			if (!user) throw new Error();
		} catch (e) {
			throw new BadRequestException('User not found');
		}
		// Find the last 5 games that the user has played
		const games = await this.prisma.game.findMany({
			where: {
				OR: [
					{ player1: { equals: userId } },
					{ player2: { equals: userId } },
				],
			},
			orderBy: { createdAt: 'desc' },
			skip: 0,
			take: 5,
		});

		let formattedGames = [];
		for (let i = 0; i < games.length; i++) {
			// Get players details
			const player1 = await this.prisma.user.findUnique({
				where: { id: games[i].player1 },
				select: { name: true },
			});
			const player2 = await this.prisma.user.findUnique({
				where: { id: games[i].player2 },
				select: { name: true },
			});

			// Put the games in the final object format
			formattedGames.push({
				player1name: player1.name,
				player1score: games[i].player1score,
				player2name: player2.name,
				player2score: games[i].player2score,
			});
		}
		return formattedGames;
	}
}
