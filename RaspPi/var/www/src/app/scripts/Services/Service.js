app.service('Service', ['$http', '$q', function ($http, $q) {
    var nodeData = {};
    var event = {};
    var rules = {};
    var settings = {};
    var surface = {};

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
    this.setSettings = function (cool, heat, start, end, timeout) {
        var request = $http({
            url: 'src/backend/db.connect.php?type=settings&cool=' + cool + '&heat=' + heat + '&start=' + start + '&end=' + end + '&timeout=' + timeout,
            method: 'GET',
        })
        request.success(function (data) {
        });
    };
    //get Settings
    this.settingsCall = function () {
        var deffered = $q.defer();
        var request = $http({
            url: 'src/backend/db.connect.php?type=getSettings',
            method: 'GET',
        })
        request.success(function (data) {
            settings = data;
            deffered.resolve();
        });
        return deffered.promise;
    }

    this.getSettings = function () {
        return settings;
    }

    //Get Control Surface from DB and sets to local variable
    this.surfaceCall = function () {
        var deffered = $q.defer();
        var request = $http({
            url: 'src/backend/db.connect.php?type=getSurface',
            method: 'GET',
        })
        request.success(function (data) {
            surface = data;
            deffered.resolve();
        });
        return deffered.promise;
    }

    //returns control surfaces
    this.getSurface = function () {
        return surface;
    }

    //Removes Control Surface
    this.removeSurface = function (pid) {
        var deffered = $q.defer();
        var request = $http({
            url: 'src/backend/db.connect.php?type=removeSurface&pid=' + pid,
            method: 'GET',
        })
        request.success(function (data) {
            deffered.resolve();
        });
        return deffered.promise;
    }

    //Adds a Control Surface
    this.addSurface = function (loc, type) {
        var deffered = $q.defer();
        var request = $http({
            url: 'src/backend/db.connect.php?type=addSurface&loc=' + loc + '&ctrlType=' + type,
            method: 'GET',
        })
        request.success(function (data) {
            deffered.resolve();
        });
        return deffered.promise;
    }

    //Edits Node information
    this.editNode = function (nid, enabled, loc) {
        var deffered = $q.defer();
        var request = $http({
            url: 'src/backend/db.connect.php?type=editNode&loc=' + loc + '&enabled=' + enabled + '&nid=' + nid,
            method: 'GET',
        })
        request.success(function (data) {
            deffered.resolve();
        });
        return deffered.promise;
    }

    //Removes a Node(Not Used)
    this.removeNode = function (nid) {
        var request = $http({
            url: 'src/backend/db.connect.php?type=removeNode' + '&nid=' + nid,
            method: 'GET',
        })
        request.success(function (data) {
        });
    }

    //Updates Control Surface data
    this.UpdateCtrlState = function (pid) {
        var request = $http({
            url: 'src/backend/db.connect.php?type=editSurface&pid=' + pid,
            method: 'GET',
        })
        request.success(function (data) {
        });
    }


}]);