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
 *  \brief     CCalcnpstat.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Semptember 14, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcnpstat.h"

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"
#include "CCalcExec.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataFasta.h"
#include "../../data_manager/Data/CDataGFF.h"
#include "../../data_manager/Data/CDataSNP.h"

CCalcnpstat::CCalcnpstat()
: ICalculation(KeyString::CALC_NPSTAT,
               KeyString::CALC_NPSTAT_BRIEF_DESC,
               KeyString::CALC_NPSTAT_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
  
  SET_INPUT_INFO(pileup_file_,                                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_NPSTAT_MPILEUP,                                      // Short Name
                   CALC_NPSTAT_MPILEUP_LONG,                                 // Long Name
                   CALC_NPSTAT_MPILEUP_DESC,                                 // Description
                   CALC_NPSTAT_MPILEUP_SAMP,                                 // Example
                   CALC_NPSTAT_MPILEUP_ONLY,                                 // Use only if
                   CALC_NPSTAT_MPILEUP_DEFV,                                 // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                            // Required)
  
  SET_INPUT_INFO(samplesize_,                                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_NPSTAT_SAMPLESIZE,                                      // Short Name
                   CALC_NPSTAT_SAMPLESIZE_LONG,                                 // Long Name
                   CALC_NPSTAT_SAMPLESIZE_DESC,                                 // Description
                   CALC_NPSTAT_SAMPLESIZE_SAMP,                                 // Example
                   CALC_NPSTAT_SAMPLESIZE_ONLY,                                 // Use only if
                   CALC_NPSTAT_SAMPLESIZE_DEFV,                                 // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)
  SET_INPUT_INFO(windowlength_,                                                 // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_NPSTAT_WINDOWLEN,                                       // Short Name
                   CALC_NPSTAT_WINDOWLEN_LONG,                                  // Long Name
                   CALC_NPSTAT_WINDOWLEN_DESC,                                  // Description
                   CALC_NPSTAT_WINDOWLEN_SAMP,                                  // Example
                   CALC_NPSTAT_WINDOWLEN_ONLY,                                  // Use only if
                   CALC_NPSTAT_WINDOWLEN_DEFV,                                  // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)
  SET_INPUT_INFO(mincov_,                                                       // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_NPSTAT_MINCOV,                                          // Short Name
                   CALC_NPSTAT_MINCOV_LONG,                                     // Long Name
                   CALC_NPSTAT_MINCOV_DESC,                                     // Description
                   CALC_NPSTAT_MINCOV_SAMP,                                     // Example
                   CALC_NPSTAT_MINCOV_ONLY,                                     // Use only if
                   CALC_NPSTAT_MINCOV_DEFV,                                     // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)
  SET_INPUT_INFO(maxcov_,                                                       // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_NPSTAT_MAXCOV,                                          // Short Name
                   CALC_NPSTAT_MAXCOV_LONG,                                     // Long Name
                   CALC_NPSTAT_MAXCOV_DESC,                                     // Description
                   CALC_NPSTAT_MAXCOV_SAMP,                                     // Example
                   CALC_NPSTAT_MAXCOV_ONLY,                                     // Use only if
                   CALC_NPSTAT_MAXCOV_DEFV,                                     // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)
  SET_INPUT_INFO(minqual_,                                                      // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_NPSTAT_MINQUAL,                                         // Short Name
                   CALC_NPSTAT_MINQUAL_LONG,                                    // Long Name
                   CALC_NPSTAT_MINQUAL_DESC,                                    // Description
                   CALC_NPSTAT_MINQUAL_SAMP,                                    // Example
                   CALC_NPSTAT_MINQUAL_ONLY,                                    // Use only if
                   CALC_NPSTAT_MINQUAL_DEFV,                                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)
  SET_INPUT_INFO(nolowfreq_,                                                    // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_NPSTAT_NOLOWFREQ,                                       // Short Name
                   CALC_NPSTAT_NOLOWFREQ_LONG,                                  // Long Name
                   CALC_NPSTAT_NOLOWFREQ_DESC,                                  // Description
                   CALC_NPSTAT_NOLOWFREQ_SAMP,                                  // Example
                   CALC_NPSTAT_NOLOWFREQ_ONLY,                                  // Use only if
                   CALC_NPSTAT_NOLOWFREQ_DEFV,                                  // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)
  SET_INPUT_INFO(outgroup_,                                                     // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_NPSTAT_OUTGROUP,                                        // Short Name
                   CALC_NPSTAT_OUTGROUP_LONG,                                   // Long Name
                   CALC_NPSTAT_OUTGROUP_DESC,                                   // Description
                   CALC_NPSTAT_OUTGROUP_SAMP,                                   // Example
                   CALC_NPSTAT_OUTGROUP_ONLY,                                   // Use only if
                   CALC_NPSTAT_OUTGROUP_DEFV,                                   // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)
  SET_INPUT_INFO(annot_,                                                        // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_NPSTAT_ANNOT,                                           // Short Name
                   CALC_NPSTAT_ANNOT_LONG,                                      // Long Name
                   CALC_NPSTAT_ANNOT_DESC,                                      // Description
                   CALC_NPSTAT_ANNOT_SAMP,                                      // Example
                   CALC_NPSTAT_ANNOT_ONLY,                                      // Use only if
                   CALC_NPSTAT_ANNOT_DEFV,                                      // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)
  SET_INPUT_INFO(snpfile_,                                                      // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_NPSTAT_SNPFILE,                                         // Short Name
                   CALC_NPSTAT_SNPFILE_LONG,                                    // Long Name
                   CALC_NPSTAT_SNPFILE_DESC,                                    // Description
                   CALC_NPSTAT_SNPFILE_SAMP,                                    // Example
                   CALC_NPSTAT_SNPFILE_ONLY,                                    // Use only if
                   CALC_NPSTAT_SNPFILE_DEFV,                                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)
  SET_OUTPUT_INFO(output_,                                                      // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_NPSTAT_OUTFILE,                                         // Short Name
                   CALC_NPSTAT_OUTFILE_LONG,                                    // Long Name
                   CALC_NPSTAT_OUTFILE_DESC,                                    // Description
                   CALC_NPSTAT_OUTFILE_SAMP,                                    // Example
                   CALC_NPSTAT_OUTFILE_ONLY,                                    // Use only if
                   CALC_NPSTAT_OUTFILE_DEFV,                                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
 
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcnpstat::~CCalcnpstat() {
}

void CCalcnpstat::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(pileup_file_)
    DM_INPUT(samplesize_)
    DM_INPUT(windowlength_)
    DM_INPUT(mincov_)
    DM_INPUT(maxcov_)
    DM_INPUT(minqual_)
    DM_INPUT(nolowfreq_)
    DM_INPUT(outgroup_)
    DM_INPUT(annot_)
    DM_INPUT(snpfile_)
  DM_GET_OUTPUTS
    DM_OUTPUT(output_)
  DM_END
  

  if (mincov_->value() == 0) {
    mincov_->set_value(4);
  }
  if (maxcov_->value() == 0) {
    maxcov_->set_value(100);
  }
  if (minqual_->value() == 0) {
    minqual_->set_value(10);
  }
}

void CCalcnpstat::Calculate(bool dry_run) {
  if (dry_run == true) {
    return;
  }

  /// CREATE CALC AND DATAS FOR THE CALCULATION
 
  CCalcExec *calc_execute = NULL;
  DM_NEW_CALC(calc_execute)
  
  CDataStdString *the_command = NULL;
  DM_NEW_DATA(the_command)

  std::string command = STR(NPSTAT_BINARY) + " ";
  
  if (samplesize_->value() != 0) {
    command += "-n ";
    command += samplesize_->value();
    command += " ";
  }
  if (windowlength_->value() != 0) {
    command += "-l ";
    command += windowlength_->value();
    command += " ";
  }
  if (mincov_->value() != 0) {
    command += "-mincov ";
    command += mincov_->value();
    command += " ";
  }
  if (maxcov_->value() != 0) {
    command += "-maxcov ";
    command += maxcov_->value();
    command += " ";
  }
  if (minqual_->value() != 0) {
    command += "-minqual ";
    command += minqual_->value();
    command += " ";
  }
  if (nolowfreq_->value() != 0) {
    command += "-nolowfreq ";
    command += nolowfreq_->value();
    command += " ";
  }
  if (outgroup_->value() != "") {
    command += "-outgroup ";
    command += outgroup_->value();
    command += " ";
  }
  if (annot_->value() != "") {
    command += "-annot ";
    command += annot_->value();
    command += " ";
  }
  if (snpfile_->value() != "") {
    command += "-snpfile ";
    command += snpfile_->value();
    command += " ";
  }
  
  command += pileup_file_->value();
  command += " > ";
  command += output_->value();
    
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

void CCalcnpstat::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
