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
 *  \brief     CCalcMstatspop.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 16, 2015
 *  \pre
 *  \bug
 *  \warning   Do not use std::cout in this calculation.
 *             Use fprintf(manager()->foutput(), message) instead.
 *             std::cout works but all mstatspop calculations use fprintf
 *             so, only one function must be used.
 */

#include "CCalcMstatspop.h"

#include <cmath>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */

#include "CCalcExec.h"

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"
#include "../../util/CFile.h"

// =============================================================================
// CALCULATIONS
// =============================================================================
/*
#include "../../calculations/CAllCalculations.h"
#include "../../calculations/Calc/CCalcOpenFastaFile.h"
#include "../../calculations/Calc/CCalcMstatspopOpenFastaFile.h"
#include "../../calculations/Calc/CCalcMstatspopOpenMsFile.h"
#include "../../calculations/Calc/CCalcFasta2DnaMatrix.h"
#include "../../calculations/Calc/CCalcDnaMatrix2MatrixPol.h"
#include "../../calculations/Calc/CCalcTOptimalTests.h"
#include "../../calculations/Calc/CCalcR2.h"
#include "../../calculations/Calc/CCalcR2p.h"
#include "../../calculations/Calc/CCalcFreqStats.h"
#include "../../calculations/Calc/CCalcMismatch.h"
#include "../../calculations/Calc/CCalcSxsfss.h"
#include "../../calculations/Calc/CCalcJointFreqDist.h"
#include "../../calculations/Calc/CCalcPiwpiafst.h"
#include "../../calculations/Calc/CCalcHwhafsth.h"
#include "../../calculations/Calc/CCalcFs.h"
#include "../../calculations/Calc/CCalcPermute.h"
#include "../../calculations/Calc/CCalcGFF.h"
#include "../../calculations/Calc/CCalcFileStats.h"
#include "../../calculations/Calc/CCalcOpenFreqSpecFile.h"
#include "../../calculations/Calc/CCalcMaskFileMs.h"
#include "../../calculations/Calc/CCalcEffecNucAndTCGAFreqs.h"
#include "../../calculations/Calc/CCalcLengthamngAndCalcs.h"
#include "../../calculations/Calc/CCalcX.h"
#include "../../calculations/Calc/CCalcY.h"
#include "../../calculations/Calc/CCalcZ.h"
#include "../../calculations/Calc/CCalcArrayOpeX.h"
#include "../../calculations/Calc/CCalcMstatspopOutput.h"
#include "../../calculations/Calc/CCalcOpenTFastaFile.h"
#include "../../calculations/Calc/CCalcOpenEffectSizesFile.h"
#include "../../calculations/Calc/CCalcOpenCoordinatesFile.h"
#include "../../calculations/Calc/CCalcOpenWeightPositionsFile.h"
*/

// =============================================================================
// DATA TYPES
// =============================================================================
#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataChar.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataCharMatrix.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataIntMatrix.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataInt64Matrix.h"
#include "../../data_manager/Data/CDataFloat.h"
#include "../../data_manager/Data/CDataFloatVector.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataDoubleVector.h"
#include "../../data_manager/Data/CDataDoubleMatrix.h"
#include "../../data_manager/Data/CDataDoubleCube.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataStringSet.h"

#include "../../commands/CAllCommands.h"

CCalcMstatspop::CCalcMstatspop()
: ICalculation(KeyString::CALC_MSTATSPOP,
               KeyString::CALC_MSTATSPOP_BRIEF_DESC,
               KeyString::CALC_MSTATSPOP_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(formatfile_,                                                 // Variable -f
                   MSTATSPOP_GROUP_GENERAL,                                     // Group
                   CCALCMSTATSPOP_FORMATFILE_,                                  // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_FORMAT_DESC,                                       // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   VALUE_0,                                                     // Default value
                   0,                                                           // Min. Value
                   10,                                                          // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(file_in_,                                                    // Variable -i
                   MSTATSPOP_GROUP_GENERAL,                                     // Group
                   CCALCMSTATSPOP_FILE_IN_,                                     // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_INPUT_DESC,                                        // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_INPUT_INFO(output_,                                                     // Variable -o
                   MSTATSPOP_GROUP_GENERAL,                                     // Group
                   CCALCMSTATSPOP_OUTPUT_,                                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_OUTPUT_DESC,                                       // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   VALUE_1,                                                     // Default value
                   0,                                                           // Min. Value
                   10,                                                          // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(populations_initial_,                                        // Variable -N
                   MSTATSPOP_GROUP_GENERAL,                                     // Group
                   CCALCMSTATSPOP_POPULATIONS_INITIAL_,                         // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_POP_DESC,                                          // Description
                   MSTATSPOP_POP_CALC_EXAMPLE,                                  // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_INPUT_INFO(b_outgroup_presence_,                                        // Variable -G
                   MSTATSPOP_GROUP_GENERAL_OPTIONAL,                            // Group
                   CCALCMSTATSPOP_OUTGROUP_PRESENCE_,                           // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_OUTGROUP_DESC,                                     // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   VALUE_0,                                                     // Default value
                   0,                                                           // Min. Value
                   1,                                                           // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(b_include_unknown_,                                          // Variable -u
                   MSTATSPOP_GROUP_GENERAL_OPTIONAL,                            // Group
                   CCALCMSTATSPOP_INCLUDE_UNKNOWN_,                             // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_INCL_UNKNO_DESC,                                   // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   VALUE_0,                                                     // Default value
                   0,                                                           // Min. Value
                   1,                                                           // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(out_file_name_,                                                   // Variable -T
                   MSTATSPOP_GROUP_GENERAL_OPTIONAL,                            // Group
                   CCALCMSTATSPOP_FILE_OUT_,                                    // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_PATHNAME_OUTPUT_FILE_DESC,                         // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   MSTATSPOP_PATHNAME_OUTPUT_FILE_DEF_VAL,                      // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(file_H1f_,                                                   // Variable -a
                   MSTATSPOP_GROUP_GENERAL_OPTIONAL,                            // Group
                   CCALCMSTATSPOP_FILE_H1F_,                                    // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_ALT_SFILE_DESC,                                    // Description
                   MSTATSPOP_ALT_SFILE_EXAMPLE,                                 // Example
                   MSTATSPOP_ALT_SFILE_ONLY,                                    // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(file_H0f_,                                                   // Variable -n
                   MSTATSPOP_GROUP_GENERAL_OPTIONAL,                            // Group
                   CCALCMSTATSPOP_FILE_H0F_,                                    // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_NULL_SFILE_DESC,                                   // Description
                   MSTATSPOP_NULL_SFILE_EXAMPLE,                                // Example
                   MSTATSPOP_NULL_SFILE_ONLY,                                   // Use only if
                   MSTATSPOP_NULL_SFILE_DEF_VAL,                                // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(r2i_ploidies_,                                               // Variable -P
                   MSTATSPOP_GROUP_GENERAL_OPTIONAL,                            // Group
                   CCALCMSTATSPOP_R2I_PLOIDIES_,                                // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_R2P_DESC,                                          // Description
                   MSTATSPOP_R2P_EXAMPLE,                                       // Example
                   MSTATSPOP_R2P_ONLY,                                          // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(sort_nsam_,                                                  // Variable -O
                   MSTATSPOP_GROUP_FA_TFA,                                      // Group
                   CCALCMSTATSPOP_SORT_NSAM_,                                   // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(niter_,                                                      // Variable -t
                   MSTATSPOP_GROUP_FA_TFA,                                      // Group
                   CCALCMSTATSPOP_NITER_,                                       // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_PERM_ITE_DESC,                                     // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(seed_,                                                       // Variable -s
                   MSTATSPOP_GROUP_FA_TFA,                                      // Group
                   CCALCMSTATSPOP_SEED_,                                        // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_SEED_DESC,                                         // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   MSTATSPOP_SEED_DEF_VAL,                                      // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(window_,                                                     // Variable -w
                   MSTATSPOP_GROUP_TFA,                                         // Group
                   CCALCMSTATSPOP_WINDOW_,                                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_WINDOW_SIZE_DESC,                                  // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(slide_,                                                      // Variable -z
                   MSTATSPOP_GROUP_TFA,                                         // Group
                   CCALCMSTATSPOP_SLIDE_,                                       // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_SLIDE_SIZE_DESC,                                   // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   MSTATSPOP_SLIDE_SIZE_DEF_VAL,                                // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(physical_length_,                                            // Variable -Y
                   MSTATSPOP_GROUP_TFA,                                         // Group
                   CCALCMSTATSPOP_PHYSICAL_LENGTH_,                             // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_WINDOW_LENGTHS_DESC,                               // Description
                   MSTATSPOP_WINDOW_LENGTHS_CALC_DESC,                          // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(file_wcoord_,                                                // Variable -W
                   MSTATSPOP_GROUP_TFA,                                         // Group
                   CCALCMSTATSPOP_FILE_WCOORD_,                                 // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_COORDS_FILE_DESC,                                  // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   MSTATSPOP_COORDS_FILE_DEF_VAL,                               // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(file_wps_,                                                   // Variable -E
                   MSTATSPOP_GROUP_TFA,                                         // Group
                   CCALCMSTATSPOP_FILE_WPS_,                                    // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_HEIGHTS_FILE_DESC,                                 // Description
                   MSTATSPOP_HEIGHTS_FILE_EXAMPLE,                              // Example
                   UNDEFINED_STRING,                                            // Use only if
                   MSTATSPOP_HEIGHTS_FILE_DEF_VAL,                              // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(length_,                                                     // Variable -l
                   MSTATSPOP_GROUP_MS,                                          // Group
                   CCALCMSTATSPOP_LENGTH_,                                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_LENGTH_DESC,                                       // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(niterdata_,                                                  // Variable -r
                   MSTATSPOP_GROUP_MS,                                          // Group
                   CCALCMSTATSPOP_NITERDATA_,                                   // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_MS_ITERATIONS_DESC,                                // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(file_mas_,                                                   // Variable -m
                   MSTATSPOP_GROUP_MS,                                          // Group
                   CCALCMSTATSPOP_FILE_MAS_,                                    // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_MASK_DESC,                                         // Description
                   MSTATSPOP_MASK_EXAMPLE,                                      // Example
                   UNDEFINED_STRING,                                            // Use only if
                   MSTATSPOP_MASK_DEF_VAL,                                      // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(ms_svratio_,                                                 // Variable -v
                   MSTATSPOP_GROUP_MS,                                          // Group
                   CCALCMSTATSPOP_MS_SVRATIO_,                                  // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_RATIOTRANS_DESC,                                   // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   MSTATSPOP_RATIOTRANS_DEF_VAL,                                // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(b_force_outgroup_,                                           // Variable -F
                   MSTATSPOP_GROUP_MS,                                          // Group
                   CCALCMSTATSPOP_FORCE_OUTGROUP_,                              // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_INCL_OUTGR_DESC,                                   // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   MSTATSPOP_INCL_OUTGR_VALUE_0,                                // Default value
                   0,                                                           // Min. Value
                   1,                                                           // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(freq_revert_,                                                // Variable -q
                   MSTATSPOP_GROUP_MS,                                          // Group
                   CCALCMSTATSPOP_FREQ_REVERT_,                                 // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_FREQREVMUT_DESC,                                   // Description
                   UNDEFINED_STRING,                                            // Example
                   MSTATSPOP_FREQREVMUT_ONLY,                                   // Use only if
                   MSTATSPOP_FREQREVMUT_DEF_VAL,                                // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(ploidy_,                                                     // Variable -p
                   MSTATSPOP_GROUP_FA,                                          // Group
                   CCALCMSTATSPOP_PLOIDY_,                                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_PLOIDY_CALC_DESC,                                  // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(file_GFF_,                                                   // Variable -g
                   MSTATSPOP_GROUP_FA,                                          // Group
                   CCALCMSTATSPOP_FILE_GFF_,                                    // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(subset_positions_,                                           // Variable
                   MSTATSPOP_GROUP_FA,                                          // Group
                   CCALCMSTATSPOP_SUBSET_POSITIONS_,                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(code_name_,                                                  // Variable
                   MSTATSPOP_GROUP_FA,                                          // Group
                   CCALCMSTATSPOP_CODE_NAME_,                                   // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(genetic_code_,                                               // Variable
                   MSTATSPOP_GROUP_FA,                                          // Group
                   CCALCMSTATSPOP_GENETIC_CODE_,                                // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(criteria_transcript_,                                        // Variable -c
                   MSTATSPOP_GROUP_FA,                                          // Group
                   CCALCMSTATSPOP_CRITERIA_TRANSCRIPT_,                         // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_CRITERIA_DESC,                                     // Description
                   UNDEFINED_STRING,                                            // Example
                   MSTATSPOP_CRITERIA_ONLY,                                     // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_INPUT_INFO(b_mask_print_,                                               // Variable -K
                   MSTATSPOP_GROUP_FA,                                          // Group
                   CCALCMSTATSPOP_MASK_PRINT_,                                  // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   MSTATSPOP_MASK_PRINT_DESC,                                   // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   MSTATSPOP_MASK_PRINT_DEF_VAL,                                // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
/*
    SET_INPUT_INFO(file_effsz_,                                                 // Variable
                   MSTATSPOP_GROUP_FA,                                          // Group
                   CCALCMSTATSPOP_FILE_EFFSZ_,                                  // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
*/

    SET_INPUT_INFO(scaffold_names_,                                              // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_SCAFFOLD_NAMES_,                              // Short Name
                   MSTATSPOP_SCAFFOLD_NAME_LONG,                                // Long Name
                   MSTATSPOP_SCAFFOLD_NAME_DESC,                                // Description
                   MSTATSPOP_SCAFFOLD_NAME_EXAMPLE,                             // Example
                   UNDEFINED_STRING,                                            // Use only if
                   MSTATSPOP_SCAFFOLD_NAME_DEF_VAL,                             // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required

    SET_INPUT_INFO(keep_intermediate_results,                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALC_ALL_KEEP_INTERMEDIATE_RESULTS,                         // Short Name
                   CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_LONG,                    // Long Name
                   CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_DESC,                    // Description
                   CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_SAMP,                    // Example
                   CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_ONLY,                    // Use only if
                   CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_DEFV,                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(file_chr_name_all_,                                           // Variable
                   UNDEFINED_STRING,                                          // Group
                   UNDEFINED_STRING,                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(kind_length_,                                           // Variable
                   UNDEFINED_STRING,                                          // Group
                   UNDEFINED_STRING,                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(freq_missing_ms_,                                           // Variable
                   UNDEFINED_STRING,                                          // Group
                   UNDEFINED_STRING,                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(n_ccov_,                                           // Variable
                   UNDEFINED_STRING,                                          // Group
                   UNDEFINED_STRING,                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(location_missing_ms_,                                           // Variable
                   UNDEFINED_STRING,                                          // Group
                   UNDEFINED_STRING,                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(first_slide_,                                           // Variable
                   UNDEFINED_STRING,                                          // Group
                   UNDEFINED_STRING,                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
  
    //!mstatspop_outputs
  
    SET_OUTPUT_INFO(calc_output_,                                               // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_OUTPUT_,                                 // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
/*
    SET_OUTPUT_INFO(out_stats_So_,                                              // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_SO_OUTPUT_,                        // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaSo_,                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_OUTPUT_,                     // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaTo_,                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_NT_TAJ_OUTPUT_,              // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaFL_,                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_NT_FULI_OUTPUT_,             // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaFW_,                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_NT_FAYWU_OUTPUT_,            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaL_,                                          // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_NT_ZENG_OUTPUT_,             // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaSA_,                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_NT_ACHAZ_WAT_OUTPUT_,        // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaTA_,                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_NT_ACHAZ_TAJ_OUTPUT_,        // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_K_,                                               // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_DIVERGENCE_NT_OUTPUT_,             // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaTHKY_,                                       // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_NT_TAJ_HKY_OUTPUT_,          // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_KHKY_,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_KHKY_OUTPUT_,                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaS_,                                          // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_S_OUTPUT_,                   // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaT_,                                          // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_T_OUTPUT_,                   // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_hapw_,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_HAPW_OUTPUT_,                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_nhpop_,                                           // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_NHPOP_OUTPUT_,                     // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_Dtaj_,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_DTAJ_OUTPUT_,                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_Dfl_,                                             // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_DFL_OUTPUT_,                       // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_Ffl_,                                             // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_FFL_OUTPUT_,                       // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_Hnfw_,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_NHFW_OUTPUT_,                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_Ez_,                                              // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_EZ_OUTPUT_,                        // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_Yach_,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_YACH_OUTPUT_,                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_FH_,                                              // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_FH_OUTPUT_,                        // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_Fs_,                                              // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_FS_OUTPUT_,                        // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_mdsd_,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_MDSD_OUTPUT_,                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_mdg1_,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_MDG1_OUTPUT_,                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_mdg2_,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_MDG2_OUTPUT_,                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_fst1all_,                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_FST1ALL_OUTPUT_,                   // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_fsth_,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_FSTH_OUTPUT_,                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_fstHKY_,                                          // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_FSTHKY_OUTPUT_,                    // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_piwHKY_,                                          // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_PIWHKY_OUTPUT_,                    // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_piaHKY_,                                          // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_PIAHKY_OUTPUT_,                    // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
*/  
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcMstatspop::~CCalcMstatspop() {
}

void CCalcMstatspop::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(formatfile_)                                                       //-f
    DM_INPUT(file_in_)                                                          //-i
    DM_INPUT(output_)                                                           //-o
    DM_INPUT(populations_initial_)                                              //-N
    DM_INPUT(b_outgroup_presence_)                                              //-G
    DM_INPUT(b_include_unknown_)                                                //-u
    DM_INPUT(out_file_name_)                                                    //-T
    DM_INPUT(file_H1f_)                                                         //-a
    DM_INPUT(file_H0f_)                                                         //-n
    DM_INPUT(r2i_ploidies_)                                                     //-P
    DM_INPUT(sort_nsam_)                                                        //-O
    DM_INPUT(niter_)                                                            //-t
    DM_INPUT(seed_)                                                             //-s
    DM_INPUT(window_)                                                           //-w
    DM_INPUT(slide_)                                                            //-z
    DM_INPUT(physical_length_)                                                  //-Y
    DM_INPUT(file_wcoord_)                                                      //-W
    DM_INPUT(file_wps_)                                                         //-E
    DM_INPUT(length_)                                                           //-l
    DM_INPUT(niterdata_)                                                        //-r
    DM_INPUT(file_mas_)                                                         //-m
    DM_INPUT(ms_svratio_)                                                       //-v
    DM_INPUT(b_force_outgroup_)                                                 //-F
    DM_INPUT(freq_revert_)                                                      //-q
    DM_INPUT(ploidy_)                                                           //-p
    DM_INPUT(file_GFF_)                                                         //-g
    DM_INPUT(subset_positions_)
    DM_INPUT(code_name_)
    DM_INPUT(genetic_code_)
    DM_INPUT(criteria_transcript_)                                              //-c
    DM_INPUT(b_mask_print_)                                                     //-K
    DM_INPUT(scaffold_names_)

//    DM_INPUT(file_effsz_)                                                       //
    DM_INPUT(keep_intermediate_results)
  DM_GET_OUTPUTS
    DM_OUTPUT(calc_output_)
/*
    DM_OUTPUT(out_stats_So_)
    DM_OUTPUT(out_stats_thetaSo_)
    DM_OUTPUT(out_stats_thetaTo_)
    DM_OUTPUT(out_stats_thetaFL_)
    DM_OUTPUT(out_stats_thetaFW_)
    DM_OUTPUT(out_stats_thetaL_)
    DM_OUTPUT(out_stats_thetaSA_)
    DM_OUTPUT(out_stats_thetaTA_)
    DM_OUTPUT(out_stats_K_)
    DM_OUTPUT(out_stats_thetaTHKY_)
    DM_OUTPUT(out_stats_KHKY_)
    DM_OUTPUT(out_stats_thetaS_)
    DM_OUTPUT(out_stats_thetaT_)
    DM_OUTPUT(out_stats_hapw_)
    DM_OUTPUT(out_stats_nhpop_)
    DM_OUTPUT(out_stats_Dtaj_)
    DM_OUTPUT(out_stats_Dfl_)
    DM_OUTPUT(out_stats_Ffl_)
    DM_OUTPUT(out_stats_Hnfw_)
    DM_OUTPUT(out_stats_Ez_)
    DM_OUTPUT(out_stats_Yach_)
    DM_OUTPUT(out_stats_FH_)
    DM_OUTPUT(out_stats_Fs_)
    DM_OUTPUT(out_stats_mdsd_)
    DM_OUTPUT(out_stats_mdg1_)
    DM_OUTPUT(out_stats_mdg2_)
    DM_OUTPUT(out_stats_fst1all_)
    DM_OUTPUT(out_stats_fsth_)
    DM_OUTPUT(out_stats_fstHKY_)
    DM_OUTPUT(out_stats_piwHKY_)
    DM_OUTPUT(out_stats_piaHKY_)
*/
  DM_END
  

    // How to decide the output file name?

    // If user sets the -T option, the output file name is this -T option.
    if (out_file_name_->value() != "") { //<<<< this is the -T option
        calc_output_->set_value(out_file_name_->value());
    }
    else {
        // If user sets the output to a file with a name, then the output file name will be this one.
        if (calc_output_->value() != "") {
            // calc_output_->set_value(calc_output_->value());
        }
        else {
            // If user sets an input file then the output file will be the path of the input file + "statistics.txt".
            if (file_in_->value() != "") {
                calc_output_->set_value(CFile::GetPathFromFileName(file_in_->value()) + "statistics.txt");
            }
        }
    }
 
    // Then, if keep intermediate results is true, the "_<ite_number>_<ite_value>" must be inserted before the last ".".
    // the <ite_value> could have a path, so this function must be used: GetFileNameWithoutExtension

    if (keep_intermediate_results->value()) {
        DM_ITERATION_NUMBER(iteration_number)
        DM_ITERATION_VALUE(iteration_value)
        calc_output_->set_value(CFile::ConcatenateIterationToFilePathName
                                    (
                                        calc_output_->value(),
                                        iteration_number->value(),
                                        CFile::GetFileNameWithoutExtension(iteration_value->value())
                                    )
                                );
  }  



/*
*****************************************
*****************************************
*****************************************
*****************************************
*****************************************

/// ============================================================================
/// START WRITING OUTPUT TO THE OUTPUT FILE
/// ============================================================================
  if (file_out_->value() != "") {
    manager()->RedirectCoutToFile(file_out_->value());
  } 
  
  // The output of this calc is printed to the screen or into a text file.
  // If it is into a text file then let's set the file name to the output of
  // this calc:
  if (calc_output_ != NULL) {
    calc_output_->set_value(file_out_->value());
  }
  
  
/// ============================================================================
/// CALCS
/// ============================================================================
  DM_NEW_CALC(calc_mstatspop_open_fasta_)
  DM_NEW_CALC(calc_mstatspop_open_ms_)
  DM_NEW_CALC(calc_optimal_tests_)
  DM_NEW_CALC(calc_r2_)
  DM_NEW_CALC(calc_r2p_)
  DM_NEW_CALC(calc_freq_stats_)
  DM_NEW_CALC(calc_mismatch_)
  DM_NEW_CALC(calc_sxsfss_)
  DM_NEW_CALC(calc_joint_freq_dist_)
  DM_NEW_CALC(calc_piwpiafst_1_)
  DM_NEW_CALC(calc_piwpiafst_2_)
  DM_NEW_CALC(calc_piwpiafst_3_)
  DM_NEW_CALC(calc_hwhafsth_1_)
  DM_NEW_CALC(calc_hwhafsth_2_)
  DM_NEW_CALC(calc_hwhafsth_3_)
  DM_NEW_CALC(calc_fs_)
  DM_NEW_CALC(calc_permute_2_)
  DM_NEW_CALC(calc_permute_3_)
  DM_NEW_CALC(calc_gff_)
  DM_NEW_CALC(calc_file_stats_)
  DM_NEW_CALC(calc_open_freq_spec_file_)
  DM_NEW_CALC(calc_mask_file_ms_)
  DM_NEW_CALC(calc_effec_nuc_TCGA_freqs_)
  DM_NEW_CALC(calc_lengthamng_and_calcs_)
  DM_NEW_CALC(calc_x_)
  DM_NEW_CALC(calc_y_)
  DM_NEW_CALC(calc_z_)
  DM_NEW_CALC(calc_array_ope_x_)
  DM_NEW_CALC(calc_mstatspop_output_)
  DM_NEW_CALC(calc_array_sum_all_)
  DM_NEW_CALC(calc_duplicate_populations_)
  DM_NEW_CALC(calc_tfasta_)
  DM_NEW_CALC(calc_effect_sizes_)
  DM_NEW_CALC(calc_coordinates_)
  DM_NEW_CALC(calc_weight_positions_)
     
/// ============================================================================
/// DATAS
/// ============================================================================
  DM_NEW_DATA(npops_)
  DM_NEW_DATA(vint_perpop_nsam_)
  DM_NEW_DATA(include_unknown_)
  DM_NEW_DATA(force_outgroup_)
  DM_NEW_DATA(outgroup_presence_)
  DM_NEW_DATA(gfffiles_)
  DM_NEW_DATA(H0frq_)
  DM_NEW_DATA(H1frq_)
  DM_NEW_DATA(mask_print_)
  DM_NEW_DATA(length_al_)
  DM_NEW_DATA(int_total_nsam_order_)
  DM_NEW_DATA(numPloidies_)
  DM_NEW_DATA(result_)
  DM_NEW_DATA(fasta_)
  DM_NEW_DATA(vint_perpop_nsam_iter_);
  DM_NEW_DATA(npops_iter_);
  DM_NEW_DATA(int_total_nsam_iter_);
  DM_NEW_DATA(dna_matrix_)
  DM_NEW_DATA(matrix_sizepos_)
  DM_NEW_DATA(matrix_segrpos_)
  DM_NEW_DATA(matrix_pol_)
  DM_NEW_DATA(matrix_pol_tcga_)
  DM_NEW_DATA(frequencies_)
  DM_NEW_DATA(positions_)
  DM_NEW_DATA(sites_)
  DM_NEW_DATA(sanc_)
  DM_NEW_DATA(matrix_perm_)
  DM_NEW_DATA(nsam2_)
  DM_NEW_DATA(psam2_)
  DM_NEW_DATA(argc_)
  DM_NEW_DATA(vector_mask_)
  DM_NEW_DATA(length_mask_)
  DM_NEW_DATA(length_mask_real_)
  DM_NEW_DATA(matrix_mask_)
  DM_NEW_DATA(vector_priors_)
  DM_NEW_DATA(npriors_)
  DM_NEW_DATA(sum_sam_mask_)
  DM_NEW_DATA(length_seg_)
  DM_NEW_DATA(mhitbp_)
  DM_NEW_DATA(names2_)
  DM_NEW_DATA(n_site_)
  DM_NEW_DATA(DNA_matr2_)
  DM_NEW_DATA(n_samp_)
  DM_NEW_DATA(flaghky_)
  DM_NEW_DATA(flaghky0_)
  DM_NEW_DATA(jfd_)
  DM_NEW_DATA(nfd_)
  DM_NEW_DATA(li_)
  DM_NEW_DATA(anx_)
  DM_NEW_DATA(bnx_)
  DM_NEW_DATA(anxo_)
  DM_NEW_DATA(bnxo_)
  DM_NEW_DATA(lengthamng_)
  DM_NEW_DATA(missratio_)
  DM_NEW_DATA(nsites1_pop_)
  DM_NEW_DATA(nsites2_pop_)
  DM_NEW_DATA(nsites3_pop_)
  DM_NEW_DATA(nsites1_pop_outg_)
  DM_NEW_DATA(nsites2_pop_outg_)
  DM_NEW_DATA(nsites3_pop_outg_)
  DM_NEW_DATA(sum_sam_)
  DM_NEW_DATA(svratio_)
  DM_NEW_DATA(tcga_)
  DM_NEW_DATA(length_al_real_)
  DM_NEW_DATA(nmhits_)
  DM_NEW_DATA(matrix_sv_)
  DM_NEW_DATA(z_pos_)
  DM_NEW_DATA(mdw_reg_lengths_)
  DM_NEW_DATA(int_total_nsam_)
  DM_NEW_DATA(wV_)
  DM_NEW_DATA(Pp_)
  DM_NEW_DATA(nV_)
  DM_NEW_DATA(wgenes_)
  DM_NEW_DATA(nwindows_)
  DM_NEW_DATA(wP_)
  DM_NEW_DATA(wPV_)
  DM_NEW_DATA(wlimit_end_)
  DM_NEW_DATA(welimit_end_)
  DM_NEW_DATA(location_missing_ms_)
  DM_NEW_DATA(kind_length_)
  DM_NEW_DATA(freq_missing_ms_)
  DM_NEW_DATA(n_ccov_)
  DM_NEW_DATA(nsamuser_eff_)
  DM_NEW_DATA(beg_)
    
/// ============================================================================
/// DATAS - STATS
/// ============================================================================
  for (int i = 0; i < 2; i++) {
    DM_NEW_DATA2(stats_piw_, i)
    DM_NEW_DATA2(stats_pia_, i)
    DM_NEW_DATA2(stats_piT_, i)
    DM_NEW_DATA2(stats_piant_, i)
    DM_NEW_DATA2(stats_piTnt_, i)
    DM_NEW_DATA2(stats_fst_, i)
    DM_NEW_DATA2(stats_piwHKY_, i)
    DM_NEW_DATA2(stats_piaHKY_, i)
    DM_NEW_DATA2(stats_piTHKY_, i)
    DM_NEW_DATA2(stats_fstHKY_, i)
    DM_NEW_DATA2(stats_fst1all_, i)
    DM_NEW_DATA2(stats_Gst_, i)
    DM_NEW_DATA2(stats_hapw_, i)
    DM_NEW_DATA2(stats_hapa_, i)
    DM_NEW_DATA2(stats_hapT_, i)
    DM_NEW_DATA2(stats_fsth_, i)
    DM_NEW_DATA2(stats_fsth1all_, i)
    DM_NEW_DATA2(stats_fstALL_, i)
    DM_NEW_DATA2(stats_fsthALL_, i)
    DM_NEW_DATA2(stats_GstALL_, i)
    DM_NEW_DATA2(stats_S_, i)
    DM_NEW_DATA2(stats_So_, i)
    DM_NEW_DATA2(stats_thetaS_, i)
    DM_NEW_DATA2(stats_thetaSo_, i)
    DM_NEW_DATA2(stats_thetaT_, i)
    DM_NEW_DATA2(stats_thetaTo_, i)
    DM_NEW_DATA2(stats_thetaTHKY_, i)
    DM_NEW_DATA2(stats_thetaFL_, i)
    DM_NEW_DATA2(stats_thetaFW_, i)
    DM_NEW_DATA2(stats_thetaL_, i)
    DM_NEW_DATA2(stats_thetaSA_, i)
    DM_NEW_DATA2(stats_thetaTA_, i)
    DM_NEW_DATA2(stats_K_, i)
    DM_NEW_DATA2(stats_KHKY_, i)
    DM_NEW_DATA2(stats_Dtaj_, i)
    DM_NEW_DATA2(stats_Dfl_, i)
    DM_NEW_DATA2(stats_Ffl_, i)
    DM_NEW_DATA2(stats_Hnfw_, i)
    DM_NEW_DATA2(stats_Ez_, i)
    DM_NEW_DATA2(stats_Yach_, i)
    DM_NEW_DATA2(stats_FH_, i)
    DM_NEW_DATA2(stats_R2_, i)
    DM_NEW_DATA2(stats_Fs_, i)
    DM_NEW_DATA2(stats_Rm_, i)
    DM_NEW_DATA2(stats_ZnA_, i)
    DM_NEW_DATA2(stats_freq_, i)
    DM_NEW_DATA2(stats_nh_, i)
    DM_NEW_DATA2(stats_nhpop_, i)
    DM_NEW_DATA2(stats_freqh_, i)
    DM_NEW_DATA2(stats_length_, i)
    DM_NEW_DATA2(stats_length2_, i)
    DM_NEW_DATA2(stats_lengthamng_, i)
    DM_NEW_DATA2(stats_total_length_, i)
    DM_NEW_DATA2(stats_total_real_length_, i)
    DM_NEW_DATA2(stats_total_svratio_, i)
    DM_NEW_DATA2(stats_total_tcga_, i)
    DM_NEW_DATA2(stats_tcga_, i)
    DM_NEW_DATA2(stats_sv_, i)
    DM_NEW_DATA2(stats_svT_, i)
    DM_NEW_DATA2(stats_nmhits_, i)
    DM_NEW_DATA2(stats_H0freq_, i)
    DM_NEW_DATA2(stats_H1freq_, i)
    DM_NEW_DATA2(stats_thetaH0_, i)
    DM_NEW_DATA2(stats_thetaH1_, i)
    DM_NEW_DATA2(stats_ToH0_ii_, i)
    DM_NEW_DATA2(stats_ToH0_00_, i)
    DM_NEW_DATA2(stats_To_ii_, i)
    DM_NEW_DATA2(stats_To_00_, i)
    DM_NEW_DATA2(stats_To_i0_, i)
    DM_NEW_DATA2(stats_To_Qc_ii_, i)
    DM_NEW_DATA2(stats_To_Qw_ii_, i)
    DM_NEW_DATA2(stats_To_Lc_ii_, i)
    DM_NEW_DATA2(stats_mdsd_, i)
    DM_NEW_DATA2(stats_mdg1_, i)
    DM_NEW_DATA2(stats_mdg2_, i)
    DM_NEW_DATA2(stats_mdw_, i)
    DM_NEW_DATA2(stats_linefreq_, i)
    DM_NEW_DATA2(stats_anx_, i)
    DM_NEW_DATA2(stats_bnx_, i)
    DM_NEW_DATA2(stats_anxo_, i)
    DM_NEW_DATA2(stats_bnxo_, i)
    DM_NEW_DATA2(stats_R2p_, i)
  }

/// ============================================================================
/// DATAS - PROBS
/// ============================================================================
  DM_NEW_DATA(piter_i_)
  DM_NEW_DATA(piter_ih_)
  DM_NEW_DATA(piter_igh_)
  DM_NEW_DATA(piter_i1_)
  DM_NEW_DATA(piter_ih1_)
  DM_NEW_DATA(piter_niteri_)
  DM_NEW_DATA(piter_niterih_)
  DM_NEW_DATA(piter_niterigh_)
  DM_NEW_DATA(piter_niteri1_)
  DM_NEW_DATA(piter_niterih1_)
  DM_NEW_DATA(piter_iall_)
  DM_NEW_DATA(piter_ihall_)
  DM_NEW_DATA(piter_ighall_)
  DM_NEW_DATA(piter_niteriall_)
  DM_NEW_DATA(piter_niterihall_)
  DM_NEW_DATA(piter_niterighall_)
  
          
  if (keep_intermediate_results->value()) {
    if (file_out_->value() != "") {
        DM_ITERATION_NUMBER(iteration_number)
        DM_ITERATION_VALUE(iteration_value)
        file_out_->set_value(CFile::ConcatenateIterationToFilePathName(file_out_->value(),
                                iteration_number->value(),
                                iteration_value->value()));
    }
  }
  
/// ============================================================================
/// DATA - Default Values
/// ============================================================================

  if (formatfile_->auto_created()) {                                            //-f
    formatfile_->set_value(TFASTA_FILE);
  }
//  if(file_in_->auto_created()) {                                              //-i Required
//  }
  if(output_->auto_created()) {                                                 //-o
    output_->set_value(1);
  }
//  if(populations_initial_->auto_created()) {                                  //-N Required
//  }
  if(b_outgroup_presence_->auto_created()) {                                    //-G
    b_outgroup_presence_->set_value(0);
  }
  if(b_include_unknown_->auto_created()) {                                      //-u
    b_include_unknown_->set_value(0);
  }
  if(file_out_->auto_created()) {                                               //-T
    // default value is stdout. file_out_
  }
  if(file_H1f_->auto_created()) {                                               //-a
  }
  if(file_H0f_->auto_created()) {                                               //-n
  }
  if(r2i_ploidies_->auto_created()) {                                           //-P
  }
  if(sort_nsam_->auto_created()) {                                              //-O
  }
  if(niter_->auto_created()) {                                                  //-t
    niter_->set_value(0);
  }
  if(seed_->auto_created()) {                                                   //-s
    seed_->set_value(123456);
  }
  if(window_->auto_created()) {                                                 //-w
  }
  if(slide_->auto_created()) {                                                  //-z
    slide_->set_value(window_->value());
  }
  if(physical_length_->auto_created()) {                                        //-Y
    physical_length_->set_value(1);
  }
  if(file_wcoord_->auto_created()) {                                            //-W
    // Default is one whole window
  }
  if(file_wps_->auto_created()) {                                               //-E
    // Default all 1.000
  }
  if(length_->auto_created()) {                                                 //-l
  }
  if(niterdata_->auto_created()) {                                              //-r
    niterdata_->set_value(1);
  }
  if(file_mas_->auto_created()) {                                               //-m
    file_mas_->set_value("-1"); // Default is no mask
  }
  if(ms_svratio_->auto_created()) {                                             //-v
    ms_svratio_->set_value(0.5);
  }
  if(b_force_outgroup_->auto_created()) {                                       //-F
    b_force_outgroup_->set_value(0);
  }
  if(freq_revert_->auto_created()) {                                            //-q
    freq_revert_->set_value(0);
  }
  if(ploidy_->auto_created()) {                                                 //-p
    ploidy_->set_value(HAPLOID);
  }
  if(file_GFF_->auto_created()) {                                               //-g
    // Default is no annotation
  }
  if(subset_positions_->auto_created()) {
  }
  if(code_name_->auto_created()) {
  }
  if(genetic_code_->auto_created()) {
  }
  if(criteria_transcript_->auto_created()) {                                    //-c
    criteria_transcript_->set_text_string(STR(CRITERIA_TRANSCRIPT_MAX));
  }
  if(b_mask_print_->auto_created()) {                                           //-K
    b_mask_print_->set_value(0);
  }
  if(file_effsz_->auto_created()) {                                             //
  }
      
/// ============================================================================
/// INPUT TRANSFORMATIONS
/// ============================================================================
   
  include_unknown_->set_value(b_include_unknown_->value()?1:0);
  force_outgroup_->set_value(b_force_outgroup_->value()?1:0);
  outgroup_presence_->set_value(b_outgroup_presence_->value()?1:0);
  gfffiles_->set_value((file_GFF_->value() != "")?1:0);
  H0frq_->set_value((file_H0f_->value() != "")?1:0);
  H1frq_->set_value((file_H1f_->value() != "")?1:0);
  mask_print_->set_value(b_mask_print_->value()?1:0);
  length_al_->set_value(static_cast<double>(length_->value()));
  int_total_nsam_order_->set_value(sort_nsam_->reg_length());
  numPloidies_->set_value(r2i_ploidies_->reg_length());
 
  

  
  DM_GET_DATA3(CDataInt64, idum_, STR(IDUM))
  idum_->set_value(-1*seed_->value());
 

  
//  for(auto it = options()->GetFirstOptionIterator();
//    it != options()->GetLastOptionIterator(); ++it) {
//  }
  
  
  /// ============================================================================
  /// VALIDATIONS
  /// ============================================================================
  bool parseResult = true;

  //
  // Validate that populations is defined:
  //
  if (populations_initial_->value() == "") {
    ERROR_MSG << STR(POPULATIONS_NOT_DEF) END_MSG;
    parseResult = false;
  }

  //
  // Validate that force_outgroup and outgroup_presence are not equal to 1 at the
  // same time:
  //
  if ((b_force_outgroup_->value() == 1) && (b_outgroup_presence_->value() == 1)) {
    ERROR_MSG << STR(FORCE_AND_OUTGROUP_ERROR) END_MSG;
    parseResult = false;
  }

  //
  // Validate outgroup_presence_:
  //
  if ((b_outgroup_presence_->value() != 0) && (b_outgroup_presence_->value() != 1)) {
    ERROR_MSG << STR(OUTGROUP_PRESENCE_ERROR) END_MSG;
    parseResult = false;
  }

  //
  // Validate force_outgroup_:
  //
  if ((b_force_outgroup_->value() != 0) && (b_force_outgroup_->value() != 1)) {
    ERROR_MSG << STR(FORCE_OUTGROUP_ERROR) END_MSG;
    parseResult = false;
  }

  //
  // Validate formatfile_ with force_outgroup_:
  //
  if(!(formatfile_->value() == MS_FILE || formatfile_->value() == MS_X_FILE) 
      && b_force_outgroup_->value() == 1) {
    ERROR_MSG << STR(FORMATFILE_FORCE_OUTGROUP_ERROR) END_MSG;
    parseResult = false;
  }

  //
  // Validate output:
  //
  if ((output_->value() < 0) || (output_->value() > 10)) {
    ERROR_MSG << STR(OUTPUT_ERROR) END_MSG;
    parseResult = false;
  }

  //
  // Validate physical_length_:
  //
  if ((physical_length_->value() != 0) && (physical_length_->value() != 1)) {
    ERROR_MSG << STR(PHYSICAL_LENGTH_ERROR) END_MSG;
    parseResult = false;
  }      

  //
  // Validate npops_:
  //
  // if (npops_->value() == 0) {
  if (populations_initial_->value() == "") {
    ERROR_MSG << STR(NPOPS_ERROR) END_MSG;
    parseResult = false;
  }

  //
  // Validate window_:
  //
  if ((window_->value() <= 0) && (formatfile_->value() == TFASTA_FILE) && (file_wcoord_->value() == "")) {
    ERROR_MSG << STR(WINDOW_ERROR) END_MSG;
    parseResult = false;
  }

  //
  // Validate slide_:
  //  
  if ((slide_->value() == 0) && (window_->value() > 0)) {
    slide_->set_value(window_->value());
  }

  if ((slide_->value() < window_->value()) &&
      (formatfile_->value() == TFASTA_FILE)) {
    ERROR_MSG << STR(SLIDE_ERROR) END_MSG;
    parseResult = false;
  }

  //
  // Validate length_:
  //
  if ((length_->value() == 0) && (formatfile_->value() == MS_FILE)) {
    ERROR_MSG << STR(LENGTH_ERROR) END_MSG;
    parseResult = false;
  }

  //
  // Validate format_file_ with niterdata_:
  //
  if ((formatfile_->value() == FASTA_FILE) && (niterdata_->value() > 1)) {
    ERROR_MSG << STR(FORMATFILE_AND_NITERDATA_ERROR) END_MSG;
    parseResult = false;
  } 

****************************
****************************
****************************
****************************
*/
}

/*
void CCalcMstatspop::MultiplyPopulationsDependingOnPloidy(void) {
  /// ==========================================================================
  /// MULTIPLY POPULATIONS (BY 2 IF DIPLOID,...) EXCEPT THE OUTGROUP POP.
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_duplicate_populations_->SetInput(npops_);
    calc_duplicate_populations_->SetInput(ploidy_);
    calc_duplicate_populations_->SetInput(outgroup_presence_);
    calc_duplicate_populations_->SetInput(formatfile_);
    calc_duplicate_populations_->SetOutput(vint_perpop_nsam_);
    calc_duplicate_populations_->SetOutput(int_total_nsam_);
    calc_duplicate_populations_->Prepare();
  }
  calc_duplicate_populations_->Calculate(manager()->all_commands()->dry_run());
  calc_duplicate_populations_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::GetSumOfPopulations(void) {
  /// ==========================================================================
  /// SUM ALL ARRAY VALUES
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_array_sum_all_->SetInput(vint_perpop_nsam_);
    calc_array_sum_all_->SetInput(npops_);
    calc_array_sum_all_->SetOutput(int_total_nsam_);
    calc_array_sum_all_->Prepare();
  }
  calc_array_sum_all_->Calculate(manager()->all_commands()->dry_run());
  calc_array_sum_all_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcMdwRegLengths(void) {
  /// ==========================================================================
  /// input:  [x][x]...[x]]
  /// output: [(x*x-1)/2][(x*x-1)/2]...[(x*x-1)/2]
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_array_ope_x_->SetInput(ploidy_);
    calc_array_ope_x_->SetInput(include_unknown_);
    calc_array_ope_x_->SetInput(force_outgroup_);
    calc_array_ope_x_->SetInput(outgroup_presence_);
    calc_array_ope_x_->SetInput(vint_perpop_nsam_);
    calc_array_ope_x_->SetInput(npops_);
    calc_array_ope_x_->SetInput(int_total_nsam_);
    calc_array_ope_x_->SetOutput(mdw_reg_lengths_);
    calc_array_ope_x_->Prepare();
  }
  calc_array_ope_x_->Calculate(manager()->all_commands()->dry_run());
  calc_array_ope_x_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::OpenAlternativeAndFreqSpectrumFile(void) {
  /// ==========================================================================
  /// OPEN ALTERNATIVE AND NULL FREQUENCY SPECTRUM FILE
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_open_freq_spec_file_->SetInput(ploidy_);
    calc_open_freq_spec_file_->SetInput(vint_perpop_nsam_);
    calc_open_freq_spec_file_->SetInput(npops_);
    calc_open_freq_spec_file_->SetInput(file_H1f_);
    calc_open_freq_spec_file_->SetInput(file_H0f_);
    calc_open_freq_spec_file_->SetOutput(stats_H1freq_[0]);
    calc_open_freq_spec_file_->SetOutput(stats_thetaH1_[0]);
    calc_open_freq_spec_file_->SetOutput(stats_H0freq_[0]);
    calc_open_freq_spec_file_->SetOutput(stats_thetaH1_[0]);
    calc_open_freq_spec_file_->SetOutput(H1frq_);
    calc_open_freq_spec_file_->SetOutput(H0frq_);
    calc_open_freq_spec_file_->Prepare();
  }
  calc_open_freq_spec_file_->Calculate(manager()->all_commands()->dry_run());
  calc_open_freq_spec_file_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::ReadFastaFile(void) {
  /// ==========================================================================
  /// READ FASTA FILE
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_mstatspop_open_fasta_->SetInput(file_in_);
    calc_mstatspop_open_fasta_->SetInput(ploidy_);
    calc_mstatspop_open_fasta_->SetInput(outgroup_presence_);
    calc_mstatspop_open_fasta_->SetInput(vint_perpop_nsam_);
    calc_mstatspop_open_fasta_->SetInput(npops_);
    calc_mstatspop_open_fasta_->SetInput(sort_nsam_);
    calc_mstatspop_open_fasta_->SetOutput(length_);
    calc_mstatspop_open_fasta_->SetOutput(names2_);
    calc_mstatspop_open_fasta_->SetOutput(n_site_);
    calc_mstatspop_open_fasta_->SetOutput(DNA_matr2_);
    calc_mstatspop_open_fasta_->SetOutput(n_samp_);
    calc_mstatspop_open_fasta_->SetOutput(matrix_segrpos_);
    calc_mstatspop_open_fasta_->SetOutput(matrix_sizepos_);
    calc_mstatspop_open_fasta_->SetOutput(nsamuser_eff_);
    calc_mstatspop_open_fasta_->Prepare();
  }
  calc_mstatspop_open_fasta_->Calculate(manager()->all_commands()->dry_run());
  calc_mstatspop_open_fasta_->Finalize();
  // ===========================================================================
}

bool CCalcMstatspop::ReadTFastaFile(void) {
  /// ==========================================================================
  /// READ THE T-FASTA FILE
  /// ==========================================================================
  static bool prepare = true;
  if (prepare) {
    prepare = false;
    calc_tfasta_->SetInput(file_in_);
    calc_tfasta_->SetInput(nwindows_);
    calc_tfasta_->SetInput(wgenes_);
    calc_tfasta_->SetInput(wlimit_end_);
    calc_tfasta_->SetInput(wP_);
    calc_tfasta_->SetInput(wPV_);
    calc_tfasta_->SetInput(ploidy_);
    calc_tfasta_->SetInput(npops_);
    calc_tfasta_->SetInput(outgroup_presence_);
    calc_tfasta_->SetInput(vint_perpop_nsam_);
    calc_tfasta_->SetInput(physical_length_);
    calc_tfasta_->SetInput(window_);
    calc_tfasta_->SetInput(slide_);
    calc_tfasta_->SetInput(sort_nsam_);
    calc_tfasta_->SetOutput(n_site_);
    calc_tfasta_->SetOutput(names2_);  // *
    calc_tfasta_->SetOutput(DNA_matr2_);  // *
    calc_tfasta_->SetOutput(vector_priors_);
    calc_tfasta_->SetOutput(mhitbp_);
    calc_tfasta_->SetOutput(matrix_sizepos_);
    calc_tfasta_->SetOutput(matrix_segrpos_);
    calc_tfasta_->SetOutput(n_samp_);
    calc_tfasta_->SetOutput(li_);
    calc_tfasta_->SetOutput(length_);
    calc_tfasta_->SetOutput(npriors_);
    calc_tfasta_->SetOutput(nsamuser_eff_);
    calc_tfasta_->SetOutput(beg_);
    calc_tfasta_->SetOutput(result_);
    calc_tfasta_->Prepare();
  }
  calc_tfasta_->Calculate(manager()->all_commands()->dry_run());
  if (!(result_->value()==1)) {
    calc_tfasta_->Finalize();
  }
  /// ==========================================================================
  
  return (result_->value()==1);
}

void CCalcMstatspop::ReadEffectSizesFile(void) {
  /// ==========================================================================
  /// READ THE EFFECT SIZES FILE
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_effect_sizes_->SetInput(file_effsz_);
    calc_effect_sizes_->SetOutput(wV_);
    calc_effect_sizes_->SetOutput(Pp_);
    calc_effect_sizes_->SetOutput(nV_);
    calc_effect_sizes_->SetOutput(welimit_end_);
    calc_effect_sizes_->Prepare();
  }
  calc_effect_sizes_->Calculate(manager()->all_commands()->dry_run());
  calc_effect_sizes_->Finalize();
  /// ==========================================================================
}
  
void CCalcMstatspop::ReadCoordinatesFile(void) {
  /// ==========================================================================
  /// READ THE COORDINATES FILE
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_coordinates_->SetInput(file_wcoord_);
    calc_coordinates_->SetOutput(wgenes_);
    calc_coordinates_->SetOutput(nwindows_);
    calc_coordinates_->Prepare();
  }
  calc_coordinates_->Calculate(manager()->all_commands()->dry_run());
  calc_coordinates_->Finalize();
  /// ==========================================================================
}

void CCalcMstatspop::ReadWeightPositionsFile(void) {
  /// ==========================================================================
  /// READ THE WEIGTH POSITIONS FILE
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_weight_positions_->SetInput(file_wps_);
    calc_weight_positions_->SetOutput(wP_);
    calc_weight_positions_->SetOutput(wPV_);
    calc_weight_positions_->SetOutput(wV_);
    calc_weight_positions_->SetOutput(wlimit_end_);
    calc_weight_positions_->Prepare();
  }
  calc_weight_positions_->Calculate(manager()->all_commands()->dry_run());
  calc_weight_positions_->Finalize();
  /// ==========================================================================
}
  
void CCalcMstatspop::FilterDnaMatrixWithGFFFile(void) {
  /// ==========================================================================
  /// FILTER THE DNA_MATRIX USING A GFF FILE
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_gff_->SetInput(include_unknown_);
    calc_gff_->SetInput(outgroup_presence_);
    calc_gff_->SetInput(vint_perpop_nsam_);
    calc_gff_->SetInput(npops_);
    calc_gff_->SetInput(DNA_matr2_); // It is an output Too
    calc_gff_->SetInput(file_GFF_);  // e.g.: "examples/MC1R.gff";
    calc_gff_->SetInput(subset_positions_);  // e.g.: "nonsynonymous"
    calc_gff_->SetInput(genetic_code_);
    calc_gff_->SetInput(criteria_transcript_);
    calc_gff_->SetInput(nsamuser_eff_);  // It was n_samp_
    calc_gff_->SetInput(n_site_);
    calc_gff_->SetOutput(matrix_sizepos_);
    calc_gff_->SetOutput(matrix_segrpos_);
    calc_gff_->SetOutput(mhitbp_);
    calc_gff_->SetOutput(nmhits_);
    calc_gff_->Prepare();
  }
  calc_gff_->Calculate(manager()->all_commands()->dry_run());
  calc_gff_->Finalize();
  // ===========================================================================
}
  
void CCalcMstatspop::CalculateStats(void) {
  CDataInt64 *formatfile64 = NULL;
  DM_NEW_DATA(formatfile64)

  if (formatfile_->value() == TFASTA_FILE) {
    nmhits_->set_value(0);
  }
    
  /// ==========================================================================
  /// CALCULATE STATS
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_file_stats_->SetInput(ploidy_);
    calc_file_stats_->SetInput(include_unknown_);
    calc_file_stats_->SetInput(outgroup_presence_);
    calc_file_stats_->SetInput(vint_perpop_nsam_);
    calc_file_stats_->SetInput(npops_);
    calc_file_stats_->SetInput(names2_);
    calc_file_stats_->SetInput(n_site_);
    calc_file_stats_->SetInput(DNA_matr2_);
    calc_file_stats_->SetInput(matrix_segrpos_);
    calc_file_stats_->SetInput(file_in_);
    calc_file_stats_->SetInput(file_mas_);
    calc_file_stats_->SetInput(output_);
    if (formatfile_->value() == TFASTA_FILE) {
      calc_file_stats_->SetInput(beg_);
    } else {
      formatfile64->set_value(0);
      calc_file_stats_->SetInput(formatfile64);
    }
    calc_file_stats_->SetOutput(matrix_pol_);
    calc_file_stats_->SetOutput(matrix_pol_tcga_);
    calc_file_stats_->SetOutput(lengthamng_);
    calc_file_stats_->SetOutput(tcga_);
    calc_file_stats_->SetOutput(anx_);
    calc_file_stats_->SetOutput(bnx_);
    calc_file_stats_->SetOutput(anxo_);
    calc_file_stats_->SetOutput(bnxo_);
    calc_file_stats_->SetOutput(length_al_);
    calc_file_stats_->SetOutput(length_seg_);
    calc_file_stats_->SetOutput(missratio_);
    calc_file_stats_->SetOutput(nsites1_pop_);
    calc_file_stats_->SetOutput(nsites1_pop_outg_);
    calc_file_stats_->SetOutput(nsites2_pop_);
    calc_file_stats_->SetOutput(nsites2_pop_outg_);
    calc_file_stats_->SetOutput(nsites3_pop_);
    calc_file_stats_->SetOutput(nsites3_pop_outg_);
    calc_file_stats_->SetOutput(sum_sam_);
    calc_file_stats_->SetOutput(svratio_);
    calc_file_stats_->SetOutput(frequencies_);
    calc_file_stats_->SetOutput(positions_);
    calc_file_stats_->SetOutput(matrix_sv_);
    calc_file_stats_->SetOutput(mhitbp_);
    calc_file_stats_->SetOutput(length_al_real_);
    calc_file_stats_->SetOutput(nmhits_);
    calc_file_stats_->SetOutput(matrix_sizepos_);
    calc_file_stats_->SetOutput(nsamuser_eff_);
    calc_file_stats_->Prepare();
  }
  calc_file_stats_->Calculate(manager()->all_commands()->dry_run());
  calc_file_stats_->Finalize();
  // ===========================================================================
  
  DM_DEL_DATA(formatfile64)
}


void CCalcMstatspop::MsMaskFile(void) {
  /// ==========================================================================
  /// MS MASK FILE
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_mask_file_ms_->SetInput(include_unknown_);
    calc_mask_file_ms_->SetInput(outgroup_presence_);
    calc_mask_file_ms_->SetInput(vint_perpop_nsam_);
    calc_mask_file_ms_->SetInput(npops_);
    calc_mask_file_ms_->SetInput(int_total_nsam_);
    calc_mask_file_ms_->SetInput(file_mas_);
    calc_mask_file_ms_->SetInput(length_);
    calc_mask_file_ms_->SetOutput(niter_);
    calc_mask_file_ms_->SetOutput(length_al_real_);
    calc_mask_file_ms_->SetOutput(vector_mask_);
    calc_mask_file_ms_->SetOutput(matrix_mask_);
    calc_mask_file_ms_->SetOutput(sum_sam_mask_);
    calc_mask_file_ms_->SetOutput(length_mask_);
    calc_mask_file_ms_->SetOutput(missratio_);
    calc_mask_file_ms_->SetOutput(length_al_);
    calc_mask_file_ms_->SetOutput(length_mask_real_);
    calc_mask_file_ms_->Prepare();
  }
  calc_mask_file_ms_->Calculate(manager()->all_commands()->dry_run());
  calc_mask_file_ms_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::OpenMsFile(void) {
  /// ==========================================================================
  /// READ MS FILE
  /// ==========================================================================
  if (li_->value() == 0) {
    // Execute this only the first time:

    calc_mstatspop_open_ms_->SetInput(file_in_);
    calc_mstatspop_open_ms_->SetInput(include_unknown_);
    calc_mstatspop_open_ms_->SetInput(outgroup_presence_);
    calc_mstatspop_open_ms_->SetInput(force_outgroup_);
    calc_mstatspop_open_ms_->SetInput(vint_perpop_nsam_);
    calc_mstatspop_open_ms_->SetInput(npops_);
    calc_mstatspop_open_ms_->SetInput(int_total_nsam_);
    calc_mstatspop_open_ms_->SetInput(length_);
    calc_mstatspop_open_ms_->SetInput(kind_length_);
    calc_mstatspop_open_ms_->SetInput(vector_mask_);
    calc_mstatspop_open_ms_->SetInput(ms_svratio_);
    calc_mstatspop_open_ms_->SetInput(freq_revert_);
    calc_mstatspop_open_ms_->SetInput(file_mas_);
    calc_mstatspop_open_ms_->SetInput(freq_missing_ms_);
    calc_mstatspop_open_ms_->SetInput(location_missing_ms_);
    calc_mstatspop_open_ms_->SetInput(formatfile_);  
    calc_mstatspop_open_ms_->SetOutput(matrix_pol_);
    calc_mstatspop_open_ms_->SetOutput(frequencies_);
    calc_mstatspop_open_ms_->SetOutput(positions_);
    calc_mstatspop_open_ms_->SetOutput(length_seg_);
    calc_mstatspop_open_ms_->SetOutput(matrix_sv_);
    calc_mstatspop_open_ms_->SetOutput(length_mask_);
    calc_mstatspop_open_ms_->SetOutput(length_mask_real_);
    calc_mstatspop_open_ms_->SetOutput(lengthamng_);
    calc_mstatspop_open_ms_->SetOutput(nmhits_);
    calc_mstatspop_open_ms_->SetOutput(matrix_mask_);
    calc_mstatspop_open_ms_->SetOutput(vector_priors_);
    calc_mstatspop_open_ms_->SetOutput(npriors_);
    calc_mstatspop_open_ms_->SetOutput(sum_sam_);
    calc_mstatspop_open_ms_->SetOutput(sum_sam_mask_);
    calc_mstatspop_open_ms_->SetOutput(nsites1_pop_);
    calc_mstatspop_open_ms_->SetOutput(nsites1_pop_outg_);
    calc_mstatspop_open_ms_->SetOutput(nsites2_pop_);
    calc_mstatspop_open_ms_->SetOutput(nsites2_pop_outg_);
    calc_mstatspop_open_ms_->SetOutput(nsites3_pop_);
    calc_mstatspop_open_ms_->SetOutput(nsites3_pop_outg_);
    calc_mstatspop_open_ms_->SetOutput(anx_);
    calc_mstatspop_open_ms_->SetOutput(bnx_);
    calc_mstatspop_open_ms_->SetOutput(anxo_);
    calc_mstatspop_open_ms_->SetOutput(bnxo_);
    calc_mstatspop_open_ms_->SetOutput(missratio_);
    calc_mstatspop_open_ms_->SetOutput(sort_nsam_);
    
    calc_mstatspop_open_ms_->Prepare();
  }
  calc_mstatspop_open_ms_->Calculate(manager()->all_commands()->dry_run());
  // ===========================================================================
}

void CCalcMstatspop::CalcX(void) {
  /// ==========================================================================
  /// CALC X
  /// ==========================================================================
  static bool prepare = true;
  if (prepare) {
    prepare = false;
    calc_x_->SetInput(include_unknown_);
    calc_x_->SetInput(vint_perpop_nsam_);
    calc_x_->SetInput(npops_);
    calc_x_->SetInput(int_total_nsam_);
    calc_x_->SetInput(vector_mask_);
    calc_x_->SetInput(length_);
    calc_x_->SetInput(length_mask_);
    calc_x_->SetInput(sum_sam_mask_);
    calc_x_->SetInput(nmhits_);
    calc_x_->SetInput(file_mas_);
    calc_x_->SetOutput(length_al_);
    calc_x_->SetOutput(flaghky_);
    calc_x_->SetOutput(sum_sam_);
    calc_x_->SetOutput(stats_length_[0]);
    calc_x_->SetOutput(stats_linefreq_[0]);
    calc_x_->SetOutput(stats_total_tcga_[0]);
    calc_x_->SetOutput(stats_tcga_[0]);
    calc_x_->Prepare();
  }
  calc_x_->Calculate(manager()->all_commands()->dry_run());
  calc_x_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalEffectiveNucleotidesAndTCGAFreqs(void) {
  /// ==========================================================================
  /// CALCULATE  NUMBER OF EFFECTIVE NUCLEOTIDES PER POPULATION AND TCGA FREQS
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_effec_nuc_TCGA_freqs_->SetInput(vint_perpop_nsam_);
    calc_effec_nuc_TCGA_freqs_->SetInput(npops_);
    calc_effec_nuc_TCGA_freqs_->SetInput(nsites2_pop_);
    calc_effec_nuc_TCGA_freqs_->SetInput(sum_sam_);
    calc_effec_nuc_TCGA_freqs_->SetInput(anx_);
    calc_effec_nuc_TCGA_freqs_->SetInput(bnx_);
    calc_effec_nuc_TCGA_freqs_->SetInput(anxo_);
    calc_effec_nuc_TCGA_freqs_->SetInput(bnxo_);
    calc_effec_nuc_TCGA_freqs_->SetInput(tcga_);
    calc_effec_nuc_TCGA_freqs_->SetOutput(stats_length_[0]);
    calc_effec_nuc_TCGA_freqs_->SetOutput(stats_length2_[0]);
    calc_effec_nuc_TCGA_freqs_->SetOutput(stats_anx_[0]);
    calc_effec_nuc_TCGA_freqs_->SetOutput(stats_bnx_[0]);
    calc_effec_nuc_TCGA_freqs_->SetOutput(stats_anxo_[0]);
    calc_effec_nuc_TCGA_freqs_->SetOutput(stats_bnxo_[0]);
    calc_effec_nuc_TCGA_freqs_->SetOutput(stats_tcga_[0]);
    calc_effec_nuc_TCGA_freqs_->SetOutput(stats_total_tcga_[0]);
    calc_effec_nuc_TCGA_freqs_->Prepare();
  }
  calc_effec_nuc_TCGA_freqs_->Calculate(manager()->all_commands()->dry_run());
  calc_effec_nuc_TCGA_freqs_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::IncludeLengthMngAndCalculations(void) {
  /// ==========================================================================
  /// INCLUDE LENGTHMNG AND CALCULATIONS
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_lengthamng_and_calcs_->SetInput(outgroup_presence_);
    calc_lengthamng_and_calcs_->SetInput(npops_);
    calc_lengthamng_and_calcs_->SetInput(length_seg_);
    calc_lengthamng_and_calcs_->SetInput(lengthamng_);
    calc_lengthamng_and_calcs_->SetInput(length_al_);
    calc_lengthamng_and_calcs_->SetInput(length_al_real_);
    calc_lengthamng_and_calcs_->SetInput(svratio_);
    calc_lengthamng_and_calcs_->SetInput(nmhits_);
    calc_lengthamng_and_calcs_->SetInput(vint_perpop_nsam_);
    calc_lengthamng_and_calcs_->SetInput(int_total_nsam_);
    calc_lengthamng_and_calcs_->SetOutput(stats_lengthamng_[0]);
    calc_lengthamng_and_calcs_->SetOutput(stats_total_length_[0]);
    calc_lengthamng_and_calcs_->SetOutput(stats_total_real_length_[0]);
    calc_lengthamng_and_calcs_->SetOutput(stats_total_svratio_[0]);
    calc_lengthamng_and_calcs_->SetOutput(stats_nmhits_[0]);
    calc_lengthamng_and_calcs_->SetOutput(jfd_);
    calc_lengthamng_and_calcs_->SetOutput(nfd_);
    calc_lengthamng_and_calcs_->SetOutput(stats_linefreq_[0]);
    calc_lengthamng_and_calcs_->SetOutput(stats_freq_[0]);
    calc_lengthamng_and_calcs_->SetOutput(stats_mdsd_[0]); 
    calc_lengthamng_and_calcs_->Prepare();
  }
  calc_lengthamng_and_calcs_->Calculate(manager()->all_commands()->dry_run());
  calc_lengthamng_and_calcs_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcSxsfss(void) {
  /// ==========================================================================
  /// GET THE SITES MATRIX FROM THE MATRIX POL
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_sxsfss_->SetInput(force_outgroup_);
    calc_sxsfss_->SetInput(outgroup_presence_);
    calc_sxsfss_->SetInput(vint_perpop_nsam_);
    calc_sxsfss_->SetInput(npops_);
    calc_sxsfss_->SetInput(matrix_pol_);
    calc_sxsfss_->SetInput(positions_);
    calc_sxsfss_->SetInput(length_seg_);
    calc_sxsfss_->SetOutput(sites_);
    calc_sxsfss_->SetOutput(sanc_);
    calc_sxsfss_->Prepare();
  }
  calc_sxsfss_->Calculate(manager()->all_commands()->dry_run());
  calc_sxsfss_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcJointFreqDistribution(void) {
  /// ==========================================================================
  /// JOINT FREQUENCY DISTRIBUTION
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_joint_freq_dist_->SetInput(force_outgroup_);
    calc_joint_freq_dist_->SetInput(outgroup_presence_);
    calc_joint_freq_dist_->SetInput(vint_perpop_nsam_);
    calc_joint_freq_dist_->SetInput(npops_);
    calc_joint_freq_dist_->SetInput(matrix_pol_);
    calc_joint_freq_dist_->SetInput(length_seg_);
    calc_joint_freq_dist_->SetOutput(jfd_);
    calc_joint_freq_dist_->SetOutput(stats_linefreq_[0]);
    calc_joint_freq_dist_->SetOutput(nfd_);
    calc_joint_freq_dist_->Prepare();
  }
  calc_joint_freq_dist_->Calculate(manager()->all_commands()->dry_run());
  calc_joint_freq_dist_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcPiwpiafst_1(void) {
  /// ==========================================================================
  /// PIWPIAFST
  /// ==========================================================================
  static bool prepare = true;
  if (prepare) {
    prepare = false;
    calc_piwpiafst_1_->SetInput(vint_perpop_nsam_);
    calc_piwpiafst_1_->SetInput(npops_);
    calc_piwpiafst_1_->SetInput(matrix_pol_);
    calc_piwpiafst_1_->SetInput(matrix_sv_);
    calc_piwpiafst_1_->SetInput(stats_tcga_[0]);
    calc_piwpiafst_1_->SetInput(stats_lengthamng_[0]);
    calc_piwpiafst_1_->SetInput(flaghky_);
    calc_piwpiafst_1_->SetInput(stats_length2_[0]);
    calc_piwpiafst_1_->SetInput(formatfile_);
    calc_piwpiafst_1_->SetInput(length_seg_);
    calc_piwpiafst_1_->SetOutput(stats_sv_[0]);
    calc_piwpiafst_1_->SetOutput(stats_svT_[0]);
    calc_piwpiafst_1_->SetOutput(stats_fst_[0]);
    calc_piwpiafst_1_->SetOutput(stats_fst1all_[0]);
    calc_piwpiafst_1_->SetOutput(stats_fstHKY_[0]);
    calc_piwpiafst_1_->SetOutput(stats_K_[0]);
    calc_piwpiafst_1_->SetOutput(stats_KHKY_[0]);
    calc_piwpiafst_1_->SetOutput(stats_pia_[0]);
    calc_piwpiafst_1_->SetOutput(stats_piaHKY_[0]);
    calc_piwpiafst_1_->SetOutput(stats_piT_[0]);
    calc_piwpiafst_1_->SetOutput(stats_piTHKY_[0]);
    calc_piwpiafst_1_->SetOutput(stats_piwHKY_[0]);
    calc_piwpiafst_1_->SetOutput(stats_piw_[0]);
    calc_piwpiafst_1_->SetOutput(stats_thetaTHKY_[0]);
    calc_piwpiafst_1_->SetOutput(stats_piant_[0]);
    calc_piwpiafst_1_->SetOutput(stats_piTnt_[0]);
    calc_piwpiafst_1_->SetOutput(stats_fstALL_[0]);
    calc_piwpiafst_1_->Prepare();
  }
  calc_piwpiafst_1_->Calculate(manager()->all_commands()->dry_run());
  calc_piwpiafst_1_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcPiwpiafst_2(void) {
  /// ==========================================================================
  /// PIWPIAFST
  /// ==========================================================================
  static bool prepare = true;
  if (prepare) {
    prepare = false;
    calc_piwpiafst_2_->SetInput(vint_perpop_nsam_);
    calc_piwpiafst_2_->SetInput(npops_);
    calc_piwpiafst_2_->SetInput(matrix_perm_);  // <--- matrix_pol
    calc_piwpiafst_2_->SetInput(matrix_sv_);
    calc_piwpiafst_2_->SetInput(stats_tcga_[1]);
    calc_piwpiafst_2_->SetInput(stats_lengthamng_[1]);
    calc_piwpiafst_2_->SetInput(flaghky0_);  // <--- 0
    calc_piwpiafst_2_->SetInput(stats_length2_[1]);
    calc_piwpiafst_2_->SetInput(formatfile_);
    calc_piwpiafst_2_->SetInput(length_seg_);
    calc_piwpiafst_2_->SetOutput(stats_sv_[1]);
    calc_piwpiafst_2_->SetOutput(stats_svT_[1]);
    calc_piwpiafst_2_->SetOutput(stats_fst_[1]);
    calc_piwpiafst_2_->SetOutput(stats_fst1all_[1]);
    calc_piwpiafst_2_->SetOutput(stats_fstHKY_[1]);
    calc_piwpiafst_2_->SetOutput(stats_K_[1]);
    calc_piwpiafst_2_->SetOutput(stats_KHKY_[1]);
    calc_piwpiafst_2_->SetOutput(stats_pia_[1]);
    calc_piwpiafst_2_->SetOutput(stats_piaHKY_[1]);
    calc_piwpiafst_2_->SetOutput(stats_piT_[1]);
    calc_piwpiafst_2_->SetOutput(stats_piTHKY_[1]);
    calc_piwpiafst_2_->SetOutput(stats_piwHKY_[1]);
    calc_piwpiafst_2_->SetOutput(stats_piw_[1]);
    calc_piwpiafst_2_->SetOutput(stats_thetaTHKY_[1]);
    calc_piwpiafst_2_->SetOutput(stats_piant_[1]);
    calc_piwpiafst_2_->SetOutput(stats_piTnt_[1]);
    calc_piwpiafst_2_->SetOutput(stats_fstALL_[1]);
    calc_piwpiafst_2_->Prepare();
  }
  flaghky0_->set_value(0);
  calc_piwpiafst_2_->Calculate(manager()->all_commands()->dry_run());
  calc_piwpiafst_2_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcPiwpiafst_3(void) {
  /// ==========================================================================
  /// PIWPIAFST
  /// ==========================================================================
    static bool prepare = true;
  if (prepare) {
    prepare = false;
    calc_piwpiafst_3_->SetInput(nsam2_);  //  <--- nsam2                            // NO: vint_perpop_nsam_iter_
    calc_piwpiafst_3_->SetInput(npops_iter_);             //  <--- 2
    calc_piwpiafst_3_->SetInput(matrix_perm_);            //  <--- matrix_pol
    calc_piwpiafst_3_->SetInput(matrix_sv_);
    calc_piwpiafst_3_->SetInput(stats_tcga_[1]);
    calc_piwpiafst_3_->SetInput(stats_lengthamng_[1]);
    calc_piwpiafst_3_->SetInput(flaghky0_);                //  <--- 0
    calc_piwpiafst_3_->SetInput(stats_length2_[1]);
    calc_piwpiafst_3_->SetInput(formatfile_);
    calc_piwpiafst_3_->SetInput(length_seg_);
    calc_piwpiafst_3_->SetOutput(stats_sv_[1]);
    calc_piwpiafst_3_->SetOutput(stats_svT_[1]);
    calc_piwpiafst_3_->SetOutput(stats_fst_[1]);
    calc_piwpiafst_3_->SetOutput(stats_fst1all_[1]);
    calc_piwpiafst_3_->SetOutput(stats_fstHKY_[1]);
    calc_piwpiafst_3_->SetOutput(stats_K_[1]);
    calc_piwpiafst_3_->SetOutput(stats_KHKY_[1]);
    calc_piwpiafst_3_->SetOutput(stats_pia_[1]);
    calc_piwpiafst_3_->SetOutput(stats_piaHKY_[1]);
    calc_piwpiafst_3_->SetOutput(stats_piT_[1]);
    calc_piwpiafst_3_->SetOutput(stats_piTHKY_[1]);
    calc_piwpiafst_3_->SetOutput(stats_piwHKY_[1]);
    calc_piwpiafst_3_->SetOutput(stats_piw_[1]);
    calc_piwpiafst_3_->SetOutput(stats_thetaTHKY_[1]);
    calc_piwpiafst_3_->SetOutput(stats_piant_[1]);
    calc_piwpiafst_3_->SetOutput(stats_piTnt_[1]);
    calc_piwpiafst_3_->SetOutput(stats_fstALL_[1]);
    calc_piwpiafst_3_->Prepare();
  }
  npops_iter_->set_value(2);
  flaghky0_->set_value(0);
  calc_piwpiafst_3_->Calculate(manager()->all_commands()->dry_run());
  calc_piwpiafst_3_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcFrequencyStats(void) {
  /// ==========================================================================
  /// FREQUENCY STATISTICS
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_freq_stats_->SetInput(include_unknown_);
    calc_freq_stats_->SetInput(force_outgroup_);
    calc_freq_stats_->SetInput(outgroup_presence_);
    calc_freq_stats_->SetInput(vint_perpop_nsam_);
    calc_freq_stats_->SetInput(npops_);
    calc_freq_stats_->SetInput(matrix_pol_);
    calc_freq_stats_->SetInput(n_ccov_);
    calc_freq_stats_->SetInput(H1frq_);
    calc_freq_stats_->SetInput(stats_H1freq_[0]);
    calc_freq_stats_->SetInput(length_seg_);
    calc_freq_stats_->SetOutput(stats_Dfl_[0]);
    calc_freq_stats_->SetOutput(stats_Dtaj_[0]);
    calc_freq_stats_->SetOutput(stats_Ez_[0]);
    calc_freq_stats_->SetOutput(stats_Ffl_[0]);
    calc_freq_stats_->SetOutput(stats_Hnfw_[0]);
    calc_freq_stats_->SetOutput(stats_S_[0]);
    calc_freq_stats_->SetOutput(stats_So_[0]);
    calc_freq_stats_->SetOutput(stats_thetaFL_[0]);
    calc_freq_stats_->SetOutput(stats_thetaFW_[0]);
    calc_freq_stats_->SetOutput(stats_thetaL_[0]);
    calc_freq_stats_->SetOutput(stats_thetaS_[0]);
    calc_freq_stats_->SetOutput(stats_thetaSA_[0]);
    calc_freq_stats_->SetOutput(stats_thetaSo_[0]);
    calc_freq_stats_->SetOutput(stats_thetaT_[0]);
    calc_freq_stats_->SetOutput(stats_thetaTA_[0]);
    calc_freq_stats_->SetOutput(stats_thetaTo_[0]);
    calc_freq_stats_->SetOutput(stats_To_00_[0]);
    calc_freq_stats_->SetOutput(stats_To_i0_[0]);
    calc_freq_stats_->SetOutput(stats_To_ii_[0]);
    calc_freq_stats_->SetOutput(stats_ToH0_00_[0]);
    calc_freq_stats_->SetOutput(stats_ToH0_ii_[0]);
    calc_freq_stats_->SetOutput(stats_Yach_[0]);
    calc_freq_stats_->SetOutput(stats_FH_[0]);
    calc_freq_stats_->SetOutput(stats_freq_[0]);
    calc_freq_stats_->Prepare();
  }
  calc_freq_stats_->Calculate(manager()->all_commands()->dry_run());
  calc_freq_stats_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcOptimalTests(void) {
  /// ==========================================================================
  /// OPTIMAL TESTS
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_optimal_tests_->SetInput(vint_perpop_nsam_);
    calc_optimal_tests_->SetInput(npops_);
    calc_optimal_tests_->SetInput(stats_freq_[0]);
    calc_optimal_tests_->SetInput(stats_total_length_[0]);
    calc_optimal_tests_->SetInput(stats_H1freq_[0]);
    calc_optimal_tests_->SetInput(stats_thetaH1_[0]);
    calc_optimal_tests_->SetInput(stats_H0freq_[0]);
    calc_optimal_tests_->SetInput(stats_thetaH0_[0]);
    calc_optimal_tests_->SetOutput(stats_ToH0_ii_[0]);
    calc_optimal_tests_->SetOutput(stats_To_ii_[0]);
    calc_optimal_tests_->SetOutput(stats_To_00_[0]);
    calc_optimal_tests_->SetOutput(stats_To_i0_[0]);
    calc_optimal_tests_->SetOutput(stats_ToH0_00_[0]);
    calc_optimal_tests_->SetOutput(stats_To_Qc_ii_[0]);
    calc_optimal_tests_->SetOutput(stats_To_Qw_ii_[0]);
    calc_optimal_tests_->SetOutput(stats_To_Lc_ii_[0]);
    calc_optimal_tests_->Prepare();
  }
  calc_optimal_tests_->Calculate(manager()->all_commands()->dry_run());
  calc_optimal_tests_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcR2(void) {
  /// ==========================================================================
  /// R2
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_r2_->SetInput(ploidy_);
    calc_r2_->SetInput(vint_perpop_nsam_);
    calc_r2_->SetInput(npops_);
    calc_r2_->SetInput(matrix_pol_);
    calc_r2_->SetInput(stats_S_[0]);
    calc_r2_->SetInput(stats_thetaT_[0]);
    calc_r2_->SetInput(length_seg_);
    calc_r2_->SetOutput(stats_R2_[0]);
    calc_r2_->Prepare();
  }
  calc_r2_->Calculate(manager()->all_commands()->dry_run());
  calc_r2_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcR2p(void) {
  /// ==========================================================================
  /// R2P
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_r2p_->SetInput(ploidy_);
    calc_r2p_->SetInput(vint_perpop_nsam_);
    calc_r2p_->SetInput(npops_);
    calc_r2p_->SetInput(matrix_pol_);
    calc_r2p_->SetInput(sum_sam_);
    calc_r2p_->SetInput(stats_S_[0]);
    calc_r2p_->SetInput(stats_thetaT_[0]);
    calc_r2p_->SetInput(r2i_ploidies_);
    calc_r2p_->SetInput(length_seg_);
    calc_r2p_->SetOutput(stats_R2_[0]);
    calc_r2p_->SetOutput(stats_R2p_[0]);
    calc_r2p_->Prepare();
  }
  calc_r2p_->Calculate(manager()->all_commands()->dry_run());
  calc_r2p_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcMismatch(void) {
  /// ==========================================================================
  /// MISMATCH
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_mismatch_->SetInput(ploidy_);
    calc_mismatch_->SetInput(vint_perpop_nsam_);
    calc_mismatch_->SetInput(npops_);
    calc_mismatch_->SetInput(matrix_pol_);
    calc_mismatch_->SetInput(stats_thetaT_[0]);
    calc_mismatch_->SetInput(length_seg_);
    calc_mismatch_->SetOutput(stats_mdg1_[0]);
    calc_mismatch_->SetOutput(stats_mdg2_[0]);
    calc_mismatch_->SetOutput(stats_mdsd_[0]);
    calc_mismatch_->SetOutput(stats_mdw_[0]);
    calc_mismatch_->Prepare();
  }
  calc_mismatch_->Calculate(manager()->all_commands()->dry_run());
  calc_mismatch_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcHwhafsth_1(void) {
  /// ==========================================================================
  /// HWHAFSTH
  /// ==========================================================================
  static bool prepare = true;
  if (prepare) {
    prepare = false;
    calc_hwhafsth_1_->SetInput(vint_perpop_nsam_);
    calc_hwhafsth_1_->SetInput(npops_);
    calc_hwhafsth_1_->SetInput(matrix_pol_);
    calc_hwhafsth_1_->SetInput(length_seg_);
    calc_hwhafsth_1_->SetOutput(stats_nhpop_[0]);
    calc_hwhafsth_1_->SetOutput(stats_hapw_[0]);
    calc_hwhafsth_1_->SetOutput(stats_hapa_[0]);
    calc_hwhafsth_1_->SetOutput(stats_hapT_[0]);
    calc_hwhafsth_1_->SetOutput(stats_fsth_[0]);
    calc_hwhafsth_1_->SetOutput(stats_fsth1all_[0]);
    calc_hwhafsth_1_->SetOutput(stats_freqh_[0]);
    calc_hwhafsth_1_->SetOutput(stats_nh_[0]);
    calc_hwhafsth_1_->SetOutput(stats_Gst_[0]);
    calc_hwhafsth_1_->SetOutput(stats_fsthALL_[0]);
    calc_hwhafsth_1_->SetOutput(stats_GstALL_[0]);
    calc_hwhafsth_1_->Prepare();
  }
  calc_hwhafsth_1_->Calculate(manager()->all_commands()->dry_run());
  calc_hwhafsth_1_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcHwhafsth_2(void) {
  /// ==========================================================================
  /// HWHAFSTH
  /// ==========================================================================
  static bool prepare = true;
  if (prepare) {
    prepare = false;
    calc_hwhafsth_2_->SetInput(vint_perpop_nsam_);
    calc_hwhafsth_2_->SetInput(npops_);
    calc_hwhafsth_2_->SetInput(matrix_perm_);  // <-- matrix_pol
    calc_hwhafsth_2_->SetInput(length_seg_);
    calc_hwhafsth_2_->SetOutput(stats_nhpop_[1]);
    calc_hwhafsth_2_->SetOutput(stats_hapw_[1]);
    calc_hwhafsth_2_->SetOutput(stats_hapa_[1]);
    calc_hwhafsth_2_->SetOutput(stats_hapT_[1]);
    calc_hwhafsth_2_->SetOutput(stats_fsth_[1]);
    calc_hwhafsth_2_->SetOutput(stats_fsth1all_[1]);
    calc_hwhafsth_2_->SetOutput(stats_freqh_[1]);
    calc_hwhafsth_2_->SetOutput(stats_nh_[1]);
    calc_hwhafsth_2_->SetOutput(stats_Gst_[1]);
    calc_hwhafsth_2_->SetOutput(stats_fsthALL_[1]);
    calc_hwhafsth_2_->SetOutput(stats_GstALL_[1]);
    calc_hwhafsth_2_->Prepare();
  }
  calc_hwhafsth_2_->Calculate(manager()->all_commands()->dry_run());
  calc_hwhafsth_2_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcHwhafsth_3(void) {
  /// ==========================================================================
  /// HWHAFSTH
  /// ==========================================================================
  static bool prepare = true;
  if (prepare) {
    prepare = false;
    calc_hwhafsth_3_->SetInput(nsam2_);                                             // NO: vint_perpop_nsam_iter_
    calc_hwhafsth_3_->SetInput(npops_iter_);              // <-- 2
    calc_hwhafsth_3_->SetInput(matrix_perm_);             // <-- matrix_pol
    calc_hwhafsth_3_->SetInput(length_seg_);
    calc_hwhafsth_3_->SetOutput(stats_nhpop_[1]);
    calc_hwhafsth_3_->SetOutput(stats_hapw_[1]);
    calc_hwhafsth_3_->SetOutput(stats_hapa_[1]);
    calc_hwhafsth_3_->SetOutput(stats_hapT_[1]);
    calc_hwhafsth_3_->SetOutput(stats_fsth_[1]);
    calc_hwhafsth_3_->SetOutput(stats_fsth1all_[1]);
    calc_hwhafsth_3_->SetOutput(stats_freqh_[1]);
    calc_hwhafsth_3_->SetOutput(stats_nh_[1]);
    calc_hwhafsth_3_->SetOutput(stats_Gst_[1]);
    calc_hwhafsth_3_->SetOutput(stats_fsthALL_[1]);
    calc_hwhafsth_3_->SetOutput(stats_GstALL_[1]);
    calc_hwhafsth_3_->Prepare();
  }
  npops_iter_->set_value(2);
  calc_hwhafsth_3_->Calculate(manager()->all_commands()->dry_run());
  calc_hwhafsth_3_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcFs(void) {
  /// ==========================================================================
  /// FS
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_fs_->SetInput(vint_perpop_nsam_);
    calc_fs_->SetInput(npops_);
    calc_fs_->SetInput(stats_thetaT_[0]);
    calc_fs_->SetInput(stats_nhpop_[0]);
    calc_fs_->SetOutput(stats_Fs_[0]);
    calc_fs_->Prepare();
  }
  calc_fs_->Calculate(manager()->all_commands()->dry_run());
  calc_fs_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcY(void) {
  /// ==========================================================================
  /// CALC Y
  /// ==========================================================================
  static bool prepare = true;
  if (prepare) {
    prepare = false;
    calc_y_->SetInput(ploidy_);
    calc_y_->SetInput(npops_);
    calc_y_->SetInput(stats_fst1all_[0]);
    calc_y_->SetInput(stats_fst1all_[1]);
    calc_y_->SetInput(stats_fsth1all_[0]);
    calc_y_->SetInput(stats_fsth1all_[1]);
    calc_y_->SetInput(stats_fstALL_[0]);
    calc_y_->SetInput(stats_fstALL_[1]);
    calc_y_->SetInput(stats_fsthALL_[0]);
    calc_y_->SetInput(stats_fsthALL_[1]);
    calc_y_->SetInput(stats_GstALL_[0]);
    calc_y_->SetInput(stats_GstALL_[1]);
    calc_y_->SetOutput(piter_i1_);
    calc_y_->SetOutput(piter_niteri1_);
    calc_y_->SetOutput(piter_ih1_);
    calc_y_->SetOutput(piter_niterih1_);
    calc_y_->SetOutput(piter_iall_);
    calc_y_->SetOutput(piter_niteriall_);
    calc_y_->SetOutput(piter_ihall_);
    calc_y_->SetOutput(piter_niterihall_);
    calc_y_->SetOutput(piter_ighall_);
    calc_y_->SetOutput(piter_niterighall_);
    calc_y_->Prepare();
  }
  calc_y_->Calculate(manager()->all_commands()->dry_run());
  calc_y_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::Permute_2(void) {
  /// ==========================================================================
  /// PERMUTE
  /// ==========================================================================
  static bool prepare = true;
  if (prepare) {
    prepare = false;
    calc_permute_2_->SetInput(int_total_nsam_);
    calc_permute_2_->SetInput(matrix_pol_);
    calc_permute_2_->SetInput(nsam2_);
    calc_permute_2_->SetInput(psam2_);
    calc_permute_2_->SetInput(length_seg_);
    calc_permute_2_->SetOutput(matrix_perm_);
    calc_permute_2_->Prepare();
  }
  calc_permute_2_->Calculate(manager()->all_commands()->dry_run());
  calc_permute_2_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::Permute_3(void) {
  /// ==========================================================================
  /// PERMUTE
  /// ==========================================================================
  static bool prepare = true;
  if (prepare) {
    prepare = false;
    calc_permute_3_->SetInput(int_total_nsam_);
    calc_permute_3_->SetInput(matrix_pol_);
    calc_permute_3_->SetInput(nsam2_);
    calc_permute_3_->SetInput(psam2_);
    calc_permute_3_->SetInput(length_seg_);
    calc_permute_3_->SetOutput(matrix_perm_);
    calc_permute_3_->Prepare();
  }
  calc_permute_3_->Calculate(manager()->all_commands()->dry_run());
  calc_permute_3_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::CalcZ(void) {
  /// ==========================================================================
  /// CALC Z
  /// ==========================================================================
  static bool prepare = true;
  if (prepare) {
    prepare = false;
    calc_z_->SetInput(ploidy_);
    calc_z_->SetInput(z_pos_);
    calc_z_->SetInput(stats_fst_[0]);
    calc_z_->SetInput(stats_fst_[1]);
    calc_z_->SetInput(stats_fsth_[0]);
    calc_z_->SetInput(stats_fsth_[1]);
    calc_z_->SetInput(stats_Gst_[0]);
    calc_z_->SetInput(stats_Gst_[1]);
    calc_z_->SetOutput(piter_i_);
    calc_z_->SetOutput(piter_niteri_);
    calc_z_->SetOutput(piter_ih_);
    calc_z_->SetOutput(piter_niterih_);
    calc_z_->SetOutput(piter_igh_);
    calc_z_->SetOutput(piter_niterigh_);
    calc_z_->Prepare();
  }
  calc_z_->Calculate(manager()->all_commands()->dry_run());
  calc_z_->Finalize();
  // ===========================================================================
}

void CCalcMstatspop::PrintOutput(void) {
  /// ==========================================================================
  /// PRINT THE OUTPUT
  /// ==========================================================================
  static bool prepare2 = true;
  if (prepare2) {
    prepare2 = false;
    calc_mstatspop_output_->SetInput(matrix_pol_);
    calc_mstatspop_output_->SetInput(matrix_pol_tcga_);
    calc_mstatspop_output_->SetInput(positions_);
    calc_mstatspop_output_->SetInput(sites_);
    calc_mstatspop_output_->SetInput(sanc_);
    calc_mstatspop_output_->SetInput(argc_);
    calc_mstatspop_output_->SetInput(file_in_);
    calc_mstatspop_output_->SetInput(file_out_);
    calc_mstatspop_output_->SetInput(gfffiles_);
    calc_mstatspop_output_->SetInput(file_GFF_);
    calc_mstatspop_output_->SetInput(subset_positions_);
    calc_mstatspop_output_->SetInput(code_name_);
    calc_mstatspop_output_->SetInput(genetic_code_);
    calc_mstatspop_output_->SetInput(length_);
    calc_mstatspop_output_->SetInput(length_al_);
    calc_mstatspop_output_->SetInput(length_al_real_);
    calc_mstatspop_output_->SetInput(niter_);
    calc_mstatspop_output_->SetInput(ploidy_);
    calc_mstatspop_output_->SetInput(include_unknown_);
    calc_mstatspop_output_->SetInput(force_outgroup_);
    calc_mstatspop_output_->SetInput(outgroup_presence_);
    calc_mstatspop_output_->SetInput(vint_perpop_nsam_);
    calc_mstatspop_output_->SetInput(npops_);
    calc_mstatspop_output_->SetInput(int_total_nsam_);
    calc_mstatspop_output_->SetInput(svratio_);
    calc_mstatspop_output_->SetInput(missratio_);
    calc_mstatspop_output_->SetInput(jfd_);
    calc_mstatspop_output_->SetInput(nfd_);
    calc_mstatspop_output_->SetInput(H1frq_);
    calc_mstatspop_output_->SetInput(H0frq_);
    calc_mstatspop_output_->SetInput(file_H1f_);
    calc_mstatspop_output_->SetInput(file_H0f_);
    calc_mstatspop_output_->SetInput(vector_priors_);
    calc_mstatspop_output_->SetInput(npriors_);
    calc_mstatspop_output_->SetInput(formatfile_);
    calc_mstatspop_output_->SetInput(freq_missing_ms_);
    calc_mstatspop_output_->SetInput(nsites1_pop_);
    calc_mstatspop_output_->SetInput(nsites1_pop_outg_);
    calc_mstatspop_output_->SetInput(nsites2_pop_);
    calc_mstatspop_output_->SetInput(nsites2_pop_outg_);
    calc_mstatspop_output_->SetInput(nsites3_pop_);
    calc_mstatspop_output_->SetInput(nsites3_pop_outg_);
    calc_mstatspop_output_->SetInput(li_);
    calc_mstatspop_output_->SetInput(r2i_ploidies_);
    calc_mstatspop_output_->SetInput(stats_piw_[0]);
    calc_mstatspop_output_->SetInput(stats_pia_[0]);
    calc_mstatspop_output_->SetInput(stats_piT_[0]);
    calc_mstatspop_output_->SetInput(stats_piant_[0]);
    calc_mstatspop_output_->SetInput(stats_piTnt_[0]);
    calc_mstatspop_output_->SetInput(stats_fst_[0]);
    calc_mstatspop_output_->SetInput(stats_piwHKY_[0]);
    calc_mstatspop_output_->SetInput(stats_piaHKY_[0]);
    calc_mstatspop_output_->SetInput(stats_piTHKY_[0]);
    calc_mstatspop_output_->SetInput(stats_fstHKY_[0]);
    calc_mstatspop_output_->SetInput(stats_fst1all_[0]);
    calc_mstatspop_output_->SetInput(stats_Gst_[0]);
    calc_mstatspop_output_->SetInput(stats_hapw_[0]);
    calc_mstatspop_output_->SetInput(stats_hapa_[0]);
    calc_mstatspop_output_->SetInput(stats_hapT_[0]);
    calc_mstatspop_output_->SetInput(stats_fsth_[0]);
    calc_mstatspop_output_->SetInput(stats_fsth1all_[0]);
    calc_mstatspop_output_->SetInput(stats_fstALL_[0]);
    calc_mstatspop_output_->SetInput(stats_fsthALL_[0]);
    calc_mstatspop_output_->SetInput(stats_GstALL_[0]);
    calc_mstatspop_output_->SetInput(stats_S_[0]);
    calc_mstatspop_output_->SetInput(stats_So_[0]);
    calc_mstatspop_output_->SetInput(stats_thetaS_[0]);
    calc_mstatspop_output_->SetInput(stats_thetaSo_[0]);
    calc_mstatspop_output_->SetInput(stats_thetaT_[0]);
    calc_mstatspop_output_->SetInput(stats_thetaTo_[0]);
    calc_mstatspop_output_->SetInput(stats_thetaTHKY_[0]);
    calc_mstatspop_output_->SetInput(stats_thetaFL_[0]);
    calc_mstatspop_output_->SetInput(stats_thetaFW_[0]);
    calc_mstatspop_output_->SetInput(stats_thetaL_[0]);
    calc_mstatspop_output_->SetInput(stats_thetaSA_[0]);
    calc_mstatspop_output_->SetInput(stats_thetaTA_[0]);
    calc_mstatspop_output_->SetInput(stats_K_[0]);
    calc_mstatspop_output_->SetInput(stats_KHKY_[0]);
    calc_mstatspop_output_->SetInput(stats_Dtaj_[0]);
    calc_mstatspop_output_->SetInput(stats_Dfl_[0]);
    calc_mstatspop_output_->SetInput(stats_Ffl_[0]);
    calc_mstatspop_output_->SetInput(stats_Hnfw_[0]);
    calc_mstatspop_output_->SetInput(stats_Ez_[0]);
    calc_mstatspop_output_->SetInput(stats_Yach_[0]);
    calc_mstatspop_output_->SetInput(stats_FH_[0]);
    calc_mstatspop_output_->SetInput(stats_R2_[0]);
    calc_mstatspop_output_->SetInput(stats_Fs_[0]);
    calc_mstatspop_output_->SetInput(stats_Rm_[0]);
    calc_mstatspop_output_->SetInput(stats_ZnA_[0]);
    calc_mstatspop_output_->SetInput(stats_freq_[0]);
    calc_mstatspop_output_->SetInput(stats_nh_[0]);
    calc_mstatspop_output_->SetInput(stats_nhpop_[0]);
    calc_mstatspop_output_->SetInput(stats_freqh_[0]);
    calc_mstatspop_output_->SetInput(stats_length_[0]);
    calc_mstatspop_output_->SetInput(stats_length2_[0]);
    calc_mstatspop_output_->SetInput(stats_lengthamng_[0]);
    calc_mstatspop_output_->SetInput(stats_total_length_[0]);
    calc_mstatspop_output_->SetInput(stats_total_real_length_[0]);
    calc_mstatspop_output_->SetInput(stats_total_svratio_[0]);
    calc_mstatspop_output_->SetInput(stats_total_tcga_[0]);
    calc_mstatspop_output_->SetInput(stats_tcga_[0]);
    calc_mstatspop_output_->SetInput(stats_sv_[0]);
    calc_mstatspop_output_->SetInput(stats_svT_[0]);
    calc_mstatspop_output_->SetInput(stats_nmhits_[0]);
    calc_mstatspop_output_->SetInput(stats_H1freq_[0]);
    calc_mstatspop_output_->SetInput(stats_thetaH1_[0]);
    calc_mstatspop_output_->SetInput(stats_H0freq_[0]);
    calc_mstatspop_output_->SetInput(stats_thetaH0_[0]);
    calc_mstatspop_output_->SetInput(stats_ToH0_ii_[0]);
    calc_mstatspop_output_->SetInput(stats_ToH0_00_[0]);
    calc_mstatspop_output_->SetInput(stats_To_ii_[0]);
    calc_mstatspop_output_->SetInput(stats_To_00_[0]);
    calc_mstatspop_output_->SetInput(stats_To_i0_[0]);
    calc_mstatspop_output_->SetInput(stats_To_Qc_ii_[0]);
    calc_mstatspop_output_->SetInput(stats_To_Qw_ii_[0]);
    calc_mstatspop_output_->SetInput(stats_To_Lc_ii_[0]);
    calc_mstatspop_output_->SetInput(stats_mdsd_[0]);
    calc_mstatspop_output_->SetInput(stats_mdg1_[0]);
    calc_mstatspop_output_->SetInput(stats_mdg2_[0]);
    calc_mstatspop_output_->SetInput(stats_mdw_[0]);
    calc_mstatspop_output_->SetInput(stats_linefreq_[0]);
    calc_mstatspop_output_->SetInput(stats_anx_[0]);
    calc_mstatspop_output_->SetInput(stats_bnx_[0]);
    calc_mstatspop_output_->SetInput(stats_anxo_[0]);
    calc_mstatspop_output_->SetInput(stats_bnxo_[0]);
    calc_mstatspop_output_->SetInput(stats_R2p_[0]);
    calc_mstatspop_output_->SetInput(piter_i_);
    calc_mstatspop_output_->SetInput(piter_ih_);
    calc_mstatspop_output_->SetInput(piter_igh_);
    calc_mstatspop_output_->SetInput(piter_i1_);
    calc_mstatspop_output_->SetInput(piter_ih1_);
    calc_mstatspop_output_->SetInput(piter_niteri_);
    calc_mstatspop_output_->SetInput(piter_niterih_);
    calc_mstatspop_output_->SetInput(piter_niterigh_);
    calc_mstatspop_output_->SetInput(piter_niteri1_);
    calc_mstatspop_output_->SetInput(piter_niterih1_);
    calc_mstatspop_output_->SetInput(piter_iall_);
    calc_mstatspop_output_->SetInput(piter_ihall_);
    calc_mstatspop_output_->SetInput(piter_ighall_);
    calc_mstatspop_output_->SetInput(piter_niteriall_);
    calc_mstatspop_output_->SetInput(piter_niterihall_);
    calc_mstatspop_output_->SetInput(piter_niterighall_);
    calc_mstatspop_output_->SetInput(output_);
    calc_mstatspop_output_->SetInput(seed_);
    calc_mstatspop_output_->SetInput(length_seg_);
    calc_mstatspop_output_->Prepare();
  }
  calc_mstatspop_output_->Calculate(manager()->all_commands()->dry_run());
  calc_mstatspop_output_->Finalize();
  // ===========================================================================
  
  ConcatenateIterationResults();
}

void CCalcMstatspop::DataMemoryAllocation(long int npops,
                                         long int int_total_nsam,
                                         int outgroup_presence) {
  //
  // Non DM data is automatically free when this calculation is finished.
  // DM data is automatically free when the ngaSP application is closed.
  //
  
  nsam2_->ReserveMemory(2, 0);
  psam2_->ReserveMemory(2, 0);
  nsites1_pop_->ReserveMemory(npops, 0);
  nsites2_pop_->ReserveMemory(npops, 0);
  nsites3_pop_->ReserveMemory(npops, 0);
  nsites1_pop_outg_->ReserveMemory(npops, 0);
  nsites2_pop_outg_->ReserveMemory(npops, 0);
  nsites3_pop_outg_->ReserveMemory(npops, 0);
  anx_->ReserveMemory(npops, 0);
  bnx_->ReserveMemory(npops, 0);
  anxo_->ReserveMemory(npops, 0);
  bnxo_->ReserveMemory(npops, 0);
  lengthamng_->ReserveMemory(npops, npops, 0.0);
  sum_sam_->ReserveMemory(int_total_nsam + !outgroup_presence, 0);
  tcga_->ReserveMemory(int_total_nsam + !outgroup_presence, 4, 0);

  stats_piw_[0]->ReserveMemory(npops, 0.0);
  stats_pia_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_piT_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_piant_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_piTnt_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_fst_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_piwHKY_[0]->ReserveMemory(npops, 0.0);
  stats_piaHKY_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_piTHKY_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_fstHKY_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_fst1all_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_Gst_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_hapw_[0]->ReserveMemory(npops, 0.0);
  stats_hapa_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_hapT_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_fsth_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_fsth1all_[0]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_S_[0]->ReserveMemory(npops, 0.0);
  stats_So_[0]->ReserveMemory(npops, 0.0);
  stats_thetaS_[0]->ReserveMemory(npops, 0.0);
  stats_thetaSo_[0]->ReserveMemory(npops, 0.0);
  stats_thetaT_[0]->ReserveMemory(npops, 0.0);
  stats_thetaTo_[0]->ReserveMemory(npops, 0.0);
  stats_thetaTHKY_[0]->ReserveMemory(npops, 0.0);
  stats_thetaFL_[0]->ReserveMemory(npops, 0.0);
  stats_thetaFW_[0]->ReserveMemory(npops, 0.0);
  stats_thetaL_[0]->ReserveMemory(npops, 0.0);
  stats_thetaSA_[0]->ReserveMemory(npops, 0.0);
  stats_thetaTA_[0]->ReserveMemory(npops, 0.0);
  stats_K_[0]->ReserveMemory(npops, 0.0);
  stats_KHKY_[0]->ReserveMemory(npops, 0.0);
  stats_Dtaj_[0]->ReserveMemory(npops, 0.0);
  stats_Dfl_[0]->ReserveMemory(npops, 0.0);
  stats_Ffl_[0]->ReserveMemory(npops, 0.0);
  stats_Hnfw_[0]->ReserveMemory(npops, 0.0);
  stats_Ez_[0]->ReserveMemory(npops, 0.0);
  stats_Yach_[0]->ReserveMemory(npops, 0.0);
  stats_FH_[0]->ReserveMemory(npops, 0.0);
  stats_R2_[0]->ReserveMemory(npops, 0.0);
  stats_Fs_[0]->ReserveMemory(npops, 0.0);
  stats_Rm_[0]->ReserveMemory(npops, 0);
  stats_ZnA_[0]->ReserveMemory(npops, 0.0);
  stats_freq_[0]->ReserveMemory(npops, (*vint_perpop_nsam_).GetData(), 0.0);
  stats_freqh_[0]->ReserveMemory(npops, int_total_nsam, 0);
  stats_nhpop_[0]->ReserveMemory(npops, 0);
  stats_length_[0]->ReserveMemory(npops, 0.0);
  stats_length2_[0]->ReserveMemory(npops, 0.0);
  stats_lengthamng_[0]->ReserveMemory(npops, npops, 0.0);
  stats_total_tcga_[0]->ReserveMemory(4, 0.0);
  stats_tcga_[0]->ReserveMemory(npops, 4, 0.0);
  stats_sv_[0]->ReserveMemory(npops, npops, 2, 0.0);
  stats_svT_[0]->ReserveMemory(npops, npops, 2, 0.0);
  stats_ToH0_ii_[0]->ReserveMemory(npops, 0.0);
  stats_ToH0_00_[0]->ReserveMemory(npops, 0.0);
  stats_To_ii_[0]->ReserveMemory(npops, 0.0);
  stats_To_00_[0]->ReserveMemory(npops, 0.0);
  stats_To_i0_[0]->ReserveMemory(npops, 0.0);
  stats_To_Qc_ii_[0]->ReserveMemory(npops, 0.0);
  stats_To_Qw_ii_[0]->ReserveMemory(npops, 0.0);
  stats_To_Lc_ii_[0]->ReserveMemory(npops, 0.0);
  stats_mdsd_[0]->ReserveMemory(npops, 0.0);
  stats_mdg1_[0]->ReserveMemory(npops, 0.0);
  stats_mdg2_[0]->ReserveMemory(npops, 0.0);
  stats_linefreq_[0]->ReserveMemory(int_total_nsam, int_total_nsam + 1, 0.0);
  stats_anx_[0]->ReserveMemory(npops, 0.0);
  stats_bnx_[0]->ReserveMemory(npops, 0.0);
  stats_anxo_[0]->ReserveMemory(npops, 0.0);
  stats_bnxo_[0]->ReserveMemory(npops, 0.0);
  stats_mdw_[0]->ReserveMemory(npops, (*mdw_reg_lengths_).GetData(), 0.0);
  stats_piw_[1]->ReserveMemory(npops, 0.0);
  stats_pia_[1]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_piT_[1]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_fst_[1]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_piwHKY_[1]->ReserveMemory(npops, 0.0);
  stats_piaHKY_[1]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_piTHKY_[1]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_fstHKY_[1]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_fst1all_[1]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_hapw_[1]->ReserveMemory(npops, 0.0);
  stats_hapa_[1]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_hapT_[1]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_fsth_[1]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_fsth1all_[1]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_Gst_[1]->ReserveMemory((npops*(npops-0))/2, 0.0);
  stats_K_[1]->ReserveMemory(npops, 0.0);
  stats_KHKY_[1]->ReserveMemory(npops, 0.0);
  stats_sv_[1]->ReserveMemory(npops, npops, 2, 0.0);
  stats_svT_[1]->ReserveMemory(npops, npops, 2, 0.0);
  stats_nhpop_[1]->ReserveMemory(npops, 0.0);
  stats_freqh_[1]->ReserveMemory(npops, int_total_nsam, 0.0);
  stats_tcga_[1]->ReserveMemory(npops, 4, 0.0);
  stats_length_[1]->ReserveMemory(npops, 0.0);
  stats_length2_[1]->ReserveMemory(npops, 0.0);
  stats_lengthamng_[1]->ReserveMemory(npops, npops, 0.0);

  piter_i1_->ReserveMemory(npops, 0);
  piter_ih1_->ReserveMemory(npops, 0);
  piter_i_->ReserveMemory((npops*(npops-0))/2, 0);
  piter_ih_->ReserveMemory((npops*(npops-0))/2, 0);
  piter_igh_->ReserveMemory((npops*(npops-0))/2, 0);
  piter_niteri1_->ReserveMemory(npops, 0);
  piter_niterih1_->ReserveMemory(npops, 0);
  piter_niteri_->ReserveMemory((npops*(npops-0))/2, 0);
  piter_niterih_->ReserveMemory((npops*(npops-0))/2, 0);
  piter_niterigh_->ReserveMemory((npops*(npops-0))/2, 0);
  
  for(int x=0;x<npops_->value();x++) {
      for(int w=0;w<4;w++) {
          (*stats_tcga_[1])[x][w] = (*stats_tcga_[0])[x][w];
      }
  }

  stats_total_length_[1]->set_value(length_al_->value());
  stats_total_svratio_[1]->set_value(svratio_->value());
  stats_nmhits_[1]->set_value(nmhits_->value()); 
  piter_iall_->set_value(0);
  piter_ihall_->set_value(0);
  piter_ighall_->set_value(0);
  piter_niteriall_->set_value(0);
  piter_niterihall_->set_value(0);
  piter_niterighall_->set_value(0);

  if(int_total_nsam_order_->value() == 0) {
    int_total_nsam_order_->set_value(int_total_nsam_->value()-!outgroup_presence_->value());
    sort_nsam_->ReserveMemory(int_total_nsam, 0);
    for(int sort_index = 0;
        sort_index < int_total_nsam_->value(); sort_index++ ) {
      (*sort_nsam_)[sort_index] = sort_index;
    }
  }
}

void CCalcMstatspop::DeleteIterationVariables(void) {
  matrix_pol_->DeleteMemory();
  frequencies_->DeleteMemory();
  positions_->DeleteMemory();
  matrix_sv_->DeleteMemory();
  sites_->DeleteMemory();
  jfd_->DeleteMemory();
  nfd_->DeleteMemory();
  
  if ((file_mas_->value()[0] == '-') &&
      ((formatfile_->value() == MS_FILE) || (formatfile_->value() == MS_X_FILE))) {
    sum_sam_mask_->DeleteMemory();
  } else {
    matrix_pol_tcga_->DeleteMemory();
  }
}

void CCalcMstatspop::ShowMstatspopInformation(void) {
  //
  // Print Header.
  //
  
  DM_GET_DATA3(CDataStdString, all_command_line_, STR(ALL_COMMAND_LINE))
  
  if ((output_->value() == 0) || (output_->value() == 10)) {
    fprintf(manager()->foutput(), STR(MSTATSPOP_DESC).c_str());
    fprintf(manager()->foutput(), STR(EOL).c_str());
    fprintf(manager()->foutput(), all_command_line_->value().c_str());
    fprintf(manager()->foutput(), STR(SPACE).c_str());
    fprintf(manager()->foutput(), STR(MSTATSPOP_OUTPUT_TITLE).c_str());
  }
}

void CCalcMstatspop::Print(std::string message) {
  //
  // Show a message to the user.
  //
  if (output_->value() == 0 || output_->value() == 10) {
    fprintf(manager()->foutput(), message.c_str());
    fprintf(manager()->foutput(), STR(EOL).c_str());
    fflush(manager()->foutput());
  }
}

void CCalcMstatspop::ChangeUserInputsIfNecessary(void) {
  //
  // Set the length_al_:
  //
  //
  //if ((formatfile_->value() == MS_FILE) || (formatfile_->value() == MS_X_FILE)) {
  //  length_al_->set_value(length_->value());
  //}

    //
	// introduce the data and mask file (last if necessary)
	//
	if (mask_print_->value() == 1 && ((formatfile_->value() == FASTA_FILE ||
     (formatfile_->value() == TFASTA_FILE && ((slide_->value() == 0 && window_->value() == 0) && 
      file_wcoord_->value() == ""))))) {
       
		if (file_in_->value() == "") {
      file_mas_->set_value(STR(DEFAULT_MASK_FILE_NAME_START) + STR(MASK_POPS_MARK) + CStringTools::ToString(npops_->value()-!outgroup_presence_->value()) + "_nsam" + CStringTools::ToString(int_total_nsam_->value()-!outgroup_presence_->value()));
    } else {
      file_mas_->set_value(CFile::GetPathFileNameWithoutExtension(file_in_->value()) + STR(MASK_POPS_MARK) + CStringTools::ToString(npops_->value()-!outgroup_presence_->value()) + "_nsam" + CStringTools::ToString(int_total_nsam_->value()-!outgroup_presence_->value()));
    }
      
    if (gfffiles_->value() == YES) {
      file_mas_->add(STR(CONTINUE_LINE) + subset_positions_->GetDataString(false));
      file_mas_->add(STR(CONTINUE_LINE) + criteria_transcript_->GetDataString(false));
    }

    if(!include_unknown_->value()) {
      file_mas_->add(STR(MASK_EXCLUDE_MIS_VARIANTS_MARK));
    }
    else {
      file_mas_->add(STR(MASK_INCLUDE_MIS_VARIANTS_MARK));
    }

    if(outgroup_presence_->value() == NO) {
      file_mas_->add(STR(MASK_NO_OUTGROUP_PRESENCE_MARK));
    }

    if(outgroup_presence_->value() == YES) {
      file_mas_->add(STR(MASK_OUTGROUP_PRESENCE_MARK));
    }

    if(ploidy_->value() == HAPLOID) {
      file_mas_->add(STR(MASK_PLOIDY_1_MARK));
    }

    if(ploidy_->value() == DIPLOID) {
      file_mas_->add(STR(MASK_PLOIDY_2_MARK));
    }            

    file_mas_->add(STR(DEFAULT_MASK_FILE_NAME_END));
	}

    //
	// Set the genetic_code_:
	//  
  if ((gfffiles_->value() == YES) && (
      (subset_positions_->GetDataString(false) == STR(SUBSET_POS_SYNONYMOUS)) ||
      (subset_positions_->GetDataString(false) == STR(SUBSET_POS_NONSYNONYMOUS)) ||
      (subset_positions_->GetDataString(false) == STR(SUBSET_POS_0_FOLD)) ||
      (subset_positions_->GetDataString(false) == STR(SUBSET_POS_2_FOLD)) ||
      (subset_positions_->GetDataString(false) == STR(SUBSET_POS_3_FOLD)) ||
      (subset_positions_->GetDataString(false) == STR(SUBSET_POS_4_FOLD)) ||
      (subset_positions_->GetDataString(false) == STR(SUBSET_POS_SILENT)))) {
    CDnaTools dna_tools;
    genetic_code_->set_text_string(
    dna_tools.genetic_codes_[(*code_name_).GetDataString(false)]);
  }  
}

void CCalcMstatspop::AddOneOutgroupIfItIsNotPresent(void) {
  //
  // Add one outgroup at the end if it is not present:
  //
  if (outgroup_presence_->value() == NO) {
    populations_initial_->set_value(populations_initial_->value() + ",1");
    CreateThePopulationsVector();
  }
}

void CCalcMstatspop::CreateThePopulationsVector(void) {
  //
  // Create the populations vector:
  //
  vint_perpop_nsam_->set_data_string(populations_initial_->value());
  npops_->set_value(vint_perpop_nsam_->reg_length());
  int_total_nsam_->set_value(0);
  for (std::size_t i = 0; i < vint_perpop_nsam_->reg_length(); i++) {
    int_total_nsam_->add((*vint_perpop_nsam_)[i]);
  }
}

void CCalcMstatspop::Calculate(bool dry_run) {
  if (dry_run == true) {
    return;
  }
 

/// ============================================================================
/// CALCULATE - MSTATSTPOP MAIN FUNCTION
/// ============================================================================
   
  CreateThePopulationsVector();
  
  ChangeUserInputsIfNecessary();

  GetSumOfPopulations();

  AddOneOutgroupIfItIsNotPresent();

  // ordering data: in case O is not a flag included
  if(int_total_nsam_order_->value() > 0 && int_total_nsam_order_->value()+!outgroup_presence_->value() != int_total_nsam_->value()) {
    ERROR_MSG << STR(SORT_NSAM_ERROR)
              END_MSG;
  }
  
  MultiplyPopulationsDependingOnPloidy();
      
  CalcMdwRegLengths();

  ICalculation *calc_randomize_ = NULL;
  DM_GET_CALC(calc_randomize_)
  if (calc_randomize_ != NULL) {
    (static_cast<CCalcRandomize *>(calc_randomize_))->InitSeed(seed_->value());
  }  else {
    ERROR_MSG << "CCalcMstatspop::" << "Randomize does not exist..." END_MSG;
  }
 
 
  DataMemoryAllocation(npops_->value(),
                       int_total_nsam_->value(),
                       outgroup_presence_->value());

 
  if (file_wps_->value() != "") {
    ReadWeightPositionsFile();
  } else {
    wP_->DeleteMemory();
  }

  if (file_wcoord_->value() == "") {
    file_wcoord_->set_value("");
    nwindows_->set_value(0);
  } else {
    ReadCoordinatesFile();
    window_->set_value(-1);
	  slide_->set_value(-1);
  }
  
  
  if (file_effsz_->value() != "") {
    ReadEffectSizesFile();
    
    if(wlimit_end_->value() > 0 && welimit_end_->value() > 0) {
      if(wlimit_end_->value() != welimit_end_->value()) {
        ERROR_MSG << STR(ERROR_POSITION_LENGTHS)
                  END_MSG;
      }
    }    
  } else {
    wV_->DeleteMemory();
  }

  ShowMstatspopInformation();
  
  OpenAlternativeAndFreqSpectrumFile();

  if (formatfile_->value() == FASTA_FILE) {
    ReadFastaFile();

		// define variables for mhits
		nmhits_->set_value(0);
    mhitbp_->ReserveMemory(n_site_->value(), 0);
    
    
    if (gfffiles_->value() == YES) {
      FilterDnaMatrixWithGFFFile();
    }

    CalculateStats();
    
    niterdata_->set_value(1);
  }

  if ((formatfile_->value() == MS_FILE) ||
      (formatfile_->value() == MS_X_FILE)) {
      svratio_->set_value(ms_svratio_->value());
      MsMaskFile();
  }

  li_->set_value(0);
  
  while(li_->value() < niterdata_->value()) {
    flaghky_->set_value(1);
    
    if ((formatfile_->value() == MS_FILE) ||
        (formatfile_->value() == MS_X_FILE)) {
      OpenMsFile();

      CalcX();
    }

    if (formatfile_->value() == TFASTA_FILE) {
      if (ReadTFastaFile() == false) {
        // printf("End processing input tfa data.\n");
        break;
      }
      // When the tfa file is finished then li=0,
      // otherwise li=-1 and the loop continue.
      
      CalculateStats();
    }
    
    CalEffectiveNucleotidesAndTCGAFreqs();

    IncludeLengthMngAndCalculations();

    CalcSxsfss();

    CalcJointFreqDistribution();

    CalcPiwpiafst_1();

    CalcFrequencyStats();

    if ((H1frq_->value()) && (include_unknown_->value() == NO)) {
      CalcOptimalTests();
    }

    CalcR2();

    CalcR2p();

    CalcMismatch();

    if (ploidy_->value() == HAPLOID) {
      CalcHwhafsth_1();
      CalcFs();
    }

    // Un monton de cosas casi-repes que volvemos a utilizar!
    // PERMUTATION
    // Only if not MS format

    if ((niter_->value()) && (npops_->value() > 2)) {
      // =======================================================================
      // Initialize
      // =======================================================================
  
//      stats_piw_[1]->InitMemory(0.);
//      stats_pia_[1]->InitMemory(0.);
//      stats_piT_[1]->InitMemory(0.);
//      stats_fst_[1]->InitMemory(0.);
//      stats_piwHKY_[1]->InitMemory(0.);
//      stats_piaHKY_[1]->InitMemory(0.);
//      stats_piTHKY_[1]->InitMemory(0.);
//      stats_fstHKY_[1]->InitMemory(0.);
//      stats_fst1all_[1]->InitMemory(0.);
//      stats_hapw_[1]->InitMemory(0.);
//      stats_hapa_[1]->InitMemory(0.);
//      stats_hapT_[1]->InitMemory(0.);
//      stats_fsth_[1]->InitMemory(0.);
//      stats_fsth1all_[1]->InitMemory(0.);
//      stats_Gst_[1]->InitMemory(0.);
//      stats_K_[1]->InitMemory(0.);
//      stats_KHKY_[1]->InitMemory(0.);
//      stats_freq_[1] = 0;
//      stats_sv_[1]->InitMemory(0.);
//      stats_svT_[1]->InitMemory(0.);
//      stats_nhpop_[1]->InitMemory(0);
//      stats_freqh_[1]->InitMemory(0);
//      stats_tcga_[1]->InitMemory(0.);
//      stats_length_[1]->InitMemory(0.);
//      stats_length2_[1]->InitMemory(0.);
//      stats_lengthamng_[1]->InitMemory(0.);
      
      stats_piw_[1]->ReserveMemory(npops_->value());
      stats_pia_[1]->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      stats_piT_[1]->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      stats_fst_[1]->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      stats_piwHKY_[1]->ReserveMemory(npops_->value());
      stats_piaHKY_[1]->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      stats_piTHKY_[1]->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      stats_fstHKY_[1]->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      stats_fst1all_[1]->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      stats_hapw_[1]->ReserveMemory(npops_->value());
      stats_hapa_[1]->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      stats_hapT_[1]->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      stats_fsth_[1]->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      stats_fsth1all_[1]->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      stats_Gst_[1]->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      stats_K_[1]->ReserveMemory(npops_->value());
      stats_KHKY_[1]->ReserveMemory(npops_->value());
      stats_sv_[1]->ReserveMemory(npops_->value(), npops_->value(), 2);
      stats_svT_[1]->ReserveMemory(npops_->value(), npops_->value(), 2);
      stats_nhpop_[1]->ReserveMemory(npops_->value());
      stats_freqh_[1]->ReserveMemory(npops_->value(), int_total_nsam_->value());
      stats_tcga_[1]->ReserveMemory(npops_->value(), 4);
      stats_length_[1]->ReserveMemory(npops_->value());
      stats_length2_[1]->ReserveMemory(npops_->value());
      stats_lengthamng_[1]->ReserveMemory(npops_->value(), npops_->value());

      
      for(int x=0;x<npops_->value();x++) {
          for(int w=0;w<4;w++) {
              (*stats_tcga_[1])[x][w] = (*stats_tcga_[0])[x][w];
          }
      }        

      stats_total_length_[1]->set_value(length_al_->value());
      stats_total_svratio_[1]->set_value(svratio_->value());
      stats_nmhits_[1]->set_value(nmhits_->value()); 
      
//      piter_i1_->InitMemory(0.);
//      piter_ih1_->InitMemory(0.);
//      piter_i_->InitMemory(0.);
//      piter_ih_->InitMemory(0.);
//      piter_igh_->InitMemory(0.);
//      piter_niteri1_->InitMemory(0.);
//      piter_niterih1_->InitMemory(0.);
//      piter_niteri_->InitMemory(0.);
//      piter_niterih_->InitMemory(0.);
//      piter_niterigh_->InitMemory(0.);      
      
      piter_i1_->ReserveMemory(npops_->value());
      piter_ih1_->ReserveMemory(npops_->value());
      piter_i_->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      piter_ih_->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      piter_igh_->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      piter_niteri1_->ReserveMemory(npops_->value());
      piter_niterih1_->ReserveMemory(npops_->value());
      piter_niteri_->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      piter_niterih_->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
      piter_niterigh_->ReserveMemory((npops_->value()*(npops_->value()-0))/2);
  
      piter_iall_->set_value(0);
      piter_ihall_->set_value(0);
      piter_ighall_->set_value(0);
      piter_niteriall_->set_value(0);
      piter_niterihall_->set_value(0);
      piter_niterighall_->set_value(0);

      matrix_perm_->ReserveMemory(length_seg_->value() * int_total_nsam_->value());
      
      // =======================================================================

      Print(STR(CALCULATING_PERMUTATION_TESTS));

      //
      // permute 1 pop against rest pops (1 vs all rest (or 2 vs all rest),
      // that means ALL mixed). Do once is enough
      //
      if (npops_->value() > 2) {
        for (int i1 = 0; i1 < niter_->value(); i1++) {
          (*nsam2_)[0] = (*vint_perpop_nsam_)[0];
          (*nsam2_)[1] =
                      int_total_nsam_->value() -
                      (*vint_perpop_nsam_)[npops_->value()-1] -
                      (*vint_perpop_nsam_)[0];
          (*psam2_)[0] = 0;
          (*psam2_)[1] = (*vint_perpop_nsam_)[0];


          Permute_2();

          // HERE WE ASSUME THAT THE LENGTH SIZE ARE THE SAME THAN FOR ORIGINAL SAMPLES!!
          for(int x=0;x<npops_->value();x++) {
              (*stats_length_[1])[x]  = (*stats_length_[0])[x];
              (*stats_length2_[1])[x] = (*stats_length2_[0])[x];

              for(int y_ite=0;y_ite<npops_->value();y_ite++) {
                  (*stats_lengthamng_[1])[x][y_ite] = (*stats_lengthamng_[0])[x][y_ite];
              }
          }            

          CalcPiwpiafst_2();

          if (ploidy_->value() == HAPLOID) {
            CalcHwhafsth_2();
          }
          CalcY();
        }

        Print(STR(PERMUTATION_TESTS_DONE));
      }

      Print(STR(CALCULATING_PERMUTATION_TESTS_PAIR));

      // permute pairs of pops
      for (int i2 = 0; i2 < niter_->value(); i2++) {
        z_pos_->set_value(0);

        (*psam2_)[0] = 0;
        (*psam2_)[1] = 0;

        for (int x = 0; x < npops_->value()-1 - !outgroup_presence_->value(); x++) {
          (*nsam2_)[0] = (*vint_perpop_nsam_)[x];
          (*psam2_)[1] = (*psam2_)[0] +
                             (*vint_perpop_nsam_)[x];

          //!20160509 vint_perpop_nsam_iter_->Copy(*vint_perpop_nsam_);

          for (int y = x+1; y < npops_->value() - !outgroup_presence_->value(); y++) {
            (*nsam2_)[1] = (*vint_perpop_nsam_)[y];

            Permute_3();

            // HERE WE ASSUME THAT THE LENGTH SIZE ARE THE SAME THAN FOR ORIGINAL SAMPLES!!
            (*stats_length_[1])[x]  = (*stats_length_[0])[x];
            (*stats_length2_[1])[x] = (*stats_length2_[0])[x];
            for(int yy=0;yy<npops_->value();yy++) {
                (*stats_lengthamng_[1])[x][yy] = (*stats_lengthamng_[0])[x][yy];
            }
            
            CalcPiwpiafst_3();

            if (ploidy_->value() == HAPLOID) {
              CalcHwhafsth_3();
            }

            CalcZ();

            (*psam2_)[1] += (*vint_perpop_nsam_)[y]; // !outgroup_presence at loops
            z_pos_->set_value(z_pos_->value() + 1);
          }
          (*psam2_)[0] += (*vint_perpop_nsam_)[x];
        }
      }
    }

    
    PrintOutput();
    
    DeleteIterationVariables();
    
    li_->add(1);
  }
  
  if (formatfile_->value() == MS_FILE) {
    calc_mstatspop_open_ms_->Finalize();
  }
}

void CCalcMstatspop::Finalize(void) {
/// ============================================================================
/// STOP WRITING OUTPUT TO THE OUTPUT FILE
/// ============================================================================
  if (file_out_->value() != "") {
    manager()->RedirectCoutToScreenAgain();
  }   
 

  
  DM_DEL_ALL_LOCAL_DATA   
}


void CCalcMstatspop::ConcatenateIterationResults(void) {
  int np = 0,
      x  = 0;
  

  if(formatfile_->value() != MS_X_FILE) {
    if(outgroup_presence_->value() == 1) {
      np = npops_->value() - 1;
  
      for(x = 0; x < np; x++) {
        if((*vint_perpop_nsam_)[x] > 1) {
          (*stats_thetaSo_[0])[x] /= (*nsites2_pop_outg_)[x];                   // Theta/nt(Wat)
          (*stats_thetaTo_[0])[x] /= (*nsites2_pop_outg_)[x];                   // Theta/nt(Taj)
          (*stats_thetaFL_[0])[x] /= (*nsites2_pop_outg_)[x];                   // Theta/nt(Fu&Li)
          (*stats_thetaFW_[0])[x] /= (*nsites2_pop_outg_)[x];                   // Theta/nt(Fay&Wu)
          (*stats_thetaL_[0])[x]  /= (*nsites2_pop_outg_)[x];                   // Theta/nt(Zeng)

          if((*vint_perpop_nsam_)[x] > 2) {
            (*stats_thetaSA_[0])[x] /= (*nsites3_pop_outg_)[x];                 // Theta/nt(Achaz,Wat)
            (*stats_thetaTA_[0])[x] /= (*nsites3_pop_outg_)[x];                 // Theta/nt(Achaz,Taj)
          }

          (*stats_K_[0])[x] /= (*nsites1_pop_outg_)[x];                         //  Divergence
        }
      }
    }
    else {
      np = npops_->value()-1;
      for(x = 0; x < np; x++) {
        if((*vint_perpop_nsam_)[x] > 1) {
          (*stats_thetaS_[0])[x] /= (*nsites2_pop_)[x];                         // Theta/nt(Wat)
          (*stats_thetaT_[0])[x] /= (*nsites2_pop_)[x];                         // Theta/nt(Taj)
          (*stats_thetaFL_[0])[x] /= (*nsites2_pop_)[x];                        // Theta/nt(Fu&Li)

          if((*vint_perpop_nsam_)[x] > 2) {
            (*stats_thetaSA_[0])[x] /= (*nsites3_pop_)[x];                      // Theta/nt(Achaz,Wat)
            (*stats_thetaTA_[0])[x] /= (*nsites3_pop_)[x];                      // Theta/nt(Achaz,Taj)
          }
        }
      }
    }
  }


//  if(outgroup_presence_->value() == 1) {
//     np = npops_->value() - 1;
//     for(x = 0; x < np; x++) {
//       if((*stats_thetaT_[0])[x]-(*stats_thetaFW_[0])[x] != NA_VALUE) {
//         (*stats_thetaT_[0])[x] -= (*stats_thetaFW_[0])[x];                      // Fay&WuH
//       }
//     }
//   }
// 
// 
//   if(npops_->value() - 1 > 1) {
//     if(npops_->value() - 1 > 2) {
//       if(stats_fstALL_[0]->value() > NA_VALUE) {
//         if(niter_->value() && piter_niteriall_ > 0) {
//           // stats_fstALL_[0]->value()                                          // Fst
//           // (double)piter_iall->value()/(double)piter_niteriall_->value()      // P-value
//         }
//       }
// 
//       if(ploidy_->value() == HAPLOID && include_unknown_->value() == 0) {
//         if(stats_fsthALL_[0]->value() > NA_VALUE) {
//           if(niter_->value() && piter_niterihall_ > 0) {
//           // stats_fsthALL_[0]->value()                                         // FstH
//           // (double)piter_ihall->value()/(double)piter_niterihall->value()     // P-value
//           }
//         }
//       }
// 
//       
//       for(x = 0; x < npops_->value() - 1; x++) {
//         if((*stats_fst1all_[0])[x] > NA_VALUE) {
//           if(niter_->value() && (*piter_niteri1_)[x] > 0) {
//             // (*stats_fst1all_[0])[x]                                          // Fst1
//             // (double)(*piter_i1)[x]/(double)(*piter_niteri1)[x]               // P-value
//           }
//         }
// 
//         if(ploidy_->value() == HAPLOID && include_unknown_->value() == 0) {
//           if((*stats_fsth1all_[0])[x] > NA_VALUE) {
//             if(niter_->value() && (*piter_niterih1_)[x] > 0) {
//               // (*stats_fsth1all_[0])[x]                                       // Fst1H
//               // (double)(*piter_ih1)[x]/(double)(*piter_niterih1)[x]           // P-value
//             }
//           }
//         }
//       }
//     }
// 
//     z = 0;
//     for(x = 0; x < npops_->value() - 1; x++) {
//       for(y = x + 1; y < npops_->value() - 0; y++) {
//         if(y == npops_->value() - 1) {
//           z++;
//           continue;
//         }
//         if((*stats_fst_[0])[z] > NA_VALUE) {
//           if(niter_->value() && (*piter_niteri_)[z] > 0) {
//             // (*stats_fst)[z]                                                  // Fst
//             // (double)(*piter_i)[z]/(double)(*piter_niteri)[z]                 // P-value
//           }
//         }
//         z++;
//       }
//     }
// 
//     z = 0;
//     for(x = 0; x < npops_->value() - 2; x++) {
//       for(y = x + 1; y < npops_->value() - 1; y++) {
//         if(y == npops_->value() - 1) {
//           z++;
//           continue;
//         }
//         if(ploidy_->value() == HAPLOID && include_unknown_->value() == 0) {
//           if((*stats_fsth_[0])[z] > NA_VALUE) {
//             if(niter_->value() && (*piter_niterih_)[z] > 0) {
//               // (*stats_fsth)[z]                                               // FstH
//               // (double)(*piter_ih)[z]/(double)(*piter_niterih)[z]             // P-value
//             }
//           }
//         }
//         z++;
//       }
//     }
// }

  /// ==========================================================================
  /// CONCATENATE ITERARION RESULTS INTO FINAL OUTPUT DATAS
  /// ==========================================================================
  out_stats_thetaSo_->Append(*(stats_thetaSo_[0])); 
  out_stats_thetaSo_->Append(*(stats_thetaSo_[0]));       // Theta/nt(Wat) *1
  out_stats_thetaTo_->Append(*(stats_thetaTo_[0]));       // Theta/nt(Taj) *2
  out_stats_thetaFL_->Append(*(stats_thetaFL_[0]));       // Theta/nt(Fu&Li)
  out_stats_thetaFW_->Append(*(stats_thetaFW_[0]));       // Theta/nt(Fay&Wu)
  out_stats_thetaL_->Append(*(stats_thetaL_[0]));         // Theta/nt(Zeng)
  out_stats_thetaSA_->Append(*(stats_thetaSA_[0]));       // Theta/nt(Achaz,Wat)
  out_stats_thetaTA_->Append(*(stats_thetaTA_[0]));       // Theta/nt(Achaz,Taj)
  out_stats_K_->Append(*(stats_K_[0]));                   // Divergence/nt
  out_stats_thetaTHKY_->Append(*(stats_thetaTHKY_[0]));   // Theta/nt(Taj)HKY
  out_stats_KHKY_->Append(*(stats_KHKY_[0]));             // DivergenceHKY
  out_stats_thetaS_->Append(*(stats_thetaS_[0]));         // Theta/nt(Wat)  *1
  out_stats_thetaT_->Append(*(stats_thetaT_[0]));         // Theta/nt(Taj)  *2
  out_stats_hapw_->Append(*(stats_hapw_[0]));             // HapW
  out_stats_nhpop_->Append(*(stats_nhpop_[0]));           // nHap
  out_stats_Dtaj_->Append(*(stats_Dtaj_[0]));             // Tajima D
  out_stats_Dfl_->Append(*(stats_Dfl_[0]));               // Fu&Li D
  out_stats_Ffl_->Append(*(stats_Ffl_[0]));               // Fu&Li F
  out_stats_Hnfw_->Append(*(stats_Hnfw_[0]));             // Fay&Wu norm H
  out_stats_Ez_->Append(*(stats_Ez_[0]));                 // Zeng E
  out_stats_Yach_->Append(*(stats_Yach_[0]));             // Achaz Y
  out_stats_FH_->Append(*(stats_FH_[0]));                 // 
  out_stats_Fs_->Append(*(stats_Fs_[0]));                 // Fs
  out_stats_mdsd_->Append(*(stats_mdsd_[0]));             // SDev
  out_stats_mdg1_->Append(*(stats_mdg1_[0]));             // Skewness  
  out_stats_mdg2_->Append(*(stats_mdg2_[0]));             // Kurtosis
  out_stats_fst1all_->Append(*(stats_fst1all_[0]));       // Fst1
  out_stats_fsth_->Append(*(stats_fsth_[0]));             // FstH
  out_stats_fstHKY_->Append(*(stats_fstHKY_[0]));         // FstHKY
  out_stats_piwHKY_->Append(*(stats_piwHKY_[0]));         // PiWHKY
  out_stats_piaHKY_->Append(*(stats_piaHKY_[0]));         // PiAHKY    
}
*/


void CCalcMstatspop::Calculate(bool dry_run) {

  if (dry_run == true) {
    return;
  }

  /// CREATE CALC AND DATAS FOR THE CALCULATION

  CCalcExec *calc_execute = NULL;
  DM_NEW_CALC(calc_execute)

  CDataStdString *the_command = NULL;
  DM_NEW_DATA(the_command)

  the_command->set_value(STR(MSTATSPOP_BINARY));

  if (!formatfile_->auto_created()) {
    the_command->add(" -f ");
    the_command->add(formatfile_->value());
  }
  if (!file_in_->auto_created()) {
    the_command->add(" -i ");
    the_command->add(file_in_->value());
  }
  if (!output_->auto_created()) {
    the_command->add(" -o ");
    the_command->add(CStringTools::ToString(output_->value()));
  }
  if (!populations_initial_->auto_created()) {/*TOcheck*/
    the_command->add(" -N ");
    the_command->add(populations_initial_->value());
  }
  if (!scaffold_names_->auto_created())     {/*TOcheck*/
    the_command->add(" -n ");
    the_command->add(file_chr_name_all_->value());
  }

  the_command->add(" -T ");
  the_command->add(calc_output_->value());

  if (!b_outgroup_presence_->auto_created()) {
    the_command->add(" -G ");
    the_command->add(b_outgroup_presence_->value() ? "1" : "0");
  }
  if (!b_include_unknown_->auto_created()) {
    the_command->add(" -u ");
    the_command->add(b_include_unknown_->value() ? "1" : "0");
  }
  if (!file_H1f_->auto_created()) {/*TOcheck*/
    the_command->add(" -A ");
    the_command->add(file_H1f_->value());
  }
  if (!file_H0f_->auto_created()) {/*TOcheck*/
    the_command->add(" -S ");
    the_command->add(file_H0f_->value());
  }
  if (!sort_nsam_->auto_created()) {
    the_command->add(" -O ");
    the_command->add(sort_nsam_->GetDataString());
  }
  if (!niter_->auto_created()) {
    the_command->add(" -t ");
    the_command->add(CStringTools::ToString(niter_->value()));
  }
  if (!seed_->auto_created()) {
    the_command->add(" -s ");
    the_command->add(CStringTools::ToString(seed_->value()));
  }
  if (!window_->auto_created()) {
    the_command->add(" -w ");
      the_command->add(CStringTools::ToString(window_->value()));
  }
  if (!slide_->auto_created()) {
    the_command->add(" -z ");
    the_command->add(CStringTools::ToString(slide_->value()));
  }
  if (!physical_length_->auto_created()) {
    the_command->add(" -Y ");
    the_command->add(CStringTools::ToString(physical_length_->value()));
  }
  if (!file_wcoord_->auto_created()) {
    the_command->add(" -W ");
    the_command->add(file_wcoord_->value());
  }
  if (!file_wps_->auto_created()) {
    the_command->add(" -E ");
    the_command->add(file_wps_->value());
  }
  if (!length_->auto_created()) {
    the_command->add(" -l ");
    the_command->add(CStringTools::ToString(length_->value()));
  }
  if (!niterdata_->auto_created()) {
    the_command->add(" -r ");
    the_command->add(CStringTools::ToString(niterdata_->value()));
  }
  if (!file_mas_->auto_created()) {
    the_command->add(" -m ");
    the_command->add(file_mas_->value());
  }
  if (!ms_svratio_->auto_created()) {
    the_command->add(" -v ");
    the_command->add(CStringTools::ToString(ms_svratio_->value()));
  }
  if (!b_force_outgroup_->auto_created()) {
    the_command->add(" -F ");
    the_command->add(b_force_outgroup_->value() ? "1" : "0");
  }
  if (!freq_revert_->auto_created()) {
    the_command->add(" -q ");
    the_command->add(CStringTools::ToString(freq_revert_->value()));
  }
  if (!ploidy_->auto_created()) {
    the_command->add(" -p ");
    the_command->add(CStringTools::ToString(ploidy_->value()));
  }
  if (!file_GFF_->auto_created()) {
    the_command->add(" -g ");
    the_command->add(file_GFF_->value());

    if (subset_positions_->Size() > 0) {
      the_command->add(" ");
      the_command->add(subset_positions_->GetData());
    }

    if (code_name_->Size() > 0) {
      the_command->add(" ");
      the_command->add(code_name_->GetData());
    }

    if (genetic_code_->Size() > 0) {
      the_command->add(" ");
      the_command->add(genetic_code_->GetData());
    }
  }
  if (criteria_transcript_->Size() > 0) {
    the_command->add(" -c ");
    the_command->add(criteria_transcript_->GetData());
  }
  if (!b_mask_print_->auto_created()) {
    the_command->add(" -K ");
    the_command->add(b_mask_print_->value() ? "1" : "0");
  }
  if (!kind_length_->auto_created()) {/*TOcheck*/
    the_command->add(" -k ");
    the_command->add(kind_length_->GetDataString());
  }
  if (!freq_missing_ms_->auto_created()) {/*TOcheck*/
    the_command->add(" -x ");
    the_command->add(CStringTools::ToString(freq_missing_ms_->value());
  }
  if (!n_ccov_->auto_created()) {/*TOcheck*/
    the_command->add(" -y ");
    the_command->add(CStringTools::ToString(n_ccov_->value());
  }
  if (!location_missing_ms_->auto_created()) {/*TOcheck*/
    the_command->add(" -M ");
    the_command->add(CStringTools::ToString(location_missing_ms_->value());
  }
  if (!r2i_ploidies_->auto_created()) {/*TOcheck*/
    the_command->add(" -P ");
    the_command->add(r2i_ploidies_->GetDataString());
  }
  if (!first_slide_->auto_created()) {/*TOcheck*/
    the_command->add(" -Z ");
    the_command->add(CStringTools::ToString(first_slide_->value());
  }

  /*
    if (file_effsz_->value() != "") {
       the_command->add(" ");
       the_command->add(file_effsz_->value());
    }
   */

  CDataStdString *the_working_directory = NULL;
  DM_NEW_DATA(the_working_directory)
  the_working_directory->set_value(STR(BINARY_PATH_INSIDE_DOCKER));

  CDataStdString *the_type = NULL;
  DM_NEW_DATA(the_type)
  the_type->set_value(STR(EXEC_TYPE_SYS));

  CDataInt *the_result = (CDataInt *) manager()->data_manager()->GetDataByName(ROOT_PARENT, STR(RESULT)); // This is a global variable. So, its parent is ROOT_PARENT.

    NORMAL_MSG << "the_command: " << the_command->value()
    END_MSG;

  /// ==========================================================================
  /// EXECUTE EXTERNAL APPLICATION OR SYSTEM COMMAND
  /// ==========================================================================
  calc_execute->SetInput(the_command);
  calc_execute->SetInput(the_working_directory);
  calc_execute->SetInput(the_type);
  calc_execute->SetOutput(the_result);
  calc_execute->Prepare();
  calc_execute->Calculate(dry_run);
  calc_execute->Finalize();
  /// ==========================================================================

  /// REMOVE CALC AND "DATAS" CREATED ONLY FOR THIS CALCULATION

  DM_DEL_CALC(calc_execute)
  DM_DEL_DATA(the_command)
  DM_DEL_DATA(the_working_directory)
  DM_DEL_DATA(the_type)
}

void CCalcMstatspop::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA   
}

