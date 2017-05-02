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
 *  \brief     CCMDVerbose.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 8, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDVERBOSE_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDVERBOSE_H_

#include "../ICommand.h"

class CCMDVerbose : public ICommand {
 public:
  CCMDVerbose();
  virtual ~CCMDVerbose();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 private:
  CLogger::LogMode log_verbose_level_;

 public:
  inline void set_log_verbose_level(CLogger::LogMode log_verbose_level) {
    log_verbose_level_ = log_verbose_level;
  }
  inline CLogger::LogMode log_verbose_level(void) const {
    return log_verbose_level_;
  }
};

#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDVERBOSE_H_
