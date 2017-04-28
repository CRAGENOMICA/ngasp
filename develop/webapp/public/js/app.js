/*
 * ngasp, a computational solution for performing next generation analysis of 
 * sequence polymorphisms using NGS data.
 * Copyright (c) 2015-2016, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
 * Centre for Research in Agricultural Genomics.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version
 * 2.1 as published by the Free Software Foundation.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 2.1 for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License version 2.1 along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
var CRAG = angular.module('CRAG', [ 'ui.router',
                                    'ui.bootstrap',
                                    'ngAnimate',
                                    // 'CRAG.services',
                                    // 'btford.socket-io',
                                    'ui.bootstrap.alerts',
                                    'FBAngular', // FullScreen
                                    'ngCookies',
                                    'ngSanitize', // To be able to use ng-bind-html
                                    'nvd3', // Charts http://krispo.github.io/angular-nvd3
                                    'chart.js',  // angular-chart.js/
                                    'luegg.directives', // angular-scroll-glue
                                    'ui.bootstrap.contextMenu'
                                    ]);

CRAG.config( ['$stateProvider', '$urlRouterProvider', //'$locationProvider', '$httpProvider'
    function ( $stateProvider,   $urlRouterProvider) {

	$urlRouterProvider.when('/' , '/index.html');

	$stateProvider
    .state("login",			              { url: '/login',		                views: { 'main' : { templateUrl: "partials/login.html", 	                      controller: "LoginController"}}})
		.state("home",			              { url: '/welcome',		              views: { 'main' : { templateUrl: "partials/welcome.html", 	                    controller: "MainController"}}})
		.state("progress",			          { url: '/progress',		              views: { 'main' : { templateUrl: "partials/progress.html", 	                    controller: "MainController"}}})
		.state("help",			              { url: '/help',	                    views: { 'main' : { templateUrl: "partials/help/help.html",                     controller: "HelpController"}}})
		.state("commands",	              { url: '/commands',	                views: { 'main' : { templateUrl: "partials/commands.html",                      controller: "HelpController"}}})
		.state("mstatspop",			          { url: '/mstatspop',	              views: { 'main' : { templateUrl: "partials/help/mstatspop.html",                controller: "HelpController"}}})
		.state("pipeline",			          { url: '/pipeline',		              views: { 'main' : { templateUrl: "partials/help/pipeline.html", 	              controller: "HelpController"}}})
		.state("examples",			          { url: '/examples',		              views: { 'main' : { templateUrl: "partials/examples/examples.html", 	          controller: "MainController"}}})
		.state("downloads",               { url: '/downloads',                views: { 'main' : { templateUrl: "partials/downloads/downloads.html",           controller: "ReportController"}}})


		.state("admin_dashboard",         { url: '/admin_dashboard',		      views: { 'main' : { templateUrl: "partials/admin_dashboard.html", 	            controller: "AdminDashboardController"}}})
		.state("network",			            { url: '/network',				          views: { 'main' : { templateUrl: "partials/network.html", 			                controller: "NetworkController"}}})
		.state("experiments",		          { url: '/experiments',			        views: { 'main' : { templateUrl: "partials/experiments.html", 		              controller: "ExperimentsController"}}})
    .state("components_diagram",      { url: '/components_diagram',       views: { 'main' : { templateUrl: "partials/docs/components_diagram.html",       controller: "DiagramsController"}}})
		.state("pipeline_editor",	        { url: '/pipeline_editor',	        views: { 'main' : { templateUrl: "partials/editor.html",                        controller: "EditorController"}}})
		.state("experiment_editor",	      { url: '/experiment_editor',	      views: { 'main' : { templateUrl: "partials/editor.html",                        controller: "EditorController"}}})
		.state("URS_FRS",	                { url: '/URS_FRS',	                views: { 'main' : { templateUrl: "partials/docs/URS_FRS.html",                  controller: "DocsController"}}})
		.state("system_diagrams",	        { url: '/system_diagrams',	 	      views: { 'main' : { templateUrl: "partials/docs/system_diagrams.html", 	        controller: "DiagramsController"}}})
		.state("traceability_matrix",     { url: '/traceability_matrix',      views: { 'main' : { templateUrl: "partials/docs/traceability_matrix.html",      controller: "DocsController"}}})
		.state("calculation_development", { url: '/calculation_development',  views: { 'main' : { templateUrl: "partials/docs/calculation_development.html",  controller: "DocsController"}}})
		.state("mstatspop_ngasp",         { url: '/mstatspop_ngasp',          views: { 'main' : { templateUrl: "partials/docs/mstatspop_ngasp.html",          controller: "DocsController"}}})
		.state("report1",                 { url: '/report1',                  views: { 'main' : { templateUrl: "partials/reports/report1.html",               controller: "ReportController"}}})
  ;
}]);

CRAG.run(['$rootScope', '$state', function ($rootScope, $state) { 
  $state.go('experiment_editor');
}]);


/*
================================================================================
Node
================================================================================
        - id                                                                    : Number
        - type
        - selected
        - position
                - top
                - left
        - value
        - outputs[]
                - id
                - to[] 
                        - node_id
                        - input_id
        - inputs[]
                - id
        - temp
                - width
                - height
                - type_obj                                                      : Type
                - input_areas[]
                        - left
                        - top
                        - width
                        - height
                        - x
                        - y
                        - id
                - output_areas[]
                - focused_input
                - focused_output
                - execution_order

================================================================================
Type
================================================================================
        - id ("input")
        - style ($scope.NodeStyle.INPUT_NODE)
        - inputs[]
                - id
                - name
                - type                                                          : "int"
                - accumulative
        - outputs[]
                - id
                - name
                - type                                                          : "int"
        - description                                                           : ???

================================================================================
output_ref
================================================================================
        - node
        - connector
                - to[]
                        - node_id
                        - input_id
                - id


================================================================================
input_ref
================================================================================
        - node
        - connector
                - from[]
                        - node_id
                        - input_id
                - id


================================================================================
joining_connector
================================================================================
        - from
                - direction                                                     : "input" / "output"
                - node
                - connector
                        - id
                        - from
        - to


================================================================================
$scope.DocsNavTabs
  GetCurrentDocument()
================================================================================
        - id
        - index
        - selected_tab                                                          : pointer to the selected tab object
        - next_id
        - list[]                                                                : list of tabs
                - id
                - properties
                        - type                                                  : $scope.FileType.EXPERIMENT / PIPELINE
                        - name
                        - email
                        - date
                        - description
-------------------- Only PIPELINES --------------------------------------------
                - interface
                        - inputs[]
                                - id
                                - name
                                - enabled                                       : true/false
                                - type                                          : "text-file"...
                        - outputs[]
                                - id
                                - name
                                - enabled                                       : true/false
                                - type                                          : "text-file"...
--------------------------------------------------------------------------------
                - visible
                - data
                        - nodes[]
                                - id
                                - enabled                                       : true/false
                                - name
                                - type                                          : "calc-"...
                                - x
                                - y
                                - value
                                - outputs[]
                                        - id
                                        - to[]
                                                - node_id
                                                - input_id
                        - next_id
                        - saved
                - page
                        - width
                        - height


================================================================================
dependecies_list
================================================================================
        - id
        - enabled
        - type
        - value
        - temp
                - type_obj
        - node_type_inputs                                                      : number of inputs
        - inputs[]
                - id
                - from[]
                        - node_id
                        - output_id
                        - name                                                  : the beautiful name
                        - type                                                  : this is the type of the node not the connector type

        - outputs[]
                - id
                - to[] 
                        - node_id
                        - input_id
        - num_inputs_satisfied                                                  : number


================================================================================
execution_list
This is the same dependencies_list but ordered by "execution order" and by:
        INPUT_NODES
        DATA_NODES
        ...
        OUTPUT_NODES
================================================================================
*/

