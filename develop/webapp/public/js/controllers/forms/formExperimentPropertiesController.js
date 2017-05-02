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
CRAG.controller('FormExperimentPropertiesController', function($scope,
                                                               $rootScope,
                                                               $modalInstance,
                                                               MessagesFactory,
                                                               properties) {
  var initial_properties = {
    name: "",
    type: -1,
    email: "",
    date: "",
    description: ""
  };

  $scope.properties = {
    name: "",
    type: -1,
    email: "",
    date: "",
    description: ""
  };

  $scope.init = function () {
    // Store the initial properties
    initial_properties.name = properties.name;
    initial_properties.type = properties.type;
    initial_properties.email = properties.email;
    initial_properties.date = properties.date;
    initial_properties.description = properties.description;

    // Fill form fields
    $scope.properties.name = properties.name;
    $scope.properties.type = properties.type;
    $scope.properties.email = properties.email;
    $scope.properties.date = properties.date;
    $scope.properties.description = properties.description;
  };

  ////////////////////////////////////////////////////////////////////////////
  // EVENTS
  ////////////////////////////////////////////////////////////////////////////

  $scope.OnOk = function() {
    if (initial_properties.name != $scope.properties.name) {
      CheckExperimentName($scope.properties.name);
    } else {
      OnOKConfirm();
    }
  };

  $scope.OnCancel = function() {
    // Restore initial data
    // Store the initial properties
    properties.name = initial_properties.name;
    properties.type = initial_properties.type;
    properties.email = initial_properties.email;
    properties.date = initial_properties.date;
    properties.description = initial_properties.description;

    $modalInstance.dismiss();
  };


  ////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  function OnOKConfirm() {
    var d = new Date();
    $scope.properties.date = d.toLocaleString();
    $modalInstance.close($scope.properties);
  };

  function CheckExperimentName(name) {
    console.log("** CheckExperimentName() **");

    var send = {
      method: 'GET',
      url: $rootScope.webAddress + 'repository_check_experiment_name/' + name,
      headers: { 'Content-Type': 'application/json' },
      data: {}
    };

    $rootScope.Http(send,
    function(message) {
      if (message.data.data == true) {
        MessagesFactory.confirm("Experiment already exists. Do you want to replace it?",
          function() {
            // Yes, do replace it.
            OnOKConfirm();
          },
          function() {
            // No, do not replace it.
            // Leave the form open.
          });
      } else {
        OnOKConfirm();
      }
    },
    function(message) {
      console.log("****** CheckExperimentName() ERROR");
    });
  };


	$scope.init();
});

