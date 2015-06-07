<?php
$link = mysqli_connect('localhost', 'root', 'H0m3r', 'homer', '3306');


function getEventLog (){
  $link = mysql_connect('localhost', 'root', 'H0m3r');
                if (!$link) {
                    die('Could not connect: ' . mysql_error());
                }
                $selected = mysql_select_db("homer",$link)
                or die("Could not select database");
              
                $result = mysql_query("Select * from Rules");
}

?>
