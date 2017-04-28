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
 *  \brief     CCalcOpenCoordinatesFile.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 14, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCOPENCOORDINATESFILE_H_
#define CALCULATIONS_CALCS_CCALCOPENCOORDINATESFILE_H_

#include <cstdio>

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataStdString.h"

class CCalcOpenCoordinatesFile : public ICalculation {
 private:
  // Inputs
  CDataStdString *file_wcoord;
  
  // Outputs
  CDataInt64Vector *wgenes;
  CDataInt64 *nwindows;
  
 public:
  CCalcOpenCoordinatesFile();
  virtual ~CCalcOpenCoordinatesFile();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcOpenCoordinatesFile(); /*clone*/  }
  
 private:
  FILE *file_wcoor_;
  
 private:
  int read_coordinates(FILE *file_output);
};



#endif  // CALCULATIONS_CALCS_CCALCOPENCOORDINATESFILE_H_
