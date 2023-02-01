import React from 'react'
import Image  from 'next/image'

const Glass = () =>{

  return (
    <div className='flex justify-center items-center h-screen w-screen'>
      <div className='outline outline-black	 shadow-[0_35px_60px_-15px_rgba(0,0,0,0.9)] bg-glass hover:ease-in-out  transition duration-150 hover:delay-150 hover:scale-[1.05] rounded-[48px] w-80 h-48 grid grid-cols-2 font-lexend text-black text-4xl md:w-[36rem] md:h-80 lg:w-[48rem] lg:h-96'>
        <div className='flex justify-center items-center text-center'> Login With Intra </div>
        <div className='relative m-12'>
          <Image 
          src="/sources/intra.png"
          layout='fill'
          priority={true}
          alt=""
          ></Image>
        </div>
      </div>
    </div>

  )
}

export default Glass