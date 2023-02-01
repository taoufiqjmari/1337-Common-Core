import React from 'react'
import Image  from 'next/image'
import { Menu ,Transition } from '@headlessui/react'

const Acheivements:React.FC<{
    ac?:Boolean[],
}> =  ({ac=[false,false,false]}) => {
  return (
    <div>
      <Menu as="div" className="relative w-full ">
          <Menu.Button as="div" className='bg-glass cursor-pointer md:hover:scale-[1.05] w-16 h-16 xl:w-24 xl:h-24 rounded-full flex justify-center items-center'>
			<div className='relative w-10 h-10  xl:w-12 xl:h-12'>
            <Image src="/sources/trophy.svg" layout='fill' />
          	</div>
          </Menu.Button>
          <div className=''>
            <Transition
            as="div"
            enter="transition ease-out duration-100"
            enterFrom="transform opacity-0 scale-95"
            enterTo="transform opacity-100 scale-100"
            leave="transition ease-in duration-75"
            leaveFrom="transform opacity-100 scale-100"
            leaveTo="transform opacity-0 scale-95"
          >
            <Menu.Items as="div" className={"absolute focus:outline-none bg-glass rounded-full"}>
              {[
                [ac[0], 'Bullseye',"/sources/eye.svg",'win 3 matches'],
                [ac[1], 'Dominator',"/sources/bolt.svg", 'score 11 - 0 in a match'],
                [ac[2], 'Newbie',"/sources/friends.svg", 'win a game'],
              ].map(([color, dsc , src, dsc2]) => (
                <Menu.Item key={`${dsc}`} as="div" disabled={!color} >
                  {({ active  }) => (
                    <div className={` w-16 h-16 xl:w-24 xl:h-24 ${color ? 'flex justify-center items-center' : 'hidden'} `}> 
                  <p className={`absolute m-auto h-20 w-48   right-24 bg-white/40 truncate rounded-full text-center text-lg p-1  ${!active && 'hidden'}`} >
                    <span className='font-bold'>{`${dsc}`}</span>
                    <br />
                    <span>{`${dsc2}`}</span>
                  </p>
                  <Image  src={`${src}`} width="40" height="40" />
                  </div> 
                  )}
                </Menu.Item>
              ))}

            </Menu.Items>
            </Transition>
          </div>
      </Menu>
    </div>
  )
}

export default Acheivements