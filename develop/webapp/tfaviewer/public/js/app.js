var CRAG = angular.module('CRAG', [ 'ui.router',
                                    'ui.bootstrap',
                                    'rzModule',
                                    'ngProgress',
                                    'ngRoute'
                                  ]);

CRAG.config( ['$stateProvider', '$urlRouterProvider',
    function ( $stateProvider,   $urlRouterProvider) {
        $urlRouterProvider.when('/' , '/index.html');
        $stateProvider.state("viewer", { url: '/viewer', views: { 'main' : { templateUrl: "partials/viewer.html", controller: "ViewerController"}}});
        $urlRouterProvider.when('/load/:tfa/:stats/:gff/:weight', ['$match', '$stateParams', '$state', '$rootScope', function ($match, $stateParams, $state, $rootScope) {
            // Example: http://localhost:3001/#/load/slashdevelopslashexamplesslashAdaptNet_Variabilityslashoutput.tfa.gz/slashdevelopslashexamplesslashAdaptNet_Variabilityslashstatistics.txt/slashdevelopslashexamplesslashAdaptNet_Variabilityslashdata_annotation.gtf/slashdevelopslashexamplesslashAdaptNet_Variabilityslashpesos.txt
            $rootScope.tfa    = $match.tfa.replace(/slash/g, "/");
            $rootScope.stats  = $match.stats.replace(/slash/g, "/");
            $rootScope.gff    = $match.gff.replace(/slash/g, "/");
            $rootScope.weight = $match.weight.replace(/slash/g, "/");
            $state.go('viewer');
            //$state.transitionTo("viewer", $match, false);
        }]);
    }
]);

CRAG.run(['$rootScope', '$state',
    function ($rootScope, $state) { 
        $state.go('viewer');
    }
]);

