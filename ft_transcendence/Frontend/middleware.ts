import { NextResponse } from 'next/server';
import type { NextRequest } from 'next/server';
import { jwtVerify } from 'jose';

const pages = ['/chat', '/home', '/play', '/settings', '/profile', '/streams'];
function BlockedPages(name: string): boolean {
	let result = false;
	pages.forEach((page) => {
		if (name.includes(page)) {
			result = true;
			return;
		}
	});
	return result;
}

async function hasAccess(jwt: string) {
	try {
		await jwtVerify(jwt, new TextEncoder().encode(process.env.JWT_ACCESS_SECRET));
		return true;
	} catch {
		return false;
	}
}
async function hasRefresh(jwt: string) {
	try {
		await jwtVerify(jwt, new TextEncoder().encode(process.env.JWT_REFRESH_SECRET));
		return true;
	} catch {
		return false;
	}
}

export default async function middleware(req: NextRequest) {
	const jwt = req.cookies.get('access-token');
	const rjwt = req.cookies.get('refresh-token');
	if (req.nextUrl.pathname === '/') {
		let hasAccessBool = await hasAccess(jwt || '');
		let hasRefreshBool = await hasRefresh(rjwt || '');
		if (hasAccessBool && hasRefreshBool) {
			return NextResponse.redirect(`http://${process.env.APPNAME}:3001/home`);
		} else {
			return NextResponse.next();
		}
	}
	if (req.nextUrl.pathname === '/tfa') {
		let hasAccessBool = await hasAccess(jwt || '');
		let hasRefreshBool = await hasRefresh(rjwt || '');
		if (hasAccessBool && !hasRefreshBool) {
			return NextResponse.next();
		} else {
			return NextResponse.redirect(`http://${process.env.APPNAME}:3001/`);
		}
	}
	if (BlockedPages(req.nextUrl.pathname)) {
		let hasAccessBool = await hasAccess(jwt || '');
		let hasRefreshBool = await hasRefresh(rjwt || '');
		if (hasAccessBool && hasRefreshBool) {
			return NextResponse.next();
		} else {
			return NextResponse.redirect(`http://${process.env.APPNAME}:3001/`);
		}
	}
	return NextResponse.next();
}
