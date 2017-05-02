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
 *  \brief     CCMDLog.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 8, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDLog.h"

#include <iostream>
#include <string>
#include <list>

#include "../../language/CStringTable.h"
#include "../../instructions/CController.h"
#include "../../util/CFile.h"
#include "../../data_manager/CDataManager.h"

CCMDLog::CCMDLog()
  : ICommand(CMD_LOG,                                                           // Command Name
             CMD_LOG_ABB,                                                       // Command Abbreviation Name
             CMD_LOG_DESC,                                                      // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  set_action(logAction::UNKNOWN);
}

CCMDLog::~CCMDLog() {
}

void CCMDLog::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    // logAction::CLEAR
    // log -c
    // log --clear
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    LOG_CLEAR_SHORT,                                            // Short Name
                    LOG_CLEAR_LONG,                                             // Long Name
                    LOG_CLEAR_DESC,                                             // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_no_argument,                                        // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION

  // logAction::LIST
  // log
}

bool CCMDLog::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::LOG_CLEAR_SHORT:
      set_action(logAction::CLEAR);
      break;
    default:
      parseResult = false;
      break;
    }
  }

  if ((action() == logAction::UNKNOWN) && (parseResult == true)) {
    set_action(logAction::LIST);
  }

  return (CheckOptions() && parseResult);
}

void CCMDLog::Run() {
  switch (action()) {
  case logAction::LIST:
    std::cout << manager()->logger()->ReadLogFile();
    break;
  case logAction::CLEAR:
    manager()->logger()->ClearLogFile();
    break;
  case logAction::UNKNOWN:
    break;
  }
}

void CCMDLog::Finalize() {
  /// Clean the command to reuse it later:
  set_action(logAction::UNKNOWN);
  
  DM_DEL_ALL_LOCAL_DATA
}

