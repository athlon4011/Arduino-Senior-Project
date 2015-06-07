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

if(isset($_GET['type'])) {
	switch($_GET['type']) {
		case 'nodeData':
			getData($link);
		break;
		case 'eventLog':
			eventLog($link);
		break;
		case 'rulesGet':
			rulesGet($link);
		break;
		case 'rulesSet':
			if(isset($_GET['rid'])) {
				rulesSet($link,$_GET['rid']);
			} else {
				wrongCall();
			}
		break;
		case 'test':
			wrongCall();
		break;
		default:
			wrongCall();	
		break;
	}
} else {
	wrongCall();
}

function wrongCall() {
	echo "Invalid request. Check Documentation.";
	exit;
}

function rulesSet($link,$rid) {
	$stmt="SELECT * FROM Rules where rid=$rid;";
	$result = mysqli_fetch_row(mysql_to_mysqli($stmt, $link));
	//print_r($result);
	echo $result[2];
	if($result[2] == 1) {
		$bool = 0;
	} else {
		$bool = 1;
	};
	$stmt="UPDATE Rules SET enabled=$bool WHERE rid=$rid;";
	mysql_to_mysqli($stmt, $link);
	exit;
}

function rulesGet($link) {
	$stmt="SELECT * FROM Rules;";
	$result = "";
	foreach(mysql_to_mysqli($stmt, $link) as $row) {
		$result .= "{ID: \"".$row['rid']."\",Enabled: ".$row['enabled'].",Title: \"".$row['Title']."\",Description: \"".$row['Description']."\"},";
	}
	$result = rtrim($result, ",");
	echo $result;
	exit;
}

function eventLog($link) {
	$stmt="SELECT * FROM Event_Log LIMIT 100;";
	$result = "";
	foreach(mysql_to_mysqli($stmt, $link) as $row) {
		$result .= "{Date: \"".$row['Date']."\",Type: \"".$row['Type']."\",Message: \"".$row['Message']."\"},";
	}
	$result = rtrim($result, ",");
	echo $result;
	exit;
}

function getData($link) {
	$stmt="SELECT * FROM Nodes;";
	$result = "";
	foreach(mysql_to_mysqli($stmt, $link) as $row) {
		$result .= "{\"NodeID\":".$row['NodeID'].",\"node\":[";
		$stmt1="SELECT Date, Data FROM Sensor_Log where NodeID='".$row['NodeID']."' order by Date desc LIMIT 50;";
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
	exit;
}



?>