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
 *  \brief     CCMDPipe.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Dec 10, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDPipe.h"
#include "../../language/CStringTable.h"
#include "../../instructions/CController.h"
#include "../../data_manager/CDataManager.h"

CCMDPipe::CCMDPipe()
  : ICommand(CMD_PIPE,                                                          // Command Name
             CMD_PIPE_ABB,                                                      // Command Abbreviation Name
             CMD_PIPE_DESC,                                                     // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  name_ = "";
}

CCMDPipe::~CCMDPipe() {
}

void CCMDPipe::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    PIPE_NAME_SHORT,                                            // Short Name
                    PIPE_NAME_LONG,                                             // Long Name
                    PIPE_NAME_DESC,                                             // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDPipe::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::PIPE_NAME_SHORT:
      name_ = arguments;
      break;
    default:
      parseResult = false;
      break;
    }
  }

  parseResult = CheckOptions() && parseResult;

  return parseResult;
}

void CCMDPipe::Run() {
  /// Set the name of the pipe to be used
  /// -----------------------------------
  
  manager()->instructions_controller()->named_pipe_.SetPipes(name());
  
  
  /// Redirect all the output to this file
  /// ------------------------------------
  
  std::string output_file_name = STR(TEMP_FOLDER);
  output_file_name += STR(PRE_OUTPUT_NAME);
  output_file_name += name();
  output_file_name += STR(OUTPUT_EXTENSION);

  COutputDescriptor * od = new COutputDescriptor(true);
  od->name_ = output_file_name;
  od->description_ = "bin_output";
  manager()->logger()->SetNewOutputDescriptor(od);
}

void CCMDPipe::Finalize() {
  /// Clean the command to reuse it later:
  name_ = "";
  
  DM_DEL_ALL_LOCAL_DATA
}
