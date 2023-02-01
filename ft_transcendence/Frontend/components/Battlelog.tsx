import React from 'react';
import { useEffect, useState } from 'react';

const Battlelog: React.FC<{
	user: any;
}> = ({ user }) => {
	const [games, getGames] = useState([]);
	useEffect(() => {
		const prfl = async () => {
			if (!user) return;
			const resp = await fetch(`http://${process.env.APPNAME}:3000/game/${user.id}`, {
				credentials: 'include',
			});
			if (!resp.ok) return;
			getGames(await resp.json());
		};
		prfl();
	}, [user]);
	if (!user) return <>no user found</>;
	return (
		<div className="bg-glass mt-24 mx-auto max-w-5xl h-[60%] rounded-3xl overflow-x-auto font-lexend text-white">
			<h3 className=" md:text-lg text-center  font-bold pt-10 md:pt-16">Last Played</h3>

			{games.map((value: any) => (
				<div
					key={Math.random()}
					className="w-full h-24 mt-10 bg-white/10 rounded-full grid grid-cols-3 items-center "
				>
					<h3 className=" md:text-lg text-center font-bold "> {value.player1name}</h3>
					<h3 className="text-xl text-center  font-bold ">{`${value.player1score} vs ${value.player2score} `}</h3>
					<h3 className=" md:text-lg text-center  font-bold ">{value.player2name}</h3>
				</div>
			))}
		</div>
	);
};

export default Battlelog;
