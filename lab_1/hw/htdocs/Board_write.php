<?

$fpn="Data.txt";

if($_POST['str']){
	$fp=fopen($fpn,"w");
	fwrite($fp,$_POST['str'],strlen($_POST['str']));
	fclose($fp);
	
	echo("<meta http-equiv='Refresh' content='1; URL=./Board_main.php'>");
}

echo("	<font size=4><b>게시판 쓰기</b></font>
	<form name='input' method='POST' action='".$_SERVER['PHP_SELF']."'>
	<textarea rows=7 cols=50 name=str></textarea><br><br>
	<input type='submit' value='등록하기'>
	<input type='reset' value='다시기입'>
	</form>
	<a href='Board_main.php'>되돌아 가기</a>
");

/*form 태그를 사용하여 textarea를 설정하여 다시기입을 클릭할 경우 영역 안 내용을 지우고
등록하기를 클릭할 경우 영역 안 내용을 str에 저장하여 상위 if문을 실행하게 한다.
상위 if문에서는 str에 내용이 입력되었을 경우 Data.txt 파일을 열어 문자열을 쓰고
Meta 태그를 통해 Board_write.php에서 Board_main.php 페이지로 돌아가게 한다.*/

?>