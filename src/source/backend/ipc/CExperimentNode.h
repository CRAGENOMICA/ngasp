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
 *  \brief     CExperimentNode.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Sep 10, 2015
 *  \pre
 *  \bug
 *  \warning
 */
#include "CNamedPipeManager.h"

#include <string>

#define INSTANCE_FREE "OPEN"
#define INSTANCE_WORKING "WORKING"
#define INSTANCE_GETTING_STATUS "..."

class CExperimentNode {
 private:
  int experiment_id_;
  CNamedPipeManager pipe_manager_;
  std::string status_;

 public:
  CExperimentNode(int experiment_id);
  ~CExperimentNode() {}

 public:
  CNamedPipeManager *pipe_manager(void) { return &pipe_manager_; }

 public:
  inline int experiment_id(void) { return experiment_id_; }
  inline std::string status(void) { return status_; }
  inline void set_status(std::string status) { status_ = status; }
  inline void set_experiment_id(int experiment_id) { experiment_id_ = experiment_id; }
};

