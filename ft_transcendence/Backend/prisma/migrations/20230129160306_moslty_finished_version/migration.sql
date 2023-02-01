-- CreateEnum
CREATE TYPE "UserStatus" AS ENUM ('ONLINE', 'OFFLINE', 'PLAYING');

-- CreateEnum
CREATE TYPE "MemberStatus" AS ENUM ('ACTIVE', 'MUTED', 'BANNED', 'BLOCKER', 'BLOCKED');

-- CreateEnum
CREATE TYPE "ChannelRole" AS ENUM ('OWNER', 'ADMIN', 'MEMBER');

-- CreateEnum
CREATE TYPE "ChannelType" AS ENUM ('DM', 'PUBLIC', 'PRIVATE', 'PROTECTED');

-- CreateEnum
CREATE TYPE "UserAchievement" AS ENUM ('WIN_A_GAME', 'WIN_THREE_GAMES', 'DENIAL');

-- CreateTable
CREATE TABLE "users" (
    "id" SERIAL NOT NULL,
    "name" TEXT NOT NULL,
    "avatar" TEXT NOT NULL DEFAULT 'public/avatars/avatar.png',
    "hashedRefreshToken" TEXT,
    "status" "UserStatus" NOT NULL DEFAULT 'OFFLINE',
    "achievements" "UserAchievement"[],
    "wins" INTEGER NOT NULL DEFAULT 0,
    "losses" INTEGER NOT NULL DEFAULT 0,
    "ladder" DOUBLE PRECISION NOT NULL DEFAULT 0,
    "email" TEXT NOT NULL,
    "tfa" BOOLEAN NOT NULL DEFAULT false,
    "tfaSecret" TEXT,

    CONSTRAINT "users_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "Friend" (
    "userId" INTEGER NOT NULL,
    "friendId" INTEGER NOT NULL,

    CONSTRAINT "Friend_pkey" PRIMARY KEY ("userId","friendId")
);

-- CreateTable
CREATE TABLE "Channel" (
    "id" SERIAL NOT NULL,
    "password" TEXT,
    "name" TEXT,
    "type" "ChannelType" NOT NULL,

    CONSTRAINT "Channel_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "Member" (
    "channelId" INTEGER NOT NULL,
    "userId" INTEGER NOT NULL,
    "status" "MemberStatus" NOT NULL DEFAULT 'ACTIVE',
    "role" "ChannelRole" NOT NULL DEFAULT 'MEMBER',
    "banExpiration" TIMESTAMP(3),
    "muteExpiration" TIMESTAMP(3),

    CONSTRAINT "Member_pkey" PRIMARY KEY ("userId","channelId")
);

-- CreateTable
CREATE TABLE "Message" (
    "id" SERIAL NOT NULL,
    "channelId" INTEGER NOT NULL,
    "from" INTEGER NOT NULL,
    "message" TEXT NOT NULL,
    "isGameInvite" BOOLEAN NOT NULL DEFAULT false,
    "sendAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT "Message_pkey" PRIMARY KEY ("id")
);

-- CreateTable
CREATE TABLE "Game" (
    "id" SERIAL NOT NULL,
    "createdAt" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "player1" INTEGER NOT NULL,
    "player2" INTEGER NOT NULL,
    "player1score" INTEGER NOT NULL,
    "player2score" INTEGER NOT NULL,

    CONSTRAINT "Game_pkey" PRIMARY KEY ("id")
);

-- CreateIndex
CREATE UNIQUE INDEX "users_name_key" ON "users"("name");

-- CreateIndex
CREATE UNIQUE INDEX "Channel_name_key" ON "Channel"("name");

-- AddForeignKey
ALTER TABLE "Friend" ADD CONSTRAINT "Friend_userId_fkey" FOREIGN KEY ("userId") REFERENCES "users"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Friend" ADD CONSTRAINT "Friend_friendId_fkey" FOREIGN KEY ("friendId") REFERENCES "users"("id") ON DELETE RESTRICT ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Member" ADD CONSTRAINT "Member_channelId_fkey" FOREIGN KEY ("channelId") REFERENCES "Channel"("id") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Member" ADD CONSTRAINT "Member_userId_fkey" FOREIGN KEY ("userId") REFERENCES "users"("id") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Message" ADD CONSTRAINT "Message_channelId_fkey" FOREIGN KEY ("channelId") REFERENCES "Channel"("id") ON DELETE CASCADE ON UPDATE CASCADE;

-- AddForeignKey
ALTER TABLE "Message" ADD CONSTRAINT "Message_from_fkey" FOREIGN KEY ("from") REFERENCES "users"("id") ON DELETE CASCADE ON UPDATE CASCADE;
