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
 *  \brief     CCalcMaskFileMs.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 13, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcMaskFileMs.h"

#include <cmath>
#include <cstring>

#include "../CAllCalculations.h"


CCalcMaskFileMs::CCalcMaskFileMs()
: ICalculation(KeyString::CALC_MASK_FILE_MS,
               KeyString::CALC_MASK_FILE_MS_BRIEF_DESC,
               KeyString::CALC_MASK_FILE_MS_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
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
  
    SET_OUTPUT_INFO(niter,                                                      // Variable
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
    SET_OUTPUT_INFO(length_al_real,                                             // Variable
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
    SET_OUTPUT_INFO(vector_mask,                                                // Variable
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
    SET_OUTPUT_INFO(matrix_mask,                                                // Variable
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
    SET_OUTPUT_INFO(sum_sam_mask,                                               // Variable
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
    SET_OUTPUT_INFO(length_mask,                                                // Variable
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
  SET_OUTPUT_INFO(length_mask_real,                                             // Variable
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

CCalcMaskFileMs::~CCalcMaskFileMs() {
}

void CCalcMaskFileMs::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(include_unknown)
    DM_INPUT(outgroup_presence)
    DM_INPUT(vint_perpop_nsam)
    DM_INPUT(npops)
    DM_INPUT(int_total_nsam)
    DM_INPUT(file_mas)
    DM_INPUT(length)
  DM_GET_OUTPUTS
    DM_OUTPUT(niter)
    DM_OUTPUT(length_al_real)
    DM_OUTPUT(vector_mask)
    DM_OUTPUT(matrix_mask)
    DM_OUTPUT(sum_sam_mask)
    DM_OUTPUT(length_mask)
    DM_OUTPUT(missratio)
    DM_OUTPUT(length_al)
    DM_OUTPUT(length_mask_real)
  DM_END
}

void CCalcMaskFileMs::Calculate(bool dry_run) {

  /*MASK FILE MS FORMAT => Ponerlo en una funcion */
  niter->set_value(0); /*permutation tests invalidated*/
  length_al_real->set_value(length->value());
  length_al->set_value(length_al_real->value());

  vector_mask->ReserveMemory(length->value(), 0.0);
  matrix_mask->ReserveMemory((int_total_nsam->value()+1) *
                               length->value(), 0);

  FILE *file_mask = NULL;
  long int li  = 0;
  int li2 = 0;
  long int n   = 0;
  int vli = 0;
  int x   = 0;
  int y   = 0;
  char c[2];
  c[0] = '\x0';
  c[1] = '\x0';
  char vvm[11];
  for (int i=0; i<11; i++) {
    vvm[i] = '\x0';
  }

  if(file_mas->value()[0] != '-') { /*file_mask defined*/
    if((file_mask = fopen (file_mas->value().c_str(),"r")) == 0) {
      printf("\n  It is not possible to open the input mask file %s.",file_mas->value().c_str());
      exit(1);
    }


    *c = fgetc(file_mask);

    while(*c != 0 && *c != -1 && n < int_total_nsam->value() - !outgroup_presence->value()+1 && li < length->value()) {
      while(*c != 10 && *c != 13 && *c != 0 && *c != -1) {
        if(n==0) {
          vvm[vli] = *c;
          while((*c = fgetc(file_mask)) != 32 && *c != 10 && *c != 13 && vli < 10) {
            vli++;
            vvm[vli] = *c;
          }
          vvm[vli+1] = (char)0; 
          (*vector_mask)[(unsigned int)li] = (float)atof(vvm); /*value of the position, usually 1 except for noncounting values or Syn/Nsyn (between 0 and 1)*/
          for(vli=0;vli<10;vli++) vvm[vli] = (char)0;
          vli = 0;
        }
        else {
          (*matrix_mask)[(unsigned int)(n-1) * (unsigned int)length->value() + (unsigned int)li] = (int)atoi(c) - 1;/*in case not defined file, all values are zero, in case file exist, normal is zero, missing is -1*/
          if((int)atoi(c) == 0 && include_unknown->value() == 0) (*vector_mask)[(unsigned int)li] = 0.; /*not counting missing values when not included*/
        }
        while((*c = fgetc(file_mask)) == 32);
        li++;
      }
      if(*c == 10 || *c == 13 || li > length->value()) {
        if(li > length->value()) {
          printf("\n  Error: Length of rows in mask file %s are longer than defined (row %ld is %ld > %ld). ",file_mas->value().c_str(), n, li, length->value());
          exit(1);
        }
        n++;
        li = 0;
        *c = fgetc(file_mask);
      }
    }
    fclose(file_mask);

    if(outgroup_presence->value() == 0) {/*the "cryptic" outgroup is all 1*/
      for(li=0;li<length->value();li++) {
        (*matrix_mask)[(unsigned int)(int_total_nsam->value()) * (unsigned int)length->value() + (unsigned int)li] = 0;
      }
    }
  /*}*/
  /*}*/
    /*if(include_unknown->value()) {*/
      sum_sam_mask->ReserveMemory(int_total_nsam->value(), 0.0);

      length_mask->set_value(0.0);
      length_mask_real->set_value(0.0);
      li2 = 0;
      for(li=0;li<length->value();li++) {
        if((*vector_mask)[li] > 0.) {
          if(npops->value() > 1) {
            x = 0;
            for(n=0;n<int_total_nsam->value()-(*vint_perpop_nsam)[npops->value()-1];n++) {
              li2 += 1;
              if((*matrix_mask)[(unsigned int)n * (unsigned int)length->value() + (unsigned int)li] == 0) {
                (*sum_sam_mask)[n] += 1.; /*1 sum, 0 no sum*/
                x += 1;
              }
              else missratio->set_value(missratio->value() + 1.);
            }
          }
          else x = 1;
          y = 0;
          for(n=int_total_nsam->value()-(*vint_perpop_nsam)[npops->value()-1];n<int_total_nsam->value();n++) {
            if(npops->value() == 1) li2 += 1;
            if((*matrix_mask)[(unsigned int)n * (unsigned int)length->value() + (unsigned int)li] == 0) {
              (*sum_sam_mask)[n] += 1.; /*1 sum, 0 no sum*/
              y += 1;
            }
            else {
              if(npops->value() == 1) missratio->set_value(missratio->value() + 1.);
            }
          }
          if(x > 0 && y > 0) {
            length_mask_real->add((long int)1); /*length where the outgroup and one of the rest lines exists*/
            length_mask->add((*vector_mask)[(unsigned int)li]); /*length where the outgroup and one of the rest lines exists*/
          }
          else {
              if(x==0 || (y==0 && x>0)) {
                 missratio->set_value(missratio->value() - ((int_total_nsam->value() - (*vint_perpop_nsam)[npops->value()-1]) - x)) ;
                 li2 -= (int_total_nsam->value() - (*vint_perpop_nsam)[npops->value()-1]);
             }
             if(y==0 && npops->value() == 1) {
                 missratio->set_value(missratio->value() - int_total_nsam->value());
                 li2 -= (int_total_nsam->value());
             }
          }            
        }
      }

      if(li2) missratio->set_value((double)missratio->value()/(double)li2);
      else missratio->set_value((double)1);
      length_al->set_value(length_mask->value());
      length_al_real->set_value(length_mask_real->value());
      /*
      li=0;
      for(n=0;n<int_total_nsam;n++) {
          li += sum_sam_mask[n];
      }
      missratio = 1.0 - (double)li2/(double)(li2+missratio);
      */
   /*}*/
	}
}

void CCalcMaskFileMs::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
