var app = angular.module('app', ['ui.bootstrap', 'ngRoute', 'ng',]);

app.config(function ($routeProvider) {
    $routeProvider
        .when('/Home',
            {
                templateUrl: 'src/app/templates/mainPage.html',
                controller: 'mainPageController'
            }
        )
        .when('/Rules',
            {
                templateUrl: 'src/app/templates/Rules.html',
                controller: 'RulesController'
            }
        )
         .when('/SimHouse',
            {
                templateUrl: 'src/app/templates/SimHouse.html',
                controller: 'SimHouseController'
            }
        )
        .otherwise({
            redirectTo: '/Home'
        });

});

