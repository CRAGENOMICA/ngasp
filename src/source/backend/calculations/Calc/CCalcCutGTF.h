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
 *  \brief     CCalcCutGTF.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      February 10, 2017
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCUT_GTF_H_
#define CALCULATIONS_CALCS_CCALCUT_GTF_H_

#include "../ICalculation.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataGTF.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataBoolean.h"

class CCalcCutGTF : public ICalculation {
 private:
  // Inputs
  CDataGTF *input_gtf_file_;
  CDataStdString *selection_;
  CDataBoolean *input_sorted_;
  CDataBoolean *keep_intermediate_results;
  
  // Outputs
  CDataGTF *output_gtf_file_;

  
public:
  CCalcCutGTF();
  virtual ~CCalcCutGTF();

public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

public:
  ICalculation* clone() const { return new CCalcCutGTF(); /*clone*/  }
};

#endif  // CALCULATIONS_CALCS_CCALCUT_GTF_H_
