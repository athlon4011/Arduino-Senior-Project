app.controller('mainPageController', ['$scope', 'Service', '$interval', function ($scope, Service, $interval) {
    Service.getNodeData().then(function () {
        $scope.Nodes = Service.retrieveNodeData();
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
            $scope.Nodes = Service.retrieveNodeData();
        });
    }, 10000);

    //Example JSON Objects
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
    ////Example JSON Objects
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