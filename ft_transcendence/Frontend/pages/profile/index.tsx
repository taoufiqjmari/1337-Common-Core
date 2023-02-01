//Frontend/Pages/profile/index.tsx
import React, { useEffect, useState } from 'react';
import Acheivements from '../../components/Acheivements';
import Battlelog from '../../components/Battlelog';
import ProfileBlock from '../../components/ProfileBlock';
import { Return } from '../../components/Return';

function Profile() {
	const [user, setuser] = useState<any>('');

	useEffect(() => {
		const person = async () => {
			try {
				const ret = await fetch(`http://${process.env.APPNAME}:3000/users/me`, {
					credentials: 'include',
				});

				const user = await ret.json();
				setuser(user);
			} catch (err) {}
		};
		person();
	}, []);
	if (user === '') return <>loading</>;
	return (
		<div className="h-screen">
			<div className="flex justify-between max-w-7xl mx-auto pt-24  ">
				<Return />
				<ProfileBlock useri={user} />
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
