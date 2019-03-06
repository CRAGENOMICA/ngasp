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
 *  \brief     CCalcFasta2DnaMatrix.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 22, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcFasta2DnaMatrix.h"

#include <string>
#include <seqan/seq_io.h>  //!prev_disabled
#include <sstream>

#include "../../language/CStringTable.h"
#include "../util/CDnaTools.h"
#include "../../util/CVectorTools.h"
#include "../../data_manager/common/CDataAccess.h"
#include "../CAllCalculations.h"

CCalcFasta2DnaMatrix::CCalcFasta2DnaMatrix()
: ICalculation(KeyString::CALC_FASTA2DNAMATRIX,
               KeyString::CALC_FASTA2DNAMATRIX_BRIEF_DESC,
               KeyString::CALC_FASTA2DNAMATRIX_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(fasta,                                                       // Variable
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
  
    SET_OUTPUT_INFO(dna_matrix,                                                 // Variable
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

CCalcFasta2DnaMatrix::~CCalcFasta2DnaMatrix() {
}

void CCalcFasta2DnaMatrix::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(fasta)
    DM_INPUT(ploidy)
    DM_INPUT(include_unknown)
    DM_INPUT(force_outgroup)
    DM_INPUT(outgroup_presence)
    DM_INPUT(vint_perpop_nsam)
    DM_INPUT(npops)
    DM_INPUT(int_total_nsam)
  DM_GET_OUTPUTS
    DM_OUTPUT(dna_matrix)
  DM_END
}

//!prev_disabled
void CCalcFasta2DnaMatrix::Calculate(bool dry_run) {



//  CDnaTools dna_tools;
//
//  // By default the min expected records in file are at least the int total nsam:
//
//  long int min_expected_file_records = int_total_nsam->value();
//
//  // But if ploidy is '2', the min expected records in the file is the middle:
//
//  if (ploidy->value() == DIPLOID) {
//    min_expected_file_records /= 2;
//  }
//
//  if (fasta->regs() < min_expected_file_records) {
//    ERROR_MSG << STR(MORE_POPS_EXPECTED) END_MSG;
//  }
//  else {
//    dna_matrix->ReserveMemory(int_total_nsam->value(),
//                              fasta->reg_length(), STR(DEFAULT_CHAR)[0]);
//
//    typedef seqan::Iterator<seqan::StringSet<CDataStringSet::TBase> >::Type
//      TStringSetIterator;
//
//    // ===========================================================================
//    // Loop FASTA file records for creating the output matrix:
//    // ===========================================================================
//    int used_regs = 0;
//    for (TStringSetIterator it = fasta->Begin();
//         ((it != fasta->End())&&
//          (used_regs < int_total_nsam->value()));
//         ++it) {
//      int column = 0;
//
//      // -------------------------------------------------------------------------
//      // Loop record bases:
//      // -------------------------------------------------------------------------
//      for (seqan::Iterator<CDataStringSet::TBase>::Type it1 = seqan::begin(*it);
//              it1 != seqan::end(*it); ++it1) {
//          // (*it1) contains 'T' or 'G' or ...
//          // dna_matrix must contain '1' or '3' or ...
//
//        switch (ploidy->value()) {
//          case HAPLOID:
//          default:
//            (*dna_matrix)[(used_regs * dna_matrix->reg_length()) + column] =
//                    dna_tools.char2dnacode(*it1)->code_ploidy_1_;
//            break;
//          case DIPLOID:
//            (*dna_matrix)[((used_regs + 0) * dna_matrix->reg_length()) + column] =
//                    dna_tools.char2dnacode(*it1)->code_ploidy_2a_;
//
//            // duplication is done just in the next register:
//            (*dna_matrix)[((used_regs + 1) * dna_matrix->reg_length()) + column] =
//                    dna_tools.char2dnacode(*it1)->code_ploidy_2b_;
//            break;
//        }
//
//        column++;
//      }
//      // -------------------------------------------------------------------------
//
//      switch (ploidy->value()) {
//        case HAPLOID:
//          used_regs = used_regs + 1;
//          break;
//        case DIPLOID:
//          used_regs = used_regs + 2;
//          break;
//      }
//
//    }
//
//    // =========================================================================
//    // ADD OUTGROUP
//    // =========================================================================
//    if (outgroup_presence->value() == 0) {
//      // Part 2: Copy the first register into the outgroup register:
//      for (int j=0; j < dna_matrix->reg_length(); j++) {
//        switch (ploidy->value()) {
//          case '1':
//            // Last record
//            (*dna_matrix)[(dna_matrix->reg_length() * (dna_matrix->regs()-1)) + j] = (*dna_matrix)[(dna_matrix->reg_length() * 0) + j];  // Equal to First record
//            break;
//          case '2':
//            // Penultimate record (regs-2):
//            (*dna_matrix)[(dna_matrix->reg_length() * (dna_matrix->regs()-2)) + j] = (*dna_matrix)[(dna_matrix->reg_length() * 0) + j];  // Equal to First record
//            // Last record (regs-1):
//            (*dna_matrix)[(dna_matrix->reg_length() * (dna_matrix->regs()-1)) + j] = (*dna_matrix)[(dna_matrix->reg_length() * 0) + j];  // Equal to First record
//            break;
//        }
//      }
//    }
//
//    // =========================================================================
//    // For each column, leave only two valid column bases depending on:
//    //
//    //     By default:    valid_column_base_1 = first_most_repeated_base in column
//    //                    valid_column_base_2 = second_most_repeated_base in column
//    //
//    //     Condition 1:   valid_column_base_1 = outgroup base
//    //                    valid_column_base_2 = first_most_repeated_base in column
//    //                                          or second if first is = outgroup
//    //
//    // Other bases will be replaced by Missing.
//    // =========================================================================
//
//    CDnaTools::NitrogenBase base = CDnaTools::NitrogenBase::Undefined;
//    CDnaTools::NitrogenBase first_more_repeated_base = CDnaTools::NitrogenBase::Undefined;
//    CDnaTools::NitrogenBase second_more_repeated_base = CDnaTools::NitrogenBase::Undefined;
//    CDnaTools::NitrogenBase outgroup_base = CDnaTools::NitrogenBase::Undefined;
//    CDnaTools::NitrogenBase valid_column_base_1 = CDnaTools::NitrogenBase::Undefined;
//    CDnaTools::NitrogenBase valid_column_base_2 = CDnaTools::NitrogenBase::Undefined;
//
//    if (ploidy->value() == DIPLOID) {
//
//      for(long int c = 0; c < dna_matrix->reg_length(); c++) {
//        std::map<CDnaTools::NitrogenBase, long int> freq_bases_map;
//
//        freq_bases_map[CDnaTools::NitrogenBase::Thymine]    = 0;
//        freq_bases_map[CDnaTools::NitrogenBase::Cytosine]   = 0;
//        freq_bases_map[CDnaTools::NitrogenBase::Guanine]    = 0;
//        freq_bases_map[CDnaTools::NitrogenBase::Adenine]    = 0;
//        freq_bases_map[CDnaTools::NitrogenBase::Weak]       = 0;
//        freq_bases_map[CDnaTools::NitrogenBase::Amino]      = 0;
//        freq_bases_map[CDnaTools::NitrogenBase::Purine]     = 0;
//        freq_bases_map[CDnaTools::NitrogenBase::Pyrimidine] = 0;
//        freq_bases_map[CDnaTools::NitrogenBase::Keto]       = 0;
//        freq_bases_map[CDnaTools::NitrogenBase::Strong]     = 0;
//
//        for(long int r = 0; r < dna_matrix->regs(); r++) {
//
//          base = dna_tools.dnacode2base((*dna_matrix)[r * dna_matrix->reg_length() + c]);
//
//          if ((base != CDnaTools::NitrogenBase::Missing) &&
//              (base != CDnaTools::NitrogenBase::Gap)) {
//            // We do not want to include missing/gap in the map.
//            freq_bases_map[base]++;
//          }
//        }
//
//        // Get the outgroup base:
//        // ======================
//
//        outgroup_base = dna_tools.dnacode2base((*dna_matrix)[(dna_matrix->reg_length() * (dna_matrix->regs()-1)) + c]);
//
//        // Get most two repeated bases from current column:
//        // ================================================
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
//        // Get the first and second vector elements.
//        // (The first one will be the greatest one):
//        std::vector<std::pair<CDnaTools::NitrogenBase, long int> >::iterator b =
//                                                      freq_bases_vector.begin();
//
//        first_more_repeated_base = b->first;
//        b++;
//        second_more_repeated_base = b->first;
//
//        // By default:
//        // ===========
//        valid_column_base_1 = first_more_repeated_base;
//        valid_column_base_2 = second_more_repeated_base;
//
//        // Condition 1:
//        // ============
//        if ((include_unknown->value() == true) &&
//            (outgroup_base != CDnaTools::NitrogenBase::Missing) &&
//            (outgroup_base != CDnaTools::NitrogenBase::Gap)) {
//
//          valid_column_base_1 = outgroup_base;
//          valid_column_base_2 = (first_more_repeated_base != outgroup_base)?first_more_repeated_base:second_more_repeated_base;
//        }
//
//        // Loop the column for changing bases to missing if they are not one of
//        // the most repeated two bases of the column:
//        for(long int r = 0; r < dna_matrix->regs(); r++) {
//          base = dna_tools.dnacode2base((*dna_matrix)[r * dna_matrix->reg_length() + c]);
//
//          if ((base != valid_column_base_1) &&
//              (base != valid_column_base_2) &&
//              (base != CDnaTools::NitrogenBase::Missing) &&
//              (base != CDnaTools::NitrogenBase::Gap)) {                         // Change Gaps by Missing?? If yes then remove (base != CDnaTools::NitrogenBase::Gap)
//            (*dna_matrix)[r * dna_matrix->reg_length() + c] =
//                    dna_tools.base2dnacode(CDnaTools::NitrogenBase::Missing);
//          }
//        }
//      }
//    }
//  }
}

void CCalcFasta2DnaMatrix::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
