import React, { useEffect, useRef, useState } from 'react';
import Image from 'next/image';
import Link from 'next/link';
import { Return } from '../../components/Return';
import { Msgbar } from '../../components/Msgbar';
import { io, Socket } from 'socket.io-client';
import { useRouter } from 'next/router';

const Msgpage = () => {
	const [socket, setSocket] = useState<Socket>();
	const [messages, setMessages] = useState<any>([]);
	const messageInputRef = useRef<HTMLInputElement>(null);
	const [user, setuser] = useState<any>();
	const router = useRouter();
	const data = router.query;

	useEffect(() => {
		if (!socket || !data.id) return;
		socket.on('message', addMessage);
		socket.on('toHome', () => {
			router.push('/home');
		});
		socket.on('toGameInterface', (id) => router.push(`/play?mode=invite&id=${id}`));

		socket.emit('join', { channelId: data.id });
		document.addEventListener('keydown', sendMessageByKey);

		return () => {
			socket.disconnect();
			document.removeEventListener('keydown', sendMessageByKey);
		};
	}, [socket, data.id]);

	useEffect(() => {
		if (!data.id) return;
		async function getMesg() {
			const response = await fetch(`http://${process.env.APPNAME}:3000/chat/${data.id}`, {
				credentials: 'include',
			});
			if (!response.ok) {
				router.push('/chat');
				return;
			}
			const userData = await response.json();
			setMessages(userData.messages);
			setuser(userData);
			setSocket(io(`http://${process.env.APPNAME}:5500`, { withCredentials: true }));
		}
		getMesg();
	}, [data.id]);

	function sendInvite() {
		if (!socket) return;
		socket.emit('inviteToGame', { channelId: data.id });
	}

	function sendMessageByKey(e?: any) {
		if (e.key != 'Enter') return;
		sendMessage();
	}

	function sendMessage() {
		if (!socket || !messageInputRef.current || !messageInputRef.current.value) return;
		socket.emit('message', { channelId: data.id, message: messageInputRef.current.value });
		messageInputRef.current.value = '';
	}

	function addMessage(message: any) {
		setMessages((currentMsg: any) => {
			return [message, ...currentMsg];
		});
	}

	if (!user) return <>loading</>;
	return (
		<div className="h-screen flex flex-col">
			<div className="mx-auto w-full h-[20%] my-auto flex items-center justify-center max-w-7xl">
				<Return />
				<Msgbar
					channelId={data.id}
					user={user}
				/>
				<Link href="/chat">
					<div className="bg-glass w-16 h-16 xl:w-24 xl:h-24 rounded-full flex justify-center items-center cursor-pointer">
						<div className="relative w-10 h-10  xl:w-12 xl:h-12">
							<Image
								src="/sources/msg.svg"
								layout="fill"
							/>
						</div>
					</div>
				</Link>
			</div>
			<div className="bg-glass mx-auto max-w-5xl my-auto h-[80%] w-[90%] rounded-3xl font-lexend text-white">
				<div className="flex flex-col-reverse gap-5 p-8 h-[90%] overflow-y-auto  rounded-3xl w-full">
					{messages.map((message: any, index: number) => {
						let mine = 'justify-start';
						let mineColor = (
							<div
								className={`bg-slate-700/40 bg-glass p-4 rounded-lg text-white text-xs text-ellipsis overflow-hidden`}
							>
								<p className="break-words">{message.message}</p>
							</div>
						);
						if (message.mine === true) {
							mine = 'justify-end';
							mineColor = (
								<div
									className={`bg-teal-500/40 bg-glass p-4 rounded-lg text-white text-xs text-ellipsis overflow-hidden`}
								>
									<p className="break-words">{message.message}</p>
								</div>
							);
						}

						if (message.isGameInvite)
							return (
								<div
									key={index}
									className={`flex ${mine}`}
								>
									<div className="max-w-[70%] flex flex-col justify-end">
										<h1 className={`text-white/40 text-xs px-2`}>
											{message.username}
										</h1>
										<div
											className={`bg-sky-600/30 bg-glass p-4 rounded-lg text-white text-xs text-ellipsis overflow-hidden hover:bg-sky-600/60`}
										>
											<Link href={message.message}>
												<p className="break-words  cursor-pointer">
													Join a game
												</p>
											</Link>
										</div>
									</div>
								</div>
							);

						return (
							<div
								key={index}
								className={`flex ${mine}`}
							>
								<div className="max-w-[70%] flex flex-col justify-end">
									<h1 className={`text-white/40 text-xs px-2`}>
										{message.username}
									</h1>
									{mineColor}
								</div>
							</div>
						);
					})}
				</div>
				<div className="bg-white/10  rounded-3xl w-full h-[10%] cursor-pointer flex items-center justify-center">
					<div className={`cursor-pointer ${user.channel.type === 'DM' ? '' : 'hidden'}`}>
						<Image
							src="/sources/Sword.svg"
							width={50}
							height={50}
							layout="fixed"
							onClick={sendInvite}
						/>
					</div>
					<input
						ref={messageInputRef}
						placeholder="Message"
						className="w-[90%] text-center placeholder-white/70 h-full rounded-full bg-transparent outline-0"
					/>
					<Image
						className="cursor-pointer"
						src="/sources/Send.svg"
						width={50}
						height={50}
						layout="fixed"
						onClick={sendMessage}
					/>
				</div>
			</div>
		</div>
	);
};

export default Msgpage;
