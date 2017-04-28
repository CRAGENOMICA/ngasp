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
 *  \brief     CCMDAdd.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 18, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDADD_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDADD_H_

#include <string>

#include "../ICommand.h"

class CCMDAdd : public ICommand {
 public:
  CCMDAdd();
  virtual ~CCMDAdd();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 public:
  std::string input_file_;
  std::string name_;
  int num_regs_;

 public:
  inline std::string input_file() const { return input_file_; }
  inline void set_input_file(const std::string &input_file) {
      input_file_ = input_file;
  }

  inline std::string name() const { return name_; }
  inline void set_name(const std::string &name) { name_ = name; }

  inline int num_regs() const { return num_regs_; }
  inline void set_num_regs(const int &num_regs) { num_regs_ = num_regs; }
};

#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDADD_H_
