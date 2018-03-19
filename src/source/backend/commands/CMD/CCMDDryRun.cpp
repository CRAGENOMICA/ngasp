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
 *  \brief     CCMDDryRun.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 13, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDDryRun.h"

#include <string>

#include "../../language/CStringTable.h"
#include "../CAllCommands.h"
#include "../../data_manager/CDataManager.h"

CCMDDryRun::CCMDDryRun()
  : ICommand(CMD_DRY_RUN,                                                       // Command Name
             CMD_DRY_RUN_ABB,                                                   // Command Abbreviation Name
             CMD_DRY_RUN_DESC,                                                  // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also  
  set_dry_run_mode(false);
}

CCMDDryRun::~CCMDDryRun() {
}

void CCMDDryRun::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    DRY_RUN_SET_SHORT,                                          // Short Name
                    DRY_RUN_SET_LONG,                                           // Long Name
                    DRY_RUN_SET_DESC,                                           // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDDryRun::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::DRY_RUN_SET_SHORT:
      if (arguments == "true") {
        set_dry_run_mode(true);
      } else {
        if (arguments == "false") {
          set_dry_run_mode(false);
        } else {
          // It is an error. The execution of this command must stop.
          ERROR_MSG << STR(DRY_RUN_SET_UNKNOWN) END_MSG;
          parseResult = false;
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

void CCMDDryRun::Run() {
  manager()->all_commands()->set_dry_run(dry_run_mode());

  if (manager()->all_commands()->dry_run()) {
    DEBUG_MSG << "Dry run enabled." END_MSG;
  } else {
    DEBUG_MSG << "Dry run disabled." END_MSG;   
  }
}

void CCMDDryRun::Finalize() {
  /// Clean the command to reuse it later:
  DM_DEL_ALL_LOCAL_DATA
}
