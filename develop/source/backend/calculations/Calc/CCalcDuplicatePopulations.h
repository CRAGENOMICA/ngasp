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
 *  \brief     CCalcDuplicatePopulations.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 16, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCDUPLICATEPOPULATIONS_H_
#define CALCULATIONS_CALCS_CCALCDUPLICATEPOPULATIONS_H_

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataCharVector.h"

class CCalcDuplicatePopulations : public ICalculation {
 private:
  // Inputs
  CDataInt64 *npops;
  CDataInt *ploidy;
  CDataInt *outgroup_presence;
  CDataInt *formatfile;
  
  // Outputs
  CDataIntVector *vint_perpop_nsam;
  CDataInt64 *int_total_nsam;
  
 public:
  CCalcDuplicatePopulations();
  virtual ~CCalcDuplicatePopulations();

public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

public:
  ICalculation* clone() const { return new CCalcDuplicatePopulations(); /*clone*/  }
};

#endif  // CALCULATIONS_CALCS_CCALCDUPLICATEPOPULATIONS_H_
