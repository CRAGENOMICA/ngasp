/*
 * mstatspop, Statistical Analysis using Multiple Populations for Genomic Data.
 * Copyright (c) 2009-2017, Sebastián Ramos Onsins,
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
 *  \brief     CCalcR2.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCR2_H_
#define CALCULATIONS_CALCS_CCALCR2_H_

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataDoubleVector.h"

#include <list>

class CCalcR2 : public ICalculation {
 public:
  CCalcR2();
  virtual ~CCalcR2();

  BEGIN_CALCULATION_INTERFACE
    DECLARE_INPUT(CDataInt,           ploidy)
    DECLARE_INPUT(CDataIntVector,     vint_perpop_nsam)
    DECLARE_INPUT(CDataInt64,         npops)
    DECLARE_INPUT(CDataCharVector,    matrix_pol)
    DECLARE_INPUT(CDataDoubleVector,  stats_S)
    DECLARE_INPUT(CDataDoubleVector,  stats_thetaT)
    DECLARE_INPUT(CDataInt64,         length)
    DECLARE_OUTPUT(CDataDoubleVector, stats_R2)
  END_CALCULATION_INTERFACE

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);
 
 public:
  ICalculation* clone() const { return new CCalcR2(); /*clone*/  }

 private:
  // R2 Ramos & Rozas: "*unic" is the number of singletons in each sequence
  // (in comparison to the sample studied)
  double R2Function(long int *unic,double pi,int sample_size,long int S);
};

#endif /* CALCULATIONS_CALCS_CCALCR2_H_ */
