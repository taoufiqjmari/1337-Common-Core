import { Logger } from '@nestjs/common';
import {OnGatewayConnection, OnGatewayDisconnect, SubscribeMessage, WebSocketGateway, WebSocketServer } from '@nestjs/websockets';
import { Server, Socket } from "socket.io";
import {Room, User} from './types/types'
import { GameService } from './game.service';
import { ConfigService } from '@nestjs/config';
import { DataService } from './data.service';
import { JwtService } from '@nestjs/jwt';
import { parse } from 'cookie';

@WebSocketGateway(5500, { cors: { origin: `http://${process.env.APPNAME}:3001`, credentials: true } })
export class GameGateway implements OnGatewayConnection, OnGatewayDisconnect{
  //! attributes
  private rooms: Room[] = new Array<Room>;
  private intervals: NodeJS.Timer[] = new Array<NodeJS.Timer>;
  private waitlist: User[] = new Array<User>;
  private logger: Logger = new Logger('GameGateway');
  
  private socketList: Map<string, string[]> =  new  Map<string, string[]>;
  private playingSocket: Map<string, string[]> = new Map<string, string[]>;
  private inviteList: Map<string, User[]> = new  Map<string, User[]>;

  //! init
  @WebSocketServer()
  server: Server;
  
  constructor(private config: ConfigService, private jwt: JwtService, private dataService: DataService){};

  async handleConnection(client: Socket) {
    const userId = await this.wsAuth(client);
    if (!userId) return;

    if (this.socketList.get(userId))
      this.socketList.get(userId).push(client.id);
    else
      this.socketList.set(userId, [client.id]);
  }         
  
  async handleDisconnect(client: any) {
    const userId = await this.wsAuth(client);
    if (!userId) return;

    this.waitlist.forEach((currentClient, index)=>{
      if(currentClient.id == userId)
        this.waitlist.splice(index, 1);
    });
    
    const currentRoom = this.rooms.find((currentRoom) => {
      return (currentRoom.players[0].clientSock.id == client.id || currentRoom.players[1].clientSock.id == client.id);
    });
    if (currentRoom && currentRoom.mode == 'multi')
      this.Punisher(client.id);
    else if (currentRoom && currentRoom.mode  == 'single')
      this.endGame(client.id);

    
    // check user status
    this.playingSocket.get(userId)?.forEach((currentSockId, index)=>{
      if (currentSockId == client.id)
        this.playingSocket.get(userId).splice(index, 1);
    });
    this.socketList.get(userId)?.forEach((currentSockId, index)=>{
      if (currentSockId == client.id)
        this.socketList.get(userId).splice(index, 1);
    });

    if(this.playingSocket.get(userId)?.length) return;
    if (!this.socketList.get(userId).length){
      this.dataService.updateUserStatus(userId, 'OFFLINE');
      this.socketList.delete(userId);
    }
    else{
      this.dataService.updateUserStatus(userId, 'ONLINE');  
    }    
  }

  //!methods

  setInviteList(user1Id:number, user2Id:number){
    this.inviteList.set(`${user1Id}${user2Id}`, [{id: user1Id.toString()}, {id: user2Id.toString()}]);
  }

  endGame(userId: string){
    this.rooms.forEach((currentRoom, index)=>{
      if (currentRoom.players[0].clientSock.id == userId){
        currentRoom.players[0].clientSock.leave(currentRoom.id);
        clearInterval(this.intervals.at(index));
        this.intervals.splice(index, 1);
        this.rooms.splice(index, 1);
      }
    });
  }

  CheckTheWinner(currentRoom:Room, gameData: GameService , index:number){
    if (gameData.player1.score == 11){
      clearInterval(this.intervals.at(index));
      this.intervals.splice(index, 1);
      this.rooms.splice(index, 1);
      currentRoom.players[0].clientSock.emit('winMessage', [`You Won`, `${gameData.player1.score}-${gameData.player2.score}`]);
      currentRoom.players[0].clientSock.leave(currentRoom.id);
      if (currentRoom.mode == 'multi'){
        currentRoom.players[1].clientSock.emit('winMessage', [`You Lost`, `${gameData.player1.score}-${gameData.player2.score}`]);
        currentRoom.players[1].clientSock.leave(currentRoom.id);
        this.server.to(currentRoom.id).emit('winMessage', [`${currentRoom.players[0].name} WIN`, ``]);
        this.dataService.addGame({player1: Number(currentRoom.players[0].id), player2: Number(currentRoom.players[1].id), player1score: gameData.player1.score, player2score: gameData.player2.score});
      }
      return ('done');
    }
    else if(gameData.player2.score == 11){
      clearInterval(this.intervals.at(index));
      this.intervals.splice(index, 1);
      this.rooms.splice(index, 1);
      currentRoom.players[0].clientSock.emit('winMessage', [`You Lost`, `${gameData.player1.score}-${gameData.player2.score}`]);
      currentRoom.players[0].clientSock.leave(currentRoom.id);
      if (currentRoom.mode == 'multi'){
        currentRoom.players[1].clientSock.emit('winMessage', [`You Won`, `${gameData.player1.score}-${gameData.player2.score}`]);
        currentRoom.players[1].clientSock.leave(currentRoom.id);
        this.server.to(currentRoom.id).emit('winMessage', [`${currentRoom.players[1].name} WIN`, ``]);
        this.dataService.addGame({player1: Number(currentRoom.players[0].id), player2: Number(currentRoom.players[1].id), player1score: gameData.player1.score, player2score: gameData.player2.score});
      }
      return ('done');
    }
    return ('still');
  }
  
  Punisher(userId: string){
    this.rooms.forEach((currentRoom, index)=>{
      if (currentRoom.players[0].clientSock.id == userId){
        currentRoom.gameObj.player1.score = 0;
        currentRoom.gameObj.player2.score = 11;
        
        currentRoom.players[0].clientSock.leave(currentRoom.id);
        currentRoom.players[1].clientSock.emit('winMessage', [`YOU WIN`, '0-11'])
        currentRoom.players[1].clientSock.leave(currentRoom.id);
        
        this.server.to(currentRoom.id).emit('winMessage', [`${currentRoom.players[0].name.slice(0,10)} vs ${currentRoom.players[1].name.slice(0,10)}`, '0 - 11']);
        clearInterval(this.intervals.at(index));
        this.intervals.splice(index, 1);
        this.rooms.splice(index, 1);
        this.dataService.addGame({player1: Number(currentRoom.players[0].id), player2: Number(currentRoom.players[1].id), player1score: 0, player2score: 11});
      }
      else if (currentRoom.players[1].clientSock.id == userId){ 
        currentRoom.gameObj.player1.score = 11;
        currentRoom.gameObj.player2.score = 0;
        
        currentRoom.players[1].clientSock.leave(currentRoom.id);
        currentRoom.players[0].clientSock.emit('winMessage', [`YOU WIN`, '11-0'])
        currentRoom.players[0].clientSock.leave(currentRoom.id);
        
        this.server.to(currentRoom.id).emit('winMessage', [`${currentRoom.players[0].name.slice(0,10)} vs ${currentRoom.players[1].name.slice(0,10)}`, '11 - 0']);
        clearInterval(this.intervals.at(index));
        this.intervals.splice(index, 1);
        this.rooms.splice(index, 1);
        this.dataService.addGame({player1: Number(currentRoom.players[0].id), player2: Number(currentRoom.players[1].id), player1score: 11, player2score: 0});
      }
    });
  }

  Update(user: User){
    this.rooms.forEach((currentRoom, index) =>
    {
      const gameData: GameService =  currentRoom.gameObj;
      if (this.CheckTheWinner(currentRoom, gameData, index) == 'still'){
        if (user.clientSock.id == currentRoom.players[0].clientSock.id || user.clientSock.id == currentRoom.players[1].clientSock.id)
          gameData.updateBall(currentRoom.mode);
        this.server.to(currentRoom.id).emit('render', {
          player1: gameData.player1,
          player2: gameData.player2,
          ball: gameData.ball,
          net: gameData.net,
          score1Pos: gameData.score1Pos,
          score2Pos:gameData.score2Pos
        });
      }
    });
  }

  //! events

  @SubscribeMessage('checkInvite')
  async checkInvite(client: Socket, room: {id:string}){
    const userId = await this.wsAuth(client);
    if (!userId) return;

    const listUsers = this.inviteList.get(room.id);

    if (!listUsers || !listUsers.find((currentUser) => {return(userId == currentUser.id)})){
      client.emit("toHome");
      return;
    }
    let userFond = listUsers.find((currentUser) => {return(userId == currentUser.id)});
    const userData = await this.dataService.getUser(userId);
    userFond.name = userData.name;
    userFond.clientSock = client;

    
    this.dataService.updateUserStatus(userId, 'PLAYING');
    if (this.playingSocket.get(userId))
      this.playingSocket.get(userId).push(client.id);
    else
      this.playingSocket.set(userId, [client.id]);

    if (listUsers[0].clientSock && listUsers[1].clientSock){
      let RoomName:string = `${listUsers[0].name} vs ${listUsers[1].name}`;
      let roomId:string = listUsers[0].clientSock.id+listUsers[0].clientSock.id;
      let Players: User[] = new Array<User>;
      let Viewers: User[] = new Array<User>;
      
      listUsers.forEach((currentUser)=>{
        Players.push(currentUser);
        currentUser.clientSock.join(roomId);
      })
      this.rooms.push({
        name: RoomName , 
        id: roomId, 
        players:Players, 
        viewers:Viewers, 
        gameObj: new GameService,
        mode: 'multi',
      });
      this.waitlist.length = 0;
      this.server.to(roomId).emit('mode', 'playing');
      this.inviteList.delete(room.id);
      const intervalId:NodeJS.Timer = setInterval(()=>{this.Update(listUsers[0]);}, 1000/50);
      this.intervals.push(intervalId);
    }
    client.emit("waitInvite", "Wait your friend to accept");
 
  }
  
  @SubscribeMessage('movePlayer')
  async MovePlayer(client: Socket, mouseY:number) {
    const userId = await this.wsAuth(client);

    if (userId){
      let gameData: GameService;
      this.rooms.forEach((currentRoom)=>{
        gameData =  currentRoom.gameObj;
        if (client.id == currentRoom.players[0].clientSock.id)
          gameData.playerMovement(mouseY, gameData.player1);
        else if (client.id == currentRoom.players[1].clientSock.id) 
          gameData.playerMovement(mouseY, gameData.player2);
      });
    }

  }

  @SubscribeMessage('playRequest')
  async PlayRequest(client: Socket, gameMode: string){
    const userId = await this.wsAuth(client);
    if (!userId) return;
    let userData = await this.dataService.getUser(userId);

    if (userData.status == 'PLAYING') return;
    this.dataService.updateUserStatus(userId, 'PLAYING');
    if (this.playingSocket.get(userId))
      this.playingSocket.get(userId).push(client.id);
    else
      this.playingSocket.set(userId, [client.id]);
    
    if (gameMode == 'multi'){
      const UserObj: User = {name: userData.name, id:userId, clientSock:client};
      this.waitlist.push(UserObj);
      if (this.waitlist.length === 2)
      {
        let RoomName:string = `${this.waitlist[0].name.slice(0, 10)} vs ${this.waitlist[1].name.slice(0, 10)}`;
        let roomId:string = this.waitlist[0].clientSock.id+this.waitlist[1].clientSock.id;
        let Players: User[] = new Array<User>;
        let Viewers: User[] = new Array<User>;
        
        this.waitlist.forEach((currentUser)=>{
          Players.push(currentUser);
          currentUser.clientSock.join(roomId);
        })
        this.rooms.push({
          name: RoomName , 
          id: roomId, 
          players:Players, 
          viewers:Viewers, 
          gameObj: new GameService,
          mode: gameMode,
        });
        this.waitlist.length = 0;
        this.server.to(roomId).emit('mode', 'playing');
        const intervalId:NodeJS.Timer = setInterval(()=>{this.Update(UserObj);}, 1000/50);
        this.intervals.push(intervalId);
      }
      else
        client.emit('makingMatch...', "Making a match...");
    }
    else if (gameMode == 'single'){
      const UserObj: User = {name: userData.name, id:userId, clientSock:client};
      const randomNum:number = Math.floor(Math.random() * 9999);
      const botObj: User = {name: `bot${randomNum}`, id: userId+randomNum, clientSock:client};
      
      let RoomName:string = `${UserObj.name.slice(0, 10)} vs ${botObj.name.slice(0, 10)}}`;
      let roomId:string = UserObj.clientSock.id;
      let Players: User[] = new Array<User>;
      let Viewers: User[] = new Array<User>;
      
      Players.push(UserObj);
      Players.push(botObj);
      UserObj.clientSock.join(roomId);
      this.rooms.push({
        name: RoomName,
        id: roomId, 
        players: Players, 
        viewers: Viewers, 
        gameObj: new GameService,
        mode: gameMode,
      });
      
      this.server.to(roomId).emit('mode', 'playing');
      const intervalId:NodeJS.Timer = setInterval(()=>{this.Update(UserObj);}, 1000/50)
      this.intervals.push(intervalId);
    }

  }
  
  @SubscribeMessage('getRooms')
  async GetRooms(client: Socket) {
    const userId = await this.wsAuth(client);
    if (userId){
      let roomsList: string[] = new Array<string>;

      this.rooms.forEach((currentRoom)=>{
        if (currentRoom.mode == 'multi')
          roomsList.push(currentRoom.name);
      });
      client.emit('roomsList', roomsList);
    }
  }
  
  @SubscribeMessage('joinGameRoom')
  async JoinGameRome(client: Socket, room: string){
    const userId = await this.wsAuth(client);
    let userData;
    if (userId){
      userData = await this.dataService.getUser(userId);

      let  currentRoom = this.rooms.find((currentRoom)=>{return currentRoom.name == room});
      if (currentRoom){
        currentRoom.viewers.push({name: userData.name, id: userId, clientSock: client});
        client.join(currentRoom.id); 
      }
      else
        client.emit('noRoom', [`There's no room with this name "${room.length - 3 > 5 ? room.slice(0,5)+'...' : room.slice(0,8)}"`, `Back to the streams page to see current games avileble`]);
    }
  }

  @SubscribeMessage('leaveGameRoom')
  async LeaveGameRome(client: Socket, room: string){
    const userId = await this.wsAuth(client);
    if (userId){
      let  currentRoom = this.rooms.find((currentRoom)=>{currentRoom.name == room});
      if (currentRoom){
        client.leave(currentRoom.id);
        currentRoom.viewers.forEach((currentClient, index)=>{
          if(currentClient.clientSock.id === client.id)
            currentRoom.viewers.splice(index, 1); 
        });
      }
    }
  }

  //! checkUser access token
  async wsAuth(client: Socket) {
    const {'access-token' : access_token} = parse(client.handshake.headers.cookie || '');
    try {
        const payload = await this.jwt.verify(access_token, {
            secret: this.config.get('JWT_ACCESS_SECRET')
        });
        return (payload.userId);
    }
    catch {
      client.emit('toLogin');  
      client.disconnect();
    }
  }
}