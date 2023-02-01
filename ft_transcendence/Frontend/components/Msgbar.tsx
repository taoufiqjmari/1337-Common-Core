import React, { useState } from 'react';
import Image from 'next/image';
import { Dialog, Transition } from '@headlessui/react';
import { Fragment } from 'react';
import { ToastContainer, toast } from 'react-toastify';
import 'react-toastify/dist/ReactToastify.css';
import { useRouter } from 'next/router';
import Select from 'react-select';

interface Channel {
	name: string;
	type: string;
}
interface Message {
	username: string;
	message: string;
	isGameInvite: boolean;
	mine: boolean;
}

interface User {
	userId: number;
	name: string;
	status: string;
	role: string;
	banExpiration: Date;
	muteExpiration: Date;
}
interface Uservalues {
	channel: Channel;
	user: User;
	members: [User];
	messages: [Message];
}

export const Msgbar: React.FC<{
	user: Uservalues;
	channelId: any;
}> = ({ user, channelId }) => {
	const options = [
		{ value: 'PRIVATE', label: 'PRIVATE' },
		{ value: 'PROTECTED', label: 'PROTECTED' },
		{ value: 'PUBLIC', label: 'PUBLIC' },
	];
	const [active, setactive] = useState(false);
	const [rules, setrules] = useState<any>(<></>);
	const [dc, setdc] = useState(false);
	const router = useRouter();
	function blockingAbility() {
		setactive(active ? false : true);
	}
	const ListUsersHandler = (id: number) => {
		router.push(`/profile/${id}`);
	};
	const SendAction = async (id: number, str: string) => {
		const bodyContent = JSON.stringify({ targetId: id });
		let response = await fetch(str, {
			method: 'POST',
			body: bodyContent,
			headers: { 'Content-Type': 'application/json' },
			credentials: 'include',
		});
		if (!response.ok) {
			toast('Failed');
			return;
		}
		toast('Success');
		setdc(false);
		router.push(`/chat`);
		return;
	};
	const LeaveChannel = async () => {
		let response = await fetch(`http://${process.env.APPNAME}:3000/chat/${channelId}/leave`, {
			method: 'POST',
			credentials: 'include',
		});
		if (!response.ok) {
			toast('Failed');
			return;
		}
		toast('Success');
		router.push('/chat');
		return;
	};
	const BlockUser = async () => {
		let response = await fetch(`http://${process.env.APPNAME}:3000/chat/${channelId}/block`, {
			method: 'POST',
			credentials: 'include',
		});
		if (!response.ok) {
			toast('Failed');
			return;
		}
		toast('Success');
		router.push('/chat');
		return;
	};
	const UnblockUser = async () => {
		let response = await fetch(`http://${process.env.APPNAME}:3000/chat/${channelId}/unblock`, {
			method: 'POST',
			credentials: 'include',
		});
		if (!response.ok) {
			toast('Failed');
			return;
		}
		toast('Success');
		router.push('/chat');
		return;
	};
	const DynamicCard = () => {
		function closeModal() {
			setdc(false);
			setactive(false);
		}
		return (
			<div className=" w-full h-full">
				<Transition
					appear
					show={dc}
					as={Fragment}
				>
					<Dialog
						as="div"
						className=" z-10"
						onClose={closeModal}
					>
						<Transition.Child
							as={Fragment}
							enter="ease-out duration-300"
							enterFrom="opacity-0"
							enterTo="opacity-100"
							leave="ease-in duration-200"
							leaveFrom="opacity-100"
							leaveTo="opacity-0"
						>
							<div className="fixed inset-0  bg-opacity-25" />
						</Transition.Child>

						<div className="fixed inset-0 overflow-y-auto">
							<div className="flex min-h-full items-center justify-center text-center">
								<Transition.Child
									as={Fragment}
									enter="ease-out duration-300"
									enterFrom="opacity-0 scale-50"
									enterTo="opacity-100 scale-100"
									leave="ease-in duration-200"
									leaveFrom="opacity-100 scale-100"
									leaveTo="opacity-0 scale-50"
								>
									<Dialog.Panel className="w-full max-w-5xl transform overflow-hidden rounded-2xl bg-glass p-6 text-left align-middle shadow-xl transition-all">
										<div className=" ">{rules}</div>
									</Dialog.Panel>
								</Transition.Child>
							</div>
						</div>
					</Dialog>
				</Transition>
				<ToastContainer />
			</div>
		);
	};
	const ListUsers = () => {
		setrules(
			<div>
				{user.members.length ? (
					user.members.map((elm, idx) => {
						return (
							<div
								key={idx}
								onClick={() => {
									ListUsersHandler(elm.userId);
								}}
							>
								{' '}
								{elm.name}{' '}
							</div>
						);
					})
				) : (
					<h3>NO USERS FOUND</h3>
				)}
			</div>
		);
		setdc(true);
		setactive(false);
	};
	const PromoteUsers = () => {
		setrules(
			<div>
				{user.members.length ? (
					user.members.map((elm, idx) => {
						if (elm.role === 'MEMBER')
							return (
								<div
									key={idx}
									className="cursor-pointer "
									onClick={() => {
										SendAction(
											elm.userId,
											`http://${process.env.APPNAME}:3000/chat/${channelId}/promote`
										);
									}}
								>
									{' '}
									{elm.name}{' '}
								</div>
							);
						return (
							<div
								key={idx}
								className="cursor-not-allowed"
							>
								{' '}
								{elm.name}{' '}
							</div>
						);
					})
				) : (
					<h3>NO USERS FOUND</h3>
				)}
			</div>
		);
		setdc(true);
		setactive(false);
	};
	const DemoteUsers = () => {
		setrules(
			<div>
				{user.members.length ? (
					user.members.map((elm, idx) => {
						if (elm.role === 'ADMIN')
							return (
								<div
									key={idx}
									className="cursor-pointer "
									onClick={() => {
										SendAction(
											elm.userId,
											`http://${process.env.APPNAME}:3000/chat/${channelId}/demote`
										);
									}}
								>
									{' '}
									{elm.name}{' '}
								</div>
							);
						return (
							<div
								key={idx}
								className="cursor-not-allowed"
							>
								{' '}
								{elm.name}{' '}
							</div>
						);
					})
				) : (
					<h3>NO USERS FOUND</h3>
				)}
			</div>
		);
		setdc(true);
		setactive(false);
	};
	const BanUsers = () => {
		setrules(
			<div>
				{user.members.length ? (
					user.members.map((elm, idx) => {
						return (
							<div
								key={idx}
								className="cursor-pointer "
								onClick={() => {
									SendAction(
										elm.userId,
										`http://${process.env.APPNAME}:3000/chat/${channelId}/ban`
									);
								}}
							>
								{' '}
								{elm.name}{' '}
							</div>
						);
					})
				) : (
					<h3>NO USERS FOUND</h3>
				)}
			</div>
		);
		setdc(true);
		setactive(false);
	};
	const UnbanUsers = () => {
		setrules(
			<div>
				{user.members.length ? (
					user.members.map((elm, idx) => {
						if (elm.status === 'BANNED')
							return (
								<div
									key={idx}
									className="cursor-pointer"
									onClick={() => {
										SendAction(
											elm.userId,
											`http://${process.env.APPNAME}:3000/chat/${channelId}/unban`
										);
									}}
								>
									{' '}
									{elm.name}{' '}
								</div>
							);
						return (
							<div
								key={idx}
								className="cursor-not-allowed "
							>
								{' '}
								{elm.name}{' '}
							</div>
						);
					})
				) : (
					<h3>NO USERS FOUND</h3>
				)}
			</div>
		);
		setdc(true);
		setactive(false);
	};
	const MuteUsers = () => {
		setrules(
			<div>
				{user.members.length ? (
					user.members.map((elm, idx) => {
						return (
							<div
								key={idx}
								className="cursor-pointer "
								onClick={() => {
									SendAction(
										elm.userId,
										`http://${process.env.APPNAME}:3000/chat/${channelId}/mute`
									);
								}}
							>
								{' '}
								{elm.name}{' '}
							</div>
						);
					})
				) : (
					<h3>NO USERS FOUND</h3>
				)}
			</div>
		);
		setdc(true);
		setactive(false);
	};
	const UnmuteUsers = () => {
		setrules(
			<div>
				{user.members.length ? (
					user.members.map((elm, idx) => {
						if (elm.status === 'MUTED')
							return (
								<div
									key={idx}
									className="cursor-pointer "
									onClick={() => {
										SendAction(
											elm.userId,
											`http://${process.env.APPNAME}:3000/chat/${channelId}/unmute`
										);
									}}
								>
									{' '}
									{elm.name}{' '}
								</div>
							);
						return (
							<div
								key={idx}
								className="cursor-not-allowed "
							>
								{' '}
								{elm.name}{' '}
							</div>
						);
					})
				) : (
					<h3>NO USERS FOUND</h3>
				)}
			</div>
		);
		setdc(true);
		setactive(false);
	};
	const KickUsers = () => {
		setrules(
			<div>
				{user.members.length ? (
					user.members.map((elm, idx) => {
						return (
							<div
								key={idx}
								className="cursor-pointer "
								onClick={() => {
									SendAction(
										elm.userId,
										`http://${process.env.APPNAME}:3000/chat/${channelId}/kick`
									);
								}}
							>
								{' '}
								{elm.name}{' '}
							</div>
						);
					})
				) : (
					<h3>NO USERS FOUND</h3>
				)}
			</div>
		);
		setdc(true);
		setactive(false);
	};
	const SetChannel = () => {
		let param: any = { name: '', type: '', password: '' };
		async function SubmitParams() {
			param.type = param.type !== '' ? param.type.value : '';
			param.name === '' ? delete param.name : '';
			param.type === '' ? delete param.type : '';
			param.password === '' ? delete param.password : '';
			let bodyContent = JSON.stringify({ ...param });
			let response = await fetch(
				`http://${process.env.APPNAME}:3000/chat/${channelId}/changeSettings`,
				{
					method: 'POST',
					body: bodyContent,
					headers: {
						'Content-Type': 'application/json',
					},
					credentials: 'include',
				}
			);
			if (!response.ok) {
				toast('wrong Input');
				param = { name: '', type: '', password: '' };
				setdc(false);
				router.push(`/chat`);
				return;
			}
			toast('success');
			setdc(false);
			router.push(`/chat`);
			param = { name: '', type: '', password: '' };
		}
		function updatename(event: any) {
			param = {
				name: event.target.value,
				type: param.type,
				password: param.password,
			};
		}
		function updatepassword(event: any) {
			param = {
				name: param.name,
				type: param.type,
				password: event.target.value,
			};
		}
		function updatetype(event: any) {
			param = { name: param.name, type: event, password: param.password };
		}
		setrules(
			<div>
				<p className="mt-2">name</p>
				<input
					onChange={updatename}
					className="rounded-full h-8  placeholder:text-black/60 text-white bg-black/50"
					type="text"
					placeholder="channel Name"
				/>
				<p className="mt-2">options</p>
				<Select
					onChange={updatetype}
					className="bg-black"
					options={options}
				/>
				<p className="mt-2">Password</p>
				<input
					onChange={updatepassword}
					className="block rounded-full h-8 placeholder:text-black/60 focus:border-white text-white bg-black/50"
					type="password"
					placeholder="Password"
				/>
				<button
					className="bg-blue-300 mt-4 h-8 w-24 rounded-3xl flex items-center justify-center "
					onClick={SubmitParams}
				>
					submit
				</button>
			</div>
		);
		setdc(true);
		setactive(false);
	};
	const AddMember = () => {
		let param: any = { username: '' };
		async function SubmitParams() {
			let bodyContent = JSON.stringify({
				username: param.username,
			});
			let response = await fetch(`http://${process.env.APPNAME}:3000/chat/${channelId}/add`, {
				method: 'POST',
				body: bodyContent,
				headers: {
					'Content-Type': 'application/json',
				},
				credentials: 'include',
			});
			if (!response.ok) {
				toast('user not found');
				param = { username: '' };
				return;
			}
			toast('success');
			router.push('/chat');
			param = { username: '' };
		}
		function updatename(event: any) {
			param = { username: event.target.value };
		}

		setrules(
			<div>
				<p className="mt-2">name</p>
				<input
					onChange={updatename}
					className="rounded-full h-8  placeholder:text-black/60 text-white bg-black/50"
					type="text"
					placeholder="channel Name"
				/>
				<button
					className="bg-blue-300 mt-4 h-8 w-24 rounded-3xl flex items-center justify-center "
					onClick={SubmitParams}
				>
					submit
				</button>
			</div>
		);
		setdc(true);
		setactive(false);
	};

	const Ability = () => {
		const style =
			'bg-glass bg-white/10 h-8 w-full text-center flex items-center justify-center  hover:bg-black/50 hover:text-white';
		if (user.channel.type == 'DM') {
			return (
				<div className="absolute top-full right-0 z-10 w-32  ">
					{user.user.status === 'ACTIVE' ? (
						<button
							onClick={() => {
								ListUsersHandler(user.members[0].userId);
							}}
							className={style}
						>
							Profile
						</button>
					) : (
						<></>
					)}
					{user.user.status === 'ACTIVE' ? (
						<button
							onClick={BlockUser}
							className={style}
						>
							Block
						</button>
					) : (
						<></>
					)}
					{user.user.status === 'BLOCKER' ? (
						<button
							onClick={UnblockUser}
							className={style}
						>
							UnBlock
						</button>
					) : (
						<></>
					)}
				</div>
			);
		}
		return (
			<div className="absolute top-full right-0 z-10 w-32 ">
				<button
					onClick={() => {
						ListUsers();
					}}
					className={style}
				>
					Users List
				</button>
				{user.user.role === 'OWNER' ? (
					<button
						onClick={PromoteUsers}
						className={style}
					>
						Promote
					</button>
				) : (
					<></>
				)}
				{user.user.role === 'OWNER' ? (
					<button
						onClick={DemoteUsers}
						className={style}
					>
						Demote
					</button>
				) : (
					<></>
				)}
				{user.user.status === 'ACTIVE' && user.user.role !== 'MEMBER' ? (
					<button
						onClick={BanUsers}
						className={style}
					>
						Ban
					</button>
				) : (
					<></>
				)}
				{user.user.status === 'ACTIVE' && user.user.role !== 'MEMBER' ? (
					<button
						onClick={UnbanUsers}
						className={style}
					>
						UnBan
					</button>
				) : (
					<></>
				)}
				{user.user.status === 'ACTIVE' && user.user.role !== 'MEMBER' ? (
					<button
						onClick={MuteUsers}
						className={style}
					>
						Mute
					</button>
				) : (
					<></>
				)}
				{user.user.status === 'ACTIVE' && user.user.role !== 'MEMBER' ? (
					<button
						onClick={UnmuteUsers}
						className={style}
					>
						Unmute
					</button>
				) : (
					<></>
				)}
				{user.user.role === 'OWNER' ? (
					<button
						onClick={SetChannel}
						className={style}
					>
						settings
					</button>
				) : (
					<></>
				)}
				{user.user.role === 'OWNER' ? (
					<button
						onClick={AddMember}
						className={style}
					>
						Add Member
					</button>
				) : (
					<></>
				)}
				{user.user.status === 'ACTIVE' && user.user.role !== 'MEMBER' ? (
					<button
						onClick={KickUsers}
						className={style}
					>
						Kick
					</button>
				) : (
					<></>
				)}
				{user.user.status === 'ACTIVE' ? (
					<button
						onClick={LeaveChannel}
						className={style}
					>
						Leave
					</button>
				) : (
					<></>
				)}
			</div>
		);
	};

	if (!user) return <>no user found</>;
	return (
		<div className="bg-white/20 pr-8  rounded-full w-[80%]  mx-auto h-[50%] cursor-pointer flex items-center justify-between">
			<div></div>
			<h3 className="text-white text-xl md:text-3xl font-bold">{user.channel.name}</h3>
			<div className="relative">
				<Image
					onClick={blockingAbility}
					src="/sources/dots.svg"
					width={30}
					height={30}
					alt=""
				/>
				<DynamicCard />
				{active ? <Ability /> : <></>}
			</div>
		</div>
	);
};
