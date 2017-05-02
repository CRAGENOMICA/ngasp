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
 *  \brief     CCalcMstatspopOpenFastaFile.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 2, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCMSTATSPOPOPENFASTAFILE_H_
#define CALCULATIONS_CALCS_CCALCMSTATSPOPOPENFASTAFILE_H_

#include <cstdio>   // FILE
#include <string>

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"      // char
#include "../../data_manager/Data/CDataCharMatrix.h"
#include "../../data_manager/Data/CDataInt.h"             // int
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64Vector.h"     // int64
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataDouble.h"          // double
#include "../../data_manager/Data/CDataDoubleVector.h"
#include "../../data_manager/Data/CDataDoubleMatrix.h"
#include "../../data_manager/Data/CDataStdString.h"       // std::string

#include "../../util/zutil.h"

class CCalcMstatspopOpenFastaFile : public ICalculation {
 private:
  // Inputs
  CDataStdString *file_in_;
  CDataInt *ploidy_;
  CDataInt *outgroup_presence_;
  CDataIntVector *nsamuser_;
  CDataInt64 *npops_;
  CDataIntVector *sort_nsam_;
  
  // Outputs
  CDataInt64 *length_;
  CDataCharMatrix *names2_;
  CDataInt64 *n_site_;
  CDataCharVector *DNA_matr2_;
  CDataInt *n_samp_;
  CDataDoubleVector *matrix_segrpos_;
  CDataDoubleVector *matrix_sizepos_;
  CDataInt *nsamuser_eff_;
  
 public:
  CCalcMstatspopOpenFastaFile();
  virtual ~CCalcMstatspopOpenFastaFile();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcMstatspopOpenFastaFile(); /*clone*/  }

  int var_char(FILE *file_input,SGZip *input_gz, long int *count,int *c,int *n_sam,long int *n_sit,int *nseq,int *maxsam,char ***names,char **DNA_matr,
	long int *n_site,int excludelines,char *name_excluded,int *n_excl,int includelines,char *name_ingroups,char *name_outgroup,int outgroup,int nsamuser_eff,int ploidy);

  int assigna(FILE *file_input,SGZip *input_gz, int *c,int *nseq,int *maxsam,char ***names);
};



#endif  // CALCULATIONS_CALCS_CCALCMSTATSPOPOPENFASTAFILE_H_
