import { useRouter } from 'next/router';
import React, { useEffect, useState } from 'react';
import Canvas from '../../components/Canvas';
import { Return } from '../../components/Return';

function Index() {
	const [gameTheme, setGameTheme] = useState('');
	const [userStatus, setUserStatus] = useState('');
	const route = useRouter();

	useEffect(() => {
		if (userStatus == 'PLAYING') route.push('/home');
	}, [userStatus]);

	useEffect(() => {
		async function checkUserStatus() {
			try {
				const res = await fetch(`http://${process.env.APPNAME}:3000/users/me`, {
					credentials: 'include',
				});
				const data = await res.json();
				setUserStatus(data.status);
			} catch (err) {}
		}
		checkUserStatus();
	}, []);

	// onclick
	function chooseGameMode(theme: string) {
		setGameTheme(theme);
	}

	if (route.query.mode == 'invite') {
		return (
			<div className="max-w-7xl mx-auto -bg-orange-400/60 pt-24 ">
				<Return />
				<Canvas
					mode="invite"
					gameMode={gameTheme}
					inviteId={route.query.id as string}
				/>
			</div>
		);
	}
	if (gameTheme != '') {
		return (
			<div className="max-w-7xl mx-auto -bg-orange-400/60 pt-24 ">
				<Return />
				<Canvas
					mode="play"
					gameMode={gameTheme}
				/>
			</div>
		);
	}

	return (
		<div className="max-w-7xl mx-auto -bg-orange-400/60 pt-24 ">
			<Return />
			<div
				className={` w-[900px] h-[500px] border-2 rounded border-#3D52D5 bg-#0C0915 mx-auto 
            canvas_sm:w-[340px] canvas_sm:h-[189px]
            canvas_md:w-[500px] canvas_md:h-[278px]
            canvas_lg:w-[700px] canvas_lg:h-[389px]
            canvas_xl:w-[900px] canvas_xl:h-[500px]
            flex`}
			>
				<button
					onClick={() => {
						chooseGameMode('multi');
					}}
					className={`text-xl font-extrabold px-5 mx-auto text-white
                    hover:grow hover:bg-white hover:text-#0C0915 hover:text-3xl duration-100
                    canvas_sm:text-xs canvas_sm:hover:text-base`}
				>
					Multiplayer
				</button>
				<button
					onClick={() => {
						chooseGameMode('single');
					}}
					className={`text-xl font-extrabold px-5 mx-auto text-white
                    hover:grow hover:bg-#3D52D5 hover:text-#CDF2F0 hover:text-3xl duration-100
                    canvas_sm:text-xs canvas_sm:hover:text-base`}
				>
					Singleplayer
				</button>
			</div>
		</div>
	);
}

export default Index;
