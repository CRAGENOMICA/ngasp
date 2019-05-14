/*
 * ngaSP: the computational solution for next generation analysis of 
 * Sequence Polymorphisms.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
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
 *  \brief     CCMDmstatspop.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      March 30, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#include "CCMDmstatspop.h"

#include <string>
#include <cstdio>

#include "../../language/CStringTable.h"

#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataInt64.h"

#include "../../commands/CAllCommands.h"

CCMDmstatspop::CCMDmstatspop()
  : ICommand(CMD_MSTATSPOP,                                                     // Command Name
             CMD_MSTATSPOP_ABB,                                                 // Command Abbreviation Name
             MSTATSPOP_BRIEF_DESC,                                              // Brief Description
             MSTATSPOP_DESC,                                                    // Long Description
             MSTATSPOP_AUTHOR,                                                  // Authors
             MSTATSPOP_SEE_ALSO) {                                              // See also 
}
  
CCMDmstatspop::~CCMDmstatspop() {
}

/// ============================================================================
/// COMMAND OPTIONS
/// ============================================================================
void CCMDmstatspop::DefineCommandOptions() {
  /// Command options:
  
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(STANDARD_GROUP_FLAGS,                                       // Group
                    DATA_MENU,                                                  // Data Type
                    MSTATSPOP_FORMAT_SHORT,                                     // Short Name
                    MSTATSPOP_FORMAT_LONG,                                      // Long Name
                    MSTATSPOP_FORMAT_DESC,                                      // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_VALUE_INFO(FORMAT_FILE_FASTA,                                           // Value
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(FORMAT_FILE_TFASTA,                                          // Value
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(FORMAT_FILE_MS,                                              // Value
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)

  
    SET_OPTION_INFO(STANDARD_GROUP_FLAGS,                                       // Group
                    DATA_FILE,                                                  // Data Type
                    MSTATSPOP_INPUT_SHORT,                                      // Short Name
                    MSTATSPOP_INPUT_LONG,                                       // Long Name
                    MSTATSPOP_INPUT_DESC,                                       // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required

    SET_OPTION_INFO(STANDARD_GROUP_FLAGS,                                       // Group
                    DATA_MENU,                                                  // Data Type
                    MSTATSPOP_OUTPUT_SHORT,                                     // Short Name
                    MSTATSPOP_OUTPUT_LONG,                                      // Long Name
                    MSTATSPOP_OUTPUT_DESC,                                      // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required

    SET_VALUE_INFO(VALUE_0,                                                     // Value
                   MSTATSPOP_OUTPUT_0_DESC,                                     // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(VALUE_1,                                                     // Value
                   MSTATSPOP_OUTPUT_1_DESC,                                     // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(VALUE_3,                                                     // Value
                   MSTATSPOP_OUTPUT_3_DESC,                                     // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(VALUE_4,                                                     // Value
                   MSTATSPOP_OUTPUT_4_DESC,                                     // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(VALUE_5,                                                     // Value
                   MSTATSPOP_OUTPUT_5_DESC,                                     // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(VALUE_6,                                                     // Value
                   MSTATSPOP_OUTPUT_6_DESC,                                     // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(VALUE_10,                                                    // Value
                   MSTATSPOP_OUTPUT_10_DESC,                                    // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
 
    
    SET_OPTION_INFO(STANDARD_GROUP_FLAGS,                                       // Group
                    DATA_VALUES,                                                // Data Type
                    MSTATSPOP_POP_SHORT,                                        // Short Name
                    MSTATSPOP_POP_LONG,                                         // Long Name
                    MSTATSPOP_POP_DESC,                                         // Description
                    MSTATSPOP_POP_EXAMPLE,                                      // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
        
                    /// Command options: General

    SET_OPTION_INFO(MSTATSPOP_GROUP_GENERAL_OPTIONAL,                           // Group
                    DATA_MENU,                                                  // Data Type
                    MSTATSPOP_OUTGROUP_SHORT,                                   // Short Name
                    MSTATSPOP_OUTGROUP_LONG,                                    // Long Name
                    MSTATSPOP_OUTGROUP_DESC,                                    // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_VALUE_INFO(VALUE_0,                                                     // Value
                   VALUE_NO,                                                    // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   true)                                                        // Default Value (true / false)
    SET_VALUE_INFO(VALUE_1,                                                     // Value
                   VALUE_YES,                                                   // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    
    SET_OPTION_INFO(MSTATSPOP_GROUP_GENERAL_OPTIONAL,                           // Group
                    DATA_MENU,                                                  // Data Type
                    MSTATSPOP_INCL_UNKNO_SHORT,                                 // Short Name
                    MSTATSPOP_INCL_UNKNO_LONG,                                  // Long Name
                    MSTATSPOP_INCL_UNKNO_DESC,                                  // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_VALUE_INFO(VALUE_0,                                                     // Value
                   VALUE_NO,                                                    // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   true)                                                        // Default Value (true / false)
    SET_VALUE_INFO(VALUE_1,                                                     // Value
                   VALUE_YES,                                                   // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    
    SET_OPTION_INFO(MSTATSPOP_GROUP_GENERAL_OPTIONAL,                           // Group
                    DATA_FILE,                                                  // Data Type
                    MSTATSPOP_PATHNAME_OUTPUT_FILE_SHORT,                       // Short Name
                    MSTATSPOP_PATHNAME_OUTPUT_FILE_LONG,                        // Long Name
                    MSTATSPOP_PATHNAME_OUTPUT_FILE_DESC,                        // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    MSTATSPOP_PATHNAME_OUTPUT_FILE_DEF_VAL,                     // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_GENERAL_OPTIONAL,                           // Group
                    DATA_FILE,                                                  // Data Type
                    MSTATSPOP_ALT_SFILE_SHORT,                                  // Short Name
                    MSTATSPOP_ALT_SFILE_LONG,                                   // Long Name
                    MSTATSPOP_ALT_SFILE_DESC,                                   // Description
                    MSTATSPOP_ALT_SFILE_EXAMPLE,                                // Example
                    MSTATSPOP_ALT_SFILE_ONLY,                                   // Use only if
                    UNDEFINED_STRING,                                           // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_GENERAL_OPTIONAL,                           // Group
                    DATA_FILE,                                                  // Data Type
                    MSTATSPOP_NULL_SFILE_SHORT,                                 // Short Name
                    MSTATSPOP_NULL_SFILE_LONG,                                  // Long Name
                    MSTATSPOP_NULL_SFILE_DESC,                                  // Description
                    MSTATSPOP_NULL_SFILE_EXAMPLE,                               // Example
                    MSTATSPOP_NULL_SFILE_ONLY,                                  // Use only if
                    MSTATSPOP_NULL_SFILE_DEF_VAL,                               // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_GENERAL_OPTIONAL,                           // Group
                    DATA_VALUES,                                                // Data Type
                    MSTATSPOP_R2P_SHORT,                                        // Short Name
                    MSTATSPOP_R2P_LONG,                                         // Long Name
                    MSTATSPOP_R2P_DESC,                                         // Description
                    MSTATSPOP_R2P_EXAMPLE,                                      // Example
                    MSTATSPOP_R2P_ONLY,                                         // Use only if
                    UNDEFINED_STRING,                                           // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_FA_TFA,                                     // Group
                    DATA_VALUES,                                                // Data Type
                    MSTATSPOP_ORDER_SHORT,                                      // Short Name
                    MSTATSPOP_ORDER_LONG,                                       // Long Name
                    MSTATSPOP_ORDER_DESC,                                       // Description
                    MSTATSPOP_ORDER_EXAMPLE,                                    // Example
                    UNDEFINED_STRING,                                           // Use only if
                    MSTATSPOP_ORDER_DEF_VAL,                                    // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_FA_TFA,                                     // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    MSTATSPOP_PERM_ITE_SHORT,                                   // Short Name
                    MSTATSPOP_PERM_ITE_LONG,                                    // Long Name
                    MSTATSPOP_PERM_ITE_DESC,                                    // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    VALUE_0,                                                    // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_FA_TFA,                                     // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    MSTATSPOP_SEED_SHORT,                                       // Short Name
                    MSTATSPOP_SEED_LONG,                                        // Long Name
                    MSTATSPOP_SEED_DESC,                                        // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    MSTATSPOP_SEED_DEF_VAL,                                     // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

                    /// Command options: For TFASTA Input

    SET_OPTION_INFO(MSTATSPOP_GROUP_TFA,                                        // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    MSTATSPOP_WINDOW_SIZE_SHORT,                                // Short Name
                    MSTATSPOP_WINDOW_SIZE_LONG,                                 // Long Name
                    MSTATSPOP_WINDOW_SIZE_DESC,                                 // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory_in_its_group)                             // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_TFA,                                        // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    MSTATSPOP_SLIDE_SIZE_SHORT,                                 // Short Name
                    MSTATSPOP_SLIDE_SIZE_LONG,                                  // Long Name
                    MSTATSPOP_SLIDE_SIZE_DESC,                                  // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    MSTATSPOP_SLIDE_SIZE_DEF_VAL,                               // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_TFA,                                        // Group
                    DATA_MENU,                                                  // Data Type
                    MSTATSPOP_WINDOW_LENGTHS_SHORT,                             // Short Name
                    MSTATSPOP_WINDOW_LENGTHS_LONG,                              // Long Name
                    MSTATSPOP_WINDOW_LENGTHS_DESC,                              // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_VALUE_INFO(VALUE_0,                                                     // Value
                   MSTATSPOP_WINDOW_LENGTHS_VAL_0,                              // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(VALUE_1,                                                     // Value
                   MSTATSPOP_WINDOW_LENGTHS_VAL_1,                              // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   true)                                                        // Default Value (true / false)
  
    SET_OPTION_INFO(MSTATSPOP_GROUP_TFA,                                        // Group
                    DATA_FILE,                                                  // Data Type
                    MSTATSPOP_COORDS_FILE_SHORT,                                // Short Name
                    MSTATSPOP_COORDS_FILE_LONG,                                 // Long Name
                    MSTATSPOP_COORDS_FILE_DESC,                                 // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    MSTATSPOP_COORDS_FILE_DEF_VAL,                              // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_TFA,                                        // Group
                    DATA_FILE,                                                  // Data Type
                    MSTATSPOP_HEIGHTS_FILE_SHORT,                               // Short Name
                    MSTATSPOP_HEIGHTS_FILE_LONG,                                // Long Name
                    MSTATSPOP_HEIGHTS_FILE_DESC,                                // Description
                    MSTATSPOP_HEIGHTS_FILE_EXAMPLE,                             // Example
                    UNDEFINED_STRING,                                           // Use only if
                    MSTATSPOP_HEIGHTS_FILE_DEF_VAL,                             // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

                    /// Command options: For MS Input

    SET_OPTION_INFO(MSTATSPOP_GROUP_MS,                                         // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    MSTATSPOP_LENGTH_SHORT,                                     // Short Name
                    MSTATSPOP_LENGTH_LONG,                                      // Long Name
                    MSTATSPOP_LENGTH_DESC,                                      // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory_in_its_group)                             // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_MS,                                         // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    MSTATSPOP_MS_ITERATIONS_SHORT,                              // Short Name
                    MSTATSPOP_MS_ITERATIONS_LONG,                               // Long Name
                    MSTATSPOP_MS_ITERATIONS_DESC,                               // Description
                    UNDEFINED_STRING,                                           // Example
                    FORMAT_FILE_MS,                                             // Use only if
                    VALUE_1,                                                    // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_MS,                                         // Group
                    DATA_FILE,                                                  // Data Type
                    MSTATSPOP_MASK_SHORT,                                       // Short Name
                    MSTATSPOP_MASK_LONG,                                        // Long Name
                    MSTATSPOP_MASK_DESC,                                        // Description
                    MSTATSPOP_MASK_EXAMPLE,                                     // Example
                    UNDEFINED_STRING,                                           // Use only if
                    MSTATSPOP_MASK_DEF_VAL,                                     // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(MSTATSPOP_GROUP_MS,                                         // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    MSTATSPOP_RATIOTRANS_SHORT,                                 // Short Name
                    MSTATSPOP_RATIOTRANS_LONG,                                  // Long Name
                    MSTATSPOP_RATIOTRANS_DESC,                                  // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    MSTATSPOP_RATIOTRANS_DEF_VAL,                               // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_MS,                                         // Group
                    DATA_MENU,                                                  // Data Type
                    MSTATSPOP_INCL_OUTGR_SHORT,                                 // Short Name
                    MSTATSPOP_INCL_OUTGR_LONG,                                  // Long Name
                    MSTATSPOP_INCL_OUTGR_DESC,                                  // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_VALUE_INFO(VALUE_0,                                                     // Value
                   MSTATSPOP_INCL_OUTGR_VALUE_0,                                // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(VALUE_1,                                                     // Value
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   true)                                                        // Default Value (true / false)
      
    SET_OPTION_INFO(MSTATSPOP_GROUP_MS,                                         // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    MSTATSPOP_FREQREVMUT_SHORT,                                 // Short Name
                    MSTATSPOP_FREQREVMUT_LONG,                                  // Long Name
                    MSTATSPOP_FREQREVMUT_DESC,                                  // Description
                    UNDEFINED_STRING,                                           // Example
                    MSTATSPOP_FREQREVMUT_ONLY,                                  // Use only if
                    MSTATSPOP_FREQREVMUT_DEF_VAL,                               // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

                    /// Command options: For FASTA Input

    SET_OPTION_INFO(MSTATSPOP_GROUP_FA,                                         // Group
                    DATA_MENU,                                                  // Data Type
                    MSTATSPOP_PLOIDY_SHORT,                                     // Short Name
                    MSTATSPOP_PLOIDY_LONG,                                      // Long Name
                    MSTATSPOP_PLOIDY_DESC,                                      // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
    
    SET_VALUE_INFO(VALUE_1,                                                     // Value
                   MSTATSPOP_PLOIDY_OPTION_HAPLOID,                             // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   true)                                                        // Default Value (true / false)
    SET_VALUE_INFO(VALUE_2,                                                     // Value
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   MSTATSPOP_PLOIDY_OPTION_DIPLOID,                             // Use only if
                   false)                                                       // Default Value (true / false)
    
    SET_OPTION_INFO(MSTATSPOP_GROUP_FA,                                         // Group
                    DATA_VALUES,                                                // Data Type
                    MSTATSPOP_GFF_FILE_SHORT,                                   // Short Name
                    MSTATSPOP_GFF_FILE_LONG,                                    // Long Name
                    MSTATSPOP_GFF_FILE_DESC,                                    // Description
                    MSTATSPOP_GFF_FILE_EXAMPLE,                                 // Example
                    UNDEFINED_STRING,                                           // Use only if
                    MSTATSPOP_GFF_FILE_DEF_VAL,                                 // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_FA,                                         // Group
                    DATA_MENU,                                                  // Data Type
                    MSTATSPOP_CRITERIA_SHORT,                                   // Short Name
                    MSTATSPOP_CRITERIA_LONG,                                    // Long Name
                    MSTATSPOP_CRITERIA_DESC,                                    // Description
                    UNDEFINED_STRING,                                           // Example
                    MSTATSPOP_CRITERIA_ONLY,                                    // Use only if
                    UNDEFINED_STRING,                                           // Default Value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory_in_its_group)                             // Required

    SET_VALUE_INFO(CRITERIA_TRANSCRIPT_MAX,                                     // Value
                   CRITERIA_TRANSCRIPT_MAX,                                     // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   true)                                                        // Default Value (true / false)
    SET_VALUE_INFO(CRITERIA_TRANSCRIPT_MIN,                                     // Value
                   CRITERIA_TRANSCRIPT_MIN,                                     // Description
                   UNDEFINED_STRING,                                            // Example
                   MSTATSPOP_PLOIDY_OPTION_DIPLOID,                             // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(CRITERIA_TRANSCRIPT_FIRST,                                   // Value
                   CRITERIA_TRANSCRIPT_FIRST,                                   // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
    SET_VALUE_INFO(CRITERIA_TRANSCRIPT_LONG,                                    // Value
                   CRITERIA_TRANSCRIPT_LONG,                                    // Description
                   UNDEFINED_STRING,                                            // Example
                   MSTATSPOP_PLOIDY_OPTION_DIPLOID,                             // Use only if
                   false)                                                       // Default Value (true / false)    
      
    SET_OPTION_INFO(MSTATSPOP_GROUP_FA,                                         // Group
                    DATA_MENU,                                                  // Data Type
                    MSTATSPOP_MASK_PRINT_SHORT,                                 // Short Name
                    MSTATSPOP_MASK_PRINT_LONG,                                  // Long Name
                    MSTATSPOP_MASK_PRINT_DESC,                                  // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_VALUE_INFO(VALUE_0,                                                     // Value
                   VALUE_NO,                                                    // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   true)                                                        // Default Value (true / false)
    SET_VALUE_INFO(VALUE_1,                                                     // Value
                   VALUE_YES,                                                   // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   false)                                                       // Default Value (true / false)
  
                    /// Command options: Help

    SET_OPTION_INFO(STANDARD_GROUP_HELP,                                        // Group
                  UNDEFINED_STRING,                                             // Data Type
                  MSTATSPOP_HELP_SHORT,                                         // Short Name
                  MSTATSPOP_HELP_LONG,                                          // Long Name
                  MSTATSPOP_HELP_DESC,                                          // Description
                  UNDEFINED_STRING,                                             // Example
                  UNDEFINED_STRING,                                             // Use only if
                  UNDEFINED_STRING,                                             // Default value
                  UNDEFINED_VALUE,                                              // Min. Value
                  UNDEFINED_VALUE,                                              // Max. Value
                  ARGTYPE_arg_required,                                         // Argument Required
                  OPTTYPE_mandatory_in_its_group)                               // Required

                    /// Command options: New & Not done

    SET_OPTION_INFO(STANDARD_GROUP_FLAGS,                                       // Group
                    DATA_FILE,                                                  // Data Type
                    MSTATSPOP_SCAFFOLD_NAME_SHORT,                                      // Short Name
                    MSTATSPOP_SCAFFOLD_NAME_LONG,                                       // Long Name
                    MSTATSPOP_SCAFFOLD_NAME_DESC,                                       // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required

    SET_OPTION_INFO(MSTATSPOP_GROUP_FA,                                       // Group
                    DATA_MENU,                                                  // Data Type
                    MSTATSPOP_KIND_LENGTH_SHORT,                                      // Short Name
                    MSTATSPOP_KIND_LENGTH_LONG,                                       // Long Name
                    MSTATSPOP_KIND_LENGTH_DESC,                                       // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    VALUE_0,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                          // Required
    
    SET_OPTION_INFO(MSTATSPOP_GROUP_MS,                                       // Group
                    DATA_ONE_VALUE,                                                  // Data Type
                    MSTATSPOP_LOCATION_MISSING_SHORT,                                      // Short Name
                    MSTATSPOP_LOCATION_MISSING_LONG,                                       // Long Name
                    MSTATSPOP_LOCATION_MISSING_DESC,                                       // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    VALUE_3,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                          // Required
    
    SET_OPTION_INFO(MSTATSPOP_GROUP_TFA,                                       // Group
                    DATA_ONE_VALUE,                                                  // Data Type
                    MSTATSPOP_FIRST_SLIDE_SHORT,                                      // Short Name
                    MSTATSPOP_FIRST_SLIDE_LONG,                                       // Long Name
                    MSTATSPOP_FIRST_SLIDE_DESC,                                       // Description
                    UNDEFINED_STRING,                                           // Example
                    UNDEFINED_STRING,                                           // Use only if
                    VALUE_0,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                          // Required

/*
    SET_OPTION_INFO (READ,
                      ,
                      ,
                      MSTATSPOP_WEIGHTS_VARIANTS_FILE_SHORT,
                      MSTATSPOP_WEIGHTS_VARIANTS_FILE_LONG,
                      MSTATSPOP_WEIGHTS_VARIANTS_FILE_DESC,
                      UNDEFINED_STRING,
                      UNDEFINED_STRING,
                      UNDEFINED_STRING,
                      UNDEFINED_VALUE,
                      UNDEFINED_VALUE,
                      ARGTYPE_arg_required, OPTTYPE_optional)

    SET_OPTION_INFO (READ,
                      ,
                      ,
                      MSTATSPOP_COUNT_TRANSITIONS_SHORT,
                      MSTATSPOP_COUNT_TRANSITIONS_LONG,
                      MSTATSPOP_COUNT_TRANSITIONS_DESC,
                      UNDEFINED_STRING,
                      UNDEFINED_STRING,
                      UNDEFINED_STRING,
                      UNDEFINED_VALUE,
                      UNDEFINED_VALUE,
                      ARGTYPE_arg_required, OPTTYPE_optional)

    SET_OPTION_INFO (READ,
                      ,
                      ,
                      MSTATSPOP_COUNT_TRANSVERSION_SHORT,
                      MSTATSPOP_COUNT_TRANSVERSION_LONG,
                      MSTATSPOP_COUNT_TRANSVERSION_DESC,
                      UNDEFINED_STRING,
                      UNDEFINED_STRING,
                      UNDEFINED_STRING,
                      UNDEFINED_VALUE,
                      UNDEFINED_VALUE,
                      ARGTYPE_arg_required, OPTTYPE_optional)

    SET_OPTION_INFO (READ,
                      ,
                      ,
                      MSTATSPOP_COUNT_GC_MUTATIONS_SHORT,
                      MSTATSPOP_COUNT_GC_MUTATIONS_LONG,
                      MSTATSPOP_COUNT_GC_MUTATIONS_DESC,
                      UNDEFINED_STRING,
                      UNDEFINED_STRING,
                      UNDEFINED_STRING,
                      UNDEFINED_VALUE,
                      UNDEFINED_VALUE,
                      ARGTYPE_arg_required, OPTTYPE_optional)

    SET_OPTION_INFO (READ,
                      ,
                      ,
                      MSTATSPOP_COUNT_AT_MUTATIONS_SHORT,
                      MSTATSPOP_COUNT_AT_MUTATIONS_LONG,
                      MSTATSPOP_COUNT_AT_MUTATIONS_DESC,
                      UNDEFINED_STRING,
                      UNDEFINED_STRING,
                      UNDEFINED_STRING,
                      UNDEFINED_VALUE,
                      UNDEFINED_VALUE,
                      ARGTYPE_arg_required, OPTTYPE_optional)
*/    
  END_COMMAND_INTERFACE_DEFINITION
}


bool CCMDmstatspop::Prepare() {
  bool parseResult = true;

  run_only_help_ = false;
  
  
/// ============================================================================
/// CALCS
/// ============================================================================
  DM_NEW_CALC(calc_mstatspop_)

/// ============================================================================
/// FIXED DATAS
/// ============================================================================
  DM_GET_DATA2(output_, STR(OUTPUT))
  DM_GET_DATA3(CDataInt, table_col_width, STR(TABLE_COL_WIDTH))
  DM_GET_DATA2(seed_, STR(SEED))
  DM_GET_DATA3(CDataInt64, idum_, STR(IDUM))

/// ============================================================================
/// DATAS
/// ============================================================================
  DM_NEW_DATA(populations_initial_)
  DM_NEW_DATA(ploidy_);
  DM_NEW_DATA(b_include_unknown_);
  DM_NEW_DATA(out_file_name_);
  DM_NEW_DATA(b_force_outgroup_);
  DM_NEW_DATA(b_outgroup_presence_);
  DM_NEW_DATA(r2i_ploidies_)
  DM_NEW_DATA(file_mas_)
  DM_NEW_DATA(niter_)
  DM_NEW_DATA(niterdata_)
  DM_NEW_DATA(ms_svratio_)
  DM_NEW_DATA(length_)
  DM_NEW_DATA(freq_revert_)
  DM_NEW_DATA(file_GFF_)
  DM_NEW_DATA(subset_positions_)
  DM_NEW_DATA(code_name_)
  DM_NEW_DATA(genetic_code_)
  DM_NEW_DATA(file_H0f_)
  DM_NEW_DATA(file_H1f_)
  DM_NEW_DATA(criteria_transcript_)
  DM_NEW_DATA(file_in_)
  DM_NEW_DATA(sort_nsam_)
  DM_NEW_DATA(formatfile_)
  DM_NEW_DATA(file_wps_)
  DM_NEW_DATA(file_wcoord_)
  DM_NEW_DATA(window_)
  DM_NEW_DATA(slide_)
  DM_NEW_DATA(physical_length_)
  //DM_NEW_DATA(file_effsz_)
  DM_NEW_DATA(b_mask_print_)
  DM_NEW_DATA(scaffold_name_)
  DM_NEW_DATA(kind_length_)
  DM_NEW_DATA(location_missing_ms_)
  DM_NEW_DATA(first_slide_)

  DM_NEW_DATA(calc_output_)
  /*DM_NEW_DATA(out_stats_So_)
  DM_NEW_DATA(out_stats_thetaSo_)
  DM_NEW_DATA(out_stats_thetaTo_)
  DM_NEW_DATA(out_stats_thetaFL_)
  DM_NEW_DATA(out_stats_thetaFW_)
  DM_NEW_DATA(out_stats_thetaL_)
  DM_NEW_DATA(out_stats_thetaSA_)
  DM_NEW_DATA(out_stats_thetaTA_)
  DM_NEW_DATA(out_stats_K_)
  DM_NEW_DATA(out_stats_thetaTHKY_)
  DM_NEW_DATA(out_stats_KHKY_)
  DM_NEW_DATA(out_stats_thetaS_)
  DM_NEW_DATA(out_stats_thetaT_)
  DM_NEW_DATA(out_stats_hapw_)
  DM_NEW_DATA(out_stats_nhpop_)
  DM_NEW_DATA(out_stats_Dtaj_)
  DM_NEW_DATA(out_stats_Dfl_)
  DM_NEW_DATA(out_stats_Ffl_)
  DM_NEW_DATA(out_stats_Hnfw_)
  DM_NEW_DATA(out_stats_Ez_)
  DM_NEW_DATA(out_stats_Yach_)
  DM_NEW_DATA(out_stats_FH_)
  DM_NEW_DATA(out_stats_Fs_)
  DM_NEW_DATA(out_stats_mdsd_)
  DM_NEW_DATA(out_stats_mdg1_)
  DM_NEW_DATA(out_stats_mdg2_)
  DM_NEW_DATA(out_stats_fst1all_)
  DM_NEW_DATA(out_stats_fsth_)
  DM_NEW_DATA(out_stats_fstHKY_)
  DM_NEW_DATA(out_stats_piwHKY_)
  //DM_NEW_DATA(out_stats_piaHKY_)
    */
  // Autocreated variables are those variables that the calculation will set to default values.
  // They are all initialy set to true.
  // Auto created will be changed to false if the user sets their value.
    
  populations_initial_->set_auto_created(true);
  ploidy_->set_auto_created(true);
  b_include_unknown_->set_auto_created(true);
  out_file_name_->set_auto_created(true);
  b_force_outgroup_->set_auto_created(true);
  b_outgroup_presence_->set_auto_created(true);
  formatfile_->set_auto_created(true);
  r2i_ploidies_->set_auto_created(true);
  file_mas_->set_auto_created(true);
  niter_->set_auto_created(true);
  niterdata_->set_auto_created(true);
  ms_svratio_->set_auto_created(true);
  length_->set_auto_created(true);
  freq_revert_->set_auto_created(true);
  file_GFF_->set_auto_created(true);
  subset_positions_->set_auto_created(true);
  code_name_->set_auto_created(true);
  genetic_code_->set_auto_created(true);
  file_H0f_->set_auto_created(true);
  file_H1f_->set_auto_created(true);
  criteria_transcript_->set_auto_created(true);
  file_in_->set_auto_created(true);
  sort_nsam_->set_auto_created(true);
  output_->set_auto_created(true);
  seed_->set_auto_created(true);
  file_wps_->set_auto_created(true);
  file_wcoord_->set_auto_created(true);
  window_->set_auto_created(true);
  slide_->set_auto_created(true);
  physical_length_->set_auto_created(true);
  //file_effsz_->set_auto_created(true);
  b_mask_print_->set_auto_created(true);
  scaffold_name_->set_auto_created(true);
  kind_length_->set_auto_created(true);
  location_missing_ms_->set_auto_created(true);
  first_slide_->set_auto_created(true);
/// ============================================================================
/// SCRIPT - INIT
/// ============================================================================
  // manager()->logger()->set_mode(CLogger::LogMode::NORMAL);
  table_col_width->set_value(1);
  

  DM_GET_DATA3(CDataStdString, all_command_line_, STR(ALL_COMMAND_LINE))
  all_command_line_->set_value(this->instruction()->GetAllCommandLine());
  
/// ============================================================================
/// COMMAND PARAMS
/// ============================================================================
  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments, one_argument;

  if (instruction()->command_arguments()->size() == 1) {
    run_only_help_ = true;
  } else {
    while (getopt_long_own(&option, &arguments)) {
      switch (option) {

      /// Command options:

        
      case KeyString::MSTATSPOP_FORMAT_SHORT:                 //-f
        // For wrapper
        formatfile_->set_value(arguments);

        /*if (arguments == STR(FORMAT_FILE_FASTA)) {
          formatfile_->set_value(FASTA_FILE);
          //niterdata_->set_value(1);
        } else {
          if (arguments == STR(FORMAT_FILE_NBRF)) {
              formatfile_->set_value(FASTA_FILE);
              // niterdata_->set_value(1);
          } else {
            if (arguments == STR(FORMAT_FILE_MS)) {
                formatfile_->set_value(MS_FILE);
            } else {
              if (arguments == STR(FORMAT_FILE_MS_EXTENDED)) {
                  formatfile_->set_value(MS_X_FILE);
              } else {
                if (arguments == STR(FORMAT_FILE_TFASTA)) {
                  formatfile_->set_value(TFASTA_FILE);
                } else {
                  parseResult = false;
                }
              }
            }
          }
        }*/ //con este if el wrapper daba error de tipos de datos
        formatfile_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_INPUT_SHORT:                //-i
        file_in_->set_value(arguments);
        file_in_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_OUTPUT_SHORT:               //-o
        output_->set_value_string(arguments);
        output_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_POP_SHORT:                  //-N
        GetArgument(&arguments);  // Discard number of elements.

        if (arguments != "") {
          // in command line, pops are separated by space but it is needed to be
          // by coma:
          CStringTools::Replace(arguments,
                                 STR(SPACE),
                                 STR(COMA));
          populations_initial_->set_value(arguments);
          populations_initial_->set_auto_created(false);
        }
        break;

      /// Command options: General

      case KeyString::MSTATSPOP_OUTGROUP_SHORT:                   //-G
        b_outgroup_presence_->set_value_string(arguments);
        b_outgroup_presence_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_INCL_UNKNO_SHORT:                 //-u
        b_include_unknown_->set_value_string(arguments);
        b_include_unknown_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_PATHNAME_OUTPUT_FILE_SHORT:       //-T        
        out_file_name_->set_value(arguments);
        out_file_name_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_ALT_SFILE_SHORT:                  //-A
        file_H1f_->set_value(arguments);
        file_H1f_->set_auto_created(false);
        // b_H1frq_->set_value(1);
        break;

      case KeyString::MSTATSPOP_NULL_SFILE_SHORT:                 //-S
        file_H0f_->set_value(arguments);
        file_H0f_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_R2P_SHORT:                        //-P
        if ((one_argument = GetArgument(&arguments)) != "") {
          //numPloidies_->set_value(static_cast<int>(atol(one_argument.c_str())));
          r2i_ploidies_->set_data_string(arguments);
          r2i_ploidies_->set_auto_created(false);
        }
        break;

      case KeyString::MSTATSPOP_ORDER_SHORT:                      //-O
        GetArgument(&arguments);  // Discard number of elements.

        if (arguments != "") {
          // in command line, items are separated by space but it is needed to
          // be by coma:
          CStringTools::Replace(arguments,
                                STR(SPACE),
                                STR(COMA));
          sort_nsam_->set_data_string(arguments);
          sort_nsam_->set_auto_created(false);
        }
        break;

      case KeyString::MSTATSPOP_PERM_ITE_SHORT:                   //-t
        niter_->set_value(static_cast<long int>(atol(arguments.c_str())));
        niter_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_SEED_SHORT:                       //-s
        seed_->set_value_string(arguments);
        seed_->set_auto_created(false);
        //idum_->set_value(-1*seed_->value());
        break;

      /// Command options: For TFASTA Input

      case KeyString::MSTATSPOP_WINDOW_SIZE_SHORT:                //-w
        window_->set_value(static_cast<long int>(atol(arguments.c_str())));
        window_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_SLIDE_SIZE_SHORT:                 //-z
        slide_->set_value(static_cast<long int>(atol(arguments.c_str())));
        slide_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_WINDOW_LENGTHS_SHORT:             //-Y
        physical_length_->set_value(static_cast<int>(atoi(arguments.c_str())));
        physical_length_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_COORDS_FILE_SHORT:                // -W
        file_wcoord_->set_value(arguments);   
        file_wcoord_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_HEIGHTS_FILE_SHORT:               //-E
        file_wps_->set_value(arguments);
        file_wps_->set_auto_created(false);
        break;

      /// Command options: For MS Input

      case KeyString::MSTATSPOP_LENGTH_SHORT:                     //-l
        length_->set_value_string(arguments);
        length_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_MS_ITERATIONS_SHORT:              //-r
        niterdata_->set_value(static_cast<long int>(atol(arguments.c_str())));
        niterdata_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_MASK_SHORT:                       //-m
        file_mas_->set_value(arguments);
        file_mas_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_RATIOTRANS_SHORT:                 //-v
        ms_svratio_->set_value_string(arguments);
        ms_svratio_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_INCL_OUTGR_SHORT:                 //-F
        b_force_outgroup_->set_value_string(arguments);
        b_force_outgroup_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_FREQREVMUT_SHORT:                 //-q
        freq_revert_->set_value_string(arguments);
        freq_revert_->set_auto_created(false);
        break;

      /// Command options: For FASTA Input      

      case KeyString::MSTATSPOP_PLOIDY_SHORT:                     //-p
        ploidy_->set_value_string(arguments);
        ploidy_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_GFF_FILE_SHORT:                   //-g
       

        if ((one_argument = GetArgument(&arguments)) != "") {
          file_GFF_->set_value(one_argument);
          file_GFF_->set_auto_created(false);
        }

        if ((one_argument = GetArgument(&arguments)) != "") {
          subset_positions_->set_text_string(one_argument);
          subset_positions_->set_auto_created(false);
        }

        if ((one_argument == STR(SUBSET_POS_SYNONYMOUS)) ||  
             (one_argument == STR(SUBSET_POS_NONSYNONYMOUS)) ||
             (one_argument == STR(SUBSET_POS_0_FOLD)) ||
             (one_argument == STR(SUBSET_POS_2_FOLD)) ||
             (one_argument == STR(SUBSET_POS_3_FOLD)) ||
             (one_argument == STR(SUBSET_POS_4_FOLD)) ||
             (one_argument == STR(SUBSET_POS_SILENT))) {
          if ((one_argument = GetArgument(&arguments)) != "") {
            code_name_->set_text_string(one_argument);
            code_name_->set_auto_created(false);
          }

          if (one_argument == STR(CODE_NAME_OTHER)) {
            genetic_code_->ReserveMemory(64, '\x0');
            genetic_code_->set_auto_created(false);
            int i = 0;
            while ((one_argument = GetArgument(&arguments)) != "") {
              (*genetic_code_)[i] = atoi(one_argument.c_str());
              i++;
            }
          }
        }
        break;

      case KeyString::MSTATSPOP_CRITERIA_SHORT:               //-c
        criteria_transcript_->set_text_string(arguments);
        criteria_transcript_->set_auto_created(false);

        if ((arguments != STR(CRITERIA_TRANSCRIPT_MAX)) &&
             (arguments != STR(CRITERIA_TRANSCRIPT_FIRST)) &&
             (arguments != STR(CRITERIA_TRANSCRIPT_LONG))) {
          parseResult = false;
        }
        break;

      case KeyString::MSTATSPOP_MASK_PRINT_SHORT:           //-K
        b_mask_print_->set_value_string(arguments);
        b_mask_print_->set_auto_created(false);
        break;
      
      case KeyString::MSTATSPOP_SCAFFOLD_NAME_SHORT:           //-n
        scaffold_name_->set_value(arguments);
        scaffold_name_->set_auto_created(false);
        break;

      case KeyString::MSTATSPOP_KIND_LENGTH_SHORT:           //-k ***NOT DONE***
        kind_length_->set_data_string(arguments);
        kind_length_->set_auto_created(false);
        break;

      /*  case KeyString::MSTATSPOP_FREQ_MISSING_SHORT:           //-x ***NOT DONE***
        freq_missing_ms_->set_value_string(arguments);
        freq_missing_ms_->set_auto_created(false);
        break;
        case KeyString::MSTATSPOP_N_CCOV_SHORT:           //-y ***NOT DONE***
        n_ccov_->set_value_string(arguments);
        n_ccov_->set_auto_created(false);
        break;*/

        case KeyString::MSTATSPOP_LOCATION_MISSING_SHORT:           //-M ***NOT DONE***
        location_missing_ms_->set_value_string(arguments);
        location_missing_ms_->set_auto_created(false);
        break;
        
        case KeyString::MSTATSPOP_FIRST_SLIDE_SHORT:           //-Z ***NOT DONE***
        first_slide_->set_value_string(arguments);
        first_slide_->set_auto_created(false);
        break;

      /// Command options: Help

      case KeyString::MSTATSPOP_HELP_SHORT:                   //-h
        run_only_help_ = true;
        break;

      /// Command options: New & Not done

      //case KeyString::MSTATSPOP_WEIGHTS_VARIANTS_FILE_SHORT:
      //  file_effsz_->set_value(arguments);
      //  file_effsz_->set_auto_created(false);
      //  break;

      case KeyString::MSTATSPOP_COUNT_TRANSITIONS_SHORT:
        break;

      case KeyString::MSTATSPOP_COUNT_TRANSVERSION_SHORT:
        break;

      case KeyString::MSTATSPOP_COUNT_GC_MUTATIONS_SHORT:
        break;

      case KeyString::MSTATSPOP_COUNT_AT_MUTATIONS_SHORT:
        break;

      default:
        break;
      }
    }
  }

     
  return (parseResult);
}

void CCMDmstatspop::Run() {
  /// ==========================================================================
  /// MSTATSPOP
  /// ==========================================================================
  calc_mstatspop_->SetInput(formatfile_);                                       //-f
  calc_mstatspop_->SetInput(file_in_);                                          //-i
  calc_mstatspop_->SetInput(output_);                                           //-o
  calc_mstatspop_->SetInput(populations_initial_);                              //-N
  calc_mstatspop_->SetInput(b_outgroup_presence_);                              //-G
  calc_mstatspop_->SetInput(b_include_unknown_);                                //-u
  calc_mstatspop_->SetInput(out_file_name_);                                    //-T
  calc_mstatspop_->SetInput(file_H1f_);                                         //-A
  calc_mstatspop_->SetInput(file_H0f_);                                         //-S
  calc_mstatspop_->SetInput(r2i_ploidies_);                                     //-P
  calc_mstatspop_->SetInput(sort_nsam_);                                        //-O
  calc_mstatspop_->SetInput(niter_);                                            //-t
  calc_mstatspop_->SetInput(seed_);                                             //-s
  calc_mstatspop_->SetInput(window_);                                           //-w
  calc_mstatspop_->SetInput(slide_);                                            //-z
  calc_mstatspop_->SetInput(physical_length_);                                  //-Y
  calc_mstatspop_->SetInput(file_wcoord_);                                      //-W
  calc_mstatspop_->SetInput(file_wps_);                                         //-E
  calc_mstatspop_->SetInput(length_);                                           //-l
  calc_mstatspop_->SetInput(niterdata_);                                        //-r
  calc_mstatspop_->SetInput(file_mas_);                                         //-m
  calc_mstatspop_->SetInput(ms_svratio_);                                       //-v
  calc_mstatspop_->SetInput(b_force_outgroup_);                                 //-F
  calc_mstatspop_->SetInput(freq_revert_);                                      //-q
  calc_mstatspop_->SetInput(ploidy_);                                           //-p
  calc_mstatspop_->SetInput(file_GFF_);                                         //-g
  calc_mstatspop_->SetInput(subset_positions_);
  calc_mstatspop_->SetInput(code_name_);
  calc_mstatspop_->SetInput(genetic_code_);
  calc_mstatspop_->SetInput(criteria_transcript_);                              //-c
  calc_mstatspop_->SetInput(b_mask_print_);                                     //-K
  //calc_mstatspop_->SetInput(file_effsz_);                                       //
  calc_mstatspop_->SetInput(scaffold_name_);                                    //-n
  calc_mstatspop_->SetInput(kind_length_);
  calc_mstatspop_->SetInput(location_missing_ms_);
  calc_mstatspop_->SetInput(first_slide_);

  calc_mstatspop_->SetOutput(calc_output_);
 /* calc_mstatspop_->SetOutput(out_stats_So_);
  calc_mstatspop_->SetOutput(out_stats_thetaSo_);
  calc_mstatspop_->SetOutput(out_stats_thetaTo_);
  calc_mstatspop_->SetOutput(out_stats_thetaFL_);
  calc_mstatspop_->SetOutput(out_stats_thetaFW_);
  calc_mstatspop_->SetOutput(out_stats_thetaL_);
  calc_mstatspop_->SetOutput(out_stats_thetaSA_);
  calc_mstatspop_->SetOutput(out_stats_thetaTA_);
  calc_mstatspop_->SetOutput(out_stats_K_);
  calc_mstatspop_->SetOutput(out_stats_thetaTHKY_);
  calc_mstatspop_->SetOutput(out_stats_KHKY_);
  calc_mstatspop_->SetOutput(out_stats_thetaS_);
  calc_mstatspop_->SetOutput(out_stats_thetaT_);
  calc_mstatspop_->SetOutput(out_stats_hapw_);
  calc_mstatspop_->SetOutput(out_stats_nhpop_);
  calc_mstatspop_->SetOutput(out_stats_Dtaj_);
  calc_mstatspop_->SetOutput(out_stats_Dfl_);
  calc_mstatspop_->SetOutput(out_stats_Ffl_);
  calc_mstatspop_->SetOutput(out_stats_Hnfw_);
  calc_mstatspop_->SetOutput(out_stats_Ez_);
  calc_mstatspop_->SetOutput(out_stats_Yach_);
  calc_mstatspop_->SetOutput(out_stats_FH_);
  calc_mstatspop_->SetOutput(out_stats_Fs_);
  calc_mstatspop_->SetOutput(out_stats_mdsd_);
  calc_mstatspop_->SetOutput(out_stats_mdg1_);
  calc_mstatspop_->SetOutput(out_stats_mdg2_);
  calc_mstatspop_->SetOutput(out_stats_fst1all_);
  calc_mstatspop_->SetOutput(out_stats_fsth_);
  calc_mstatspop_->SetOutput(out_stats_fstHKY_);
  calc_mstatspop_->SetOutput(out_stats_piwHKY_);
  //calc_mstatspop_->SetOutput(out_stats_piaHKY_);
  */
  calc_mstatspop_->Prepare();
  calc_mstatspop_->Calculate(manager()->all_commands()->dry_run());
  calc_mstatspop_->Finalize();
  // =========================================================================
}

void CCMDmstatspop::Finalize() {
  /// Clean the command to reuse it later:
  
  DM_DEL_CALC(calc_mstatspop_)
    
  DM_DEL_DATA(populations_initial_)
  DM_DEL_DATA(ploidy_);
  DM_DEL_DATA(b_include_unknown_);
  DM_DEL_DATA(out_file_name_);
  DM_DEL_DATA(b_force_outgroup_);
  DM_DEL_DATA(b_outgroup_presence_);
  DM_DEL_DATA(r2i_ploidies_)
  DM_DEL_DATA(file_mas_)
  DM_DEL_DATA(niter_)
  DM_DEL_DATA(niterdata_)
  DM_DEL_DATA(ms_svratio_)
  DM_DEL_DATA(length_)
  DM_DEL_DATA(freq_revert_)
  DM_DEL_DATA(file_GFF_)
  DM_DEL_DATA(subset_positions_)
  DM_DEL_DATA(code_name_)
  DM_DEL_DATA(genetic_code_)
  DM_DEL_DATA(file_H0f_)
  DM_DEL_DATA(file_H1f_)
  DM_DEL_DATA(criteria_transcript_)
  DM_DEL_DATA(file_in_)
  DM_DEL_DATA(sort_nsam_)
  DM_DEL_DATA(formatfile_)
  DM_DEL_DATA(file_wps_)
  DM_DEL_DATA(file_wcoord_)
  DM_DEL_DATA(window_)
  DM_DEL_DATA(slide_)
  DM_DEL_DATA(physical_length_)
  //DM_DEL_DATA(file_effsz_)
  DM_DEL_DATA(scaffold_name_)
  DM_DEL_DATA(kind_length_)
  DM_DEL_DATA(location_missing_ms_)
  DM_DEL_DATA(first_slide_)

  DM_DEL_DATA(calc_output_)
 /* DM_DEL_DATA(out_stats_So_)
  DM_DEL_DATA(out_stats_thetaSo_)
  DM_DEL_DATA(out_stats_thetaTo_)
  DM_DEL_DATA(out_stats_thetaFL_)
  DM_DEL_DATA(out_stats_thetaFW_)
  DM_DEL_DATA(out_stats_thetaL_)
  DM_DEL_DATA(out_stats_thetaSA_)
  DM_DEL_DATA(out_stats_thetaTA_)
  DM_DEL_DATA(out_stats_K_)
  DM_DEL_DATA(out_stats_thetaTHKY_)
  DM_DEL_DATA(out_stats_KHKY_)
  DM_DEL_DATA(out_stats_thetaS_)
  DM_DEL_DATA(out_stats_thetaT_)
  DM_DEL_DATA(out_stats_hapw_)
  DM_DEL_DATA(out_stats_nhpop_)
  DM_DEL_DATA(out_stats_Dtaj_)
  DM_DEL_DATA(out_stats_Dfl_)
  DM_DEL_DATA(out_stats_Ffl_)
  DM_DEL_DATA(out_stats_Hnfw_)
  DM_DEL_DATA(out_stats_Ez_)
  DM_DEL_DATA(out_stats_Yach_)
  DM_DEL_DATA(out_stats_FH_)
  DM_DEL_DATA(out_stats_Fs_)
  DM_DEL_DATA(out_stats_mdsd_)
  DM_DEL_DATA(out_stats_mdg1_)
  DM_DEL_DATA(out_stats_mdg2_)
  DM_DEL_DATA(out_stats_fst1all_)
  DM_DEL_DATA(out_stats_fsth_)
  DM_DEL_DATA(out_stats_fstHKY_)
  DM_DEL_DATA(out_stats_piwHKY_)
  //DM_DEL_DATA(out_stats_piaHKY_)
  */
  DM_DEL_ALL_LOCAL_DATA    
}

