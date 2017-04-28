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
 *  \brief     CCMDExec.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Mar 8, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDExec.h"

#include <string>
#include <cstring>

#include "../../language/CStringTable.h"
#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../commands/CAllCommands.h"

#include "../../calculations/CCalcFactory.h"
#include "../../calculations/ICalculation.h"
#include "../../calculations/Calc/CCalcExec.h"

CCMDExec::CCMDExec()
  : ICommand(CMD_EXEC,                                                          // Command Name
             CMD_EXEC_ABB,                                                      // Command Abbreviation Name
             CMD_EXEC_DESC,                                                     // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also  
  set_command("");
  set_working_directory("");
  set_type("");
}

CCMDExec::~CCMDExec() {
}

void CCMDExec::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    EXEC_APP_SHORT,                                            // Short Name
                    EXEC_APP_LONG,                                             // Long Name
                    EXEC_APP_DESC,                                             // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    EXEC_WORKING_DIR_SHORT,                                     // Short Name
                    EXEC_WORKING_DIR_LONG,                                      // Long Name
                    EXEC_WORKING_DIR_DESC,                                      // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    EXEC_TYPE_SHORT,                                            // Short Name
                    EXEC_TYPE_LONG,                                             // Long Name
                    EXEC_TYPE_DESC,                                             // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDExec::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::EXEC_APP_SHORT:
      set_command(arguments);
      break;
    case KeyString::EXEC_WORKING_DIR_SHORT:
      set_working_directory(arguments);
      break;
    case KeyString::EXEC_TYPE_SHORT:
      set_type(arguments);
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

void CCMDExec::Run() {
  /// CREATE CALC AND DATAS FOR THE CALCULATION
 
  CCalcExec *calc_execute = NULL;
  DM_NEW_CALC(calc_execute)
  
  CDataStdString *the_command = NULL;
  DM_NEW_DATA(the_command)
  the_command->set_value(command());
    
  CDataStdString *the_working_directory = NULL;
  DM_NEW_DATA(the_working_directory)
  the_working_directory->set_value(working_directory());
    
  CDataStdString *the_type = NULL;
  DM_NEW_DATA(the_type)
  the_type->set_value(type());
    
  CDataInt *the_result = (CDataInt *)manager()->data_manager()->GetDataByName(ROOT_PARENT, STR(RESULT));  // This is a global variable. So, its parent is ROOT_PARENT.
  
  /// ==========================================================================
  /// EXECUTE EXTERNAL APPLICATION OR SYSTEM COMMAND
  /// ==========================================================================
  calc_execute->SetInput(the_command);
  calc_execute->SetInput(the_working_directory);
  calc_execute->SetInput(the_type);
  calc_execute->SetOutput(the_result);
  calc_execute->Prepare();
  calc_execute->Calculate(manager()->all_commands()->dry_run());
  calc_execute->Finalize();
  /// ==========================================================================

  /// REMOVE CALC AND "DATAS" CREATED ONLY FOR THIS CALCULATION
  
  DM_DEL_CALC(calc_execute)
  DM_DEL_DATA(the_command)
  DM_DEL_DATA(the_working_directory)
  DM_DEL_DATA(the_type)
}

void CCMDExec::Finalize() {
  /// Clean the command to reuse it later:
  set_command("");
  set_working_directory("");
  set_type("");
  
  DM_DEL_ALL_LOCAL_DATA
}
