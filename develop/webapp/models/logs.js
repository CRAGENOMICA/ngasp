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
/// @file logs.js
/// @namespace ngaSP
/// Module description
/// ---------------------------------------------------------------------------

// ============================================================================
// INCLUDES
// ============================================================================

var Constants		= require('./constants');
var cte = new Constants();

// ============================================================================
// EXPORT
// ============================================================================

var num_ = 0;

//if (!Date.now) {
//    Date.now = function() { return new Date().getTime(); }
//}

module.exports = {
    isSilence: function() { return false; },
    num: function() {
        return +new Date() + " "; 
        //return Date.now() + " ";
        // return Date.now() + " ";
        // num_++;
        // return "(" + num_ + ") ";
    },
    process_text: function(text) {
        return text.replace("\n", "<br />");
    },
	cm: function(text) {
		if (!this.isSilence()) { console.log(this.num() + cte.CM_HEADER() + " " + this.process_text(text)); }
	},
	cm_debug: function(text) {
		if (this.isSilence()) { console.log(this.num() + cte.CM_HEADER() + " " + this.process_text(text)); }
	},
	node: function(text) {
		if (!this.isSilence()) { console.log(this.num() + cte.NODE_HEADER() + " " + this.process_text(text)); }
	},
    nodeRec: function (from, data) {
		if (!this.isSilence()) { console.log(this.num() + cte.NODE_HEADER() + " (<" + from + ") " + JSON.stringify(data)); }
    },
    cmRec: function (from, data) {
		if (!this.isSilence()) { console.log(this.num() + cte.CM_HEADER() + " (<" + from + ") " + JSON.stringify(data)); }
    },
    cmSend: function (to, data) {
		if (!this.isSilence()) { console.log(this.num() + cte.CM_HEADER() + " (>" + to + ") " + JSON.stringify(data)); }
    },
};

