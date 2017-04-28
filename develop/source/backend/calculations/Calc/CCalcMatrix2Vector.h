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
 *  \brief     CCalcMatrix2Vector.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      February 15, 2017
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALMATRIX2VECTOR_H_
#define CALCULATIONS_CALCS_CCALMATRIX2VECTOR_H_

#include "../ICalculation.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataStdStringVector.h"
#include "../../data_manager/Data/CDataStdStringMatrix.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataBoolean.h"

class CCalcMatrix2Vector : public ICalculation {
 private:
  // Inputs
  CDataStdStringMatrix *string_matrix_;
  CDataInt64 *pos_;
  CDataBoolean *column_;
  CDataBoolean *remove_index_;
  CDataBoolean *flattern_unique_;
  CDataBoolean *sort_items_;
  
  // Outputs
  CDataStdStringVector *string_vector_;

  
public:
  CCalcMatrix2Vector();
  virtual ~CCalcMatrix2Vector();

public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

public:
  ICalculation* clone() const { return new CCalcMatrix2Vector(); /*clone*/  }
};

#endif  // CALCULATIONS_CALCS_CCALMATRIX2VECTOR_H_

