app.controller('RulesController', ['$scope', 'dateFilter', '$interval','Service', function ($scope, dateFilter, $interval,Service) {

    $scope.formEnable = true;
    $scope.degree = '\xB0' + 'F';
    Service.getRulesLog().then(function () {
        $scope.items = Service.getRules();
    });


    //Edit Button
    $scope.EditButton = function () {
        $scope.formEnable = false;
    }

    //Cancel Button
    $scope.CancelButton = function () {
        $scope.formEnable = true;
    }

    //Formats the Time's to hh:mm:ss a
    $scope.$watch('restrictedStartTime', function (value) {
        time = dateFilter(value, 'HH:mm:a');
        test = time.split(":");
        HoursTOSeconds = parseInt(test[0]) * 3600;
        MinutesToSeconds = parseInt(test[1]) * 60;
        epoch = HoursTOSeconds + MinutesToSeconds;
        $scope.CtrlFormData.restrictedStartTime =  epoch;
 
    });
    $scope.$watch('restrictedEndTime', function (value) {
        time = dateFilter(value, 'HH:mm:a');
        test = time.split(":");
        HoursTOSeconds = parseInt(test[0]) * 3600;
        MinutesToSeconds = parseInt(test[1]) * 60;
        epoch = HoursTOSeconds + MinutesToSeconds;
        $scope.CtrlFormData.restrictedEndTime = epoch;
    });

    //Object Data for form
    $scope.CtrlFormData = {
        LowTemp: 75,
        HighTemp: 95,
        restrictedStartTime: '' ,
        restrictedEndTime:'',
    }




    //Will send submitted Desired Temp information to SQL Server
    $scope.submitCtrlForm = function () {
        if ($scope.CtrlForm.$valid) {
            //Convert Object to String
            $scope.cool = $scope.CtrlFormData.LowTemp.toString();
            $scope.heat = $scope.CtrlFormData.HighTemp.toString();
            $scope.start = $scope.CtrlFormData.restrictedStartTime.toString();
            $scope.endtime = $scope.CtrlFormData.restrictedEndTime.toString();
            //Send variables to php
            Service.setSettings(cool, heat, start, endtime);
            $scope.formEnable = true;
        }
    }

    //Example JSON Objects
    //$scope.items = [
    //    {
    //        ID: 0,
    //        Enabled: true,
    //        Title: 'AC',
    //        Description: "Turn on AC"
    //    },
    //    {
    //        ID: 1,
    //        Enabled: false,
    //        Title: 'Heater',
    //        Description: "Turn on Heater"
    //    },

    //];

    //Testing of enable// Soon will send status back to SQL server
    $scope.Test = function (ID) {
        Service.setRulesEnabled(ID);
    }

}]);