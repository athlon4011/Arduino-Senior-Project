

<?php
	$id = $_GET["id"];
	$status = $_GET["status"];
	$link = mysqli_connect('localhost', 'root', 'H0m3r', 'test');
    if (!$link) {
        die('Could not connect: ' . mysql_error());
    }             
    $sql = "UPDATE testRules
            SET status = '$status'
            WHERE ID = '$id'";
    
    mysqli_query($link, $sql);

    mysqli_close($link);

?>