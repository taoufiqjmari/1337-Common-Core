import '../styles/globals.css';
import type { AppProps } from 'next/app';
import Bground from '../components/Bground';
import { io, Socket } from 'socket.io-client';
import { useEffect } from 'react';

function MyApp({ Component, pageProps }: AppProps) {
	let socket: Socket;

	// handle user status
	useEffect(() => {
		socket = io(`http://${process.env.APPNAME}:5500`, {
			withCredentials: true,
		});

		return () => {
			socket.disconnect();
		};
	}, []);

	return (
		<>
			<Bground />
			<Component {...pageProps} />
		</>
	);
}

export default MyApp;
