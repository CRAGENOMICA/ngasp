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
 *  \brief     CCalcGetSeqLength.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 12, 2017
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcGetSeqLength.h"

#include <fstream>

#include "../../language/CStringTable.h"


CCalcGetSeqLength::CCalcGetSeqLength()
: ICalculation(KeyString::CALC_GET_SEQ_LEN,
               KeyString::CALC_GET_SEQ_LEN_BRIEF_DESC,
               KeyString::CALC_GET_SEQ_LEN_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {

  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(fasta_,                                                      // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_GET_SEQ_LEN_FASTA,                                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CALC_GET_SEQ_LEN_FASTA_DESC,                                 // Description
                   UNDEFINED_STRING,                                            // CutGTF
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  

    SET_OUTPUT_INFO(length_,                                                    // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_GET_SEQ_LEN_LEN,                                        // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CALC_GET_SEQ_LEN_LEN_DESC,                                   // Description
                   UNDEFINED_STRING,                                            // CutGTF
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  END_CALCULATION_INTERFACE_DEFINITION

}

CCalcGetSeqLength::~CCalcGetSeqLength() {
}

void CCalcGetSeqLength::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(fasta_)
  DM_GET_OUTPUTS
    DM_OUTPUT(length_)
  DM_END
  
}

/**
 *
 */
void CCalcGetSeqLength::Calculate(bool dry_run) {
    if (dry_run == true) {
        return;
    }

    length_->set_value(0);

    try {
        std::ifstream infile(fasta_->value());

        bool ready = false;
        

        for(std::string line; std::getline(infile, line); ) {
            if (ready == false) {
                if ((line != "") && (line[0] == '>')) {
                    ready = true;
                }
            } else {
                if (line != "") {
                    if (line[0] != '>') {
                        length_->add(line.length());
                    }
                    else {
                        break; // <---------------------------------------- get out of the "for" loop
                    }
                }
            }
        }
    } catch(...) {
        ERROR_MSG << "File not found: '" << fasta_->value() << "'..." END_MSG;
    }
}

void CCalcGetSeqLength::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

