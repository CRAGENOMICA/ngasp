var CRAG = angular.module('CRAG', [ 'ui.router',
                                    'ui.bootstrap',
                                    'ngAnimate'
                                  ]);

CRAG.config( ['$stateProvider', '$urlRouterProvider',
    function ( $stateProvider,   $urlRouterProvider) {

	$urlRouterProvider.when('/' , '/index.html');

	$stateProvider
    .state("downloads",   { url: '/downloads',    views: { 'main' : { templateUrl: "partials/downloads.html",     controller: "MainController"}}})
    .state("examples",    { url: '/examples',     views: { 'main' : { templateUrl: "partials/examples.html",      controller: "MainController"}}})
    .state("home",        { url: '/home',         views: { 'main' : { templateUrl: "partials/home.html",          controller: "MainController"}}})
    .state("how_to_use",  { url: '/how_to_use',   views: { 'main' : { templateUrl: "partials/how_to_use.html",    controller: "MainController"}}})
    .state("commands",    { url: '/commands',     views: { 'main' : { templateUrl: "partials/commands.html",      controller: "MainController"}}})
    .state("calculations",{ url: '/calculations', views: { 'main' : { templateUrl: "partials/calculations.html",  controller: "MainController"}}})
    .state("mstatspop",   { url: '/mstatspop',    views: { 'main' : { templateUrl: "partials/mstatspop.html",     controller: "MainController"}}})
    .state("pipeline",    { url: '/pipeline',     views: { 'main' : { templateUrl: "partials/pipeline.html",      controller: "MainController"}}})
    .state("project",     { url: '/project',      views: { 'main' : { templateUrl: "partials/project.html",       controller: "MainController"}}})
    .state("team",        { url: '/team',         views: { 'main' : { templateUrl: "partials/team.html",          controller: "MainController"}}})
    .state("captures",    { url: '/captures',     views: { 'main' : { templateUrl: "partials/captures.html",      controller: "MainController"}}})
  ;
}]);

CRAG.run(['$rootScope', '$state', function ($rootScope, $state) { 
  $state.go('home');
}]);

