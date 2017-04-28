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
 *  \brief     CCalcGFF.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 4, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCGFF_H_
#define CALCULATIONS_CALCS_CCALCGFF_H_

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"
#include <stdint.h>

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataIntMatrix.h"
#include "../../data_manager/Data/CDataDoubleVector.h"
#include "../../data_manager/Data/CDataStdString.h"


struct valuesgff
{
	char filename[256];
	char source[256];
	char feature[256];
	char strand[1];
	long int start;
	long int end;
	char score[256];
	char frame[1];
	char seqname[256];
	char gene_id[256];
	char transcript_id[256];
};

class CCalcGFF : public ICalculation {
 private:
  // Inputs
  CDataInt *include_unknown_;
  CDataInt *outgroup_presence_;
  CDataIntVector *vint_perpop_nsam_;
  CDataInt64 *npops_;
  CDataCharVector *dna_matrix_;
  CDataStdString *name_fileinputgff_;
  CDataCharVector *subset_positions_;
  CDataCharVector *genetic_code_;
  CDataCharVector *criteria_transcripts_;
  CDataInt *nsamuser_eff_;   // It was n_samp
  CDataInt64 *n_site_;
  
  // Outputs
  CDataDoubleVector *matrix_sizepos_;
  CDataDoubleVector *matrix_segrpos_;
  CDataInt64Vector *mhitbp_;
  CDataInt64 *nmhits_;
  
 public:
  CCalcGFF();
  virtual ~CCalcGFF();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

public:
  ICalculation* clone() const { return new CCalcGFF(); /*clone*/  }

 private:
  char **codons_sam;
  int *freq_codons;
  int codons_length;
  void FreeMemory(void);

  int use_gff(char *name_fileinputgff,char *subset_positions,char *genetic_code,
			double *matrix_sizepos,int n_samp,long int n_site,char *DNA_matr,
			double *matrix_segrpos,FILE *file_output,int include_unknown,
			char *criteria_transcripts, int type_output, long int *nmhits, long int *mhitbp,
			int outgroup_presence, int nsamoutg);
  int tripletnsamp(char *cod3n,char *DNA_matr,char strand,double *cmat,
					int n_samp,long int n_site,long int end,long int ii,
					FILE *file_output/*,int mainargc*/,int include_unknown,int type_output,
					long int *nmhits, long int *mhitbp, int outgroup_presence, int nsamoutg);
  int function_do_nfold_triplets(int n_fold[64][3], char *genetic_code, char tripletsN[64][4]);

};



#endif  // CALCULATIONS_CALCS_CCALCGFF_H_
