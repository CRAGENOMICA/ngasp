/*
 * ngasp, a computational solution for performing next generation analysis of 
 * sequence polymorphisms using NGS data.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
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
/**
 *  \brief     CCMDWith.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 6, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDWith.h"

#include "../../data_manager/CDataManager.h"

CCMDWith::CCMDWith()
  : ICommand(CMD_WITH,                                                          // Command Name
             CMD_WITH_ABB,                                                      // Command Abbreviation Name
             CMD_WITH_DESC,                                                     // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also  
  set_name("");
}

CCMDWith::~CCMDWith() {
}

void CCMDWith::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    WITH_NAME_SHORT,                                            // Short Name
                    WITH_NAME_LONG,                                             // Long Name
                    WITH_NAME_DESC,                                             // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDWith::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::WITH_NAME_SHORT:
      set_name(arguments);
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

void CCMDWith::Run() {
  /*
   * User can only create ROOT_PARENT variables, so this command
   * only reserves selects ROOT_PARENT variables.
   */  
  manager()->set_with(name());
}

void CCMDWith::Finalize() {
  /// Clean the command to reuse it later:
  set_name("");
  
  DM_DEL_ALL_LOCAL_DATA
}

