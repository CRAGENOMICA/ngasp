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
 *  \brief     CCalcCollectDataColumns.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 30, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcCollectDataColumns.h"

#include "../../language/CStringTable.h"

#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataTextFile.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../util/CFile.h"
#include "CCalcExec.h"

CCalcCollectDataColumns::CCalcCollectDataColumns()
: ICalculation(KeyString::CALC_COLLECT_DATA_COLUMNS,                            // Calculation Name
               KeyString::CALC_COLLECT_DATA_COLUMNS_BRIEF_DESC,                 // Brief Description
               KeyString::CALC_COLLECT_DATA_COLUMNS_DESC,                       // Long Description
               KeyString::NGASP_AUTHORS,                                        // Authors
               KeyString::MSTATSPOP_COPYRIGHT,                                  // Copyright
               KeyString::GENERIC_CITATIONS,                                    // Citations
               KeyString::UNDEFINED_STRING) {                                   // See also
  BEGIN_CALCULATION_INTERFACE_DEFINITION
         
    SET_INPUT_INFO(required_columns,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_COLLECT_DATA_COLUMNS_REQ_COLUMNS_FILE,                  // Short Name
                   CALC_COLLECT_DATA_COLUMNS_REQ_COLUMNS_FILE_LONG,             // Long Name
                   CALC_COLLECT_DATA_COLUMNS_REQ_COLUMNS_FILE_DESC,             // Description
                   CALC_COLLECT_DATA_COLUMNS_REQ_COLUMNS_FILE_SAMP,             // Example
                   CALC_COLLECT_DATA_COLUMNS_REQ_COLUMNS_FILE_ONLY,             // Use only if
                   CALC_COLLECT_DATA_COLUMNS_REQ_COLUMNS_FILE_DEFV,             // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  
    SET_INPUT_INFO(statistics_file,                                             // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_COLLECT_DATA_COLUMNS_STATS_FILE,                        // Short Name
                   CALC_COLLECT_DATA_COLUMNS_STATS_FILE_LONG,                   // Long Name
                   CALC_COLLECT_DATA_COLUMNS_STATS_FILE_DESC,                   // Description
                   CALC_COLLECT_DATA_COLUMNS_STATS_FILE_SAMP,                   // Example
                   CALC_COLLECT_DATA_COLUMNS_STATS_FILE_ONLY,                   // Use only if
                   CALC_COLLECT_DATA_COLUMNS_STATS_FILE_DEFV,                   // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
          
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
  
    SET_OUTPUT_INFO(filtered_statistics_file,                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_COLLECT_DATA_COLUMNS_FIL_STATS_FILE,                    // Short Name
                   CALC_COLLECT_DATA_COLUMNS_FIL_STATS_FILE_LONG,               // Long Name
                   CALC_COLLECT_DATA_COLUMNS_FIL_STATS_FILE_DESC,               // Description
                   CALC_COLLECT_DATA_COLUMNS_FIL_STATS_FILE_SAMP,               // Example
                   CALC_COLLECT_DATA_COLUMNS_FIL_STATS_FILE_ONLY,               // Use only if
                   CALC_COLLECT_DATA_COLUMNS_FIL_STATS_FILE_DEFV,               // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcCollectDataColumns::~CCalcCollectDataColumns() {
}

void CCalcCollectDataColumns::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(required_columns)
    DM_INPUT(statistics_file)
    DM_INPUT(keep_intermediate_results)
  DM_GET_OUTPUTS
    DM_OUTPUT(filtered_statistics_file)
  DM_END
  
  if (filtered_statistics_file->value() == "") {
      filtered_statistics_file->set_value(statistics_file->value() + ".filtered");
  }
          
  if (keep_intermediate_results->value()) {
    DM_ITERATION_NUMBER(iteration_number)
    DM_ITERATION_VALUE(iteration_value)
    filtered_statistics_file->set_value(CFile::ConcatenateIterationToFilePathName(filtered_statistics_file->value(),
                                        iteration_number->value(),
                                        iteration_value->value()));  
  }
}

void CCalcCollectDataColumns::Calculate(bool dry_run) {
  if (dry_run) {
    return;
  }
  /// CREATE CALC AND DATAS FOR THE CALCULATION
 
  CCalcExec *calc_execute = NULL;
  DM_NEW_CALC(calc_execute)
  
  CDataStdString *the_command = NULL;
  DM_NEW_DATA(the_command)
  the_command->set_value(STR(COLLECT_DATA_COLUMNS_BINARY) + " -in " + statistics_file->value() + " -fc " + required_columns->value() + " > " + filtered_statistics_file->value());
    
  CDataStdString *the_working_directory = NULL;
  DM_NEW_DATA(the_working_directory)
  the_working_directory->set_value(STR(BINARY_PATH_INSIDE_DOCKER));
    
  CDataStdString *the_type = NULL;
  DM_NEW_DATA(the_type)
  the_type->set_value(STR(EXEC_TYPE_SYS));
  
  CDataInt *the_result = (CDataInt *)manager()->data_manager()->GetDataByName(ROOT_PARENT, STR(RESULT));  // This is a global variable. So, its parent is ROOT_PARENT.
  
    
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

void CCalcCollectDataColumns::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

