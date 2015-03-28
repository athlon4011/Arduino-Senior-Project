<? require("functions.php");
$stmt="SELECT rid,Title,Description,enabled FROM Rules;";
?>
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>jQuery UI Dialog - Modal form</title>
  <link rel="stylesheet" href="//code.jquery.com/ui/1.11.4/themes/smoothness/jquery-ui.css">
  <script src="//code.jquery.com/jquery-1.10.2.js"></script>
  <script src="//code.jquery.com/ui/1.11.4/jquery-ui.js"></script>
  <script src="/js/jquery.tabletojson.min.js"></script>
  <style>
    body { font-size: 62.5%; }
    label, input { display:block; }
    input.text { margin-bottom:12px; width:95%; padding: .4em; }
    fieldset { padding:0; border:0; margin-top:25px; }
    h1 { font-size: 1.2em; margin: .6em 0; }
    div#users-contain { width: 350px; margin: 20px 0; }
    div#users-contain table { margin: 1em 0; border-collapse: collapse; width: 100%; }
    div#users-contain table td, div#users-contain table th { border: 1px solid #eee; padding: .6em 10px; text-align: left; }
    .ui-dialog .ui-state-error { padding: .3em; }
    .validateTips { border: 1px solid transparent; padding: 0.3em; }
  </style>
  <script>
  $(function() {
    var dialog, form,
	//modifier = "<select id='modifier'><option>max</option><option>min</option><option>avg</option><option>sum</option><option>na</option></select>",
	//leftype = "<select id='leftype'><option>nodeall</option><option>nodeany</option><option>nodeexact</option><option>system</option></select>",
	//operand = "<select id='operand'><option>==</option><option>!=</option><option><</option><option><=</option><option>></option><option>>=</option></select>",
	//rightype = "<select id='rightype'><option>nodeall</option><option>nodeany</option><option>nodeexact</option><option>system</option><option>server</option><option>numbervalue</option></select>",
	//joiner = "<select id='joiner'><option value='||'>or</option><option value='&&'>and</option><option>na</option></select>", 
      // From http://www.whatwg.org/specs/web-apps/current-work/multipage/states-of-the-type-attribute.html#e-mail-state-%28type=email%29
      emailRegex = /^[a-zA-Z0-9.!#$%&'*+\/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/,
      name = $( "#name" ),
      email = $( "#email" ),
      password = $( "#password" ),
      allFields = $( [] ).add( name ).add( email ).add( password ),
      tips = $( ".validateTips" );
 
    function updateTips( t ) {
      tips
        .text( t )
        .addClass( "ui-state-highlight" );
      setTimeout(function() {
        tips.removeClass( "ui-state-highlight", 1500 );
      }, 500 );
    }
 
    function checkLength( o, n, min, max ) {
      if ( o.val().length > max || o.val().length < min ) {
        o.addClass( "ui-state-error" );
        updateTips( "Length of " + n + " must be between " +
          min + " and " + max + "." );
        return false;
      } else {
        return true;
      }
    }
 
    function checkRegexp( o, regexp, n ) {
      if ( !( regexp.test( o.val() ) ) ) {
        o.addClass( "ui-state-error" );
        updateTips( n );
        return false;
      } else {
        return true;
      }
    }
 
    function addUser() {
      var valid = true;
      allFields.removeClass( "ui-state-error" );
 
      valid = valid && checkLength( name, "username", 3, 16 );
      valid = valid && checkLength( email, "email", 6, 80 );
      valid = valid && checkLength( password, "password", 5, 16 );
 
      valid = valid && checkRegexp( name, /^[a-z]([0-9a-z_\s])+$/i, "Username may consist of a-z, 0-9, underscores, spaces and must begin with a letter." );
      valid = valid && checkRegexp( email, emailRegex, "eg. ui@jquery.com" );
      valid = valid && checkRegexp( password, /^([0-9a-zA-Z])+$/, "Password field only allow : a-z 0-9" );
 
      if ( valid ) {
        $( "#users tbody" ).append( "<tr>" +
          "<td>" + name.val() + "</td>" +
          "<td>" + email.val() + "</td>" +
          "<td>" + password.val() + "</td>" +
        "</tr>" );
        dialog.dialog( "close" );
      }
      return valid;
    }
	
	function selectConvert() {
		$( "#conditions select" ).each( function( key, value ) {
			$( this ).replaceWith( $(this).val() );
		});
		
		$( "#conditions input" ).each( function( key, value ) {
			$( this ).replaceWith( $(this).val() );
		});
		var table = $('#conditions').tableToJSON();
		console.log(table);
		alert(JSON.stringify(table)); 

	}
 
    dialog = $( "#dialog-form" ).dialog({
      autoOpen: false,
      height: 350,
      width: 450,
      modal: true,
      buttons: {
        "Submit": addUser,
		"Convert": selectConvert,
        Cancel: function() {
          dialog.dialog( "close" );
        }
      },
      close: function() {
        form[ 0 ].reset();
        allFields.removeClass( "ui-state-error" );
      }
    });
 
    form = dialog.find( "form" ).on( "submit", function( event ) {
      event.preventDefault();
      addUser();
    });
	
	function logArrayElements(element, index, array) {
		console.log('a[' + index + '] = ' + element.leftvar);
		var modifier = "<select class='text ui-widget-content ui-corner-all' id='modifier"+index+"'><option>max</option><option>min</option><option>avg</option><option>sum</option><option>na</option></select>";
		var leftype = "<select class='text ui-widget-content ui-corner-all' id='leftype"+index+"'><option>nodeall</option><option>nodeany</option><option>nodeexact</option><option>system</option><option>server</option></select>";
		var leftvar = "<select class='text ui-widget-content ui-corner-all' id='leftvar"+index+"'><option>lux</option><option>motion</option><option>temp</option><option>smoke</option><option>systemvar</option></select>";
		var operand = "<select class='text ui-widget-content ui-corner-all' id='operand"+index+"'><option>==</option><option>!=</option><option><</option><option><=</option><option>></option><option>>=</option></select>";
		if(element.rightype == "numbervalue") {
			var rightvar = "<input type='text' id='rightvar"+index+"' class='text ui-widget-content ui-corner-all'>";
		} else {
			var rightvar = element.rightvar;
		}
		var rightype = "<select class='text ui-widget-content ui-corner-all' id='rightype"+index+"'><option>nodeall</option><option>nodeany</option><option>nodeexact</option><option>system</option><option>server</option><option>numbervalue</option></select>";
		var joiner = "<select class='text ui-widget-content ui-corner-all' id='joiner"+index+"'><option value='||'>or</option><option value='&&'>and</option><option>na</option></select>";
		$( '#conditions' ).append( '<tr><td>'+modifier+'</td><td>'+leftype+'</td><td>'+leftvar+'</td><td>'+operand+'</td><td>'+rightype+'</td><td>'+rightvar+'</td><td>'+joiner+'</td></tr>' );
		//alert($( '#leftype' ).length);
		$( '#modifier'+index ).val(element.modifier);
		$( '#leftype'+index ).val(element.leftype);
		$( '#leftvar'+index ).val(element.leftvar);
		$( '#operand'+index ).val(element.operand);
		$( '#rightype'+index ).val(element.rightype);
		$( '#rightvar'+index ).val(element.rightvar);
		$( '#joiner'+index ).val(element.joiner);
	}

	<?
	foreach(mysql_to_mysqli($stmt, $link) as $row) {
	//print_r($row);
	echo "$( \"#".$row['rid']."e\" ).button().on( \"click\", function() {
      dialog.dialog( \"open\" );
	  $.post( 'dataPull.php', {type: 'single',query: 'select',rid: '".$row['rid']."'}, function( data ) {
		  $('#Title').val( data.Title );
		  $('#Description').val( data.Description );
		  $('#Data').val( data.Data );
		  var testData = jQuery.parseJSON(data.Data);
		  //$('#Data').val( testData.if.condition[0].modifier );
		  //console.log(testData.if.condition[0]);
		  
		  $('#conditions').empty().append('<thead><th>modifier</th><th>leftype</th><th>leftvar</th><th>operand</th><th>rightype</th><th>rightvar</th><th>joiner</th></thead>');
		  //$( '#conditions' ).append( '<tr><td>'+testData.if.condition[0].modifier+'</td><td>World</td></tr>' );
		  testData.if.condition.forEach(logArrayElements);
		  
		}, 'json');
    });";
}
	?>
  });
  </script>
</head>
<body>
<div id="dialog-form" title="Create new user">
  <p class="validateTips">All form fields are required.</p>
 
  <form>
    <fieldset>
      <label for="Title">Title</label>
      <input type="text" name="Title" id="Title" value="" class="text ui-widget-content ui-corner-all">
      <label for="Description">Description</label>
      <input type="text" name="Description" id="Description" value="" class="text ui-widget-content ui-corner-all">
      <label for="Data">IF</label>
	  <table id='test'><thead><th>condition</th></thead><tr>
	  <table id="conditions" border="1"></table>
 
      <!-- Allow form submission with keyboard without duplicating the dialog button -->
      <input type="submit" tabindex="-1" style="position:absolute; top:-1000px">
    </fieldset>
  </form>
</div>
<?




echo'<table class="table table-bordered" id="lists" border=1>
                          <tr class="active">
                            <td>
                              #
                            </td>
                            <td>
                              Name
                            </td>
                            <td>
                              Description
                            </td>
							<td>
                              Enabled
                            </td>
							<td>
                              Edit
                            </td>
                          </tr>
                        ';
						

$rslt=mysql_to_mysqli($stmt, $link);
$number_of_logs = mysqli_num_rows($rslt);
echo "Row count: ".$number_of_logs;
echo "<script>";
//print "<PRE>";
echo "$( \"#create-user\" ).button().on( \"click\", function() {
      //dialog.dialog( \"open\" );
	  alert('test');
    });";


echo "</script>";
$i=0;
while ($i < $number_of_logs)
	{

	$row=mysqli_fetch_row($rslt);
	
	echo "<tr>";
	echo "<td>$row[0]</td>";
	echo "<td>$row[1]</td>";
	echo "<td>$row[2]</td>";
	echo "<td><input id='$row[0]' class='ui-button ui-widget-content ui-corner-all' onchange='UpdateDataBaseCheckBox(this)' type='checkbox'".(($row[3]== 1)?'checked':'')."/>
									</td>";
	echo "<td><button id='$row[0]e'>Edit</button></td>";
	echo "</tr>";
	$i++;
	}



echo '</table>';

?>

</body>
</html>