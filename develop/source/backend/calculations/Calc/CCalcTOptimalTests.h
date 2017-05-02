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
 *  \brief     CCalcTOptionalTests.h
 *  \details   Algorithms developed by Luca Ferretti and Giacomo Marmorini (2010)
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 14, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CCALCTOPTIONALTESTS_H_
#define CALCULATIONS_CCALCTOPTIONALTESTS_H_

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/common/CTestRinf.h"
#include "../../data_manager/common/CTestR0.h"
#include "../../data_manager/common/CTestQuad.h"
#include "../../data_manager/common/CTestLc.h"
#include "../../data_manager/common/CTestQuadWc.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Matrix.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataDoubleVector.h"
#include "../../data_manager/Data/CDataDoubleMatrix.h"


#ifndef inGSL
  #define inGSL 1
#endif

#define DEBUG_DEN 0

class CCalcTOptimalTests : public ICalculation {
 private:
  // Inputs
  CDataIntVector *vint_perpop_nsam;
  CDataInt64 *npops;
  CDataInt64Matrix *stats_freq;
  CDataDouble *stats_total_length;
  CDataDoubleMatrix *stats_H1freq;
  CDataDoubleVector *stats_thetaH1;
  CDataDoubleMatrix *stats_H0freq;
  CDataDoubleVector *stats_thetaH0;  // Used?
  
  // Outputs
  CDataDoubleVector *stats_ToH0_ii;
  CDataDoubleVector *stats_To_ii;
  CDataDoubleVector *stats_To_00;
  CDataDoubleVector *stats_To_i0;
  CDataDoubleVector *stats_ToH0_00;
  CDataDoubleVector *stats_To_Qc_ii;
  CDataDoubleVector *stats_To_Qw_ii;
  CDataDoubleVector *stats_To_Lc_ii;
  
 public:
  CCalcTOptimalTests();
  virtual ~CCalcTOptimalTests();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcTOptimalTests(); /*clone*/  }

 private:
  int generate_optimal_test_rinf_gennull(CTestRinf *opt,int n,double *xi_b, double *xi_null);
  int generate_optimal_test_rinf(CTestRinf *opt,int n,double *xi_b) ;
  double optimal_test_rinf(CTestRinf *t_rinf, double *xi);
  double optimal_test_rinf2(double *exp_spfr, double *obs_spfr, int n, double S);
  int generate_optimal_test_r0(CTestR0 *opt,int n, double *xi_b,/* temporary: double theta*/ long sw, long l) ;
  int generate_optimal_test_r0_gennull(CTestR0 *opt,int n, double *xi_b,double *xi_null, /* temporary: double theta*/ long sw, long l);
  double optimal_test_r0(CTestR0 *t_r0, double *xi);
  int generate_optimal_test_rinf0 (CTestRinf *opt,int n, double *xi_b, long sw, long l);
  double optimal_test_rinf_rvar0 (CTestRinf *t_rinf, double *xi);
  int generate_optimal_test_quad (CTestQuad *opt,int n, double *xi_b,double theta, long l);
  double optimal_test_quad(CTestQuad *t_quad, double *xi);
  int generate_optimal_test_lc (CTestLc *opt, int n, double *xi_b,double theta, long l);
  double optimal_test_lc(CTestLc *t_lc, double *xi);
  int generate_optimal_test_quad_wc (CTestQuadWc *opt, int n, double *xi_b,double theta, long l);
  double optimal_test_quad_wc(CTestQuadWc *t_quad_wc, double *xi);
};

#endif /* CALCULATIONS_CCALCTOPTIONALTESTS_H_ */
