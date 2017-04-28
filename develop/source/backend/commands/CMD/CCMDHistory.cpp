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
 *  \brief     CCMDHistory.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 29, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDHistory.h"

#include <iostream>
#include <string>
#include <list>

#include "../../language/CStringTable.h"
#include "../../instructions/CController.h"
#include "../../instructions/CInstructionsHistory.h"
#include "../../data_manager/CDataManager.h"

CCMDHistory::CCMDHistory()
  : ICommand(CMD_HISTORY,                                                       // Command Name
             CMD_HISTORY_ABB,                                                   // Command Abbreviation Name
             CMD_HISTORY_DESC,                                                  // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  set_action(HistoryAction::UNKNOWN);
  set_action_num_to_run(0);
}

CCMDHistory::~CCMDHistory() {
}

void CCMDHistory::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    // HistoryAction::CLEAR
    // history -c
    // history --clear
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    HISTORY_CLEAR_SHORT,                                        // Short Name
                    HISTORY_CLEAR_LONG,                                         // Long Name
                    HISTORY_CLEAR_DESC,                                         // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_no_argument,                                        // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    // HistoryAction::RUN
    // history -r 3
    // history --run 3
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    HISTORY_RUN_SHORT,                                          // Short Name
                    HISTORY_RUN_LONG,                                           // Long Name
                    HISTORY_RUN_DESC,                                           // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION

  // HistoryAction::LIST
  // history
}

bool CCMDHistory::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::HISTORY_CLEAR_SHORT:
      set_action(HistoryAction::CLEAR);
      break;
    case KeyString::HISTORY_RUN_SHORT:
      set_action(HistoryAction::RUN);
      set_action_num_to_run(atol(arguments.c_str()));
      break;
    default:
      parseResult = false;
      break;
    }
  }

  if ((action() == HistoryAction::UNKNOWN) && (parseResult == true)) {
    set_action(HistoryAction::LIST);
  }

  return (CheckOptions() && parseResult);
}

void CCMDHistory::Run() {
  int instruction_number = 1;
  CInstructionsHistory *history =
      manager()->instructions_controller()->history();

  std::string instruction;

  switch (action()) {
  case HistoryAction::LIST:
    for (std::list<std::string>::iterator it = history->instructions()->begin();
         it != history->instructions()->end();
         ++it) {
      std::cout << STR(IDENTATION);
      std::cout << instruction_number;
      std::cout << STR(IDENTATION);
      std::cout << (*it);
      std::cout << STR(EOL);
      instruction_number++;
    }
    break;
  case HistoryAction::CLEAR:
    history->ClearHistoryFromFile();
    break;
  case HistoryAction::RUN:
    instruction += STR(NGASP_APP_EXECUTABLE_NAME);
    instruction += STR(SPACE);
    instruction += history->GetInstruction(action_num_to_run());
    manager()->instructions_controller()->pushInstruction(instruction);
    break;
  case HistoryAction::UNKNOWN:
    break;
  }
}

void CCMDHistory::Finalize() {
  /// Clean the command to reuse it later:
  set_action(HistoryAction::UNKNOWN);
  set_action_num_to_run(0);
  
  DM_DEL_ALL_LOCAL_DATA
}

