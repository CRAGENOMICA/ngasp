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
 *  \brief     CCalcVCFToGFasta.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Semptember 14, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcVCFToGFasta.h"

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"
#include "CCalcExec.h"

#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataMpileup.h"
#include "../../data_manager/Data/CDataFasta.h"


CCalcVCFToGFasta::CCalcVCFToGFasta()
: ICalculation(KeyString::CALC_VCF2GFASTA,
               KeyString::CALC_VCF2GFASTA_BRIEF_DESC,
               KeyString::CALC_VCF2GFASTA_DESC,
               KeyString::GVCF2TFASTA_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(vcf_,                                                        // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_VCF2GFASTA_VCF,                                         // Short Name
                   CALC_VCF2GFASTA_VCF_LONG,                                    // Long Name
                   CALC_VCF2GFASTA_VCF_DESC,                                    // Description
                   CALC_VCF2GFASTA_VCF_SAMP,                                    // Example
                   CALC_VCF2GFASTA_VCF_ONLY,                                    // Use only if
                   CALC_VCF2GFASTA_VCF_DEFV,                                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(fasta_ref_,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_VCF2GFASTA_FASTAREF,                                    // Short Name
                   CALC_VCF2GFASTA_FASTAREF_LONG,                               // Long Name
                   CALC_VCF2GFASTA_FASTAREF_DESC,                               // Description
                   CALC_VCF2GFASTA_FASTAREF_SAMP,                               // Example
                   CALC_VCF2GFASTA_FASTAREF_ONLY,                               // Use only if
                   CALC_VCF2GFASTA_FASTAREF_DEFV,                               // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(num_samples_,                                                // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_VCF2GFASTA_NUMSAMPS,                                    // Short Name
                   CALC_VCF2GFASTA_NUMSAMPS_LONG,                               // Long Name
                   CALC_VCF2GFASTA_NUMSAMPS_DESC,                               // Description
                   CALC_VCF2GFASTA_NUMSAMPS_SAMP,                               // Example
                   CALC_VCF2GFASTA_NUMSAMPS_ONLY,                               // Use only if
                   CALC_VCF2GFASTA_NUMSAMPS_DEFV,                               // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)  
    SET_OUTPUT_INFO(gfasta_,                                                    // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_VCF2GFASTA_GFASTA,                                      // Short Name
                   CALC_VCF2GFASTA_GFASTA_LONG,                                 // Long Name
                   CALC_VCF2GFASTA_GFASTA_DESC,                                 // Description
                   CALC_VCF2GFASTA_GFASTA_SAMP,                                 // Example
                   CALC_VCF2GFASTA_GFASTA_ONLY,                                 // Use only if
                   CALC_VCF2GFASTA_GFASTA_DEFV,                                 // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcVCFToGFasta::~CCalcVCFToGFasta() {
}

void CCalcVCFToGFasta::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(vcf_)
    DM_INPUT(fasta_ref_)
    DM_INPUT(num_samples_)
  DM_GET_OUTPUTS
    DM_OUTPUT(gfasta_)
  DM_END
}

void CCalcVCFToGFasta::Calculate(bool dry_run) {
  if (dry_run == true) {
    return;
  }

  /// CREATE CALC AND DATAS FOR THE CALCULATION
 
  CCalcExec *calc_execute = NULL;
  DM_NEW_CALC(calc_execute)
  
  CDataStdString *the_command = NULL;
  DM_NEW_DATA(the_command)

    
  the_command->set_value(STR(SNP_CALLER_BINARY) + " " + vcf_->value() + " " + fasta_ref_->value() + " " + CStringTools::ToString(num_samples_->value()) + " " + gfasta_->value());
    
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

void CCalcVCFToGFasta::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
