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
 *  \brief     CCalcDnaMatrix2MatrixPol.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 22, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_CALCULATIONS_CALC_CCALCDNAMATRIX2MATRIXPOL_H_
#define BACKEND_SRC_CALCULATIONS_CALC_CCALCDNAMATRIX2MATRIXPOL_H_

#include <string>

#include "../ICalculation.h"
#include "../util/CDnaTools.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataIntMatrix.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataDoubleVector.h"


class CCalcDnaMatrix2MatrixPol : public ICalculation {
 private:
  // Inputs
  CDataCharVector *dna_matrix;
  CDataInt *ploidy;
  CDataInt *include_unknown;
  CDataInt *force_outgroup;
  CDataInt *outgroup_presence;
  CDataIntVector *vint_perpop_nsam;
  CDataInt64 *npops;
  CDataInt64 *int_total_nsam;
  CDataDoubleVector *matrix_sizepos;
  CDataDoubleVector *matrix_segrpos;
  
  // Outputs
  CDataCharVector *matrix_pol;
  CDataInt64Vector *positions;
  CDataInt64Vector *frequencies;
  
 public:
  CCalcDnaMatrix2MatrixPol();
  virtual ~CCalcDnaMatrix2MatrixPol();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

public:
  ICalculation* clone() const { return new CCalcDnaMatrix2MatrixPol(); /*clone*/  }


// private:
//  CDnaTools::NitrogenBase GetMostRepeatedBase(
//                          long int thymine_frequency,
//                          long int cytosine_frequency,
//                          long int guanine_frequency,
//                          long int adenine_frequency,
//                          long int missing_frequency,
//                          long int weak_frequency,
//                          long int amino_frequency,
//                          long int purine_frequency,
//                          long int pyrimidine_frequency,
//                          long int keto_frequency,
//                          long int strong_frequency);
//  void UpdateFrequencies(CDnaTools::NitrogenBase base,
//                          long int &thymine_frequency,
//                          long int &cytosine_frequency,
//                          long int &guanine_frequency,
//                          long int &adenine_frequency,
//                          long int &missing_frequency,
//                          long int &weak_frequency,
//                          long int &amino_frequency,
//                          long int &purine_frequency,
//                          long int &pyrimidine_frequency,
//                          long int &keto_frequency,
//                          long int &strong_frequency);
//  int GetNumberOfDifferentBasesXColumn(
//                          long int thymine_frequency,
//                          long int cytosine_frequency,
//                          long int guanine_frequency,
//                          long int adenine_frequency,
//                          long int weak_frequency,
//                          long int amino_frequency,
//                          long int purine_frequency,
//                          long int pyrimidine_frequency,
//                          long int keto_frequency,
//                          long int strong_frequency);
};

#endif  // BACKEND_SRC_CALCULATIONS_CALC_CCALCDNAMATRIX2MATRIXPOL_H_
