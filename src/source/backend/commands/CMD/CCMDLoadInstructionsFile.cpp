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
 *  \brief     CCMDLoadInstructionsFile.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      March 30, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#include "CCMDLoadInstructionsFile.h"

#include <string>
#include <fstream>

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"
#include "../../instructions/CController.h"
#include "../../instructions/CFromYaml.h"
#include "../../data_manager/CDataManager.h"

CCMDLoadInstructionsFile::CCMDLoadInstructionsFile()
  : ICommand(CMD_LOAD_FILE,                                                     // Command Name
             CMD_LOAD_FILE_ABB,                                                 // Command Abbreviation Name
             CMD_LOAD_FILE_DESC,                                                // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  set_format(InstructionsFileType::CMD_INSTRUCTIONS_FILE);
  set_file_name("");
  set_values_file_name("");
}

CCMDLoadInstructionsFile::~CCMDLoadInstructionsFile() {
}

void CCMDLoadInstructionsFile::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    LOAD_OPE_FILE_SHORT,                                        // Short Name
                    LOAD_OPE_FILE_LONG,                                         // Long Name
                    LOAD_OPE_FILE_DESC,                                         // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required

    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    LOAD_OPE_FILE_INPUTS_SHORT,                                 // Short Name
                    LOAD_OPE_FILE_INPUTS_LONG,                                  // Long Name
                    LOAD_OPE_FILE_INPUTS_DESC,                                  // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    LOAD_OPE_FILE_FORMAT_SHORT,                                 // Short Name
                    LOAD_OPE_FILE_FORMAT_LONG,                                  // Long Name
                    LOAD_OPE_FILE_FORMAT_DESC,                                  // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDLoadInstructionsFile::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::LOAD_OPE_FILE_FORMAT_SHORT:
      if (arguments == STR(FORMAT_YAML)) {
        set_format(YAML_INSTRUCTIONS_FILE);
      } else {
        if (arguments == STR(FORMAT_NGASP)) {
          set_format(CMD_INSTRUCTIONS_FILE);
        } else {
          parseResult = false;
        }
      }
      break;
    case KeyString::LOAD_OPE_FILE_SHORT:
      this->set_file_name(arguments);
      break;
    case KeyString::LOAD_OPE_FILE_INPUTS_SHORT:
      this->set_values_file_name(arguments);
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

void CCMDLoadInstructionsFile::TreatCFile(std::string ngasp_code, bool valfile) {
  std::string line;
  std::string line_start_char;
  std::string instruction_string;

  while (ngasp_code != "") {
    line = CStringTools::GetString(ngasp_code, tPosition::GET_LEFT, '\n');
    ngasp_code = CStringTools::GetString(ngasp_code, tPosition::GET_RIGHT, '\n');

    if (line != "") {
      // Remove all tabs and spaces from the beginning of the line:
      while ((line != "") && ((line[0] == ' ') || (line[0] == '\t'))) {
        line = line.substr(1);
      }

      line_start_char = line[0];
      if (line_start_char != STR(LINE_COMMENT_TAG)) {
        instruction_string += line;

        if ((instruction_string.length() > 2) &&
            (instruction_string.at(instruction_string.length()-2) == STR(SPACE)[0]) &&
            (instruction_string.at(instruction_string.length()-1) == STR(CONTINUE_LINE)[0])
        ) {
          // Remove only the CONTINUE_LINE character, not the space one.
          // In order to keep an space between this line and the next one.
          // Remember that the code above will remove all tabs and spaces of
          // the next line.
          instruction_string = instruction_string.substr(0,
                               instruction_string.length()-1);
        } else {
          // ...............................................................
          // IDENTICAL CODE
          // ...............................................................
          if ((instruction_string == STR(INCLUDE_VALUES)) && (valfile == false)) {
            std::string values_code;
            // CFile values_file(values_file_name());
            CFromYaml from_yaml;

            switch (format()) {
              case InstructionsFileType::YAML_INSTRUCTIONS_FILE:
                values_code = from_yaml.ToNgasp(values_file_name());
                break;
              case InstructionsFileType::UNDEFINED:
              case InstructionsFileType::CMD_INSTRUCTIONS_FILE:
              default:
                //if (values_file.Open() == true) {
                  // values_code = values_file.ReadAll();
                if (CFile::ReadAll(values_file_name(), values_code) == false) {
                  ERROR_MSG << STR(LOAD_OPE_FILE_NOT_FOUND) END_MSG;
                }
                break;
            }

            TreatCFile(values_code, true);
            instruction_string = "";
          }
          else {
            SendInstruction(instruction_string);
          }
          // ...............................................................
        }
      }
    }
  }

  // ...............................................................
  // IDENTICAL CODE
  // ...............................................................
  if ((instruction_string == STR(INCLUDE_VALUES)) && (valfile == false)) {
    std::string values_code;
    // CFile values_file(values_file_name());
    CFromYaml from_yaml;

    switch (format()) {
      case InstructionsFileType::YAML_INSTRUCTIONS_FILE:
        values_code = from_yaml.ToNgasp(values_file_name());
        break;
      case InstructionsFileType::UNDEFINED:
      case InstructionsFileType::CMD_INSTRUCTIONS_FILE:
      default:
        //if (values_file.Open() == true) {
          // values_code = values_file.ReadAll();
        if (CFile::ReadAll(values_file_name(), values_code) == false) {
          ERROR_MSG << STR(LOAD_OPE_FILE_NOT_FOUND) END_MSG;
        }
        break;
    }

    TreatCFile(values_code, true);
    instruction_string = "";
  }
  else {
    SendInstruction(instruction_string);
  }
  // ...............................................................

//  if (instruction_string != "") {
//    // ...............................................................
//    // IDENTICAL CODE
//    // ...............................................................
//    if ((instruction_string == STR(INCLUDE_VALUES)) && (valfile == false)) {
//      CFile values_file(values_file_name());
//      TreatCFile(&values_file, true);
//      instruction_string = "";
//    } else {
//      SendInstruction(instruction_string);
//    }
//    // ...............................................................
//  }
}

void CCMDLoadInstructionsFile::Run() {
  //CFile instructions_file(file_name());
  CFromYaml from_yaml;
  std::string ngasp_code;

  switch (format()) {
    case InstructionsFileType::YAML_INSTRUCTIONS_FILE:
      ngasp_code = from_yaml.ToNgasp(file_name());
      break;
    case InstructionsFileType::UNDEFINED:
    case InstructionsFileType::CMD_INSTRUCTIONS_FILE:
    default:
      //if (instructions_file.Open() == true) {
       // ngasp_code = instructions_file.ReadAll();
       if (CFile::ReadAll(file_name(), ngasp_code) == false) {
        ERROR_MSG << STR(LOAD_OPE_FILE_NOT_FOUND) END_MSG;
      }
      break;
  }

//  std::cout << ngasp_code << std::endl;
  TreatCFile(ngasp_code, false);
}

void CCMDLoadInstructionsFile::SendInstruction(std::string & instruction_str) {
  instruction_str = STR(NGASP_APP_EXECUTABLE_NAME) +
                       STR(SPACE) +
                       instruction_str;

  manager()->instructions_controller()->pushInstruction(instruction_str);

  instruction_str = "";
}

void CCMDLoadInstructionsFile::Finalize() {
  /// Clean the command to reuse it later:
  set_format(InstructionsFileType::CMD_INSTRUCTIONS_FILE);
  set_file_name("");
  set_values_file_name("");
  
  DM_DEL_ALL_LOCAL_DATA
}


