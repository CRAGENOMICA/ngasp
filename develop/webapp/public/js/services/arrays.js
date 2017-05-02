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
CRAG.factory('arrays', function ($rootScope) {
  return {
    // Array elements must have a field named: 'id'.
    FindArrayElementById: function (array, id) {
        var ret = null;
        for (var i = 0; ((i < array.length) && (ret == null)); i++) {
            if (array[i].id == id) {
                ret = array[i];
            }
        }
        return ret;
    },
    FindArrayElementIndexById: function (array, id) {
        var ret = null;
        for (var i = 0; ((i < array.length) && (ret == null)); i++) {
            if (array[i].id == id) {
                ret = i;
            }
        }
        return ret;
    },
    RemoveElementById: function (array, id) {
        var ret = false;
        var index = this.FindArrayElementIndexById(array, id);

        if (index != null) {
            array.splice(index, 1);
            ret = true;
        }
        return ret;
    },
  };
});

