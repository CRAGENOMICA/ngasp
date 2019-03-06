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
 *  \brief     CCalcGetMeanReadDepth.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 12, 2017
 *  \pre
 *  \bug
 *  \warning
 */
#include "CCalcGetMeanReadDepth.h"

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"

CCalcGetMeanReadDepth::CCalcGetMeanReadDepth()
: ICalculation(KeyString::CALC_GET_MRD,
               KeyString::CALC_GET_MRD_BRIEF_DESC,
               KeyString::CALC_GET_MRD_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {

  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(bam_files_,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_GET_MRD_BAM_FILES,                                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CALC_GET_MRD_BAM_FILES_DESC,                                 // Description
                   UNDEFINED_STRING,                                            // CutGTF
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_INPUT_INFO(sequence_length_,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_GET_MRD_SEQ_LEN,                                        // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CALC_GET_MRD_SEQ_LEN_DESC,                                   // Description
                   UNDEFINED_STRING,                                            // CutGTF
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required

    SET_OUTPUT_INFO(mrd_,                                                       // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_GET_MRD_MRD,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CALC_GET_MRD_MRD_DESC,                                       // Description
                   UNDEFINED_STRING,                                            // CutGTF
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                            // Required
  END_CALCULATION_INTERFACE_DEFINITION

}

CCalcGetMeanReadDepth::~CCalcGetMeanReadDepth() {
}

void CCalcGetMeanReadDepth::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(bam_files_)
    DM_INPUT(sequence_length_)
  DM_GET_OUTPUTS
    DM_OUTPUT(mrd_)
  DM_END
}

/**
 *
 */
void CCalcGetMeanReadDepth::Calculate(bool dry_run) {
    if (dry_run == true) {
        return;
    }

    std::string path;
    std::string command = "echo ";

    for (int i = 0; i < bam_files_->Size(); i++) {
        if (i == 0) { path = CFile::GetPathFromFileName((*bam_files_)[i]); }
        else { command += ","; }
        command += "$(samtools depth " + (*bam_files_)[i] + " | awk '{sumrd +=$3} END {print sumrd/" + CStringTools::ToString(sequence_length_->value()) + "}' - )";
    }

    command += " > " + path + "mrd.tmp";
    DEBUG_MSG << command END_MSG;
    system(command.c_str());

    std::string buffer;
    if (CFile::ReadAll(path + "mrd.tmp", buffer) == true) {
        mrd_->set_data_string(buffer);

        CFile::Remove(path + "mrd.tmp");
    }
}

void CCalcGetMeanReadDepth::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

