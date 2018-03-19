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
 *  \brief     CAllCommands.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      March 30, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#ifndef BACKEND_SRC_COMMANDS_CALLCOMMANDS_H_
#define BACKEND_SRC_COMMANDS_CALLCOMMANDS_H_

#include <list>
#include <string>
#include <sstream>

#include "../IBase.h"
#include "ICommand.h"

class CAllCommands : public IBase {
 public:
CAllCommands();
~CAllCommands();

void IncludeAllCommands();

 private:
  std::list<ICommand *> *commands_;
  /// This iterator points to the current command that it is being executed:
  std::list<ICommand *>::iterator selected_command_;
  bool dry_run_;  /// This is a General Option

 public:
  inline std::list<ICommand *> *commands(void) { return commands_; }
  inline void set_commands(std::list<ICommand *> *commands) {
    commands_ = commands;
  }

  inline std::list<ICommand *>::iterator GetFirstCommandIterator() {
    return commands_->begin();
  }
  inline std::list<ICommand *>::iterator GetLastCommandIterator() {
    return commands_->end();
  }

  inline std::list<ICommand *>::iterator selected_command(void) const {
    return selected_command_;
  }
  inline void set_selected_command(
      std::list<ICommand *>::iterator selected_command) {
    selected_command_ = selected_command;
  }
  void set_selected_command(const std::string & command_name);

  inline void set_dry_run(bool dry_run) { dry_run_ = dry_run; }
  inline bool dry_run(void) { return dry_run_; }
  
  std::string GetCommandsList(void);
  std::string GetCommandsInformation(CManager *manager);
};

#endif  // BACKEND_SRC_COMMANDS_CALLCOMMANDS_H_
