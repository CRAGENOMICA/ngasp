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
 *  \brief     CCalcPermute.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 16, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcPermute.h"

#include <cmath>

#include "../CAllCalculations.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataDouble.h"

#include "../../commands/CAllCommands.h"

CCalcPermute::CCalcPermute()
: ICalculation(KeyString::CALC_PERMUTE,
               KeyString::CALC_PERMUTE_BRIEF_DESC,
               KeyString::CALC_PERMUTE_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(int_total_nsam,                                              // Variable
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
    SET_INPUT_INFO(nsam2,                                                       // Variable
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
    SET_INPUT_INFO(psam2,                                                       // Variable
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
    SET_OUTPUT_INFO(matrix_perm,                                                // Variable
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

  /// ==========================================================================
  /// RANDOMIZE CALCULATION
  /// ==========================================================================
  calc_randomize_ = NULL;
}

CCalcPermute::~CCalcPermute() {
}

void CCalcPermute::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(int_total_nsam)
    DM_INPUT(matrix_pol)
    DM_INPUT(nsam2)
    DM_INPUT(psam2)
    DM_INPUT(length)
  DM_GET_OUTPUTS
    DM_OUTPUT(matrix_perm)
  DM_END
}

void CCalcPermute::Calculate(bool dry_run) {
  //!20150505 replaced (a,b,c) by (a*b,c)
  //!20160509 matrix_perm->ReserveMemory(int_total_nsam->value() * length->value(), STR(DEFAULT_CHAR)[0]);


  /*matrix_pol->reg_length_ is the number of variants in (*matrix_pol)
   int_total_nsam->value() is the number of samples
   (*matrix_pol) is a vector with data: (matrix_pol->reg_length_ x int_total_nsam->value())
   matrix_perm is the new vector with the data (samples permuted)
   psam2 and nsam2 are included to chose 2 populations in order to do Fst
  */
  /*nsam2 is the samplesize of each of the 2 pops. psam2 is the position (cummulative value from int_total_nsam->value()) of each of the 2 pops.
   ex: pop1=10 pop2 =15. nsam2[0]=10 nsam2[1]=15 psam2[0]=0 psam2[1]=10.*/
  // double ran1(void);

  int *count;
  int sumnsam2;
  int x,y,c;
  long int j;

  count = (int *)calloc(int_total_nsam->value(),sizeof(int));

  /*samples not considered are 0, considered are 1 in count vector*/
  for(y=0;y<int_total_nsam->value();y++) count[y] = 0;
  for(x=0;x<2;x++) {
    for(y=(*psam2)[x];y<(*psam2)[x]+(*nsam2)[x];y++) {
      count[y] = 1;
    }
  }

  /*permute*/
  sumnsam2 = (*nsam2)[0]+(*nsam2)[1];
  while(sumnsam2) {
    c = (int)floor(ran1()*(double)sumnsam2);
    for(y=0;y<int_total_nsam->value();y++) {
      if(count[y] == 1) c--;
      if(c<0) break;
    }
    for(j=0;j<length->value();j++) {
      /*strncpy(matrix_perm+x*int_total_nsam->value()+((nsam2[0]+nsam2[1])-sumnsam2),(*matrix_pol)+x*int_total_nsam->value()+y,1);*/
      (*matrix_perm)[j*((*nsam2)[0]+(*nsam2)[1])+(((*nsam2)[0]+(*nsam2)[1])-sumnsam2)] = (*matrix_pol)[j*int_total_nsam->value()+y];
    }
    count[y] = 0;
    sumnsam2--;
  }
  /*
  c=0;
  for(y=int_total_nsam->value()-nsam[npops->value()-1];y<int_total_nsam->value();y++,c++)
    for(x=0;x<matrix_pol->reg_length_;x++)
      strncpy(matrix_perm+x*int_total_nsam->value()+(nsam2[0]+nsam2[1])+c,(*matrix_pol)+x*nsamtot->value()+y,1);
  */
  free(count);
}

void CCalcPermute::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

double CCalcPermute::ran1(void) {
  double ret = 0;
  
  /// ==========================================================================
  /// RANDOMIZE CALCULATION
  /// ==========================================================================
  if (calc_randomize_ == NULL) {
    DM_GET_CALC(calc_randomize_)
    DM_GET_DATA2(randomize_value_, STR(RANDOMIZE_VALUE))
  }
  
  if ((calc_randomize_ == NULL) || (randomize_value_ == NULL)) {
    ERROR_MSG << "CCalcMstatspopOpenMsFile::" << "Randomize does not exist..." END_MSG;
  } else {
    calc_randomize_->SetOutput(randomize_value_);
    calc_randomize_->Prepare();
    calc_randomize_->Calculate(manager()->all_commands()->dry_run());
    calc_randomize_->Finalize();
    ret = randomize_value_->value();
  }

  return ret;
}
