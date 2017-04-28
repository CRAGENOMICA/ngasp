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
 *  \brief     CCMDHistory.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 29, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDHISTORY_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDHISTORY_H_

#include "../ICommand.h"

class CCMDHistory : public ICommand {
 public:
  CCMDHistory();
  virtual ~CCMDHistory();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 private:
  enum HistoryAction {
    UNKNOWN   = 0,
    LIST      = 1,
    CLEAR     = 2,
    RUN       = 3
  };

  HistoryAction action_;
  int action_num_to_run_;

 public:
  inline void set_action(const HistoryAction &action) { action_ = action; }
  inline HistoryAction action() const { return action_; }

  inline void set_action_num_to_run(int action_num_to_run) {
    action_num_to_run_ = action_num_to_run;
  }
  inline int action_num_to_run() const { return action_num_to_run_; }
};

#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDHISTORY_H_
