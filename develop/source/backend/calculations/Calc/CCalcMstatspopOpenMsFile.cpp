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
 *  \brief     CCalcMstatspopOpenMsFile.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 2, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcMstatspopOpenMsFile.h"

#include <cmath>
#include <cstring>

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../CAllCalculations.h"

#include "CCalcRandomize.h"

#include "../../commands/CAllCommands.h"

CCalcMstatspopOpenMsFile::CCalcMstatspopOpenMsFile()
: ICalculation(KeyString::CALC_MSTATSPOP_OPEN_MS,
               KeyString::CALC_MSTATSPOP_OPEN_MS_BRIEF_DESC,
               KeyString::CALC_MSTATSPOP_OPEN_MS_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(file_in,                                                     // Variable
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
    SET_INPUT_INFO(nsamuser,                                                    // Variable
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
    SET_INPUT_INFO(nsamtot,                                                     // Variable
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
    SET_INPUT_INFO(kind_length,                                                 // Variable
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
    SET_INPUT_INFO(vector_mask,                                                 // Variable
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
    SET_INPUT_INFO(svratio,                                                     // Variable
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
    SET_INPUT_INFO(freq_revert,                                                 // Variable
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
    SET_INPUT_INFO(freq_missing_ms,                                             // Variable
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
    SET_INPUT_INFO(location_missing_ms,                                         // Variable
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
                   OPTTYPE_mandatory)                                           // Required

    SET_OUTPUT_INFO(matrix_pol,                                                 // Variable
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
    SET_OUTPUT_INFO(matrix_freq,                                                // Variable
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
    SET_OUTPUT_INFO(matrix_pos,                                                 // Variable
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
    SET_OUTPUT_INFO(length_seg,                                                 // Variable
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
    SET_OUTPUT_INFO(matrix_sv,                                                  // Variable
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
    SET_OUTPUT_INFO(length_mask_real,                                           // Variable
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
    SET_OUTPUT_INFO(lengthamng,                                                 // Variable
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
    SET_OUTPUT_INFO(nmhits,                                                     // Variable
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
    SET_OUTPUT_INFO(vector_priors,                                              // Variable
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
    SET_OUTPUT_INFO(npriors,                                                    // Variable
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
    SET_OUTPUT_INFO(sum_sam,                                                    // Variable
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
    SET_OUTPUT_INFO(nsites1_pop,                                                // Variable
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
    SET_OUTPUT_INFO(nsites1_pop_outg,                                           // Variable
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
    SET_OUTPUT_INFO(nsites2_pop,                                                // Variable
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
    SET_OUTPUT_INFO(nsites2_pop_outg,                                           // Variable
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
    SET_OUTPUT_INFO(nsites3_pop,                                                // Variable
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
    SET_OUTPUT_INFO(nsites3_pop_outg,                                           // Variable
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
    SET_OUTPUT_INFO(anx,                                                        // Variable
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
    SET_OUTPUT_INFO(bnx,                                                        // Variable
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
    SET_OUTPUT_INFO(anxo,                                                       // Variable
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
    SET_OUTPUT_INFO(bnxo,                                                       // Variable
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
    SET_OUTPUT_INFO(sort_nsam,                                                  // Variable
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

  file_input_ = NULL;

  /// ==========================================================================
  /// RANDOMIZE CALCULATION
  /// ==========================================================================
  calc_randomize_ = NULL;
}

CCalcMstatspopOpenMsFile::~CCalcMstatspopOpenMsFile() {
}

void CCalcMstatspopOpenMsFile::Prepare(void) {
  // Opening files
  if (calc_randomize_ == NULL) {
    DM_GET_CALC(calc_randomize_)
    DM_GET_DATA2(randomize_value_, STR(RANDOMIZE_VALUE))
  } 
  if ((calc_randomize_ == NULL) || (randomize_value_ == NULL)) {
    ERROR_MSG << "CCalcMstatspopOpenMsFile::" << "Randomize does not exist..." END_MSG;
  }
  

  CDataStdString *file_in = NULL;
  file_in = (CDataStdString *)manager()->data_manager()->GetDataByName(
                                                            file_in,
                                                            GetParentInput(0),
                                                            GetInputName(0));

  if (file_input_ != NULL) {
    fzclose(file_input_, &input_gz_);
    file_input_ = NULL;
  }

  if (file_in->value() == "") {
    file_input_ = stdin;
  }
  else {
    if ((file_input_ = fopen( file_in->value().c_str(), "r")) == 0) {
      printf("\n It is not possible to open the input file %s.", file_in->value().c_str());
      exit(1);
    }
  }


  //============================================================================
	init_gzip_structure(&input_gz_);
	input_gz_.file_compressed = 0;
  if (file_in->value().length() > 3) {
    if((file_in->value()[file_in->value().length()-3] == '.') &&
         (file_in->value()[file_in->value().length()-2] == 'g') &&
         (file_in->value()[file_in->value().length()-1] == 'z')) {
        input_gz_.file_compressed = 1;
    }
  }
  //============================================================================
  
  
  
  DM_GET_INPUTS
    DM_INPUT(file_in)  // Used in Prepare()
    DM_INPUT(include_unknown)
    DM_INPUT(outgroup_presence)
    DM_INPUT(force_outgroup)  // <--------------- NEW
    DM_INPUT(nsamuser)
    DM_INPUT(npops)
    DM_INPUT(nsamtot)
    DM_INPUT(length)
    DM_INPUT(kind_length)
    DM_INPUT(vector_mask)
    DM_INPUT(svratio)
    DM_INPUT(freq_revert)
    DM_INPUT(file_mas)
    DM_INPUT(freq_missing_ms)
    DM_INPUT(location_missing_ms)
    DM_INPUT(formatfile)  // <--------------- NEW
  DM_GET_OUTPUTS
    DM_OUTPUT(matrix_pol)
    DM_OUTPUT(matrix_freq)
    DM_OUTPUT(matrix_pos)
    DM_OUTPUT(length_seg)  // <--------------- NEW
    DM_OUTPUT(matrix_sv)
    DM_OUTPUT(length_mask)
    DM_OUTPUT(length_mask_real)  // <------------- NEW
    DM_OUTPUT(lengthamng)
    DM_OUTPUT(nmhits)
    DM_OUTPUT(matrix_mask)
    DM_OUTPUT(vector_priors)
    DM_OUTPUT(npriors)
    DM_OUTPUT(sum_sam)
    DM_OUTPUT(sum_sam_mask)
    DM_OUTPUT(nsites1_pop)
    DM_OUTPUT(nsites1_pop_outg)
    DM_OUTPUT(nsites2_pop)
    DM_OUTPUT(nsites2_pop_outg)
    DM_OUTPUT(nsites3_pop)
    DM_OUTPUT(nsites3_pop_outg)
    DM_OUTPUT(anx)
    DM_OUTPUT(bnx)
    DM_OUTPUT(anxo)
    DM_OUTPUT(bnxo)
    DM_OUTPUT(missratio)
    DM_OUTPUT(sort_nsam)  // <--------------- NEW
  DM_END  
}

#define TOCONSIDER 0

void CCalcMstatspopOpenMsFile::Calculate(bool dry_run) {
	static char c[1],cc[1];
	long int li,li2,max_biasites = 256;
	char value[20];
	int i,y,y2,k,n2;

#if TOCONSIDER==1
    long int posmhitinit;
	int t_0=0;
	int t_1=0;
	int s1_0=0;
	int s1_1=0;
	int s2_0=0;
	int s2_1=0;
	double r0,r1;
    int physical;
    long int *matrix_phys;
#endif
	int ft;
	long int n,xx,li3;
	int x,z,v,p,z2,v2;
	
	long int *mhitbp;
	long int *discarded;
	double freq_missing_ms2=0.;
    int *matrix_mask2=0;
	
	/*matrix_sv: number of transitions and transversions. We have to give these results to the main function*/
	
	nmhits->set_value(0);

	/*READ THE MS FILE */
	
	*cc = fzgetc(file_input_, &input_gz_);
	if(*cc==0 || *cc==-1) return; // 1;
	*c  = fzgetc(file_input_, &input_gz_);
	if(*c==0 || *c==-1) return; // 1;
	while ((*c != '/' || *cc != '/') && *c != 0 && *c != -1) { /* read initial iteration signal: '//' */
		*cc = *c;
		*c  = fzgetc(file_input_, &input_gz_);
	}
	if(*c==0 || *c==-1) return; // 1;
	if(*c == '/') {
		*c  = fzgetc(file_input_, &input_gz_);
		if(*c==0 || *c==-1) return; // 1;
		
		ft=0;
		/*Read priors or other parameters*/
		if ((*vector_priors).GetData()==0) {
      vector_priors->ReserveMemory(1, 0.0);
//			if((*vector_priors = (double *)calloc((long int)1,sizeof(double)))==0) {
//				puts("Error: memory not allocated. get_msdata.01"); 
//				return; //(1);
//			}
			ft = 1;
		}
		npriors->set_value(0);
		while (*c != 10  && *c != 13 && *c != 0) {
			while(*c == 32 || *c == 9) {*c  = fzgetc(file_input_, &input_gz_);}
			i = 0;
			while(*c!=32 && *c != 9 && *c != 10 && *c != 13) {
				value[i] = *c;
				*c  = fzgetc(file_input_, &input_gz_);
				i++;
			}
			if(*c == 0 || *c == 10 || *c == 13) if(i==0) break;
			value[i] = '\0';
			(*vector_priors)[npriors->value()] = (double)atof(value);
			npriors->add(1);
			if(ft) {
        vector_priors->ReallocMemory(npriors->value()+1, 0);
//				if((*vector_priors = (double *)realloc(*vector_priors,(long int)(npriors->value()+1)*sizeof(double)))==0) {
//					puts("Error: memory not allocated. get_msdata.02"); 
//					return; //(1);
//				}
			}
		}	
		ft = 0;
		/*... go next line*//*
		while (*c != 10) 
			*c  = fzgetc(file_input_, &input_gz_);
		*/
        
        if((matrix_mask2 = (int *)calloc((unsigned int)(nsamtot->value()+1)*length->value(),sizeof(int))) == 0) {
            printf("Error allocating memory");
            exit(1);
        }

        /*BEGIN define mask: define first the ratio of missing values:*/
        /*formatfile->value()=2 IS DEPRECATED*/
		/*if(formatfile->value() == 2 && npriors->value() >= location_missing_ms->value() && location_missing_ms->value() > 0)
			freq_missing_ms2 = (*vector_priors)[location_missing_ms->value()-1];
		else */freq_missing_ms2 = freq_missing_ms->value();
		
		/*eliminate positions from mask*/ /*it is much faster to include a binomial distribution per position in the calculations!!*/
		if((file_mas->value()[0] == '-'  && file_mas->value()[1] == '1')/* || formatfile->value() == 2*/) { /*all positions are accepted*/
			for(li2=0;li2<length->value();li2++) (*vector_mask)[li2] = 1.0;
			if(freq_missing_ms2) {
				/* MODIFY TO INCLUDE CONDITIONAL LENGTH (kind_length:0,1,2,3) *//*
				for(li2=0;li2<(nsamtot->value()-(*nsamuser)[npops->value()-1])*length->value();li2++) {
					if(ran1() <= freq_missing_ms2 && formatfile->value() == 1) 
						(*matrix_mask)[li2] = -1;
					else (*matrix_mask)[li2] = 0;
				}
				*/
				for(li2=0;li2<length->value();li2++) {
					li3 = -1; /*number of samples with no-Ns from a binomial*/
					/*Even in the case of NGS reads, the distribution of Ns seems a binomial. */
					/*In cases with high depth the variance increase. Another factors also influence. Some regions have clearly lower depth than expected*/
					/*On the other hand, a binomial approach seems justified*/
					while(li3 < kind_length->value()) /*CONDITIONAL on kind_length*/
						li3 = largebinomialdist(1.0-freq_missing_ms2, nsamtot->value()-(*nsamuser)[npops->value()-1]);
					for(n=nsamtot->value()-(*nsamuser)[npops->value()-1]-1;n>=0;n--) { /*define for each sample if N or nt*/
						if(ran1() > (double)li3/(double)(n+1)) {
							(*matrix_mask)[(unsigned int)n*(unsigned int)length->value()+(unsigned int)li2] = -1; /*N*/
						}
						else {
							(*matrix_mask)[(unsigned int)n*(unsigned int)length->value()+(unsigned int)li2] = 0; /*nt*/
							li3 -= 1;
						}
					}
				}
				/*END MODIFICATION*/
				/*the outgroup has no missing values!!*//* <<<<<<<<<<<<-----------------------------------!!!!!!!!*/
				for(li2=(nsamtot->value()-(*nsamuser)[npops->value()-1])*length->value();li2<(nsamtot->value())*length->value();li2++) 
					(*matrix_mask)[li2] = 0;
			}
			else {
				for(li2=0;li2<(nsamtot->value())*length->value();li2++) (*matrix_mask)[li2] = 0;
			}

            /*if(include_unknown->value()) {*/
                sum_sam_mask->ReserveMemory(nsamtot->value(), 0.0);
//                if((*sum_sam_mask = (double *)calloc(nsamtot->value(),sizeof(double))) == 0) {
//                    printf("Error allocating memory");
//                    exit(1);
//                }
            /*}*/
            missratio->set_value(0.);
            length_mask->set_value(0.);
            length_mask_real->set_value(0);
            li3 = 0;
            for(li2=0;li2<length->value();li2++) {
                if((*vector_mask)[li2] > 0.) {
                    if(npops->value() > 1) {
                        x = 0;
                        for(n=0;n<nsamtot->value()-(*nsamuser)[npops->value()-1];n++) {
                            li3 += 1;
                            if((*matrix_mask)[(unsigned int)n*(unsigned int)length->value()+(unsigned int)li2] == 0) {
                                sum_sam_mask[0][n] += 1.; /*1 sum, 0 no sum*/
                                x += 1;
                            }
                            else missratio->add(1.);
                        }
                    }
                    else x = 1;
                    y = 0;
                    for(n=nsamtot->value()-(*nsamuser)[npops->value()-1];n<nsamtot->value();n++) {
                        if(npops->value() == 1) li3 += 1;
                        if((*matrix_mask)[(unsigned int)n*(unsigned int)length->value()+(unsigned int)li2] == 0) {
                            (*sum_sam_mask)[n] += 1.; /*1 sum, 0 no sum*/
                            y += 1;
                        }
                        else {
                            if(npops->value() == 1) missratio->add(1.);
                        }
                    }
                    if(x > 0 && y > 0) {
                        length_mask_real->add(1); /*length where the outgroup and one of the rest lines exists*/
                        length_mask->add((*vector_mask)[li2]); /*length where the outgroup and one of the rest lines exists*/
                    }
                    else {
                        if(x==0 || (y==0 && x>0)) {
                            missratio->set_value(missratio->value() - ((nsamtot->value() - (*nsamuser)[npops->value()-1]) - x));
                            li3 -= (nsamtot->value() - (*nsamuser)[npops->value()-1]);
                        }
                        if(y==0 && npops->value() == 1) {
                            missratio->set_value(missratio->value() - (nsamtot->value())) ;
                            li3 -= (nsamtot->value());
                        }
                    }
                }
            }
            if(li3) missratio->set_value((double)missratio->value()/(double)li3);   
            else missratio->set_value(1.);
		}
		/*END defining mask in case m option ==-1 and include_unknown->value() ==1*/
		
        while (*c==32 || *c == 9 || *c == 13 || *c == 10) *c = fzgetc(file_input_, &input_gz_);
		/*READ the row with the number of segregating sites*/
		i = 0;
		while(*c!=32 && *c != 9 && *c != 10 && *c != 13) {
			value[i] = *c;
			*c  = fzgetc(file_input_, &input_gz_);
			i++;
		}
		value[i] = '\0';
		if(strcmp(value,"segsites:") == 0) {
			while(*c == 32 || *c == 9) {*c  = fzgetc(file_input_, &input_gz_);}
			i = 0;
			while(*c!=32 && *c != 9 && *c != 10 && *c != 13) {
				value[i] = *c;
				*c  = fzgetc(file_input_, &input_gz_);
				i++;
			}
			value[i] = '\0';
		}
		max_biasites = (long int)atol(value);
		
		/*allocate memory*/
    matrix_pol->ReserveMemory(nsamtot->value()*(max_biasites+1), STR(DEFAULT_CHAR)[0]);
//        if((*matrix_pol = (char *) calloc (((long int)nsamtot->value()*(max_biasites+1)),sizeof(char))) == 0) {
//            puts("Error: memory not allocated. get_msdata.3");
//            return; //(1);
//        }
    matrix_freq->ReserveMemory(max_biasites+1, 0);
//		if((*matrix_freq = (long int *) calloc (max_biasites+1,sizeof(long int))) == 0) {
//			puts("Error: memory not allocated. get_msdata.5"); 
//			return; //(1);
//		}
    matrix_pos->ReserveMemory(max_biasites+1, 0);
//		if((*matrix_pos = (long int *) calloc (max_biasites+1,sizeof(long int))) == 0) {
//			puts("Error: memory not allocated. get_msdata.4"); 
//			return; //(1);
//		}
    matrix_sv->ReserveMemory(max_biasites+1, 0);
//		if((*matrix_sv = (long int *) calloc((long int)max_biasites+1,sizeof(long int)))==0) {
//			puts("Error: memory not allocated. get_msdata.00"); 
//			return; //(1);
//		}
        if(max_biasites == 0)
		{
			length_seg->set_value(0);
			return; // 0;
		}
		
		if((mhitbp = (long int *) calloc (length->value()+1, sizeof(long int))) == 0) {
			puts("Error: memory not reallocated. get_msdata.13"); 
			return; //(0);
		}
#if TOCONSIDER == 0
        if((discarded = (long int *) calloc (max_biasites+1, sizeof(long int))) == 0) {
            puts("Error: memory not reallocated. get_msdata.13");
            return; //(0);
        }
#else
        if((matrix_phys = (long int *) calloc (max_biasites+1,sizeof(long int))) == 0) {
            puts("Error: memory not allocated. get_msdata.4");
            return; //(1);
        }
		if((discarded = (long int *) calloc (max_biasites+1, sizeof(long int))) == 0) {
			puts("Error: memory not reallocated. get_msdata.13"); 
			return; //(0);
		}
#endif
		/*READ the row header */
		while (*c != 10) {
			*c  = fzgetc(file_input_, &input_gz_); /*next line*/
		}
		while (*c==32 || *c == 9 || *c == 13 || *c == 10) {*c  = fzgetc(file_input_, &input_gz_);}
		i = 0;
		while(*c!=32 && *c != 9 && *c != 10 && *c != 13) {
			value[i] = *c;
			{*c  = fzgetc(file_input_, &input_gz_);}
			i++;
		}
		value[i] = '\0';
		
#if TOCONSIDER == 1
        physical = 0;
		if(strcmp(value,"physical:") == 0) {
			physical = 1;
			for(li=0;li<max_biasites;li++) {
				while(*c == 32 || *c == 9 || *c == 13 || *c == 10) {*c  = fzgetc(file_input_, &input_gz_);}
				i = 0;
				while(*c!=32 && *c != 9 && *c != 10 && *c != 13) {
					value[i] = *c;
					{*c  = fzgetc(file_input_, &input_gz_);}
					i++;
				}
				value[i] = '\0';
				matrix_phys[li] = (long int)round((double)atof(value));
			}

			/*READ the row with the positions*/
			while (*c != 10) {
				*c  = fzgetc(file_input_, &input_gz_); /*next line*/
			}
			while (*c==32 || *c == 9 || *c == 13 || *c == 10) {*c  = fzgetc(file_input_, &input_gz_);}
			i = 0;
			while(*c!=32 && *c != 9 && *c != 10 && *c != 13) {
				value[i] = *c;
				{*c  = fzgetc(file_input_, &input_gz_);}
				i++;
			}
			value[i] = '\0';
		}
#endif
        /*Take the "positions" in physical integer positions (starting from 1!!!): */
        /*if mhit, keep the physical position (mhitbp) in order to consider*/
        /*will keep only those positions that reverted to 1/2 variants, otherwise reject*/
 		if(strcmp(value,"positions:") == 0) {
#if TOCONSIDER==1
			posmhitinit = -1;
#endif
            while(*c == 32 || *c == 9 || *c == 13 || *c == 10) {*c  = fzgetc(file_input_, &input_gz_);}
			for(li=0;li<max_biasites;li++) {
				while(*c == 32 || *c == 9) {*c  = fzgetc(file_input_, &input_gz_);}
                if(*c == 13 || *c == 10) {max_biasites = li+1; break;}
                i = 0;
				while(*c!=32 && *c != 9 && *c != 10 && *c != 13) {
					value[i] = *c;
					{*c  = fzgetc(file_input_, &input_gz_);}
					i++;
				}
				value[i] = '\0';
                (*matrix_pos)[li] = round(((double)atof(value)*length->value())+1);/*start from 1!!!*/
                /*Mandatory to count a negative (missing) value at position 0!!!*/
				if((*matrix_pos)[li] == (long int)length->value()) (*matrix_pos)[li] = (long int)length->value()+1-1;
                /*in case ms has a position value of 1.000 by rounding (...)*/
#if TOCONSIDER==0
                /*TOO COMPLEX: REJECT MHIT POSITIONS DIRECTLY*/
                /*use this code instead*/
                if(li) {
                    if(labs((*matrix_pos)[li]) == labs((*matrix_pos)[li])-1) {
                        if(mhitbp[(long int)labs((*matrix_pos)[li])] == 0) nmhits->add(1);
                        mhitbp[(long int)labs((*matrix_pos)[li])] = 1;
                    }
                }
#else
                if(svratio->value() > -1.0) {
					if(li==0) {/*first position: transition or transversion?*/
						if((r0=ran1()) < (svratio->value()/(svratio->value()+1.))) {(*matrix_sv)[li]=1;t_0 = 1;s1_0 = 0;s2_0 = 0;}
						else {
							if(r0 > (svratio->value()/(svratio->value()+1.)) + (1.-svratio->value()/(svratio->value()+1.))/2.) {
								(*matrix_sv)[li]=2;t_0 = 0;s1_0 = 1;s2_0 = 0;
							}
							else {(*matrix_sv)[li]=3;t_0 = 0;s1_0 = 0;s2_0 = 1;}
						}
					}
					if(li) {
						if(labs((*matrix_pos)[li]) == labs((*matrix_pos)[li])-1) {
							/*mhit: can we recover it? (the same two nucleotides)*/
							if(posmhitinit == -1) {
								posmhitinit = li-1; /*locate first column of mhit position*/
								/*define if transition,transversion1 or transversion2 (t,s1,s2) for column0*/
							}
							/*if((*matrix_pos)[posmhitinit] >= 0) {*//*now always true*/
								/*define if transition,transversion1 or transversion2 (t,s1,s2) for given column*/
								if((r1=ran1()) < (svratio->value()/(svratio->value()+1.))) {
                                    t_1 = 1;s1_1 = 0;s2_1 = 0;
                                }
								else {
									if(r1 < (svratio->value()/(svratio->value()+1.)) + (1.-svratio->value()/(svratio->value()+1.))/2.) {
										t_1 = 0;s1_1 = 1;s2_1 = 0;
									}
									else {
										t_1 = 0;s1_1 = 0;s2_1 = 1;
									}
								}
							/*}*/
							if(!(t_0 == t_1 && s1_0 == s1_1 && s2_0 == s2_1)) { /*mhit*/
								/*when it is a mhit */
								/* count the position mhit in a matrix*/
                                mhitbp[(long int)labs((*matrix_pos)[li])] = 1;
                                if(t_1)  (*matrix_sv)[li]=1;
								else if(s1_1) (*matrix_sv)[li]=2;
								else if(s2_1) (*matrix_sv)[li]=3;
                                for(li2=posmhitinit;li2<=li;li2++)
                                    discarded[li2] = 1;/*mhit: discard the positions*/
							}
							else {
                                if(discarded[posmhitinit]==0) {/*if there were more mhits we discard the position*/
                                    /*mhit reverted to the same two nucleotides: no observed mhit*/
                                    /*in fact ms is not using discrete positions. It is only an approach when there is recombination*/
                                    mhitbp[(long int)labs((*matrix_pos)[li])] = 2;/*mhit but not seen*/
                                    (*matrix_sv)[li] = (*matrix_sv)[posmhitinit];
                                }
                                else
                                    discarded[li] = 1;
							}
						}
						else {
							/*if no mhit calculate if transition or transversion*/
							if((r0=ran1()) < (svratio->value()/(svratio->value()+1.))) {(*matrix_sv)[li]=1;t_0 = 1;s1_0 = 0;s2_0 = 0;}
							else {
								if(r0 < (svratio->value()/(svratio->value()+1.)) + (1.-svratio->value()/(svratio->value()+1.))/2.) {
									(*matrix_sv)[li]=2;t_0 = 0;s1_0 = 1;s2_0 = 0;
								}
								else {(*matrix_sv)[li]=3;t_0 = 0;s1_0 = 0;s2_0 = 1;}
							}
                            posmhitinit = -1;
						}
					}
				}
#endif
			}
		}
				
#if TOCONSIDER==1
		/*READ the matrix*/
        /*we accept values 0,1 for variants (DEPRECATED!: TO ERASE: and 8 and 9 for gaps and missing values)*/
        for(y=0;y<nsamtot->value()-!outgroup_presence->value();y++) {
			while(*c == 32 || *c == 9 || *c == 13 || *c == 10) {*c  = fzgetc(file_input_, &input_gz_);}
			li=0; /*li is the counter for max_bialsites.*/
            li2=0;/*li2 only count if the physical position is not equal*/
            k=0;/*index to control hidden mhits (2 mutations in the same position with same variants)*/
            for(li=0;li<max_biasites;li++)/*while(*c != 10 && *c != 13)*/ {
                if(li==0 || (li > 0 && labs((*matrix_pos)[li]) != labs((*matrix_pos)[li])-1)) k=0; /*{*/
                if(mhitbp[(long int)labs((*matrix_pos)[li])] == 0) {
                    if(li>0) li2++;
                    if((*matrix_mask)[y*length->value()+(long int)labs((*matrix_pos)[li])-1] == -1 ||
                       matrix_mask2[y*length->value()+(long int)labs((*matrix_pos)[li])-1] == -1 || *c=='8' || *c == '9') {/*missing*/
                        (*matrix_pol)[((li2*nsamtot->value())+y)] = '-';
                        matrix_mask2[y*length->value()+(long int)labs((*matrix_pos)[li])-1] = -1;
                        (*matrix_pos)[li] = -(long int)labs((*matrix_pos)[li]);
                        /* <---- means this position has mising values (Ns)*/
                    }	
                    if((*matrix_mask)[y*length->value()+(long int)labs((*matrix_pos)[li])-1] == 0 &&
                       matrix_mask2[y*length->value()+(long int)labs((*matrix_pos)[li])-1] == 0 && *c!='8' && *c != '9') {/*no missing*/
                        (*matrix_pol)[((li2*nsamtot->value())+y)] = *c;
                    }
                    if((*matrix_mask)[y*length->value()+(long int)labs((*matrix_pos)[li])-1] != -1 && *c > '0' && *c != '8' && *c != '9') {
                        (*matrix_freq)[li2] += 1;
                    }
                    if(outgroup_presence->value() == 0 && y == nsamtot->value()-2) {
                        /*make a copy of the last line and calculate the total frequency of derived*/
                        if(ran1()<freq_revert->value()) {
                            y2 = y;
                            while(y2 > 0 && (*matrix_pol)[((li2*nsamtot->value())+y2)] == '-') y2--;
                            (*matrix_pol)[((li2*nsamtot->value())+y+1)] = (*matrix_pol)[((li2*nsamtot->value())+y2)];
                            if((*matrix_pol)[((li2*nsamtot->value())+y2)] != '0' && (*matrix_pol)[((li2*nsamtot->value())+y2)] != '-')
                                (*matrix_freq)[li2] += 1;
                        }
                        else 
                            (*matrix_pol)[((li2*nsamtot->value())+y+1)] = '0';
                    }
                }
                /*}*/
                else {/*mhit*/
                    if(discarded[li] == 0) {
                        /* mhit with two variants (invisible mhit)*/
                        if((*matrix_mask)[y*length->value()+(long int)labs((*matrix_pos)[li])-1] == -1 ||
                           matrix_mask2[y*length->value()+(long int)labs((*matrix_pos)[li])-1] == -1 || *c=='8' || *c == '9') {
                            /*missing data*/
                            (*matrix_pol)[(((li2)*nsamtot->value())+y)] = '-';
                            matrix_mask2[y*length->value()+(long int)labs((*matrix_pos)[li])-1] = -1;
                            (*matrix_pos)[li2] = -(long int)labs((*matrix_pos)[li2]);
                            /* <---- means this position has mising values ('N')*/
                            k+=1;
                        }
                        else {
                            if((*matrix_mask)[y*length->value()+(int)labs((*matrix_pos)[li])-1] == 0 &&
                               matrix_mask2[y*length->value()+(int)labs((*matrix_pos)[li])-1] == 0) {
                                /*no missing position in mask neither missing in *c */
                                if((*matrix_pol)[(long int)(((li2)*(long int)nsamtot->value())+y)] == '0' && *c != '0') {
                                    /*mutation in *c, change (*matrix_pol) and count freq*/
                                    (*matrix_pol)[(long int)(((li2)*(long int)nsamtot->value())+y)] = *c;
                                    (*matrix_freq)[(long int)li2] += (long int)1;
                                }
                                /*if((*matrix_pol)[(((li2)*nsamtot->value())+y)] != '0' && *c == '0') {*/
                                    /*no mutation in *c, nothing changes*/
                                /*}*/
                                if((*matrix_pol)[(long int)(((li2)*(long int)nsamtot->value())+y)] != '0' && *c != '0') {
                                    /*mutation in both positions: revert to '0'*/
                                    (*matrix_pol)[(long int)(((li2)*(long int)nsamtot->value())+y)] = '0';/*revert the mutation to ancestral*/
                                    (*matrix_freq)[(long int)li2] -= (long int)1;
                                }
                            }
                            k+=1;
                        }
                        if(y==nsamtot->value()-!outgroup_presence->value()-1 && k>1)
                            discarded[li]=1;
                    }
                }
				*c  = fzgetc(file_input_, &input_gz_);
			}
		}
#else
        /*READ the matrix*/
        /*we accept values 0,1 for variants (DEPRECATED!: TO ERASE: and 8 and 9 for gaps and missing values)*/
        for(y=0;y<nsamtot->value()-!outgroup_presence->value();y++) {
            while(*c == 32 || *c == 9 || *c == 13 || *c == 10) {*c  = fzgetc(file_input_, &input_gz_);}
            li=0; /*li is the counter for max_bialsites.*/
            for(li=0;li<max_biasites;li++) {
                if((*matrix_mask)[y*length->value()+(long int)labs((*matrix_pos)[li])-1] == -1) {/*missing*/
                    (*matrix_pol)[((li*nsamtot->value())+y)] = '-';
                    (*matrix_pos)[li] = -(long int)labs((*matrix_pos)[li]);
                }
                if((*matrix_mask)[y*length->value()+(long int)labs((*matrix_pos)[li])-1] == 0) {/*no missing*/
                    (*matrix_pol)[((li*nsamtot->value())+y)] = *c;
                }
                if((*matrix_mask)[y*length->value()+(long int)labs((*matrix_pos)[li])-1] != -1 && *c > '0') {
                    (*matrix_freq)[li] += 1;
                }
                if(outgroup_presence->value() == 0 && y == nsamtot->value()-2) {
                    /*make a copy of the last line and calculate the total frequency of derived*/
                    if(ran1()<freq_revert->value()) {
                        y2 = y;
                        while(y2 > 0 && (*matrix_pol)[((li*nsamtot->value())+y2)] == '-') y2--;
                        (*matrix_pol)[((li*nsamtot->value())+y+1)] = (*matrix_pol)[((li*nsamtot->value())+y2)];
                        if((*matrix_pol)[((li*nsamtot->value())+y2)] != '0' && (*matrix_pol)[((li*nsamtot->value())+y2)] != '-')
                            (*matrix_freq)[li] += 1;
                    }
                    else
                        (*matrix_pol)[((li*nsamtot->value())+y+1)] = '0';
                }
                *c  = fzgetc(file_input_, &input_gz_);
            }
        }
#endif
        
        /*eliminate those positions that are partial (syn/nsyn) according to their probability (ex. if it is a Syn with 0.6 it has 0.4 to be NSyn and in that case will not be counted): FOR SIMULATIONS!!! */
        /* (not really correct, it is correlated to svratio, but approx ok): TOO COMPLEX, AVOID IT*/
       /**/
        length_seg->set_value(0);
        for(li=0;li<max_biasites;li++) {
            if((include_unknown->value() == 0 && (*matrix_pos)[li] >= 0) || (include_unknown->value() == 1)) {
                if(li==0 || (li > 0 && (long int)labs((*matrix_pos)[li]) != (long int)labs((*matrix_pos)[li])-1)) {
                    if((*vector_mask)[(long int)labs((*matrix_pos)[li])-1] == 1.0)
                        length_seg->add(1);
                    else {
                        if(ran1() < (*vector_mask)[(long int)labs((*matrix_pos)[li])-1]) {
                            length_seg->add(1);
                        }
                        else {
                            discarded[li] = 1;
                            /*(*vector_mask)[(long int)labs((*matrix_pos)[li])-1] = 0.;*/
                            /*(*matrix_pos)[li] = -999999999*/ /*-(long int)fabs((*matrix_pos)[li])*/;
                        }
                    }
                }
                /**/
                if(outgroup_presence->value() == 1) {
                    n2=0;
                    for(n=nsamtot->value()-(*nsamuser)[npops->value()-1];n<nsamtot->value();n++) {
                        if((*matrix_mask)[(unsigned int)n*(unsigned int)length->value()+(unsigned int)labs((*matrix_pos)[li])-1] == -1) {
                            n2 += 1;
                        }
                        else
                            break;
                    }
                    if(n2 == (*nsamuser)[npops->value()-1]) {
                        discarded[li] = 1;
                     }
                }
                /**/
            }
            
#if TOCONSIDER==0
            if(mhitbp[(long int)labs((*matrix_pos)[li])] == 1) { /*keep the highest frequency*/
                li2 = li + 1;
                while(mhitbp[(long int)labs((*matrix_pos)[li])] == mhitbp[(long int)labs((*matrix_pos)[li2])]) {
                    if((*matrix_freq)[li2] > (*matrix_freq)[li]) {
                        discarded[li] = 1;
                        li = li2;
                    }
                    else {
                        discarded[li2] = 1;
                    }
                    li2 += 1;
                }
                li = li2;
            }
#endif
        }
        /**/
        
        /*change '-1' values to '0' in matrix_mask if it is a VARIANT position AND includes '8' or '9' [format ms_e]*/
        /*discarded*/
        /*
        if(formatfile->value() == 2){
            for(li=0;li<max_biasites;li++) {
                if((*matrix_pos)[li] > 0) {
                    for(y=0;y<nsamtot->value()-!outgroup_presence->value();y++) 
                        matrix_mask2[y*length->value()+(*matrix_pos)[li]-1] = 0;
                }
            }
        }
        */
#if TOCONSIDER==1
        /*re-calculate the matrix_sv: 1:transition, 2:transversion*/
		for(li=0;li<max_biasites;li++) {
			if((*matrix_sv)[li] == 3) (*matrix_sv)[li] = 2;
		}
        
        nmhits->set_value(0);
        posmhitinit = -1;
        for(li=0;li<length->value();li++) {
            /*printf("\nmhitbp[%ld]=%ld",li+1,mhitbp[li+1]);*/
            if(mhitbp[li+1] == 1) {
                nmhits->add(1);
            }
        }
#endif
		/*recalculate matrix_pos: eliminate all discarded values. Also count the number of total positions*/
		li2 = 0;
		for(li=0;li<max_biasites;li++) {
            /*printf("\n(*matrix_pos)[%ld]=%ld\tdiscarded[%ld]=%ld",li,(*matrix_pos)[li],li,discarded[li]);*/
            if(discarded[li] == 0) {
 				(*matrix_pos)[li2] = (*matrix_pos)[li];
                for(y=0;y<nsamtot->value();y++)
                    (*matrix_pol)[li2*nsamtot->value()+y] = (*matrix_pol)[li*nsamtot->value()+y];
				li2++;
			}
		}
		for(li=li2;li<max_biasites;li++) {
			(*matrix_pos)[li] = -999999999;
            for(y=0;y<nsamtot->value();y++)
                (*matrix_pol)[li*nsamtot->value()+y] = '-';
		}
		
#if TOCONSIDER==1
        /*rename the positions of the (*matrix_pos) by the physical positions, if the information is included:*/
		if(physical) {
			for(li=0;li<max_biasites;li++) {
				if((*matrix_pos)[li] >= 0) {
					(*matrix_pos)[li] =  (long int)labs(matrix_phys[li]);
				}
				else {
					(*matrix_pos)[li] = -(long int)labs(matrix_phys[li]);
				}
			}
		}
#endif
		/*count number of total positions (excluding gaps and mhits) per line*/
		for(li=0;li<li2;li++) {
			for(y=0;y<nsamtot->value();y++) {
				if((*matrix_pol)[(li*nsamtot->value())+y] != '-')
					(*sum_sam)[y] += (double)1;
			}
		}
		
		/*calculate the number of positions per population considering or not the outgroup*/
		/*calculate nsites1_pop and nsites1_pop_outg*/
		for(y=0;y<npops->value()-!outgroup_presence->value();y++) {
			(*nsites1_pop)[y] = 0.;
			(*nsites1_pop_outg)[y] = 0.;
			(*nsites2_pop)[y] = 0.;
			(*nsites2_pop_outg)[y] = 0.;
			(*nsites3_pop)[y] = 0.;
			(*nsites3_pop_outg)[y] = 0.;
		}
		z = 0;
		for(y=0;y<npops->value()-1;y++) {
			(*anx)[y]  = (*bnx)[y]  = 0.0;
			(*anxo)[y] = (*bnxo)[y] = 0.0;
			for(xx=0;xx<length->value();xx++) {
				v = 0;
				for(x=z;x<z+(*nsamuser)[y];x++) {
					if((*matrix_mask)[x*length->value()+xx] == -1 || matrix_mask2[x*length->value()+xx] == -1) v += 1; /*number of Ns*/
				}
/*
				if(discarded[xx] == 0 && ((include_unknown->value() == 1 && (*vector_mask)[xx] > 0) ||
				   (include_unknown->value()==0 && v == 0 && (*vector_mask)[xx] > 0))) {
*/
                if(mhitbp[xx+1] != 1 &&
                   ((include_unknown->value() == 1 && (*vector_mask)[xx] > 0) ||
                    (include_unknown->value() == 0 && (*vector_mask)[xx] > 0  && v == 0))) {

                    if(v < (*nsamuser)[y])
						(*nsites1_pop)[y] += (*vector_mask)[xx];
					if(v < (*nsamuser)[y]-1) 
						(*nsites2_pop)[y] += (*vector_mask)[xx];
					if(v < (*nsamuser)[y]-2) 
						(*nsites3_pop)[y] += (*vector_mask)[xx];
					for(k=1;k<(*nsamuser)[y]-v;k++) {
						(*anx)[y] += 1.0/((double)k);
						(*bnx)[y] += 1.0/((double)k*(double)k);
					}
					p = 0;
					if(outgroup_presence->value() == 1) {
						for(x=nsamtot->value()-1;x>=nsamtot->value()-(*nsamuser)[npops->value()-1];x--)
							if(matrix_mask2[x*length->value()+xx] == -1 || (*matrix_mask)[x*length->value()+xx] == -1 ) p += 1;
						if(p < (*nsamuser)[npops->value()-1] && v < (*nsamuser)[y])
							(*nsites1_pop_outg)[y] += (*vector_mask)[xx];
						if(p < (*nsamuser)[npops->value()-1] && v < (*nsamuser)[y]-1)
							(*nsites2_pop_outg)[y] += (*vector_mask)[xx];
						if(p < (*nsamuser)[npops->value()-1] && v < (*nsamuser)[y]-2)
							(*nsites3_pop_outg)[y] += (*vector_mask)[xx];
						if(p < (*nsamuser)[npops->value()-1] && v < (*nsamuser)[y]) {
							for(k=1;k<(*nsamuser)[y]-v;k++) {
								(*anxo)[y] += 1.0/((double)k);
								(*bnxo)[y] += 1.0/((double)k*(double)k);
							}
						}
					}
				}
			}
			z += (*nsamuser)[y];
			/*(*nsites1_pop)[y] -= nmhits->value();
			(*nsites1_pop_outg)[y] -= nmhits->value();
			(*nsites2_pop)[y] -= nmhits->value();
			(*nsites2_pop_outg)[y] -= nmhits->value();*/
			if((*nsites2_pop)[y]>0) {
				(*anx)[y] /= (double)(*nsites2_pop)[y];
				(*bnx)[y] /= (double)(*nsites2_pop)[y];
			}
			if((*nsites2_pop_outg)[y]>0) {
				(*anxo)[y] /= (double)(*nsites2_pop_outg)[y];
				(*bnxo)[y] /= (double)(*nsites2_pop_outg)[y];
			}
		}

		
		/*calculate lengthamng*/
		for(y=0;y<npops->value()-1;y++) for(y2=y+1;y2<npops->value()-1;y2++) (*lengthamng)[y][y2] = 0.;
		for(xx=0;xx<length->value();xx++) {
			z = 0;
			for(y=0;y<npops->value()-1;y++) {
				v = 0;
				for(x=z;x<z+(*nsamuser)[y];x++) {
					if((*matrix_mask)[x*length->value()+xx] == -1 || matrix_mask2[x*length->value()+xx] == -1) v += 1;
				}
				z2 = 0; x= 0;
				while(x<y+1) {z2 += (*nsamuser)[x]; x++;}
				for(y2=y+1;y2<npops->value()-1;y2++) {
					v2 = 0;
					for(x=z2;x<z2+(*nsamuser)[y2];x++) {
						if((*matrix_mask)[x*length->value()+xx] == -1 || matrix_mask2[x*length->value()+xx] == -1) v2 += 1;
					}
					p = 0;
					if(mhitbp[xx]!=1 && ((include_unknown->value() == 1 && (*vector_mask)[xx] > 0) ||
					   (include_unknown->value()==0 && v == 0 && (*vector_mask)[xx] > 0))) {
						if(outgroup_presence->value() == 1) {
							for(x=nsamtot->value()-1;x>=nsamtot->value()-(*nsamuser)[npops->value()-1];x--) {
								if(matrix_mask2[x*length->value()+xx] == -1/**/ || (*matrix_mask)[x*length->value()+xx] == -1/**/) p += 1;
							}
							if(p < (*nsamuser)[npops->value()-1] && v < (*nsamuser)[y] && v2 < (*nsamuser)[y2]) 
								(*lengthamng)[y][y2] += (*vector_mask)[xx];
						}
						else {
							if(v < (*nsamuser)[y] && v2 < (*nsamuser)[y2]) 
								(*lengthamng)[y][y2] += (*vector_mask)[xx];
						}
					}
					z2 += (*nsamuser)[y2];
				}
				z += (*nsamuser)[y];
			}
		}
		/**/
#if TOCONSIDER==1
        free(matrix_phys);
#endif
        free(discarded);
		free(mhitbp);
        free(matrix_mask2);
		
		return; // 0;
	}
	else {
		printf("\nError: ms file finished abruptely.\n");
		exit(1);
	}
	
	return; // 1;
}

void CCalcMstatspopOpenMsFile::Finalize(void) {
  if (file_input_ != NULL) {
    fzclose(file_input_, &input_gz_);
    file_input_ = NULL;
  }

  if (calc_randomize_ != NULL) {
    manager()->all_calculations()->RemoveCalculationByName(
                                                      calc_randomize_->parent(),
                                                      calc_randomize_->name());
  }
  
  DM_DEL_ALL_LOCAL_DATA
}

double CCalcMstatspopOpenMsFile::ran1(void) {
  /// ==========================================================================
  /// RANDOMIZE CALCULATION
  /// ==========================================================================
  calc_randomize_->SetOutput(randomize_value_);
  calc_randomize_->Prepare();
  calc_randomize_->Calculate(manager()->all_commands()->dry_run());
  calc_randomize_->Finalize();

  return randomize_value_->value();
}


double CCalcMstatspopOpenMsFile::gammln(double zz) {
  /*Based on Numerical Recipes in C, Press et al. 1992. p. 213. and on
   Lanczos 1964 J. SIAM Numer. Anal. Ser. B, Vol. 1 pp 86-96.*/

  /*gamma distribution for a z integer*/
  double loggammaz;
  double z,logg,h,sumc;
  static double gamma = 5.0;
  static double c0 =  1.000000000178;
  static double c1 = 76.180091729406;
  static double c2 = 86.505320327112;
  static double c3 = 24.014098222230;
  static double c4 =  1.231739516140;
  static double c5 =  0.001208580030;
  static double c6 =  0.000005363820;

  if(zz <= 0.) {
    puts("Error gamma");
    return (double)NA_VALUE; //.
  }

  z = (double)zz;
  h = (double)sqrt(2. * PI);
  sumc = c0 + c1/(z+1.) - c2/(z+2.) + c3/(z+3.)  - c4/(z+4.) + c5/(z+5.) - c6/(z+6.);
  logg = (z + 0.5)*(double)log((double)(z + gamma + 0.5)) - (z + gamma + 0.5);
  loggammaz = log((double)h);
  loggammaz += logg + log((double)sumc);
  loggammaz -= log((double)z);

  return (double)loggammaz;
}

double CCalcMstatspopOpenMsFile::largebinomialdist(double pp, double n)
{
  /*Based on Numerical Recipes in C, Press et al. 1992 and on
   Fishman 1979 J. American Statistical Association Vol. 74, No. 366, pp 418-423*/

  double p,np;
  int N;
  double A,B,C,D,V,s;
  double g,plog,pclog,sq,angle,y,em,tt;

  if(pp > 0.5) p = (double)1.-pp;
  else p = pp;

  np = n * p;

  if(n==0) {
    puts("Error bindist");
    return (double)NA_VALUE; //.
  }
  if(p==(double)0) {
    if(pp > 0.5) return (double)n;
    return (double)0;
  }

  if(np < (double)10) {
    /*Rejection Method: BI Algorithm*/
    s = (double)1- p;
    A = (double)1;
    B = p/s;
    C = ((double)n+(double)1)*B;
    D = A;
    N = 0;
    V = ran1()/(double)pow(s,(double)n);
    while(V > A) {
      N++;
      D *= (C/(double)N - B);
      A += D;
      if(N > n) break;
    }
  }
  else { /*Rejection method with a Lorentzian comparison distribution*/
    g = gammln(n+1.);
    plog  = (double)log(p);
    pclog = (double)log((1.0 - p));
    sq = (double)sqrt(2.0*np*(1.0 - p));
    do {
      do {
        angle = PI*ran1();
        y = tan(angle);
        em=sq*y+np;
      } while(em < 0.0 || em >= (n + 1.0));
      em = floor(em);
      tt = 1.2*sq*(1.0+y*y)*exp(g-gammln(em+1.0) - gammln(n-em+1.0)+em*plog+(n-em)*pclog);
    } while(ran1() > tt);
    N = (int)em;
  }

  if(pp > 0.5) N = (int)n - N;
  return (double)N;
}

