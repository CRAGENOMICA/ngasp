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
 *  \brief     CCalcJointFreqDist.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcJointFreqDist.h"

#include "../../language/CStringTable.h"
#include "../util/CMatrixPol.h"
#include "../../data_manager/common/CDataAccess.h"


CCalcJointFreqDist::CCalcJointFreqDist()
: ICalculation(KeyString::CALC_JOINT_FREQ_DIST,
               KeyString::CALC_JOINT_FREQ_DIST_BRIEF_DESC,
               KeyString::CALC_JOINT_FREQ_DIST_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(force_outgroup,                                              // Variable
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
    SET_INPUT_INFO(nsam,                                                        // Variable
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
  
    SET_OUTPUT_INFO(jfd,                                                        // Variable
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
    SET_OUTPUT_INFO(stats_linefreq,                                             // Variable
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
    SET_OUTPUT_INFO(nfd,                                                        // Variable
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

CCalcJointFreqDist::~CCalcJointFreqDist() {
}

void CCalcJointFreqDist::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(force_outgroup)
    DM_INPUT(outgroup_presence)
    DM_INPUT(nsam)
    DM_INPUT(npops)
    DM_INPUT(matrix_pol)
    DM_INPUT(length)
  DM_GET_OUTPUTS
    DM_OUTPUT(jfd)
    DM_OUTPUT(stats_linefreq)
    DM_OUTPUT(nfd)
  DM_END
}

void CCalcJointFreqDist::Calculate(bool dry_run) {
  CMatrixPol matrixPol;

	long int j;
	int x,sumnsam;
	int a0,a1,a2,pol,polc,anc,ancl,n,popo,pop1,polv;
	int *initsq1,initso,inits;
 
    initsq1 = (int *)calloc(npops->value(),sizeof(int));

    sumnsam = 0;
    for(x=0;x<npops->value();x++) {
        initsq1[x] = sumnsam;
        sumnsam += (*nsam)[x];
    }
    
    a0=a1=0;
    for(j=0;j<length->value();j++) {
        //!20160504 GetData()
        if((matrixPol.ispolmis((*matrix_pol).GetData(),sumnsam,j,length->value())) > 0) 
            continue;
        else {
            polc = n = 0;
            initso = sumnsam-(*nsam)[npops->value()-1];/*initso is the number of sample where the outgroup (or single pop) starts*/
            while((a0 = (*matrix_pol)[j*sumnsam+initso]) == '-' && initso < sumnsam) initso++;
            if(initso >= sumnsam) polc = -1; /*we do not have outgroup (or pop) in this position and we do not count jfd*/
            else {
                n = 1;
                for(popo=initso+1;popo<sumnsam;popo++) {
                    while((a1 = (*matrix_pol)[j*sumnsam+popo]) == '-' && popo < sumnsam) popo++;
                    if(popo >= sumnsam) {
                        break;
                    }
                    else {
                        if(a1 != a0) {
                            polc += 1; /*there is polymorphism within the outgroup (or single pop)*/
                        }
                    }
                    n += 1;
                }
            }
            if(outgroup_presence->value()+force_outgroup->value() == 1 && polc== 0) { /*outgroup*/
                anc = a0;
                for(x=0;x<npops->value()-1;x++) {
                    a0 = a1 = pol = n = 0;
                    inits = initsq1[x];
                    while((a0 = (*matrix_pol)[j*sumnsam+inits]) == '-' && inits < initsq1[x]+(*nsam)[x]) inits += 1;
                    if(inits > initsq1[x]+(*nsam)[x]-1) pol = 0;
                    else {
                        n = 1;
                        for(pop1=inits+1;pop1<initsq1[x]+(*nsam)[x];pop1++) {
                            while((a1 = (*matrix_pol)[j*sumnsam+pop1]) == '-' && pop1 < initsq1[x]+(*nsam)[x]) pop1++;
                            if(pop1 >= initsq1[x]+(*nsam)[x]) break;
                            if(a1 != a0) {
                                pol += 1;
                            }
                            n += 1;
                        }				
                    }
                    if(n) {
                        if(anc != a0) pol = n-pol;
                        (*jfd)[x][j] = (double)pol/(double)n;
                        (*nfd)[x][j] = n;
                        
                        /*count frequency of snps per line*/
                        for(pop1=inits;pop1<initsq1[x]+(*nsam)[x];pop1++) {
                            while((a2 = (*matrix_pol)[j*sumnsam+pop1]) == '-' && pop1 < initsq1[x]+(*nsam)[x]) pop1++;
                            if(pop1 >= initsq1[x]+(*nsam)[x]) break;
                            if(a2 != anc) 
                                (*stats_linefreq)[pop1][pol] += 1;
                            /*else statistics[0].linefreq[pop1][n-pol] += 1;*/
                        }
                    }						
                }
            }
            else { 
                if(polc==0) { /*no outgroup*/
                    anc = a0;
                    for(x=0;x<npops->value()-1;x++) {
                        a0 = a1 = a2 = pol = n = 0;
                        inits = initsq1[x];
                        while((a0 = (*matrix_pol)[j*sumnsam+inits]) == '-' && inits < initsq1[x]+(*nsam)[x]) inits += 1;
                        if(inits > initsq1[x]+(*nsam)[x]-1) pol = 0;
                        else {
                            n = 1;
                            for(pop1=inits+1;pop1<initsq1[x]+(*nsam)[x];pop1++) {
                                while((a1 = (*matrix_pol)[j*sumnsam+pop1]) == '-' && pop1 < initsq1[x]+(*nsam)[x]) pop1++;
                                if(pop1 >= initsq1[x]+(*nsam)[x]) break;
                                if(a1 != a0) {
                                    pol += 1;
                                    a2 = a1;
                                }
                                n += 1;
                            }				
                        }
                        if(n) {
                            if/*(anc != a0)*/(pol > n-pol) pol = n-pol;
                            (*jfd)[x][j] = (double)pol/(double)n;
                            (*nfd)[x][j] = n;
                            /*
                            jfd[x][j] = (pol < n-pol)? (double)pol/(double)n:(double)(n-pol)/(double)n;
                            nfd[x][j] = n;
                            */
                            ancl  = (pol < n-pol)? a0:a2;
                            polv  = (pol < n-pol)? pol:n-pol;

                            /*count frequency of snps per line*/
                            for(pop1=inits;pop1<initsq1[x]+(*nsam)[x];pop1++)
                            {
                                while((a2 = (*matrix_pol)[j*sumnsam+pop1]) == '-' && pop1 < initsq1[x]+(*nsam)[x]) pop1++;
                                if(pop1 >= initsq1[x]+(*nsam)[x]) break;
                                if(a2 != ancl) 
                                    (*stats_linefreq)[pop1][polv] += 1;
                                /*else statistics[0].linefreq[pop1][n-pol] += 1;*/
                            }
                        }						
                    }
                }
            }
        }
    }
    free(initsq1);
}

void CCalcJointFreqDist::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
