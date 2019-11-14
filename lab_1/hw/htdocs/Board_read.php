<?

$fpn="Data.txt";
$fp=fopen($fpn,"r");
$a=fread($fp,1000);
$str=(string)$a;	//Data.txt 파일을 열어 내용을 읽어와 변수에 저장한다.
fclose($fp);

echo("	<font size=4><b>게시판 읽기</b></font>
	<form name='output'>
	<textarea rows=7 cols=50>$str</textarea></form>
");			//textarea를 설정하여 저장된 문자열을 출력한다.

echo("	<a href='Board_main.php'>되돌아 가기</a>");

?>