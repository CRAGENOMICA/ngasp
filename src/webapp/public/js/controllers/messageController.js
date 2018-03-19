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
CRAG.controller('MessageController', function($scope, $modalInstance, type, title, message, list_values) {

    // INIT ...................................................................

    $scope.type = type;                                 // Window type: ['alert' / 'confirm' / 'error' / 'input'].
    $scope.title = (title != null) ? title : 'ngaSP';	// Window title.
    $scope.message = message;                           // Show message.
    $scope.list_values = list_values;                   // This window can show a list of { id, value }.
	$scope.list_selection = [];							// Selected values from the list_values.
	$scope.input = "";									// The accepted value when the window type is input.

    // VISIBILITY .............................................................

    /*
     * Return true: Alert Window
     */
    $scope.ShowOneButton = function() {
        return (($scope.type == 'alert') || ($scope.type == 'error'));
    };

    /*
     * Return true: Confirm Window
     */
    $scope.ShowTwoButtonsConfirm = function() {
        return ($scope.type == 'confirm');
    };

    $scope.ShowTwoButtonsInput = function() {
        return ($scope.type == 'input');
    };

    $scope.bError = function () {
        return ($scope.type == 'error');
    };

    $scope.bInput = function () {
        return ($scope.type == 'input');
    };

    $scope.bConfirm = function () {
        return ($scope.type == 'confirm');
    };

    $scope.bAlert = function () {
        return ($scope.type == 'alert');
    };

    $scope.ShowListValues = function () {
        return (($scope.list_values != null) && ($scope.list_values.length > 0));
    };

    // ACTIONS ................................................................

    /*
     * Accept message.
     */
    $scope.OnOk = function() {
        $modalInstance.close($scope.input);
    };

    /*
     * Discard message.
     */
    $scope.OnCancel = function() {
        $modalInstance.dismiss('');
    };
});

