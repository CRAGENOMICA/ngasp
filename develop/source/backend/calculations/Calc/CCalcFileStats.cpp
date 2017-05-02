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
 *  \brief     CCalcFileStats.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 7, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcFileStats.h"

#include "../../data_manager/common/CDataAccess.h"
#include "../../util/CStringTools.h"

#include <iostream>
#include <cmath>
#include <cstdlib>

CCalcFileStats::CCalcFileStats()
: ICalculation(KeyString::CALC_FILE_STATS,
               KeyString::CALC_FILE_STATS_BRIEF_DESC,
               KeyString::CALC_FILE_STATS_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
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
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(include_unknown,                                             // Variable
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
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(vint_perpop_nsam,   /*nsamuser*/                             // Variable
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
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(names,                                                       // Variable
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
    SET_INPUT_INFO(n_site,                                                      // Variable
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
    SET_INPUT_INFO(DNA_matr,                                                    // Variable
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
    SET_INPUT_INFO(matrix_segrpos,                                              // Variable
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
    SET_INPUT_INFO(file_mas,                                                    // Variable
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
    SET_INPUT_INFO(output,                                                      // Variable
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
    SET_INPUT_INFO(formatfile,                                                  // Variable
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
  
    SET_OUTPUT_INFO(matrix_pol,                                                 // Variable
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
    SET_OUTPUT_INFO(matrix_pol_tcga,                                            // Variable
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
    SET_OUTPUT_INFO(lengthamng,                                                 // Variable
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
    SET_OUTPUT_INFO(tcga,                                                       // Variable
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
    SET_OUTPUT_INFO(anx,                                                        // Variable
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
    SET_OUTPUT_INFO(bnx,                                                        // Variable
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
    SET_OUTPUT_INFO(anxo,                                                       // Variable
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
    SET_OUTPUT_INFO(bnxo,                                                       // Variable
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
    SET_OUTPUT_INFO(length_al,                                                  // Variable
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
    SET_OUTPUT_INFO(length_seg,                                                 // Variable
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
    SET_OUTPUT_INFO(missratio,                                                  // Variable
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
    SET_OUTPUT_INFO(nsites1_pop,                                                // Variable
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
    SET_OUTPUT_INFO(nsites1_pop_outg,                                           // Variable
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
    SET_OUTPUT_INFO(nsites2_pop,                                                // Variable
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
    SET_OUTPUT_INFO(nsites2_pop_outg,                                           // Variable
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
    SET_OUTPUT_INFO(nsites3_pop,                                                // Variable
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
    SET_OUTPUT_INFO(nsites3_pop_outg,                                           // Variable
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
    SET_OUTPUT_INFO(sum_sam,                                                    // Variable
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
    SET_OUTPUT_INFO(svratio,                                                    // Variable
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
    SET_OUTPUT_INFO(matrix_freq,                                                // Variable
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
    SET_OUTPUT_INFO(matrix_pos,                                                 // Variable
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
    SET_OUTPUT_INFO(matrix_sv,                                                  // Variable
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
    SET_OUTPUT_INFO(n_realsite,                                                 // Variable
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
    SET_OUTPUT_INFO(nmhits,                                                     // Variable
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
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcFileStats::~CCalcFileStats() {
}

void CCalcFileStats::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(ploidy)
    DM_INPUT(include_unknown)
    DM_INPUT(outgroup_presence)
    DM_INPUT(vint_perpop_nsam)
    DM_INPUT(npops)
    DM_INPUT(names)
    DM_INPUT(n_site)
    DM_INPUT(DNA_matr)
    DM_INPUT(matrix_segrpos)
    DM_INPUT(file_in)
    DM_INPUT(file_mas)
    DM_INPUT(output)
    DM_INPUT(formatfile)
  DM_GET_OUTPUTS
    DM_OUTPUT(matrix_pol)
    DM_OUTPUT(matrix_pol_tcga)
    DM_OUTPUT(lengthamng)
    DM_OUTPUT(tcga)
    DM_OUTPUT(anx)
    DM_OUTPUT(bnx)
    DM_OUTPUT(anxo)
    DM_OUTPUT(bnxo)
    DM_OUTPUT(length_al)
    DM_OUTPUT(length_seg)  //<<<
    DM_OUTPUT(missratio)
    DM_OUTPUT(nsites1_pop)
    DM_OUTPUT(nsites1_pop_outg)
    DM_OUTPUT(nsites2_pop)
    DM_OUTPUT(nsites2_pop_outg)
    DM_OUTPUT(nsites3_pop)
    DM_OUTPUT(nsites3_pop_outg)
    DM_OUTPUT(sum_sam)
    DM_OUTPUT(svratio)
    DM_OUTPUT(matrix_freq)
    DM_OUTPUT(matrix_pos)
    DM_OUTPUT(matrix_sv)
    DM_OUTPUT(mhitbp) //<<<<
    DM_OUTPUT(n_realsite)
    DM_OUTPUT(nmhits)
    DM_OUTPUT(matrix_sizepos)  //<<<
    DM_OUTPUT(n_samp)   // It was n_samp
  DM_END
}
    
void CCalcFileStats::Calculate(bool dry_run) {


  FILE *file_output = manager()->foutput();
  FILE *file_mask = NULL;
      
  if ((file_mas->value() != "") && (file_mas->value() != "-1")) {
    if (file_in->value() == "") {
      if((file_mask = fopen("mask_file_exits.txt","w")) == 0) {
        ERROR_MSG << "Error in mask file mask_file_exits.txt"
                  END_MSG;
        return;
      }
    }
    else
    {
      if((file_mask = fopen(file_mas->value().c_str(),"w")) == 0) {
        ERROR_MSG << "Error in mask file "
                  << file_mas->value()
                  END_MSG;
        return;
      }
    }
  }
  
 
  
	/*int *unic = 0;*/
	/*long int mhits = 0;*/
    /*long int *mhitbp = 0;*/
    long int maxnsite = 128;
    long int maxbialsites = 256;
    long int maxnsamp = 32;
    int *nnsam = 0;
    // int nnnsam;  //!removed because it is not used
	long int *unic;
	
	long int transitions;
	long int transversions;
	
    double algsites;
    long int bial_sites = 0;
 
    int m_0,k_0,m_1,k_1;
    int v,w,x,y,z,mis,p,q,k,v2,y2,z2,xm;
	int a,aloutg,al1,al2,fal1,fal2,fal[5];
	
	long int xx;
  
  //!added ++++++++++++++++++++++++++++
  int nPloidy = ploidy->value();
  //+++++++++++++++++++++++++++++++++++

    /*int v0,v1,y0,y1,b,c;*/
    /*char *strin;*/
	int d;
    double _sites;
	
	long int *mvbp;
	long int mv = 0;
 	int nsamtot;
	long int totalmis=0;
	long int mis2,miso;
    /*int alleles,fao[5];*/
    int al3,fal3,al4,fal4;
	
	nsamtot = 0;
	for(x=0;x<npops->value();x++)
		nsamtot += (*vint_perpop_nsam)[x];

	/* Two pointers indicating the samples that are current samples and the outgroup samples */
	if((nnsam = (int *) calloc(maxnsamp,sizeof(int))) == 0) {
		fprintf(file_output,"Error: memory not reallocated. get_obsstats.1"); 
		return;
	}
	/* matrix of polymorphisms: only 0 and 1 */
      //!20160504 All IDataVector::ReserveMemory(a, a*b, STR) have been replaced by IDataVector::ReserveMemory(a*b, STR)
      matrix_pol->ReserveMemory(maxnsamp * maxbialsites, STR(DEFAULT_CHAR)[0]);
//    if((*matrix_pol = (char *) calloc (maxnsamp*maxbialsites, sizeof(char))) == 0) {
//        fprintf(file_output,"Error: memory not reallocated. get_obsstat.3");
//        return;
//    }
      //!20160504
      matrix_pol_tcga->ReserveMemory(maxnsamp * maxbialsites, STR(DEFAULT_CHAR)[0]);
//    if((*matrix_pol_tcga = (char *) calloc (maxnsamp*maxbialsites, sizeof(char))) == 0) {
//        fprintf(file_output,"Error: memory not reallocated. get_obsstat.3");
//        return;
//    }
	/* indicates the position and the frequency */
    matrix_pos->ReserveMemory(maxbialsites, 0);
//	if((*matrix_pos = (long int *) calloc (maxbialsites, sizeof(long int))) == 0) {
//		fprintf(file_output,"Error: memory not reallocated. get_obsstat.4"); 
//		return;
//	}
    matrix_freq->ReserveMemory(maxbialsites, 0);
//	if((*matrix_freq = (long int *) calloc (maxbialsites, sizeof(long int))) == 0) {
//		fprintf(file_output,"Error: memory not reallocated. get_obsstat.5"); 
//		return;
//	}
    matrix_sv->ReserveMemory(maxbialsites, 0);
//	if((*matrix_sv = (long int *) calloc (maxbialsites, sizeof(long int))) == 0) {
//		fprintf(file_output,"Error: memory not reallocated. get_obsstat.7"); 
//		return;
//	}
	if((unic = (long int *) calloc (maxnsamp, sizeof(long int))) == 0) {
		fprintf(file_output,"Error: memory not reallocated. get_obsstat.6"); 
		return;
	}
	/* indicates the position of the mhits */
	/*
	if((mhitbp = (long int *) calloc (maxnsite, sizeof(long int))) == 0) {
		fprintf(file_output,"Error: memory not reallocated. get_obsstat.6"); 
		return;
	}
	*/
	if((mvbp = (long int *) calloc (maxnsite, sizeof(long int))) == 0) {
		fprintf(file_output,"Error: memory not reallocated. get_obsstat.13"); 
		return;
	}
 
	if(n_samp->value() > maxnsamp) {
        /* Reallocation in case the value be larger than specified */
          //!20160504
          matrix_pol->ReallocMemory(n_samp->value() * maxbialsites, STR(DEFAULT_CHAR)[0]);
//        if((*matrix_pol = (char *) realloc (*matrix_pol,(n_samp*maxbialsites)*sizeof(char))) == 0) {
//            fprintf(file_output,"Error: memory not reallocated. get_obsstat.7b");
//            return;
//        }
          //!20160504
          matrix_pol_tcga->ReallocMemory(n_samp->value() * maxbialsites, STR(DEFAULT_CHAR)[0]);
//        if((*matrix_pol_tcga = (char *) realloc (*matrix_pol_tcga,(n_samp*maxbialsites)*sizeof(char))) == 0) {
//            fprintf(file_output,"Error: memory not reallocated. get_obsstat.7b");
//            return;
//        }
        if((nnsam = (int *) realloc(nnsam,n_samp->value()*sizeof(int))) == 0) {
            fprintf(file_output,"Error: memory not reallocated. get_obsstats.9"); 
            return;
        }
        if((unic = (long int *) realloc(unic,n_samp->value()*sizeof(long int))) == 0) {
            fprintf(file_output,"Error: memory not reallocated. get_obsstats.11"); 
            return;
        }
        maxnsamp = n_samp->value();
    }
    if(n_site->value() > maxnsite) {
		/*
        if((mhitbp = (long int *) realloc (mhitbp,n_site*sizeof(long int))) == 0) {
            fprintf(file_output,"Error: memory not reallocated. get_obsstat.8"); 
            return;
        }
		*/
        if((mvbp = (long int *) realloc (mvbp,n_site->value()*sizeof(long int))) == 0) {
            fprintf(file_output,"Error: memory not reallocated. get_obsstat.12"); 
            return;
        }
        maxnsite = n_site->value();
    }

    algsites = (double)n_site->value(); /* number of aligned positions, excluding gaps and mhits */
    //nnnsam = 0;
    
    /* calculate number of samples in outgroup and in the current sample */
	/* if no outgroup, then all sequences are samples */
	if(n_samp->value() < 2) {
		printf(" n_samples: %d .",n_samp->value());
		printf(" NOT ENOUGH SAMPLES.");
		if(file_output) {
			fprintf(file_output," n_samples: %d .",n_samp->value());
			fprintf(file_output," NOT ENOUGH SAMPLES.");
		}
		return;
	}
	for(x=0;x<n_samp->value();x++) nnsam[x] = x;
	//nnnsam = n_samp->value();

    /*init unics*/
    for(y=0;y<n_samp->value();y++) {
        unic[y] = 0;
    }
    /* find positions that are biallelic, excluding the rest. */
    /* IMPORTANT: multiple hits are eliminated from analysis */
    _sites = (double)0;
    transitions = 0;
	transversions = 0;
	n_realsite->set_value((long int)0);
	mis2 = 0;
	
	for(xx=0;xx<n_site->value();xx++) {
		/*eliminate those positions that are not included in analysis*/
		if((*matrix_sizepos)[xx] == (double)0) {
			algsites -= (double)1;
			continue;
		}
		/*matrix making biallelic (and missing) variants*/
        n_realsite->add((long int)1);
      

        k_0 = m_1 = k_1 = y = z = v = mis = miso = 0;
        
        m_0 = *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)0)+(unsigned long)xx));
        do {
            w = *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx));
            if(w > 48 + 4) { /* the position y (also y == 0) is not a, g, t or c */
                mis += 1;
                if(y>=n_samp->value()-(*vint_perpop_nsam)[npops->value()-1]) miso += 1;
                                if(include_unknown->value() == 1) {/*==*/
                                  if(m_0 > (48 + 4)) {/*==*/
                                    if(y+1 < nsamtot) {
                                      m_0 = *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)(y+1))+(unsigned long)xx));
                                    }
                                  }
                                }
                                else {
                                  z = 1;
                                  v = 0;
                                  algsites -= (*matrix_sizepos)[xx];
                                }
            }
            else { /* the position y is a, g, t or c */
                (*tcga)[y][w-49] += 1.; /*count for tcga and transition and transversions*/
				if(w != m_0 && w != k_0) { /* if position 0 and y are different, and also different of the k_0 */
					if(k_0 == 0) { /* if k_0 is 0 (initialized), the k_0 will be w */
                        k_0 = w;
                        k_1++; /* counting the numbers of w different from m_0 and not > 4 and not mhits */
                    }
                    else { /* if k_0 has already a value */
                        if((w <= 48 + 4) && (m_0 <= 48 + 4))  
                            v = 1; /* if w and m_0 are different and are also different from k_0 = mhit */
                    }
                }
                else { /* in case w=m_0 or w=k_0 */
                    if(w == m_0) m_1++; /* if w equal to m_0 count m_1 */
                    else k_1++; /* if w is different from m_0 */
                }
            }
            y++;
        } while(z==0 && y < nsamtot/*n_samp*/);        
		/* mhit position */
        if(v == 1) {
            (*mhitbp)[nmhits->value()] = xx+1;
            nmhits->add(1);
            /*keeping mhits by taking all variants as new biallelic independent sites */
            /*(add missing where were other variants) (in case include_unknown->value() == 1)*/
            if(include_unknown->value() == 1) {
				aloutg = -1;
				fal[0]=fal[1]=fal[2]=fal[3]=fal[4]=0;
				/*look at the outgroup: keep the ancestral, if more than one allele reject position, if only N also reject*/
				if(outgroup_presence->value()) {
					for(y=nsamtot-(*vint_perpop_nsam)[npops->value()-1];y<nsamtot;y++) {
						a = (int)*((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx));
						switch(a) {
							case 48+1:
								fal[0]+= 1;
								aloutg = 0;
								break;
							case 48+2:
								fal[1]+= 1;
								aloutg = 1;
								break;
							case 48+3:
								fal[2]+= 1;
								aloutg = 2;
								break;
							case 48+4:
								fal[3]+= 1;
								aloutg = 3;
								break;
							case 48+5: /*Ns*/
								fal[4]+= 1;
								break;
							case 48+6: /*gaps=Ns*/
								fal[4]+= 1;
								break;
						}
					}
				}
				if(outgroup_presence->value()==1 && (aloutg == -1 || fal[aloutg]+fal[4] < (*vint_perpop_nsam)[npops->value()-1])) {
					/*reject*/
					algsites -= (*matrix_sizepos)[xx];
          n_realsite->set_value(n_realsite->value() - (long int)1);
                    /*add Ns at the ouygroup*/
                    for(y=nsamtot-(*vint_perpop_nsam)[npops->value()-1];y<nsamtot;y++)
                        *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx)) = 48+5;
					z = 1;
				}
				else {
					/*look at the rest of samples: transform all variants in new biallelic positions*/
                    /*keep only the two more frequent alleles, the rest convert to Ns*/
					fal[0]=fal[1]=fal[2]=fal[3]=fal[4]=0;
					for(y=0;y<nsamtot-(*vint_perpop_nsam)[npops->value()-1];y++) {
						a = (int)*((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx));
						switch(a) {
							case 48+1:
								fal[0]+= 1;
								break;
							case 48+2:
								fal[1]+= 1;
								break;
							case 48+3:
								fal[2]+= 1;
								break;
							case 48+4:
								fal[3]+= 1;
								break;
							case 48+5: /*Ns*/
								fal[4]+= 1;
								break;
							case 48+6: /*gaps=Ns*/
								fal[4]+= 1;
								break;
						}
					}
 					/*sort the two best (or coincident with the outgroup)*/
					al1=al2=al3=al4=-1;
					fal1=fal2=fal3=fal4=0;
					if(aloutg == -1) {
                        al1 = 0;
						fal1=fal[0];
                        for(y=1;y<4;y++) {
                            if(fal[y] > fal1) {
                                al1 = y;
                                fal1 = fal[y];
                            }
                        }
					}
					else {
						al1 = aloutg;
						fal1= fal[aloutg];
					}
                    for(y=0;y<4;y++) {
                        if(y != al1) {
                            if(fal[y] > fal2) {
                                al2 = y;
                                fal2 = fal[y];
                            }
                        }
                    }
                    for(y=0;y<4;y++) {
                        if(y != al1 && y != al2) {
                            if(fal[y] > fal3) {
                                al3 = y;
                                fal3 = fal[y];
                            }
                        }
                    }
                    for(y=0;y<4;y++) {
                        if(y != al1 && y != al2 && y != al3) {
                            if(fal[y] > fal4) {
                                al4 = y;
                                fal4 = fal[y];
                            }
                        }
                    }
                    _sites += (*matrix_sizepos)[xx];
                    algsites -= (double)1 - (*matrix_sizepos)[xx];
                    for(y=0;y<nsamtot;y++) {
                        if(*((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx)) != 48+5 &&
                           *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx)) != 48+6) /*6 added*/
                            (*sum_sam)[y] += (double)(*matrix_sizepos)[xx];
                    }
                    /*Loop adding the number of bialsites (2 or 3) at this position*/
                    for(y=0;y<(int)(fal2>0)+(int)(fal3>0)+(int)(fal4>0);y++) {
                        if((*matrix_segrpos)[xx]/*to eliminate biallelic syn/nsyn not desired*/) {
                            k_0 = al1+48+1;
                            if(y==0) m_0 = al2+48+1;
                            if(y==1) m_0 = al3+48+1;
                            if(y==2) m_0 = al4+48+1;
                            if((k_0 == '1' && m_0 == '2') || (k_0 == '2' && m_0 == '1') ||
                               (k_0 == '4' && m_0 == '3') || (k_0 == '3' && m_0 == '4')) {
                                transitions += 1;
                                (*matrix_sv)[bial_sites] = 1;
                            }
                            else {
                                transversions += 1;
                                (*matrix_sv)[bial_sites] = 2;
                            }
                            d = 0;
                            for(y2=0;y2<nsamtot/*n_samp*/;y2++) { /* non-outgroup: 0 indicates higher frequency */
                                if(*((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y2)+(unsigned long)xx)) == k_0) {
                                    (*matrix_pol)[((bial_sites*(nsamtot/*n_samp*/))+y2)] = '0';
                                    (*matrix_pol_tcga)[((bial_sites*(nsamtot/*n_samp*/))+y2)] = k_0;
                                }
                                else {
                                    if(*((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y2)+(unsigned long)xx)) == m_0) {
                                        (*matrix_pol)[((bial_sites*(nsamtot/*n_samp*/))+y2)] = '1';
                                        (*matrix_pol_tcga)[((bial_sites*(nsamtot/*n_samp*/))+y2)] = m_0;
                                        d += 1;
                                    }
                                    else {
                                        (*matrix_pol)[((bial_sites*(nsamtot/*n_samp*/))+y2)] = '-';
                                        (*matrix_pol_tcga)[((bial_sites*(nsamtot/*n_samp*/))+y2)] = '-';
                                    }
                                }
                            }
                            
                            (*matrix_pos)[bial_sites] = -(long int)(xx+(long int)1);
                            /*positions with missing have a negative position (to exclude in haplotype calculations)*/
                            mvbp[mv] = xx+1;
                            mv++;
                            
                            if(mv >= maxnsite) {
                                if((mvbp = (long int *) realloc (mvbp,(mv+128)*sizeof(long int))) == 0) {
                                    fprintf(file_output,"Error: memory not reallocated. get_obsstat.12"); 
                                    return; // (0);
                                }
                                maxnsite = mv;
                            }
                            
                            (*matrix_freq)[bial_sites] = d;
                            /*calculate unique variants*/
                            for(y2=0;y2<nsamtot/*n_samp*/;y2++) {
                                if((d==1 && (*matrix_pol)[((bial_sites*(nsamtot/*n_samp*/))+y2)] == '1') ||
                                   (d==nsamtot/*n_samp*/-1 && (*matrix_pol)[((bial_sites*(nsamtot/*n_samp*/))+y2)] == '0'))
                                    unic[y2] += 1;
                            }
                            /* one more position */
                            bial_sites++;
                            /* reallocations */
                            if(bial_sites == maxbialsites) {
                                maxbialsites += 128;
                                //!20160504
                                  matrix_pol->ReallocMemory( maxnsamp * maxbialsites, STR(DEFAULT_CHAR)[0]);
//                                if((*matrix_pol = realloc(*matrix_pol,(maxnsamp)*(maxbialsites)*sizeof(char))) == 0) {
//                                    fprintf(file_output,"Error: memory not reallocated. get_obsstat.11");
//                                    return;
//                                }
                                  //!20160504
                                  matrix_pol_tcga->ReallocMemory(maxnsamp * maxbialsites, STR(DEFAULT_CHAR)[0]);
//                                if((*matrix_pol_tcga = realloc(*matrix_pol_tcga,(maxnsamp)*(maxbialsites)*sizeof(char))) == 0) {
//                                    fprintf(file_output,"Error: memory not reallocated. get_obsstat.11");
//                                    return;
//                                }
                                  matrix_pos->ReallocMemory(maxbialsites, 0);
//                                if((*matrix_pos = realloc(*matrix_pos,(maxbialsites)*sizeof(long int))) == 0) {
//                                    fprintf(file_output,"Error: memory not reallocated. get_obsstat.12");
//                                    return;
//                                }
                                  matrix_freq->ReallocMemory(maxbialsites, 0);
//                                if((*matrix_freq = realloc(*matrix_freq,(maxbialsites)*sizeof(long int))) == 0) {
//                                    fprintf(file_output,"Error: memory not reallocated. get_obsstat.13");
//                                    return;
//                                }
                                  matrix_sv->ReallocMemory(maxbialsites, 0);
//                                if((*matrix_sv = realloc(*matrix_sv,(maxbialsites)*sizeof(long int))) == 0) {
//                                    fprintf(file_output,"Error: memory not reallocated. get_obsstat.14");
//                                    return;
//                                }
                            }
                        }
                    }
				}
			} else {
        n_realsite->add(-(long int)1);
				algsites -= (*matrix_sizepos)[xx];
				z = 1;
			}
        }
		
        if(z==0 && v == 0) {
			_sites += (*matrix_sizepos)[xx];
			algsites -= (double)1 - (*matrix_sizepos)[xx];
			for(y=0;y<nsamtot;y++) 
				if(*((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx)) != 48+5 &&
				   *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx)) != 48+6) /*6 added*/
					(*sum_sam)[y] += (double)(*matrix_sizepos)[xx];
		}
        /* do the matrix of biallelic positions: */
        if(v==0 && z==0 && m_1+mis<nsamtot/*n_samp*/ && (*matrix_segrpos)[xx]/*to eliminate biallelic syn/nsyn not desired*/) {
			
			/*count for transitions and transversions*/
			/*
			for(y=0;y<nsamtot;y++) {
				w = *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx));
				(*tcga)[y][w-49] += 1.;
			}
			*/
			if(k_0 != 0 && k_0 != m_0 && v == 0 && z == 0) {
				if((k_0 == '1' && m_0 == '2') || (k_0 == '2' && m_0 == '1') || 
				   (k_0 == '4' && m_0 == '3') || (k_0 == '3' && m_0 == '4')) {
					transitions += 1;
					(*matrix_sv)[bial_sites] = 1;
				}
				else {
					transversions += 1;
					(*matrix_sv)[bial_sites] = 2;
				}
			}			
			
			/* k_0 will be the large frequency */
			if(m_1 > k_1)  {
                k_1 = m_0;
                k_0 = m_0;
                m_0 = k_1;
				k_1 = m_1;
			}
			d = 0;
			for(y=0;y<nsamtot/*n_samp*/;y++) { /* non-outgroup: 0 indicates higher frequency */
                if(*((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx)) == k_0) {
                    (*matrix_pol)[((bial_sites*(nsamtot/*n_samp*/))+y)] = '0';
                    (*matrix_pol_tcga)[((bial_sites*(nsamtot/*n_samp*/))+y)] = k_0;
                }
				else {
					if(*((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx)) == 48+5 ||
                       *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx)) == 48+6) {/*6 addded*/
                        (*matrix_pol)[((bial_sites*(nsamtot/*n_samp*/))+y)] = '-';
                        (*matrix_pol_tcga)[((bial_sites*(nsamtot/*n_samp*/))+y)] = '-';
                    }
					else {
                        (*matrix_pol)[((bial_sites*(nsamtot/*n_samp*/))+y)] = '1';
                        (*matrix_pol_tcga)[((bial_sites*(nsamtot/*n_samp*/))+y)] = m_0;
						d += 1;
					}
				}
			}
			if(mis==0) 
				(*matrix_pos)[bial_sites] = (long int)(xx+(long int)1);
			else {
				(*matrix_pos)[bial_sites] = -(long int)(xx+(long int)1); /*positions with missing have a negative position (to exclude in haplotype calculations)*/
				mvbp[mv] = xx+1;
				mv++;
                if(mv >= maxnsite) {
                    if((mvbp = (long int *) realloc (mvbp,(mv+128)*sizeof(long int))) == 0) {
                        fprintf(file_output,"Error: memory not reallocated. get_obsstat.12");
                        return; // (0);
                    }
                    maxnsite = mv;
                }        
			}
			(*matrix_freq)[bial_sites] = d;
			/*calculate unics*/
			for(y=0;y<nsamtot/*n_samp*/;y++) {
				if((d==1 && (*matrix_pol)[((bial_sites*(nsamtot/*n_samp*/))+y)] == '1') ||
				   (d==nsamtot/*n_samp*/-1 && (*matrix_pol)[((bial_sites*(nsamtot/*n_samp*/))+y)] == '0')) 
					unic[y] += 1;
			}
            /* one more position */
            bial_sites++;
            /* reallocations */
            if(bial_sites == maxbialsites) {
                /*
				if(maxbialsites == 32767) {
                    printf("\n Sorry, it is only accepted a maximum of 32767 biallelic sites per loci. It has been cut at position %ld.",xx+1);
                    if(file_output) fprintf(file_output,"\n Sorry, it is only accepted a maximum of 32767 biallelic sites per loci. It has been cut at position %ld.",xx+1);
                    return;
                }
                else if(maxbialsites > 32767 - 128) maxbialsites = 32767;
                    else */maxbialsites += 128;
                  //!20160504
                  matrix_pol->ReallocMemory(maxnsamp * maxbialsites, STR(DEFAULT_CHAR)[0]);
//                if((*matrix_pol = realloc(*matrix_pol,(maxnsamp)*(maxbialsites)*sizeof(char))) == 0) {
//                    fprintf(file_output,"Error: memory not reallocated. get_obsstat.11");
//                    return;
//                }
                  matrix_pol_tcga->ReallocMemory(maxnsamp * maxbialsites, STR(DEFAULT_CHAR)[0]);
//                if((*matrix_pol_tcga = realloc(*matrix_pol_tcga,(maxnsamp)*(maxbialsites)*sizeof(char))) == 0) {
//                    fprintf(file_output,"Error: memory not reallocated. get_obsstat.11");
//                    return;
//                }
                  matrix_pos->ReallocMemory(maxbialsites, 0);
//                if((*matrix_pos = realloc(*matrix_pos,(maxbialsites)*sizeof(long int))) == 0) {
//                    fprintf(file_output,"Error: memory not reallocated. get_obsstat.12");
//                    return;
//                }
                  matrix_freq->ReallocMemory(maxbialsites, 0);
//                if((*matrix_freq = realloc(*matrix_freq,(maxbialsites)*sizeof(long int))) == 0) {
//                    fprintf(file_output,"Error: memory not reallocated. get_obsstat.13");
//                    return;
//                }
                  matrix_sv->ReallocMemory(maxbialsites, 0);
//                if((*matrix_sv = realloc(*matrix_sv,(maxbialsites)*sizeof(long int))) == 0) {
//                    fprintf(file_output,"Error: memory not reallocated. get_obsstat.14");
//                    return;
//                }
            }
        }
        if(include_unknown->value() == 1) {
          if(mis == nsamtot || miso == (*vint_perpop_nsam)[npops->value()-1]) {
              n_realsite->add(-(long int)1);
              algsites -= (*matrix_sizepos)[xx];
          }
          else {
              totalmis += mis;
              mis2 += (mis - miso);
          }
        }
       
    }        
        
	/*
	if(_sites != algsites) {
		printf("CHECK BUG in get_obsatastats.c");
	}
	*/


	/**nmhits = mhits;*/
    if(file_output) {
		if(output->value() == 0 || output->value() == 10) {
			/*
			fprintf(file_output,"\n\nWARNING: Positions with missing values and multiple hits (including codon positions with more than 2 variants) are filtered using THE COMPLETE FILE included.");
			fprintf(file_output,"\n\nREADING INPUT FILE DATA:\n\n Number of Total Samples (if diploid, doubled): %d\n Valid sites: %.2f\n Multiple hits: %ld\n Polymorphic (biallelic) positions with missing samples: %ld\n Ratio missing/positions: %f\n Ratio trans/transv: %.3f.",nnnsam-!outgroup_presence->value(),_sites,mhits,mv,(double)totalmis/(double)(nnnsam*_sites),(double)transitions/(double)transversions);
			*/
			if(nmhits->value()) {
                fprintf(file_output,"\n Position(s) of the multiple hits ");
                if(include_unknown->value())
                    fprintf(file_output," (minor frequency not outgroup excluded in the analysis):");
                else
                    fprintf(file_output," (excluded from the analysis):");
				for(x=0;x<nmhits->value();x++) {
          if(formatfile->value()>0) fprintf(file_output," %ld",(*mhitbp)[x]+formatfile->value()-1);
          else fprintf(file_output," %ld",(*mhitbp)[x]);
				}
			}
			if(mv) {
				fprintf(file_output,"\n Position(s) of the Variable (converted biallelic if mhits) base with missing samples:");
				for(x=0;x<mv;x++) {
          if(formatfile->value()>0) fprintf(file_output," %ld",mvbp[x] + formatfile->value()-1);
          else fprintf(file_output," %ld",mvbp[x]);          
				}
			}
			fprintf(file_output,"\n\n Names from sample selected by the user (the first %d, if diploid is doubled):",(nsamtot-!outgroup_presence->value())/nPloidy);
			z = 0;
			for(y=0;y<npops->value()-!outgroup_presence->value();y++) {
				if(y < npops->value()-1 || npops->value()==1) fprintf(file_output,"\n\n Population[%d]:\n",y);
				else fprintf(file_output,"\n\n Outgroup: \n");
				for(x=0;x<(*vint_perpop_nsam)[y]/nPloidy;x++) {
					fprintf(file_output,"\n %s",(*names)[z].GetDataString(false));
					z+=nPloidy;
				}
			}
      /*!----------------------------------
      printf(".\n\nCalculating statistics...\n");
      fflush(stdout);
      ------------------------------------*/
      //!++++++++++++++++++++++++++++++++++++
      fprintf(file_output,".\n\nCalculating statistics...\n");
      fflush(file_output);
      //!++++++++++++++++++++++++++++++++++++ 
		}
	}
	else {
		if(output->value() == 0 || output->value() == 10) {
			/*printf(" n_samples: %d, valid sites: %.2f. mhits: %d, transitio/transversion: %.3f.",nnnsam,_sites,nmhits->value(),(double)transition/(double)transversion);*/
			/*
			printf("\n\nWARNING: Positions with missing values and multiple hits (including codon positions with more than 2 variants) are filtered using THE COMPLETE FILE included.");
			printf("\n\nREADING INPUT FILE DATA:\n\n Number of Total Samples (if diploid, doubled): %d\n Valid sites: %.2f\n Multiple hits: %ld\n Polymorphic (biallelic) positions with missing samples: %ld\n Ratio missing/positions: %f\n Ratio trans/transv: %.3f.",nnnsam-!outgroup_presence->value(),_sites,nmhits->value(),mv,(double)totalmis/(double)(nnnsam*_sites),(double)transitions/(double)transversions);
			*/
			if(nmhits->value()) {
                printf("\n Position(s) of the multiple hits ");
                if(include_unknown->value())
                    printf(" (minor frequency not outgroup excluded in the analysis):");
                else
                    printf(" (excluded from the analysis):");
				for(x=0;x<nmhits->value();x++) {
          if(formatfile->value()>0) printf(" %ld",(*mhitbp)[x] + formatfile->value()-1);
          else printf(" %ld",(*mhitbp)[x]);          
				}
			}
			if(mv) {
				printf("\n Position(s) of the Variable (biallelic) base with missing samples:");
				for(x=0;x<mv;x++) {
					printf(" %ld",mvbp[x]);
				}
			}
			printf("\n\n Names from samples selected by the user (the first %d, if diploid is doubled):",(nsamtot-!outgroup_presence->value())/nPloidy);
			z = 0;
			for(y=0;y<npops->value()-!outgroup_presence->value();y++) {
				if(y < npops->value()-1 || npops->value()==1) printf("\n\n Population[%d]:\n",y);
				else printf("\n\n Outgroup: \n");
				for(x=0;x<(*vint_perpop_nsam)[y]/nPloidy;x++) {
					printf("\n %s",(*names)[z].GetDataString(false));
					z++;
				}
			}
			printf("\n");
		}
    }
	if(_sites == (double)0) {
        for(y=0;y<npops->value()-!outgroup_presence->value();y++) {
            (*nsites1_pop)[y] = 0.;
            (*nsites1_pop_outg)[y] = 0.;
            (*nsites2_pop)[y] = 0.;
            (*nsites2_pop_outg)[y] = 0.;
            (*nsites3_pop)[y] = 0.;
            (*nsites3_pop_outg)[y] = 0.;
            (*anx)[y]  = (*bnx)[y]  = 0.0;
            (*anxo)[y] = (*bnxo)[y] = 0.0;
        }
        /*    
        if(file_output) 
			fprintf(file_output,"Not valid sites available in this file: ");
		else
			printf("Not valid sites available in this file:  ");
        return 0;*/
    }
	else { /*print mask, in case considering missing values, in a new file named ..._mask.txt*/
		if(/*include_unknown->value() && */file_mask){
            xm=0;
			for(xx=0;xx<n_site->value();xx++) {
				/*
				w = (char)0;
				for(y=0;y<nsamtot;y++) {
					w = *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx));
					if(w > (48+5)) {
						(*matrix_sizepos)[xx] = (double)0;
						fprintf(file_mask,"%.3f ",(*matrix_sizepos)[xx]);
						break;
					}
				}
				if(w <= (48+5)) */
                while((*mhitbp)[xm]<xx+1 && xm<nmhits->value()) {
                    xm++;
                }
                if(include_unknown->value() == 0 && (*mhitbp)[xm]==xx+1)
                    fprintf(file_mask,"%.3f ",(float)0);
                else
                    fprintf(file_mask,"%.3f ",(*matrix_sizepos)[xx]); /*print the value of each position*/
			}
			fprintf(file_mask,"\n");
			for(x=0;x<nsamtot;x++) {
				for(xx=0;xx<n_site->value();xx++) {
				/*if((*matrix_sizepos)[xx] > (double)0) {
						for(y=0;y<nsamtot;y++) {
							w = *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)y)+(unsigned long)xx));
							if(w > (48+5))
								break;
						}
				 		if(y == nsamtot) {
				*/
							w = *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)x)+(unsigned long)xx));
							if(w >= 48+5) fprintf(file_mask,"0");/*missing*/
							else fprintf(file_mask,"1");/*normal*/
				/*		}
				}*/
				}
				fprintf(file_mask,"\n");
			}
		}
		if(include_unknown->value()) {
			/*calculate nsites1_pop, nsites2_pop and nsites1_pop_outg, nsites2_pop_outg*/
			for(y=0;y<npops->value()-!outgroup_presence->value();y++) {
				(*nsites1_pop)[y] = 0.;
				(*nsites1_pop_outg)[y] = 0.;
				(*nsites2_pop)[y] = 0.;
				(*nsites2_pop_outg)[y] = 0.;
				(*nsites3_pop)[y] = 0.;
				(*nsites3_pop_outg)[y] = 0.;
			}
			z = 0;
			for(y=0;y<npops->value()-!outgroup_presence->value();y++) {
				(*anx)[y]  = (*bnx)[y]  = 0.0;
				(*anxo)[y] = (*bnxo)[y] = 0.0;
				xm = 0;
				for(xx=0;xx<n_site->value();xx++) {
					v = 0;
					for(x=z;x<z+(*vint_perpop_nsam)[y];x++) {
						w = *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)x)+(unsigned long)xx));	
						if(w == 48+5) v += 1;
					}
					while((*mhitbp)[xm]<xx+1 && xm<nmhits->value()) {
                        xm++;
                    }
					if(((*matrix_sizepos)[xx] > 0/* && (*mhitbp)[xm] != xx+1*/)/* && ((include_unknown->value() == 1) || (include_unknown->value()==0 && v == 0))*/) {
						if(v < (*vint_perpop_nsam)[y]) (*nsites1_pop)[y] += ((*matrix_sizepos)[xx]);
						if(v < (*vint_perpop_nsam)[y]-1) (*nsites2_pop)[y] += ((*matrix_sizepos)[xx]);
						if(v < (*vint_perpop_nsam)[y]-2) (*nsites3_pop)[y] += ((*matrix_sizepos)[xx]);
						for(k=1;k<(*vint_perpop_nsam)[y]-v;k++) {
							(*anx)[y] += 1.0/((double)k);
							(*bnx)[y] += 1.0/((double)k*(double)k);
						}
						p = 0;
						if(outgroup_presence->value() == 1) {
							for(x=nsamtot-1;x>=nsamtot-(*vint_perpop_nsam)[npops->value()-1];x--) {
								q = *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)x)+(unsigned long)xx));	
								if(q == 48+5) p += 1;
							}
							if(p < (*vint_perpop_nsam)[npops->value()-1] && v < (*vint_perpop_nsam)[y]/* && (*mhitbp)[xm] != xx+1*/)
								(*nsites1_pop_outg)[y] += ((*matrix_sizepos)[xx]);
							if(p < (*vint_perpop_nsam)[npops->value()-1] && v < (*vint_perpop_nsam)[y]-1/* && (*mhitbp)[xm] != xx+1*/)
								(*nsites2_pop_outg)[y] += ((*matrix_sizepos)[xx]);
							if(p < (*vint_perpop_nsam)[npops->value()-1] && v < (*vint_perpop_nsam)[y]-2/* && (*mhitbp)[xm] != xx+1*/)
								(*nsites3_pop_outg)[y] += ((*matrix_sizepos)[xx]);
							if(p < (*vint_perpop_nsam)[npops->value()-1]) {
								for(k=1;k<(*vint_perpop_nsam)[y]-p;k++) {
									(*anxo)[y] += 1.0/((double)k);
									(*bnxo)[y] += 1.0/((double)k*(double)k);
								}
							}
						}
					}
				}
				z += (*vint_perpop_nsam)[y];
				if((*nsites2_pop)[y]>0) {
					(*anx)[y] /= (double)(*nsites2_pop)[y];
					(*bnx)[y] /= (double)(*nsites2_pop)[y];
				}
				if((*nsites2_pop_outg)[y]>0) {
					(*anxo)[y] /= (double)(*nsites2_pop_outg)[y];
					(*bnxo)[y] /= (double)(*nsites2_pop_outg)[y];
				}
			}
			/*calculate lengthamng*/
			xm = 0;
			for(xx=0;xx<n_site->value();xx++) {
				z = 0;
				for(y=0;y<npops->value()-!outgroup_presence->value()-1;y++) {
					v = 0;
					for(x=z;x<z+(*vint_perpop_nsam)[y];x++) {
						w = *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)x)+(unsigned long)xx));	
						if(w == 48+5) v += 1;
					}
					z2 = z; x= y;
					while(x<y+1) {z2 += (*vint_perpop_nsam)[x]; x++;}
					for(y2=y+1;y2<npops->value()-!outgroup_presence->value();y2++) {
						v2 = 0;
						for(x=z2;x<z2+(*vint_perpop_nsam)[y2];x++) {
							w = *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)x)+(unsigned long)xx));	
							if(w == 48+5) v2 += 1;
						}
						while((*mhitbp)[xm]<xx+1 && xm<nmhits->value()) {xm++;} 
						p = 0;
						if((/*include_unknown->value() == 1 && */(*matrix_sizepos)[xx] > 0)/* || (include_unknown->value()==0 && v == 0 && (*matrix_sizepos)[xx] > 0)*/) {
							if(outgroup_presence->value() == 1) {
								for(x=nsamtot-1;x>=nsamtot-(*vint_perpop_nsam)[npops->value()-1];x--) {
									q = *((*DNA_matr)+(((long long)n_site->value()*(unsigned long)x)+(unsigned long)xx));	
									if(q == 48+5) p += 1;
								}
								if(p < (*vint_perpop_nsam)[npops->value()-1] && v < (*vint_perpop_nsam)[y] && v2 < (*vint_perpop_nsam)[y2]/* && (*mhitbp)[xm] != xx+1*/)
									(*lengthamng)[y][y2] += ((*matrix_sizepos)[xx]);
							}
							else {
								if(v < (*vint_perpop_nsam)[y] && v2 < (*vint_perpop_nsam)[y2]/* && (*mhitbp)[xm] != xx+1*/)
									(*lengthamng)[y][y2] += ((*matrix_sizepos)[xx]);
							}
						}
						z2 += (*vint_perpop_nsam)[y2];
					}
					z += (*vint_perpop_nsam)[y];
				}
			}
		}
		else {
			for(y=0;y<npops->value()-!outgroup_presence->value();y++) {
				for(k=1;k<(*vint_perpop_nsam)[y];k++) {
					(*anx)[y] += 1.0/((double)k);
					(*bnx)[y] += 1.0/((double)k*(double)k);
				}
				if((*vint_perpop_nsam)[y]>0) (*nsites1_pop)[y] = algsites;
				if((*vint_perpop_nsam)[y]>1) (*nsites2_pop)[y] = algsites;
				if((*vint_perpop_nsam)[y]>2) (*nsites3_pop)[y] = algsites;
				for(y2=y+1;y2<npops->value()-!outgroup_presence->value();y2++) {
					(*lengthamng)[y][y2] = algsites;
				}
				
				if(outgroup_presence->value() == 1) {
					for(k=1;k<(*vint_perpop_nsam)[y];k++) {
						(*anxo)[y] += 1.0/((double)k);
						(*bnxo)[y] += 1.0/((double)k*(double)k);
					}
					if((*vint_perpop_nsam)[y]>0) (*nsites1_pop_outg)[y] = algsites;
					if((*vint_perpop_nsam)[y]>1) (*nsites2_pop_outg)[y] = algsites;
					if((*vint_perpop_nsam)[y]>2) (*nsites3_pop_outg)[y] = algsites;
				}
			}
		}

		/**/
	}
	
	fflush(file_output);
	length_al->set_value(algsites);
	length_seg->set_value(bial_sites);
	
	svratio->set_value((double)transitions/(double)transversions);
	/**missratio = (double)totalmis/(double)(nnnsam*_sites);*/
  if(((double)(n_samp->value()-(*vint_perpop_nsam)[npops->value()-1])*n_realsite->value()))
    missratio->set_value((double)mis2/((double)(n_samp->value()-(*vint_perpop_nsam)[npops->value()-1])*n_realsite->value()));
  else
    missratio->set_value(1.0);
	
	free(unic);
	/*free((*mhitbp));*/
	free(nnsam);
	free(mvbp);
  

  
  if (file_mask != NULL) {
    fclose(file_mask);  //!added
  }
}

void CCalcFileStats::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
