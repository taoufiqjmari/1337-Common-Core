import React from 'react';
import Image from 'next/image';
import Link from 'next/link';
import { useRouter } from 'next/router';
import { useState } from 'react';
import { ToastContainer, toast } from 'react-toastify';
import 'react-toastify/dist/ReactToastify.css';
const Channeltag: React.FC<{
	id: any;
	name: any;
	ismember: any;
	type: any;
}> = ({ id, name, ismember, type }) => {
	const [protect, setprotect] = useState(false);
	const [pass, setpass] = useState('');
	const router = useRouter();

	async function submitandenter() {
		if (type === 'PROTECTED') {
			setprotect(true);
			return;
		}
		let response = await fetch(`http://${process.env.APPNAME}:3000/chat/${id}/join`, {
			method: 'POST',
			credentials: 'include',
		});
		if (response.ok) {
			router.push(`/chat/${id}`);
			return;
		}
	}
	const handleChange = (event: any) => {
		setpass(event?.target?.value);
	};

	const handleKeyDown = async (event: any) => {
		if (event?.key === 'Enter') {
			let bodyContent = JSON.stringify({
				password: pass,
			});
			let response = await fetch(`http://${process.env.APPNAME}:3000/chat/${id}/join`, {
				method: 'POST',
				body: bodyContent,
				headers: {
					'Content-Type': 'application/json',
				},
				credentials: 'include',
			});
			if (response.ok) {
				router.push(`/chat/${id}`);
				return;
			}
			toast('wrong password');
			setpass('');
			setprotect(false);
		}
	};
	if (ismember) {
		return (
			<Link href={`/chat/${id}`}>
				<div className="flex items-center gap-4 p-4 cursor-pointer hover:bg-white/20">
					<Image
						width={40}
						height={40}
						src="/sources/Channel.svg"
					/>
					<h3> {name} </h3>
				</div>
			</Link>
		);
	}
	if (protect) {
		return (
			<button onClick={submitandenter}>
				<div className="flex items-center gap-4 p-4 cursor-pointer hover:bg-white/20">
					<Image
						width={40}
						height={40}
						src="/sources/Channel.svg"
					/>
					<input
						onChange={handleChange}
						onKeyDown={handleKeyDown}
						type="password"
						value={pass}
					/>
				</div>
				<ToastContainer />
			</button>
		);
	}
	return (
		<div onClick={submitandenter}>
			<div className="flex items-center gap-4 p-4 cursor-pointer hover:bg-white/20">
				<Image
					width={40}
					height={40}
					src="/sources/Channel.svg"
				/>
				<h3> {name} </h3>
			</div>
		</div>
	);
};

export default Channeltag;
