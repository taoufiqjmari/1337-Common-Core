import { Socket } from "socket.io";
import { GameService } from "../game.service";

export type Paddle = {
    x:number, 
    y:number, 
    width:number, 
    height:number, 
    score:number, 
    color:string,
};

export type Net = {
    x:number, 
    y:number, 
    width:number, 
    height:number, 
    color:string,
};

export type Ball = {
    x:number, 
    y:number, 
    radius:number, 
    speed:number, 
    velocityX:number, 
    velocityY:number, 
    color:string,
}

export type ScorePosition = {
    x:number, 
    y:number,
    size:string, 
}

export type User = {
    id: string,
    name?: string,
    clientSock?: Socket,
}
  
export type Room = {
    name: string,
    id: string,
    players: User[],
    viewers: User[],
    gameObj: GameService,
    mode: string,
}