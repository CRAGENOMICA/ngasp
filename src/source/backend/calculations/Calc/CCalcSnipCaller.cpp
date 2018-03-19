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
 *  \brief     CCalcSnipCaller.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      April 29, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcSnipCaller.h"

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"
#include "CCalcExec.h"

#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataMpileup.h"
#include "../../data_manager/Data/CDataFasta.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../util/CFile.h"

CCalcSnipCaller::CCalcSnipCaller()
: ICalculation(KeyString::CALC_SNIPCALLER,
               KeyString::CALC_SNIPCALLER_BRIEF_DESC,
               KeyString::CALC_SNIPCALLER_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(input_file,                                           // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_SNP_CALLER_MPILEUP,                                     // Short Name
                   CALC_SNP_CALLER_MPILEUP_LONG,                                // Long Name
                   CALC_SNP_CALLER_MPILEUP_DESC,                                // Description
                   CALC_SNP_CALLER_MPILEUP_SAMP,                                // Example
                   CALC_SNP_CALLER_MPILEUP_ONLY,                                // Use only if
                   CALC_SNP_CALLER_MPILEUP_DEFV,                                // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
  
    SET_INPUT_INFO(baseq,                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_SNP_CALLER_BASEQ,                         // Short Name
                   CALC_SNP_CALLER_BASEQ_LONG,                    // Long Name
                   CALC_SNP_CALLER_BASEQ_DESC,                    // Description
                   CALC_SNP_CALLER_BASEQ_SAMP,                    // Example
                   CALC_SNP_CALLER_BASEQ_ONLY,                    // Use only if
                   CALC_SNP_CALLER_BASEQ_DEFV,                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(mindep,                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_SNP_CALLER_MINDEP,                         // Short Name
                   CALC_SNP_CALLER_MINDEP_LONG,                    // Long Name
                   CALC_SNP_CALLER_MINDEP_DESC,                    // Description
                   CALC_SNP_CALLER_MINDEP_SAMP,                    // Example
                   CALC_SNP_CALLER_MINDEP_ONLY,                    // Use only if
                   CALC_SNP_CALLER_MINDEP_DEFV,                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(maxdep,                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_SNP_CALLER_MAXDEP,                         // Short Name
                   CALC_SNP_CALLER_MAXDEP_LONG,                    // Long Name
                   CALC_SNP_CALLER_MAXDEP_DESC,                    // Description
                   CALC_SNP_CALLER_MAXDEP_SAMP,                    // Example
                   CALC_SNP_CALLER_MAXDEP_ONLY,                    // Use only if
                   CALC_SNP_CALLER_MAXDEP_DEFV,                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(mrd,                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_SNP_CALLER_MRD,                         // Short Name
                   CALC_SNP_CALLER_MRD_LONG,                    // Long Name
                   CALC_SNP_CALLER_MRD_DESC,                    // Description
                   CALC_SNP_CALLER_MRD_SAMP,                    // Example
                   CALC_SNP_CALLER_MRD_ONLY,                    // Use only if
                   CALC_SNP_CALLER_MRD_DEFV,                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required



    SET_INPUT_INFO(platform,                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_SNP_CALLER_PLATFORM,                         // Short Name
                   CALC_SNP_CALLER_PLATFORM_LONG,                    // Long Name
                   CALC_SNP_CALLER_PLATFORM_DESC,                    // Description
                   CALC_SNP_CALLER_PLATFORM_SAMP,                    // Example
                   CALC_SNP_CALLER_PLATFORM_ONLY,                    // Use only if
                   CALC_SNP_CALLER_PLATFORM_DEFV,                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(outgroup,                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_SNP_CALLER_OUTGROUP,                         // Short Name
                   CALC_SNP_CALLER_OUTGROUP_LONG,                    // Long Name
                   CALC_SNP_CALLER_OUTGROUP_DESC,                    // Description
                   CALC_SNP_CALLER_OUTGROUP_SAMP,                    // Example
                   CALC_SNP_CALLER_OUTGROUP_ONLY,                    // Use only if
                   CALC_SNP_CALLER_OUTGROUP_DEFV,                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

    SET_INPUT_INFO(names,                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_SNP_CALLER_NAMES,                         // Short Name
                   CALC_SNP_CALLER_NAMES_LONG,                    // Long Name
                   CALC_SNP_CALLER_NAMES_DESC,                    // Description
                   CALC_SNP_CALLER_NAMES_SAMP,                    // Example
                   CALC_SNP_CALLER_NAMES_ONLY,                    // Use only if
                   CALC_SNP_CALLER_NAMES_DEFV,                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required

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
  
    SET_OUTPUT_INFO(output_fasta,                                               // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_SNP_CALLER_FASTA,                                       // Short Name
                   CALC_SNP_CALLER_FASTA_LONG,                                  // Long Name
                   CALC_SNP_CALLER_FASTA_DESC,                                  // Description
                   CALC_SNP_CALLER_FASTA_SAMP,                                  // Example
                   CALC_SNP_CALLER_FASTA_ONLY,                                  // Use only if
                   CALC_SNP_CALLER_FASTA_DEFV,                                  // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcSnipCaller::~CCalcSnipCaller() {
}


void CCalcSnipCaller::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(input_file)
    DM_INPUT(baseq)
    DM_INPUT(mindep)
    DM_INPUT(maxdep)
    DM_INPUT(mrd)
    DM_INPUT(platform)
    DM_INPUT(outgroup)
    DM_INPUT(names)
    DM_INPUT(keep_intermediate_results)
  DM_GET_OUTPUTS
    DM_OUTPUT(output_fasta)
  DM_END
  
  if (input_file->value() != "") {
    if (output_fasta->value() == "") {
        output_fasta->set_value(CFile::GetPathFileNameWithoutExtension(input_file->value()) + ".fas");
    }  
  } else {
    ERROR_MSG << "Input file name missing..." END_MSG;
  }
  
  if (keep_intermediate_results->value()) {
    DM_ITERATION_NUMBER(iteration_number)
    DM_ITERATION_VALUE(iteration_value)
    output_fasta->set_value(CFile::ConcatenateIterationToFilePathName(output_fasta->value(),
                            iteration_number->value(),
                            iteration_value->value()));  
  }
}

void CCalcSnipCaller::Calculate(bool dry_run) {
  if (dry_run == true) {
    return;
  }

  /// CREATE CALC AND DATAS FOR THE CALCULATION
 
  CCalcExec *calc_execute = NULL;
  DM_NEW_CALC(calc_execute)
  
  CDataStdString *the_command = NULL;
  DM_NEW_DATA(the_command)
  

  std::string command = STR(SNP_CALLER_BINARY) +
                        " -i " + input_file->value() +
                        " -o " + output_fasta->value();






  if (!baseq->auto_created()) {
    command += " --baseq " + CStringTools::ToString(baseq->value());
  }

  if (!platform->auto_created()) {
    command += " --platform " + CStringTools::ToString(platform->value());
  }

  if (!outgroup->auto_created()) {
    command += " --outgroup " + outgroup->value();
  }

  if (!names->auto_created()) {
    command += " --names " + names->value();
  }

  std::string values;
  if ((!mrd->auto_created()) && (mindep->auto_created())) {
    values = "";
    for (int i = 0; i < mrd->Size(); i++) {
        if (i != 0) { values += ","; }
        values += CStringTools::ToString((*mrd)[i] / 2);
    }
  } else {
      if (!mindep->auto_created()) {
        values = CStringTools::ToString(mindep->value());
      }
  }
  if (values != "") {
    command += " --mindep " + values;
  }
  
  if ((!mrd->auto_created()) && (maxdep->auto_created())) {
    values = "";
    for (int i = 0; i < mrd->Size(); i++) {
        if (i != 0) { values += ","; }
        values += CStringTools::ToString((*mrd)[i] + (*mrd)[i]);
    }
  } else {
      if (!maxdep->auto_created()) {
        values = CStringTools::ToString(mindep->value());
      }
  }
  if (values != "") {
    command += " --maxdep " + values;
  }



  the_command->set_value(command);
    
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

void CCalcSnipCaller::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
