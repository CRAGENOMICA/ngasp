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
 *  \brief     CCMDExec.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Mar 8, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDEXEC_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDEXEC_H_

#include <string>

#include "../ICommand.h"

class CCMDExec : public ICommand {
 public:
  CCMDExec();
  virtual ~CCMDExec();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 public:
  std::string command_;
  std::string working_directory_;
  std::string type_;

 public:
  inline std::string command() const { return command_; }
  inline void set_command(const std::string &command) {
      command_ = command;
  }

  inline std::string working_directory() const { return working_directory_; }
  inline void set_working_directory(const std::string &working_directory) {
      working_directory_ = working_directory;
  }

  inline std::string type() const { return type_; }
  inline void set_type(const std::string &type) {
      type_ = type;
  }
};

#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDEXEC_H_
