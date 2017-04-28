/*
 * ngasp, a computational solution for performing next generation analysis of 
 * sequence polymorphisms using NGS data.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
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
 *  \brief     CCalcBoxPlotValues.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 27, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCBOXPLOTVALUES_H_
#define CALCULATIONS_CALCS_CCALCBOXPLOTVALUES_H_

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

class CCalcBoxPlotValues : public ICalculation {
 private:
  // Inputs
  CDataDoubleVector *array_;

  // Outputs
  CDataDouble *q1_;
  CDataDouble *median_;
  CDataDouble *q3_;
  CDataDouble *min_;
  CDataDouble *max_;
//  CDataDouble *higher_outlier_;
//  CDataDouble *lower_outlier_;
  CDataDoubleVector *outliers_;
                
 public:
  CCalcBoxPlotValues();
  virtual ~CCalcBoxPlotValues();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcBoxPlotValues(); /*clone*/  }
};

#endif  // CALCULATIONS_CALCS_CCALCBOXPLOTVALUES_H_
