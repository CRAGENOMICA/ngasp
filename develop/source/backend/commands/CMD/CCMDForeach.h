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
 *  \brief     CCMDForeach.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 11, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDFOREACH_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDFOREACH_H_

#include <string>

#include "../ICommand.h"
#include "../../data_manager/common/CDataAccess.h"

class CCMDForeach : public ICommand {
 public:
  CCMDForeach();
  virtual ~CCMDForeach();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 private:
  CDataAccess *data_;
  CDataAccess *node_;
  CDataAccess *from_;
  CDataAccess *to_;
  int increment_value_;
  long int from_value_;
  long int to_value_;

 public:
  inline int increment_value(void) const { return increment_value_; }
  inline void set_increment_value(int increment_value) {
    increment_value_ = increment_value;
  }

  inline int from_value(void) const { return from_value_; }
  inline void set_from_value(int from_value) {
    from_value_ = from_value;
  }

  inline int to_value(void) const { return to_value_; }
  inline void set_to_value(int to_value) {
    to_value_ = to_value;
  }
};

#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDFOREACH_H_
