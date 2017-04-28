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
 *  \brief     CCalcR2p.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcR2p.h"

#include <cmath>
#include <cstddef>
#include <cstdlib>

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"


CCalcR2p::CCalcR2p()
: ICalculation(KeyString::CALC_R2P,
               KeyString::CALC_R2P_BRIEF_DESC,
               KeyString::CALC_R2P_DESC,
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
    SET_INPUT_INFO(sum_sam,                                                     // Variable
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
    SET_INPUT_INFO(stats_S,                                                     // Variable
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
    SET_INPUT_INFO(r2i_ploidies,                                                // Variable
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
  
    SET_OUTPUT_INFO(stats_R2,                                                   // Variable
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
    SET_OUTPUT_INFO(stats_R2p,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // RequiredSET_OUTPUT_INFO(stats_R2p)
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcR2p::~CCalcR2p() {
}

void CCalcR2p::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(ploidy)
    DM_INPUT(vint_perpop_nsam)
    DM_INPUT(npops)
    DM_INPUT(matrix_pol)
    DM_INPUT(sum_sam)
    DM_INPUT(stats_S)
    DM_INPUT(stats_thetaT)
    DM_INPUT(r2i_ploidies)
    DM_INPUT(length)  // length_seg
  DM_GET_OUTPUTS
    DM_OUTPUT(stats_R2)
    DM_OUTPUT(stats_R2p)
  DM_END
}

void CCalcR2p::Calculate(bool dry_run) {

  /*in case r2i_ploidies is undefined*/
  if ((*r2i_ploidies).GetData() == 0) {
    r2i_ploidies->ReserveMemory(2, 0);

    (*r2i_ploidies)[0] = 1;
    
    if(ploidy->value() == HAPLOID) {
      (*r2i_ploidies)[1] = 1;
    }
    
    if(ploidy->value() == DIPLOID) {
      (*r2i_ploidies)[1] = 2;
    }
  }

  stats_R2p->ReserveMemory((*r2i_ploidies)[0], npops->value(), 0.0);


    int *initsq1;
    long int *unic;
    int x,y,pop1,inits,max,sumnsam;
    int freq[4];
    long int j;
    double efflength;

    /*init*/
    for( pop1=0;pop1<npops->value();pop1++ ) {
        (*stats_R2)[pop1] = NA_VALUE;
        for(x=0;x<(*r2i_ploidies)[0];x++) {
            (*stats_R2p)[x][pop1] = NA_VALUE;
        }
    }
    if(length->value()==0) return;  // return 1;
    
    //initsq1 = (int *)calloc(npops->value(),sizeof(int));
    initsq1 = new int[npops->value()](); // () to initialize to 0 like calloc did it

    sumnsam = 0;
    for(x=0;x<npops->value();x++) {
    initsq1[x] = sumnsam;
    sumnsam += (*vint_perpop_nsam)[x];
    }

    //unic = (long int *)calloc(sumnsam,sizeof(long int));
    unic = new long int[sumnsam](); // () to initialize to 0 like calloc did it

  inits = 0;
  max = sumnsam;

    for( pop1=0;pop1<npops->value();pop1++ )
    {
        if( (*vint_perpop_nsam)[pop1] > 1 && length->value() > 0)
        {
      inits   = initsq1[pop1];
      max     = initsq1[pop1]+(*vint_perpop_nsam)[pop1];

      for(j=0;j<length->value();j++)
            {
                freq[0] = freq[1] = freq[2] = freq[3] = 0;
                for( y=inits;y<max;y++)
                {
                    if((*matrix_pol)[j*sumnsam+y] == '0') {freq[1] += 1;freq[0] += 1;}
                    if((*matrix_pol)[j*sumnsam+y] == '1') {freq[2] += 1;freq[0] += 1;}
                    if((*matrix_pol)[j*sumnsam+y] == '-') {freq[3] += 1;}
                }
                if(freq[0])
                {
                    if(freq[1]==1)
                    {
                        /**< Revisar este trozo de codigo */
                        for(y=inits;y<max;y++) if((*matrix_pol)[j*sumnsam+y] == '0') break;
                        unic[y] += 1;
                    }
                    else {
            if(freq[2]==1) {
              for(y=inits;y<max;y++) if((*matrix_pol)[j*sumnsam+y] == '1') break;
              unic[y] += 1;
            }
                    }
                }
            }

      efflength = 0.;
      for( y=inits;y<max;y++)
        efflength += (*sum_sam)[y];

      for(x=0;x<(*r2i_ploidies)[0];x++) {
        (*stats_R2p)[x][pop1] = R2pFunction(unic+initsq1[pop1],
                        (*stats_thetaT)[pop1],
                        floor((*vint_perpop_nsam)[pop1]/(double)(*r2i_ploidies)[x+1]),
                        (int)(*stats_S)[pop1],(*sum_sam)+initsq1[pop1],efflength,(*r2i_ploidies)[x+1]);
        /*
        if(x==1 && ploidy[0] == '1') statistics[0].R2(*)[pop1] = statistics[0].R2(*p)[x][pop1];
        if(x==2 && ploidy[0] == '2') statistics[0].R2(*)[pop1] = statistics[0].R2(*p)[x][pop1];
        */
      }
        }
    else {
      (*stats_R2)[pop1] = NA_VALUE;
      /*
      if(x==1 && ploidy[0] == '1') statistics[0].R2(*)[pop1] = NA_VALUE;
      if(x==2 && ploidy[0] == '2') statistics[0].R2(*)[pop1] = NA_VALUE;
      */
    }
    }

//    free(initsq1);
//    free(unic);

    delete[] initsq1;
    delete[] unic;

    //return 1;
}

void CCalcR2p::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

double CCalcR2p::R2pFunction(long int *unic,double pi,int sample_size,long int S, double *efflength_sam, double efflength, int the_ploidy)
{
    double sm2 = 0.0;
    int i,j;
    long int unicp;
  double effposi;

    if(S == 0 || sample_size == 0) return(NA_VALUE);
    for( i=0;i<sample_size*the_ploidy;i+=the_ploidy ) {
    unicp=0;
    effposi=0.0;
    for(j=i;j<i+the_ploidy;j++) {
      unicp += unic[j];
      effposi += (double)efflength_sam[j];
        }

		sm2 += ((double)unicp - effposi/((double)efflength)
            * pi/2.0*(double)the_ploidy) *
			   ((double)unicp - effposi/((double)efflength) * pi/2.0*(double)the_ploidy);
    }
    sm2 = sqrt(sm2) / (double)S;

    if( fabs(sm2) < 1.0E-15 )
    sm2 = 0.0;

    return (double)sm2;
}
