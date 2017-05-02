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
 *  \brief     CCalcFreqStats.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCFREQSTATS_H_
#define CALCULATIONS_CALCS_CCALCFREQSTATS_H_

#include "../ICalculation.h"

#include "../util/CMissingFreqs.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Matrix.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataDoubleVector.h"
#include "../../data_manager/Data/CDataDoubleMatrix.h"

#include "CCalcRandomize.h"

#define DEBUG_EMANUELE 0
#define SAMPLE_LARGE 4000
#define NITER 1e6

struct covar_ij { // Defined here because only this calculation uses it.
  int i1;
  int i2;
  int n1;
  int n2;
  int n12;
  double Covij;
};

class CCalcFreqStats : public ICalculation {
 private:
  // Inputs
  CDataInt *include_unknown_;
  CDataInt *force_outgroup_;
  CDataInt *outgroup_presence_;
  CDataIntVector *vint_perpop_nsam_;
  CDataInt64 *npops_;
  CDataCharVector *matrix_pol_;
  CDataInt *n_ccov_;
  CDataInt *H1frq_;
  CDataDoubleMatrix *stats_H1freq_;
  CDataInt64 *length_;
  
  // Outputs
  CDataDoubleVector *stats_Dfl_;
  CDataDoubleVector *stats_Dtaj_;
  CDataDoubleVector *stats_Ez_;
  CDataDoubleVector *stats_Ffl_;
  CDataDoubleVector *stats_Hnfw_;
  CDataDoubleVector *stats_S_;
  CDataDoubleVector *stats_So_;
  CDataDoubleVector *stats_thetaFL_;
  CDataDoubleVector *stats_thetaFW_;
  CDataDoubleVector *stats_thetaL_;
  CDataDoubleVector *stats_thetaS_;
  CDataDoubleVector *stats_thetaSA_;
  CDataDoubleVector *stats_thetaSo_;
  CDataDoubleVector *stats_thetaT_;
  CDataDoubleVector *stats_thetaTA_;
  CDataDoubleVector *stats_thetaTo_;
  CDataDoubleVector *stats_To_00_;
  CDataDoubleVector *stats_To_i0_;
  CDataDoubleVector *stats_To_ii_;
  CDataDoubleVector *stats_ToH0_00_;
  CDataDoubleVector *stats_ToH0_ii_;
  CDataDoubleVector *stats_Yach_;
  CDataDoubleVector *stats_FH_;
  CDataInt64Matrix  *stats_freq_;
  
public:
  CCalcFreqStats();
  virtual ~CCalcFreqStats();

public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

public:
  ICalculation* clone() const { return new CCalcFreqStats(); /*clone*/  }

//public:
//  /// Parameters
////  int force_outgroup;
////  int include_unknown;
////  int npops;
////  int outgroup_presence;
////  int *nsam;
//  int n_ccov;
//
//  /// Inputs
////  char *matrix_pol;
//  double **H1freq;
//  int H1frq;
////  long int length;
//
//  /// Outputs //All must be pointers:
//  double *Dfl;
//  double *Dtaj;
//  double *Ez;
//  double *Ffl;
//  double *Hnfw;
//  double *S;
//  double *So;
//  double *thetaFL;
//  double *thetaFW;
//  double *thetaL;
//  double *thetaS;
//  double *thetaSA;
//  double *thetaSo;
//  double *thetaT;
//  double *thetaTA;
//  double *thetaTo;
//  double *To_00;
//  double *To_i0;
//  double *To_ii;
//  double *ToH0_00;
//  double *ToH0_ii;
//  double *Yach;
//  long int **freq;
private:
  double *an_m;  //!added

private:
  CMissingFreqs missing_freqs_;

  void init_coef(double *p,int sample_size);
  double tajima_d(double k_, long int S_, double *coef_taj);
  double fl_f( long int fr1, long int S, double pi, double *coef);
  double fl_d( long int fr1,long int S, double *coef);
  double fay_wu_normalized2(int n,double thetaL,double thetaw,double S,double *coef,double pi);
  double E_zeng(int n,double thetaL,double thetaw,double S,double *coef);
  double fl_d2(int sample_size,long int fr1w,long int S, double *coef);
  double fl_f2(int sample_size,long int fr1w, long int S, double pi, double *coef);
  double freqtesto_achaz(int sample_size,long int *fr,int singleton,double *w1,double *w2);
  double freqtestn_achaz(int sample_size,long int *fr,int singleton,double *w1,double *w2);
  double an(int n);
  double a2n(int n);
  double bn(int n,int i);
  double sigmaii(int n,int i);
  double sigmaij(int n,int i,int j);
  double omegai(int n,int i,double *w1,double *w2,double sumw1,double sumw2);
  double psii(int n,int i);
  double rhoii(int n,int i);
  double rhoij(int n,int i,int j);
  double omegain(int n,int i,double *w1,double *w2,double sumw1,double sumw2);
  float cov_missing(int, int, int, int, int, float);
  int ominx_tajD(double **ominx, int **nx, int *no, double any, int nsam, long int length, long int Sc);
  int ominx_Dfl(double **ominx, int **nx, int *no, double any, int nsam, long int length, long int Sco);
  int ominx_Ffl(double **ominx, int **nx, int *no, int nsam, long int length, long int Sco);
  int ominx_Hnfw(double **ominx, int **nx, int *no, int nsam, long int length, long int Sco);
  int ominx_Ezeng(double **ominx, int **nx, int *no, double any, int nsam, long int length, long int Sco);
  int ominx_Yachaz(double **ominx, int **nx, int *no, double any, int nsam, long int length, long int Sco);
  int ominx_tajDnooutg(double **ominx, int **nx, double any, int nsam, long int length, long int Sc);
  int ominx_Dfl2(double **ominx, int **nx, double any, int nsam, long int length, long int Sc);
  int ominx_Ffl2(double **ominx, int **nx, int nsam, long int length, long int Sc);
  int ominx_Yachaz2(double **ominx, int **nx, double any, int nsam, long int length, long int Sc);
  int ominx_FH(double **ominx, int **nx, int *no, double any, int nsam, long int length, long int Sco);
  int ominx_Optimal_unfolded(double **ominx, int **nx, int *no, double any, int nsam, long int length, long int Sco, double *mean_freqsptr);
  int ominx_Optimal_folded(double **ominx, int **nx, double any, int nsam, long int length, long int S, double *mean_freqsptr);
  double freqtest_outg_missing(double **ominx,long int **eix,int **nx, int *no, double thetaw, int nsam,
                 long int length, int n_ccov, struct covar_ij **Covi1i2, long int *count_cov,int singleton,
                 double *bnxp, double *theta_square);
  double freqtest_noutg_missing(double **ominx,long int **eix,int **nx, double thetaw, int nsam,
                  long int length, int n_ccov, struct covar_ij **Covi1i2, long int *count_cov,int singleton,
                  double *bnxp, double *theta_square);
  float watterson_variance(float theta, int l, int* nx, int* ny,int* nxy, float* var_d, float* var_h);
  long int maxd(double x,double y);

/// ============================================================================
/// RANDOMIZE CALCULATION
/// ============================================================================
 private:
  CDataDouble *randomize_value_;
  ICalculation *calc_randomize_;
  double ran1(void);
};

#endif /* CALCULATIONS_CALCS_CCALCFREQSTATS_H_ */
