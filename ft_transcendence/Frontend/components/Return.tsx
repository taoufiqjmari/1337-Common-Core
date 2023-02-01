import React from 'react'
import Image  from 'next/image'
import Link from 'next/link'

export const Return = () => {
  return (
      <Link href="/home">
        <div className=' bg-glass w-16 h-16 xl:w-24 xl:h-24 rounded-full flex justify-center items-center cursor-pointer'>
          <div className='relative w-10 h-10  xl:w-12 xl:h-12'>
            <Image src="/sources/return.svg" layout='fill' alt='' />
          </div>
        </div>
      </Link>
  )
}
