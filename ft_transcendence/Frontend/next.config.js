/** @type {import('next').NextConfig} */
const nextConfig = {
	reactStrictMode: false,
	swcMinify: true,
	eslint: {
		ignoreDuringBuilds: true,
	},
	env: {
		APPNAME: process.env.APPNAME,
	},
};

module.exports = nextConfig;
