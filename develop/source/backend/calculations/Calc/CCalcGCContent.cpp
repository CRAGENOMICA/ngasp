/*
 * ngasp, a computational solution for performing next generation analysis of 
 * sequence polymorphisms using NGS data.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
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
 *  \brief     CCalcGCContent.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      October 27, 2015
 *  \pre
 *  \bug
 *  \warning
 */
#include "CCalcGCContent.h"

#include <cmath>

#include "../../language/CStringTable.h"

CCalcGCContent::CCalcGCContent()
: ICalculation(KeyString::CALC_GCCONTENT,
               KeyString::CALC_GCCONTENT_BRIEF_DESC,
               KeyString::CALC_GCCONTENT_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(vector,                                                      // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_GCCONTENT_VECTOR,                                       // Short Name
                   CALC_GCCONTENT_VECTOR_LONG,                                  // Long Name
                   CALC_GCCONTENT_VECTOR_DESC,                                  // Description
                   CALC_GCCONTENT_VECTOR_SAMP,                                  // Example
                   CALC_GCCONTENT_VECTOR_ONLY,                                  // Use only if
                   CALC_GCCONTENT_VECTOR_DEFV,                                  // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(percentage,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_GCCONTENT_PERCENTAGE,                                   // Short Name
                   CALC_GCCONTENT_PERCENTAGE_LONG,                              // Long Name
                   CALC_GCCONTENT_PERCENTAGE_DESC,                              // Description
                   CALC_GCCONTENT_PERCENTAGE_SAMP,                              // Example
                   CALC_GCCONTENT_PERCENTAGE_ONLY,                              // Use only if
                   CALC_GCCONTENT_PERCENTAGE_DEFV,                              // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
  
    SET_OUTPUT_INFO(total,                                                      // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_GCCONTENT_TOTAL,                                        // Short Name
                   CALC_GCCONTENT_TOTAL_LONG,                                   // Long Name
                   CALC_GCCONTENT_TOTAL_DESC,                                   // Description
                   CALC_GCCONTENT_TOTAL_SAMP,                                   // Example
                   CALC_GCCONTENT_TOTAL_ONLY,                                   // Use only if
                   CALC_GCCONTENT_TOTAL_DEFV,                                   // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcGCContent::~CCalcGCContent() {
}

void CCalcGCContent::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(vector)
    DM_INPUT(percentage)
  DM_GET_OUTPUTS
    DM_OUTPUT(total)
  DM_END
}

/**
 *  GC_Content Formula: https://en.wikipedia.org/wiki/GC-content
 */
void CCalcGCContent::Calculate(bool dry_run) {


  total->set_value(0);

  long int T = 0;
  long int C = 0;
  long int G = 0;
  long int A = 0;

  for (std::size_t i = 0; i < vector->Size(); i++) {
    switch((*vector)[i]) {
      case 'T':
        T++;
        break;
      case 'C':
        C++;
        break;
      case 'G':
        G++;
        break;
      case 'A':
        A++;
        break;
      default:
        break;
    }
  }

  long int numerador = 0;
  long int divisor = 0;

  if (percentage->value() == true) {
    numerador = (G+C);
    divisor = (A+T+G+C);
  } else {
    numerador = (A+T);
    divisor = (G+C);
  }

  if (divisor != 0) {
    float result = numerador;
    result /= divisor;
    total->set_value(result);
  }
}

void CCalcGCContent::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

