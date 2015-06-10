app.controller('SimHouseController', ['$scope', function ($scope, $model) {

    $scope.enabled = true;

    $scope.items = [
        {
            nodeID: '1',
            nodeLocation: 'Room1',
            ctrlSurface: [
                {
                    type: 'Light',
                    Location: 'Room1',
                    Status: 'On',
                },
                {
                    type: 'Fan',
                    Location: 'Room1',
                    Status: 'On',
                },
                {
                    type: 'HVAC',
                    Location: 'Room1',
                    Status: 'On',
                },
            ]
        },
         {
             nodeID: '2',
             nodeLocation: 'Room2',
             ctrlSurface: [
                 {
                     type: 'Light',
                     Location: 'Room2',
                     Status: 'On',
                 },
                 {
                     type: 'Fan',
                     Location: 'Room2',
                     Status: 'On',
                 },
                 {
                     type: 'Light',
                     Location: 'Room2',
                     Status: 'On',
                 },
             ]
         },
         {
             nodeID: '3',
             nodeLocation: 'Room3',
             ctrlSurface: [
                 {
                     type: 'Light',
                     Location: 'Room3',
                     Status: 'On',
                 },
                 {
                     type: 'Fan',
                     Location: 'Room3',
                     Status: 'On',
                 },
                 {
                     type: 'Light',
                     Location: 'Room3',
                     Status: 'On',
                 },
             ]
         },
         {
             nodeID: '4',
             nodeLocation: 'Room4',
             ctrlSurface: [
                 {
                     type: 'Light',
                     Location: 'Room4',
                     Status: 'On',
                 },
                 {
                     type: 'Fan',
                     Location: 'Room4',
                     Status: 'On',
                 },
                 {
                     type: 'Light',
                     Location: 'Room4',
                     Status: 'On',
                 },
             ]
         }
    ]


}]);
