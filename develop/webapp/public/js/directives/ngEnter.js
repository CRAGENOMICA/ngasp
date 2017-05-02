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
/*
 * Aquesta directiva permet que un objecte html pugui fer alguna cosa quan es prem la tecla enter sobre ell:
 */
CRAG.directive('ngEnter', function () {
    return function (scope, element, attrs) {
        element.bind("keydown keypress", function (event) {                     //Es controla que es premi una tecla sobre el control                        
            if(event.which === 13) {                                            //Si la tecla és un ENTER (codi 13)
                scope.$apply(function (){
                    scope.$eval(attrs.ngEnter);                                 
                });

                event.preventDefault();
            }
        });
    };
});

// http://www.ngroutes.com/questions/1b42da5/angular-modal-instance-cant-read-dom-elements.html
CRAG.directive('signaturePad', function() {
    return {
        link: function(scope, element) {

            var wrapper = element[0],
                canvas = wrapper.children[0]; //querySelector("canvas_chart");

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

            if (canvas != null) {
                var context = canvas.getContext('2d');
                new Chart(context).Line(riceData);   
            }

        }
    };
});

