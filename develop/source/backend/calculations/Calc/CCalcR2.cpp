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
 *  \brief     CCalcR2.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcR2.h"

#include <cmath>
#include <cstddef>

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"

#include <list>

CCalcR2::CCalcR2()
: ICalculation(KeyString::CALC_R2,
               KeyString::CALC_R2_BRIEF_DESC,
               KeyString::CALC_R2_DESC,
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
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcR2::~CCalcR2() {
}

void CCalcR2::Prepare(void) {
}

void CCalcR2::Calculate(bool dry_run) {
  DM_GET_INPUTS
    DM_INPUT(ploidy)
    DM_INPUT(vint_perpop_nsam)
    DM_INPUT(npops)
    DM_INPUT(matrix_pol)
    DM_INPUT(stats_S)
    DM_INPUT(stats_thetaT)
    DM_INPUT(length)
  DM_GET_OUTPUTS
    DM_OUTPUT(stats_R2)
  DM_END
  
  
  int *initsq1;
  long int *unic;
  int x,y,pop1,inits,max,sumnsam;
  int freq[4];
  long int j;

  
  /*init*/
  for( pop1=0;pop1<npops->value();pop1++ ) (*stats_R2)[pop1] = NA_VALUE;

  if(length->value()==0) return;  // return 1;
  
  initsq1 = (int *)calloc(npops->value(),sizeof(int));

  sumnsam = 0;
  for(x=0;x<npops->value();x++) {
          initsq1[x] = sumnsam;
          sumnsam += (*vint_perpop_nsam)[x];
  }

  unic = (long int *)calloc(sumnsam,sizeof(long int));
  inits = 0;
  max = sumnsam;

  for( pop1=0;pop1<npops->value();pop1++ )
  {
      if( (*vint_perpop_nsam)[pop1] > 1 && length->value() > 0)
      {
          for(j=0;j<length->value();j++)
          {
              inits   = initsq1[pop1];
              max     = initsq1[pop1]+(*vint_perpop_nsam)[pop1];
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
    if(ploidy->value() == HAPLOID) {
      (*stats_R2)[pop1] =
          R2Function( unic+initsq1[pop1],
            (*stats_thetaT)[pop1],
            (*vint_perpop_nsam)[pop1],
            (int)(*stats_S)[pop1] );
    }
    if(ploidy->value() == DIPLOID) {
      for(y=inits;y<max;y+=2) unic[y] += unic[y+1];
      (*stats_R2)[pop1] =
          R2Function( unic+initsq1[pop1],
           2.0*(*stats_thetaT)[pop1],
           (*vint_perpop_nsam)[pop1]/2,
           (int)(*stats_S)[pop1] );
    }
      }
  else {
    (*stats_R2)[pop1] = NA_VALUE;
  }
  }

  free(initsq1);
  free(unic);

  //return 1;
}

void CCalcR2::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

double CCalcR2::R2Function(long int *unic,double pi,int sample_size,long int S)
{
    double sm2 = 0.0;
    int i;

    if(S == 0 || sample_size == 0) return(NA_VALUE);
    for( i=0;i<sample_size;i++ ) {
        sm2 += ((double)unic[i] - pi/2.0) * ((double)unic[i] - pi/2.0);
    }

    sm2 = sqrt(sm2/((double)sample_size))/(double)S;

    if( fabs(sm2) < 1.0E-15 )
    sm2 = 0.0;

    return (double)sm2;
}
