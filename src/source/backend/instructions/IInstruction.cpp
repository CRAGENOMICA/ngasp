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
 *  \brief     IInstruction.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 9, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "IInstruction.h"

#include <string>
#include <list>

#include "../util/CStringTools.h"

IInstruction::IInstruction() {
  command_name_ = "";
  general_options_list_ = new std::list<std::string>();
  command_arguments_ = new std::list<std::string>();
  set_loop_id(0);
}

IInstruction::~IInstruction() {
  // General Options
  if (general_options_list() != NULL) {
    general_options_list_->clear();
    delete general_options_list_;
    general_options_list_ = NULL;
  }

  // Command Arguments
  if (command_arguments() != NULL) {
    command_arguments_->clear();
    delete command_arguments_;
    command_arguments_ = NULL;
  }
}

void IInstruction::ClearGeneralOptions(void) {
  if (general_options_list() != NULL) {
    general_options_list_->clear();
    delete general_options_list_;
    general_options_list_ = NULL;
  }
  general_options_list_ = new std::list<std::string>();
}

void IInstruction::ClearCommandArguments(void) {
  if (command_arguments() != NULL) {
    command_arguments_->clear();
    delete command_arguments_;
    command_arguments_ = NULL;
  }
  command_arguments_ = new std::list<std::string>();
}

std::string IInstruction::GetAllCommandLine(void) {
  std::string all_command_line;

  for (std::list<std::string>::iterator it = command_arguments()->begin();
       it != command_arguments()->end(); ++it) {
    if (it != command_arguments()->begin()) {
      all_command_line += " ";
    }
    all_command_line += (*it);
  }

  return all_command_line;
}

void IInstruction::ReplaceConstantsInText(
              std::list<std::pair<std::string, std::string> > *constants,
              std::string & text) {
  for (std::list<std::pair<std::string, std::string> >::iterator it
          = constants->begin(); it != constants->end(); ++it) {
    CStringTools::Replace(text, (*it).first, (*it).second);
  }
}

void IInstruction::ReplaceConstants(
                 std::list<std::pair<std::string, std::string> >  *constants) {
  if (constants->empty() == false) {
    /// Replace constants in command name:
    ReplaceConstantsInText(constants, command_name_);

    /// Replace constants in command arguments:
    for (std::list<std::string>::iterator it = command_arguments_->begin();
         it != command_arguments_->end(); ++it) {
      ReplaceConstantsInText(constants, (*it));
    }

    /// Replace constants in command general options:
    for (std::list<std::string>::iterator it = general_options_list_->begin();
         it != general_options_list_->end(); ++it) {
      ReplaceConstantsInText(constants, (*it));
    }
  }
}
