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
CRAG.controller('HelpController', function($scope, $rootScope) {

  $scope.mstatspop_command = 
    {
      name: 'mstatspop',
      options:
      [
        {
          type: 'A',
          short: 'f',
          long: '',
          desc:  'Input format',
          example: '',
          only: 'dfsdf',
          values:
          [
            { value: 'fasta',
              desc: 'fasta file',
              default: 'yes',
              example: 'examples',
              only: ''
            },
            { value: 'tfa',
              desc: 'transposed fasta file',
              default: '',
              example: 'examples',
              only: ''
            },
            { value: 'ms',
              desc: 'ms file',
              default: '',
              example: '',
              only: ''
            }
          ]
        },
        {
          type: 'A',
          short: 'f',
          long: '',
          desc:  'Input format',
          example: '',
          only: 'dfsdf',
          values:
          [
            { value: 'fasta',
              desc: 'fasta file',
              default: 'yes',
              example: 'examples',
              only: ''
            },
            { value: 'tfa',
              desc: 'transposed fasta file',
              default: '',
              example: 'examples',
              only: ''
            },
            { value: 'ms',
              desc: 'ms file',
              default: '',
              example: '',
              only: ''
            }
          ]
        }
,
        {
          type: 'B',
          short: 'f',
          long: '',
          desc:  'Input format',
          example: '',
          only: 'dfsdf',
          values:
          [
            { value: 'fasta',
              desc: 'fasta file',
              default: 'yes',
              example: 'examples',
              only: ''
            },
            { value: 'tfa',
              desc: 'transposed fasta file',
              default: '',
              example: 'examples',
              only: ''
            },
            { value: 'ms',
              desc: 'ms file',
              default: '',
              example: '',
              only: ''
            }
          ]
        }

      ]
    };
/*
  $scope.commands:
  [
  ];
*/

	$scope.init = function() {
  };

	$scope.init();
});






