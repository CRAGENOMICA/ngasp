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
 *  \brief     CCMDAppHelp.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 8, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include <iostream>

#include <list>
#include <string>

#include "CCMDAppHelp.h"
#include "../../language/CStringTable.h"
#include "../CAllCommands.h"
#include "CCMDDim.h"
#include "CCMDCalc.h"
#include "../../data_manager/CDataManager.h"
#include "../../calculations/CAllCalculations.h"

#include "../ICommand.h"
#include "../../calculations/ICalculation.h"
#include "../../IFunction.h"

CCMDAppHelp::CCMDAppHelp()
  : ICommand(CMD_APP_HELP,                                                      // Command Name
             CMD_APP_HELP_ABB,                                                  // Command Abbreviation Name
             CMD_APP_HELP_DESC,                                                 // Brief Description
             MSTATSPOP_DESC,                                                    // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also
  set_name("");
  set_output_format(STR2(KeyString::PRINT_MODE_NORMAL));
}

CCMDAppHelp::~CCMDAppHelp() {
}

void CCMDAppHelp::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    CMD_APP_HELP_CMD_SHORT,                                     // Short Name
                    CMD_APP_HELP_CMD_LONG,                                      // Long Name
                    CMD_APP_HELP_CMD_DESC,                                      // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_MENU,                                                  // Data Type
                    CMD_APP_HELP_FORMAT_SHORT,                                  // Short Name
                    CMD_APP_HELP_FORMAT_LONG,                                   // Long Name
                    CMD_APP_HELP_FORMAT_DESC,                                   // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_VALUE_INFO(PRINT_MODE_NORMAL,                                           // Value
                   PRINT_MODE_NORMAL,                                           // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // only
                   true)                                                        // Default Value
  
    SET_VALUE_INFO(PRINT_MODE_HTML,                                             // Value
                   PRINT_MODE_HTML,                                             // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // only
                   false)                                                       // Default Value
  END_COMMAND_INTERFACE_DEFINITION
}


bool CCMDAppHelp::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::CMD_APP_HELP_CMD_SHORT:
      set_name(arguments);
      break;
    case KeyString::CMD_APP_HELP_FORMAT_SHORT:
      set_output_format(arguments);
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

#define SCREEN_WIDTH 80

std::string CCMDAppHelp::PrepareText(int start_column,
                                     std::string input_text,
                                     int start_column_remaining_lines) {

  CStringTools::Replace(input_text, "\n", "");

  std::string output_text = input_text.substr(0, SCREEN_WIDTH - start_column) + STR(EOL);
  if ((signed)input_text.length() > (SCREEN_WIDTH - start_column)) {
    input_text = input_text.substr(SCREEN_WIDTH - start_column);
  } else {
    input_text = "";
  }

  if (input_text != "") {
    std::string first_spaces;
    for (int i = 0; i < start_column_remaining_lines; i++) {
      first_spaces += STR(SPACE);
    }

    while (input_text != "") {
        input_text = first_spaces + input_text;

        output_text = output_text + input_text.substr(0, SCREEN_WIDTH) + STR(EOL);
        if (input_text.length() > SCREEN_WIDTH) {
          input_text = input_text.substr(SCREEN_WIDTH);
        } else {
          input_text = "";
        }
    }
  }

  return output_text;
}



// Remove:
// HELP_COMMAND_LINE

void CCMDAppHelp::Run() {
  std::string line;
  OutputEncoding previous_encoding = OutputEncoding::UNDEFINED_ENCODING;
  
  if (output_format() == STR2(KeyString::PRINT_MODE_HTML)) {
    previous_encoding = CStringTable::Instance()->encoding();
    CStringTable::Instance()->set_encoding(OutputEncoding::ENGLISH_HTML);
  }
  
  /// Help
  std::cout << STR(EOL);

  if (name() == "")   {
    ShowCommandHelp(this, true);
  }
  else {
    bool found = false;
    std::list<ICommand *>::iterator cmd;
    for (cmd = this->manager()->all_commands()->GetFirstCommandIterator();
      ((cmd != manager()->all_commands()->GetLastCommandIterator()) && (!found));
      cmd++) {
      found = (STR2((*cmd)->name()) == name());
      
      if (found) {
        ShowCommandHelp((*cmd), true);
      }
    }
    
    if (!found) {
      std::map<KeyString, ICalculation *>::iterator it;
      for (it = manager()->calc_factory()->data_map_.begin();
          ((it != manager()->calc_factory()->data_map_.end()) && (!found));
          ++it) {
        found =  (((*it).second)->name() == name());
        
        if (found) {
          ShowCommandHelp((*it).second, false);
        }
      }
      
      if (!found) {
        ShowCommandHelp(this, true);
      }
    }
  }
  
  if (previous_encoding != OutputEncoding::UNDEFINED_ENCODING) {
    CStringTable::Instance()->set_encoding(previous_encoding);
  }  
}

void CCMDAppHelp::Finalize() {
  /// Clean to reuse it later:
  set_name("");
  set_output_format(STR2(KeyString::PRINT_MODE_NORMAL));
  
  DM_DEL_ALL_LOCAL_DATA
}


std::string CCMDAppHelp::CreateCommandSynopsis(IFunction *cmd) {
  std::string synopsis;

  KeyString previous_group = KeyString::UNDEFINED_STRING;
  int opened_groups = 0;
  for (std::list<COption *>::iterator command_option =
       cmd->options()->GetFirstOptionIterator();
       command_option != cmd->options()->GetLastOptionIterator();
       command_option++ ) {

    if ((*command_option)->group() != previous_group) {
      if (opened_groups == 0) {
      }
      else {
        if (opened_groups == 1) {
          synopsis += "[";
        }
        else {
          // Remove last space. For example: "[-p] " to "[-p]"
          if ((synopsis != "") && (synopsis.at(synopsis.length()-1)==' ')) {
            synopsis = synopsis.substr(0, synopsis.length()-1);
          }
          synopsis += "]" + STR(SPACE) + "[";
        }
      }
      previous_group = (*command_option)->group();
      opened_groups++;
    }

    if ((*command_option)->opt_type() == COption::OPTTYPES::OPTTYPE_optional) {
      synopsis += "[";
    }
    synopsis += STR(PARAM) + (*command_option)->short_name();

    if ((*command_option)->arg_type() != COption::ARGTYPES::ARGTYPE_no_argument) {
      if ((*command_option)->data_type() == KeyString::DATA_FILE) {
        synopsis += STR(SPACE);
        synopsis += "file";
      } else {
        if ((*command_option)->data_type() == KeyString::DATA_ONE_VALUE) {
          synopsis += STR(SPACE);
          synopsis += "value";
        } else {
          if ((*command_option)->data_type() == KeyString::DATA_VALUES) {
            synopsis += STR(SPACE);
            synopsis += "values";
          } else {
            if((*command_option)->values()->size() > 0) {
              synopsis += STR(SPACE) + "(";
              for (std::list<CValue *>::iterator it = (*command_option)->values()->begin();
                   it != (*command_option)->values()->end(); ++it) {
                if (it != (*command_option)->values()->begin()) {
                  synopsis += "/";
                }
                synopsis += STR2((*it)->value());
              }
              synopsis += ")";
            }
          }
        }
      }
    }


    if ((*command_option)->opt_type() == COption::OPTTYPES::OPTTYPE_optional) {
      synopsis += "]";
    }
    synopsis += STR(SPACE);
  }

  if (opened_groups > 1) {
    // Remove last space. For example: "[-p] " to "[-p]"
    if ((synopsis != "") && (synopsis.at(synopsis.length()-1)==' ')) {
      synopsis = synopsis.substr(0, synopsis.length()-1);
    }
    synopsis += "]";
  }  
  
  return synopsis;
}

std::string CCMDAppHelp::IdentateLongTexts(const std::string & text) {
  std::string ret = text;
  CStringTools::Replace(ret, "\n", "\n" + STR(TAB6));
  return ret;
}

void CCMDAppHelp::ShowListOfCommandsAndCalculations(void) {
  std::string list;
  
  std::cout << STR(TAB6) << STR(BOLD_START) << "Commands:" << STR(BOLD_END) << STR(EOL);
  list = STR(TAB6);
  
  list += this->manager()->all_commands()->GetCommandsList();
  
  std::cout << list << STR(EOL) << STR(EOL);
 
  std::cout << STR(TAB6) << STR(BOLD_START) << "Calculations:" << STR(BOLD_END) << STR(EOL);
  list = STR(TAB6);
  
  list += this->manager()->calc_factory()->GetCalculationsList();

  std::cout << list << STR(EOL) << STR(EOL);
}

void CCMDAppHelp::ShowCommandHelp(IFunction *cmd, bool command) {
  std::cout << STR(BOLD_START) << STR(MAN_NAME) << STR(BOLD_END) << STR(EOL);
  std::cout << STR(TAB6) << STR2(cmd->function_name()) << STR(SPACE) << "-" << STR(SPACE) << STR2(cmd->brief_description());
  std::cout << STR(EOL) << STR(EOL);

  if (command) {
    std::cout << STR(BOLD_START) << STR(MAN_SYNOPSIS) << STR(BOLD_END) << STR(EOL);
    std::cout << STR(TAB6) << STR(BOLD_START) << STR2(cmd->function_name()) << STR(BOLD_END) << STR(SPACE) << CreateCommandSynopsis(cmd);
    std::cout << STR(EOL) << STR(EOL);
  }
  
  std::cout << STR(BOLD_START) << STR(MAN_DESCRIPTION) << STR(BOLD_END) << STR(EOL);
  std::cout << STR(TAB6) << IdentateLongTexts(STR2(cmd->description()));
  std::cout << STR(EOL);
  std::cout << STR(EOL);

  KeyString previous_group = KeyString::UNDEFINED_STRING;

  for (std::list<COption *>::iterator command_option =
       cmd->options()->GetFirstOptionIterator();
       command_option != cmd->options()->GetLastOptionIterator();
       command_option++ ) {

    if ((*command_option)->group() != previous_group) {
      previous_group = (*command_option)->group();

      std::cout << STR(TAB6);
      std::cout << STR(BOLD_START) << STR2((*command_option)->group()) << STR(BOLD_END);
      std::cout << STR(EOL);
    }

    std::cout << STR(TAB6);
    std::cout << STR(BOLD_START);
    std::cout << STR(PARAM) << (*command_option)->short_name();

    std::size_t params_size = STR(PARAM).size() + ((*command_option)->short_name()).size();

    if (((*command_option)->long_name() != "") && ((*command_option)->long_name() != (*command_option)->short_name())) {
      std::cout << "," << STR(SPACE) << STR(PARAM) << STR(PARAM) << (*command_option)->long_name();

      params_size += 2 + STR(PARAM).size() + STR(PARAM).size() + ((*command_option)->long_name()).size();
    } else {
      if (6 > params_size) {  // 6 is STR(TAB6).size()
        for (std::size_t i = 0; i < (6 - params_size); i++) {  // 6 is STR(TAB6).size()
          std::cout << STR(SPACE);
        }
      }
    }

    std::cout << STR(BOLD_END);

    if (params_size > 6) {
      std::cout << STR(EOL);
      std::cout << STR(TAB6) << STR(TAB6);
    }

    std::cout << (*command_option)->description() << STR(EOL);

    if ((*command_option)->example() != KeyString::UNDEFINED_STRING) {
      std::cout << STR(TAB6) << STR(TAB6) << "Example:" << STR(SPACE) << STR2((*command_option)->example()) << STR(EOL);
    }
    if ((*command_option)->only() != KeyString::UNDEFINED_STRING) {
      std::cout << STR(TAB6) << STR(TAB6) << "This option is used only for:" << STR(SPACE) << STR2((*command_option)->only()) << STR(EOL);
    }
    if ((*command_option)->def_val() != KeyString::UNDEFINED_STRING) {
      std::cout << STR(TAB6) << STR(TAB6) << "Default value:" << STR(SPACE) << STR2((*command_option)->def_val()) << STR(EOL);
    }

    if((*command_option)->values()->size() > 0) {
      std::cout << STR(TAB6) << STR(TAB6) << "The possible values are:" << STR(EOL);
      for (std::list<CValue *>::iterator it = (*command_option)->values()->begin();
           it != (*command_option)->values()->end(); ++it) {
        std::cout << STR(TAB6) << STR(TAB6) << STR(TAB6) << STR2((*it)->value());
        if (((*it)->description() != "") && ((*it)->description() != STR2((*it)->value()))) {
          std::cout << STR(SPACE) << ":" << STR(SPACE) << (*it)->description();
        }
        if ((*it)->def_val()) {
          std::cout << STR(SPACE) << "(Default)";
        }
        std::cout << STR(EOL);
      }        
    }

    // Range ++

    std::cout << STR(EOL);     
  }

  // std::cout << STR(EOL);

  if (cmd->function_name() == KeyString::CMD_APP_HELP) {
    ShowListOfCommandsAndCalculations();
  }
  
  std::cout << STR(BOLD_START) << STR(MAN_AUTHOR) << STR(BOLD_END) << STR(EOL);
  std::cout << STR(TAB6) << STR2(cmd->author());
  std::cout << STR(EOL) << STR(EOL);

  std::cout << STR(BOLD_START) << STR(MAN_COPYRIGHT) << STR(BOLD_END) << STR(EOL);
  std::cout << STR(TAB6) << STR2(cmd->copyright());
  std::cout << STR(EOL) << STR(EOL);

  std::cout << STR(BOLD_START) << STR(MAN_SEE_ALSO) << STR(BOLD_END) << STR(EOL);
  std::cout << STR(TAB6) << STR2(cmd->see_also());
  std::cout << STR(EOL) << STR(EOL);
}
