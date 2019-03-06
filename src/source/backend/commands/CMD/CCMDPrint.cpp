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
 *  \brief     CCMDPrint.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 6, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDPrint.h"

#include <string>
#include <iostream>

// SLEEP functions:
#include <thread>         // std::thread
#include <chrono>         // std::chrono::seconds
#include <mutex>          // std::mutex


#include "../../IObject.h"
#include "../../language/CStringTable.h"
#include "../../data_manager/CDataManager.h"
#include "../../data_manager/common/CDataAccess.h"

CCMDPrint::CCMDPrint()
  : ICommand(CMD_PRINT,                                                         // Command Name
             CMD_PRINT_ABB,                                                     // Command Abbreviation Name
             CMD_PRINT_DESC,                                                    // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  data_access_ = new CDataAccess();
  set_text("");
  set_print_mode(PrintMode::NORMAL);
  set_eol(false);
}

CCMDPrint::~CCMDPrint() {
  if (data_access_ != NULL) {
    delete data_access_;
    data_access_ = NULL;
  }
}

void CCMDPrint::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    PRINT_NAME_SHORT,                                           // Short Name
                    PRINT_NAME_LONG,                                            // Long Name
                    PRINT_NAME_DESC,                                            // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    PRINT_TEXT_SHORT,                                           // Short Name
                    PRINT_TEXT_LONG,                                            // Long Name
                    PRINT_TEXT_DESC,                                            // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    PRINT_MODE_SHORT,                                           // Short Name
                    PRINT_MODE_LONG,                                            // Long Name
                    PRINT_MODE_DESC,                                            // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    PRINT_EOL_SHORT,                                            // Short Name
                    PRINT_EOL_LONG,                                             // Long Name
                    PRINT_EOL_DESC,                                             // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_no_argument,                                        // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDPrint::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::PRINT_NAME_SHORT:
      data_access_->Set(manager(), arguments);
      if (data_access_->data_object() == NULL) {
        parseResult = false;
        ERROR_MSG << arguments << STR(SPACE)
                  << STR(VARIABLE_NOT_FOUND)
                  END_MSG;
      }
      break;
    case KeyString::PRINT_TEXT_SHORT:
      set_text(arguments);
      break;
    case KeyString::PRINT_MODE_SHORT:
      set_print_mode(arguments);
      break;
    case KeyString::PRINT_EOL_SHORT:
      set_eol(true);
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

void CCMDPrint::Run() {
  
  // std::this_thread::sleep_for (std::chrono::milliseconds(100));
  
  if (text() != "") {
    std::string message = text();
    if (message.at(0) == '\"') {
      message = message.substr(1);
    }
    if (message.at(message.length()-1) == '\"') {
      message = message.substr(0, message.length()-1);
    }

    CStringTools::Replace(message, "\\n", "\n");

    std::cout << message;
  }

  /**
   * Print the specified object:
   */
  if (data_access_->data_object() != NULL) {
    if (print_mode()==PrintMode::JSON) {
      std::cout << data_access_->data_object()->ToJSON();
    } else {
      data_access_->data_object()->Print(print_mode());
    }
  } else {
    /**
     * If no object has been specified then print the selected one:
     *
     * Better not. Because if I want to print a text only I can't.
     */
//    if (manager()->with() != NULL) {
//      manager()->with()->Print();
//    }
  }

  if (eol()) {
    std::cout << std::endl;
  }
}

void CCMDPrint::Finalize() {
  /// Clean the command to reuse it later:
  set_text("");
  data_access_->Clear();
  set_print_mode(PrintMode::NORMAL);
  set_eol(false);
  
  DM_DEL_ALL_LOCAL_DATA
}

