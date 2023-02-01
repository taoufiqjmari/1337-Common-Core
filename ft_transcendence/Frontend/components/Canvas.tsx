import { useRouter } from "next/router";
import { useRef, useState, useEffect } from "react";
import { io, Socket } from "socket.io-client";


const Canvas = ({ mode, gameMode, roomName, inviteId }: { mode:string, gameMode?:string, roomName?: string, inviteId?:string}) => { 
  const [ctx2d, setCtx2d] = useState<CanvasRenderingContext2D | null>(null);
  const canvasRef = useRef<HTMLCanvasElement | null>(null);
  const router = useRouter();  
  let socket: Socket;

  useEffect(()=>{
    if (!canvasRef.current || !ctx2d) return;
    socket = io(`http://${process.env.APPNAME}:5500`, { withCredentials: true });

    socket.on("toLogin", ()=>{router.push('/')});
    socket.on("toHome", ()=>{router.push('/home')});
    socket.on("mode", isPlayer);
    socket.on("render", render);
    socket.on("winMessage", winMessage);
    socket.on("noRoom", noRoom);

    if (mode == "play") {
      socket.emit("playRequest", gameMode);
      socket.on("makingMatch...", matchMaking);
    }
    else if (mode == "invite"){
      socket.emit('checkInvite', {id: inviteId});
      socket.on("waitInvite", matchMaking);
    }
    else if (mode == "stream"){
      socket.emit("joinGameRoom", roomName);
    }

    return () => {
        if (mode === "stream"){
          socket.emit("leaveGameRoom", roomName);
          socket.disconnect();
        }
        else (mode === "play" || mode === "invite")
          socket.disconnect();
    }
  }, [ctx2d]);

  useEffect(() => {
    if (!canvasRef.current) return;
    setCtx2d(canvasRef.current.getContext("2d"));
  }, []);


  
  function render(data: any){
    if (!canvasRef.current || !ctx2d) return;
    const {player1, player2, ball, net, score1Pos, score2Pos} = data;
    
    ctx2d.clearRect(0, 0, canvasRef.current.width, canvasRef.current.height);
    drawRect(player1);
    drawRect(player2);
    drawNet(net);
    drawBall(ball);
    drawScore(score1Pos, player1);
    drawScore(score2Pos, player2);
  }

  function isPlayer(mode: string) {
    if (!canvasRef.current) return;
    if (mode == "playing")
      canvasRef.current.addEventListener("mousemove", sendMouseY);
  }

  function sendMouseY(e: any) {
    if (!canvasRef.current || !socket) return;
    let mouseY: number = e.pageY - canvasRef.current.offsetTop;
    mouseY /=  (canvasRef.current.clientHeight / 500);//responsive
    socket.emit("movePlayer", mouseY);
  }

  function winMessage(text: string[]){
    if (!canvasRef.current || !ctx2d) return;
    ctx2d.clearRect(0, 0, canvasRef.current.width, canvasRef.current.height);
    drawText(text[0], "4rem", canvasRef.current.width / 2, canvasRef.current.height / 5);
    drawText(text[1], "4rem", canvasRef.current.width / 2, canvasRef.current.height / 3);
    // setTimeout(()=>{router.push('/home')}, 2000);
  }
  
  function noRoom(text:string[]){
    if (!canvasRef.current || !ctx2d) return;
    ctx2d.clearRect(0, 0, canvasRef.current.width, canvasRef.current.height);
    drawText(text[0], "3rem", canvasRef.current.width / 2, canvasRef.current.height / 5);
    drawText(text[1], "2rem", canvasRef.current.width / 2, canvasRef.current.height / 3.5);
    setTimeout(()=>{router.push('/streams')}, 2000);
  }

  function matchMaking(text:string){
    if (!canvasRef.current || !ctx2d) return;
    ctx2d.clearRect(0, 0, canvasRef.current.width, canvasRef.current.height);
    drawText(text, "4rem", canvasRef.current.width / 2, canvasRef.current.height / 5);
  }

  function drawRect(player: any) {
    if (!ctx2d) return;
    ctx2d.fillStyle = player.color;
    ctx2d.fillRect(player.x, player.y, player.width, player.height);
  }

  function drawNet(net: any) {
    if (!canvasRef.current || !ctx2d) return;
    for (let i = 0; i < canvasRef.current.height; i += 35) {
      ctx2d.fillStyle = net.color;
      ctx2d.fillRect(net.x, net.y + i, net.width, net.height);
    }
  }

  function drawBall(ball: any) {
    if (!ctx2d) return;
    ctx2d.fillStyle = ball.color;
    ctx2d.beginPath();
    ctx2d.arc(ball.x, ball.y, ball.radius, 0, Math.PI * 2, false);
    ctx2d.closePath();
    ctx2d.fill();
  }

  function drawScore(score: any, player: any) {
    if (!ctx2d) return;
    ctx2d.fillStyle = "#CDF2F0ee";
    ctx2d.font = `${score.size} BrickShapers`;
    ctx2d.textAlign = "center";
    ctx2d.fillText(player.score, score.x, score.y);
  }

  function drawText(text: string, size: string, x: number, y: number) {
    if (!ctx2d) return;
    ctx2d.fillStyle = '#38E1BB';
    ctx2d.font = `${size} BrickShapers`;
    ctx2d.textAlign = "center";
    ctx2d.fillText(text, x, y);
  }


  return (
    <>
      <canvas
        ref={canvasRef}
        width={900}
        height={500}
        className={`cursor-none cursor border-2 rounded border-#3D52D5 bg-#0C0915 mx-auto 
            canvas_sm:w-[340px] canvas_sm:h-[189px]
            canvas_md:w-[500px] canvas_md:h-[278px]
            canvas_lg:w-[700px] canvas_lg:h-[389px]
            canvas_xl:w-[900px] canvas_xl:h-[500px]`}
      ></canvas>
    </>
  );
};

export default Canvas;