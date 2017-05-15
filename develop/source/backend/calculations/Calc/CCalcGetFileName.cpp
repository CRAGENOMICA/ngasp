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
 *  \brief     CCalcGetFileName.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 10, 2017
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcGetFileName.h"

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"
#include "CCalcExec.h"

#include "../../data_manager/Data/CDataTextFile.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../util/CFile.h"


CCalcGetFileName::CCalcGetFileName()
: ICalculation(KeyString::CALC_GET_FILE_NAME, // Calculation Name
KeyString::CALC_GET_FILE_NAME_BRIEF_DESC, // Brief Description
KeyString::CALC_GET_FILE_NAME_DESC, // Long Description
KeyString::NGASP_AUTHORS, // Authors
KeyString::MSTATSPOP_COPYRIGHT, // Copyright
KeyString::GENERIC_CITATIONS, // Citations
KeyString::UNDEFINED_STRING) { // See also
    BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(input_file_, // Variable
            UNDEFINED_STRING, // Group
            CALC_GET_FILE_NAME_FILE_1, // Short Name
            CALC_GET_FILE_NAME_FILE_1_LONG, // Long Name
            CALC_GET_FILE_NAME_FILE_1_DESC, // Description
            CALC_GET_FILE_NAME_FILE_1_SAMP, // Example
            CALC_GET_FILE_NAME_FILE_1_ONLY, // Use only if
            CALC_GET_FILE_NAME_FILE_1_DEFV, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_mandatory) // Required

            SET_OUTPUT_INFO(file_name_, // Variable
            UNDEFINED_STRING, // Group
            CALC_GET_FILE_NAME_NAME, // Short Name
            CALC_GET_FILE_NAME_NAME_LONG, // Long Name
            CALC_GET_FILE_NAME_NAME_DESC, // Description
            CALC_GET_FILE_NAME_NAME_SAMP, // Example
            CALC_GET_FILE_NAME_NAME_ONLY, // Use only if
            CALC_GET_FILE_NAME_NAME_DEFV, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_mandatory) // Required
            END_CALCULATION_INTERFACE_DEFINITION
}

CCalcGetFileName::~CCalcGetFileName() {
}

void CCalcGetFileName::Prepare(void) {
    DM_GET_INPUTS
        DM_INPUT(input_file_)
    DM_GET_OUTPUTS
        DM_OUTPUT(file_name_)
    DM_END
}

void CCalcGetFileName::Calculate(bool dry_run) {
/*
    I do not want a dry_run in this calculation.

    if (dry_run == true) {
        return;
    }
*/

    file_name_->set_value(input_file_->value());
}

void CCalcGetFileName::Finalize(void) {
    DM_DEL_ALL_LOCAL_DATA
}

