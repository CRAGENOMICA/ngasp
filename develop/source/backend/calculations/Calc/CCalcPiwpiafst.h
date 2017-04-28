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
 *  \brief     CCalcPiwpiafst.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCPIWPIAFST_H_
#define CALCULATIONS_CALCS_CCALCPIWPIAFST_H_

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataDoubleVector.h"
#include "../../data_manager/Data/CDataDoubleMatrix.h"
#include "../../data_manager/Data/CDataDoubleCube.h"

#ifndef inMISSINGH
  #define MISSINGH 0
#else
  #define MISSINGH 2./32.
#endif

class CCalcPiwpiafst : public ICalculation {
 private:  
  // Inputs
  CDataIntVector *vint_perpop_nsam;
  CDataInt64 *npops;
  CDataCharVector *matrix_pol;
  CDataInt64Vector *matrix_sv;
  CDataDoubleMatrix *stats_tcga;
  CDataDoubleMatrix *stats_lengthamng;
  CDataInt *flaghky;
  CDataDoubleVector *stats_length2;
  CDataInt *formatfile;
  CDataInt64 *length;
  
  // Ouputs
  CDataDoubleCube *stats_sv;
  CDataDoubleCube *stats_svT;
  CDataDoubleVector *stats_fst;
  CDataDoubleVector *stats_fst1all;
  CDataDoubleVector *stats_fstHKY;
  CDataDoubleVector *stats_K;
  CDataDoubleVector *stats_KHKY;
  CDataDoubleVector *stats_pia;
  CDataDoubleVector *stats_piaHKY;
  CDataDoubleVector *stats_piT;
  CDataDoubleVector *stats_piTHKY;
  CDataDoubleVector *stats_piwHKY;
  CDataDoubleVector *stats_piw;
  CDataDoubleVector *stats_thetaTHKY;
  CDataDoubleVector *stats_piant;
  CDataDoubleVector *stats_piTnt;
  CDataDouble *stats_fstALL;
  
  
 public:
  CCalcPiwpiafst();
  virtual ~CCalcPiwpiafst();

 public:
  ICalculation* clone() const { return new CCalcPiwpiafst(); /*clone*/  }

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

private:
  /// P1 is the A/G, P2 is T/C and Q is transversions.
  double tn93(double gT,double gC,double gG,double gA, double P1, double P2, double Q,double len);
};

#endif /* CALCULATIONS_CALCS_CCALCPIWPIAFST_H_ */
