<?

$fpn="Data.txt";

if($_POST['str']){
	$fp=fopen($fpn,"w");
	fwrite($fp,$_POST['str'],strlen($_POST['str']));
	fclose($fp);
	
	echo("<meta http-equiv='Refresh' content='1; URL=./Board_main.php'>");
}

echo("	<font size=4><b>�Խ��� ����</b></font>
	<form name='input' method='POST' action='".$_SERVER['PHP_SELF']."'>
	<textarea rows=7 cols=50 name=str></textarea><br><br>
	<input type='submit' value='����ϱ�'>
	<input type='reset' value='�ٽñ���'>
	</form>
	<a href='Board_main.php'>�ǵ��� ����</a>
");

/*form �±׸� ����Ͽ� textarea�� �����Ͽ� �ٽñ����� Ŭ���� ��� ���� �� ������ �����
����ϱ⸦ Ŭ���� ��� ���� �� ������ str�� �����Ͽ� ���� if���� �����ϰ� �Ѵ�.
���� if�������� str�� ������ �ԷµǾ��� ��� Data.txt ������ ���� ���ڿ��� ����
Meta �±׸� ���� Board_write.php���� Board_main.php �������� ���ư��� �Ѵ�.*/

?>