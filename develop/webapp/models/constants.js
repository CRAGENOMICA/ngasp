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
/// @file constants.js
/// @namespace ngaSP
/// Module description
/// ---------------------------------------------------------------------------

module.exports = function() {
// ============================================================================
// CONSTANTS: SERVER
// ============================================================================

  this.HOST                  = function() { return "0.0.0.0"; };
  this.PORT_WEB              = function() { return 3000; };
  this.PORT_CM               = function() { return 6969; };
  this.PUBLIC_FOLDER         = function() { return "/public"; };
  this.ONE_MINUTE            = function() { return 60000; };
  this.FIVE_MINUTES          = function() { return 300000; };
  this.ONE_HOUR              = function() { return 600000; };
  this.TIME_REFRESH_LM_LIST  = function() { return 600000; };
  this.SERVER_DATA_FOLDER    = function() { return "/develop/data/"; };
  this.DATA_FILES_TABLE_FILE = function() { return "/develop/data/data_files.json"; };

// ============================================================================
// CONSTANTS: MESSAGES
// ============================================================================

  this.NODE_HEADER           = function() { return "NO"; };
  this.CM_HEADER             = function() { return "CM"; };


// ============================================================================
// CONSTANTS: MESSAGES FROM THE CENTRAL MANAGER TO THE LOCAL MANAGER
// ============================================================================

  this.LM_COMMAND_WELLCOME         = function() { return "WELLCOME"; };
  this.LM_COMMAND_GET_INSTANCE_KEY = function() { return "GET_NEW_INSTANCE_KEY"; };
  this.LM_CLOSE_LM                 = function() { return "CLOSE"; };
  this.LM_COMMAND_RUN              = function() { return "RUN"; };
  this.LM_GET_EXPERIMENT_RESULT    = function() { return "GET_EXPERIMENT_RESULT"; };
  this.LM_CLEAN_EXPERIMENT_RESULT  = function() { return "CLEAN_EXPERIMENT_RESULT"; };
  this.LM_GET_INSTANCES_LIST       = function() { return "INSTANCES_LIST"; };


// ============================================================================
// CONSTANTS: MESSAGES FROM THE LOCAL MANAGER TO THE CENTRAL MANAGER
// ============================================================================

  this.CM_COMMAND_ENROLL_LM     = function() { return "HELLO"; };
  this.CM_COMMAND_INSTANCE_KEY  = function() { return "INSTANCE_KEY"; };
  this.CM_COMMAND_RESULT        = function() { return "RESULT"; };
  this.CM_EXPERIMENT_RESULT     = function() { return "EXPERIMENT_RESULT"; };
  this.CM_INSTANCES_LIST        = function() { return "INSTANCES_LIST"; };


// ============================================================================
// CONSTANTS: MESSAGES FROM THE CENTRAL MANAGER TO THE WEB PAGE
// ============================================================================

  this.WEB_KEY_RECEIVED        = function() { return "KEY_RECEIVED"; };
  this.WEB_COMMAND_EXECUTED    = function() { return "COMMAND_EXECUTED"; };
  this.WEB_EXPERIMENT_OUTPUT   = function() { return "EXPERIMENT_OUTPUT_RECEIVED"; };
  this.WEB_LOCAL_MANAGERS_LIST = function() { return "LOCAL_MANAGERS_LIST"; };

// ============================================================================
// CONSTANTS: TRANSFER CONTROL CHARACTERS
// ============================================================================

  this.EOT                  = function() { return '<'; }; // End Of Transmission
  this.COMMAND_SEPARATOR    = function() { return '>'; };
  this.PARAM_SEPARATOR      = function() { return '%'; };
  this.KEY_SEPARATOR        = function() { return '-'; };
};

