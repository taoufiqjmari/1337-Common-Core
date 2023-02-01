import React from 'react';
import Image from 'next/image';
import { useState, useEffect } from 'react';
import { Return } from '../../components/Return';
import Channeltag from '../../components/Channeltag';
import CreateChannel from '../../components/CreateChannel';
import Usertag from '../../components/Usertag';

const chat = () => {
	const [chat, setchat] = useState<any>();
	const [srch, setsrch] = useState<any>();
	const [search, setsearch] = useState(false);
	const [message, setMessage] = useState('');

	const tochat = () => {
		setsrch('');
		setsearch(false);
		setMessage('');
	};
	const handleChange = (event: any) => {
		setMessage(event?.target?.value);
	};

	const handleKeyDown = async (event: any) => {
		if (event?.key === 'Enter') {
			let response = await fetch(
				`http://${process.env.APPNAME}:3000/chat/search?name=${message}`,
				{
					credentials: 'include',
				}
			);
			if (!response.ok) return;
			let data = await response.json();
			setsearch(true);
			setsrch(data);
		}
	};

	useEffect(() => {
		const chat = async () => {
			const resp = await fetch(`http://${process.env.APPNAME}:3000/chat`, {
				credentials: 'include',
			});
			if (!resp.ok) return;
			setchat(await resp.json());
		};
		chat();
	}, []);
	if (!chat) return <>loading</>;
	if (search && srch) {
		return (
			<div className="h-screen flex flex-col">
				<div className=" mx-auto w-full h-[20%] my-auto flex items-center justify-center max-w-7xl">
					<div className="grow">
						<Return />
					</div>
				</div>
				<div className="relative bg-glass mx-auto max-w-5xl my-auto h-[80%] w-[90%] rounded-3xl font-lexend text-white">
					<div className="bg-white/10  rounded-full w-full h-[10%] cursor-pointer flex items-center justify-center">
						<input
							onChange={handleChange}
							onKeyDown={handleKeyDown}
							value={message}
							placeholder="Search"
							className="w-[80%] placeholder-white/70 h-full rounded-full bg-transparent outline-0  "
						/>
						<Image
							onClick={tochat}
							src="/sources/return.svg"
							width={50}
							height={50}
							layout="fixed"
						/>
					</div>
					<div className="h-[45%] overflow-x-auto  ">
						<h3 className="w-full h[10%] pt-4  text-center">Users</h3>
						{srch.map((tag: any, index: number) => {
							if (tag.type === 'DM') {
								return (
									<Usertag
										key={tag.id || index}
										idx={tag.id}
										name={tag.name}
										member={tag.isMember}
									/>
								);
							}
						})}
					</div>
					<div className="bg-white/10 h-[45%] rounded-3xl overflow-x-auto">
						<div className=" w-full h-[10%] pt-2 flex items-center justify-center">
							<h3 className="  w-[90%] h-full text-center">Channels</h3>
							<div className=" w-[10%] h-full ">
								<CreateChannel />
							</div>
						</div>
						{srch.map((tag: any) => {
							if (tag.type !== 'DM') {
								return (
									<Channeltag
										key={tag.id}
										id={tag.id}
										name={tag.name}
										type={tag.type}
										ismember={tag.isMember}
									/>
								);
							}
						})}
					</div>
				</div>
			</div>
		);
	}
	return (
		<div className="h-screen flex flex-col">
			<div className=" mx-auto w-full h-[20%] my-auto flex items-center justify-center max-w-7xl">
				<div className="grow">
					<Return />
				</div>
			</div>
			<div className="relative bg-glass mx-auto max-w-5xl my-auto h-[80%] w-[90%] rounded-3xl font-lexend text-white">
				<div className="bg-white/10  rounded-full w-full h-[10%] cursor-pointer flex items-center justify-center">
					<input
						onChange={handleChange}
						onKeyDown={handleKeyDown}
						value={message}
						placeholder="Search"
						className="w-[80%] placeholder-white/70 h-full rounded-full bg-transparent outline-0  "
					/>
					<Image
						className=" "
						src="/sources/Srch.svg"
						width={50}
						height={50}
						layout="fixed"
					/>
				</div>
				<div className="h-[45%] overflow-x-auto  ">
					<h3 className="w-full h[10%] pt-4  text-center">Users</h3>
					{chat.map((tag: any, index: number) => {
						if (tag.type === 'DM') {
							return (
								<Usertag
									key={tag.id || index}
									idx={tag.id}
									name={tag.name}
									member={true}
								/>
							);
						}
					})}
				</div>
				<div className="bg-white/10 h-[45%] rounded-3xl overflow-x-auto">
					<div className=" w-full h-[10%] pt-2 flex items-center justify-center">
						<h3 className="  w-[90%] h-full text-center">Channels</h3>
						<div className=" w-[10%] h-full ">
							<CreateChannel />
						</div>
					</div>
					{chat.map((tag: any) => {
						if (tag.type !== 'DM') {
							return (
								<Channeltag
									key={tag.id}
									id={tag.id}
									name={tag.name}
									type={tag.type}
									ismember={true}
								/>
							);
						}
					})}
				</div>
			</div>
		</div>
	);
};

export default chat;
