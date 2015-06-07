app.service('Service', ['$http', function ($http) {
    
    this.getEventLog = function () {
        var request = $http({
            method: 'get',
            url: 'src/app/php.php.getEventLog',
        });

        return request.success(function (data) { alert(data); return data; });
    }
}]);