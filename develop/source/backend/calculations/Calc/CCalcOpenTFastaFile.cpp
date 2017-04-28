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
 *  \brief     CCalcOpenTFastaFile.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 13, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcOpenTFastaFile.h"

/* #include <seqan/seq_io.h> */
#include <string.h>  //!added strncpy
#include <tgmath.h> //!added floor

#include <cstdio>

#include "../../language/CStringTable.h"
#include "../../calculations/util/CDnaTools.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
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

CCalcOpenTFastaFile::CCalcOpenTFastaFile()
: ICalculation(KeyString::CALC_OPEN_TFASTA,
               KeyString::CALC_OPEN_TFASTA_BRIEF_DESC,
               KeyString::CALC_OPEN_TFASTA_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(file_in,                                                     // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(nwindows,                                                    // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(wgenes,                                                      // Variable
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
    SET_INPUT_INFO(wlimit_end,                                                  // Variable
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
    SET_INPUT_INFO(wP,                                                          // Variable
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
    SET_INPUT_INFO(wPV,                                                         // Variable
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
    SET_INPUT_INFO(ploidy,                                                      // Variable
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
    SET_INPUT_INFO(npops,                                                       // Variable
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
    SET_INPUT_INFO(outgroup_presence,                                           // Variable
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
    SET_INPUT_INFO(nsamuser,                                                    // Variable
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
    SET_INPUT_INFO(physical_length,                                             // Variable
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
    SET_INPUT_INFO(window,                                                      // Variable
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
    SET_INPUT_INFO(slide,                                                       // Variable
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
    SET_INPUT_INFO(sort_nsam,                                                   // Variable
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
    SET_OUTPUT_INFO(n_site,                                                     // Variable
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
    SET_OUTPUT_INFO(names,                                                      // Variable
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
    SET_OUTPUT_INFO(DNA_matr,                                                   // Variable
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
    SET_OUTPUT_INFO(vector_priors,                                              // Variable
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
    SET_OUTPUT_INFO(mhitbp,                                                     // Variable
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
    SET_OUTPUT_INFO(matrix_sizepos,                                             // Variable
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
    SET_OUTPUT_INFO(matrix_segrpos,                                             // Variable
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
    SET_OUTPUT_INFO(n_samp,                                                     // Variable
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
    SET_OUTPUT_INFO(li,                                                         // Variable
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
    SET_OUTPUT_INFO(length,                                                     // Variable
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
    SET_OUTPUT_INFO(npriors,                                                    // Variable
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
    SET_OUTPUT_INFO(nsamuser_eff,                                               // Variable
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
    SET_OUTPUT_INFO(beg,                                                        // Variable
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
    SET_OUTPUT_INFO(the_result,                                                 // Variable
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
    
  file_input_ = NULL;
}

CCalcOpenTFastaFile::~CCalcOpenTFastaFile() {
}

void CCalcOpenTFastaFile::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(file_in)
    DM_INPUT(nwindows)
    DM_INPUT(wgenes)
    DM_INPUT(wlimit_end)
    DM_INPUT(wP)
    DM_INPUT(wPV)
    DM_INPUT(ploidy)
    DM_INPUT(npops)
    DM_INPUT(outgroup_presence)
    DM_INPUT(nsamuser)
    DM_INPUT(physical_length)
    DM_INPUT(window)
    DM_INPUT(slide)
    DM_INPUT(sort_nsam)    
  DM_GET_OUTPUTS
    DM_OUTPUT(n_site)
    DM_OUTPUT(names)            // names2_
    DM_OUTPUT(DNA_matr)         // DNA_matr2_
    DM_OUTPUT(vector_priors)
    DM_OUTPUT(mhitbp)
    DM_OUTPUT(matrix_sizepos)
    DM_OUTPUT(matrix_segrpos)
    DM_OUTPUT(n_samp)
    DM_OUTPUT(li)
    DM_OUTPUT(length)
    DM_OUTPUT(npriors)
    DM_OUTPUT(nsamuser_eff)
    DM_OUTPUT(beg)
    DM_OUTPUT(the_result)
  DM_END
}

void CCalcOpenTFastaFile::Calculate(bool dry_run) {

  
  FILE *file_output = manager()->foutput();
 
  if (file_input_ == NULL) {
    // Opening files
    if (file_in->value() == "") {
      file_input_ = stdin;
    }
    else {
      if ((file_input_ = fopen(file_in->value().c_str(), "r")) == 0) {
        ERROR_MSG << "It is not possible to open the input file "
                  << file_in->value()
                  END_MSG;
        return;
      }
      
      //========================================================================
      init_gzip_structure(&input_gz_);
      input_gz_.file_compressed = 0;
      if (file_in->value().length() > 3) {
        if((file_in->value()[file_in->value().length()-3] == '.') &&
             (file_in->value()[file_in->value().length()-2] == 'g') &&
             (file_in->value()[file_in->value().length()-1] == 'z')) {
            input_gz_.file_compressed = 1;
        }
      }
      //========================================================================
    }
  }
  
  the_result->set_value(get_tfadata(file_output));
}

  
int CCalcOpenTFastaFile::get_tfadata(FILE *file_output) {
  ploidy->set_value(HAPLOID);
  
  n_site->set_value(0);
  n_samp->set_value(0);
    
  int n_sam                 = 0;
  int x                     = 0;
  int nsamtot               = 0;
  static long int init_site = 1;
  static long wc            = 0;
  long int lx               = 0;
  long int end              = 0;
  double wl                 = 0;
  char *DNA_matr2           = 0;
  char **names2             = 0;     // limit of the name of the lines to 50 characters. be careful ...
  long int xx               = 0;
  static long int maxsites  = 0;
  
//  long int n_site           = 0;
//  double *matrix_segrpos    = 0;     // always 1 except in those biallelic positions that are not desired (e.g., choose syn but we do not want nsyn)

  
//  double *matrix_sizepos    = 0;     // size of each position, 0 not include, >0 include, Syn/Nsyn positions are allowed
//  long int *mhitbp          = NULL;  // vector of positions where mhits are
//  long int count            = 0;

//  int c                     = 0;
//  int nseq                  = 0;
//  int maxsam                = 128;
//  int n_samp                = 0;

  int flag_change_sort      = 0;     // in case the order of samples is not consecutive

        
    for(x=0;x<npops->value();x++) {
        nsamtot += (*nsamuser)[x];  // abans nsamuser
    }    
    nsamuser_eff->set_value((nsamtot- !outgroup_presence->value()));
    
    //!20160504
    if((*names).Size() == 0) { /* only initialize once. Check */
        names->ReserveMemory(128, 50, '\x0');
        
//        if((names = (char **)calloc(128,sizeof(char *))) == 0) {
//          ERROR_MSG << "Error: memory not reallocated. get_obsdata.1"
//            END_MSG;
//            return 0;
//        }
//        for(x=0;x<128;x++) {
//            if((names[x] = (char *)calloc(50,sizeof(char))) == 0) {
//                ERROR_MSG << "Error: memory not reallocated. get_obsdata.2"
//                  END_MSG;
//                return 0;
//            }
//        }
        DNA_matr->ReserveMemory(10000, '\x0');
//        if((DNA_matr = (char *)calloc(10000,sizeof(char))) == 0) {
//            for(x=0;x<128;x++) free(names[x]); free(names);
//            ERROR_MSG << "Error: memory not reallocated. get_obsdata.3"
//              END_MSG;
//            return 0;
//        }
    }
    

	/*FIND THE WINDOW OF POSITIONS TO ANALYZE*/
	if(nwindows->value() == 0) {
		if(physical_length->value() == 1) {
			beg->set_value(init_site);/*the initial position of the window*/
			end = init_site + window->value() - 1;/*the final position of the window*/
			init_site += slide->value();/*init for next window (static variable)*/
		}
		else {/*if(physical_length->value() == 0)*/
			beg->set_value(init_site);/*the final position of the window*/
			end = beg->value();
			wl=0.0;
			while(wl<window->value() && end <= wlimit_end->value()) {
				wl += (*wP)[end-1] * (*wPV)[end-1];
				end += 1;
			}
			end -= 1;/*the final position of the window (static variable)*/
			
			lx = end;
			wl=0.0;
			while(wl<slide->value() && lx <= wlimit_end->value()) {
				wl += (*wP)[lx-1] * (*wPV)[lx-1];
				lx += 1;
			}
			init_site = lx;/*init for next window*/
		}
	}
	else {/*(nwindows->value() > 0)*//*that is, using coordinate positions*/
		beg->set_value((*wgenes)[wc++]);/*the initial position of the window*/
		end = (*wgenes)[wc++];/*the final position of the window*/
	}
   if((*vector_priors).GetData() == 0) {
        npriors->set_value(2);
        vector_priors->ReserveMemory(2, 0.0);
//        if((*vector_priors = (float *)calloc((long int)*npriors,sizeof(float)))==0) {
//            ERROR_MSG << "Error: memory not allocated. get_tfadata.01"
//              END_MSG;
//            return 1;
//        }
    }
    (*vector_priors)[0] = (double)beg->value();
    (*vector_priors)[1] = (double)end;
    
    /*READ TFASTA FILE*/
	/*define the init and the end site first! use slide and window if necessary: use also the weights if necessary*/	
	/*detect the end of the file! (*li=0,otherwise *li=-1)*/

    
    if((x=function_read_tfasta(beg->value(),
                               end,
                               &n_sam)) == 0) {
        ERROR_MSG << "Unable reading tfasta file"
          END_MSG;
        return 1;
    }
       
    if(x==-1) li->set_value(0);
    else li->set_value(-1);
	   
    n_samp->set_value(n_sam);
    length->set_value(n_site->value());
    
    if(n_samp->value() < nsamuser_eff->value())
        return 0;
    if(n_samp->value() == 0 || n_site->value() == 0)
        return 0;
    else {
        /*modify the order of samples using option flag O*/
        flag_change_sort = 0;
        for(x=0;x<nsamuser_eff->value();x++) {
            if((*sort_nsam)[x] != x) {
                flag_change_sort = 1;
                break;
            }
        }
        if(flag_change_sort == 1) {
            /*define duplicated matr*/
            if ((DNA_matr2 = (char *)calloc(n_site->value()*(long long)n_samp->value(),sizeof(char))) == 0) {
                ERROR_MSG << "Error: memory not reallocated. get_obsdata.23d"
                  END_MSG;
                names->DeleteMemory();
                DNA_matr->DeleteMemory();
//                for(x=0;x<n_samp->value();x++) free(names[x]); free(names);
//                free(DNA_matr);
                return 0;
            }
            if((names2 = (char **)calloc(n_samp->value(),sizeof(char *))) == 0) {
                ERROR_MSG << "Error: memory not reallocated. get_obsdata.1s2"
                  END_MSG;
                names->DeleteMemory();
                DNA_matr->DeleteMemory();
//                for(x=0;x<n_samp->value();x++) free(names[x]); free(names);
//                free(DNA_matr);
                return 0;
            }
            for(x=0;x<n_samp->value();x++) {
                if((names2[x] = (char *)calloc(50,sizeof(char))) == 0) {
                  ERROR_MSG << "Error: memory not reallocated. get_obsdata.22"
                    END_MSG;
                  names->DeleteMemory();
                  DNA_matr->DeleteMemory();
//                  for(x=0;x<n_samp->value();x++) free(names[x]); free(names);
//                  free(DNA_matr);
                  return 0;
                }
                /*copy duplicated data*/
                strncpy(names2[x],(*names)[x].GetData(),50);
            }
            strncpy(DNA_matr2+(long long)n_site->value()*(long long)0,(*DNA_matr)+(long long)n_site->value()*(long long)0,(long long)n_site->value()*n_samp->value());
            /*end define and duplicate*/
            
            /*include data in *DNA_matr and in *names[] in the correct order*/
            for(x=0;x<nsamuser_eff->value();x++) {
                strncpy((*DNA_matr)+(long long)n_site->value()*(long long)x,DNA_matr2+(long long)n_site->value()*(long long)(*sort_nsam)[x],n_site->value());
                //!20160504
                //strncpy((*names)[x],names2[(*sort_nsam)[x]],50);
                //!20160504
                (*names)[x].set_text_string(std::string(names2[(*sort_nsam)[x]]).substr(0,50));
                
            }
            /*delete duplicated matr*/
            for(x=0;x<n_samp->value();x++) free(names2[x]);
            free(names2);
            free(DNA_matr2);
            
            /*erase lines no used*/
            if(nsamuser_eff->value() > n_samp->value()) {
                ERROR_MSG << "Error: too low samples in the file according to defined in -N flag."
                  END_MSG;
                names->DeleteMemory();
                DNA_matr->DeleteMemory();
//                for(x=0;x<n_sam;x++) free(names[x]); free(names);
//                free(DNA_matr);
                return 0;
            }
        }
        /*end option flag O*/
  
        if(nsamuser_eff->value() > 32167) {
            ERROR_MSG << "Error: too much samples. Only 32167 samples per loci are allowed."
              END_MSG;
            return 0;
        }
  
  
        /*init matrix_sizepos*/
        if((*matrix_sizepos).GetData() == 0) {
              matrix_sizepos->ReserveMemory(n_site->value(), 0.0);
//            if((matrix_sizepos = (double *)malloc(n_site*sizeof(double))) == 0) {
//                ERROR_MSG << "Error: memory not reallocated. get_obsstat.2"
//                  END_MSG;
//                for(x=0;x<n_samp;x++) free(names[x]); free(names);
//                free(DNA_matr);
//                return 0;
//            }
              matrix_segrpos->ReserveMemory(n_site->value(), 0.0);
//            if((matrix_segrpos = (double *)malloc(n_site*sizeof(double))) == 0) {
//                ERROR_MSG << "Error: memory not reallocated. get_obsstat.2"
//                  END_MSG;
//                for(x=0;x<n_samp;x++) free(names[x]); free(names);
//                free(DNA_matr);
//                free(matrix_sizepos);
//                return 0;
//            }
            maxsites = n_site->value();
        }
        else{
            if(n_site->value() > maxsites) {
                matrix_sizepos->ReallocMemory(n_site->value(), 0.0);
//                if((matrix_sizepos = (double *)realloc(matrix_sizepos,n_site*sizeof(double))) == 0) {
//                    ERROR_MSG << "Error: memory not reallocated. get_obsstat.2b"
//                      END_MSG;
//                    for(x=0;x<n_samp;x++) free(names[x]); free(names);
//                    free(DNA_matr);
//                    return 0;
//                }
                matrix_segrpos->ReallocMemory(n_site->value(), 0.0);
//                if((matrix_segrpos = (double *)realloc(matrix_segrpos,n_site*sizeof(double))) == 0) {
//                    ERROR_MSG << "Error: memory not reallocated. get_obsstat.2b"
//                      END_MSG;
//                    for(x=0;x<n_samp;x++) free(names[x]); free(names);
//                    free(DNA_matr);
//                    free(matrix_sizepos);
//                    return 0;
//                }
                maxsites = n_site->value();
            }
        }
        
        for(xx=0;xx<n_site->value();xx++) {
            (*matrix_sizepos)[xx] = (double)1;
            (*matrix_segrpos)[xx] = (double)1;
        }
     
        if(outgroup_presence->value() == 0) {
        
              DNA_matr->ReallocMemory(n_site->value()*(nsamuser_eff->value()+!outgroup_presence->value()), 0);
                      
//            if ((DNA_matr/*2*/ = (char *)realloc(DNA_matr/*2*/,(long long)n_site->value()*(n_samp->value()+1)*sizeof(char))) == 0) {
//                ERROR_MSG << "Error: memory not reallocated. get_obsdata.23a"
//                  END_MSG;
////                for(x=0;x<n_samp;x++) free(names[x]); free(names);
////                free(DNA_matr);
//                names->DeleteMemory();
//                DNA_matr->DeleteMemory();
//                
//                /*free(DNA_matr2);*/
//                free(matrix_sizepos);
//                free(matrix_segrpos);
//                return 0;
//            }
            /*we forced the invented outgroup without gaps or uncertainties, if possible*/
            strncpy((*DNA_matr)+(unsigned long)n_site->value()*(unsigned long)(nsamuser_eff->value()),
                    (*DNA_matr)+(unsigned long)n_site->value()*(unsigned long)(nsamuser_eff->value()-1),
                    n_site->value());
            nsamuser_eff->add(1);
        }
           
        if((*wP).GetData() != 0) {
            /*define the weights*/
            for(long int n_sit=0;n_sit<n_site->value();n_sit++) {
                (*matrix_sizepos)[n_sit] = (*wP)[beg->value()+n_sit-1];
                (*matrix_segrpos)[n_sit] = (*wPV)[beg->value()+n_sit-1]/* * wV[nsit-1]*/;
            }
        }

        
        /*define variables for mhits*/
        mhitbp->ReserveMemory(n_site->value(), 0);
//        *nmhits = 0;
//        if((mhitbp = (long int *) calloc (n_site, sizeof(long int))) == 0) {
//            ERROR_MSG << "Error: memory not reallocated. get_obsstat.6"
//              END_MSG;
//            return 0;
//        }
          
        /*function to analyze all data*/
//        if(get_obsstats(file_output,'\0',n_samp,n_site,length_al_real,names/*2*/,DNA_matr/*2*/,matrix_sizepos,matrix_segrpos,
//                        matrix_pol,matrix_freq,matrix_pos,length_al,length_seg,nsamuser,npops,svratio,missratio,include_unknown,
//                        sum_sam,tcga,matrix_sv,nmhits,output,ploidy,outgroup_presence,nsites1_pop,nsites1_pop_outg,
//                        nsites2_pop,nsites2_pop_outg,nsites3_pop,nsites3_pop_outg,anx,bnx,anxo,bnxo,lengthamng,mhitbp,matrix_pol_tcga) == 0) {
//            for(x=0;x<n_sam;x++) free(names[x]); free(names);
//            free(DNA_matr);
//            /*free(DNA_matr2);*/
//            free(matrix_sizepos);
//            free(matrix_segrpos);
//            free(mhitbp);
//            return 0;
//        }
//		/*free(names2);
//		free(DNA_matr2);*/
//		free(matrix_sizepos);
//		free(matrix_segrpos);
//    free(mhitbp);
    }
    
    return(1);
}

void CCalcOpenTFastaFile::Finalize(void) {
  if (file_input_ != NULL) {
    fzclose(file_input_, &input_gz_);
    file_input_ = NULL;
  }
  
  DM_DEL_ALL_LOCAL_DATA
}

int CCalcOpenTFastaFile::function_read_tfasta(long int init_site,
                                              long int end_site,
                                              int *n_sam)
{
    char c[1];
    char *cc;
    char line[32767*2];
    int col=0;
    static int nseq=0;
    int x;
    static int maxsam=128;
    static long int position=0;
    long int end_position=end_site;
    long int dd,ee,count,xx;
    char *DNA_matr2;
    
    c[0] = '\t';  //!added
    
    if ((DNA_matr2 = (char *)calloc(10000,sizeof(char))) == 0) {
        ERROR_MSG << "Error: memory not reallocated. get_tfadata.23d"
                  END_MSG;
        free(DNA_matr2);
        return(0);
    }

    if(position == 0) {/*to allow sliding windows non-overlapped*/
        /*if names and number of samples are defined then skip the definition of names*/
        *c = fzgetc(file_input_, &input_gz_);
        if((*c==10 || *c==13 || *c == -1 || *c == 0 || *c=='\xff' || *c=='\xfe'))
            return -1;
        line[col] = *c;
        col++;
        
        while(*c=='#') {
            /*parse comments*/
            while(*c != 0 && *c!=-1 && *c!=10 && *c!=13 && *c!='\xff' && *c!='\xfe') {
                *c = fzgetc(file_input_, &input_gz_);
                line[col] = *c;
                col++;
            }
            line[col] = '\0';
            if((cc=strstr(line, "#NAMES:")) != 0) {
                /*collect names*/
                nseq = 0;
                cc = strtok (line,">\n\r ");
                while (cc != NULL)
                {
                    if(strstr(cc,"#NAMES:") == 0) {
                        //!20160504
                        //strcpy((*names)[nseq],cc);
                        //!20160504
                        (*names)[nseq].set_text_string(std::string(cc));
                        
                        nseq++;
                        if(nseq == maxsam) {
                            maxsam += 128;
                            if(maxsam > 32767) {
                                ERROR_MSG << "Sorry, no more than 32767 samples are allowed."
                                          END_MSG;
                                return 0;
                            }
                            names->ReallocMemory(maxsam, 50, '\x0');
//                            if ((*names = (char **)realloc(*names,maxsam*sizeof(char *))) == 0) {
//                                ERROR_MSG << "Error: memory not reallocated. assigna.1"
//                                          END_MSG;
//                                return(0);
//                            }
//                            for(x=nseq;x<maxsam;x++) {
//                                if (((*names)[x] = (char *)calloc(50,sizeof(char))) == 0) {
//                                  ERROR_MSG << "Error: memory not reallocated. assigna.2"
//                                            END_MSG;
//                                  return(0);
//                                }
//                            }
                        }
                    }
                    cc = strtok(NULL, ">\n\r ");
                }
                *n_sam = nseq;
            }
            col=0;
            *c = fzgetc(file_input_, &input_gz_);
            line[col] = *c;
            col++;
        }
        
        /*include in DNAmatrix the positions from the init_site to the end_site (if defined)*/
        col = 0;
        while(*c != 0 && *c!=-1 && *c!=10 && *c!=13 && *c != 9 && *c != 32 && *c!='\xff' && *c!='\xfe') {
            line[col] = *c;
            col++;
            *c = fzgetc(file_input_, &input_gz_);
        }
        if(*c == 0 || *c==-1 || *c=='\xff' || *c=='\xfe') return(-1);
        
        line[col] = '\0';
        position = atol(line);
    }
    if(end_site == -1) end_position = init_site + 1;
    while(position < init_site) {
        while(!(*c==10 || *c==13 || *c == -1 || *c == 0 || *c=='\xff' || *c=='\xfe')) *c = fzgetc(file_input_, &input_gz_);
        if(*c == 0 || *c==-1 || *c=='\xff' || *c=='\xfe') return(-1);
        if(*c==10 || *c==13) {
            while(*c==10 || *c==13) *c = fzgetc(file_input_, &input_gz_);
            col = 0;
            while(*c != 0 && *c!=-1 && *c!=10 && *c!=13 && *c != 9 && *c != 32 && *c!='\xff' && *c!='\xfe') {
                line[col] = *c;
                col++;
                *c = fzgetc(file_input_, &input_gz_);
            }
            line[col] = '\0';
            position = atol(line);
            if(end_site == -1) end_position = position + 1;
        }
    }
    if(!(*c == 0 || *c==-1 || *c=='\xff' || *c=='\xfe'))
        *c = fzgetc(file_input_, &input_gz_);

    n_site->set_value(0);
    col = 0;
    count=0;
    while (position <= end_position) {
        switch(*c) {
            case 'T':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '1';
                col += 1;
                count += 1;
                break;
            case 't':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '1';
                col += 1;
                count += 1;
                break;
            case 'U':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '1';
                col += 1;
                count += 1;
                break;
            case 'u':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '1';
                col += 1;
                count += 1;
                break;
            case 'C':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '2';
                col += 1;
                count += 1;
                break;
            case 'c':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '2';
                col += 1;
                count += 1;
                break;
            case 'G':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '3';
                col += 1;
                count += 1;
                break;
            case 'g':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '3';
                col += 1;
                count += 1;
                break;
            case 'A':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '4';
                col += 1;
                count += 1;
                break;
            case 'a':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '4';
                col += 1;
                count += 1;
                break;
            case 0:
                break;
            case -1:
                break;
            case 10:
                break;
            case 13:
                break;
            case 32:
                break;
            case 9:
                break;
            case 'N':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'n':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case '?':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case '-':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '6';
                col += 1;
                count += 1;
                break;
                /*gaps are converted to N*/
            case 'W':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = 'w';
                col += 1;
                count += 1;
                break;
            case 'w':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = 'w';
                col += 1;
                count += 1;
                break;
            case 'M':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = 'm';
                col += 1;
                count += 1;
                break;
            case 'm':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = 'm';
                col += 1;
                count += 1;
                break;
            case 'R':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = 'r';
                col += 1;
                count += 1;
                break;
            case 'r':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = 'r';
                col += 1;
                count += 1;
                break;
            case 'Y':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = 'y';
                col += 1;
                count += 1;
                break;
            case 'y':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = 'y';
                col += 1;
                count += 1;
                break;
            case 'K':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = 'k';
                col += 1;
                count += 1;
                break;
            case 'k':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = 'k';
                col += 1;
                count += 1;
                break;
            case 'S':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = 's';
                col += 1;
                count += 1;
                break;
            case 's':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = 's';
                col += 1;
                count += 1;
                break;
            case 'b':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'B':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'd':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'D':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'h':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'H':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'v':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'V':
                DNA_matr2[(((long long)nseq*n_site->value())+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            default:
                ERROR_MSG << "Unexpected value in tfa file: position "
                          << position
                          << ", sample "
                          << col
                          << *c
                          END_MSG;
                return(0);
                break;
        }
        if(*c == -1 || *c == 0) break;
        *c = fzgetc(file_input_, &input_gz_);
        if(*c==10 || *c==13 || *c == -1 || *c == 0) {
            while(*c==10 || *c==13) *c = fzgetc(file_input_, &input_gz_);
            if(col != nseq) {
                ERROR_MSG << "Error: The number of columns are not coincident in all positions: "
                          << position
                          END_MSG;
            }
            *n_sam = col;
            col = 0;
            while(*c != 0 && *c!=-1 && *c!=10 && *c!=13 && *c != 9 && *c != 32) {
                line[col] = *c;
                col++;
                *c = fzgetc(file_input_, &input_gz_);
            }
            line[col] = '\0';
            col = 0;
            position = atol(line);
            n_site->set_value(n_site->value() + 1);
            if(end_site == -1) end_position = position + 1;
        }
        /*realloc DNAmatr if nnecessary*/
        dd = (long int)floor((double)count/(double)10000);
        ee = (double)count/(double)10000;
        if(dd == ee) {
            if((DNA_matr2 = (char *)realloc(DNA_matr2,((long int)dd+(long int)1)*(long int)10000*sizeof(char))) == 0) {
                ERROR_MSG << "Error: realloc error varchar.1"
                          END_MSG;
                return(0);
            }
        }
    }
    /*return n_site,n_sam,DNA matrix and names in pointers*/

    // If I do this:
    //   DNA_matr->ReallocMemory(n_site->value()*(long long)(*n_sam), '\x0');
    // I get this:
    //   It is supposed that new dimensions should be bigger than current ones not smaller...
    // So I am going to delete the data and to create it:
    DNA_matr->DeleteMemory();
    DNA_matr->ReserveMemory(n_site->value()*(long long)(*n_sam), STR(DEFAULT_CHAR)[0]);
    
//    if ((*DNA_matr = (char *)realloc(*DNA_matr,n_site->value()*(long long)n_sam[0]*sizeof(char))) == 0) {
//        ERROR_MSG << "Error: memory not reallocated. get_tfadata.23d"
//                  END_MSG;
//        free(DNA_matr2);
//        return(0);
//    }
    for(x=0;x<(*n_sam);x++) {
        for(xx=0;xx<n_site->value();xx++) { /*transpose */
            (*DNA_matr)[(((long long)n_site->value()*(unsigned long)x)+(unsigned long)xx)] =
            DNA_matr2 [(((long long)(*n_sam)*(unsigned long)xx)+(unsigned long)x)];
        }
    }
    free(DNA_matr2);
    
    return(1);
}
