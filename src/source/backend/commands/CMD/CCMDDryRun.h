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
 *  \brief     CCMDDryRun.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 13, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDDRYRUN_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDDRYRUN_H_

#include "../ICommand.h"

class CCMDDryRun : public ICommand {
 public:
  CCMDDryRun();
  virtual ~CCMDDryRun();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 private:
  bool dry_run_mode_;

 public:
  inline void set_dry_run_mode(bool dry_run_mode) {
    dry_run_mode_ = dry_run_mode;
  }
  inline bool dry_run_mode(void) { return dry_run_mode_; }
};

#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDDRYRUN_H_
