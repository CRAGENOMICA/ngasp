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
 *  \brief     CAllCommands.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      March 30, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#include "CAllCommands.h"

#include <list>
#include <string>
#include <sstream>

#include "CCommandFactory.h"
#include "ICommand.h"


CAllCommands::CAllCommands() {
  set_commands(NULL);
  set_dry_run(false);
}

CAllCommands::~CAllCommands() {
  if (commands()) {
    // Delete all list elements:
    std::list<ICommand *>::iterator it = commands()->begin();
    while (it != commands_->end()) {
      delete *it;
      it++;
    }

    // Delete the list:
    commands_->clear();
    delete commands_;
    commands_ = NULL;
  }
}

void CAllCommands::IncludeAllCommands() {
  set_commands(new std::list<ICommand *>);

  CCommandFactory::FillListWithAllCommands(commands());


/*  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_LOAD_FILE));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_APP_VERSION));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_VERBOSE));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_APP_HELP));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_STOP));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_DRY_RUN));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_MEMORY_INFO));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_OPEN_DATA_FILE));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_DELETE));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_HISTORY));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_DIM));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_CALC));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_SET_VALUE));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_WITH));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_END_WITH));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_PRINT));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_RUN));
  commands()->push_back(CCommandFactory::GetCommand(
      KeyString::CMD_ADD));
*/

  for (std::list<ICommand *>::iterator cmd = commands()->begin();
       cmd != commands()->end(); cmd++ ) {
    (*cmd)->set_manager(this->manager());
    (*cmd)->DefineCommandOptions();
  }
}

void CAllCommands::set_selected_command(const std::string & command_name) {
  set_selected_command((std::list<ICommand *>::iterator)commands()->end());

  for (std::list<ICommand *>::iterator cmd  = commands()->begin();
       cmd != commands()->end() && selected_command() == commands()->end();
       cmd++) {
    if (command_name ==
        STR2((*cmd)->name())) {
      set_selected_command((std::list<ICommand *>::iterator)cmd);
    }
  }
}

std::string CAllCommands::GetCommandsList(void) {
  std::string list;

  for (std::list<ICommand *>::iterator cmd = GetFirstCommandIterator();
      cmd != GetLastCommandIterator(); cmd++) {
    if (cmd != GetFirstCommandIterator()) {
      list += "," + STR(SPACE);
    }
    list += STR2((*cmd)->name());
  }

  return list;
}

std::string CAllCommands::GetCommandsInformation(CManager *manager) {
  std::string ret = "{";
  ret += "\"commands\":[";

  std::string name, command_description;
  
  for (std::list<ICommand *>::iterator cmd = GetFirstCommandIterator();
      cmd != GetLastCommandIterator(); cmd++) {
    if (cmd != GetFirstCommandIterator()) {
      ret += ",";
    }
    
    name = STR2((*cmd)->name());
    command_description = STR2((*cmd)->brief_description());
    command_description = CStringTools::ScapeForJSONfield(command_description);
      
    ret += "{";
    ret += "\"id\":\"" + name + "\",";
    ret += "\"description\":\"" + command_description + "\"";
    ret += "}";
  }

  ret += "]";
  ret += "}";

  std::cout << "\n\n";
  std::cout << ret;
  std::cout << "\n\n";
  return ret;
}
