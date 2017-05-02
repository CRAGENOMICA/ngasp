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
CRAG.controller('ChartController', function($scope,
                                            $modalInstance) {

    $scope.message = "";

    $scope.init = function() {
        /*
        var riceData = {
            labels : ["January","February","March","April","May","June"],
            datasets : [
                {
                    fillColor : "rgba(172,194,132,0.4)",
                    strokeColor : "#ACC26D",
                    pointColor : "#fff",
                    pointStrokeColor : "#9DB86D",
                    data : [203000,15600,99000,25100,30500,24700]
                }
            ]
        }

        var canvas = document.getElementById('rice');
        if (canvas != null) {
            var context = canvas.getContext('2d');
            new Chart(context).Line(riceData);   
        } else {
            $scope.message = "KO";
        }*/
    };

    ////////////////////////////////////////////////////////////////////////////
    // EVENTS
    ////////////////////////////////////////////////////////////////////////////

    $scope.OnOk = function() {
        $modalInstance.close();
    };

    $scope.OnCancel = function() {
        $modalInstance.dismiss();
    };

    $modalInstance.opened.then($scope.init);
});

