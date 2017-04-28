/*
 * ngasp, a computational solution for performing next generation analysis of 
 * sequence polymorphisms using NGS data.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
 * Centre for Research in Agricultural Genomics.
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
 *  \brief     CCalcConcatFiles.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 30, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcConcatFiles.h"

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"
#include "CCalcExec.h"

#include "../../data_manager/Data/CDataTextFile.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../util/CFile.h"

CCalcConcatFiles::CCalcConcatFiles()
: ICalculation(KeyString::CALC_CONCAT_FILES, // Calculation Name
KeyString::CALC_CONCAT_FILES_BRIEF_DESC, // Brief Description
KeyString::CALC_CONCAT_FILES_DESC, // Long Description
KeyString::NGASP_AUTHORS, // Authors
KeyString::MSTATSPOP_COPYRIGHT, // Copyright
KeyString::GENERIC_CITATIONS, // Citations
KeyString::UNDEFINED_STRING) { // See also
    BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(input_file_1, // Variable
            UNDEFINED_STRING, // Group
            CALC_CONCAT_FILES_FILE_1, // Short Name
            CALC_CONCAT_FILES_FILE_1_LONG, // Long Name
            CALC_CONCAT_FILES_FILE_1_DESC, // Description
            CALC_CONCAT_FILES_FILE_1_SAMP, // Example
            CALC_CONCAT_FILES_FILE_1_ONLY, // Use only if
            CALC_CONCAT_FILES_FILE_1_DEFV, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_mandatory) // Required

            SET_INPUT_INFO(input_file_2, // Variable
            UNDEFINED_STRING, // Group
            CALC_CONCAT_FILES_FILE_2, // Short Name
            CALC_CONCAT_FILES_FILE_2_LONG, // Long Name
            CALC_CONCAT_FILES_FILE_2_DESC, // Description
            CALC_CONCAT_FILES_FILE_2_SAMP, // Example
            CALC_CONCAT_FILES_FILE_2_ONLY, // Use only if
            CALC_CONCAT_FILES_FILE_2_DEFV, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_optional) // Required

            SET_INPUT_INFO(keep_intermediate_results, // Variable
            UNDEFINED_STRING, // Group
            CCALC_ALL_KEEP_INTERMEDIATE_RESULTS, // Short Name
            CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_LONG, // Long Name
            CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_DESC, // Description
            CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_SAMP, // Example
            CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_ONLY, // Use only if
            CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_DEFV, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_optional) // Required

            SET_OUTPUT_INFO(output_file, // Variable
            UNDEFINED_STRING, // Group
            CALC_CONCAT_FILES_OUTPUT, // Short Name
            CALC_CONCAT_FILES_OUTPUT_LONG, // Long Name
            CALC_CONCAT_FILES_OUTPUT_DESC, // Description
            CALC_CONCAT_FILES_OUTPUT_SAMP, // Example
            CALC_CONCAT_FILES_OUTPUT_ONLY, // Use only if
            CALC_CONCAT_FILES_OUTPUT_DEFV, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_mandatory) // Required
            END_CALCULATION_INTERFACE_DEFINITION
}

CCalcConcatFiles::~CCalcConcatFiles() {
}

void CCalcConcatFiles::Prepare(void) {
    DM_GET_INPUTS
        DM_INPUT(input_file_1)
        DM_INPUT(input_file_2)
        DM_INPUT(keep_intermediate_results)
    DM_GET_OUTPUTS
        DM_OUTPUT(output_file)
    DM_END

    /*
    Option 1:

            File1 + File2 ===> OutputFile

            If OutputFile name is "" then OutputFile is the concatenation of the File1 and File2 names.

    Option 2:

            OutputFile + File1 ===> OutputFile

            If OutputFile must have a name.
     */
          
    if ((input_file_1->value() != "") && (input_file_2->value() != "")) {
        // Option 1
        if (output_file->value() == "") {
            output_file->set_value(
                    CFile::GetPathFileNameWithoutExtension(input_file_1->value()) +
                    "_" +
                    CFile::GetFileNameWithoutExtension(input_file_2->value()) +
                    "." +
                    CFile::GetExtensionFromFileName(input_file_1->value()));
        }
        origin1 = input_file_1->value();
        origin2 = input_file_2->value();
        destination = output_file->value();
    } else {
        if ((input_file_1->value() != "") && (output_file->value() != "")) {
            // Option 2
            origin1 = output_file->value();
            origin2 = input_file_1->value();
            destination = output_file->value();
        } else {
            ERROR_MSG << "Concatenate options are: File1 + File2 => OutputFile or OutputFile + File1 => OutputFile"
                    END_MSG;
        }
    }

DEBUG_MSG << "input_file_1->value()  is " << input_file_1->value()  END_MSG;
DEBUG_MSG << "input_file_2->value()  is " << input_file_2->value()  END_MSG;
DEBUG_MSG << "output_file->value()  is " << output_file->value()  END_MSG;

  if (keep_intermediate_results->value()) {
        DM_ITERATION_NUMBER(iteration_number)
        DM_ITERATION_VALUE(iteration_value)
        destination = CFile::ConcatenateIterationToFilePathName(destination,
                                                                                                                                        iteration_number->value(),
                                                                                                                                        iteration_value->value());
    }
}

void CCalcConcatFiles::Calculate(bool dry_run) {
    if (dry_run == true) {
        return;
    }

    /// CREATE CALC AND DATAS FOR THE CALCULATION

    CCalcExec *calc_execute = NULL;
    DM_NEW_CALC(calc_execute)

    CDataStdString *the_command = NULL;
    DM_NEW_DATA(the_command)

    if (origin1 == destination) {
        the_command->set_value(STR(CONCATENATE_FILES_BINARY) + " " + origin2 + " >> " + destination);
    } else {
        if (origin2 == destination) {
            the_command->set_value(STR(CONCATENATE_FILES_BINARY) + " " + origin1 + " >> " + destination);
        }
        else {
            the_command->set_value(STR(CONCATENATE_FILES_BINARY) + " " + origin1 + " " + origin2 + " > " + destination);
        }
    }

    CDataStdString *the_working_directory = NULL;
    DM_NEW_DATA(the_working_directory)
    the_working_directory->set_value(STR(BINARY_PATH_INSIDE_DOCKER));

    CDataStdString *the_type = NULL;
    DM_NEW_DATA(the_type)
    the_type->set_value(STR(EXEC_TYPE_SYS));

    CDataInt *the_result = (CDataInt *) manager()->data_manager()->GetDataByName(ROOT_PARENT, STR(RESULT)); // This is a global variable. So, its parent is ROOT_PARENT.

    /// ==========================================================================
    /// EXECUTE EXTERNAL APPLICATION OR SYSTEM COMMAND
    /// ==========================================================================
    calc_execute->SetInput(the_command);
    calc_execute->SetInput(the_working_directory);
    calc_execute->SetInput(the_type);
    calc_execute->SetOutput(the_result);
    calc_execute->Prepare();
    calc_execute->Calculate(dry_run);
    calc_execute->Finalize();
    /// ==========================================================================

    /// REMOVE CALC AND "DATAS" CREATED ONLY FOR THIS CALCULATION

    DM_DEL_CALC(calc_execute)
    DM_DEL_DATA(the_command)
    DM_DEL_DATA(the_working_directory)
    DM_DEL_DATA(the_type)
}

void CCalcConcatFiles::Finalize(void) {
    DM_DEL_ALL_LOCAL_DATA
}

