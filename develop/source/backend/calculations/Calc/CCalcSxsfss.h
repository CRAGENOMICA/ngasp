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
 *  \brief     CCalcSxsfss.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCSXSFSS_H_
#define CALCULATIONS_CALCS_CCALCSXSFSS_H_

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Vector.h"

class CCalcSxsfss : public ICalculation {
 private:
  // Inputs
  CDataInt *force_outgroup;
  CDataInt *outgroup_presence;
  CDataIntVector *nsam;
  CDataInt64 *npops;
  CDataCharVector *matrix_pol;
  CDataInt64Vector *matrix_pos;
  CDataInt64 *length;
  
  // Outputs
  CDataInt64Vector *sites_matrix;
  CDataInt64Vector *stats_sanc;
  
 public:
  CCalcSxsfss();
  virtual ~CCalcSxsfss();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcSxsfss(); /*clone*/  }

 private:
  int calc_sxsfss(CDataInt64 *npops,
                  CDataIntVector *nsam,
                  CDataCharVector *matrix_pol,
                  CDataInt64Vector *matrix_pos,
                  CDataInt64 *length,
                  CDataInt64Vector *sites_matrix,
                  CDataInt *outgroup_presence,
                  CDataInt *force_outgroup,
                  CDataInt64Vector *stats_sanc);
};



#endif /* CALCULATIONS_CALCS_CCALCSXSFSS_H_ */
