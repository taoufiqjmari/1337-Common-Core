import { useState, useEffect } from 'react';
import Image from 'next/image';
import React from 'react';

const ProfileBlock: React.FC<{
	useri: any;
}> = ({ useri }) => {
	const [blob, setblob] = useState<any>('');
	const [sta, setsta] = useState<any>(false);

	async function friendrequest() {
		let bodyContent = JSON.stringify({
			friendId: useri.id,
		});
		const resp = await fetch(
			`http://${process.env.APPNAME}:3000/users/${
				useri.isFriend === 'NO' ? 'addfriend' : 'unfriend'
			}`,
			{
				method: 'POST',
				body: bodyContent,
				headers: {
					'Content-Type': 'application/json',
				},
				credentials: 'include',
			}
		);
		if (resp.ok) {
			useri.isFriend = useri.isFriend === 'NO' ? 'YES' : 'NO';
			setsta(sta ? false : true);
		}
	}
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
	}, [sta]);
	if (!useri || !blob) return <>no user or blob</>;
	return (
		<div className="w-64 h-64 rounded-3xl md:w-96 md:h-96 bg-glass flex flex-col justify-between text-center  text-white  font-lexend">
			<div className="relative  flex flex-col items-center justify-center">
				<Image
					className="rounded-full "
					src={blob}
					width={150}
					height={150}
					layout="fixed"
					alt=""
				></Image>
				<div
					className={`rounded-full w-6 fixed right-[150px] top-[130px] md:left-[150px] border-white border-2 h-6 ${
						useri.status === 'OFFLINE' ? 'bg-gray-400' : 'bg-green-600'
					}`}
				/>
			</div>
			<div
				onClick={friendrequest}
				className={`absolute right-8  ${
					useri.isFriend === 'ME' ? 'hidden' : ''
				} md:right-24 top-24 w-14 h-14`}
			>
				<Image
					className={`rounded-full ${
						useri.isFriend === 'NO' ? 'bg-green-500' : 'bg-red-500'
					} cursor-pointer`}
					src="/sources/Plus.svg"
					width={42}
					height={42}
					layout="fixed"
					alt=""
				></Image>
			</div>
			<div className="relative flex items-center justify-center">
				<h3 className={`font-bold truncate  w-[40%]`}>{useri.name}</h3>
			</div>
			<div className="relative table rounded-3xl h-12 md:h-20  ">
				<div className="absolute h-full w-full flex items-center justify-center">
					<h3>{`level ${Math.floor(useri.ladder / 100)} - ${useri.ladder % 100}%`}</h3>
				</div>
			</div>
		</div>
	);
};

export default ProfileBlock;
