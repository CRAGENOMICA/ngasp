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
/// ---------------------------------------------------------------------------
/// @file math_tools.js
/// @namespace ngaSP
/// Module description
/// ---------------------------------------------------------------------------

// ============================================================================
// EXPORT
// ============================================================================

module.exports = {
	GenerateRandomId: function(size) {
		var ret = "";
		var possible = "abcdefghijklmnopqrstuvwxyz0123456789";

		for(var i = 0; i < size; i++)
		    ret += possible.charAt(Math.floor(Math.random() * possible.length));

		return ret;
	}
};


