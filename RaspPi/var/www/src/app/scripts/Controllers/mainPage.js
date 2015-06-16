app.controller('mainPageController', ['$scope', 'Service', '$interval', function ($scope, Service, $interval) {
    $scope.Toggle = true;

    Service.getNodeData().then(function () {
        $scope.Nodes = Service.retrieveNodeData();
        //Add true false for displaying header
        for (var i = 0; i < $scope.Nodes.length; i++) {
            if (i == 0)
            {
                $scope.Nodes[i].hide = false;
            }
            else
            {
                $scope.Nodes[i].hide = true;
            }
        }
    });
    //To grab EventLog JSON
    Service.eventLog().then(function () {
        $scope.items = Service.getEventLog();
    });

    $interval(function () {
        //To grab EventLog JSON
        Service.eventLog().then(function () {
            $scope.items = Service.getEventLog();
        });
        //To grab NodeLog JSON
        Service.getNodeData().then(function () {
            var object = Service.retrieveNodeData();
            for (var i = 0; i < $scope.Nodes.length; i++) {
                for (var k = 0; k < $scope.Nodes[i].node.length; k++) {
                    $scope.Nodes[i].node[k] = object[i].node[k];
                }
            }
        });
    }, 3000);

    //Toggle EventLog System events
    $scope.EventToggle = function () {
        if ($scope.Toggle == true) {
            $scope.Toggle = false;
            $scope.selectedGenres = ['Alert', 'Rule'];
            $scope.filterByGenres = function (item) {
                return ($scope.selectedGenres.indexOf(item.Type) !== -1);
            };
        }
        else {
            $scope.filterByGenres = function (item) {
                $scope.Toggle = true;
                $scope.selectedGenres = ['Alert', 'Rule','Error','System'];
                return ($scope.selectedGenres.indexOf(item.Type) !== -1);
            };
        }

    }

    //Toggle AccordionHeader
    $scope.AccordionHeader = function (idx) {
            if ($scope.Nodes[idx].hide == true) {
                $scope.Nodes[idx].hide = false;
            }
            else{
                $scope.Nodes[idx].hide = true;
            }
        }

    ////Example JSON Objects
    //$scope.items = [
    //    {
    //        Date: '06/01/2015',
    //        Type: 'System',
    //        Message: "NODE 1 Sent data",
    //    },
    //    {
    //        Date: '06/01/2015',
    //        Type: 'Alert',
    //        Message: "High Gas Levels",
    //    },

    //];
    //Example JSON Objects
    //$scope.Nodes = [
    //    {
    //        "NodeID": 0,
    //        "node": [
    //            {
    //                "Date": '06/06/2015',
    //                "lux": "1", 
    //                "motion": "0", 
    //                "temp": "70.62",
    //            },
    //             {
    //                 "Date": '06/06/2015',
    //                 "lux": "0",
    //                 "motion": "0",
    //                 "temp": "60.62",
    //             }
    //        ]
    //    },
    //   {
    //       "NodeID": 1,
    //       "node": [
    //           {
    //               "Date": '06/06/2015',
    //               "lux": "0", "motion": "0", "temp": "80.62" ,
    //           },
    //            {
    //                "Date": '06/06/2015',
    //               "lux": "0", "motion": "1", "temp": "90.62" ,
    //            },

    //       ]
    //   },
    //   {
    //       "NodeID": 2,
    //       "node": [
    //           {
    //               "Date": '06/06/2015',
    //                "lux": "0", "motion": "0", "temp": "80.62" ,
    //           },
    //            {
    //                "Date": '06/06/2015',
    //                "lux": "0", "motion": "1", "temp": "90.62" ,
    //            },

    //       ]
    //   },

    //];

}]);