import React from 'react';
import Link from 'next/link';

const Usertag: React.FC<{
	idx: any;
	name: any;
	member: boolean;
}> = ({ idx, name, member }) => {
	return (
		<Link href={member ? `/chat/${idx}` : `/profile/${idx}`}>
			<div className="flex items-center justify-center gap-4 p-4 cursor-pointer hover:bg-white/20">
				<h3> {name} </h3>
			</div>
		</Link>
	);
};

export default Usertag;
