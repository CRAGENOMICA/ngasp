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
 *  \brief     CCalcMstatspopOpenFastaFile.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 2, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcMstatspopOpenFastaFile.h"


#include <cstring>  // strcmp
#include <cmath>    // floor
#include <cstdio>   // FILE
#include <string>

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../CAllCalculations.h"
#include "../Calc/CCalcFileStats.h"

CCalcMstatspopOpenFastaFile::CCalcMstatspopOpenFastaFile()
: ICalculation(KeyString::CALC_MSTATSPOP_OPEN_FASTA,
               KeyString::CALC_MSTATSPOP_OPEN_FASTA_BRIEF_DESC,
               KeyString::CALC_MSTATSPOP_OPEN_FASTA_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(file_in_,                                                    // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_INPUT_INFO(ploidy_,                                                     // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_INPUT_INFO(outgroup_presence_,                                          // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_INPUT_INFO(nsamuser_,                                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_INPUT_INFO(npops_,                                                      // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_INPUT_INFO(sort_nsam_,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  
    SET_OUTPUT_INFO(length_,                                                    // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_OUTPUT_INFO(names2_,                                                    // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_OUTPUT_INFO(n_site_,                                                    // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_OUTPUT_INFO(DNA_matr2_,                                                 // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_OUTPUT_INFO(n_samp_,                                                    // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_OUTPUT_INFO(matrix_segrpos_,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_OUTPUT_INFO(matrix_sizepos_,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_OUTPUT_INFO(nsamuser_eff_,                                              // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcMstatspopOpenFastaFile::~CCalcMstatspopOpenFastaFile() {
}

void CCalcMstatspopOpenFastaFile::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(file_in_)
    DM_INPUT(ploidy_)
    DM_INPUT(outgroup_presence_)
    DM_INPUT(nsamuser_)
    DM_INPUT(npops_)
    DM_INPUT(sort_nsam_)
  DM_GET_OUTPUTS
    DM_OUTPUT(length_)
    DM_OUTPUT(names2_)
    DM_OUTPUT(n_site_)
    DM_OUTPUT(DNA_matr2_)
    DM_OUTPUT(n_samp_)
    DM_OUTPUT(matrix_segrpos_)
    DM_OUTPUT(matrix_sizepos_)
    DM_OUTPUT(nsamuser_eff_)
  DM_END
}

void CCalcMstatspopOpenFastaFile::Calculate(bool dry_run) {
  if (dry_run == true) {
     return;
  } 
 
  FILE *file_output = manager()->foutput();
  FILE *file_input = NULL;
  SGZip input_gz;

  // Opening files
  if (file_in_->value() == "") {
    file_input = stdin;
  }
  else {
    if ((file_input = fopen( file_in_->value().c_str(), "r")) == 0) {
      ERROR_MSG << "It is not possible to open the input file "
                << file_in_->value()
                END_MSG;
      return;
    }
    
    //==========================================================================
    init_gzip_structure(&input_gz);
    input_gz.file_compressed = 0;
    if (file_in_->value().length() > 3) {
      if((file_in_->value()[file_in_->value().length()-3] == '.') &&
           (file_in_->value()[file_in_->value().length()-2] == 'g') &&
           (file_in_->value()[file_in_->value().length()-1] == 'z')) {
          input_gz.file_compressed = 1;
      }
    }
    //==========================================================================  
  }

  
  //!added ++++++++++++++++++++++++++++
  int nPloidy = ploidy_->value();
  //+++++++++++++++++++++++++++++++++++

  
  static char *DNA_matr = 0;
  static char **names = 0; /* limit of the name of the lines to 50 characters. be careful ... */

	//long int *mhitbp; /*vector of positions where mhits are*/  //!removed because it is not used
    long int count,xx;
    int c;
    int n_sam,ns;
    long int n_sit;
    int nseq;
    int maxsam;
	int n_excl;
        
    int x;
	static long int maxsites = 0;
	
	/*all these variables are zero because are not used here*/
	int excludelines = 0;
	char *name_excluded = 0;
	int includelines = 0;
	char *name_ingroups = 0;
	char *name_outgroup = 0;
	int outgroup = 0;
	int nsamtot;
	int flag_change_sort; /*in case the order of samples is not consecutive*/
		
    count = 0;
    c = 0;
    n_sam = 0;
    n_sit = 0;
    nseq  = 0;
    maxsam= 128;
    n_samp_->set_value(0);
    n_site_->set_value(0);
	n_excl= 0;
	
	nsamtot = 0;
	for(x=0;x<npops_->value();x++) {
		nsamtot += (*nsamuser_)[x];
	}
	
	nsamuser_eff_->set_value((nsamtot- !outgroup_presence_->value())/nPloidy);
	
    if(names == 0) { /* only initialize once. Check */
        if((names = (char **)calloc(128,sizeof(char *))) == 0) {
            fprintf(file_output,"\nError: memory not reallocated. get_obsdata.1 \n");
            return;
        }
        for(x=0;x<128;x++) {
            if((names[x] = (char *)calloc(50,sizeof(char))) == 0) {
                fprintf(file_output,"\nError: memory not reallocated. get_obsdata.2 \n");
                return;
            }
        }    
        if((DNA_matr = (char *)calloc(10000,sizeof(char))) == 0) {
			for(x=0;x<128;x++) free(names[x]); free(names);
            fprintf(file_output,"\nError: memory not reallocated. get_obsdata.3 \n");
            return;
        }
        
    }
    
    c = fzgetc(file_input, &input_gz);
    while (c != 0 && c != -1 /*&& n_sam < nsamuser_eff_->value()*/) {
        while(c == 32 || c == 9 || c == 13 || c == 10 || c == '*') c = fzgetc(file_input, &input_gz);
        n_sit = 0;
        long int aux_n_site = n_site_->value();
        int aux_nsamuser_eff = nsamuser_eff_->value();
        if(!(var_char(file_input,&input_gz,&count,&c,&n_sam,&n_sit,&nseq,&maxsam,&names,&DNA_matr,&aux_n_site,excludelines,name_excluded,&n_excl,includelines,name_ingroups,name_outgroup,outgroup,aux_nsamuser_eff,ploidy_->value()))) {
          n_site_->set_value(aux_n_site);
          nsamuser_eff_->set_value(aux_nsamuser_eff);
          return;
        } else {
          n_site_->set_value(aux_n_site);
          nsamuser_eff_->set_value(aux_nsamuser_eff);
        }
        if(n_sam == 32767) {
            fprintf(file_output,"Only 32767 samples per loci are allowed.\n");
            break;
        }
    }
    n_samp_->set_value(n_sam);
	length_->set_value(n_site_->value());
	
	/*modify the order of samples using option flag O*/
	flag_change_sort = 0;
  for(x=0;x<nsamuser_eff_->value();x++) {
		if((*sort_nsam_)[x] != x) {
			flag_change_sort = 1;
			break;
		}
	}
	if(flag_change_sort == 1) {
		/*define duplicated matr*/
    DNA_matr2_->ReserveMemory(n_site_->value() * n_samp_->value(), STR(DEFAULT_CHAR)[0]);
//		if ((DNA_matr2 = (char *)calloc(n_site_->value()*(long long)n_samp_->value(),sizeof(char))) == 0) {
//			fprintf(file_output,"\nError: memory not reallocated. get_obsdata.23d \n");
//			for(x=0;x<n_samp_->value();x++) free(names[x]); free(names);
//			free(DNA_matr);
//			return;
//		}
    names2_->ReserveMemory(n_samp_->value(), 50, STR(DEFAULT_CHAR)[0]);
//		if(((*names2_) = (char **)calloc(n_samp_->value(),sizeof(char *))) == 0) {
//			fprintf(file_output,"\nError: memory not reallocated. get_obsdata.1s2 \n");
//			for(x=0;x<n_samp_->value();x++) free(names[x]); free(names);
//			free(DNA_matr);
//			return;
//		}
		for(x=0;x<n_samp_->value();x++) {
//			if(((*names2_)[x] = (char *)calloc(50,sizeof(char))) == 0) {
//				fprintf(file_output,"\nError: memory not reallocated. get_obsdata.22 \n");
//				for(x=0;x<n_samp_->value();x++) free(names[x]); free(names);
//				free(DNA_matr);
//				return;
//			}
			/*copy duplicated data*/
			strncpy((*DNA_matr2_)+(long long)n_site_->value()*(long long)x,DNA_matr+(long long)n_site_->value()*(long long)x,n_site_->value());			
      //!20160504
			//strncpy((*names2_)[x],names[x],50);
      //!20160504
      (*names2_)[x].set_text_string(std::string(names[x]).substr(0, 50));
		}
		/*end define and duplicate*/
		
		/*include data in *DNA_matr and in *names[] in the correct order*/
		for(x=0;x<nsamuser_eff_->value();x++) {
			strncpy(DNA_matr+(long long)n_site_->value()*(long long)x,(*DNA_matr2_)+(long long)n_site_->value()*(long long)(*sort_nsam_)[x],n_site_->value());			
			strncpy(names[x],(*names2_)[(*sort_nsam_)[x]].GetDataString(false),50);
		}
		/*delete duplicated matr*/
		//for(x=0;x<n_samp_->value();x++) free((*names2_)[x]); free((*names2_));
    names2_->DeleteMemory();
		DNA_matr2_->DeleteMemory();
		
		/*erase lines no used*/
		if(nsamuser_eff_->value() > n_samp_->value()) {
			fprintf(file_output,"Error: too low samples in the file according to defined in -N flag.\n");
			for(x=0;x<n_sam;x++) free(names[x]); free(names);
			free(DNA_matr);
			return;
		}
	}
	/*end option flag O*/
    
	if(n_samp_->value() * nPloidy < nsamtot-!outgroup_presence_->value()) return;
    if(n_samp_->value() == 0 || n_site_->value() == 0) return;
    else {
        if(nsamuser_eff_->value() > 32767) {
            fprintf(file_output,"Error: too much samples. Only 32767 samples per loci are allowed.\n");
            return;
        }
		/*init matrix_sizepos*/
		if((*matrix_sizepos_).GetData() == 0) {
			matrix_sizepos_->ReserveMemory(n_site_->value(), 0.0);
//      if(((*matrix_sizepos_) = (double *)malloc(n_site_->value()*sizeof(double))) == 0) {
//				fprintf(file_output,"Error: memory not reallocated. get_obsstat.2"); 
//				for(x=0;x<n_sam;x++) free(names[x]); free(names);
//				free(DNA_matr);
//				return;
//			}
      matrix_segrpos_->ReserveMemory(n_site_->value(), 0);
//			if(((*matrix_segrpos_) = (double *)malloc(n_site_->value()*sizeof(double))) == 0) {
//				fprintf(file_output,"Error: memory not reallocated. get_obsstat.2"); 
//				for(x=0;x<n_sam;x++) free(names[x]); free(names);
//				free(DNA_matr);
//				free((*matrix_sizepos_));
//				return;
//			}
			maxsites = n_site_->value();
		}
		else{
			if(n_site_->value() > maxsites) {
				matrix_sizepos_->ReallocMemory(n_site_->value(), 0.0);
//        if(((*matrix_sizepos_) = (double *)realloc((*matrix_sizepos_),n_site_->value()*sizeof(double))) == 0) {
//					fprintf(file_output,"Error: memory not reallocated. get_obsstat.2b"); 
//					for(x=0;x<n_sam;x++) free(names[x]); free(names);
//					free(DNA_matr);
//					return;
//				}
        matrix_segrpos_->ReallocMemory(n_site_->value(), 0.0);
//				if(((*matrix_segrpos_) = (double *)realloc((*matrix_segrpos_),n_site_->value()*sizeof(double))) == 0) {
//					fprintf(file_output,"Error: memory not reallocated. get_obsstat.2b"); 
//					for(x=0;x<n_sam;x++) free(names[x]); free(names);
//					free(DNA_matr);
//					free((*matrix_sizepos_));
//					return;
//				}
				maxsites = n_site_->value();
			}
		}
		for(xx=0;xx<n_site_->value();xx++) {
			(*matrix_sizepos_)[xx] = (double)1;
			(*matrix_segrpos_)[xx] = (double)1;
		}
		if(ploidy_->value() == DIPLOID){
			DNA_matr2_->ReserveMemory(n_site_->value() * nsamuser_eff_->value() * 2, STR(DEFAULT_CHAR)[0]);
//      if (((*DNA_matr2_) = (char *)calloc(n_site_->value()*(long long)n_samp_->value()*2,sizeof(char))) == 0) {
//				fprintf(file_output,"\nError: memory not reallocated. get_obsdata.23 \n");
//				for(x=0;x<n_sam;x++) free(names[x]); free(names);
//				free(DNA_matr);
//				free((*matrix_sizepos_));
//				free((*matrix_segrpos_));
//				return;
//			}
			names2_->ReserveMemory(nsamuser_eff_->value() * 2, 50, STR(DEFAULT_CHAR)[0]);
//      if(((*names2_) = (char **)calloc(n_samp_->value()*2,sizeof(char *))) == 0) {
//				fprintf(file_output,"\nError: memory not reallocated. get_obsdata.12 \n");
//				return(0);
//			}
//			for(x=0;x<n_samp_->value()*2;x++) {
//				if(((*names2_)[x] = (char *)calloc(50,sizeof(char))) == 0) {
//					fprintf(file_output,"\nError: memory not reallocated. get_obsdata.22 \n");
//					return;
//				}
//			}
			for(x=0;x<nsamuser_eff_->value();x++) {
				strncpy((*DNA_matr2_)+(long long)n_site_->value()*(long long)x*2,DNA_matr+(long long)n_site_->value()*(long long)x,n_site_->value());
				strncpy((*DNA_matr2_)+(long long)n_site_->value()*(long long)(x*2+1),DNA_matr+(long long)n_site_->value()*(long long)x,n_site_->value());	
				
        //!20160504
//				strncpy((*names2_)[x*2],names[x],50);
//				strncpy((*names2_)[x*2+1],names[x],50);
//				strncat((*names2_)[x*2],".1\0",50);
//				strncat((*names2_)[x*2+1],".2\0",50);

        //!20160504
        (*names2_)[x*2].set_text_string(std::string(names[x]).substr(0, 50) + ".1");
        (*names2_)[x*2+1].set_text_string(std::string(names[x]).substr(0, 50) + ".2");
			}
      
			for(xx=0;xx<n_site_->value();xx++) {
				for(x=0;x<nsamuser_eff_->value();x++) {
					if((*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] == 'w') {
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] = '1';
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)(x*2+1) + xx] = '4';
					}
					if((*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] == 'm') {
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] = '2';
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)(x*2+1) + xx] = '4';
					}
					if((*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] == 'r') {
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] = '3';
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)(x*2+1) + xx] = '4';
					}
					if((*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] == 'y') {
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] = '1';
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)(x*2+1) + xx] = '2';
					}
					if((*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] == 'k') {
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] = '1';
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)(x*2+1) + xx] = '3';
					}
					if((*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] == 's') {
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] = '2';
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)(x*2+1) + xx] = '3';
					}
					if((*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] == 't') {
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] = '1';
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)(x*2+1) + xx] = '5';
					}
					if((*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] == 'c') {
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] = '2';
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)(x*2+1) + xx] = '5';
					}
					if((*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] == 'g') {
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] = '3';
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)(x*2+1) + xx] = '5';
					}
					if((*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] == 'a') {
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)x*2 + xx] = '4';
						(*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)(x*2+1) + xx] = '5';
					}
				}
			}
			nsamuser_eff_->set_value(nsamuser_eff_->value() * 2);
		}
		else {
			DNA_matr2_->ReserveMemory(n_site_->value() * nsamuser_eff_->value(), STR(DEFAULT_CHAR)[0]);
//      if(((*DNA_matr2_) = (char *)calloc((long long)n_site_->value()*n_samp_->value(),sizeof(char))) == 0) {
//				fprintf(file_output,"\nError: memory not reallocated. get_obsdata.23 \n");
//				for(x=0;x<n_sam;x++) free(names[x]); free(names);
//				free(DNA_matr);
//				free((*matrix_sizepos_));
//				free((*matrix_segrpos_));
//				return(0);
//			}
      names2_->ReserveMemory(nsamuser_eff_->value() * 1, 50, STR(DEFAULT_CHAR)[0]);
//			if(((*names2_) = (char **)calloc(n_samp_->value()*1,sizeof(char *))) == 0) {
//				fprintf(file_output,"\nError: memory not reallocated. get_obsdata.12 \n");
//				return(0);
//			}
//			for(x=0;x<n_samp_->value()*1;x++) {
//				if(((*names2_)[x] = (char *)calloc(50,sizeof(char))) == 0) {
//					fprintf(file_output,"\nError: memory not reallocated. get_obsdata.22 \n");
//					return(0);
//				}
//			}
			for(x=0;x<nsamuser_eff_->value()*1;x++) {
				strncpy((*DNA_matr2_)+(long long)n_site_->value()*(long long)x,DNA_matr+(long long)n_site_->value()*(long long)x,n_site_->value());				
        //!20160504
				//strncpy((*names2_)[x],names[x],50);
        //!20160504
        (*names2_)[x].set_text_string(std::string(names[x]).substr(0, 50));
			}
		}
		if(outgroup_presence_->value() == 0) {
			DNA_matr2_->ReallocMemory(n_site_->value() * (nsamuser_eff_->value()+!outgroup_presence_->value()), STR(DEFAULT_CHAR)[0]);
//      if (((*DNA_matr2_) = (char *)realloc((*DNA_matr2_),(long long)n_site_->value()*(n_samp_->value()+1)*sizeof(char))) == 0) {
//				fprintf(file_output,"\nError: memory not reallocated. get_obsdata.23a \n");
//				for(x=0;x<n_sam;x++) free(names[x]); free(names);
//				free(DNA_matr);
//				free((*DNA_matr2_));
//				free((*matrix_sizepos_));
//				free((*matrix_segrpos_));
//				return(0);
//			}
			/*we forced the invented outgroup without gaps or uncertainties, if possible*/
			/*strncpy((*DNA_matr2_)+(unsigned long)n_site_->value()*(unsigned long)(n_samp_->value()),(*DNA_matr2_)+(unsigned long)n_site_->value()*(unsigned long)(n_samp_->value()-1),n_site_->value());*/
			for(xx=0;xx<n_site_->value();xx++) {
				ns = 0;
				while(ns < nsamuser_eff_->value()-1 && (*DNA_matr2_)[(long long)n_site_->value()*(unsigned long)ns+xx] > '4') ns++;
				(*DNA_matr2_)[(unsigned long)n_site_->value()*(long long)(nsamuser_eff_->value())+xx] = (*DNA_matr2_)[(unsigned long)n_site_->value()*(unsigned long)ns+xx];
			}
			
			nsamuser_eff_->add(1);
		}
  }
}

void CCalcMstatspopOpenFastaFile::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

int CCalcMstatspopOpenFastaFile::var_char(FILE *file_input,SGZip *input_gz, long int *count,int *c,int *n_sam,long int *n_sit,int *nseq,int *maxsam,char ***names,char **DNA_matr,
	long int *n_site,int excludelines,char *name_excluded,int *n_excl,int includelines,char *name_ingroups,char *name_outgroup,int outgroup,int nsamuser_eff,int ploidy)
{
    int  aa = 0;
    int  bb = 0;
    long int  dd;
    double ee;
    char *strin;
    /*long long t;*/
    
    aa = assigna(file_input,input_gz,c,nseq,maxsam,names);
	if(aa == 1) {
		if(outgroup > 0) {
			if(((strin = strstr(names[0][*nseq-1],name_outgroup)) == 0)) {
				if(excludelines > 0) {
					if(((strin = strstr(names[0][*nseq-1],name_excluded)) != 0)) {
						*nseq -= 1;
						*n_excl += 1;
						*c = fzgetc(file_input, input_gz);
						while(*c != '*' && *c != -1 && *c != 0 && *c != '>')
							*c = fzgetc(file_input, input_gz);
						aa = 0;
					}
				}
				if(includelines > 0) {
					if(((strin = strstr(names[0][*nseq-1],name_ingroups)) == 0)) {
						*nseq -= 1;
						*n_excl += 1;
						*c = fzgetc(file_input, input_gz);
						while(*c != '*' && *c != -1 && *c != 0 && *c != '>')
							*c = fzgetc(file_input, input_gz);
						aa = 0;
					}
				}
			}
		}
		else {
			if(excludelines > 0) {
				if(((strin = strstr(names[0][*nseq-1],name_excluded)) != 0)) {
					*nseq -= 1;
					*n_excl += 1;
					*c = fzgetc(file_input, input_gz);
					while(*c != '*' && *c != -1 && *c != 0 && *c != '>')
						*c = fzgetc(file_input, input_gz);
					aa = 0;
				}
			}
			if(includelines > 0) {
				if(((strin = strstr(names[0][*nseq-1],name_ingroups)) == 0)) {
					*nseq -= 1;
					*n_excl += 1;
					*c = fzgetc(file_input, input_gz);
					while(*c != '*' && *c != -1 && *c != 0 && *c != '>')
						*c = fzgetc(file_input, input_gz);
					aa = 0;
				}
			}
		}
	}
    if(aa == 1) {
        while(bb == 0) {
            dd = (long int)floor((double)*count/(double)10000);
            ee = (double)*count/(double)10000;
            
            if(dd == ee) {
				/*
                if((t=(((long int)dd+(long int)1)*(long int)10000)) > 2147483647) {
                    puts("Error: too much positions.\n");
                    return(0);
                }
				*/
                if((*DNA_matr = (char *)realloc(*DNA_matr,((long long)dd+(long long)1)*(long long)10000*sizeof(char))) == 0) {  //! cast added
                    puts("Error: realloc error varchar.1\n");
                    return(0);
                }    
            }
            switch(*c/* = fzgetc(file_input, input_gz);*/) {
                case 'T':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '1';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 't':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '1';
					if(ploidy==DIPLOID)
						DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 't';
					*count += 1;
                    *n_sit += 1;
                    break;
                case 'U':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '1';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'u':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '1';
					if(ploidy==DIPLOID)
						DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 't';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'C':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '2';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'c':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '2';
					if(ploidy==DIPLOID)
						DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'c';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'G':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '3';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'g':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '3';
					if(ploidy==DIPLOID)
						DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'g';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'A':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '4';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'a':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '4';
					if(ploidy==DIPLOID)
						DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'a';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 0:
                    bb = 1; /*in FASTA case*/
                    break;
                case -1:
                    bb = 1; /*in FASTA case*/
                    break;
                case 10:
                    break;
                case 13:
                    break;
                case 32:
                    break;
                case '*': /* in NBRF case*/
                    bb = 1;
                    break;
                case '>': /* in FASTA case*/
                    bb = 1;
                    break;
				case 'N':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'n':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case '?':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
                    break;
				case '-':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '6';
                    *count += 1;
                    *n_sit += 1;
                    break;
                /*degenerated are converted to N*/
                case 'W':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'w';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'w':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'w';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'M':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'm';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'm':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'm';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'R':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'r';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'r':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'r';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'Y':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'y';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'y':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'y';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'K':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'k';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'k':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'k';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'S':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 's';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 's':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 's';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'b':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'B':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'd':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'D':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'h':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'H':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
                    break;
				case 'v':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
                    break;
                case 'V':
                    DNA_matr[0][(((long long)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
                    break;
				default:
                    puts("Unexpected value in file");
                    printf("%d",*c);
                    return(0);
                    break;
            }
            if(*c !='>'/*|| *c != 0 || *c != -1*/) *c = fzgetc(file_input, input_gz);
        }
        *n_sam += 1;
        if(*n_site == 0) *n_site = *n_sit;
        else if(*n_site != *n_sit) {
            puts("The number of sites are not equal in all lines in the alignment.");
            return(0);
        }
    }
    return 1;
}

int CCalcMstatspopOpenFastaFile::assigna(FILE *file_input,SGZip *input_gz,int *c,int *nseq,int *maxsam,char ***names)
{
    int N_VAR = 2;
    char var_file[2][50]  =
    {
        { ">"},
        { ">DL;"},
    };

    int i_;
    int j;
    int nn;
    int x;
    int c0; 
    
    j = 0;
    for(i_=0;i_<N_VAR;i_++) {
        while((var_file[i_][j]) == *c && (var_file[i_][j]) != '\0' && *c != '\0') {  //!added *c != '\0'
            *c = fzgetc(file_input, input_gz);
            j++;
        }
    }
    if(j<4 && j>0) i_= 1;/*FASTA*/
    else if(j==4) i_= 2;/*NBRF*/
        else {
            i_=0;/*NO ACCEPTED*/
            if(*c != 0 && *c != -1) *c = fzgetc(file_input, input_gz);
        }
        
    if((i_ == 2  && *c != 0 && *c != -1)) { /* NBRF files */
        nn = 0;
        while(*c != '\0' && *c != 13 && *c != 10 && nn < 50-2) {
            if(*c != '\t' && *c != 32) {
				names[0][*nseq][nn] = (char)*c;
				nn++;
			}
			*c = fzgetc(file_input, input_gz);
        }
        names[0][*nseq][nn] = '\0';
        *nseq += 1;
        if(*nseq == *maxsam) {
            *maxsam += 32;
            if(*maxsam > 32767) {
                puts("\n Sorry, no more samples are allowed.");
                    return 0;
            }
            if ((*names = (char **)realloc(*names,*maxsam*sizeof(char *))) == 0) {
                puts("\nError: memory not reallocated. assigna.1 \n");
                return(0);
            }
            for(x=*nseq;x<*maxsam;x++) {
                if ((names[0][x] = (char *)calloc(50,sizeof(char))) == 0) {
                    puts("\nError: memory not reallocated. assigna.2 \n");
                    return(0);
                }
            }
        }
        /*use unix or macos or dos format. begin*/
        while(*c != '\0' && *c != 13 && *c != 10 && *c != -1 && *c != 0)
            *c = fzgetc(file_input, input_gz);

        c0 = *c;
        *c = fzgetc(file_input, input_gz);
        if(c0 == 13 && *c == 10) *c = fzgetc(file_input, input_gz);
        while(*c != 10 && *c != 13 && *c != -1 && c != 0) 
            *c = fzgetc(file_input, input_gz);
        if(*c == -1 || *c == 0) {
            puts("\n Unexpected end of file");
            return(0);
        }
        c0 = *c;
        *c = fzgetc(file_input, input_gz);
        if(c0 == 13 && *c == 10) *c = fzgetc(file_input, input_gz);
        if(*c == -1 || *c == 0) {
            puts("\n Unexpected end of file");
            return(0);
        }
        /*use unix or macos or dos format. end*/
        
        return(1);
    }
    else {	
        if(i_ == 1 && *c != 0 && *c != -1) {	/* FASTA files */
            nn = 0;
            while(*c != '\0' && *c != 13 && *c != 10 && nn < 50-2) {
				if(*c != '\t' && *c != 32) {
					names[0][*nseq][nn] = (char)*c;
					nn++;
				}
				*c = fzgetc(file_input, input_gz);
            }
            names[0][*nseq][nn] = '\0';
            *nseq += 1;
            if(*nseq == *maxsam) {
                *maxsam += 32;
                if(*maxsam > 32767) {
                    puts("\n Sorry, no more samples are allowed.");
                        return 0;
                }
                if ((*names = (char **)realloc(*names,*maxsam*sizeof(char *))) == 0) {
                    puts("\nError: memory not reallocated. assigna.1 \n");
                    return(0);
                }
                for(x=*nseq;x<*maxsam;x++) {
                    if ((names[0][x] = (char *)calloc(50,sizeof(char))) == 0) {
                        puts("\nError: memory not reallocated. assigna.2 \n");
                        return(0);
                    }
                }
            }
            /*use unix or macos or dos format. begin*/
            while(*c != '\0' && *c != 13 && *c != 10 && *c != -1 && *c != 0)
                *c = fzgetc(file_input, input_gz);
    
            c0 = *c;
            *c = fzgetc(file_input, input_gz);
            if(c0 == 13 && *c == 10) *c = fzgetc(file_input, input_gz);
            if(*c == -1 || *c == 0) {
                puts("\n Unexpected end of file");
                return 0;
            }
            /*use unix or macos or dos format. end*/
            return(1);
        }
        else return(0);
    }
    return 0;
}

