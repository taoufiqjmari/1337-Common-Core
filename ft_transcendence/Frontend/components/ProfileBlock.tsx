import { useState, useRef, useEffect } from 'react';
import Image from 'next/image';
import Link from 'next/link';
import React from 'react';

const ProfileBlock: React.FC<{
	useri: any;
}> = ({ useri }) => {
	const [isEdit, setEdit] = useState(false);
	const [user, setuser] = useState(useri);
	const [blob, setblob] = useState<any>('');
	const [message, setMessage] = useState('');
	const inputRef = useRef<any>(null);

	const handleChange = (event: any) => {
		setMessage(event?.target?.value);
	};
	const handleKeyDown = async (event: any) => {
		if (event?.key === 'Enter') {
			setEdit(false);
			let bodyContent = JSON.stringify({
				name: message,
			});
			let response = await fetch(`http://${process.env.APPNAME}:3000/users/edit`, {
				method: 'PUT',
				body: bodyContent,
				headers: {
					'Content-Type': 'application/json',
				},
				credentials: 'include',
			});
			if (!response.ok) return;
			let data = await response.json();
			setuser(data);
			setMessage('');
		}
	};
	const uploadImage = () => {
		inputRef?.current?.click();
	};
	const uploaded = async (event: any) => {
		const fileUploaded = event?.target?.files[0];
		if (!fileUploaded) return;
		const formData = new FormData();
		formData.append('avatar', event.target.files![0]);
		let setAvatar = await fetch(`http://${process.env.APPNAME}:3000/users/avatar`, {
			method: 'POST',
			body: formData,
			credentials: 'include',
		});
		if (!setAvatar.ok) return;
		const data = await setAvatar.json();
		const resp = await fetch(`http://${process.env.APPNAME}:3000/users/avatar/${data.id}`, {
			credentials: 'include',
		});
		if (!resp.ok) return;
		const blob = await resp.blob();
		const img = URL.createObjectURL(blob);
		setuser(data);
		setblob(img);
	};
	useEffect(() => {
		const prfl = async () => {
			if (!useri) return;
			const resp = await fetch(
				`http://${process.env.APPNAME}:3000/users/avatar/${useri.id}`,
				{
					credentials: 'include',
				}
			);
			if (!resp.ok) return;
			const blob = await resp.blob();
			const img = URL.createObjectURL(blob);
			setblob(img);
		};
		prfl();
	}, []);
	if (!useri || !blob) return <>no user or blob</>;
	return (
		<div className="w-64 h-64 rounded-3xl md:w-96 md:h-96 bg-glass flex flex-col justify-between text-center  text-white  font-lexend">
			<div className="relative  flex items-center justify-center">
				<Image
					className="rounded-full "
					src={blob}
					width={150}
					height={150}
					layout="fixed"
					alt=""
				></Image>
				<div className="absolute left-48 md:left-80 bottom-24 ">
					<Link href={`http://${process.env.APPNAME}:3000/auth/logout`}>
						<button>
							<Image
								className="rounded-full cursor-pointer"
								src="/sources/Power.svg"
								width={50}
								height={50}
								layout="fixed"
								alt=""
							></Image>
						</button>
					</Link>
				</div>
				<div
					className="absolute right-8  md:right-24 top-24 w-14 h-14"
					onClick={uploadImage}
				>
					<Image
						className="rounded-full bg-glass cursor-pointer"
						src="/sources/Plus.svg"
						width={42}
						height={42}
						layout="fixed"
						alt=""
					></Image>
					<input
						className="hidden"
						ref={inputRef}
						onChange={uploaded}
						type="file"
						accept="image/*"
					/>
				</div>
			</div>
			<div className="relative flex items-center justify-center">
				<h3 className={`font-bold truncate  w-[40%] ${isEdit ? 'hidden' : ''}`}>
					{user.name}
				</h3>
				<input
					onChange={handleChange}
					onKeyDown={handleKeyDown}
					value={message}
					maxLength={10}
					minLength={3}
					placeholder={'...'}
					className={`bg-transparent outline-0 text-center w-[40%] font-bold placeholder:text-white ${
						!isEdit ? 'hidden' : ''
					}`}
				></input>
				<div className="absolute left-[80%]">
					<button
						onClick={() => {
							setEdit(isEdit ? false : true);
						}}
					>
						<Image
							className={`cursor-pointer `}
							src={`/sources/${isEdit ? 'keyb' : 'pen'}.svg`}
							width={25}
							height={25}
							layout="fixed"
							alt=""
						></Image>
					</button>
				</div>
			</div>
			<div className="relative table rounded-3xl h-12 md:h-20  ">
				<div className="absolute h-full w-full flex items-center justify-center">
					<h3>{`level ${Math.floor(user.ladder / 100)} - ${user.ladder % 100}%`}</h3>
				</div>
			</div>
		</div>
	);
};

export default ProfileBlock;
