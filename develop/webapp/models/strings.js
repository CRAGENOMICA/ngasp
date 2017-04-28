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
/// @file strings.js
/// @namespace ngaSP
/// Module description
/// ---------------------------------------------------------------------------

// ============================================================================
// CONSTANTS: MESSAGES FROM THE CENTRAL MANAGER TO THE LOCAL MANAGER
// ============================================================================

module.exports = function() {
	this.APP_LISTENING_PORT 				= function() { return "This app is listening at http://"; };
	this.APP_ERROR 							= function() { return "I found this server error: "; };
	this.SEARCHING_LOCAL_MANAGER 			= function() { return "I am searching the local manager..."; };
	this.SEARCHING_BEST_LOCAL_MANAGER 		= function() { return "I am going to find the less used local manager."; };
	this.LOCAL_MANAGER_NOT_FOUND 			= function() { return "I could not find the local manager."; };
	this.LOCAL_MANAGER_FOUND 				= function() { return "Local manager found."; };
	this.LM_ENROL_REQUEST 					= function() { return "A new LM is telling me hello. I am going to assign to it a new lm_key."; };
	this.LM_DATA_NOT_RECOGNIZED 			= function() { return "I do not understand data received from local manager: "; };
	this.REQUEST_EXPERIMENT_KEY 			= function() { return "The user wants me to give him/her a new experiment key."; };
	this.RUN_COMMAND 						= function() { return "The user wants me to run this command: "; };
	this.EXPERIMENT_INFO 					= function() { return "Experiment info: "; };
	this.LOCAL_MANAGER_IS_CLOSED 			= function() { return "Local manager is closed: "; };
	this.LOCAL_MANAGER_IS_DISCONNECTED 		= function() { return "Local manager is disconnected: "; };
	this.LOCAL_MANAGER_SENDS_ERROR 			= function() { return "I found this server error: "; };
	this.CM_LISTENING 						= function() { return "I am listening on: "; };
	this.USER_REQUEST_EXPERIMENT_OUTPUT 	= function() { return "The user wants me to give him/her the output of the experiment: "; };
};

