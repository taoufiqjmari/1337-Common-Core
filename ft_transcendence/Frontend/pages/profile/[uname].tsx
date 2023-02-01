import React, { useEffect, useState } from 'react';
import Acheivements from '../../components/Acheivements';
import FriendProfile from '../../components/FriendProfile';
import { Return } from '../../components/Return';
import Battlelog from '../../components/Battlelog';

import { useRouter } from 'next/router';

function Profile() {
	const router = useRouter();
	const { uname } = router.query;

	const [user, setuser] = useState<any>('');

	useEffect(() => {
		const person = async () => {
			try {
				if (!uname) return;
				const ret = await fetch(`http://${process.env.APPNAME}:3000/users/${uname}`, {
					credentials: 'include',
				});
				const user = await ret.json();

				if (ret.ok) setuser(user);
			} catch (err) {}
		};

		person();
	}, [uname]);

	if (!uname)
		return (
			<div className="h-screen">
				<div className="flex justify-between max-w-7xl mx-auto pt-24  ">
					<Return />
				</div>
				<div className="bg-glass w-[90%] h-[90%] max-w-7xl mx-auto flex items-center justify-center font-lexend text-white">
					<h3>Loading</h3>
				</div>
			</div>
		);
	if (user === '')
		return (
			<div className="h-screen">
				<div className="flex justify-between max-w-7xl mx-auto pt-24  ">
					<Return />
				</div>
				<div className="bg-glass w-[90%] h-[90%] max-w-7xl mx-auto flex items-center justify-center font-lexend text-white">
					<h3>This user does not exist !!!</h3>
				</div>
			</div>
		);
	return (
		<div className="h-screen">
			<div className="flex justify-between max-w-7xl mx-auto pt-24  ">
				<Return />
				<FriendProfile useri={user} />
				<Acheivements
					ac={[
						user?.achievements.includes('WIN_THREE_GAMES'),
						user?.achievements.includes('DENIAL'),
						user?.achievements.includes('WIN_A_GAME'),
					]}
				/>
			</div>
			<Battlelog user={user} />
		</div>
	);
}

export default Profile;
