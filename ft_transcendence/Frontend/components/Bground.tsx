import Image  from 'next/image'

function Bground() {
  return (
    <div className='z-[-999] fixed  w-screen h-screen overflow-hidden'>
        <Image 
        className='brightness-50'
        src="/sources/g_bg.jpeg"
        layout='fill'
        objectFit="cover"
        priority={true}
        />
    </div>
  )
}

export default Bground

