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
 *  \brief     CCMDSetValue.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 6, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDSETVALUE_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDSETVALUE_H_

#include "../ICommand.h"
#include "../../data_manager/common/CDataAccess.h"

#define UNDEFINED_CHAR '\x0'
#define UNDEFINED_NUM -9999
#define UNDEFINED_FLOAT -9999.0

class CCMDSetValue : public ICommand {
 public:
  CCMDSetValue();
  virtual ~CCMDSetValue();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 private:
  CDataAccess *this_info_;
  CDataAccess *ref_info_;
  CDataAccess *inc_info_;
  SetAction action_;

  bool changing_encode_value_;
};

#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDSETVALUE_H_
