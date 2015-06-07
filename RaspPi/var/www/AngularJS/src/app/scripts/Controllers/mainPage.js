﻿app.controller('mainPageController', ['$scope','Service', function ($scope, Service) {

    $scope.message = 'MainPage';

    //To grab EventLog JSON
    //$scope.items = Service.getEventLog();


    //Example JSON Objects
    $scope.items = [
        {
            Date: '06/01/2015',
            Type: 'System',
            Message: "NODE 1 Sent data",
        },
        {
            Date: '06/01/2015',
            Type: 'Alert',
            Message: "High Gas Levels",
        },

    ];
    //Example JSON Objects
    $scope.Nodes = [
        {
            "NodeID": 0,
            "node": [
                {
                    "Date": '06/06/2015',
                    "Data": { "lux": "1", "motion": "0", "temp": "70.62" },
                },
                 {
                     "Date": '06/06/2015',
                     "Data": { "lux": "0", "motion": "0", "temp": "60.62" },
                 }
            ]
        },
       {
           "NodeID": 1,
           "node": [
               {
                   "Date": '06/06/2015',
                   "Data": { "lux": "0", "motion": "0", "temp": "80.62" },
               },
                {
                    "Date": '06/06/2015',
                    "Data": { "lux": "0", "motion": "1", "temp": "90.62" },
                },

           ]
       },
       {
           "NodeID": 2,
           "node": [
               {
                   "Date": '06/06/2015',
                   "Data": { "lux": "0", "motion": "0", "temp": "80.62" },
               },
                {
                    "Date": '06/06/2015',
                    "Data": { "lux": "0", "motion": "1", "temp": "90.62" },
                },

           ]
       },

    ];

}]);