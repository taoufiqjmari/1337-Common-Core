import { useRouter } from "next/router";
import Canvas  from "../../components/Canvas";
import { Return } from "../../components/Return";

export default function StreamID() {
  const router = useRouter();
  const data = router.query;

  if (!data.id) return(<></>);
  return (
    <div className='max-w-7xl mx-auto -bg-orange-400/60 pt-24 '>
      <Return />
      <Canvas mode="stream" roomName={data.id as string}/>
    </div>
  );
}