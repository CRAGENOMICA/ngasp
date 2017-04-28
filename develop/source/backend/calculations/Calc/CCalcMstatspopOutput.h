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
 *  \brief     CCalcMstatspopOutput.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 14, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCMSTATSPOPOUTPUT_H_
#define CALCULATIONS_CALCS_CCALCMSTATSPOPOUTPUT_H_

#include "../ICalculation.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataIntMatrix.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataInt64Matrix.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataDoubleVector.h"
#include "../../data_manager/Data/CDataDoubleMatrix.h"
#include "../../data_manager/Data/CDataDoubleCube.h"
#include "../../data_manager/Data/CDataFloatVector.h"
#include "../../data_manager/Data/CDataStdString.h"

class CCalcMstatspopOutput : public ICalculation {
 private:
  // Inputs
  CDataCharVector *matrix_pol;
  CDataCharVector *matrix_pol_tcga;
  CDataInt64Vector *positions;
  CDataInt64Vector *sites;
  CDataInt64Vector *sanc;
  CDataInt *mainargc;
  CDataStdString *file_input;
  CDataStdString *file_output;
  CDataInt *gfffiles;
  CDataStdString *file_GFF;
  CDataCharVector *subset_positions;
  CDataCharVector *code_name;
  CDataCharVector *genetic_code;
  CDataInt64 *length;
  CDataDouble *length_al;
  CDataInt64 *length_al_real;
  CDataInt64 *niter;
  CDataInt *ploidy;
  CDataInt *include_unknown;
  CDataInt *force_outgroup;
  CDataInt *the_outgroup_presence;
  CDataIntVector *vint_perpop_nsam;
  CDataInt64 *npops;
  CDataInt64 *int_total_nsam;
  CDataDouble *svratio;
  CDataDouble *missratio;
  CDataDoubleMatrix *jfd;
  CDataIntMatrix *nfd;
  CDataInt *H1frq;
  CDataInt *H0frq;
  CDataStdString *file_H1f;
  CDataStdString *file_H0f;
  CDataDoubleVector *vector_priors;
  CDataInt *npriors;
  CDataInt *formatfile;
  CDataDouble *freq_missing_ms;
  CDataDoubleVector *nsites1_pop;
  CDataDoubleVector *nsites1_pop_outg;
  CDataDoubleVector *nsites2_pop;
  CDataDoubleVector *nsites2_pop_outg;
  CDataDoubleVector *nsites3_pop;
  CDataDoubleVector *nsites3_pop_outg;
  CDataInt64 *li;
  CDataIntVector *r2i_ploidies;
  CDataDoubleVector *stats_piw;
  CDataDoubleVector *stats_pia;
  CDataDoubleVector *stats_piT;
  CDataDoubleVector *stats_piant;
  CDataDoubleVector *stats_piTnt;
  CDataDoubleVector *stats_fst;
  CDataDoubleVector *stats_piwHKY;
  CDataDoubleVector *stats_piaHKY;
  CDataDoubleVector *stats_piTHKY;
  CDataDoubleVector *stats_fstHKY;
  CDataDoubleVector *stats_fst1all;
  CDataDoubleVector *stats_Gst;
  CDataDoubleVector *stats_hapw;
  CDataDoubleVector *stats_hapa;
  CDataDoubleVector *stats_hapT;
  CDataDoubleVector *stats_fsth;
  CDataDoubleVector *stats_fsth1all;
  CDataDouble *stats_fstALL;
  CDataDouble *stats_fsthALL;
  CDataDouble *stats_GstALL;
  CDataDoubleVector *stats_S;
  CDataDoubleVector *stats_So;
  CDataDoubleVector *stats_thetaS;
  CDataDoubleVector *stats_thetaSo;
  CDataDoubleVector *stats_thetaT;
  CDataDoubleVector *stats_thetaTo;
  CDataDoubleVector *stats_thetaTHKY;
  CDataDoubleVector *stats_thetaFL;
  CDataDoubleVector *stats_thetaFW;
  CDataDoubleVector *stats_thetaL;
  CDataDoubleVector *stats_thetaSA;
  CDataDoubleVector *stats_thetaTA;
  CDataDoubleVector *stats_K;
  CDataDoubleVector *stats_KHKY;
  CDataDoubleVector *stats_Dtaj;
  CDataDoubleVector *stats_Dfl;
  CDataDoubleVector *stats_Ffl;
  CDataDoubleVector *stats_Hnfw;
  CDataDoubleVector *stats_Ez;
  CDataDoubleVector *stats_Yach;
  CDataDoubleVector *stats_FH;
  CDataDoubleVector *stats_R2;
  CDataDoubleVector *stats_Fs;
  CDataInt64Vector *stats_Rm;
  CDataDoubleVector *stats_ZnA;
  CDataInt64Matrix *stats_freq;
  CDataInt *stats_nh;
  CDataIntVector *stats_nhpop;
  CDataInt64Matrix *stats_freqh;
  CDataDoubleVector *stats_length;
  CDataDoubleVector *stats_length2;
  CDataDoubleMatrix *stats_lengthamng;
  CDataDouble *stats_total_length;
  CDataDouble *stats_total_real_length;
  CDataDouble *stats_total_svratio;
  CDataDoubleVector *stats_total_tcga;
  CDataDoubleMatrix *stats_tcga;
  CDataDoubleCube *stats_sv;
  CDataDoubleCube *stats_svT;
  CDataInt64 *stats_nmhits;
  CDataDoubleMatrix *stats_H1freq;
  CDataDoubleVector *stats_thetaH1;
  CDataDoubleMatrix *stats_H0freq;
  CDataDoubleVector *stats_thetaH0;
  CDataDoubleVector *stats_ToH0_ii;
  CDataDoubleVector *stats_ToH0_00;
  CDataDoubleVector *stats_To_ii;
  CDataDoubleVector *stats_To_00;
  CDataDoubleVector *stats_To_i0;
  CDataDoubleVector *stats_To_Qc_ii;
  CDataDoubleVector *stats_To_Qw_ii;
  CDataDoubleVector *stats_To_Lc_ii;
  CDataDoubleVector *stats_mdsd;
  CDataDoubleVector *stats_mdg1;
  CDataDoubleVector *stats_mdg2;
  CDataDoubleMatrix *stats_mdw;
  CDataDoubleMatrix *stats_linefreq;
  CDataDoubleVector *stats_anx;
  CDataDoubleVector *stats_bnx;
  CDataDoubleVector *stats_anxo;
  CDataDoubleVector *stats_bnxo;
  CDataDoubleMatrix *stats_R2p;
  CDataInt64Vector *piter_i;
  CDataInt64Vector *piter_ih;
  CDataInt64Vector *piter_igh;
  CDataInt64Vector *piter_i1;
  CDataInt64Vector *piter_ih1;
  CDataInt64Vector *piter_niteri;
  CDataInt64Vector *piter_niterih;
  CDataInt64Vector *piter_niterigh;
  CDataInt64Vector *piter_niteri1;
  CDataInt64Vector *piter_niterih1;
  CDataInt64 *piter_iall;
  CDataInt64 *piter_ihall;
  CDataInt64 *piter_ighall;
  CDataInt64 *piter_niteriall;
  CDataInt64 *piter_niterihall;
  CDataInt64 *piter_niterighall;
  CDataInt *output;
  CDataInt64 *nseed;
  CDataInt64 *length_seg;
  
  // Outputs
  // Empty
  
  
  public:
  CCalcMstatspopOutput();
  virtual ~CCalcMstatspopOutput();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);
  
 public:
  ICalculation* clone() const { return new CCalcMstatspopOutput(); /*clone*/  }
};

#endif  // CALCULATIONS_CALCS_CCALCMSTATSPOPOUTPUT_H_
