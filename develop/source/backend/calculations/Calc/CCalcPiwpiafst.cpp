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
 *  \brief     CCalcPiwpiafst.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcPiwpiafst.h"

#include <cmath>

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataDoubleVector.h"
#include "../../data_manager/Data/CDataDoubleMatrix.h"
#include "../../data_manager/Data/CDataDoubleCube.h"

CCalcPiwpiafst::CCalcPiwpiafst()
: ICalculation(KeyString::CALC_PIWPIAFST,
               KeyString::CALC_PIWPIAFST_BRIEF_DESC,
               KeyString::CALC_PIWPIAFST_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(vint_perpop_nsam,                                            // Variable
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
    SET_INPUT_INFO(matrix_pol,                                                  // Variable
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
    SET_INPUT_INFO(matrix_sv,                                                   // Variable
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
    SET_INPUT_INFO(stats_tcga,                                                  // Variable
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
    SET_INPUT_INFO(stats_lengthamng,                                            // Variable
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
    SET_INPUT_INFO(flaghky,                                                     // Variable
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
    SET_INPUT_INFO(stats_length2,                                               // Variable
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
                   OPTTYPE_mandatory)                                           // Required
    SET_INPUT_INFO(length,                                                      // Variable
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
    SET_OUTPUT_INFO(stats_sv,                                                   // Variable
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
    SET_OUTPUT_INFO(stats_svT,                                                  // Variable
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
    SET_OUTPUT_INFO(stats_fst,                                                  // Variable
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
    SET_OUTPUT_INFO(stats_fst1all,                                              // Variable
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
    SET_OUTPUT_INFO(stats_fstHKY,                                               // Variable
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
    SET_OUTPUT_INFO(stats_K,                                                    // Variable
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
    SET_OUTPUT_INFO(stats_KHKY,                                                 // Variable
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
    SET_OUTPUT_INFO(stats_pia,                                                  // Variable
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
    SET_OUTPUT_INFO(stats_piaHKY,                                               // Variable
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
    SET_OUTPUT_INFO(stats_piT,                                                  // Variable
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
    SET_OUTPUT_INFO(stats_piTHKY,                                               // Variable
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
    SET_OUTPUT_INFO(stats_piwHKY,                                               // Variable
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
    SET_OUTPUT_INFO(stats_piw,                                                  // Variable
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
    SET_OUTPUT_INFO(stats_thetaTHKY,                                            // Variable
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
    SET_OUTPUT_INFO(stats_piant,                                                // Variable
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
    SET_OUTPUT_INFO(stats_piTnt,                                                // Variable
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
    SET_OUTPUT_INFO(stats_fstALL,                                               // Variable
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

void CCalcPiwpiafst::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

CCalcPiwpiafst::~CCalcPiwpiafst() {
}

void CCalcPiwpiafst::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(vint_perpop_nsam)
    DM_INPUT(npops)
    DM_INPUT(matrix_pol)
    DM_INPUT(matrix_sv)
    DM_INPUT(stats_tcga)
    DM_INPUT(stats_lengthamng)
    DM_INPUT(flaghky)
    DM_INPUT(stats_length2)
    DM_INPUT(formatfile)
    DM_INPUT(length)
  DM_GET_OUTPUTS
    DM_OUTPUT(stats_sv)
    DM_OUTPUT(stats_svT)
    DM_OUTPUT(stats_fst)
    DM_OUTPUT(stats_fst1all)
    DM_OUTPUT(stats_fstHKY)
    DM_OUTPUT(stats_K)
    DM_OUTPUT(stats_KHKY)
    DM_OUTPUT(stats_pia)
    DM_OUTPUT(stats_piaHKY)
    DM_OUTPUT(stats_piT)
    DM_OUTPUT(stats_piTHKY)
    DM_OUTPUT(stats_piwHKY)
    DM_OUTPUT(stats_piw)
    DM_OUTPUT(stats_thetaTHKY)
    DM_OUTPUT(stats_piant)
    DM_OUTPUT(stats_piTnt)
    DM_OUTPUT(stats_fstALL)
  DM_END
}

void CCalcPiwpiafst::Calculate(bool dry_run) {
	int x,y,z;
	long int j;
	int pop1,pop2;
	int **freq;
	int sumnsam,*initsq1,inits,max;
	double pia,piw,piT,*pia1all;
	double spiw,spiwn,spia,spian;
    double *mean_nsam,**mean_nsam_amng;
    long int *n_nsam,**n_nsam_amng;
	int ncw,nca;
	// double tn93(double,double,double,double, double, double, double,double);
	double gT,gC,gA,gG,P1,P2,Q;
	double total_effective_length,sumg;
	
    /*init*/
    z = 0;
    stats_fstALL->set_value(NA_VALUE);
    for(pop1=0;pop1<npops->value()-1;pop1++) {
        (*stats_piw)[pop1] = 0.;
        (*stats_K)[pop1] = 0.;
        (*stats_piwHKY)[pop1] = NA_VALUE;
        (*stats_KHKY)[pop1] = NA_VALUE;
        (*stats_fst1all)[pop1] = NA_VALUE;
        for(pop2=pop1+1;pop2<npops->value();pop2++) {
            (*stats_pia)[z] = 0.;
            (*stats_piT)[z] = 0.;
            (*stats_piaHKY)[z] = NA_VALUE;
            (*stats_piTHKY)[z] = NA_VALUE;
            (*stats_fst)[z] = NA_VALUE;
            (*stats_fstHKY)[z] = NA_VALUE;
            z++;
        }
    }
    
    if(length->value()==0) return;

    initsq1 = (int *)calloc(npops->value(),sizeof(int));
    pia1all = (double *)calloc(npops->value(),sizeof(double));
    freq = (int **)calloc(npops->value(),sizeof(int *));
    for(x=0;x<npops->value();x++) freq[x] = (int *)calloc(4,sizeof(int));
    mean_nsam = (double *)calloc(npops->value(),sizeof(double));
    mean_nsam_amng = (double **)calloc(npops->value(),sizeof(double *));
    for(x=0;x<npops->value();x++) mean_nsam_amng[x] = (double *)calloc(npops->value(),sizeof(double));
    n_nsam = (long int *)calloc(npops->value(),sizeof(long int));
    n_nsam_amng = (long int **)calloc(npops->value(),sizeof(long int *));
    for(x=0;x<npops->value();x++) n_nsam_amng[x] = (long int *)calloc(npops->value(),sizeof(long int));

    sumnsam = 0;
    for(x=0;x<npops->value();x++) {
        initsq1[x] = sumnsam;
        sumnsam += (*vint_perpop_nsam)[x];
    }
    
    /*NOTE THE HAPLOTYPE VALUES GO FROM 0 to npops-1 BUT FREQUENCY GOES FROM 0 to npops!!!!!!*/
    for(j=0;j<length->value();j++) {		
        /*calculate the frequencies of each population for each position*/
        for(pop1=0;pop1<npops->value()-0;pop1++) {
            inits = initsq1[pop1];
            max   = initsq1[pop1]+(*vint_perpop_nsam)[pop1];
            freq[pop1][0]=freq[pop1][1]=freq[pop1][2]=freq[pop1][3]=0;
            for(y=inits;y<max;y++) {
                if((*matrix_pol)[j*sumnsam+y] == '0') {freq[pop1][1] += 1;freq[pop1][0] += 1;}
                if((*matrix_pol)[j*sumnsam+y] == '1') {freq[pop1][2] += 1;freq[pop1][0] += 1;}
                if((*matrix_pol)[j*sumnsam+y] == '-') {freq[pop1][3] += 1;}
            }
            if((*vint_perpop_nsam)[pop1] > 1 && freq[pop1][0] > 1) {
                piw = (double)(freq[pop1][1]*freq[pop1][2])/(double)(freq[pop1][0]*(freq[pop1][0]-1.0)/2.0);
                (*stats_piw)[pop1] += piw;
                if(flaghky->value() == 1) if((*matrix_sv)[j] == 1) (*stats_sv)[pop1][pop1][0] += piw;
                if(flaghky->value() == 1) if((*matrix_sv)[j] == 2) (*stats_sv)[pop1][pop1][1] += piw;
                mean_nsam[pop1] += (double)freq[pop1][0];
                n_nsam[pop1] += 1;
            }
        }
        z=0;
        for(pop1=0;pop1<npops->value()-1;pop1++) {
            for(pop2=pop1+1;pop2<npops->value()-0;pop2++) {
                if((freq[pop1][0]*freq[pop2][0]) > 0) {
                    pia = (double)(freq[pop1][1]*freq[pop2][2] + freq[pop1][2]*freq[pop2][1])/(double)(freq[pop1][0]*freq[pop2][0]);
                    (*stats_pia)[z] += pia;
                    if(flaghky->value() == 1) if((*matrix_sv)[j] == 1) (*stats_sv)[pop1][pop2][0] += pia;
                    if(flaghky->value() == 1) if((*matrix_sv)[j] == 2) (*stats_sv)[pop1][pop2][1] += pia;
                    if(pop2 ==npops->value()-1) 
                        (*stats_K)[pop1] += pia;
                    if((pop2 < npops->value()-1 || npops->value() == 2) && (*vint_perpop_nsam)[pop1]>1 && (*vint_perpop_nsam)[pop2]>1) {
                        /*we do not show these results. we do not consider those values that are not in Fst*/
                        pia1all[pop1] += pia;
                        pia1all[pop2] += pia;
                    }
                    mean_nsam_amng[pop1][pop2] += (double)freq[pop1][0] * (double)freq[pop2][0];
                    mean_nsam_amng[pop1][pop2] += 1;
                }
                z++;
            }
        }
        z = 0;
        for(pop1=0;pop1<npops->value()-1;pop1++) {
            for(pop2=pop1+1;pop2<npops->value()-0;pop2++) {
                if(((*vint_perpop_nsam)[pop1]+(*vint_perpop_nsam)[pop2]) > 1 && (freq[pop1][0]+freq[pop2][0]) > 1) {
                    piT = (double)((freq[pop1][1]+freq[pop2][1])*(freq[pop1][2]+freq[pop2][2]))/(double)((freq[pop1][0]+freq[pop2][0])*((freq[pop1][0]+freq[pop2][0])-1.0)/2.0);
                    (*stats_piT)[z] += piT;
                    if(flaghky->value() == 1) if((*matrix_sv)[j] == 1) (*stats_svT)[pop1][pop2][0] += piT;
                    if(flaghky->value() == 1) if((*matrix_sv)[j] == 2) (*stats_svT)[pop1][pop2][1] += piT;
                }
                z++;
            }
        }
    }
    
    for(pop1=0;pop1<npops->value()-1;pop1++) {
        mean_nsam[pop1] = mean_nsam[pop1]/(double)n_nsam[pop1];
        for(pop2=pop1+1;pop2<npops->value()-0;pop2++) {
            mean_nsam_amng[pop1][pop2] = mean_nsam_amng[pop1][pop2]/(double)mean_nsam_amng[pop1][pop2];
        }
    }
  
//	int x,y,z;
//	long int j;
//	int pop1,pop2;
//	int **freq;
//	int sumnsam,*initsq1,inits,max;
//	double pia,piw,piT,*pia1all;
//	double spiw,spiwn,spia,spian;
//    double *mean_nsam,**mean_nsam_amng;
//    long int *n_nsam,**n_nsam_amng;
//	int ncw,nca;
////	double tn93(double,double,double,double, double, double, double,double);
//	double gT,gC,gA,gG,P1,P2,Q;
//	double total_effective_length,sumg;
//
//    /*init*/
//    z = 0;
//    stats_fstALL->set_value(NA_VALUE);
//    for(pop1=0;pop1<npops->value()-1;pop1++) {
//        (*stats_piw)[pop1] = 0.;
//        (*stats_K)[pop1] = 0.;
//        (*stats_piwHKY)[pop1] = NA_VALUE;
//        (*stats_KHKY)[pop1] = NA_VALUE;
//        (*stats_fst1all)[pop1] = NA_VALUE;
//        for(pop2=pop1+1;pop2<npops->value();pop2++) {
//            (*stats_pia)[z] = 0.;
//            (*stats_piT)[z] = 0.;
//            (*stats_piaHKY)[z] = NA_VALUE;
//            (*stats_piTHKY)[z] = NA_VALUE;
//            (*stats_fst)[z] = NA_VALUE;
//            (*stats_fstHKY)[z] = NA_VALUE;
//            z++;
//        }
//    }
//    
//    if(length->value()==0) return 1;
//
//    initsq1 = (int *)calloc(npops->value(),sizeof(int));
//    pia1all = (double *)calloc(npops->value(),sizeof(double));
//    freq = (int **)calloc(npops->value(),sizeof(int *));
//    for(x=0;x<npops->value();x++) freq[x] = (int *)calloc(4,sizeof(int));
//    mean_nsam = (double *)calloc(npops->value(),sizeof(double));
//    mean_nsam_amng = (double **)calloc(npops->value(),sizeof(double *));
//    for(x=0;x<npops->value();x++) mean_nsam_amng[x] = (double *)calloc(npops->value(),sizeof(double));
//    n_nsam = (long int *)calloc(npops->value(),sizeof(long int));
//    n_nsam_amng = (long int **)calloc(npops->value(),sizeof(long int *));
//    for(x=0;x<npops->value();x++) n_nsam_amng[x] = (long int *)calloc(npops->value(),sizeof(long int));
//
//    sumnsam = 0;
//    for(x=0;x<npops->value();x++) {
//        initsq1[x] = sumnsam;
//        sumnsam += (*vint_perpop_nsam)[x];
//    }
//    
//
//    
//    /*NOTE THE HAPLOTYPE VALUES GO FROM 0 to npops-1 BUT FREQUENCY GOES FROM 0 to npops!!!!!!*/
//    for(j=0;j<length->value();j++) {		
//        /*calculate the frequencies of each population for each position*/
//        for(pop1=0;pop1<npops->value()-0;pop1++) {
//            inits = initsq1[pop1];
//            max   = initsq1[pop1]+(*vint_perpop_nsam)[pop1];
//            freq[pop1][0]=freq[pop1][1]=freq[pop1][2]=freq[pop1][3]=0;
//            for(y=inits;y<max;y++) {
//                if((*matrix_pol)[j*sumnsam+y] == '0') {freq[pop1][1] += 1;freq[pop1][0] += 1;}
//                if((*matrix_pol)[j*sumnsam+y] == '1') {freq[pop1][2] += 1;freq[pop1][0] += 1;}
//                if((*matrix_pol)[j*sumnsam+y] == '-') {freq[pop1][3] += 1;}
//            }
//            if((*vint_perpop_nsam)[pop1] > 1 && freq[pop1][0] > 1) {
//                piw = (double)(freq[pop1][1]*freq[pop1][2])/(double)(freq[pop1][0]*(freq[pop1][0]-1.0)/2.0);
//                (*stats_piw)[pop1] += piw;
//                if(flaghky->value() == 1) if((*matrix_sv)[j] == 1) (*stats_sv)[pop1][pop1][0] += piw;
//                if(flaghky->value() == 1) if((*matrix_sv)[j] == 2) (*stats_sv)[pop1][pop1][1] += piw;
//                mean_nsam[pop1] += (double)freq[pop1][0];
//                n_nsam[pop1] += 1;
//            }
//        }
//        z=0;
//        for(pop1=0;pop1<npops->value()-1;pop1++) {
//            for(pop2=pop1+1;pop2<npops->value()-0;pop2++) {
//                if((freq[pop1][0]*freq[pop2][0]) > 0) {
//                    pia = (double)(freq[pop1][1]*freq[pop2][2] + freq[pop1][2]*freq[pop2][1])/(double)(freq[pop1][0]*freq[pop2][0]);
//                    (*stats_pia)[z] += pia;
//                    if(flaghky->value() == 1) if((*matrix_sv)[j] == 1) (*stats_sv)[pop1][pop2][0] += pia;
//                    if(flaghky->value() == 1) if((*matrix_sv)[j] == 2) (*stats_sv)[pop1][pop2][1] += pia;
//                    if(pop2 ==npops->value()-1) 
//                        (*stats_K)[pop1] += pia;
//                    if((pop2 < npops->value()-1 || npops->value() == 2) && (*vint_perpop_nsam)[pop1]>1 && (*vint_perpop_nsam)[pop2]>1) {
//                        /*we do not show these results. we do not consider those values that are not in Fst*/
//                        pia1all[pop1] += pia;
//                        pia1all[pop2] += pia;
//                    }
//                    mean_nsam_amng[pop1][pop2] += (double)freq[pop1][0] * (double)freq[pop2][0];
//                    mean_nsam_amng[pop1][pop2] += 1;
//                }
//                z++;
//            }
//        }
//        z = 0;
//        for(pop1=0;pop1<npops->value()-1;pop1++) {
//            for(pop2=pop1+1;pop2<npops->value()-0;pop2++) {
//                if(((*vint_perpop_nsam)[pop1]+(*vint_perpop_nsam)[pop2]) > 1 && (freq[pop1][0]+freq[pop2][0]) > 1) {
//                    piT = (double)((freq[pop1][1]+freq[pop2][1])*(freq[pop1][2]+freq[pop2][2]))/(double)((freq[pop1][0]+freq[pop2][0])*((freq[pop1][0]+freq[pop2][0])-1.0)/2.0);
//                    (*stats_piT)[z] += piT;
//                    if(flaghky->value() == 1) if((*matrix_sv)[j] == 1) (*stats_svT)[pop1][pop2][0] += piT;
//                    if(flaghky->value() == 1) if((*matrix_sv)[j] == 2) (*stats_svT)[pop1][pop2][1] += piT;
//                }
//                z++;
//            }
//        }
//    }
//    
//    for(pop1=0;pop1<npops->value()-1;pop1++) {
//        mean_nsam[pop1] = mean_nsam[pop1]/(double)n_nsam[pop1];
//        for(pop2=pop1+1;pop2<npops->value()-0;pop2++) {
//            mean_nsam_amng[pop1][pop2] = mean_nsam_amng[pop1][pop2]/(double)mean_nsam_amng[pop1][pop2];
//        }
//    }
    
    /*HKY correction and piant*/
    if(flaghky->value() == 1) { 
        if(formatfile->value() == FASTA_FILE || formatfile->value() == TFASTA_FILE) {
            z=0;
            for(pop1=0;pop1<npops->value()-1;pop1++)
            {
                if((double)(*stats_length2)[pop1] == 0) {
                    (*stats_piwHKY)[pop1] = NA_VALUE;
                    (*stats_thetaTHKY)[pop1] = NA_VALUE;
                    for(pop2=pop1+1;pop2<npops->value()-0;pop2++) {
                        (*stats_piaHKY)[z] = NA_VALUE;
                        (*stats_piTHKY)[z] = NA_VALUE;
                        if(pop2 ==npops->value()-1) 
                            (*stats_KHKY)[pop1] = NA_VALUE;
                        (*stats_piant)[z] = NA_VALUE;
                        (*stats_piTnt)[z] = NA_VALUE;
                        z++;
                    }
                    continue;
                }
                /**/total_effective_length = (double)(*stats_length2)[pop1];/**/
                sumg = (double) (*stats_tcga)[pop1][0] + (*stats_tcga)[pop1][1] + (*stats_tcga)[pop1][2] + (*stats_tcga)[pop1][3];
                gT = (*stats_tcga)[pop1][0] /sumg * total_effective_length;
                gC = (*stats_tcga)[pop1][1] /sumg * total_effective_length;
                gG = (*stats_tcga)[pop1][2] /sumg * total_effective_length;
                gA = (*stats_tcga)[pop1][3] /sumg * total_effective_length;
                P1 = (*stats_sv)[pop1][pop1][0] * (gA*gG/(gA*gG + gT*gC));
                P2 = (*stats_sv)[pop1][pop1][0] * (gT*gC/(gA*gG + gT*gC));		
                Q = (*stats_sv)[pop1][pop1][1];		
                (*stats_piwHKY)[pop1] = tn93(gT,gC,gG,gA,P1,P2,Q,/*stats_total_length*/ /**/total_effective_length/**/);
                (*stats_thetaTHKY)[pop1] = (*stats_piwHKY)[pop1];
                for(pop2=pop1+1;pop2<npops->value()-0;pop2++)
                {
                    if((double)(*stats_lengthamng)[pop1][pop2] == 0) {
                        (*stats_piaHKY)[z] = NA_VALUE;
                        (*stats_piTHKY)[z] = NA_VALUE;
                        if(pop2 ==npops->value()-1) 
                            (*stats_KHKY)[pop1] = NA_VALUE;
                        (*stats_piant)[z] = NA_VALUE;
                        (*stats_piTnt)[z] = NA_VALUE;
                        z++;
                        continue;
                    }
                    total_effective_length = (double)(*stats_lengthamng)[pop1][pop2];
                    sumg = (double) (*stats_tcga)[pop1][0] + (*stats_tcga)[pop1][1] + (*stats_tcga)[pop1][2] + (*stats_tcga)[pop1][3] + 
                                    (*stats_tcga)[pop2][0] + (*stats_tcga)[pop2][1] + (*stats_tcga)[pop2][2] + (*stats_tcga)[pop2][3];
                    gT = ((*stats_tcga)[pop1][0] + (*stats_tcga)[pop2][0]) /sumg * total_effective_length;
                    gC = ((*stats_tcga)[pop1][1] + (*stats_tcga)[pop2][1]) /sumg * total_effective_length;
                    gG = ((*stats_tcga)[pop1][2] + (*stats_tcga)[pop2][2]) /sumg * total_effective_length;
                    gA = ((*stats_tcga)[pop1][3] + (*stats_tcga)[pop2][3]) /sumg * total_effective_length;		
                    P1 = (*stats_sv)[pop1][pop2][0] * (gA*gG/(gA*gG + gT*gC));
                    P2 = (*stats_sv)[pop1][pop2][0] * (gT*gC/(gA*gG + gT*gC));		
                    Q = (*stats_sv)[pop1][pop2][1];		
                    (*stats_piaHKY)[z] = tn93(gT,gC,gG,gA,P1,P2,Q,/*stats_total_length*/ /**/total_effective_length/**/);/*it is incorrect in case missing values are considered...*/
                    /*piant*/  
                    (*stats_piant)[z] = (*stats_pia)[z]/(double)(total_effective_length/*stats_total_length*/);/*incorrect*/

                    P1 = (*stats_svT)[pop1][pop2][0] * (gA*gG/(gA*gG + gT*gC));
                    P2 = (*stats_svT)[pop1][pop2][0] * (gT*gC/(gA*gG + gT*gC));		
                    Q =  (*stats_svT)[pop1][pop2][1];		
                    (*stats_piTHKY)[z] = tn93(gT,gC,gG,gA,P1,P2,Q,/*stats_total_length*/ /**/total_effective_length/**/);/*it is incorrect in case missing values are considered...*/
                    /*piTnt*/  
                    (*stats_piTnt)[z] = (*stats_piT)[z]/(double)(/**/total_effective_length/*stats_total_length*/);/*incorrect*/

                    if(pop2 ==npops->value()-1) 
                        (*stats_KHKY)[pop1] = (*stats_piaHKY)[z];
                    z++;					
                }
            }
        }
        if(formatfile->value() == MS_FILE || formatfile->value() == MS_X_FILE) {
            z=0;
            /*
            for(pop1=0;pop1<npops;pop1++) {
                n1 = ceil(stats_length[pop1]/stats_total_length - 1E-5/);
                gT = stats_tcga[pop1][0];
                gC = stats_tcga[pop1][1];
                gG = stats_tcga[pop1][2];
                gA = stats_tcga[pop1][3];		
                P1 = stats_sv[pop1][pop1][0] * (gA*gG/(gA*gG + gT*gC));
                P2 = stats_sv[pop1][pop1][0] * (gT*gC/(gA*gG + gT*gC));		
                Q = stats_sv[pop1][pop1][1];		
                (*stats_piwHKY)[pop1] = tn93(gT,gC,gG,gA,P1,P2,Q,stats_total_length);
                stats_thetaTHKY[pop1] = (*stats_piwHKY)[pop1];
                for(pop2=pop1+1;pop2<npops;pop2++) {
                    n2 = ceil(stats_length[pop2]/stats_total_length- 1E-5);
                    gT = stats_tcga[pop1][0] + stats_tcga[pop2][0];
                    gC = stats_tcga[pop1][1] + stats_tcga[pop2][1];
                    gG = stats_tcga[pop1][2] + stats_tcga[pop2][2];
                    gA = stats_tcga[pop1][3] + stats_tcga[pop2][3];		
                    P1 = stats_sv[pop1][pop2][0] * (gA*gG/(gA*gG + gT*gC));
                    P2 = stats_sv[pop1][pop2][0] * (gT*gC/(gA*gG + gT*gC));		
                    Q = stats_sv[pop1][pop2][1];		
                    (*stats_piaHKY)[z] = tn93(gT,gC,gG,gA,P1,P2,Q,stats_total_length);
                    if(pop2 ==npops-1) 
                        (*stats_KHKY)[pop1] = (*stats_piaHKY)[z];
                    stats_piant[z] = (*stats_pia)[z]/(double)(stats_total_length);
                    z++;					
                }
            }
            */
        }
    }
    else {
        if(formatfile->value() == MS_FILE || formatfile->value() == MS_X_FILE) {
            z=0;
            for(pop1=0;pop1<npops->value()-1;pop1++) {
                (*stats_piwHKY)[pop1] = NA_VALUE;
                (*stats_thetaTHKY)[pop1] = NA_VALUE;
                for(pop2=pop1+1;pop2<npops->value()-0;pop2++) {
                    (*stats_piaHKY)[z] = NA_VALUE;
                    (*stats_piTHKY)[z] = NA_VALUE;
                    if(pop2 ==npops->value()-1) 
                        (*stats_KHKY)[pop1] = NA_VALUE;
                    (*stats_piant)[z] = NA_VALUE;
                    (*stats_piTnt)[z] = NA_VALUE;
                    z++;
                }
            }
        }
    }
    
    /*Fst pair-pair*/
    z=0;
    for(pop1=0;pop1<npops->value()-1;pop1++) {
        for(pop2=pop1+1;pop2<npops->value()-0;pop2++) {
            if((*stats_pia)[z] && (*vint_perpop_nsam)[pop1] > 1 && (*vint_perpop_nsam)[pop2] > 1 &&
               (double)(*stats_length2)[pop1] > 0 && 
               (double)(*stats_length2)[pop2] > 0 &&
               (double)(*stats_lengthamng)[pop1][pop2] > 0) {
                (*stats_fst)[z] = 1.0 - (((*stats_piw)[pop1]/(double)(*stats_length2)[pop1] + 
                                               (*stats_piw)[pop2]/(double)(*stats_length2)[pop2])/2.0 
                                              + MISSINGH*(*stats_pia)[z]/(double)(*stats_lengthamng)[pop1][pop2])/
                                                ((*stats_pia)[z]/(double)(*stats_lengthamng)[pop1][pop2]);
            } else {
                (*stats_fst)[z] = NA_VALUE;
            }
            if(flaghky->value() == 1 &&
               (double)(*stats_length2)[pop1] > 0 && 
               (double)(*stats_length2)[pop2] > 0 &&
               (double)(*stats_lengthamng)[pop1][pop2] > 0) {
                if((*stats_piaHKY)[z] > 0 && (*vint_perpop_nsam)[pop1] > 1 && (*vint_perpop_nsam)[pop2] > 1) {
                    (*stats_fstHKY)[z] = 1.0 - (((*stats_piwHKY)[pop1]/(double)(*stats_length2)[pop1] + 
                                                      (*stats_piwHKY)[pop2]/(double)(*stats_length2)[pop2])/2.0)/
                                                    ((*stats_piaHKY)[z]/(double)(*stats_lengthamng)[pop1][pop2]);
                } else {
                    (*stats_fstHKY)[z] = -10000;
                }
            }
            else if(formatfile->value() == MS_FILE || formatfile->value() == MS_X_FILE) (*stats_fstHKY)[z] = NA_VALUE;
            z++;
        }
    }
        
    /*Fstall*//*Fst calculated excluding the outgroup (always the last even in case it is not defined)*/
    if(npops->value() > 2) {
        z = 0;
        spiw = spiwn = spia = spian = 0.;
        ncw = nca = 0;
        for(pop1=0;pop1<npops->value()-1;pop1++) {
            if((*vint_perpop_nsam)[pop1] > 1 && (double)(*stats_length2)[pop1] > 0) {
                spiwn += (*stats_piw)[pop1]/(double)(*stats_length2)[pop1];
                spiw  += (*stats_piw)[pop1]/(double)(*stats_length2)[pop1] * mean_nsam[pop1] * (mean_nsam[pop1]-1.0) / 2.0;
                ncw += 1;
            }
            for(pop2=pop1+1;pop2<npops->value()-0;pop2++) {
                if((*vint_perpop_nsam)[pop1] + (*vint_perpop_nsam)[pop2] > 1 && pop2 < npops->value()-1 && (double)(*stats_lengthamng)[pop1][pop2] > 0) {
                    spian += (*stats_pia)[z]/(double)(*stats_lengthamng)[pop1][pop2];
                    spia  += (*stats_pia)[z]/(double)(*stats_lengthamng)[pop1][pop2] * mean_nsam_amng[pop1][pop2];
                    nca += 1;
                }
                z++;
            }
        }
        for(pop1=0;pop1<npops->value()-1;pop1++) {
            if((*vint_perpop_nsam)[pop1] > 1 && (/*spiw+*/spia) > 0.) {
                /*(*stats_fst1all)[pop1] = 1.0 - ((*stats_piw)[pop1]/((spiw+spia)/((sumnsam-nsam[npops-1])*(sumnsam-nsam[npops-1]-1.0)/2.0)));*/
                /*(*stats_fst1all)[pop1] = 1.0 - ((*stats_piw)[pop1]/((spia)/((sumnsam-nsam[npops-1])*(sumnsam-nsam[npops-1]-1.0)/2.0)));*/
                (*stats_fst1all)[pop1] = 1.0 - (((*stats_piw)[pop1]/(double)(*stats_length2)[pop1])/((spian)/(double)nca));
            } else {
                (*stats_fst1all)[pop1] = NA_VALUE;
            }
        }
        /*calculate fstALL*/
        if((/*spiw+*/spia) > 0.) {
            /*stats_fstALL = 1.0 - ((spiwn/(double)ncw)/((spiw+spia)/((sumnsam-nsam[npops-1])*(sumnsam-nsam[npops-1]-1.0)/2.0)));*/
            /*stats_fstALL = 1.0 - ((spiwn/(double)ncw)/((spia)/((sumnsam-nsam[npops-1])*(sumnsam-nsam[npops-1]-1.0)/2.0)));*/
            stats_fstALL->set_value(1.0 - ((spiwn/(double)ncw)/((spian)/(double)nca)));
        } else {
            stats_fstALL->set_value(NA_VALUE);
        }
    }
    
    free(initsq1);
    free(pia1all);
    for(x=0;x<npops->value();x++) free(freq[x]);
    free(freq);
    free(mean_nsam);
    for(x=0;x<npops->value();x++) free(mean_nsam_amng[x]);
    free(mean_nsam_amng);
    free(n_nsam);
    for(x=0;x<npops->value();x++) free(n_nsam_amng[x]);
    free(n_nsam_amng);
}

/*P1 is the A/G, P2 is T/C and Q is transversions.*/
double CCalcPiwpiafst::tn93(double gT,double gC,double gG,double gA, double P1, double P2, double Q,double len) {
	double d1,d2,d3,gR,gY,sum,d;
	
	sum = gT+gC+gG+gA;
	gT 	= gT/sum;
	gC 	= gC/sum;
	gG 	= gG/sum;
	gA 	= gA/sum;
	P1 	= P1/len;
	P2 	= P2/len;
	Q  	= Q/len;
	
	gR = gA + gG;
	gY = gT + gC;
	
	if(P1+P2+Q == 0) return 0.;
	if(gR/(2.*gA*gG) * P1 - 1./(2.*gR) * Q >= 1.) return NA_VALUE;
	if(gY/(2.*gT*gC) * P2 - 1./(2.*gY) * Q >= 1.) return NA_VALUE;
	if(1./(2.*gR*gY) * Q >= 1.) return NA_VALUE;
	
	d1 = -2.*gA*gG/gR * log(1. - gR/(2.*gA*gG) * P1 - 1./(2.*gR) * Q);
	d2 = -2.*gT*gC/gY * log(1. - gY/(2.*gT*gC) * P2 - 1./(2.*gY) * Q);
	d3 = -2.*(gR*gY - gA*gG*gY/gR - gT*gC*gR/gY) * log(1. - 1./(2.*gR*gY) * Q);
	
	d = d1 + d2 + d3;
	
	if(d < 0.) return NA_VALUE;
	return d;
}
