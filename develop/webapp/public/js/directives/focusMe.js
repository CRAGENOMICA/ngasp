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
/*
 * Aquesta directiva serveix per posar el focus en un control determinat.
 * Es fa servir així:
 * <input focus-me >
 * <select focus-me >
 * ...
 */ 
CRAG.directive('focusMe', function($timeout) {
    return {
        scope: { trigger: '=focusMe' },                                         //En la creació se li assigna un valor
        link: function(scope, element) {
            scope.$watch('trigger', function(value) {                           //Detecta que el valor ha canviat
                //console.info("focus-me");
                $timeout(function() {                                           //El timeout retarda una mica el que hi ha dins: és necessari perquè funcioni també als popus
                    element[0].focus();                                         //Posa el focus al control
                });                
            });
        }
    };
});

