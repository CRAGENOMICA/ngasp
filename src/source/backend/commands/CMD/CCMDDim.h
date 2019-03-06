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
 *  \brief     CCMDDim.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 6, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDDIM_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDDIM_H_

#include <string>
#include <list>

#include "../ICommand.h"

class CCMDDim : public ICommand {
 public:
  CCMDDim();
  virtual ~CCMDDim();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 private:
  std::string name_;
  std::string as_;
  //std::list<KeyString> *all_creatable_types_;

 public:
  inline std::string name(void) const { return name_; }
  inline void set_name(const std::string & name) { name_ = name; }

  inline std::string as(void) const { return as_; }
  inline void set_as(const std::string & as) { as_ = as; }

//  inline std::list<KeyString> *all_creatable_types() {
//    return all_creatable_types_;
//  }
//  inline void set_all_creatable_types(std::list<KeyString>
//  *all_creatable_types) {
//    all_creatable_types_ = all_creatable_types;
//  }

// private:
//  bool ValidateType(const std::string &type);
};

#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDDIM_H_
