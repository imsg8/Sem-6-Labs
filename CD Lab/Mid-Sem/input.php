<?
/* A program to generate tokens ad and display symbol table entry */

if(isset($_POST['submit']))
{
	$num = $_POST['num'];
	/* Looping starts*/
	for($j=2; $j<$num; $j++){
		for($j=2; $j<$num; $j++){
			if($j % $k == 0){
				break;
				/* Looping starts*/
			}
			if($k == $j){
				echo "Prime number: $j <br/>";
			}
		}
	}
}
?>
