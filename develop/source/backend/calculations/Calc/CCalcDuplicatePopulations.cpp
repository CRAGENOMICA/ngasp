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
 *  \brief     CCalcDuplicatePopulations.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 16, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcDuplicatePopulations.h"

#include <cmath>

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"

CCalcDuplicatePopulations::CCalcDuplicatePopulations()
: ICalculation(KeyString::CALC_DUPLICATE_POPULATIONS,
               KeyString::CALC_DUPLICATE_POPULATIONS_BRIEF_DESC,
               KeyString::CALC_DUPLICATE_POPULATIONS_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
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
                   OPTTYPE_mandatory)                                           // Required)
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
                   OPTTYPE_mandatory)                                           // Required)
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
                   OPTTYPE_mandatory)                                           // Required)
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
                   OPTTYPE_mandatory)                                           // Required)
  
    SET_OUTPUT_INFO(vint_perpop_nsam,                                           // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_OUTPUT_INFO(int_total_nsam,                                             // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcDuplicatePopulations::~CCalcDuplicatePopulations() {
}

void CCalcDuplicatePopulations::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(npops)
    DM_INPUT(ploidy)
    DM_INPUT(outgroup_presence)
    DM_INPUT(formatfile)
  DM_GET_OUTPUTS
    DM_OUTPUT(vint_perpop_nsam)
    DM_OUTPUT(int_total_nsam)
  DM_END
}

void CCalcDuplicatePopulations::Calculate(bool dry_run) {


  if ((ploidy->value() == DIPLOID) && (formatfile->value() == FASTA_FILE)) {
    int_total_nsam->set_value(int_total_nsam->value() * 2);
      
    for (int i = 0; i < npops->value(); i++) {
      if ((outgroup_presence->value() == 0) && (i == npops->value()-1)) {
        // Do not multiply by 2 the last one if it is the added outgroup.
      } else {
        // If ploidy is 2, all populations must be multiplied by 2.
        (*vint_perpop_nsam)[i] *= 2;
      }
    }
  }
}

void CCalcDuplicatePopulations::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
