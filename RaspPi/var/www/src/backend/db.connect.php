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
		case 'settings':
			if(isset($_GET['start']) && isset($_GET['end']) && isset($_GET['cool']) && isset($_GET['heat'])) {
				unset($_GET['type']);
				updateSettings($link, json_encode($_GET));
			} else {
				wrongCall();
			}
		break;
		case 'getSettings':
			getSettings($link);
		break;
		case 'getSurface':
			getSurface($link);
		break;
		case 'removeSurface':
			if(isset($_GET['pid'])) {
				removeSurface($link,$_GET['pid']);
			} else {
				wrongCall();
			}
		break;
		case 'addSurface':
			if(isset($_GET['loc']) && isset($_GET['type'])) {
				addSurface($link,$_GET['loc'],$_GET['type']);
			} else {
				wrongCall();
			}
		break;
		case 'editNode':
			if(isset($_GET['nid']) && isset($_GET['enabled']) && isset($_GET['loc'])) {
				editNode($link,$_GET);
			} else {
				wrongCall();
			}
		break;
		case 'removeNode':
			if(isset($_GET['nid'])) {
				removeNode($link,$_GET['nid']);
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

function removeNode($link,$nid) {
	$stmt = "DELETE FROM Nodes WHERE NodeID='$nid';";
	mysql_to_mysqli($stmt, $link);
	exit;
}

function editNode($link,$params) {
	$stmt = "DELETE FROM ctrl_surf WHERE loc='".$params['loc']."';";
	mysql_to_mysqli($stmt, $link);
	$stmt = "UPDATE Nodes SET Loc='".$params['loc']."', enabled='".$params['enabled']."' WHERE NodeID='".$params['nid']."';";
	mysql_to_mysqli($stmt, $link);
	exit;
}

function addSurface($link,$loc,$type) {
	$stmt = "INSERT INTO ctrl_surf (Type, Loc, State) VALUES ('$type', '$loc', 'off');";
	mysql_to_mysqli($stmt, $link);
	exit;
}

function removeSurface($link,$pid) {
	$stmt = "DELETE FROM ctrl_surf WHERE PID='$pid';";
	mysql_to_mysqli($stmt, $link);
	exit;
}

function getSurface($link) {
	$stmt="SELECT * FROM Nodes;";
	$result = "[";
	foreach(mysql_to_mysqli($stmt, $link) as $row) {
		if($row['enabled'] == 1) {
			$bool = "true";
		} else {
			$bool = "false";
		}
		$result .= "{\"nodeID\":\"".$row['NodeID']."\",\"enabled\":\"".$bool."\",\"nodeLocation\":\"".$row['Loc']."\",\"ctrlSurface\"[";
		$stmt1="SELECT * FROM homer.ctrl_surf where Loc='".$row['Loc']."';";
		foreach(mysql_to_mysqli($stmt1, $link) as $row1) {
			//echo $row1['Data'];
			$result .= "{\"pid\": \"".$row1['PID']."\",\"type\": \"".$row1['Type']."\",\"Status\": \"".$row1['State']."\"},";
		}
		$result = rtrim($result, ",");
		$result .= "]},";
	}
	$result = rtrim($result, ",");
	//echo "<pre>";
	$result .= "]";
	echo $result;
	exit;
}

function getSettings($link) {
    $stmt="SELECT * FROM Settings LIMIT 1;";
    $result = "";
    foreach(mysql_to_mysqli($stmt, $link) as $row) {
    $result .= $row['Settings'];
    }
    echo $result;
    exit;
}

function updateSettings($link, $params) {
	$stmt = "UPDATE Settings SET Settings='".$params."' WHERE PID='1';";
	mysql_to_mysqli($stmt, $link);
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
	$result = "[";
	foreach(mysql_to_mysqli($stmt, $link) as $row) {
		if($row['enabled'] == 1) {
			$bool = "true";
		} else {
			$bool = "false";
		}
		//$result .= "{ID: '".$row['rid']."',Enabled: $bool,Title: '".$row['Title']."',Description: '".$row['Description']."'},";
		$result .= "{\"ID\": \"".$row['rid']."\",\"Enabled\": $bool,\"Title\": \"".$row['Title']."\",\"Description\": \"".$row['Description']."\"},";
	}
	$result = rtrim($result, ",");
	$result .= "]";
	echo $result;
	exit;
}

function eventLog($link) {
	$stmt="SELECT * FROM Event_Log order by Date desc LIMIT 100;";
	$result = "[";
	foreach(mysql_to_mysqli($stmt, $link) as $row) {
		$result .= "{\"Date\": \"".$row['Date']."\",\"Type\": \"".$row['Type']."\",\"Message\": \"".$row['Message']."\"},";
	}
	$result = rtrim($result, ",");
	$result .= "]";
	echo $result;
	exit;
}

function getData($link) {
	$stmt="SELECT * FROM Nodes where type='data';";
	$result = "[";
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
	$result .= "]";
	echo $result;
	exit;
}



?>