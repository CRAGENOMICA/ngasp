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
/// ---------------------------------------------------------------------------
/// @file string_tools.js
/// @namespace ngaSP
/// Module description
/// ---------------------------------------------------------------------------

// ============================================================================
// EXPORT
// ============================================================================

module.exports = {
	GetString: function(a, separator) {
		var text = "" + a;
		var ret = {
			first: text,
			second: ""
		};
		var separator_pos = text.indexOf(separator);

		if (separator_pos != -1) {
			ret.first = text.substring(0, separator_pos);
			ret.second = text.substring(separator_pos + 1);
		}

		return ret;
	},
};

