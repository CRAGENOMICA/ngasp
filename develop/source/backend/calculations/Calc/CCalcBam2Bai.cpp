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
 *  \brief     CCalcBam2Bai.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */
#include "CCalcBam2Bai.h"

#include <cmath>
#include <string.h>

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"

#include <export.h>

CCalcBam2Bai::CCalcBam2Bai()
: ICalculation(KeyString::CALC_BAM2BAI,
               KeyString::CALC_BAM2BAI_BRIEF_DESC,
               KeyString::CALC_BAM2BAI_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(bam_file_,                                                   // Variable
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
    SET_OUTPUT_INFO(bai_file_,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)  
//    SET_OUTPUT_INFO(index_list_,                                                  // Variable
//                   UNDEFINED_STRING,                                            // Group
//                   UNDEFINED_STRING,                                            // Short Name
//                   UNDEFINED_STRING,                                            // Long Name
//                   UNDEFINED_STRING,                                            // Description
//                   UNDEFINED_STRING,                                            // Example
//                   UNDEFINED_STRING,                                            // Use only if
//                   UNDEFINED_STRING,                                            // Default value
//                   UNDEFINED_VALUE,                                             // Min. Value
//                   UNDEFINED_VALUE,                                             // Max. Value
//                   OPTTYPE_mandatory)  
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcBam2Bai::~CCalcBam2Bai() {
}

void CCalcBam2Bai::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(bam_file_)
  DM_GET_OUTPUTS
    DM_OUTPUT(bai_file_)
  DM_END
  
  
  if (bai_file_->value() == "") {
    bai_file_->set_value(CFile::GetPathFileNameWithoutExtension(bam_file_->value()) + ".bai");
  }  
}

void CCalcBam2Bai::Calculate(bool dry_run) {
    if (dry_run == true) {
        return;
    }

    char *p_bam_file = new char[bam_file_->value().length() + 1];
    strcpy(p_bam_file, bam_file_->value().c_str());    

    if (CFile::Exists(bai_file_->value()) == false) {
        char *p_bai_file = new char[bai_file_->value().length() + 1];
        strcpy(p_bai_file, bai_file_->value().c_str());

        char *argv[] = {"index",
            "-b",
            p_bam_file,
            p_bai_file,
            NULL};
        int argc = sizeof (argv) / sizeof (char*) - 1;

        bam_index(argc, argv);

        delete []p_bam_file;
        delete []p_bai_file;
    }
}

void CCalcBam2Bai::Finalize(void) {
    DM_DEL_ALL_LOCAL_DATA
}

