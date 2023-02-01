import React from 'react';
import { useRouter } from 'next/router';
import { useState } from 'react';

const Tfa = () => {
	const router = useRouter();
	const [message, setMessage] = useState<any>('');

	const handleChange = (event: any) => {
		setMessage(event?.target?.value);
	};
	const handleKeyDown = async (event: any) => {
		if (event?.key === 'Enter') {
			let bodyContent = JSON.stringify({
				token: message,
			});
			try {
				let response = await fetch(`http://${process.env.APPNAME}:3000/tfa/authenticate`, {
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
			setMessage('');
			router.push('/home');
		}
	};

	return (
		<div className="h-screen flex flex-col">
			<div className="bg-glass mx-auto max-w-5xl my-auto min-h-[800px] h-[60%] w-[90%] rounded-3xl flex flex-col gap-1 md:gap-20 items-center justify-center font-lexend text-white">
				<div className="bg-[#8F0982] shadow-[inset_0px_0px_20px_10px_#212121] rounded-full w-[80%] h-[15%] cursor-pointer flex items-center justify-center">
					<input
						onChange={handleChange}
						onKeyDown={handleKeyDown}
						value={message}
						placeholder="Enter 2FA Password"
						className="w-[80%] h-full rounded-full bg-transparent outline-0 text-center "
					/>
				</div>
			</div>
		</div>
	);
};

export default Tfa;
