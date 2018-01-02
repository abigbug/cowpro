<?php
class Common
{
	private $antistate = 0;
	
	public function getAntiState()
	{
		return $this->antistate;
	}
	
	public function getRandomNum($length)
	{
		$output='';
		for($a=0;$a<$length;$a++)
		{
			$output.=chr(mt_rand(48,57));//生成php随机数
		}
		return $output;
	}
	
	public function getTimeStamp()
	{
		$output=gmdate('YmdHis', time() + 3600 * 8).floor(microtime()*1000);
		return $output;
	}
	
	public function getRandomTimeStamp()
	{
		$output=$this->getRandomNum(2).$this->getTimeStamp();
		return $output;
	}
}
?>