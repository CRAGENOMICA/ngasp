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
 *  \brief     CCalcCutGTF.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      February 10, 2017
 *  \pre
 *  \bug
 *  \warning
 */
#include "CCalcCutGTF.h"

#include "../../language/CStringTable.h"

#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../util/CFile.h"

CCalcCutGTF::CCalcCutGTF()
: ICalculation(KeyString::CALC_CUT_GTF,
               KeyString::CALC_CUT_GTF_BRIEF_DESC,
               KeyString::CALC_CUT_GTF_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {

  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(input_gtf_file_,                                             // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCCUT_GTF_INPUT_GTF_FILE,                                 // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CCALCCUT_GTF_INPUT_GTF_FILE_DESC,                            // Description
                   UNDEFINED_STRING,                                            // CutGTF
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                            // Required
    SET_INPUT_INFO(selection_,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCCUT_GTF_SELECTION,                                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CCALCCUT_GTF_SELECTION_DESC,                                 // Description
                   UNDEFINED_STRING,                                            // CutGTF
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                            // Required
    SET_INPUT_INFO(input_sorted_, // Variable
                   UNDEFINED_STRING, // Group
                   CCALCCUT_GTF_INPUT_SORTED, // Short Name
                   UNDEFINED_STRING, // Long Name
                   CCALCCUT_GTF_INPUT_SORTED_DESC, // Description
                   UNDEFINED_STRING, // CutBED
                   UNDEFINED_STRING, // Use only if
                   CCALCCUT_GTF_INPUT_SORTED_DEFV, // Default value
                   UNDEFINED_VALUE, // Min. Value
                   UNDEFINED_VALUE, // Max. Value
                   OPTTYPE_optional) // Required
  
  
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
  

    SET_OUTPUT_INFO(output_gtf_file_,                                           // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCCUT_GTF_OUTPUT_GTF_FILE,                                // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CCALCCUT_GTF_OUTPUT_GTF_FILE_DESC,                           // Description
                   UNDEFINED_STRING,                                            // CutGTF
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                            // Required
  END_CALCULATION_INTERFACE_DEFINITION

}

CCalcCutGTF::~CCalcCutGTF() {
}

void CCalcCutGTF::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(input_gtf_file_)
    DM_INPUT(selection_)
    DM_INPUT(input_sorted_)
    DM_INPUT(keep_intermediate_results)
  DM_GET_OUTPUTS
    DM_OUTPUT(output_gtf_file_)
  DM_END
  
  // Output File Name Example:
  // Input_file     : a.gtf
  // Chrom selected : chr01
  // Output file    : a.chr01.gtf
  output_gtf_file_->set_value(CFile::GetPathFileNameWithoutExtension(input_gtf_file_->value()) + "." + selection_->value() + "." + CFile::GetExtensionFromFileName(input_gtf_file_->value()));

  if (keep_intermediate_results->value()) {
    DM_ITERATION_NUMBER(iteration_number)
    DM_ITERATION_VALUE(iteration_value)
    output_gtf_file_->set_value(CFile::ConcatenateIterationToFilePathName(output_gtf_file_->value(),
                            iteration_number->value(),
                            iteration_value->value()));
  }  
}

/**
 *
 */
void CCalcCutGTF::Calculate(bool dry_run) {
    if (dry_run == true) {
        return;
    }

    std::ifstream file(input_gtf_file_->value());

    if (file.is_open()) {
        std::streampos last_position = 0;

        if(input_sorted_->value() == true) {
            // ==================================================================================
            // Move to the last stored position
            // ==================================================================================
            CFile::MoveToLastAccessedPosition(input_gtf_file_->value(), file);
            // ==================================================================================
        }
        
        std::string output_gtf_file_buffer;

        bool selection_found = false;
        // Start reading lines:
        for (std::string line; (std::getline(file, line));) {
            // process line.

            std::size_t start_pos = line.find(selection_->value() + "\t");

            if ((start_pos != std::string::npos) && // It is not the end of the file
                    (start_pos == 0)) { // The tag of the search is at the beginning of the line
                selection_found = true;
                output_gtf_file_buffer += line;
                output_gtf_file_buffer += "\n";
                //std::string temp = line.substr(start_pos+6);
            } else {
                if (selection_found) {
                    // There is no more lines of the "selection" value.
                    break; // <---------------------------------------------------------------------------------- break the loop
                }
            }

            if(input_sorted_->value() == true) {
                // =================================================================================
                // Update the last position
                // =================================================================================
                last_position = file.tellg();
                // =================================================================================
            }
        }

        if(input_sorted_->value() == true) {
            // ==================================================================================
            // Store the last position
            // ==================================================================================
            CFile::StoreLastAccessedPosition(input_gtf_file_->value(), file, (selection_found) ? last_position : file.end);
            // ==================================================================================
        }

        CFile::ReplaceContentBy(output_gtf_file_->value(), output_gtf_file_buffer);
    } else {
        ERROR_MSG
                << "Failed to open file ' " << input_gtf_file_->value() << "'..." << EOL
                END_MSG;
    }
}

void CCalcCutGTF::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

