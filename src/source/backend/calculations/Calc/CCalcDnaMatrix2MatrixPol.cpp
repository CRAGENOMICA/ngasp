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
 *  \brief     CCalcDnaMatrix2MatrixPol.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 22, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcDnaMatrix2MatrixPol.h"

#include <string>
#include <seqan/seq_io.h>  //!prev_disabled
#include <sstream>
#include <algorithm>  // std::sort

#include "../../language/CStringTable.h"
#include "../../util/CVectorTools.h"
#include "../../data_manager/common/CDataAccess.h"


CCalcDnaMatrix2MatrixPol::CCalcDnaMatrix2MatrixPol()
: ICalculation(KeyString::CALC_DNAMATRIX2MATRIXPOL,
               KeyString::CALC_DNAMATRIX2MATRIXPOL_BRIEF_DESC,
               KeyString::CALC_DNAMATRIX2MATRIXPOL_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(dna_matrix,                                                  // Variable
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
                   OPTTYPE_mandatory)                                           // Required)
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
                   OPTTYPE_mandatory)                                           // Required)
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
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(matrix_sizepos,                                              // Variable
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
    SET_INPUT_INFO(matrix_segrpos,                                              // Variable
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
                   OPTTYPE_mandatory)                                           // Required)
    SET_OUTPUT_INFO(positions,                                                  // Variable
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
    SET_OUTPUT_INFO(frequencies,                                                // Variable
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

CCalcDnaMatrix2MatrixPol::~CCalcDnaMatrix2MatrixPol() {
}

void CCalcDnaMatrix2MatrixPol::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(dna_matrix)
    DM_INPUT(ploidy)
    DM_INPUT(include_unknown)
    DM_INPUT(force_outgroup)
    DM_INPUT(outgroup_presence)
    DM_INPUT(vint_perpop_nsam)
    DM_INPUT(npops)
    DM_INPUT(int_total_nsam)
    DM_INPUT(matrix_sizepos)
    DM_INPUT(matrix_segrpos)
  DM_GET_OUTPUTS
    DM_OUTPUT(matrix_pol)
    DM_OUTPUT(positions)
    DM_OUTPUT(frequencies)
  DM_END
}

void CCalcDnaMatrix2MatrixPol::Calculate(bool dry_run) {



//  // ===========================================================================
//  // First Dna Matrix Loop. For getting the columns that will be in the output
//  // ===========================================================================
//
//  long int width = dna_matrix->reg_length();
//  long int height = dna_matrix->regs();
//
//  CDnaTools::NitrogenBase base = CDnaTools::NitrogenBase::Undefined;
//  // CDnaTools::NitrogenBase first_known_column_base = CDnaTools::NitrogenBase::Undefined;
//  CDnaTools::NitrogenBase most_repeated_base = CDnaTools::NitrogenBase::Undefined;
//
//
//  std::list<long int> included_columns;
//  std::list<CDnaTools::NitrogenBase> most_repeated_base_in_column;
//
//  CDnaTools dna_tools;
//  bool discard_column = false;
//  bool current_column_has_missings_or_unknown_data = false;
//
//
//  for (long int i=0; i<width; i++) {
//    discard_column = false;
//    // matrix_sizepos contains those columns that have to be discarded:
//
//    if ((matrix_sizepos != NULL) &&
//        ((*matrix_sizepos).Size() != 0) && //!2May
//        ((*matrix_sizepos)[i] == 0 /*< 0.67*/ )) {
//			discard_column = true;
//		} else {
//      std::map<CDnaTools::NitrogenBase, long int> freq_bases_map;
//
//      freq_bases_map[CDnaTools::NitrogenBase::Thymine]    = 0;
//      freq_bases_map[CDnaTools::NitrogenBase::Cytosine]   = 0;
//      freq_bases_map[CDnaTools::NitrogenBase::Guanine]    = 0;
//      freq_bases_map[CDnaTools::NitrogenBase::Adenine]    = 0;
//      freq_bases_map[CDnaTools::NitrogenBase::Missing]    = 0;
//      freq_bases_map[CDnaTools::NitrogenBase::Weak]       = 0;
//      freq_bases_map[CDnaTools::NitrogenBase::Amino]      = 0;
//      freq_bases_map[CDnaTools::NitrogenBase::Purine]     = 0;
//      freq_bases_map[CDnaTools::NitrogenBase::Pyrimidine] = 0;
//      freq_bases_map[CDnaTools::NitrogenBase::Keto]       = 0;
//      freq_bases_map[CDnaTools::NitrogenBase::Strong]     = 0;
//
//
//      // most_repeated_base = CDnaTools::NitrogenBase::Undefined;
//      // first_known_column_base = CDnaTools::NitrogenBase::Undefined;
//      current_column_has_missings_or_unknown_data = false;
//
//      for (long int j=0; ((j<height) && (discard_column == false)); j++) {
//        // Get the current base:
//
//        base = dna_tools.dnacode2base((*dna_matrix)[j*width + i]);
//
//        freq_bases_map[base]++;
//
//        if ((base ==  CDnaTools::NitrogenBase::Missing) ||
//         (base ==  CDnaTools::NitrogenBase::Gap)) {
//          current_column_has_missings_or_unknown_data = true;
//        }
//
//        if ((current_column_has_missings_or_unknown_data == true) &&
//            (include_unknown->value() == 0)) {
//          // Exclude column if it has missings and include missings is false:
//          discard_column = true;
//        }
//      }
//
//
//      // Get the number of different bases of this current column:
//
//      int num_diff_bases_found =
//        ((freq_bases_map[CDnaTools::NitrogenBase::Thymine]    != 0)?1:0) +
//        ((freq_bases_map[CDnaTools::NitrogenBase::Cytosine]   != 0)?1:0) +
//        ((freq_bases_map[CDnaTools::NitrogenBase::Guanine]    != 0)?1:0) +
//        ((freq_bases_map[CDnaTools::NitrogenBase::Adenine]    != 0)?1:0) +
//        ((freq_bases_map[CDnaTools::NitrogenBase::Weak]       != 0)?1:0) +
//        ((freq_bases_map[CDnaTools::NitrogenBase::Amino]      != 0)?1:0) +
//        ((freq_bases_map[CDnaTools::NitrogenBase::Purine]     != 0)?1:0) +
//        ((freq_bases_map[CDnaTools::NitrogenBase::Pyrimidine] != 0)?1:0) +
//        ((freq_bases_map[CDnaTools::NitrogenBase::Keto]       != 0)?1:0) +
//        ((freq_bases_map[CDnaTools::NitrogenBase::Strong]     != 0)?1:0);
//
//
//
//      if (num_diff_bases_found != 2) {
//        // Exclude column if it has always the same base or it has more than 2
//        // different bases:
//        discard_column = true;
//      }
//
//
//      if ((matrix_segrpos != NULL) &&
//          (matrix_segrpos->Size() != 0) &&
//          ((*matrix_segrpos)[i] == 0)) {
//        discard_column = true;
//      }
//
//      if (discard_column==false) {
//
//        // Get most repeated base from current column:
//
//        // Transform the map into a vector:
//        std::vector<std::pair<CDnaTools::NitrogenBase, long int> >
//                freq_bases_vector(freq_bases_map.begin(), freq_bases_map.end());
//
//        // Sort vector items from greater to lower.
//        std::sort(freq_bases_vector.begin(),
//                  freq_bases_vector.end(),
//                  greater_than_key<CDnaTools::NitrogenBase, long int>());
//
//        // Get the first vector element.
//        // (The first one will be the greatest one):
//        std::vector<std::pair<CDnaTools::NitrogenBase, long int> >::iterator b =
//                                                      freq_bases_vector.begin();
//        most_repeated_base = b->first;
//
//
//        // Include column into the output matrix:
//        if (current_column_has_missings_or_unknown_data == true) {
//          // column number is negative if the column has missing data:
//          included_columns.push_back(i * (-1));
//        } else {
//          included_columns.push_back(i);
//        }
//        most_repeated_base_in_column.push_back(most_repeated_base);
//      }
//    }
//  }
//
//  // ===========================================================================
//  // Second Dna Matrix Loop. For creating the output
//  // ===========================================================================
//
//  matrix_pol->ReserveMemory(dna_matrix->regs(), included_columns.size(), STR(DEFAULT_CHAR)[0]);
//  positions->ReserveMemory(included_columns.size(), 0);
//  frequencies->ReserveMemory(included_columns.size(), 0);
//
//  long int i = 0;
//  long int output_i = 0;
//  std::list<long int>::iterator it1 = included_columns.begin();
//  std::list<CDnaTools::NitrogenBase>::iterator it2 = most_repeated_base_in_column.begin();
//
//  long int position = 0;
//
//  for (; ((it1 != included_columns.end()) &&
//          (it2 != most_repeated_base_in_column.end())); ++it1, ++it2) {
//    i = (*it1);
//
//    // Column number 'i' is negative if the column has missings, so...:
//    if (i>0) {
//      (*positions)[output_i] = i + 1;  // e.g. "i = 5" --> "position = 6"
//    } else {
//      (*positions)[output_i] = i - 1;  // e.g. "i = -5" --> "position = -6"
//    }
//
//    // And now, we need the absolute value of 'i' for accessing the dna_matrix:
//    if (i < 0) { i *= (-1); }
//
//
//    for (long int j=0; j<height; j++) {
//      // Get the current base:
//      base = dna_tools.dnacode2base((*dna_matrix)[j*width + i]);
//
//      position = output_i * dna_matrix->regs() + j;                                 // old remove--> j*included_columns.size() + output_i
//
//      if (base == (*it2)) {
//        (*matrix_pol)[position] = '0';
//      } else {
//        if ((base == CDnaTools::NitrogenBase::Missing) ||
//            (base == CDnaTools::NitrogenBase::Gap) ) {
//          (*matrix_pol)[position] = '-';
//        } else {
//          (*matrix_pol)[position] = '1';
//        }
//
//        (*frequencies)[output_i]++;
//
//      }
//    }
//    output_i++;
//  }
}

void CCalcDnaMatrix2MatrixPol::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
