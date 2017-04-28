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
CRAG.controller('NetworkController', function($scope, $rootScope, socket, logs, MessagesFactory) {

	$scope.init = function () {
        $rootScope.OnRefreshClientsList();
		$rootScope.OnRefreshLocalManagersList();
	};


	$scope.OnCloseServer = function() {
		MessagesFactory.confirm("Are you sure that you want to close the server?", 
		function() {  // Yes
		    $rootScope.Http({
		            method: 'DELETE',
		            url: $rootScope.webAddress + 'servers',
				    headers: { 'Content-Type': 'application/json' },
		            data: {},
	        },
            function(message) {
			    $scope.command_status = "Server is closed.";
		    },
		    function(message) {
		    });
		},
		function() {  // No
		});
	};

	$scope.init();
});


