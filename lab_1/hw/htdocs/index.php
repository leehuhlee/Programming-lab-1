<?

$fpn="counter.txt";

$fp=fopen($fpn,"r");
$count=fread($fp,filesize($fpn));
fclose($fp);		//counter.txt ������ �о�� ������ �����Ѵ�.

if(!$_COOKIE['ip']){
	setcookie("ip",$_SERVER['REMOTE_ADDR']);
	$count++;
}			//��Ű�� �������� ���� ��� ��Ű�� �����ϰ� ������ ������Ų��.

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
//������ ���ڿ��� �����Ͽ� �� �ڸ����� ���� �ش� ���ڿ� �����ϴ� �̹����� HTML �±׸� �̿��Ͽ� ����Ѵ�.

$fp=fopen($fpn,"w");
fwrite($fp,"$count",strlen($count));	//���� �������� �ٽ� ���Ͽ� �����Ѵ�.
fclose($fp);

?>