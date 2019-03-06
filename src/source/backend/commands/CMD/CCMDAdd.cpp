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
 *  \brief     CCMDAdd.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 18, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDAdd.h"

#include <string>
#include <cstring>

#include "../../language/CStringTable.h"
#include "../../data_manager/CDataManager.h"
// #include "../../calculations/CAllCalculations.h"

CCMDAdd::CCMDAdd()
  : ICommand(CMD_ADD,                                                           // Command Name
             CMD_ADD_ABB,                                                       // Command Abbreviation Name
             CMD_ADD_DESC,                                                      // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also  
    set_input_file("");
    set_name("");
    set_num_regs(-1);
}

CCMDAdd::~CCMDAdd() {
}

void CCMDAdd::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    ADD_FILE_NAME_SHORT,                                        // Short Name
                    ADD_FILE_NAME_LONG,                                         // Long Name
                    ADD_FILE_NAME_DESC,                                         // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    ADD_NAME_SHORT,                                             // Short Name
                    ADD_NAME_LONG,                                              // Long Name
                    ADD_NAME_DESC,                                              // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required

    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    ADD_NUM_REGS_SHORT,                                         // Short Name
                    ADD_NUM_REGS_LONG,                                          // Long Name
                    ADD_NUM_REGS_DESC,                                          // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required  
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDAdd::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::ADD_FILE_NAME_SHORT:
      set_input_file(arguments);
      break;
    case KeyString::ADD_NAME_SHORT:
      set_name(arguments);
      break;
    case KeyString::ADD_NUM_REGS_SHORT:
      set_num_regs(atol(arguments.c_str()));
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

void CCMDAdd::Run() {
  std::cout << "Obsolete command..." << std::endl;
}

void CCMDAdd::Finalize() {
  /// Clean the command to reuse it later:
  DM_DEL_ALL_LOCAL_DATA
}
