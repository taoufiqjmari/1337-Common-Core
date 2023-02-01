import React, { useState } from 'react';
import { io } from 'socket.io-client';
import Link from 'next/link';
import { Return } from '../../components/Return';

let socket = io(`http://${process.env.APPNAME}:5500`, {
	withCredentials: true,
});

export default function Streams() {
	const [rooms, setRooms] = useState<string[]>([]);
	const [none, setNone] = useState('None');

	setInterval(() => {
		socket.emit('getRooms');
	}, 1000 / 2);

	socket.on('roomsList', (listOfRooms: string[]) => {
		setRooms(listOfRooms);
		if (listOfRooms.length > 0) setNone('');
		else setNone('None');
	});

	return (
		<div className="max-w-7xl mx-auto -bg-orange-400/60 pt-24">
			<Return />
			<div className=" rounded bg-glass p-8 m-5 bg-#3D52D5/10 min-h-[42rem]">
				<div className="grid auto-rows-fr gap-6 ">
					<h1 className="text-2xl text-white font-bold col-start-1 col-end-5 text-center">
						Rooms : {none}
					</h1>
					{rooms.map((room) => {
						return (
							<Link
								key={room}
								href={`/streams/${room}`}
							>
								<div className="bg-#CDF2F0/20 bg-glass font-bold text-lg text-#0C0915 text-center py-8 rounded cursor-pointer">
									{room}
								</div>
							</Link>
						);
					})}
				</div>
			</div>
		</div>
	);
}
