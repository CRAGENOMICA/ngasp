/*
 * mstatspop, Statistical Analysis using Multiple Populations for Genomic Data.
 * Copyright (c) 2009-2017, Sebastián Ramos Onsins,
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
 *  \brief     CCalcMstatspopOpenMsFile.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 2, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCMSTATSPOPOPENMSFILE_H_
#define CALCULATIONS_CALCS_CCALCMSTATSPOPOPENMSFILE_H_

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataDoubleVector.h"
#include "../../data_manager/Data/CDataDoubleMatrix.h"
#include "../../data_manager/Data/CDataFloat.h"
#include "../../data_manager/Data/CDataFloatVector.h"
#include "../../data_manager/Data/CDataStdString.h"

#include "../../util/zutil.h"

#include "CCalcRandomize.h"

#define PI 3.14159265359

class CCalcMstatspopOpenMsFile : public ICalculation {
 private:// Inputs
  CDataStdString *file_in;  // Used in Prepare(;
  CDataInt *include_unknown;
  CDataInt *outgroup_presence;
  CDataInt *force_outgroup;  // <--------------- NEW
  CDataIntVector *nsamuser;
  CDataInt64 *npops;
  CDataInt64 *nsamtot;
  CDataInt64 *length;
  CDataInt *kind_length;
  CDataFloatVector *vector_mask;
  CDataFloat *svratio;
  CDataFloat *freq_revert;
  CDataStdString *file_mas;
  CDataDouble *freq_missing_ms;
  CDataInt *location_missing_ms;
  CDataInt *formatfile;  // <--------------- NEW

// Outputs
  CDataCharVector *matrix_pol;
  CDataInt64Vector *matrix_freq;
  CDataInt64Vector *matrix_pos;
  CDataInt64 *length_seg;  // <--------------- NEW
  CDataInt64Vector *matrix_sv;
  CDataDouble *length_mask;
  CDataDouble *length_mask_real;  // <--------------- NEW
  CDataDoubleMatrix *lengthamng;
  CDataInt64 *nmhits;
  CDataIntVector *matrix_mask;
  CDataDoubleVector *vector_priors;
  CDataInt *npriors;
  CDataDoubleVector *sum_sam;
  CDataDoubleVector *sum_sam_mask;
  CDataDoubleVector *nsites1_pop;
  CDataDoubleVector *nsites1_pop_outg;
  CDataDoubleVector *nsites2_pop;
  CDataDoubleVector *nsites2_pop_outg;
  CDataDoubleVector *nsites3_pop;
  CDataDoubleVector *nsites3_pop_outg;
  CDataDoubleVector *anx;
  CDataDoubleVector *bnx;
  CDataDoubleVector *anxo;
  CDataDoubleVector *bnxo;
  CDataDouble *missratio;
  CDataIntVector *sort_nsam;  // <--------------- NEW
  
 public:
  CCalcMstatspopOpenMsFile();
  virtual ~CCalcMstatspopOpenMsFile();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcMstatspopOpenMsFile(); /*clone*/  }

 private:
  double gammln(double zz);
  double largebinomialdist(double pp, double n);
  
 private:
  FILE *file_input_;
  SGZip input_gz_;

/// ============================================================================
/// RANDOMIZE CALCULATION
/// ============================================================================
 private:
  CDataDouble     *randomize_value_;
  ICalculation  *calc_randomize_;
  double ran1(void);
};

#endif  // CALCULATIONS_CALCS_CCALCMSTATSPOPOPENMSFILE_H_
