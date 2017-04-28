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
 *  \brief     CCalcFileStats.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 7, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCFILESTATS_H_
#define CALCULATIONS_CALCS_CCALCFILESTATS_H_

#include "../ICalculation.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataCharMatrix.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataDoubleVector.h"
#include "../../data_manager/Data/CDataDoubleMatrix.h"
#include "../../data_manager/Data/CDataStdString.h"

#include "../../data_manager/common/CDataAccess.h"

class CCalcFileStats : public ICalculation {
 private:
  // Inputs
  CDataInt *ploidy;
  CDataInt *include_unknown;
  CDataInt *outgroup_presence;
  CDataIntVector *vint_perpop_nsam;
  CDataInt64 *npops;
  CDataCharMatrix *names;
  CDataInt64 *n_site;
  CDataCharVector *DNA_matr;
  CDataDoubleVector *matrix_segrpos;
  CDataStdString *file_in;
  CDataStdString *file_mas;
  CDataInt *output;
  CDataInt64 *formatfile;
  
  // Outputs
  CDataCharVector *matrix_pol;
  CDataCharVector *matrix_pol_tcga;
  CDataDoubleMatrix *lengthamng;
  CDataDoubleMatrix *tcga;
  CDataDoubleVector *anx;
  CDataDoubleVector *bnx;
  CDataDoubleVector *anxo;
  CDataDoubleVector *bnxo;
  CDataDouble *length_al;
  CDataInt64 *length_seg;  //<<<
  CDataDouble *missratio;
  CDataDoubleVector *nsites1_pop;
  CDataDoubleVector *nsites1_pop_outg;
  CDataDoubleVector *nsites2_pop;
  CDataDoubleVector *nsites2_pop_outg;
  CDataDoubleVector *nsites3_pop;
  CDataDoubleVector *nsites3_pop_outg;
  CDataDoubleVector *sum_sam;
  CDataDouble *svratio;
  CDataInt64Vector *matrix_freq;
  CDataInt64Vector *matrix_pos;
  CDataInt64Vector *matrix_sv;
  CDataInt64Vector *mhitbp; //<<<<
  CDataInt64 *n_realsite;
  CDataInt64 *nmhits;
  CDataDoubleVector *matrix_sizepos;  //<<<
  CDataInt *n_samp;   // It was n_samp
  
 public:
  CCalcFileStats();
  virtual ~CCalcFileStats();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcFileStats(); /*clone*/  }
};

#endif /* CALCULATIONS_CALCS_CCALCFILESTATS_H_ */
