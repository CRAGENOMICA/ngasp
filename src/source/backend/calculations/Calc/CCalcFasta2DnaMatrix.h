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
 *  \brief     CCalcFasta2DnaMatrix.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 22, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_CALCULATIONS_CALC_CCALCFASTA2DNAMATRIX_H_
#define BACKEND_SRC_CALCULATIONS_CALC_CCALCFASTA2DNAMATRIX_H_

#include <string>

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataStringSet.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataIntMatrix.h"
#include "../../data_manager/Data/CDataInt64.h"

class CCalcFasta2DnaMatrix : public ICalculation {
 private:
  // Inputs
  CDataStringSet *fasta;
  CDataInt *ploidy;
  CDataInt *include_unknown;
  CDataInt *force_outgroup;
  CDataInt *outgroup_presence;
  CDataIntVector *vint_perpop_nsam;
  CDataInt64 *npops;
  CDataInt64 *int_total_nsam;
  
  // Outputs
  CDataCharVector *dna_matrix;
  
 public:
  CCalcFasta2DnaMatrix();
  virtual ~CCalcFasta2DnaMatrix();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

public:
  ICalculation* clone() const { return new CCalcFasta2DnaMatrix(); /*clone*/  }
};

#endif  // BACKEND_SRC_CALCULATIONS_CALC_CCALCFASTA2DNAMATRIX_H_
