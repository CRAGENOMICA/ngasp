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
 *  \brief     CCalcSxsfss.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcSxsfss.h"

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../util/CMatrixPol.h"

CCalcSxsfss::CCalcSxsfss()
: ICalculation(KeyString::CALC_SXSFSS,
               KeyString::CALC_SXSFSS_BRIEF_DESC,
               KeyString::CALC_SXSFSS_DESC,
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
    SET_INPUT_INFO(matrix_pos,                                                  // Variable
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
  
    SET_OUTPUT_INFO(sites_matrix,                                               // Variable
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
    SET_OUTPUT_INFO(stats_sanc,                                                 // Variable
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

CCalcSxsfss::~CCalcSxsfss() {
}

void CCalcSxsfss::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(force_outgroup)
    DM_INPUT(outgroup_presence)
    DM_INPUT(nsam)
    DM_INPUT(npops)
    DM_INPUT(matrix_pol)
    DM_INPUT(matrix_pos)
    DM_INPUT(length)
  DM_GET_OUTPUTS
    DM_OUTPUT(sites_matrix)
    DM_OUTPUT(stats_sanc)
  DM_END
}

void CCalcSxsfss::Calculate(bool dry_run) {
  CMatrixPol matrixPol;

  //!20160505 regs() by Size()
  if ((*matrix_pol).Size() == 0) {
    matrix_pol->Print(PrintMode::NORMAL);
    ERROR_MSG << STR(QUOTE) << GetParentInput(4) << "::" 
                            << GetInputName(4)
              << STR(QUOTE)
              << " has no records..."
              END_MSG;
    return;
  }

	int x;
	long int j;
	int sumnsam;
	int ispolmis(char *,int,long int,long int);
	int polc,pop1,pop2,popo,npo;
	int a0,a1;
	int *initsq1,*initsq1a,*initsq2,initso,initsa,*polqa,*polqb;
	int initsb=0;
	long int *y0,*y1,*y2,*y3,*o0,*o1,*o2,*o3;
	long int css_rest;
  
  
  //NO: sites_matrix_matrix->ReserveMemory(matrix_pol->regs() * 4, length->value());
  //!20160505 replace (a,b,c) by (a*b,c))
  sites_matrix->ReserveMemory((4 * npops->value()) * ((length->value() + 1)), 0);
  stats_sanc->ReserveMemory(4 * npops->value(), 0);

  
    for(x=0;x<4*npops->value();x++) {
        (*stats_sanc)[x] = 0;
    }
    if(length->value()==0) return;
    
        initsq1 = (int *)calloc(npops->value(),sizeof(int));
        initsq2 = (int *)calloc(npops->value(),sizeof(int));
    initsq1a= (int *)calloc(npops->value(),sizeof(int));
    polqa   = (int *)calloc(npops->value(),sizeof(int));
    polqb   = (int *)calloc(npops->value(),sizeof(int));
    
    y0   = (long int *)calloc(npops->value(),sizeof(long int));
    y1   = (long int *)calloc(npops->value(),sizeof(long int));
    y2   = (long int *)calloc(npops->value(),sizeof(long int));
    y3   = (long int *)calloc(npops->value(),sizeof(long int));
    o0   = (long int *)calloc(1,sizeof(long int));
    o1   = (long int *)calloc(1,sizeof(long int));
    o2   = (long int *)calloc(1,sizeof(long int));
    o3   = (long int *)calloc(1,sizeof(long int));
    
    sumnsam = 0;
    for(x=0;x<npops->value();x++) {
        initsq1[x] = sumnsam;
        if(x) initsq2[x] = 0;
        else initsq2[x] = (*nsam)[0];
        sumnsam += (*nsam)[x];
        y0[x]=y1[x]=y2[x]=y3[x]=0;
    }
    o0[0]=o1[0]=o2[0]=0;
    
    a0=a1=0;
    for(j=0;j<length->value();j++)
    {
        if((matrixPol.ispolmis((*matrix_pol).GetData(),sumnsam,j,length->value())) > 0) {
            continue;
        }
        else {
            /*outgroup*/
            polc = 0;
            initso = sumnsam-(*nsam)[npops->value()-1];
            while((a0 = (*matrix_pol)[j*sumnsam+initso]) == '-' && initso < sumnsam) initso++;
            if(initso >= sumnsam) {
                polc = -1;
            }
            else
            {
                for(popo=initso+1;popo<sumnsam;popo++) {
                    while((a1 = (*matrix_pol)[j*sumnsam+popo]) == '-' && popo < sumnsam) popo++;
                    if(popo >= sumnsam) {
                        polc = 0;
                        break;
                    }
                    else {
                        if(a1 != a0) {
                            polc = 1;
                            break;
                        }
                    }
                }				
            }
            /*populations*/
            css_rest = 1;
            for(x=0;x<npops->value()-1;x++) {
                /*check if each group is polymorphic or not*/
                polqa[x] = polqb[x] = 0;
                initsa = initsq1a[x] = initsq1[x];
                while((a0 = (*matrix_pol)[j*sumnsam+initsa]) == '-' && initsa < initsq1[x]+(*nsam)[x]) initsa += 1;
                if(initsa >= initsq1[x]+(*nsam)[x]) {polqa[x] = -1;}
                else {
                    initsq1a[x] = initsa;
                    for(pop1=initsa+1;pop1<initsq1[x]+(*nsam)[x];pop1++) {
                        while((a1 = (*matrix_pol)[j*sumnsam+pop1]) == '-' && pop1 < initsq1[x]+(*nsam)[x]) pop1++;
                        if(pop1 >= initsq1[x]+(*nsam)[x]) break;
                        if(a1 != a0) {
                            polqa[x] = 1;
                            break;
                        }
                    }				
                }
                for(pop1=0;pop1<npops->value()-1;pop1++) {
                    if(pop1 != x) {
                        initsb = initsq2[x];
                        while((a0 = (*matrix_pol)[j*sumnsam+initsb]) == '-' && initsb < sumnsam-(*nsam)[npops->value()-1]) {
                            if(initsb == initsq1[x]) 
                                initsb += (*nsam)[x];
                            else initsb += 1;
                        }
                        if(initsb >= (sumnsam-(*nsam)[npops->value()-1])) polqb[x] = -1;
                        else {
                            /*a0 = nt in inits+0*/
                            for(pop2=initsb+1;pop2<sumnsam-(*nsam)[npops->value()-1];pop2++) {
                                if(pop2 >= initsq1[x] && pop2 < initsq1[x]+(*nsam)[x]) 
                                    pop2 = initsq1[x+1];
                                while((a1 = (*matrix_pol)[j*sumnsam+pop2]) == '-' && pop2 < sumnsam-(*nsam)[npops->value()-1]) {
                                    if(pop2 == initsq1[x]) pop2 += (*nsam)[x];
                                    else pop2++;
                                }
                                if(pop2 >= initsq1[x] && pop2 < initsq1[x]+(*nsam)[x]) 
                                    pop2 = initsq1[x+1];
                                if(pop2 >= (sumnsam-(*nsam)[npops->value()-1])) break;
                                if(a1 != a0) {
                                    polqb[x] = 1;
                                    break;
                                }
                            }				
                        }
                    }
                    if(polqb[x] == 1) break;
                }
                /*define classes*/
                if(polqa[x]==1 && polqb[x]==0 && polc==0) {
                    if((npops->value() == 2) || ((*matrix_pol)[j*sumnsam+initsb] == (*matrix_pol)[j*sumnsam+initso])) {
                        (*stats_sanc)[x*4+0] += 1;/*Sx1*/
                        (*sites_matrix)[y0[x]*4*npops->value()+4*x+0] = (*matrix_pos)[j];
                        y0[x] += 1;
                        css_rest = 0;
                        continue;
                    }
                    else {
                        if(outgroup_presence->value()+force_outgroup->value() == 1) (*stats_sanc)[x*4+2] += 1;/*Sx1f2*/
                        if(outgroup_presence->value()+force_outgroup->value() == 0) (*stats_sanc)[x*4+0] += 1;/*Sx1*/
                        (*sites_matrix)[y2[x]*4*npops->value()+4*x+2] = (*matrix_pos)[j];
                        y2[x] += 1;
                        css_rest = 0;
                        continue;
                    }
                }
                if(polqa[x]==1 && polqb[x]==1 && polc==0) {
                    (*stats_sanc)[x*4+3] += 1;/*Ssh*/
                    (*sites_matrix)[y3[x]*4*npops->value()+4*x+3] = (*matrix_pos)[j];
                    y3[x] += 1;
                    css_rest = 0;
                    continue;
                }
                if(polqa[x]==0 && polqb[x]==0 && polc==0) {
                    if(outgroup_presence->value()+force_outgroup->value() == 1) {
                        if((npops->value() == 2 && (*matrix_pol)[j*sumnsam+initsa] != (*matrix_pol)[j*sumnsam+initso]) || ((*matrix_pol)[j*sumnsam+initsa] != (*matrix_pol)[j*sumnsam+initso] && (*matrix_pol)[j*sumnsam+initsb] == (*matrix_pol)[j*sumnsam+initso])) {
                            (*stats_sanc)[x*4+1]+= 1;/*Sf1*/
                            (*sites_matrix)[y1[x]*4*npops->value()+4*x+1] = (*matrix_pos)[j];
                            y1[x] += 1;
                            css_rest = 0;
                            continue;
                        }
                    }
                    if(outgroup_presence->value()+force_outgroup->value() == 0) {
                        if((*matrix_pol)[j*sumnsam+initsa] != (*matrix_pol)[j*sumnsam+initsb]) {
                            (*stats_sanc)[x*4+1]+= 1;/*Sf1*/
                            (*sites_matrix)[y1[x]*4*npops->value()+4*x+1] = (*matrix_pos)[j];
                            y1[x] += 1;
                            css_rest = 0;
                            continue;
                        }
                    }
                }
                if(polqa[x]== -1) {
                    /*no information for this population and position, continue*/
                    continue;
                }
                if(polqb[x] == -1) {
                    /*this is like 2 pops with no outgroup: Sx1,Ss,Sf[1 vs outg]: not considered because fixed variants can not be polarized. It is inconsistent with the rest of mutations with 3 pops.*/
                    continue;
                }
            }
            /*for the outgroup: it doesn't matter what is the group of populations(x), we chose pop <- npops->value()-2 if it is not -1*/
            npo=npops->value()-2;
            while(npo > 0 && (polqa[npo] == -1 || polqb[npo] == -1)) npo--;
            if(polc == 1) {
                if(npops->value() > 1) {
                    if(polqa[npo] == 0 && polqb[npo] == 0) {
                        if((npops->value() == 2) || (*matrix_pol)[j*sumnsam+initsb] == (*matrix_pol)[j*sumnsam+initsq1a[npo]]) {
                            (*stats_sanc)[(npops->value()-1)*4+0] += 1;/*Sxo*/
                            (*sites_matrix)[o0[0]*4*npops->value()+4*(npops->value()-1)+0] = (*matrix_pos)[j];
                            o0[0]++;
                            css_rest = 0;
                            continue;
                        }
                        else {
                           (*stats_sanc)[(npops->value()-1)*4+2] += 1; /*Sanco*/
                           (*sites_matrix)[o2[0]*4*npops->value()+4*(npops->value()-1)+2] = (*matrix_pos)[j];
                           o2[0]++;
                            css_rest = 0;
                            continue;
                        }
                    }
                    else {
                        if(polqa[npo] != -1 && polqb[npo] != -1) {
                            (*stats_sanc)[(npops->value()-1)*4+2] += 1; /*Sanco*/
                            (*sites_matrix)[o2[0]*4*npops->value()+4*(npops->value()-1)+2] = (*matrix_pos)[j];
                            o2[0]++;
                            css_rest = 0;
                            continue;
                        }
                        else {
                            if(polqa[npo] == 0 || polqb[npo] == 0) {
                                (*stats_sanc)[(npops->value()-1)*4+0] += 1;/*Sxo*/
                                (*sites_matrix)[o0[0]*4*npops->value()+4*(npops->value()-1)+0] = (*matrix_pos)[j];
                                o0[0]++;
                                css_rest = 0;
                                continue;
                            }
                            else {
                                (*stats_sanc)[(npops->value()-1)*4+2] += 1; /*Sanco*/
                                (*sites_matrix)[o2[0]*4*npops->value()+4*(npops->value()-1)+2] = (*matrix_pos)[j];
                                o2[0]++;
                                css_rest = 0;
                                continue;
                            }
                        }
                    }
                }
                else  { 
                    (*stats_sanc)[(npops->value()-1)*4+0] += 1;/*Sx1*/
                    (*sites_matrix)[y0[0]*4*npops->value()+4*(npops->value()-1)+0] = (*matrix_pos)[j];
                    y0[0] += 1;
                    css_rest = 0;
                    continue;
                }
            }
            if(npops->value() > 1) { 
                if(polqa[npo]==0 && polqb[npo]==0 && polc==0) {
                    if((npops->value() == 2 && (*matrix_pol)[j*sumnsam+initsq1a[npo]] != (*matrix_pol)[j*sumnsam+initso]) || ((*matrix_pol)[j*sumnsam+initsb] == (*matrix_pol)[j*sumnsam+initsq1a[npo]] &&  (*matrix_pol)[j*sumnsam+initsq1a[npo]] != (*matrix_pol)[j*sumnsam+initso])) {
                        (*stats_sanc)[(npops->value()-1)*4+1] += 1;/*Sfo*/
                        (*sites_matrix)[o1[0]*4*npops->value()+4*(npops->value()-1)+1] = (*matrix_pos)[j];
                        o1[0]++;
                        css_rest = 0;
                        continue;
                    }
                }
            }
            if(polc == -1) {
                /*this is like 2 pops with no outgroup: Sx,Ss,Sf[1 vs 2]: not considered because fixed variants can not be polarized. It is inconsistent with the rest of mutations with 3 pops.*/
                continue;
            }
            if(css_rest == 1) {
                (*stats_sanc)[(npops->value()-1)*4+3] += 1;/*Ssrest fixed between several pops: NOT COUNTED  BEFORE!*/
                (*sites_matrix)[o3[0]*4*npops->value()+4*(npops->value()-1)+3] = (*matrix_pos)[j];
                o3[0]++;
                css_rest = 0;
            }
        }
    }
    
    free(initsq1);
    free(initsq2);
    free(initsq1a);
    free(polqa);
    free(polqb);

    for(x=0;x<npops->value()-1;x++){
        (*sites_matrix)[y0[x]*4*npops->value()+4*x+0] = 0;
        (*sites_matrix)[y1[x]*4*npops->value()+4*x+1] = 0;
        (*sites_matrix)[y2[x]*4*npops->value()+4*x+2] = 0;
        (*sites_matrix)[y3[x]*4*npops->value()+4*x+3] = 0;
    }
    if(npops->value() >1) {
        (*sites_matrix)[o0[0]*4*npops->value()+4*(npops->value()-1)+0] = 0;
        (*sites_matrix)[o1[0]*4*npops->value()+4*(npops->value()-1)+1] = 0;
        (*sites_matrix)[o2[0]*4*npops->value()+4*(npops->value()-1)+2] = 0;
    }
    free(y0);
    free(y1);
    free(y2);
    free(y3);
    free(o0);
    free(o1);
    free(o2);
    free(o3);
}

void CCalcSxsfss::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
