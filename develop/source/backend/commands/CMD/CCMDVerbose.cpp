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
 *  \brief     CCMDVerbose.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 8, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDVerbose.h"

#include <iostream>
#include <string>

#include "../../language/CStringTable.h"
#include "../../data_manager/CDataManager.h"

CCMDVerbose::CCMDVerbose()
  : ICommand(CMD_VERBOSE,                                                       // Command Name
             CMD_VERBOSE_ABB,                                                   // Command Abbreviation Name
             CMD_VERBOSE_DESC,                                                  // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  set_log_verbose_level(CLogger::LogMode::NORMAL_MODE);
}

CCMDVerbose::~CCMDVerbose() {
}

void CCMDVerbose::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    VERBOSE_LEVEL_SHORT,                                        // Short Name
                    VERBOSE_LEVEL_LONG,                                         // Long Name
                    VERBOSE_LEVEL_DESC,                                         // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDVerbose::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::VERBOSE_LEVEL_SHORT:
      if (arguments == STR(VERBOSE_LEVEL_SILENT)) {
        set_log_verbose_level(CLogger::LogMode::SILENT_MODE);
      } else {
        if (arguments == STR(VERBOSE_LEVEL_NORMAL)) {
          set_log_verbose_level(CLogger::LogMode::NORMAL_MODE);
        } else {
          if (arguments == STR(VERBOSE_LEVEL_DEBUG)) {
            set_log_verbose_level(CLogger::LogMode::DEBUG_MODE);
          } else {
            // It is an error. The execution of this command must stop.
            ERROR_MSG << STR(VERBOSE_LEVEL_UNKNOWN) END_MSG;
            parseResult = false;
          }
        }
      }
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

void CCMDVerbose::Run() {
  manager()->logger()->set_mode(log_verbose_level());
  std::cout << STR(VERBOSE_TITLE);
  std::cout << manager()->logger()->mode_str();
  std::cout << std::endl;
}

void CCMDVerbose::Finalize() {
  /// Clean the command to reuse it later:
  set_log_verbose_level(CLogger::LogMode::NORMAL_MODE);
  
  DM_DEL_ALL_LOCAL_DATA
}
