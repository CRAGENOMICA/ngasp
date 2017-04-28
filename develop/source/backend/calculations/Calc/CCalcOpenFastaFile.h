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
 *  \brief     CCalcOpenFastaFile.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCOPENFASTAFILE_H_
#define CALCULATIONS_CALCS_CCALCOPENFASTAFILE_H_

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataStringSet.h"
#include "../../data_manager/Data/CDataStdString.h"

class CCalcOpenFastaFile : public ICalculation {
 private:
  // Inputs
  CDataStdString *file_name;
  CDataInt *ploidy;
  CDataInt *include_unknown;
  CDataInt *force_outgroup;
  CDataInt *outgroup_presence;
  CDataIntVector *vint_perpop_nsam;
  CDataInt64 *npops;
  CDataInt64 *int_total_nsam;
  
  // Outputs
  CDataStringSet *fasta;
  
 public:
  CCalcOpenFastaFile();
  virtual ~CCalcOpenFastaFile();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcOpenFastaFile(); /*clone*/  }
};



#endif  // CALCULATIONS_CALCS_CCALCOPENFASTAFILE_H_
