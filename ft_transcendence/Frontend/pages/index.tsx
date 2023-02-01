//Frontend/Pages/index.tsx
import Head from 'next/head';
import Link from 'next/link';
import Bground from '../components/Bground';
import Glass from '../components/Glass';

const Home = () => {
	return (
		<>
			<Head>
				<title>transcendence</title>
			</Head>
			<Bground />
			<Link href={`http://${process.env.APPNAME}:3000/auth/login`}>
				<button>
					<Glass />
				</button>
			</Link>
		</>
	);
};

export default Home;
