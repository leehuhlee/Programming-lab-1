<?

$fpn="Data.txt";
$fp=fopen($fpn,"r");
$a=fread($fp,1000);
$str=(string)$a;	//Data.txt ������ ���� ������ �о�� ������ �����Ѵ�.
fclose($fp);

echo("	<font size=4><b>�Խ��� �б�</b></font>
	<form name='output'>
	<textarea rows=7 cols=50>$str</textarea></form>
");			//textarea�� �����Ͽ� ����� ���ڿ��� ����Ѵ�.

echo("	<a href='Board_main.php'>�ǵ��� ����</a>");

?>