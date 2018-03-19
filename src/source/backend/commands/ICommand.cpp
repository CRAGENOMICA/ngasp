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
 *  \brief     ICommand.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      March 30, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#include "ICommand.h"

#include <string>
#include <list>

#include "../language/CStringTable.h"

///*
// * *** OBSOLETE CONSTRUCTOR ***
// */
//ICommand::ICommand(KeyString command_name,
//                   KeyString command_abbreviation,
//                   KeyString brief_description) : IFunction() {
//  set_manager(NULL);
//
//  set_name(command_name);
//  set_command_abbreviation(command_abbreviation);
//  set_brief_description(brief_description);
//  set_experiment("default");
//  set_ready_to_run(false);
//  
//  options()->set_manager(manager());  
//}

ICommand::ICommand(KeyString command_name,
                   KeyString command_abbreviation,
                   KeyString brief_description,
                   KeyString description,
                   KeyString author,
                   KeyString see_also)
  : IFunction(command_name, 
              brief_description,
              description,
              author,
              KeyString::GENERIC_COPYRIGHT,
              KeyString::UNDEFINED_STRING,
              see_also) {
  set_manager(NULL);

  set_name(command_name);
  set_command_abbreviation(command_abbreviation);
  set_experiment("default");
  set_ready_to_run(false);
  
  options()->set_manager(manager());  
}


void ICommand::set_instruction(IInstruction *instruction) {
  instruction_ = instruction;
  options_index_ = instruction_->command_arguments()->begin();
}

ICommand::~ICommand() {
}

bool ICommand::CheckOptions() {
  bool success = true;

  if (options_missing_options()) {
    // Show message and do not run command:
    ERROR_MSG << STR(MISSING_OPTIONS) END_MSG;
    success = false;
  }

  if (options_missing_option_arguments()) {
    // Show message and do not run command:
    ERROR_MSG << STR(MISSING_OPTION_ARGUMENTS) END_MSG;
    success = false;
  }

  if (options_unknown_parameter()) {
    // Show message and do not run command:
    ERROR_MSG << STR(UNKNOWN_OPTION) END_MSG;
    success = false;
  }

  return success;
}

bool ICommand::getopt_long_own(KeyString * option,
                               std::string * arguments) {
  bool continue_searching = true;

  if (options_index_ == instruction()->command_arguments()->begin()) {
    // Set error variables to initial value here:
    options_missing_options_ = false;
    options_missing_option_arguments_ = false;
    options_unknown_parameter_ = false;
  }

  ++options_index_;  // index will never be begin()
                     // to discard the application name

  if (options_index_!= instruction()->command_arguments()->end()) {
    std::string parameter = (*options_index_);

    // The parameter can be an option or its argument.
    // It is an option if it starts with '-', else it is an argument.
    if (parameter[0] == '-') {
      // Search this option in the options list:
      std::list<COption *>::iterator it_option =
          options()->GetFirstOptionIterator();

      bool option_found = false;

      while ((it_option != options()->GetLastOptionIterator()) &&
             (option_found == false)) {
        // Compare the option with the sort and long names:
        if ((parameter == "--" + (*it_option)->long_name()) ||
            (parameter == "-" + (*it_option)->short_name())) {
          // Option found:
          option_found = true;
          (*it_option)->set_activated(true);

          // The option name to return will be the short one:
          *option = (*it_option)->short_name_keystring();

          // Let's see if this option should have arguments:
          if ((*it_option)->arg_type() ==
              COption::ARGTYPES::ARGTYPE_arg_required) {
            // Yes. This option should have arguments.
            // Let's add all its arguments in one string:
            *arguments = "";

            // Define the iterator j that will iterate through the option
            // arguments:
            std::list<std::string>::iterator it_argument = options_index_;

            ++it_argument;
            std::list<std::string>::iterator it_first = it_argument;

            while ((it_argument != instruction()->command_arguments()->end()) &&
                    ((*it_argument) != "") &&
                    ((*it_argument)[0] != '-')) {
              // Let's put an space for separating arguments:
              if (it_argument != it_first) {  // it means not for the first ite
                *arguments += " ";
              }
              *arguments += (*it_argument);

              ++it_argument;
            }
            // move the index after the option arguments:
            --it_argument;
            options_index_ = it_argument;

            if (*arguments == "") {
              // options_missing_option_arguments_ = true;
              continue_searching = false;
            }
          }
        }

        ++it_option;
      }

      if (option_found == false) {
        *option = KeyString::UNDEFINED_STRING;
        continue_searching = false;
      }
    } else {
      // unknown parameter found without. For example: "help sdkfhh"
      options_unknown_parameter_ = true;
      continue_searching = false;
    }
  } else {
    continue_searching = false;

    // Let's see if all required options have been set and
    // let's do cleaning for next use:
     std::list<COption *>::iterator it_option =
         options()->GetFirstOptionIterator();

     while (it_option != options()->GetLastOptionIterator()) {
       if (((*it_option)->mandatory() == true) &&
           ((*it_option)->activated() == false)) {
         options_missing_options_ = true;
       }
       (*it_option)->set_activated(false);
       ++it_option;
     }

     options_index_ = instruction()->command_arguments()->begin();
  }

  return continue_searching;
}

std::string ICommand::GetArgument(std::string *arguments) {

/*
  std::string argument;
  if (*arguments != "") {
    char ch = arguments->c_str()[0];
    if (ch == '\"') {
      for (unsigned int pos = 0; pos < arguments->length(); pos++) {
        ch = arguments->c_str()[0];
        if (ch == '\"') {
          argument = arguments->substr(0, pos);
          *arguments = arguments->substr(pos+1);
        }
      }
    } else {
      int pos = arguments->find(" ");
      if (pos >= 0) {
        argument = arguments->substr(0, pos);
        *arguments = arguments->substr(pos+1);
      } else {
        argument = *arguments;
        *arguments = "";
      }
    }
  }
  return argument;
*/

  std::string argument;
  if (*arguments != "") {
    int pos = arguments->find(" ");
    if (pos >= 0) {
      argument = arguments->substr(0, pos);
      *arguments = arguments->substr(pos+1);
    } else {
      argument = *arguments;
      *arguments = "";
    }
  }
  return argument;
}

