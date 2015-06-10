app.controller('RulesController', ['$scope', 'dateFilter', '$interval','Service', function ($scope, dateFilter, $interval,Service) {

    $scope.formEnable = true;
    $scope.degree = '\xB0' + 'F';
    $scope.start = "00:00";
    $scope.end = "00:00";
    document.getElementById('restrictedStartTime').value = TimeCounter(0);
    document.getElementById('restrictedEndTime').value = TimeCounter(0);

    Service.getRulesLog().then(function () {
        $scope.items = Service.getRules();
    });

    //Service.settingsCall().then(function(){
    //    $scope.CtrlFormData = Service.getSettings();
    //    alert(JSON.stringify($scope.CtrlFormData));
    //});

    //Edit Button
    $scope.EditButton = function () {
        $scope.formEnable = false;
    }

    //Cancel Button
    $scope.CancelButton = function () {
        $scope.formEnable = true;
    }

    //Formats the Time's to hh:mm:ss a
    $scope.$watch('start', function (value) {
        time = dateFilter(value, 'HH:mm:a');
        test = time.split(":");
        HoursTOSeconds = parseInt(test[0]) * 3600;
        MinutesToSeconds = parseInt(test[1]) * 60;
        epoch = HoursTOSeconds + MinutesToSeconds;
        $scope.CtrlFormData['start'] =  epoch;
 
    });
    $scope.$watch('end', function (value) {
        time = dateFilter(value, 'HH:mm:a');
        test = time.split(":");
        HoursTOSeconds = parseInt(test[0]) * 3600;
        MinutesToSeconds = parseInt(test[1]) * 60;
        epoch = HoursTOSeconds + MinutesToSeconds;
        $scope.CtrlFormData['end'] = epoch;
    });

    //Object Data for form
    $scope.CtrlFormData = {
        cool: 75,
        heat: 95,
        start: '' ,
        end: '',
    };

    //Converts Seconds to HH:mm
    function TimeCounter(value) {
        var t = parseInt(value);
        var hours = parseInt(t / 3600);
        t = t - (hours * 3600);
        var minutes = parseInt(t / 60);
        t = t - (minutes * 60);
        var content = "";
        if (hours) {
            if (content) content += ", "; content += hours;
        }
        if (content)
            content += ":";
        if (minutes < 10) {
            minutes = '0' + minutes;
        }
        content += minutes; return content;
    }



    //Will send submitted Desired Temp information to SQL Server
    $scope.submitCtrlForm = function () {
        if ($scope.CtrlForm.$valid) {
            //Convert Object to String
            cool = $scope.CtrlFormData.cool.toString();
            heat = $scope.CtrlFormData.heat.toString();
            start = $scope.CtrlFormData.start.toString();
            endtime = $scope.CtrlFormData.end.toString();
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