app.service('Service', ['$http', '$q', function ($http, $q) {
    var nodeData = {};
    var event = {};
    var rules = {};

    //EVENT LOG
    this.eventLog = function () {
        var deffered = $q.defer();
        var request = $http({
            url: 'src/backend/db.connect.php?type=eventLog',
            method: 'GET',
        });
        request.success(function (data) {
            event = data;
            deffered.resolve();
        });
        return deffered.promise;
    }

    this.getEventLog = function () {
        return event;
    }

    //NODE LOG
    this.getNodeData = function () {
        var deffered = $q.defer();
        var request = $http({
            url: 'src/backend/db.connect.php?type=nodeData',
            method: 'GET',
        });
        request.success(function (data) {
            nodeData = data;
            deffered.resolve();
        });
        return deffered.promise;
    }

    this.retrieveNodeData = function () {
        return nodeData;
    }

    //RULE LOG
    this.getRulesLog = function () {
        var deffered = $q.defer();
        var request = $http({
            url: 'src/backend/db.connect.php?type=rulesGet',
            method: 'GET',
        });
        request.success(function (data) {
            rules = data;
            deffered.resolve();
        });
        return deffered.promise;
    }

    this.getRules = function () {
        return rules;
    }

    //SET Rule Enabled
    this.setRulesEnabled = function (ID) {
        var request = $http({
            url: 'src/backend/db.connect.php?type=rulesSet&rid=' + ID.toString(),
            method:'GET',
        })
        request.success(function (data) {          
        });
    }
    //Set Settings
    this.setSettings = function (cool, heat, start, end) {
        alert('HERE')
        var request = $http({
            url: 'src/backend/db.connect.php?type=settings&cool=' + cool + '&heat=' + heat + '&start=' + start + '&end=' + end,
            method: 'GET',
        })
        request.success(function (data) {
        });
    };
}]);