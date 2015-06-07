app.controller('RulesController', ['$scope', function ($scope) {

    $scope.formEnable = true;
    $scope.degree = '\xB0' + 'F';

    //Edit Button
    $scope.EditButton = function () {
        $scope.formEnable = false;
    }

    //Cancel Button
    $scope.CancelButton = function () {
        $scope.formEnable = true;
    }

    //Will send submitted Desired Temp information to SQL Server
    $scope.submitTempForm = function () {
        if ($scope.TempForm.$valid) {
            //Send the Temp information to Server
        }
    }


    //Example JSON Objects
    $scope.items = [
        {
            ID: 0,
            Date: '06/01/2015',
            Type: 'System',
            Message: "NODE 1 Sent data",
            Enabled: true,
            Title: 'AC',
            Description: "Turn on AC"
        },
        {
            ID: 1,
            Date: '06/01/2015',
            Type: 'Alert',
            Message: "High Gas Levels sdasdasd asdas dasd as dasdasdadadadasdasdasd",
            Enabled: false,
            Title: 'Heater',
            Description: "Turn on Heater"
        },

    ];

    //Testing of enable// Soon will send status back to SQL server
    $scope.Test = function (ID,status) {
        alert('ID: ' + ID.toString() + ' Status: ' + status);
    }

}]);