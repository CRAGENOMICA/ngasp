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
CRAG.controller('ReportController', function($scope, $rootScope) {

	$scope.init = function () {
  };

  $scope.getNumber = function(num) {
    var x = new Array();
    for(var i = 0; i <= num; i++) {
      x.push( i + 1 );
    }
    return x; 
  }

  $scope.file_name = "examples/input.fa";
  $scope.file_type = "fasta";
  $scope.option_o = 0;
  $scope.option_p = 1;
  $scope.option_u = 0;
  $scope.option_t = 1000;
  $scope.option_s = 123456;
  $scope.option_G = 0;
  $scope.num_populations = 3;
  $scope.samples_x_population = "48 46 1";
  $scope.sum_samples_x_population = 96;


  $scope.names = [
    {a:'EUROPACOMMERCIALHA', b:'ASIALOCALBM', c:'Babyrousa_babyrussa'},
    {a:'EUROPACOMMERCIALHA2', b:'ASIALOCALBM2', c:''},
    {a:'EUROPACOMMERCIALLR05', b:'ASIALOCALHZ1', c:''},
    {a:'EUROPACOMMERCIALLR052', b:'ASIALOCALHZ12', c:''},
    {a:'EUROPACOMMERCIALLR09', b:'ASIALOCALHZ2', c:''},
    {a:'EUROPACOMMERCIALLR092', b:'ASIALOCALHZ22', c:''},
    {a:'EUROPACOMMERCIALLR10', b:'ASIALOCALJQH', c:''},
    {a:'EUROPACOMMERCIALLR102', b:'ASIALOCALJQH2', c:''},
    {a:'EUROPACOMMERCIALLR111', b:'ASIALOCALMS02', c:''},
    {a:'EUROPACOMMERCIALLR1112', b:'ASIALOCALMS022', c:''},
    {a:'EUROPACOMMERCIALLR112', b:'ASIALOCALLW', c:''},
    {a:'EUROPACOMMERCIALLR1122', b:'ASIALOCALLW2', c:''},
    {a:'EUROPACOMMERCIALLR121', b:'ASIALOCALLP', c:''},
    {a:'EUROPACOMMERCIALLR1212', b:'ASIALOCALLP2', c:''},
    {a:'EUROPACOMMERCIALLR122', b:'ASIALOCALRC1', c:''},
    {a:'EUROPACOMMERCIALLR1222', b:'ASIALOCALRC12', c:''},
    {a:'EUROPACOMMERCIALLR123', b:'ASIALOCALRC2', c:''},
    {a:'EUROPACOMMERCIALLR1232', b:'ASIALOCALRC22', c:''},
    {a:'EUROPACOMMERCIALLR14', b:'ASIALOCALNJ1', c:''},
    {a:'EUROPACOMMERCIALLR142', b:'ASIALOCALNJ12', c:''},
    {a:'EUROPACOMMERCIALLW05', b:'ASIALOCALNJ2', c:''},
    {a:'EUROPACOMMERCIALLW052', b:'ASIALOCALNJ22', c:''},
    {a:'EUROPACOMMERCIALLW061', b:'ASIALOCALQB', c:''},
    {a:'EUROPACOMMERCIALLW0612', b:'ASIALOCALQB2', c:''},
    {a:'EUROPACOMMERCIALLW062', b:'ASIALOCALSG', c:''},
    {a:'EUROPACOMMERCIALLW0622', b:'ASIALOCALSG2', c:''},
    {a:'EUROPACOMMERCIALLW07', b:'ASIALOCALTC', c:''},
    {a:'EUROPACOMMERCIALLW072', b:'ASIALOCALTC2', c:''},
    {a:'EUROPACOMMERCIALPI03', b:'ASIALOCALXP', c:''},
    {a:'EUROPACOMMERCIALPI032', b:'ASIALOCALXP2', c:''},
    {a:'EUROPACOMMERCIALPI04', b:'ASIALOCALYM', c:''},
    {a:'EUROPACOMMERCIALPI042', b:'ASIALOCALYM2', c:''},
    {a:'EUROPACOMMERCIALDU02', b:'ASIALOCALYS', c:''},
    {a:'EUROPACOMMERCIALDU022', b:'ASIALOCALYS2', c:''},
    {a:'EUROPACOMMERCIALDU03', b:'ASIALOCALZP', c:''},
    {a:'EUROPACOMMERCIALDU032', b:'ASIALOCALZP2', c:''},
    {a:'EUROPACOMMERCIALLR04', b:'ASIALOCALJH', c:''},
    {a:'EUROPACOMMERCIALLR042', b:'ASIALOCALJH2', c:''},
    {a:'EUROPACOMMERCIALLR08', b:'ASIALOCALXX', c:''},
    {a:'EUROPACOMMERCIALLR082', b:'ASIALOCALXX2', c:''},
    {a:'EUROPACOMMERCIALLW021', b:'ASIALOCALSX', c:''},
    {a:'EUROPACOMMERCIALLW0212', b:'ASIALOCALSX2', c:''},
    {a:'EUROPACOMMERCIALLW022', b:'ASIALOCALMP', c:''},
    {a:'EUROPACOMMERCIALLW0222', b:'ASIALOCALMP2', c:''},
    {a:'EUROPACOMMERCIALLW023', b:'ASIALOCALJZ', c:''},
    {a:'EUROPACOMMERCIALLW0232', b:'ASIALOCALJZ2', c:''},
    {a:'EUROPACOMMERCIALLW024', b:'', c:''},
    {a:'EUROPACOMMERCIALLW0242', b:'', c:''}
  ];

	$scope.init();
});

