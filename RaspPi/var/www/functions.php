<?

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



?>