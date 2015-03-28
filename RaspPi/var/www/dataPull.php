<?
require("functions.php");

$type = $_POST['type'];
$query = $_POST['query'];
$rid = $_POST['rid'];
switch($type) {
	case 'single':
		if($query == 'select') {
			$stmt="SELECT Title,Description,Data FROM Rules where rid=$rid;";
			$result = mysqli_fetch_row(mysql_to_mysqli($stmt, $link));
			echo json_encode(array("Title"=>$result[0],"Description"=>$result[1],"Data"=>$result[2]));
		}
	break;
}


?>