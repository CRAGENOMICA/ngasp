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
 *  \brief     CCalcCreateTFastaAnnotation.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_CALCULATIONS_CALC_CCALCCREATETFASTAANNOTATION_H_
#define BACKEND_SRC_CALCULATIONS_CALC_CCALCCREATETFASTAANNOTATION_H_

#include <string>

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/common/CGFFFile.h"
#include "../../data_manager/common/CTFastaInfo.h"
#include "../../data_manager/common/CTFastaAnnotation.h"

class CCalcCreateTFastaAnnotation : public ICalculation {
 private:// Inputs
  CDataStdString *input_tfasta_file_name;
  CDataStdString *input_gff_file_name;
  CDataStdString *annotation;
  CDataStdString *genetic_code;
  CDataStdString *output_tfa_file_name;
  
  // Outputs
  // None
  
 public:
  CCalcCreateTFastaAnnotation();
  virtual ~CCalcCreateTFastaAnnotation();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const {
    return new CCalcCreateTFastaAnnotation(); /*clone*/
  }
};

#endif  // BACKEND_SRC_CALCULATIONS_CALC_CCALCCREATETFASTAANNOTATION_H_
