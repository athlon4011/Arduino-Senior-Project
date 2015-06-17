app.controller('ControlSurfaceController', ['$scope', 'Service','$interval', function ($scope, Service, $interval) {

    $scope.select = {};
    $scope.CtrlState;

    //Add Hide Elements
    $scope.addElements = function () {
        for (var i = 0; i < $scope.items.length; i++) {
            $scope.items[i]['hide'] = true;
            $scope.items[i]['addHide'] = true;
            for (var k = 0; k < $scope.items[i].ctrlSurface.length; k++) {
                if ($scope.items[i].ctrlSurface[k].Status == 'on')
                    $scope.items[i].ctrlSurface[k]['ctrlState'] = true;
                else {
                    $scope.items[i].ctrlSurface[k]['ctrlState'] = false;
                }
            }
        }
    }

    //Calls Service Function to retrieve Ctrl Surface Data
    Service.surfaceCall().then(function () {
        $scope.items = Service.getSurface();
        $scope.addElements();
    });


    //Toggle hiding of edit Node form
    $scope.toggleEnable = function (idx) {
        if($scope.items[idx].hide == true){
            $scope.items[idx].hide = false;
        }
        else {
            $scope.items[idx].hide = true;
        }
    }
    //Toggle Add Surface Form
    $scope.toggleAddEnable = function (idx) {
        if ($scope.items[idx].addHide == true) {
            $scope.items[idx].addHide = false;
        }
        else {
            $scope.items[idx].addHide = true;
        }
    }

    //submitting edit node form
    $scope.submitNodeForm = function (idx) {
        var node = $scope.items[idx];
        var enabled
        if (node.enabled == true)
            enabled = 1;
        else
            enabled = 0;
        Service.editNode(node.nodeID, enabled, node.nodeLocation).then(function () {
            Service.surfaceCall().then(function () {
                $scope.items = Service.getSurface();
                $scope.addElements();
            });
        })
    }

    //Continously Get Surface information every 3 seconds if edit or add control surface is not true;
    $interval(function () {
            //Getting CTRL surface information
        Service.surfaceCall().then(function () {
            var object = Service.getSurface();
            for (var i = 0; i < $scope.items.length; i++) {
                for (var k = 0; k < $scope.items[i].ctrlSurface.length; k++) {
                    $scope.items[i].ctrlSurface[k] = object[i].ctrlSurface[k];
                    if ($scope.items[i].ctrlSurface[k].Status == 'on')
                        $scope.items[i].ctrlSurface[k]['ctrlState'] = true;
                    else {
                        $scope.items[i].ctrlSurface[k]['ctrlState'] = false;
                    }
                }
            }
        });
    }, 1000)

    //Add Ctrl Surface
    $scope.add = function (idx) {
        //Selected Surface Type
        type = $scope.select[idx].label
        //Location
        loc = $scope.items[idx].nodeLocation;
        //Add Surface
        Service.addSurface(loc, type).then(function () {
            //Getting CTRL surface information
            Service.surfaceCall().then(function () {
                $scope.items = Service.getSurface();
                $scope.addElements();
            });
        })
    }

    //Remove Ctrl Surface
    $scope.remove = function (pIdx, cIdx) {
        //pid for selected control surface to remove.
        pid = $scope.items[pIdx].ctrlSurface[cIdx].pid;
        Service.removeSurface(pid).then(function () {
            //Getting CTRL surface information
            Service.surfaceCall().then(function () {
                $scope.items = Service.getSurface();
                $scope.addElements();
            });
        })
    }

    //Updates the state of the Control Surface, Power ON/Power OFF
    $scope.UpdateState = function (pIdx, cIdx) {
        pid = $scope.items[pIdx].ctrlSurface[cIdx].pid;

        Service.UpdateCtrlState(pid).then(function () {
            if ($scope.items[pid].ctrlSurface[cIdx].State == 'on')
                $scope.items[pIdx].ctrlSurface[cIdx]['ctrlState'] = true;
            else {
                $scope.items[pIdx].ctrlSurface[cIdx]['ctrlState'] = false;
            }
        })
    }

    //Used to populate add control surface dropdown
    $scope.ctrlSurfaces = [
        {
            value: "Light",
            label: "Light"
        },
        {
            value: "Fan",
            label: "Fan",
        }
    ]

}]);
