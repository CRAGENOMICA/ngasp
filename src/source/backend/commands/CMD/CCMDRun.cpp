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
/**
 *  \brief     CCMDRun.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDRun.h"

#include <string>
#include <iostream>
#include <ctime>          // clock

#include "../../language/CStringTable.h"
#include "../CAllCommands.h"
#include "../ICommand.h"
#include "../../calculations/CAllCalculations.h"
#include "../../calculations/ICalculation.h"
#include "../../data_manager/CDataManager.h"

CCMDRun::CCMDRun()
  : ICommand(CMD_RUN,                                                           // Command Name
             CMD_RUN_ABB,                                                       // Command Abbreviation Name
             CMD_RUN_DESC,                                                      // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  set_name("");
  prepare_ = false;
  calculate_ = false;
  finalize_ = false;
}

CCMDRun::~CCMDRun() {
}

void CCMDRun::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    RUN_NAME_SHORT,                                             // Short Name
                    RUN_NAME_LONG,                                              // Long Name
                    RUN_NAME_DESC,                                              // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required

    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    RUN_PREPARE_SHORT,                                          // Short Name
                    RUN_PREPARE_LONG,                                           // Long Name
                    RUN_PREPARE_DESC,                                           // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_no_argument,                                        // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    RUN_CALCULATE_SHORT,                                        // Short Name
                    RUN_CALCULATE_LONG,                                         // Long Name
                    RUN_CALCULATE_DESC,                                         // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_no_argument,                                        // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    RUN_FINALIZE_SHORT,                                         // Short Name
                    RUN_FINALIZE_LONG,                                          // Long Name
                    RUN_FINALIZE_DESC,                                          // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_no_argument,                                        // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDRun::Prepare() {
  bool parseResult = true;


  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::RUN_NAME_SHORT:
      set_name(arguments);
      break;
    case KeyString::RUN_PREPARE_SHORT:
      prepare_ = true; // CStringTools::ToBoolean(arguments);
      break;
    case KeyString::RUN_CALCULATE_SHORT:
      calculate_ = true; // CStringTools::ToBoolean(arguments);
      break;
    case KeyString::RUN_FINALIZE_SHORT:
      finalize_ = true; // CStringTools::ToBoolean(arguments);
      break;
    default:
      parseResult = false;
      break;
    }
  }

  if ((prepare_ == false) && (calculate_ == false) && (finalize_ == false)) {
    prepare_ = true;
    calculate_ = true;
    finalize_ = true;
  }

  return (CheckOptions() && parseResult);
}

/*
 * User can only create ROOT_PARENT calculations, so this command
 * only executes ROOT_PARENT calculations.
 */
void CCMDRun::Run() {
  ICalculation *calc =
      manager()->all_calculations()->GetCalculationByName(ROOT_PARENT, name());

  if (calc != NULL) {
//    // =========================================================================
//    // Start Clock
//    // =========================================================================
//    clock_t begin = clock();
//    // =========================================================================
    
    if (prepare_) {
      calc->Prepare();
    }

    if (calculate_) {
      calc->Calculate(manager()->all_commands()->dry_run());
    }

    if (finalize_) {
      calc->Finalize();
    }
    
//    // =========================================================================
//    // End Clock
//    // =========================================================================
//    clock_t end = clock();
//    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;  
//    DEBUG_MSG << STR(EOL)
//              << std::fixed
//              << elapsed_secs
//              << " seconds."
//              << STR(EOL)
//              END_MSG;
//    // =========================================================================
   
  } else {
    ERROR_MSG << STR(CALCULATION_NOT_FOUND) END_MSG;
  }
}

void CCMDRun::Finalize() {
  /// Clean the command to reuse it later:
  set_name("");
  prepare_ = false;
  calculate_ = false;
  finalize_ = false;
  
  DM_DEL_ALL_LOCAL_DATA
}
