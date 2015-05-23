var app = angular.module('app', ['ngRoute','ng']);

app.config(function ($routeProvider) {
    $routeProvider
        .when('#/Home',
            {
                templateUrl: 'src/app/templates/mainPage.html',
                controller: 'mainPageController'
            }
        )
        .when('#/Rules',
            {
                templateUrl: 'src/app/templates/Rules.html',
                controller: 'RulesController'
            }
        )
        .otherwise({
            redirectTo: '#/Home'
        });

});

