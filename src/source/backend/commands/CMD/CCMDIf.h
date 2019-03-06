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
 *  \brief     CCMDIf.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 6, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDIF_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDIF_H_

#include "../ICommand.h"
#include "../../data_manager/common/CDataAccess.h"
#include "../../data_manager/Data/CDataBoolean.h"

#define UNDEFINED_CHAR '\x0'
#define UNDEFINED_NUM -9999
#define UNDEFINED_FLOAT -9999.0

enum GrammaticalConjuntion {
  AND,
  OR,
};

class CCMDIf : public ICommand {
 public:
  CCMDIf();
  virtual ~CCMDIf();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 private:
  CDataAccess *reference_;
  CDataAccess *compared_to_;
  ComparisonType comparison_type_;
  //! CDataBoolean *last_condition_;
  GrammaticalConjuntion conjuntion_;
  bool if_condition_evaluation_result_;

  void Compare(void);

 public:
  void set_comparison_type(const ComparisonType &comparison_type) {
    comparison_type_ = comparison_type;
  }
  ComparisonType comparison_type(void) const { return comparison_type_; }

  void set_conjuntion(const GrammaticalConjuntion &conjuntion) {
    conjuntion_ = conjuntion;
  }
  GrammaticalConjuntion conjuntion(void) const { return conjuntion_; }
};

#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDIF_H_
