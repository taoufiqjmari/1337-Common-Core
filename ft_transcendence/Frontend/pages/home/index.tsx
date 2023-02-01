import React from 'react';
import Link from 'next/link';
import Image from 'next/image';

const t = [
	[
		'Play',
		'Play with your friends or with random players',
		'col-span-2 ',
		'/sources/tableF.png',
		'h-full',
		'',
	],
	[
		'Streams',
		'Watch your friends or random players playing pong',
		'',
		'/sources/tvF.png',
		'w-full h-[0]  pt-[100%]',
		'flex justify-center items-center',
	],
	[
		'Chat',
		'Make interesting converstions with your friends and challenge them',
		'',
		'/sources/msgF.png',
		'w-full h-[0]  pt-[100%]',
		'flex justify-center items-center',
	],
	[
		'Settings',
		'Enable or Disable two factor authentication',
		'',
		'/sources/gearF.png',
		'w-full h-[0]  pt-[100%]',
		'flex justify-center items-center',
	],
	[
		'Profile',
		'invite some friends and see your level, trophies and acheivements',
		'',
		'/sources/prflF.png',
		'w-full h-[0]  pt-[100%]',
		'flex justify-center items-center',
	],
];

function Home() {
	return (
		<div className="flex justify-center items-center h-screen">
			<div className="font-lexend  grid grid-cols-2 grid-rows-3 gap-2 w-96 h-[32rem] md:w-[32rem] md:h-[40rem] lg:w-[40rem] lg:h-[48rem] xl:w-[48rem] xl:h-[54rem] 2xl:w-[54rem] 2xl:h-[62rem]">
				{t.map(([title, dsc, style, imge, style2, style3]) => (
					<Link
						key={title}
						href={title.toLocaleLowerCase()}
					>
						<div
							className={`cursor-pointer bg-glass border border-black rounded-[48px] grid grid-cols-2 ${style} `}
						>
							<div className=" grid place-items-center lg:grid-rows-2 text-center xl:text-lg 2xl:text-xl text-black">
								<div className="md:text-lg xl:text-xl 2xl:text-2xl"> {title}</div>
								<p className="text-clip hidden lg:block lg:text-ellipsis w-full h-full font-nanum px-2">
									{' '}
									{dsc}
								</p>
							</div>
							<div className={`${style3}`}>
								<div className={`relative drop-shadow-2xl ${style2}`}>
									<Image
										src={imge}
										layout="fill"
										priority={true}
									></Image>
								</div>
							</div>
						</div>
					</Link>
				))}
			</div>
		</div>
	);
}

export default Home;
