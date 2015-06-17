var app = angular.module('app', ["ui.bootstrap","ui.bootstrap.tpls", 'ngRoute', 'ng',]);

//Routing
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
         .when('/CtrlSurface',
            {
                templateUrl: 'src/app/templates/CtrlSurface.html',
                controller: 'ControlSurfaceController'
            }
        )
        .otherwise({
            redirectTo: '/Home'
        });

});

