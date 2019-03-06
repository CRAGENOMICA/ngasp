/*
 * ngaSP: the computational solution for next generation analysis of 
 * Sequence Polymorphisms.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
 * Centre for Research in Agricultural Genomics (CRAG).
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
CRAG.controller('AdminDashboardController', function($scope, $rootScope, $location) {

	var layout_hierarchical = { };

	$scope.init = function () {
		$scope.OnRefreshNetworkGraph();
	};

	// ========================================================================
	// GRAPH VARS
	// ========================================================================
	var nodes 	= null;
	var edges 	= null;
	var network 	= null;

	// ========================================================================
	// CONSTANTS
	// ========================================================================
	var IMAGES_DIR 	= '../images/';
	var EDGE_USERS 	= 150;
	var EDGE_LMS   	= 175;
	var EDGE_BINS  	= 150;
	var CM   		= 100;
	var LM   		= 150;
	var USER 		= 300;
	var BIN  		= 500;
	var USERS_LEVEL = 1;
	var CM_LEVEL    = 2;
	var LMS_LEVEL   = 3;
	var BINS_LEVEL  = 4;
  var CONNECTED_COLOR = '#4285f4';     // blue
  var DISCONNECTED_COLOR = "#ff0000";  // red


	$scope.OnRefreshNetworkGraph = function() {
        $rootScope.OnRefreshClientsList();
        $rootScope.OnRefreshLocalManagersList();
        $rootScope.OnRefreshExperimentsList();
    };

	$scope.DrawNetworkGraph = function() {
		nodes = new vis.DataSet();
		nodes.add([
    			{id: CM, level: CM_LEVEL, label: $location.host() + ":" + $location.port(), image: IMAGES_DIR + 'cm.png', shape: 'image', value: 1},
		]);

		edges = new vis.DataSet();

		// add, update, remove

		for (var i=0; i < $rootScope.clients_list.length; i++) {			
			nodes.add({id: USER + i, level: USERS_LEVEL, label: $rootScope.clients_list[i].address, image: IMAGES_DIR + 'user.png', shape: 'image', value: 1});
            edges.add({from: USER + i, to: CM, length: EDGE_USERS, color:{color:CONNECTED_COLOR, highlight:CONNECTED_COLOR}, dashes:false, label: '', font: {align: 'top'}});
		}

		for (var i=0; i < $rootScope.local_manager_list.length; i++) {			
			nodes.add({id: LM + i, level: LMS_LEVEL, label: $rootScope.local_manager_list[i].address + "\n(" + $rootScope.local_manager_list[i].lm_id + ")", image: IMAGES_DIR + 'computer.png', shape: 'image'});

            var disconnected = ($rootScope.local_manager_list[i].status != "OPEN");

			if (disconnected) {
				line_color = DISCONNECTED_COLOR;
			} else {
                line_color = CONNECTED_COLOR;
            }

			edges.add({from: CM, to: LM + i, length: EDGE_LMS, color:{color:line_color, highlight:line_color }, dashes: disconnected, label: '', font: {align: 'top', color: line_color}});
		}

		for (var i=0; i < $rootScope.experiments_list.length; i++) {

            $rootScope.experiments_list[i]

			nodes.add({id: BIN + i, level: BINS_LEVEL, label: $rootScope.experiments_list[i].name + "\n(" + $rootScope.experiments_list[i].experiment_id + ")", image: IMAGES_DIR + 'experiment.png', shape: 'image'});

			for (var j=0; j < $rootScope.local_manager_list.length; j++) {
				if ($rootScope.experiments_list[i].lm_id == $rootScope.local_manager_list[j].lm_id) {
                    var disconnected = ($rootScope.experiments_list[i].status != "OPEN");
    
			        if (disconnected) {
				        line_color = DISCONNECTED_COLOR;
			        } else {
                        line_color = CONNECTED_COLOR;
                    }

   					edges.add({from: LM + j, to: BIN + i, length: EDGE_BINS, color:{color:line_color, highlight:line_color}, dashes: disconnected, label: '', font: {align: 'top'}});
				}
			}
		}

		// create a network
		var container = document.getElementById('network');
		var data = {
			nodes: nodes,
			edges: edges
		};

		var options = {
			nodes: {
				// shape: 'dot',
				size: 30,
				font: {
					size: 12
				},
				borderWidth: 2,
				// shadow: { size: 10, x:1, y:1 },
			},
			edges: {
				width: 1,
				// shadow: { size: 10, x:1, y:1 },
			},
			layout: layout_hierarchical
		};

		network = new vis.Network(container, data, options);
	};

	$scope.OnSetLayoutHierarchical = function(layout) {
		if (layout == "UD") {
			layout_hierarchical = { hierarchical: { direction: 'UD' } };
		}
		if (layout == "DU") {
			layout_hierarchical = { hierarchical: { direction: 'DU' } };
		}
		if (layout == "LR") {
			layout_hierarchical = { hierarchical: { direction: 'LR' } };
		}
		if (layout == "RL") {
			layout_hierarchical = { hierarchical: { direction: 'RL' } };
		}
		if (layout == "None") {
			layout_hierarchical = { };
		}

        $scope.DrawNetworkGraph();
	};

	// ========================================================================
	// WATCHES
	// ========================================================================

    $scope.$watch('clients_list', function (newValue, oldValue) {
        $scope.DrawNetworkGraph();
    }, true); 

    $scope.$watch('local_manager_list', function (newValue, oldValue) {
        $scope.DrawNetworkGraph();
    }, true); 

    $scope.$watch('experiments_list', function (newValue, oldValue) {
        $scope.DrawNetworkGraph();
    }, true); 

	$scope.init();
});


