<?

$fpn="counter.txt";

$fp=fopen($fpn,"r");
$count=fread($fp,filesize($fpn));
fclose($fp);		//counter.txt 파일을 읽어와 변수에 저장한다.

if(!$_COOKIE['ip']){
	setcookie("ip",$_SERVER['REMOTE_ADDR']);
	$count++;
}			//쿠키가 존재하지 않을 경우 쿠키를 생성하고 변수를 증가시킨다.

$str=(string)$count;

for($i=0; $i<strlen($str); $i++){
	$ch=substr($str,$i,1);
	switch($ch){
		case 0; echo("<img src='0.jpg'>");	break;
		case 1; echo("<img src='1.jpg'>");	break;
		case 2; echo("<img src='2.jpg'>");	break;
		case 3; echo("<img src='3.jpg'>");	break;
		case 4; echo("<img src='4.jpg'>");	break;
		case 5; echo("<img src='5.jpg'>");	break;
		case 6; echo("<img src='6.jpg'>");	break;
		case 7; echo("<img src='7.jpg'>");	break;
		case 8; echo("<img src='8.jpg'>");	break;
		case 9; echo("<img src='9.jpg'>");	break;
	}
}
//변수를 문자열로 저장하여 각 자릿수를 떼어 해당 숫자에 대응하는 이미지를 HTML 태그를 이용하여 출력한다.

$fp=fopen($fpn,"w");
fwrite($fp,"$count",strlen($count));	//최종 변수값을 다시 파일에 저장한다.
fclose($fp);

?>