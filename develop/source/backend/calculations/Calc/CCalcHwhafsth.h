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
 *  \brief     CCalcHwhafsth.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15 *2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCHWHAFSTH_H_
#define CALCULATIONS_CALCS_CCALCHWHAFSTH_H_

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Matrix.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataDoubleVector.h"

class CCalcHwhafsth : public ICalculation {
  private:
  // Inputs
  CDataIntVector *vint_perpop_nsam;
  CDataInt64 *npops;
  CDataCharVector *matrix_pol;
  CDataInt64 *length;
    
  // Outputs
  CDataIntVector *stats_nhpop;
  CDataDoubleVector *stats_hapw;
  CDataDoubleVector *stats_hapa;
  CDataDoubleVector *stats_hapT;
  CDataDoubleVector *stats_fsth;
  CDataDoubleVector *stats_fsth1all;
  CDataInt64Matrix *stats_freqh;
  CDataInt *stats_nh;
  CDataDoubleVector *stats_Gst;
  CDataDouble *stats_fsthALL;
  CDataDouble *stats_GstALL;
  
 public:
  CCalcHwhafsth();
  virtual ~CCalcHwhafsth();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcHwhafsth(); /*clone*/  }
};

#endif  // CALCULATIONS_CALCS_CCALCHWHAFSTH_H_
