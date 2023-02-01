import { Injectable } from '@nestjs/common';
import {Ball, Net, Paddle, ScorePosition} from './types/types'

@Injectable()
export class GameService {
    private CANVAS_WIDTH:number = 900;
    private CANVAS_HEIGHT:number = 500;
    private BALL_SPEED:number = 9;
    private FONT_SIZE:number = 4;

    private BALL_COLOR: string = '#38E1BB';
    private PADDLE_COLOR: string = '#3D52D5';
    private NET_COLOR: string = '#3D52D5bb';

    public player1: Paddle = {
        x: 10,
        y: this.CANVAS_HEIGHT/2 - ((this.CANVAS_HEIGHT/5)/2),
        width: 15,
        height: this.CANVAS_HEIGHT/5,
        score: 0,
        color: this.PADDLE_COLOR,
    }
    
    public player2: Paddle = {
        x: this.CANVAS_WIDTH - 15 - 10,
        y: this.CANVAS_HEIGHT/2 - ((this.CANVAS_HEIGHT/5)/2),
        width: 15,
        height: this.CANVAS_HEIGHT/5,
        score: 0,
        color: this.PADDLE_COLOR,
    }

    public net: Net = {
        x: this.CANVAS_WIDTH/2 - 5/2,
        y: 0,
        width: 5,
        height: 15,
        color: this.NET_COLOR,
    }

    public ball: Ball = {
        x: this.CANVAS_WIDTH/2,
        y: this.CANVAS_HEIGHT/2,
        radius: 10,
        speed: this.BALL_SPEED,
        velocityX: Math.floor(Math.random() * 2) == 0 ? this.BALL_SPEED : this.BALL_SPEED,
        velocityY: Math.floor(Math.random() * 2) == 0 ? this.BALL_SPEED : -this.BALL_SPEED,
        color: this.BALL_COLOR,
    }

    public score1Pos: ScorePosition = {
        x: this.CANVAS_WIDTH/4,
        y: 2 * this.CANVAS_HEIGHT/18,
        size: `${this.FONT_SIZE}rem`,
    }

    public score2Pos: ScorePosition = {
        x: 3 * this.CANVAS_WIDTH/4,
        y: 2 * this.CANVAS_HEIGHT/18,
        size: `${this.FONT_SIZE}rem`,
    }

    collision(ball:any, player:any){
        ball.top = ball.y - ball.radius;
        ball.bottom = ball.y + ball.radius;
        ball.left = ball.x - ball.radius;
        ball.right = ball.x + ball.radius;
        player.top = player.y;
        player.bottom = player.y + player.height;
        player.left = player.x;
        player.right = player.x + player.width;

        return (ball.top < player.bottom && ball.bottom > player.top && ball.right > player.left && ball.left < player.right);
    }

    resetBall(){
        this.ball.x = this.CANVAS_WIDTH/2;
        this.ball.y = this.CANVAS_HEIGHT/2;
        this.ball.speed = this.BALL_SPEED;
        this.ball.velocityX = this.ball.velocityX > 0 ? this.BALL_SPEED : -this.BALL_SPEED;
        this.ball.velocityY = Math.floor(Math.random() * 2) == 0 ? this.BALL_SPEED : -this.BALL_SPEED;
    }

    updateBall(gameMode:string){
        this.ball.x += this.ball.velocityX;
        this.ball.y += this.ball.velocityY;
        if ((this.ball.y + this.ball.radius + this.ball.velocityY) > this.CANVAS_HEIGHT || (this.ball.y - this.ball.radius + this.ball.velocityY) < 0){
            this.ball.velocityY *= -1;
        }
        if (gameMode == 'single')
            this.player2.y += (this.ball.y - (this.player2.y + this.player2.height/2)) * .115;
        const player = this.ball.x < this.CANVAS_WIDTH/2 ? this.player1 : this.player2;
        const concurrent = player === this.player1 ? this.player2 : this.player1;
        if (this.collision(this.ball, player)){
            if (this.ball.speed <= 15)
                this.ball.speed += .5;
            let collidepoint: number = this.ball.y - (player.y + player.height/2);
            collidepoint /= (player.height/2);
            const angle: number = (Math.PI/4) * collidepoint;
            const derection: number = this.ball.x < this.CANVAS_WIDTH/2 ? 1 : -1;
            this.ball.velocityX = this.ball.speed * Math.cos(angle) * derection;
            this.ball.velocityY = this.ball.speed * Math.sin(angle);
        }
        else if (this.ball.x + this.ball.radius <= 0 || this.ball.x - this.ball.radius >= this.CANVAS_WIDTH)
        {
            this.resetBall();
            concurrent.score++;
        }
    }

    playerMovement(mouseY: number, player: Paddle){
        mouseY -= (player.height/2);
        if (mouseY > 0  && mouseY < (this.CANVAS_HEIGHT - player.height))
            player.y = mouseY;
    }
}