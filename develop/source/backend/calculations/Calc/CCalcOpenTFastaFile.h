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
 *  \brief     CCalcOpenTFastaFile.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 13, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCOPENTFASTAFILE_H_
#define CALCULATIONS_CALCS_CCALCOPENTFASTAFILE_H_

#include <cstdio>

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataFloatVector.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataDoubleVector.h"

#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataCharMatrix.h"

#include "../../util/zutil.h"

class CCalcOpenTFastaFile : public ICalculation {
 private:  
  CDataStdString *file_in;
  CDataInt64 *nwindows;
  CDataInt64Vector *wgenes;
  CDataInt64 *wlimit_end;
  CDataFloatVector *wP;
  CDataFloatVector *wPV;
  CDataInt *ploidy;
  CDataInt64 *npops;
  CDataInt *outgroup_presence;
  CDataIntVector *nsamuser;
  CDataInt *physical_length;
  CDataInt64 *window;
  CDataInt64 *slide;
  CDataIntVector *sort_nsam;    

  CDataInt64 *n_site;
  CDataCharMatrix *names;            // names2_
  CDataCharVector *DNA_matr;         // DNA_matr2_
  CDataDoubleVector *vector_priors;
  CDataInt64Vector *mhitbp;
  CDataDoubleVector *matrix_sizepos;
  CDataDoubleVector *matrix_segrpos;
  CDataInt *n_samp;
  CDataInt64 *li;
  CDataInt64 *length;
  CDataInt *npriors;
  CDataInt *nsamuser_eff;
  CDataInt64 *beg;
  CDataInt *the_result;
  
  
 public:
  CCalcOpenTFastaFile();
  virtual ~CCalcOpenTFastaFile();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcOpenTFastaFile(); /*clone*/  }
  
 private:
  FILE *file_input_;
  SGZip input_gz_;
 
 private:
  int get_tfadata(FILE *file_output);
        
  int function_read_tfasta(long int init_site,
                           long int end_site,
                           int *n_sam);  
};



#endif  // CALCULATIONS_CALCS_CCALCOPENTFASTAFILE_H_
