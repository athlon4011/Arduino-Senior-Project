
<!DOCTYPE html>
<html lang="en">
<head>
    <title>DisplayPage</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" href="/css/bootstrap.css">
    <link rel="stylesheet" type="text/css" href="/css/DisplayCSS.css">
	<link rel="stylesheet" type="text/css" href="/css/jquery-ui.css">
	<link rel='stylesheet' href='/js/tablesorter/themes/blue/style.css' type='text/css' media='print, projection, screen' />

    <script type='text/javascript' src="/js/jquery-1.11.2.min.js"></script>
	<script type='text/javascript' src="/js/jquery-ui.min.js"></script>
    <script type='text/javascript' src="/js/bootstrap.js"></script>
	<script type='text/javascript' src='/js/tablesorter/jquery.tablesorter.js'></script> 

    <script>
		$(document).ready(function() 
				{ 
					$('#lists').tablesorter({widthFixed: true, widgets: ['zebra']});
					//$('#lists').tablesorterPager({container: $('#pager')}); 
				} 
			); 
        window.setInterval(function () {
            xmlRequest("getDbData.php");
        }, 3000);

        function xmlRequest(url) {
            if (window.XMLHttpRequest) {
                xmlhttp = new XMLHttpRequest();
            }
            else {
                xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
            }
            xmlhttp.onreadystatechange = function () {
                if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
                    document.getElementById("Rules").innerHTML = xmlhttp.responseText;
                }
            }
            xmlhttp.open("POST", url, true);
            xmlhttp.send();
        }

        function xmlUpdateRequest(url) {
            if (window.XMLHttpRequest) {
                xmlhttp = new XMLHttpRequest();
            } else {
                xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
            }
            xmlhttp.open("POST", url, true);
            xmlhttp.send();
        }
    </script>
</head>
<body>
    <div class="container-fluid background">
        <? include "header.php";?>
        <div class="container bottomPanel">
            <strong>Time: </strong><small id="time">8:00 A.M</small>
            <strong style="margin-left:10%">Date: </strong><small id="date">01/25/2015</small>
        </div>

        <!-- Tab panes -->
        <div class="tab-content HomePage">
            <div class="tab-pane fade in active" id="Home">TESTING</div>
            <div class="tab-pane fade" id="Rules">

            </div>
            <div class="tab-pane fade" id="House"><iframe class="iframeSimHouse" scrolling="no" src="SimulatedHouse.html"></iframe></div>
        </div>
        <div class="console"></div>
    </div>
    <script>

        $('#myTab a').click(function (e) {
            e.preventDefault()
            $(this).tab('show')
        });

        // store the currently selected tab in the hash value
        $("ul.nav-tabs > li > a").on("shown.bs.tab", function (e) {
            var id = $(e.target).attr("href").substr(1);
            window.location.hash = id;
        });

        // on load of the page: switch to the currently selected tab
        var hash = window.location.hash;
        $('#myTab a[href="' + hash + '"]').tab('show');

        //Update Time on Webpage
        function UpdateTime() {
            var curdate = new Date();
            var date = ((curdate.getMonth() + 1 < 10) ? "0" : "") + (curdate.getMonth() + 1) + '/' + ((curdate.getDate() < 10) ? "0" : "") + curdate.getDate() + '/' + curdate.getFullYear();
            var time = ((curdate.getHours() < 10) ? "0" : "") + ((curdate.getHours() > 12) ? (curdate.getHours() - 12) : curdate.getHours()) + ":" + ((curdate.getMinutes() < 10) ? "0" : "") + curdate.getMinutes() + '      ' + ((curdate.getHours() > 12) ? ('PM') : 'AM');
            document.getElementById("date").innerHTML = date;
            document.getElementById("time").innerHTML = time;
            setTimeout(UpdateTime, 1000);
        }
        UpdateTime();

        function UpdateDataBaseCheckBox(element) {
            var id = element.id;
            var status = element.checked;
            if (status == true) {
                status = 1;
            }
            var url = "UpdateDb.php?status=" + status + "&id=" + id;
            xmlUpdateRequest(url);
        }
    </script>

</body>
</html>
