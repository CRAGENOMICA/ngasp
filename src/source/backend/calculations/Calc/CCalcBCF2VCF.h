/*
 * ngaSP: the computational solution for next generation analysis of 
 * Sequence Polymorphisms.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
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
 *  \brief     CCalcBCF2VCF.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      April 25, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCBCF2VCF_H_
#define CALCULATIONS_CALCS_CCALCBCF2VCF_H_

#include "../ICalculation.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataBCF.h"
#include "../../data_manager/Data/CDataVCF.h"


class CCalcBCF2VCF : public ICalculation {
 private:// Inputs
  CDataBCF *bcf;
  
  // Outputs
  CDataVCF *vcf;
  
 public:
  CCalcBCF2VCF();
  virtual ~CCalcBCF2VCF();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcBCF2VCF(); /*clone*/  }
};

#endif  // CALCULATIONS_CALCS_CCALCBCF2VCF_H_
