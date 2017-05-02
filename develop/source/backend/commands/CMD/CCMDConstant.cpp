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
 *  \brief     CCMDConstant.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Aug 3, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDConstant.h"

#include <string>

#include "../../data_manager/CDataManager.h"
#include "../../language/CStringTable.h"
#include "../../util/CStringTools.h"
#include "../../data_manager/common/CDataAccess.h"
#include "../../instructions/CController.h"

CCMDConstant::CCMDConstant()
  : ICommand(CMD_CONSTANT,                                                      // Command Name
             CMD_CONSTANT_ABB,                                                  // Command Abbreviation Name
             CMD_CONSTANT_DESC,                                                 // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also    
}

CCMDConstant::~CCMDConstant() {
}

void CCMDConstant::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    CONSTANT_NAME_SHORT,                                        // Short Name
                    CONSTANT_NAME_LONG,                                         // Long Name
                    CONSTANT_NAME_DESC,                                         // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    CONSTANT_BY_SHORT,                                          // Short Name
                    CONSTANT_BY_LONG,                                           // Long Name
                    CONSTANT_BY_DESC,                                           // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDConstant::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::CONSTANT_NAME_SHORT:
      constant_name_ = arguments;
      break;
    case KeyString::CONSTANT_BY_SHORT:
      translate_by_ = arguments;
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

void CCMDConstant::Run() {
  manager()->instructions_controller()->AddConstant(constant_name_,
                                                    translate_by_);
}

void CCMDConstant::Finalize() {
  /// Clean the command to reuse it later:
  constant_name_ = "";
  translate_by_ = "";
  
  DM_DEL_ALL_LOCAL_DATA
}
