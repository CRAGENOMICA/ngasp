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
 *  \brief     CCMDDelete.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 28, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDDelete.h"

#include <string>

#include "../../language/CStringTable.h"
#include "../../data_manager/CDataManager.h"
#include "../../calculations/CAllCalculations.h"

CCMDDelete::CCMDDelete()
  : ICommand(CMD_DELETE,                                                        // Command Name
             CMD_DELETE_ABB,                                                    // Command Abbreviation Name
             CMD_DELETE_DESC,                                                   // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also    
}

CCMDDelete::~CCMDDelete() {
}

void CCMDDelete::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    DELETE_DATA_VNAME_SHORT,                                    // Short Name
                    DELETE_DATA_VNAME_LONG,                                     // Long Name
                    DELETE_DATA_VNAME_DESC,                                     // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDDelete::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::DELETE_DATA_VNAME_SHORT:
      set_data_name_to_delete(arguments);
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

/*
 * User can only create ROOT_PARENT variables / calculations, so this command
 * only deletes ROOT_PARENT variables / calculations.
 */
void CCMDDelete::Run() {
  if (data_name_to_delete() != "") {
    if (data_name_to_delete().find(STR(RESERVED_DATA_NAME_PREFIX)) == 0) {
      WARNING_MSG << STR(DELETE_DATA_RESERVED_NAME) END_MSG;
    } else {     
      if (manager()->data_manager()->RemoveDataByName(ROOT_PARENT, data_name_to_delete())
          == false) {
        if (manager()->all_calculations()->
                        RemoveCalculationByName(ROOT_PARENT, data_name_to_delete()) == false) {
          WARNING_MSG << STR(VARIABLE_NOT_FOUND) END_MSG;
        }
      }
    }
  }
}

void CCMDDelete::Finalize() {
  /// Clean the command to reuse it later:
  DM_DEL_ALL_LOCAL_DATA
}
