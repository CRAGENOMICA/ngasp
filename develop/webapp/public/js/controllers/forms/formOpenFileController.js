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
CRAG.controller('FormOpenFileController', function($scope,
                                                   $modalInstance,
                                                   type,
                                                   items) {
  $scope.list = [];
  $scope.title = "";

	$scope.init = function () {
      $scope.title = "Load " + type;
      for (var i = 0; i < items.data.length; i++) {

        if (type == "Experiment") {
          $scope.list.push({name:items.data[i].name,selected:false})
        }
        if (type == "Pipeline") {
          $scope.list.push({name:items.data[i].properties.name,selected:false})
        }
      } 
  };

    ////////////////////////////////////////////////////////////////////////////
    // EVENTS
    ////////////////////////////////////////////////////////////////////////////

    $scope.OnOk = function() {
      var result = [];
      for (var i = 0; i < $scope.list.length; i++) {
        if ($scope.list[i].selected == true) {
          result.push($scope.list[i]);
        }
      } 

      $modalInstance.close(result);
    };

    $scope.OnCancel = function() {
        $modalInstance.dismiss();
    };

	$scope.init();
});

