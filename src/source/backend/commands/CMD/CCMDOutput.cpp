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
 *  \brief     CCMDOutput.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 18, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDOutput.h"
#include "../../language/CStringTable.h"
#include "../../instructions/CController.h"
#include "../../data_manager/CDataManager.h"

CCMDOutput::CCMDOutput()
  : ICommand(CMD_OUTPUT,                                                        // Command Name
             CMD_OUTPUT_ABB,                                                    // Command Abbreviation Name
             CMD_OUTPUT_DESC,                                                   // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  name_ = "";
}

CCMDOutput::~CCMDOutput() {
}

void CCMDOutput::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    OUTPUT_FILE_NAME_SHORT,                                     // Short Name
                    OUTPUT_FILE_NAME_LONG,                                      // Long Name
                    OUTPUT_FILE_NAME_DESC,                                      // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    OUTPUT_SCREEN_SHORT,                                        // Short Name
                    OUTPUT_SCREEN_LONG,                                         // Long Name
                    OUTPUT_SCREEN_DESC,                                         // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_no_argument,                                        // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDOutput::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::OUTPUT_FILE_NAME_SHORT:
      name_ = arguments;
      break;
    case KeyString::OUTPUT_SCREEN_SHORT:
      name_ = "";
      break;
    default:
      parseResult = false;
      break;
    }
  }

  parseResult = CheckOptions() && parseResult;

  return parseResult;
}

void CCMDOutput::Run() {
  if (name() == "") {
    manager()->RedirectCoutToScreenAgain();
  } else {
    manager()->RedirectCoutToFile(name());
  }
}

void CCMDOutput::Finalize() {
  /// Clean the command to reuse it later:
  name_ = "";
  
  DM_DEL_ALL_LOCAL_DATA
}
