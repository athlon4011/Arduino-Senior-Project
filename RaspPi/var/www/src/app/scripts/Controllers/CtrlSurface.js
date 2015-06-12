app.controller('ControlSurfaceController', ['$scope', 'Service', function ($scope, Service) {

    $scope.select = {};

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
        //$scope.items[idx].hide = true;

    }

    //Getting CTRL surface information
    Service.surfaceCall().then(function () {
        $scope.items = Service.getSurface();
        $scope.addElements();
    });

    //Add Hide Elements
    $scope.addElements = function () {
        for (var i = 0; i < $scope.items.length; i++) {
            $scope.items[i]['hide'] = true;
            $scope.items[i]['addHide'] = true;
        }
    }

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

    //if (confirm("Press a button!") == true) {
    //    x = "You pressed OK!";
    //} else {
    //    x = "You pressed Cancel!";
    //}


    //$scope.items = [
    //    {
    //        nodeID: '1',
    //        nodeLocation: 'Room1',
    //        ctrlSurface: [
    //            {
    //                type: 'Light',
    //                Status: 'On',
    //            },
    //            {
    //                type: 'Fan',
    //                Status: 'On',
    //            },
    //        ]
    //    },
    //     {
    //         nodeID: '2',
    //         nodeLocation: 'Room2',
    //         ctrlSurface: [
    //             {
    //                 type: 'Light',
    //                 Status: 'On',
    //             },
    //             {
    //                 type: 'Fan',
    //                 Status: 'On',
    //             },
    //         ]
    //     },
    //     {
    //         nodeID: '3',
    //         nodeLocation: 'Room3',
    //         ctrlSurface: [
    //             {
    //                 type: 'Light',
    //                 Status: 'On',
    //             },
    //             {
    //                 type: 'Fan',
    //                 Status: 'On',
    //             },
    //         ]
    //     },
    //     {
    //         nodeID: '4',
    //         nodeLocation: 'Room4',
    //         ctrlSurface: [
    //             {
    //                 type: 'Light',
    //                 Location: 'Room4',
    //                 Status: 'On',
    //             },
    //             {
    //                 type: 'Fan',
    //                 Location: 'Room4',
    //                 Status: 'On',
    //             },
    //         ]
    //     }
    //]


}]);
