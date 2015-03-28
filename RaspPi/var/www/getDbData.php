
<?php
                $link = mysql_connect('localhost', 'root', 'H0m3r');
                if (!$link) {
                    die('Could not connect: ' . mysql_error());
                }
                $selected = mysql_select_db("homer",$link)
                or die("Could not select database");
              
                $result = mysql_query("Select * from Rules");
                
                echo'<table class="table table-bordered" id="lists">
                          <tr class="active">
                            <td>
                              #
                            </td>
                            <td>
                              Command
                            </td>
                            <td>
                              Status
                            </td>
                          </tr>
                        ';
                
                while ($row = mysql_fetch_array($result)){                
                    echo "	<tr>
								<td>".$row[0]."</td>
								<td>".$row[3]."</td>
								<td><input id='$row[0]' onchange='UpdateDataBaseCheckBox(this)' type='checkbox'".(($row[2]== 1)?'checked':'')."/>
									<h6 style='display:inline-block'>Enabled</h6></td>
							</tr>";
                    //$txt = sprintf("%u:%s:%u",$row[0],$row[1],$row[2]);
                    //echo $txt,"<br>";
                };           
                echo "</table>";              
                mysql_close($link);
?>


 
