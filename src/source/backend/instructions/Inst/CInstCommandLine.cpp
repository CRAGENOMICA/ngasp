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
 *  \brief     CInstCommandLine.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CInstCommandLine.h"

#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
#include <list>

#include "../../commands/ICommand.h"
#include "../../commands/CAllCommands.h"
#include "../../util/CStringTools.h"


CInstCommandLine::CInstCommandLine() {
  arguments_ = NULL;
}

CInstCommandLine::~CInstCommandLine() {
  // Arguments
  if (arguments() != NULL) {
    arguments_->clear();
    delete arguments_;
    arguments_ = NULL;
  }
}

void CInstCommandLine::ClearArguments(void) {
  if (arguments() != NULL) {
    arguments_->clear();
    delete arguments_;
    arguments_ = NULL;
  }
  arguments_ = new std::list<std::string>();
}

void CInstCommandLine::set_command_arguments(int argc, char **argv) {
  ClearArguments();

  for (int i = 0; i < argc; i++) {
    arguments()->push_back(argv[i]);
  }

  SetInstruction();

  ExtractGeneralOptions();
}

void CInstCommandLine::set_command_arguments(const std::string & _szCommand) {
  ClearArguments();

  std::string cmd = _szCommand;

  CStringTools::Replace(cmd, STR(TAB), STR(SPACE));

  std::vector<std::string> elems = CStringTools::SplitStrings(cmd,
                                                              PARAMS_SEPARATOR);

  // Copy arguments:
  int argc = elems.size();
  for (int i = 0; i < argc; i++) {
    arguments()->push_back(elems[i].c_str());
  }

//
//
//  std::string long_argument; // For example: _szCommand: "-option argument -option \"this is a long argument\" -option argument"
//  bool is_long = false;
//
//  // Copy arguments:
//  int argc = elems.size();
//  for (int i = 0; i < argc; i++) {
//
//    if (elems[i] != "") {
//      if (is_long == true) {
//        if (elems[i].c_str()[elems[i].length()-1] == '\"') {
//          // end of a long argument:
//          is_long = false;
//          long_argument += PARAMS_SEPARATOR;
//          //long_argument += elems[i].substr(0,elems[i].length()-1);              // Remove last "
//          long_argument += elems[i];                                              // Do not remove last "
//          arguments()->push_back(long_argument);
//        } else {
//          // continue getting the long argument:
//          long_argument += PARAMS_SEPARATOR;
//          long_argument += elems[i];
//        }
//      } else {
//        if (elems[i].c_str()[0] == '\"') {
//          // beginning of a long argument:
//          is_long = true;
//          // long_argument = elems[i].substr(1);                                  // Remove first "
//          long_argument = elems[i];                                               // Do not remove first "
//          if (long_argument[long_argument.length()-1] == '\"') {
//            // end of a long argument:
//            is_long = false;
//            // long_argument = long_argument.substr(0,long_argument.length()-1);  // Remove last "
//              arguments()->push_back(long_argument);                              // Do not remove last "
//          }
//        } else {
//          // push_back this normal argument:
//          arguments()->push_back(elems[i].c_str());
//        }
//      }
//    }
//  }

  SetInstruction();

  ExtractGeneralOptions();
}

std::list<std::string>::iterator CInstCommandLine::GetCommandPosition() {
  std::string argv_lower;
  std::string command_lower;
  std::string abbreviation_lower;
  std::list<std::string>::iterator command_position = arguments()->end();

  // Discard the first position because it is the application name:
  std::list<std::string>::iterator it = arguments()->begin();
  ++it;

  for (;((it != arguments()->end()) &&
         (command_position == arguments()->end())); ++it) {
    for (std::list<ICommand *>::iterator cmd
         = manager()->all_commands()->GetFirstCommandIterator();
        ((cmd != manager()->all_commands()->GetLastCommandIterator()) &&
         (command_position == arguments()->end())); cmd++) {

      argv_lower = (*it);
      std::transform(argv_lower.begin(),
                     argv_lower.end(),
                     argv_lower.begin(),
                    ::tolower);

      command_lower = STR2((*cmd)->name());
      std::transform(command_lower.begin(),
                     command_lower.end(),
                     command_lower.begin(),
                     ::tolower);

      abbreviation_lower = STR2((*cmd)->command_abbreviation());
      std::transform(abbreviation_lower.begin(),
                     abbreviation_lower.end(),
                     abbreviation_lower.begin(),
                     ::tolower);

      if ((argv_lower == command_lower) || (argv_lower == abbreviation_lower)) {
        set_command_name(STR2((*cmd)->name()));
        command_position = it;
      }
    }
  }

  return command_position;
}

void CInstCommandLine::ExtractGeneralOptions() {
  ClearGeneralOptions();

  std::list<std::string>::iterator command_position = GetCommandPosition();

  // From 1 because 0 is the app name. It can not be a general option:
  std::list<std::string>::iterator it = arguments()->begin();
  ++it;

  std::string value;
  for (;it != command_position; ++it) {
    value = (*it);
    general_options_list()->push_back(value);
  }
}

void CInstCommandLine::SetInstruction() {
  ClearCommandArguments();

  std::list<std::string>::iterator it_command_position = GetCommandPosition();
  std::string value;
  for (std::list<std::string>::iterator it = it_command_position;
       it != arguments()->end(); ++it) {
    value = (*it);

    if (it == it_command_position) {
      command_arguments()->push_back(command_name());
    } else {
      command_arguments()->push_back(value);
    }
  }
}

