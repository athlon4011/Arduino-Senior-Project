<?php

$VARDB_server = 'localhost';
$VARDB_port = '3306';
$VARDB_user = 'root';
$VARDB_pass = 'H0m3r';
$VARDB_custom_user = 'custom';
$VARDB_custom_pass = 'custom1234';
$VARDB_database = 'homer';
$WeBServeRRooT = '/usr/local/apache2/htdocs';

$link=mysqli_connect($VARDB_server, "$VARDB_user", "$VARDB_pass", "$VARDB_database", $VARDB_port);

function mysql_to_mysqli($stmt, $link) {
	$rslt=mysqli_query($link, $stmt);
	return $rslt;
}
//getData($link);

if(isset($_POST['type'])) {
	switch($_POST['type']) {
		case 'nodeData':
		getData($link);
		break;
		case 'rulesGet':
		
		break;
		case 'rulesSet':
		
		break;
		case 'test':
		break;
	}
}

function getData($link) {
	$stmt="SELECT * FROM Nodes;";
	$result = "";
	foreach(mysql_to_mysqli($stmt, $link) as $row) {
		$result .= "{\"NodeID\":".$row['NodeID'].",\"node\":[";
		$stmt1="SELECT Date, Data FROM homer.Sensor_Log where NodeID='".$row['NodeID']."' order by Date desc LIMIT 50;";
		foreach(mysql_to_mysqli($stmt1, $link) as $row1) {
			//echo $row1['Data'];
			$newstr = substr_replace($row1['Data'], "\"Date\": \"".$row1['Date']."\",", 1, 0);
			$newstr .= ",";
			$result .= $newstr;
		}
		$result = rtrim($result, ",");
		$result .= "]},";
	}
	$result = rtrim($result, ",");
	//echo "<pre>";
	echo $result;
}



?>