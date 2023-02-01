import React from 'react';
import Image from 'next/image';
import { useRouter } from 'next/router';
import { Return } from '../../components/Return';
import { useEffect, useState } from 'react';

const Settings = () => {
	const router = useRouter();
	const [user, setuser] = useState<any>(false);
	const [blob, setblob] = useState<any>(false);
	const [message, setMessage] = useState<any>('');

	const handleChange = (event: any) => {
		setMessage(event?.target?.value);
	};
	const handleKeyDownDisable = async (event: any) => {
		if (event?.key === 'Enter') {
			let bodyContent = JSON.stringify({
				token: message,
			});
			try {
				let response = await fetch(`http://${process.env.APPNAME}:3000/tfa/disable`, {
					method: 'POST',
					body: bodyContent,
					headers: {
						'Content-Type': 'application/json',
					},
					credentials: 'include',
				});
				if (!response.ok) return;
			} catch (err) {
				return;
			}
			setuser(user);
			setMessage('');
			router.push('/home');
		}
	};
	const handleKeyDown = async (event: any) => {
		if (event?.key === 'Enter') {
			let bodyContent = JSON.stringify({
				token: message,
			});
			try {
				let response = await fetch(`http://${process.env.APPNAME}:3000/tfa/enable`, {
					method: 'POST',
					body: bodyContent,
					headers: {
						'Content-Type': 'application/json',
					},
					credentials: 'include',
				});
				if (!response.ok) return;
			} catch (err) {
				return;
			}
			setuser(user);
			setMessage('');
			router.push('/home');
		}
	};
	useEffect(() => {
		const person = async () => {
			try {
				const ret = await fetch(`http://${process.env.APPNAME}:3000/users/me`, {
					credentials: 'include',
				});
				if (!ret.ok) return;
				const user = await ret.json();
				setuser(user);
			} catch {}
		};
		if (!user) person();
		const tfaBlob = async () => {
			try {
				const ret = await fetch(`http://${process.env.APPNAME}:3000/tfa/generate`, {
					credentials: 'include',
				});
				if (!ret.ok) return;
				const dump = await ret.blob();
				const img = URL.createObjectURL(dump);
				setblob(img);
			} catch {}
		};
		if (user && user.tfa == false) tfaBlob();
	}, [user]);
	if (!user) return <>loading</>;
	if (user.tfa) {
		return (
			<div className="h-screen flex flex-col">
				<div className="mx-auto w-full my-auto flex items-center justify-center max-w-7xl">
					<div className="grow">
						<Return />
					</div>
				</div>
				<div className="bg-glass mx-auto max-w-5xl my-auto min-h-[800px] h-[60%] w-[90%] rounded-3xl flex flex-col gap-1 md:gap-20 items-center justify-center font-lexend text-white">
					<div className="bg-[#8F0982] shadow-[inset_0px_0px_20px_10px_#212121] rounded-full w-[80%] h-[15%] cursor-pointer flex items-center justify-center">
						<input
							onChange={handleChange}
							onKeyDown={handleKeyDownDisable}
							value={message}
							placeholder="to disable 2FA enter the code"
							className="w-[80%] h-full rounded-full bg-transparent outline-0 text-center "
						/>
						<Image
							className=" "
							src="/sources/Send.svg"
							width={50}
							height={50}
							layout="fixed"
						/>
					</div>
				</div>
			</div>
		);
	}
	if (!blob) return <>loading qr code</>;
	return (
		<div className="h-screen flex flex-col">
			<div className="mx-auto w-full my-auto flex items-center justify-center max-w-7xl">
				<div className="grow">
					<Return />
				</div>
			</div>
			<div className="bg-glass mx-auto max-w-5xl my-auto min-h-[800px] h-[60%] w-[90%] rounded-3xl flex flex-col gap-1 md:gap-20 items-center justify-center font-lexend text-white">
				<Image
					className=""
					src={blob}
					width={300}
					height={300}
					layout="fixed"
				/>
				<div className="bg-[#8F0982] shadow-[inset_0px_0px_20px_10px_#212121] rounded-full w-[80%] h-[15%] cursor-pointer flex items-center justify-center">
					<input
						onChange={handleChange}
						onKeyDown={handleKeyDown}
						value={message}
						placeholder="Confirmation Number"
						className="w-[80%] h-full rounded-full bg-transparent outline-0 text-center "
					/>
					<Image
						className=" "
						src="/sources/Send.svg"
						width={50}
						height={50}
						layout="fixed"
					/>
				</div>
			</div>
		</div>
	);
};

export default Settings;
