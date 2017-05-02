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
 *  \brief     CCalcMismatch.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcMismatch.h"

#include <cmath>

#include "../util/CMatrixPol.h"


CCalcMismatch::CCalcMismatch()
: ICalculation(KeyString::CALC_MISMATCH,
               KeyString::CALC_MISMATCH_BRIEF_DESC,
               KeyString::CALC_MISMATCH_DESC,
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
    SET_INPUT_INFO(stats_thetaT,                                                // Variable
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
  
    SET_OUTPUT_INFO(stats_mdg1,                                                 // Variable
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
    SET_OUTPUT_INFO(stats_mdg2,                                                 // Variable
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
    SET_OUTPUT_INFO(stats_mdsd,                                                 // Variable
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
    SET_OUTPUT_INFO(stats_mdw,                                                  // Variable
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

CCalcMismatch::~CCalcMismatch() {
}

void CCalcMismatch::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(ploidy)
    DM_INPUT(nsam)
    DM_INPUT(npops)
    DM_INPUT(matrix_pol)
    DM_INPUT(stats_thetaT)
    DM_INPUT(length)
  DM_GET_OUTPUTS
    DM_OUTPUT(stats_mdg1)
    DM_OUTPUT(stats_mdg2)
    DM_OUTPUT(stats_mdsd)
    DM_OUTPUT(stats_mdw)
  DM_END
}

void CCalcMismatch::Calculate(bool dry_run) {
	/*
		Error: using missing values the weight (comb) is not correctly calculated. Do it for each position independently...
	*/
	int x,y;
	long int z,zz,ncomb;
	long int j;
	int pop1;
    double thetaT=0.0;
    double w,moment;
	double *freq1,*freq2,*freq3,*freq4,s,s2,g1,g2;
	long int sumnsam,maxnsam;
	int *initsq1,inits,max;
	
  CMatrixPol matrixPol;
  
	for(pop1=0;pop1<npops->value()-1;pop1++){
		(*stats_mdg1)[pop1] = NA_VALUE; //.
		(*stats_mdg2)[pop1] = NA_VALUE; //.
	}
    
    initsq1 = (int *)calloc(npops->value(),sizeof(int));
	sumnsam = 0;
	maxnsam = 0;
	
	for(x=0;x<npops->value();x++) {
		initsq1[x] = (int)sumnsam;
		sumnsam += (*nsam)[x];
		if(maxnsam < (*nsam)[x]) maxnsam = (*nsam)[x];
	}
	
	freq1 = (double *)calloc(maxnsam*(maxnsam-1)/2,sizeof(double));
	freq2 = (double *)calloc(maxnsam*(maxnsam-1)/2,sizeof(double));
	freq3 = (double *)calloc(maxnsam*(maxnsam-1)/2,sizeof(double));
	freq4 = (double *)calloc(maxnsam*(maxnsam-1)/2,sizeof(double));
	
	for(pop1=0;pop1<npops->value()-1;pop1++)
	{
		if(ploidy->value() == HAPLOID) 
			thetaT = (*stats_thetaT)[pop1];
		if(ploidy->value() == DIPLOID) {
			thetaT = 0.;
			w = 0.;
			inits = initsq1[pop1];
			max   = initsq1[pop1]+(*nsam)[pop1];
			for(x=inits;x<max-1;x+=2)  {
				for(y=x+1;y<max;y+=2)  {
					zz = 0;
					for(j=0;j<length->value();j++) {		
            //!20160504 GetData()
						if((matrixPol.ispolmis((*matrix_pol).GetData(),(int)sumnsam,j,length->value())) > 0)
							continue;
						else {
							if((*matrix_pol)[j*sumnsam+x] != '-' && (*matrix_pol)[j*sumnsam+y] != '-') {
								zz++;
								if((*matrix_pol)[j*sumnsam+x] != (*matrix_pol)[j*sumnsam+y]) {
									thetaT += 1;
								}
							}
						}
					}
					w+=(double)zz/(double)length->value();
				}
			}
			thetaT /= (double)w;
		}
		
		if(ploidy->value() == HAPLOID) {
			ncomb = (*nsam)[pop1]*((*nsam)[pop1]-1)/2;
			for(z=0;z<ncomb;z++)  {
				freq1[z] = 0.;
				freq2[z] = 0.;
				freq3[z] = 0.;
				freq4[z] = 0.;
			}
			
			z = 0;
			inits = initsq1[pop1];
			max   = initsq1[pop1]+(*nsam)[pop1];
			for(x=inits;x<max-1;x++)  {
				for(y=x+1;y<max;y++)  {
					for(j=0;j<length->value();j++) {		
            //!20160504 GetData()
						if((matrixPol.ispolmis((*matrix_pol).GetData(),(int)sumnsam,j,length->value())) > 0)
							continue;
						else {
							if((*matrix_pol)[j*sumnsam+x] != (*matrix_pol)[j*sumnsam+y] && (*matrix_pol)[j*sumnsam+x] != '-' && (*matrix_pol)[j*sumnsam+y] != '-') {
								if(ploidy->value() == HAPLOID) freq1[z] += 1;
							}
						}
					}
					moment = (freq1[z] - thetaT);
					freq2[z] = moment * moment;
					freq3[z] = moment * moment * moment;
					freq4[z] = moment * moment * moment * moment;
					(*stats_mdw)[pop1][z] = freq1[z]; /*mismatch distribution*/
					z++;
				}
			}
			s2 = g1 = g2 = 0.;				
			for(z=0;z<ncomb;z++)  {
				s2 += freq2[z];
				g1 += freq3[z];
				g2 += freq4[z];
			}
			s = sqrt(s2/((double)ncomb-1));
			(*stats_mdsd)[pop1] = s;
			if(s) {
				(*stats_mdg1)[pop1] = g1 * (double)ncomb/(((double)ncomb-2)*((double)ncomb-1)*s*s*s);
				(*stats_mdg2)[pop1] = g2 * ((double)ncomb-1) * ncomb /(((double)ncomb-3)*((double)ncomb-2)*((double)ncomb-1)*s*s*s*s)
										  - (3. * ((double)ncomb-1)*((double)ncomb-1))/(((double)ncomb-3)*((double)ncomb-2));
			}
			else {
				(*stats_mdg1)[pop1] = NA_VALUE; //.
				(*stats_mdg2)[pop1] = NA_VALUE; //.
			}
		}
		if(ploidy->value() == DIPLOID) {
			ncomb = ((*nsam)[pop1])*(((*nsam)[pop1])-1)/2;
			for(z=0;z<ncomb;z++)  {
				freq1[z] = 0.;
				freq2[z] = 0.;
				freq3[z] = 0.;
				freq4[z] = 0.;
			}
			
			z = 0;
			inits = initsq1[pop1];
			max   = initsq1[pop1]+(*nsam)[pop1];
			w = 0.;
			for(x=inits;x<max-1;x+=1)  {
				for(y=x+1;y<max;y+=1)  {
					if(x/2 == (double)x/2 && y==x+1) 
						continue;
					zz = 0;
					for(j=0;j<length->value();j++) {	
            //!20160504 GetData()
						if((matrixPol.ispolmis((*matrix_pol).GetData(),(int)sumnsam,j,length->value())) > 0)
							continue;
						else {
							if((*matrix_pol)[j*sumnsam+x] != '-' && (*matrix_pol)[j*sumnsam+y] != '-') {
								zz++;
								if((*matrix_pol)[j*sumnsam+x] != (*matrix_pol)[j*sumnsam+y]) {
									freq1[z] += 1;
								}
							}
						}
					}
					w+=(double)zz/(double)length->value();
					moment = (freq1[z] - thetaT);
					freq2[z] = moment * moment;
					freq3[z] = moment * moment * moment;
					freq4[z] = moment * moment * moment * moment;
					(*stats_mdw)[pop1][z] = freq1[z]; /*mismatch distribution*/
					z++;
				}
			}
			s2 = g1 = g2 = 0.;				
			for(z=0;z<ncomb;z++)  {
				s2 += freq2[z];
				g1 += freq3[z];
				g2 += freq4[z];
			}
			/*ncomb = (long int)w; CHANGE ncomb by w: IMPORTANT!! ???? <<<<---------------*/
			s = sqrt(s2/((double)w-1));
			(*stats_mdsd)[pop1] = s;
			if(s) {
				(*stats_mdg1)[pop1] = g1 * w/((w-2)*(w-1)*s*s*s);
				(*stats_mdg2)[pop1] = g2 * (w-1) * w /((w-3)*(w-2)*(w-1)*s*s*s*s) - (3. * (w-1)*(w-1))/((w-3)*(w-2));
			}
			else {
				(*stats_mdg1)[pop1] = NA_VALUE; //.
				(*stats_mdg2)[pop1] = NA_VALUE; //.
			}
		}
	}
	
	free(initsq1);
	free(freq1);
	free(freq2);
	free(freq3);
	free(freq4);
}

void CCalcMismatch::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
