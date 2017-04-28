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
 *  \brief     CCalcHwhafsth.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcHwhafsth.h"

#include <cmath>
#include <cstring>

#include "../../language/CStringTable.h"

#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Matrix.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataDoubleVector.h"
#include "../../data_manager/CDataManager.h"
#include "../../data_manager/common/CDataAccess.h"

CCalcHwhafsth::CCalcHwhafsth()
: ICalculation(KeyString::CALC_HWHAFSTH,
               KeyString::CALC_HWHAFSTH_BRIEF_DESC,
               KeyString::CALC_HWHAFSTH_DESC,
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
    SET_OUTPUT_INFO(stats_nhpop,                                                // Variable
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
    SET_OUTPUT_INFO(stats_hapw,                                                 // Variable
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
    SET_OUTPUT_INFO(stats_hapa,                                                 // Variable
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
    SET_OUTPUT_INFO(stats_hapT,                                                 // Variable
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
    SET_OUTPUT_INFO(stats_fsth,                                                 // Variable
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
    SET_OUTPUT_INFO(stats_fsth1all,                                             // Variable
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
    SET_OUTPUT_INFO(stats_freqh,                                                // Variable
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
    SET_OUTPUT_INFO(stats_nh,                                                   // Variable
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
    SET_OUTPUT_INFO(stats_Gst,                                                  // Variable
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
    SET_OUTPUT_INFO(stats_fsthALL,                                              // Variable
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
    SET_OUTPUT_INFO(stats_GstALL,                                               // Variable
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

CCalcHwhafsth::~CCalcHwhafsth() {
}

void CCalcHwhafsth::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(vint_perpop_nsam)
    DM_INPUT(npops)
    DM_INPUT(matrix_pol)
    DM_INPUT(length)
  DM_GET_OUTPUTS
    DM_OUTPUT(stats_nhpop)
    DM_OUTPUT(stats_hapw)
    DM_OUTPUT(stats_hapa)
    DM_OUTPUT(stats_hapT)
    DM_OUTPUT(stats_fsth)
    DM_OUTPUT(stats_fsth1all)
    DM_OUTPUT(stats_freqh)
    DM_OUTPUT(stats_nh)
    DM_OUTPUT(stats_Gst)
    DM_OUTPUT(stats_fsthALL)
    DM_OUTPUT(stats_GstALL)
  DM_END
}

void CCalcHwhafsth::Calculate(bool dry_run) {
  /*
    stats_ -> stats_
  */

	int x,y,z,yy,w;
	long int j,k;
	int flag;
	int pop1,pop2;
	int sumnsam,*initsq1,inits,max;	
  double *hapa1all,*hapw1all,*hapT1all,hapw,spiw,spiwn,spia;
	char *matrix_hap;
	int nn,np;
	int **sfreqh;
	char **valh;
	double hs,ht,xi,nm,Js,Hs,Dm,Dkl,Ht;
	int nh,nhp;	
	double shapw,shapa;
	int ncw,nca;
	
    /*init*/
    z = 0;
    stats_fsthALL->set_value(NA_VALUE);
    stats_GstALL->set_value(NA_VALUE);
    for(pop1=0;pop1<npops->value();pop1++) {
        (*stats_nhpop)[pop1] = 0;
        (*stats_hapw)[pop1] = 0.;
        (*stats_fsth)[pop1] = NA_VALUE;
        (*stats_fsth1all)[pop1] = NA_VALUE;
        for(pop2=pop1+1;pop2<npops->value();pop2++) {
            (*stats_hapa)[z] = 0.;
            (*stats_hapT)[z] = 0.;
            (*stats_Gst)[z] = NA_VALUE;
            z++;
        }
    }
    
    if(length->value()==0) return;
    
    
	initsq1  = (int *)calloc(npops->value(),sizeof(int));

	hapa1all = (double *)calloc(npops->value(),sizeof(double));
	hapT1all = (double *)calloc(npops->value(),sizeof(double));
	hapw1all = (double *)calloc(npops->value(),sizeof(double));

	sfreqh   = (int **)calloc(npops->value(),sizeof(int *));
	
	sumnsam = 0;
	for(x=0;x<npops->value();x++) {
		initsq1[x] = sumnsam;
		sumnsam += (*vint_perpop_nsam)[x];  //!20160509 nsam
		(*stats_nhpop)[x] = 0;
		(*stats_hapw)[x] = 0.;
	}	
	
	z=0;
	for(pop1=0;pop1<npops->value()-2;pop1++) {
		for(pop2=pop1+1;pop2<npops->value()-1;pop2++) {
			(*stats_hapa)[z] = 0.;
			(*stats_hapT)[z] = 0.;
			z++;
		}
	}
	
	for(x=0;x<npops->value();x++)
		sfreqh[x] = (int *)calloc(sumnsam,sizeof(int));
	valh = (char **)calloc(sumnsam,sizeof(char *)); /*pointer to each diff haplotype*/	

	matrix_hap = (char *)calloc(sumnsam*length->value(),sizeof(char));

	/*NOTE THE HAPLOTYPE VALUES GOES FROM 0 to npops->value()-1 BUT FREQUENCY GOES FROM 0 to npops->value()!!!!!!*/
	/*obtain haplotypes in matrix_hap*/
	k = 0;
	for(pop1=0;pop1<npops->value()-1;pop1++) {
		k = 0;
		for(j=0;j<length->value();j++) {
			inits = initsq1[pop1];
			max   = initsq1[pop1]+(*vint_perpop_nsam)[pop1];
			flag = 0;
			for(y=inits;y<max;y++) {
				if((*matrix_pol)[j*sumnsam+y] != '-') {
					matrix_hap[y*length->value()+k] = (*matrix_pol)[j*sumnsam+y];
				}
				else {
					flag = 1;
					for(yy=inits;yy<=y;yy++) matrix_hap[yy*length->value()+k] = (char)0;
					break;
				}
			}
			if(flag == 0) k++;
		}
	}
	
	/*calculate hapw*/
	nh = 0;
	for(pop1=0;pop1<npops->value()-1;pop1++) {
		(*stats_hapw)[pop1] = 0.;
		inits = initsq1[pop1];
		max   = initsq1[pop1]+(*vint_perpop_nsam)[pop1];
		for(y=inits;y<max/*-1*/;y++) {
			/*calculate calculate freq hap*/
			if(y==inits && pop1 == 0) {
				sfreqh[pop1][nh] += 1;
				if(sfreqh[pop1][nh] == 1) (*stats_nhpop)[pop1] += 1;
				valh[nh] = matrix_hap+y*length->value();
				nh++;
			}
			else {
				w = 0;
				for(z=nh-1;z>=0;z--) {
					if((memcmp(matrix_hap+y*length->value(),valh[z],k) == 0)) {
						sfreqh[pop1][z] += 1;
						if(sfreqh[pop1][z] == 1) (*stats_nhpop)[pop1] += 1;
						w = 1;
						break;
					}
				}
				if(w==0) {
					sfreqh[pop1][nh] += 1;
					if(sfreqh[pop1][nh] == 1) (*stats_nhpop)[pop1] += 1;
					valh[nh] = matrix_hap+y*length->value();
					nh++;
				}
			}
			/*end calculation freq hap*/
			for(z=y+1;z<max;z++) {
				if(memcmp(matrix_hap+y*length->value(),matrix_hap+z*length->value(),k) != 0) {
					(*stats_hapw)[pop1] += 1;
				}
			}
			for(z=0;z<nh;z++)
				(*stats_freqh)[pop1][z] = sfreqh[pop1][z];
		}
		(*stats_hapw)[pop1] /= ((*vint_perpop_nsam)[pop1]*((*vint_perpop_nsam)[pop1]-1.0)/2.0);		
	}
	stats_nh->set_value(nh);
	
	/*calculate hapa and hapT*/
	z=0;
	for(pop1=0;pop1<npops->value()-2;pop1++) {
		for(pop2=pop1+1;pop2<npops->value()-1;pop2++) {
			k = 0;
			for(j=0;j<length->value();j++) {
				inits = initsq1[pop1];
				max   = initsq1[pop1]+(*vint_perpop_nsam)[pop1];
				flag = 0;
				for(y=inits;y<max;y++) {
					if((*matrix_pol)[j*sumnsam+y] != '-') {
						matrix_hap[y*length->value()+k] = (*matrix_pol)[j*sumnsam+y];
					}
					else {
						flag = 1;
						for(yy=inits;yy<=y;yy++) matrix_hap[yy*length->value()+k] = (char)0;
						break;
					}
				}
				if(flag == 1) continue;
				inits = initsq1[pop2];
				max   = initsq1[pop2]+(*vint_perpop_nsam)[pop2];
				for(y=inits;y<max;y++) {
					if((*matrix_pol)[j*sumnsam+y] != '-') {
						matrix_hap[y*length->value()+k] = (*matrix_pol)[j*sumnsam+y];
					}
					else {
						flag = 1;
						for(yy=inits;yy<=y;yy++) matrix_hap[yy*length->value()+k] = (char)0;
						break;
					}
				}
				if(flag == 0) k++;
			}
			/*calculate hapa*/
			(*stats_hapa)[z] = 0.;
			for(y=initsq1[pop1];y<initsq1[pop1]+(*vint_perpop_nsam)[pop1];y++) {
				for(x=initsq1[pop2];x<initsq1[pop2]+(*vint_perpop_nsam)[pop2];x++) {
					if(memcmp(matrix_hap+y*length->value(),matrix_hap+x*length->value(),k) != 0) {
						(*stats_hapa)[z] += 1;
						(*stats_hapT)[z] += 1;
					}
				}
			}
			(*stats_hapa)[z] /= (double)((*vint_perpop_nsam)[pop1]*(*vint_perpop_nsam)[pop2]);
			
			/*calculate hapT*/
			for(y=initsq1[pop1];y<initsq1[pop1]+(*vint_perpop_nsam)[pop1]-1;y++) {
				for(x=y+1;x<initsq1[pop1]+(*vint_perpop_nsam)[pop1];x++) {
					if(memcmp(matrix_hap+x*length->value(),matrix_hap+y*length->value(),k) != 0) {
						(*stats_hapT)[z] += 1;
					}
					
				}
			}
			for(y=initsq1[pop2];y<initsq1[pop2]+(*vint_perpop_nsam)[pop2]-1;y++) {
				for(x=y+1;x<initsq1[pop2]+(*vint_perpop_nsam)[pop2];x++) {
					if(memcmp(matrix_hap+x*length->value(),matrix_hap+y*length->value(),k) != 0) {
						(*stats_hapT)[z] += 1;
					}
					
				}
			}
			(*stats_hapT)[z] /= (double)((*vint_perpop_nsam)[pop1]+(*vint_perpop_nsam)[pop2])*((*vint_perpop_nsam)[pop1]+(*vint_perpop_nsam)[pop2]-1.0)/2.0;
			z++;
		}
	}
	
	/*calculate fsth1all*/
	/**/
	if(npops->value()==2) {
		nn = sumnsam;
		np = 0;
	}
	else {
		nn = sumnsam-(*vint_perpop_nsam)[npops->value()-1];
		np = 1;
	}/**//**/
	if(npops->value() > 2) {
		nn = sumnsam-(*vint_perpop_nsam)[npops->value()-1];
		np = 1;	
		k = 0;
		for(j=0;j<length->value();j++) {
			flag = 0;
			for(y=0;y<nn;y++) {
				if((*matrix_pol)[j*sumnsam+y] != '-') {
					matrix_hap[y*length->value()+k] = (*matrix_pol)[j*sumnsam+y];
				}
				else {
					flag = 1;
					for(yy=0;yy<=y;yy++) matrix_hap[yy*length->value()+k] = (char)0;
					break;
				}
			}
			if(flag == 0) k++;
		}
		for(pop1=0;pop1<npops->value()-np;pop1++) {
			hapw1all[pop1] = 0.;
			inits = initsq1[pop1];
			max   = initsq1[pop1]+(*vint_perpop_nsam)[pop1];
			for(y=inits;y<max-1;y++) {
				for(z=y+1;z<max;z++) {
					if(memcmp(matrix_hap+y*length->value(),matrix_hap+z*length->value(),k) != 0) {
						hapw1all[pop1] += 1;
					}
				}
			}
			if((*vint_perpop_nsam)[pop1]>1) hapw1all[pop1] /= ((*vint_perpop_nsam)[pop1]*((*vint_perpop_nsam)[pop1]-1.0)/2.0);
			else hapw1all[pop1] = 0.;
		}
		
		for(pop1=0;pop1<npops->value()-np;pop1++) {
			hapa1all[pop1] = 0.;
			hapT1all[pop1] = 0.;
		}

		for(pop1=0;pop1<npops->value()-1;pop1++) {				
			for(pop2=pop1+1;pop2<npops->value()-np;pop2++) {
				if((*vint_perpop_nsam)[pop1] > 1 && (*vint_perpop_nsam)[pop2] > 1) {
					for(y=initsq1[pop1];y<initsq1[pop1]+(*vint_perpop_nsam)[pop1];y++) {
						for(x=initsq1[pop2];x<initsq1[pop2]+(*vint_perpop_nsam)[pop2];x++) {
							if(memcmp(matrix_hap+y*length->value(),matrix_hap+x*length->value(),k) != 0) {
								hapa1all[pop1] += 1.0/(double)((*vint_perpop_nsam)[pop1]*(*vint_perpop_nsam)[pop2]);
								hapa1all[pop2] += 1.0/(double)((*vint_perpop_nsam)[pop1]*(*vint_perpop_nsam)[pop2]);
								hapT1all[pop1] += 1.0;
								hapT1all[pop2] += 1.0;
							}
						}
					}
				}
				if((*vint_perpop_nsam)[pop1] > 1) {
					for(y=initsq1[pop1];y<initsq1[pop1]+(*vint_perpop_nsam)[pop1]-1;y++) {
						for(x=y+1;x<initsq1[pop1]+(*vint_perpop_nsam)[pop1];x++) {
							if(memcmp(matrix_hap+y*length->value(),matrix_hap+x*length->value(),k) != 0) {
								hapT1all[pop1] += 1.0;
							}
						}
					}
				}
				if((*vint_perpop_nsam)[pop2] > 1) {
					for(y=initsq1[pop2];y<initsq1[pop2]+(*vint_perpop_nsam)[pop2]-1;y++) {
						for(x=y+1;x<initsq1[pop2]+(*vint_perpop_nsam)[pop2];x++) {
							if(memcmp(matrix_hap+y*length->value(),matrix_hap+x*length->value(),k) != 0) {
								hapT1all[pop2] += 1.0;
							}
						}
					}
				}
			}
		}
	}
	/**/
	/*calculate fsth*/
	z = 0;
	for(pop1=0;pop1<npops->value()-2;pop1++) {
		for(pop2=pop1+1;pop2<npops->value()-1;pop2++) {
      if((*stats_hapa)[z] && (*vint_perpop_nsam)[pop1] > 1 && (*vint_perpop_nsam)[pop2] > 1)
				(*stats_fsth)[z] = 1.0 - (((*stats_hapw)[pop1] + (*stats_hapw)[pop2])/2.0)/(*stats_hapa)[z];
			else (*stats_fsth)[z] = NA_VALUE;
			z++;
		}
	}
	/*calculate Gst (Nei 1973) for pair-pair comparisons*/
	z = 0;
	for(pop1=0;pop1<npops->value()-2;pop1++) {
		for(pop2=pop1+1;pop2<npops->value()-1;pop2++) {
			if((*vint_perpop_nsam)[pop1] > 1 && (*vint_perpop_nsam)[pop2] > 1) {
				Js = Dm = Dkl = 0;
				for(y=0;y<sumnsam;y++) {
					Js += (double)(sfreqh[pop1][y])/(double)(*vint_perpop_nsam)[pop1]*(double)(sfreqh[pop1][y])/(double)(*vint_perpop_nsam)[pop1];
					Js += (double)(sfreqh[pop2][y])/(double)(*vint_perpop_nsam)[pop2]*(double)(sfreqh[pop2][y])/(double)(*vint_perpop_nsam)[pop2];
					Dkl += (double)pow(((double)(sfreqh[pop1][y])/(double)(*vint_perpop_nsam)[pop1] - (double)(sfreqh[pop2][y])/(double)(*vint_perpop_nsam)[pop2]),2.0)/2.0;
				}
				Js /= 2.0;
				Hs = 1.0 - Js;
				Dm += Dkl/2.0;
				Ht = Hs + Dm;
				(*stats_Gst)[z] = Dm / Ht;
				/**/
				nm = 2.0/(1.0/(double)(*vint_perpop_nsam)[pop1] + 1.0/(double)(*vint_perpop_nsam)[pop2]);
				hs = ht = 0.;
				for(y=0;y<sumnsam;y++) {
					hs += (double)(sfreqh[pop1][y])/(double)(*vint_perpop_nsam)[pop1]*(double)(sfreqh[pop1][y])/(double)(*vint_perpop_nsam)[pop1];
					hs += (double)(sfreqh[pop2][y])/(double)(*vint_perpop_nsam)[pop2]*(double)(sfreqh[pop2][y])/(double)(*vint_perpop_nsam)[pop2];
					xi  = (double)(sfreqh[pop1][y])/(double)(*vint_perpop_nsam)[pop1]+(double)(sfreqh[pop2][y])/(double)(*vint_perpop_nsam)[pop2];
					xi /= 2.0;
					ht += xi*xi;
				}
				hs /= 2.0;
				hs = 1.0 - hs;
				hs = nm*hs/(nm - 1.0);
				ht = 1.0 - ht;
				ht = ht + hs/(nm*2.0);
				(*stats_Gst)[z] = 1.0 - hs/ht;
				/**/
			}
			else (*stats_Gst)[z] = NA_VALUE;
			z++;
		}
	}
	
	if(npops->value() > 2) {
		z = 0;
		spiw = spiwn = spia = 0.;
		ncw = 0;
		for(pop1=0;pop1<npops->value()-1;pop1++) {
			if((*vint_perpop_nsam)[pop1] > 1) {
				spiwn += (*stats_hapw)[pop1];
				spiw  += (*stats_hapw)[pop1] * (*vint_perpop_nsam)[pop1] * ((*vint_perpop_nsam)[pop1]-1.0) / 2.0;
				ncw += 1;
			}
			for(pop2=pop1+1;pop2<npops->value()-1;pop2++) {
				if((*vint_perpop_nsam)[pop1] + (*vint_perpop_nsam)[pop2] > 1) {
					spia += (*stats_hapa)[z] * (*vint_perpop_nsam)[pop1] * (*vint_perpop_nsam)[pop2];
				}
				z++;
			}
		}
		for(pop1=0;pop1<npops->value()-1;pop1++) {
			if((*vint_perpop_nsam)[pop1] > 1 && (spiw+spia) > 0.)
				(*stats_fsth1all)[pop1] = 1.0 - ((*stats_hapw)[pop1]/((spiw+spia)/((sumnsam-(*vint_perpop_nsam)[npops->value()-1])*(sumnsam-(*vint_perpop_nsam)[npops->value()-1]-1.0)/2.0)));
			else (*stats_fsth1all)[pop1] = NA_VALUE;
		}
		/*calculate fstALL*/
    /*
		if((spiw+spia) > 0.)
			stats_fsthALL->set_value(1.0 - ((spiwn/(double)ncw)/((spiw+spia)/((sumnsam-(*vint_perpop_nsam)[npops->value()-1])*(sumnsam-(*vint_perpop_nsam)[npops->value()-1]-1.0)/2.0))));
		else stats_fsthALL->set_value(NA_VALUE);
     */
		
		/**/
		for(pop1=0;pop1<npops->value()-1;pop1++) {
			hapw = 0.;
			ncw = 0;
			for(pop2=0;pop2<npops->value()-1;pop2++) {
				if(pop2 != pop1 && (*vint_perpop_nsam)[pop2] > 1) {
					hapw += hapw1all[pop2];
					ncw += 1;
				}
			}
			hapw /= (double)ncw;
			nca = ncw;
			if(hapa1all[pop1] && (*vint_perpop_nsam)[pop1] > 1 && ncw > 0)
        (*stats_fsth1all)[pop1] = 1.0 - ((/*hapw1all[pop1] + ?*/hapw)/2.0)/(hapa1all[pop1]/(double)nca);
			else (*stats_fsth1all)[pop1] = NA_VALUE;
		}		
		/**/
		/*calculate fsthALL*/
		/**/
		shapw = shapa = 0.;
		ncw = nca = 0;
		
		z = 0;
		for(pop1=0;pop1<npops->value()-1;pop1++) {
			if((*vint_perpop_nsam)[pop1] > 1) {
				shapw += (*stats_hapw)[pop1];
				ncw += 1;
			}
			for(pop2=pop1+1;pop2<npops->value();pop2++) {
				if((*vint_perpop_nsam)[pop1] > 1 && (*vint_perpop_nsam)[pop2] > 1 && pop2 < npops->value()-1) {
					shapa += (*stats_hapa)[z];
					nca += 1;
				}
				z++;
			}
		}
		if(shapa) stats_fsthALL->set_value(1.0 - (shapw/(double)ncw)/(shapa/(double)nca));
		else stats_fsthALL->set_value(NA_VALUE);
		/**/
		/*number of pops with nsam>1 nhp*/
		nhp = 0;
		for(pop1=0;pop1<npops->value()-1;pop1++) {
			if((*vint_perpop_nsam)[pop1]>1) nhp++;
		}
		
		/*calculate GstALL (G'st = Dm/H't)*/
		Js = 0.;
		for(pop1=0;pop1<npops->value()-1;pop1++) {
			if((*vint_perpop_nsam)[pop1] > 1) {
				for(z=0;z<sumnsam;z++) {
					Js += (double)(sfreqh[pop1][z])/(double)(*vint_perpop_nsam)[pop1]*(double)(sfreqh[pop1][z])/(double)(*vint_perpop_nsam)[pop1];
				}
			}
		}
		Js /= (double)nhp;
		Hs = 1.0 - Js;

		Dm = 0.;
		for(pop1=0;pop1<npops->value()-2;pop1++) {
			if((*vint_perpop_nsam)[pop1] > 1) {
				for(pop2=0;pop2<npops->value()-1;pop2++) {
					if((*vint_perpop_nsam)[pop2] > 1 && pop1 != pop2) {
						Dkl = 0.;
						for(z=0;z<sumnsam;z++) {
							Dkl += (double)pow(((double)(sfreqh[pop1][z])/(double)(*vint_perpop_nsam)[pop1] - (double)(sfreqh[pop2][z])/(double)(*vint_perpop_nsam)[pop2]),2.0)/2.0;
						}
						Dm += Dkl;
					}
				}
			}
		}
		Dm /= (double)(nhp*(nhp-1));
		Ht = Hs + Dm;
		stats_GstALL->set_value(Dm / Ht);
		
		/**/
		nm = 0.;
		for(pop1=0;pop1<npops->value()-1;pop1++) {
			if((*vint_perpop_nsam)[pop1] > 1) {
				nm += 1.0/(double)((*vint_perpop_nsam)[pop1]);
			}
		}
		nm = (double)nhp/nm;		

		hs = 0.;
		for(pop1=0;pop1<npops->value()-1;pop1++) {
			if((*vint_perpop_nsam)[pop1] > 1) {
				for(z=0;z<sumnsam;z++) {
					hs += (double)(sfreqh[pop1][z])/(double)(*vint_perpop_nsam)[pop1]*(double)(sfreqh[pop1][z])/(double)(*vint_perpop_nsam)[pop1];
				}
			}
		}
		hs /= (double)nhp;
		hs = 1.0 - hs;
		hs = nm*hs/(nm - 1.0);

		ht = 0.;
		for(y=0;y<sumnsam;y++) {
			xi = 0.;
			for(pop1=0;pop1<npops->value()-1;pop1++) {
				if((*vint_perpop_nsam)[pop1] > 1) {
					xi += (double)(sfreqh[pop1][y])/(double)(*vint_perpop_nsam)[pop1];
				}
			}
			xi /= (double)nhp;
			ht += xi*xi;
		}
		ht = 1.0 - ht;
		ht = ht + hs/(nm*(double)nhp);

		stats_GstALL->set_value(1.0 - hs/ht);
		/**/
		
	
	}	
	
	for(x=0;x<npops->value();x++)
		free(sfreqh[x]);
	free(sfreqh);
	free(valh);
	free(initsq1);
	/**/
	free(hapa1all);
	free(hapT1all);
	free(hapw1all);
	/**/
	free(matrix_hap);
}

void CCalcHwhafsth::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
