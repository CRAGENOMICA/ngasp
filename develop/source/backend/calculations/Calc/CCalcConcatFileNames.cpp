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
 *  \brief     CCalcConcatFileNames.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 10, 2017
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcConcatFileNames.h"

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"
#include "CCalcExec.h"

#include "../../data_manager/Data/CDataTextFile.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../util/CFile.h"


CCalcConcatFileNames::CCalcConcatFileNames()
: ICalculation(KeyString::CALC_CONCAT_FILE_NAMES, // Calculation Name
KeyString::CALC_CONCAT_FILE_NAMES_BRIEF_DESC, // Brief Description
KeyString::CALC_CONCAT_FILE_NAMES_DESC, // Long Description
KeyString::NGASP_AUTHORS, // Authors
KeyString::MSTATSPOP_COPYRIGHT, // Copyright
KeyString::GENERIC_CITATIONS, // Citations
KeyString::UNDEFINED_STRING) { // See also
    BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(input_file_1, // Variable
            UNDEFINED_STRING, // Group
            CALC_CONCAT_FILEN_FILE_1, // Short Name
            CALC_CONCAT_FILEN_FILE_1_LONG, // Long Name
            CALC_CONCAT_FILEN_FILE_1_DESC, // Description
            CALC_CONCAT_FILEN_FILE_1_SAMP, // Example
            CALC_CONCAT_FILEN_FILE_1_ONLY, // Use only if
            CALC_CONCAT_FILEN_FILE_1_DEFV, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_mandatory) // Required

            SET_INPUT_INFO(input_file_2, // Variable
            UNDEFINED_STRING, // Group
            CALC_CONCAT_FILEN_FILE_2, // Short Name
            CALC_CONCAT_FILEN_FILE_2_LONG, // Long Name
            CALC_CONCAT_FILEN_FILE_2_DESC, // Description
            CALC_CONCAT_FILEN_FILE_2_SAMP, // Example
            CALC_CONCAT_FILEN_FILE_2_ONLY, // Use only if
            CALC_CONCAT_FILEN_FILE_2_DEFV, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_optional) // Required

            SET_OUTPUT_INFO(output_names, // Variable
            UNDEFINED_STRING, // Group
            CALC_CONCAT_FILEN_OUTPUT, // Short Name
            CALC_CONCAT_FILEN_OUTPUT_LONG, // Long Name
            CALC_CONCAT_FILEN_OUTPUT_DESC, // Description
            CALC_CONCAT_FILEN_OUTPUT_SAMP, // Example
            CALC_CONCAT_FILEN_OUTPUT_ONLY, // Use only if
            CALC_CONCAT_FILEN_OUTPUT_DEFV, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_mandatory) // Required
            END_CALCULATION_INTERFACE_DEFINITION
}

CCalcConcatFileNames::~CCalcConcatFileNames() {
}

void CCalcConcatFileNames::Prepare(void) {
    DM_GET_INPUTS
        DM_INPUT(input_file_1)
        DM_INPUT(input_file_2)
    DM_GET_OUTPUTS
        DM_OUTPUT(output_names)
    DM_END
}

void CCalcConcatFileNames::Calculate(bool dry_run) {
/*
    I do not want a dry_run in this calculation.

    if (dry_run == true) {
        return;
    }
*/

    /*
    Option 1:

               ------------
        file_1 []         [] output_names
        NULL   []         
               ------------

            output_names += file_1

    Option 2:

               ------------
        file_1 []         [] output_names
        file_2 []        
               ------------

            output_names = file_1 + file_2
     */
          

    if (input_file_1->value() != "") {

        if (input_file_2->value() == "") {
            // Option 1
            output_names->PushBack(input_file_1->value());
        }
        else {
            // Option 2
            output_names->DeleteMemory();
            output_names->PushBack(input_file_1->value());
            output_names->PushBack(input_file_2->value());
        }
    }
}

void CCalcConcatFileNames::Finalize(void) {
    DM_DEL_ALL_LOCAL_DATA
}

