app.controller('SimHouseController', ['$scope','Service', function ($scope, Service) {

    $scope.enabled = true;

    $scope.toggleEnable = function () {
        $scope.enabled = false;
    }

    Service.surfaceCall().then(function () {
        $scope.items = Service.getSurface();
    });

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
