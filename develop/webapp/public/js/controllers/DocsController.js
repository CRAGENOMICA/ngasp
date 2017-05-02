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
CRAG.controller('DocsController', function($scope, $rootScope, $state, docs, arrays) {

	$scope.init = function() {
	};

  $scope.OpenDiagramsPage = function() {
    $state.go("traceability_matrix");
  };

  $scope.To3Digits = function(id) {
    return docs.To3Digits(id);
  };


  var show_all_cases = true;
  $scope.ShowAllCases = function() {
    return show_all_cases;
  };

  $scope.SetShowAllCases = function(val) {
    show_all_cases = val;
  };

  $scope.MatrixFilter = function(item) {
    var ret = true;
    if ($scope.ShowAllCases() == false) {
      ret = ((item.id==null) ||
               ((item.case_type == docs.CASE_START_PROCESS) ||
                (item.case_type == docs.CASE_MANUAL_PROCESS)
               )
            );
    }
    return ret;
  };

  $scope.GetDocsLib = function() {
    return docs;
  };

  $scope.GetURSDescription = function(urs_id) {
    return arrays.FindArrayElementById($rootScope.URS_list, urs_id).desc;
  };

	$scope.init();
});


/*
The system must have at least one master.
The master must have one data manager.
The master must have one engine.
The master must have at least one worker.
The worker must have one data manager.
The master's engine will decide the worker that will run a calculation.
The master's engine will send messages to the worker identifying: calc_id to be executed, its inputs and its outputs.
The worker must execute one calculate at a time.
The calculation could have more than one implementations.
The calculation's default implementation will be serial.
The calculation will ask for inputs and outputs to its worker's DM.
The worker's DM will synchronize its data with its master's DM.
The worker will communicate the calculation's finished status to its master: done / error message.
The pipeline parallelism will be defined explicitly by its node dependencies.
The master's engine will own the scattering and gathering data process.
The Data Manager types will be: master's DM & worker's DM.


*/

/*
    docs.AddToDictionary("\"boolean\"", "I has 1 bit.");
    docs.AddToDictionary("\"char\"", "I has 8 bits.");
    docs.AddToDictionary("\"int64\"", "It is a 64 bits signed integer.");
    docs.AddToDictionary("\"double\"", "It has 15 to 16 decimal digits of precision.");
    docs.AddToDictionary("\"float\"", "It has 7 decimal digits of precision.");
    docs.AddToDictionary("\"string\"", "It is a c++ std::string.");
    docs.AddToDictionary("[GOS]*", "0 or more general options");
    docs.AddToDictionary("[CMD]?", "0 or 1 commands");
    docs.AddToDictionary("[COS]*", "0 or more command options");
    docs.AddToDictionary("magnetic connections", "Magnetic connections is when you aproximate a connector line to a connector and automatically both connect.");
*/ 

