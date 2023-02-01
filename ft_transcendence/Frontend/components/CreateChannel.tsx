import React from 'react';
import Select from 'react-select';
import { Dialog, Transition } from '@headlessui/react';
import { Fragment, useState } from 'react';
import Image from 'next/image';
import { useRouter } from 'next/router';
import { ToastContainer, toast } from 'react-toastify';
import 'react-toastify/dist/ReactToastify.css';

const CreateChannel = () => {
	const [param, setparam] = useState({ name: '', type: '', password: '' });
	let [isOpen, setIsOpen] = useState(false);
	const router = useRouter();
	const options = [
		{ value: 'PRIVATE', label: 'PRIVATE' },
		{ value: 'PROTECTED', label: 'PROTECTED' },
		{ value: 'PUBLIC', label: 'PUBLIC' },
	];
	function exitModal() {
		setparam({ name: '', type: '', password: '' });
		setIsOpen(false);
	}
	async function closeModal() {
		let bodyContent = JSON.stringify({ ...param });
		let response = await fetch(`http://${process.env.APPNAME}:3000/chat/createChannel`, {
			method: 'POST',
			body: bodyContent,
			headers: {
				'Content-Type': 'application/json',
			},
			credentials: 'include',
		});
		if (!response.ok) {
			toast('wrong Input');
			setIsOpen(false);
			setparam({ name: '', type: '', password: '' });
			return;
		}
		let data = await response.json();
		router.push(`http://${process.env.APPNAME}:3001/chat/${data.id}`);
		setIsOpen(false);
	}
	function updatename(event: any) {
		setparam({
			name: event.target.value,
			type: param.type,
			password: param.password,
		});
	}
	function updatepassword(event: any) {
		setparam({
			name: param.name,
			type: param.type,
			password: event.target.value,
		});
	}
	function updatetype(event: any) {
		setparam({ name: param.name, type: event.value, password: param.password });
	}
	function openModal() {
		setIsOpen(true);
	}
	return (
		<div className=" w-full h-full">
			<div className="flex items-center justify-center">
				<button
					type="button"
					onClick={openModal}
					className="  hover:bg-opacity-30"
				>
					<Image
						className="z-10"
						src="/sources/Plus.svg"
						width={25}
						height={25}
					></Image>
				</button>
			</div>

			<Transition
				appear
				show={isOpen}
				as={Fragment}
			>
				<Dialog
					as="div"
					className=" z-10"
					onClose={exitModal}
				>
					<Transition.Child
						as={Fragment}
						enter="ease-out duration-300"
						enterFrom="opacity-0"
						enterTo="opacity-100"
						leave="ease-in duration-200"
						leaveFrom="opacity-100"
						leaveTo="opacity-0"
					>
						<div className="fixed inset-0  bg-opacity-25" />
					</Transition.Child>

					<div className="fixed inset-0 overflow-y-auto">
						<div className="flex min-h-full items-center justify-center text-center">
							<Transition.Child
								as={Fragment}
								enter="ease-out duration-300"
								enterFrom="opacity-0 scale-50"
								enterTo="opacity-100 scale-100"
								leave="ease-in duration-200"
								leaveFrom="opacity-100 scale-100"
								leaveTo="opacity-0 scale-50"
							>
								<Dialog.Panel className="w-full max-w-5xl transform overflow-hidden rounded-2xl bg-glass p-6 text-left align-middle shadow-xl transition-all">
									<Dialog.Title
										as="h3"
										className="text-lg font-medium leading-6 text-gray-900"
									>
										Create Room
									</Dialog.Title>
									<div className="mt-2 ">
										<p>name</p>
										<input
											onChange={updatename}
											value={param.name}
											className="rounded-full placeholder:text-black/60 bg-white/20"
											type="text"
											placeholder="channel Name"
										/>
										<p>options</p>
										<Select
											onChange={updatetype}
											className="bg-black"
											options={options}
										/>
										<p>Password</p>
										<input
											onChange={updatepassword}
											value={param.password}
											className="rounded-full placeholder:text-black/60 focus:border-white bg-white/20"
											type="password"
											placeholder="Password"
										/>
									</div>

									<div className="mt-4">
										<button
											type="button"
											className="inline-flex justify-center rounded-md bg-blue-100 px-4 py-2 text-sm font-medium text-blue-900 hover:bg-blue-200"
											onClick={closeModal}
										>
											Submit
										</button>
									</div>
								</Dialog.Panel>
							</Transition.Child>
						</div>
					</div>
				</Dialog>
			</Transition>
			<ToastContainer />
		</div>
	);
};

export default CreateChannel;
