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
 *  \brief     CCalcConcatStrings.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      February 23, 2017
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcConcatStrings.h"

#include "../../language/CStringTable.h"

#include "../../data_manager/Data/CDataStdString.h"

CCalcConcatStrings::CCalcConcatStrings()
: ICalculation(KeyString::CALC_CONCAT_STRINGS, // Calculation Name
KeyString::CALC_CONCAT_STRINGS_BRIEF_DESC, // Brief Description
KeyString::CALC_CONCAT_STRINGS_DESC, // Long Description
KeyString::NGASP_AUTHORS, // Authors
KeyString::MSTATSPOP_COPYRIGHT, // Copyright
KeyString::GENERIC_CITATIONS, // Citations
KeyString::UNDEFINED_STRING) { // See also
    BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(input_1_, // Variable
            UNDEFINED_STRING, // Group
            CALC_CONCAT_STRINGS_1, // Short Name
            CALC_CONCAT_STRINGS_1_LONG, // Long Name
            CALC_CONCAT_STRINGS_1_DESC, // Description
            CALC_CONCAT_STRINGS_1_SAMP, // Example
            CALC_CONCAT_STRINGS_1_ONLY, // Use only if
            CALC_CONCAT_STRINGS_1_DEFV, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_mandatory) // Required

            SET_INPUT_INFO(input_2_, // Variable
            UNDEFINED_STRING, // Group
            CALC_CONCAT_STRINGS_2, // Short Name
            CALC_CONCAT_STRINGS_2_LONG, // Long Name
            CALC_CONCAT_STRINGS_2_DESC, // Description
            CALC_CONCAT_STRINGS_2_SAMP, // Example
            CALC_CONCAT_STRINGS_2_ONLY, // Use only if
            CALC_CONCAT_STRINGS_2_DEFV, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_optional) // Required

            SET_OUTPUT_INFO(output_, // Variable
            UNDEFINED_STRING, // Group
            CALC_CONCAT_STRINGS_OUTPUT, // Short Name
            CALC_CONCAT_STRINGS_OUTPUT_LONG, // Long Name
            CALC_CONCAT_STRINGS_OUTPUT_DESC, // Description
            CALC_CONCAT_STRINGS_OUTPUT_SAMP, // Example
            CALC_CONCAT_STRINGS_OUTPUT_ONLY, // Use only if
            CALC_CONCAT_STRINGS_OUTPUT_DEFV, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_mandatory) // Required
            END_CALCULATION_INTERFACE_DEFINITION
}

CCalcConcatStrings::~CCalcConcatStrings() {
}

void CCalcConcatStrings::Prepare(void) {
    DM_GET_INPUTS
        DM_INPUT(input_1_)
        DM_INPUT(input_2_)
    DM_GET_OUTPUTS
        DM_OUTPUT(output_)
    DM_END
}

void CCalcConcatStrings::Calculate(bool dry_run) {
    if (dry_run == true) {
        return;
    }
    
    output_->set_value(input_1_->value() + input_2_->value());
}

void CCalcConcatStrings::Finalize(void) {
    DM_DEL_ALL_LOCAL_DATA
}

