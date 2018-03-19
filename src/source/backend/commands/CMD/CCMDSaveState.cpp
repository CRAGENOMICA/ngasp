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
 *  \brief     CCMDSaveState.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 12, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDSaveState.h"

#include <string>

#include "../../language/CStringTable.h"
#include "../../data_manager/CDataManager.h"

CCMDSaveState::CCMDSaveState()
  : ICommand(CMD_SAVE_STATE,                                                    // Command Name
             CMD_SAVE_STATE_ABB,                                                // Command Abbreviation Name
             CMD_SAVE_STATE_DESC,                                               // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  file_to_ = STR(DM_FILE_NAME);
}

CCMDSaveState::~CCMDSaveState() {
}

void CCMDSaveState::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    SAVE_STATE_TO_FILE_SHORT,                                   // Short Name
                    SAVE_STATE_TO_FILE_LONG,                                    // Long Name
                    SAVE_STATE_TO_FILE_DESC,                                    // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDSaveState::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::SAVE_STATE_TO_FILE_SHORT:
      file_to_ = arguments;
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

/**
 * THIS COMMAND IS ALREADY FINISHED.
 */
void CCMDSaveState::Run() {
  manager()->data_manager()->SaveState(file_to_); 
}

void CCMDSaveState::Finalize() {
  /// Clean the command to reuse it later:
  file_to_ = STR(DM_FILE_NAME);
  
  DM_DEL_ALL_LOCAL_DATA
}
