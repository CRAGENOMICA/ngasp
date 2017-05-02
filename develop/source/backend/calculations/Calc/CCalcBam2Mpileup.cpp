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
 *  \brief     CCalcBam2Mpileup.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      April 25, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcBam2Mpileup.h"

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"

#include <bam_plcmd.h>
#include <export.h>

#include <iostream>

#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../util/CFile.h"

CCalcBam2Mpileup::CCalcBam2Mpileup()
: ICalculation(KeyString::CALC_BAM2MPILEUP,                                     // Calculation Name
               KeyString::CALC_BAM2MPILEUP_BRIEF_DESC,                          // Brief Description
               KeyString::CALC_BAM2MPILEUP_DESC,                                // Long Description
               KeyString::NGASP_AUTHORS,                                        // Authors
               KeyString::MSTATSPOP_COPYRIGHT,                                  // Copyright
               KeyString::GENERIC_CITATIONS,                                    // Citations
               KeyString::UNDEFINED_STRING) {                                   // See also
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(bam_file,                                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCBAM2MPILEUP_BAM_FILES,                                  // Short Name
                   CCALCBAM2MPILEUP_BAM_FILES_LONG,                             // Long Name
                   CCALCBAM2MPILEUP_BAM_FILES_DESC,                             // Description
                   CCALCBAM2MPILEUP_BAM_FILES_SAMP,                             // Example
                   CCALCBAM2MPILEUP_BAM_FILES_ONLY,                             // Use only if
                   CCALCBAM2MPILEUP_BAM_FILES_DEFV,                             // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
          
    SET_INPUT_INFO(fasta_ref,                                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCBAM2MPILEUP_FASTA_REF,                                  // Short Name
                   CCALCBAM2MPILEUP_FASTA_REF_LONG,                             // Long Name
                   CCALCBAM2MPILEUP_FASTA_REF_DESC,                             // Description
                   CCALCBAM2MPILEUP_FASTA_REF_SAMP,                             // Example
                   CCALCBAM2MPILEUP_FASTA_REF_ONLY,                             // Use only if
                   CCALCBAM2MPILEUP_FASTA_REF_DEFV,                             // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required

    SET_INPUT_INFO(filter,                                                     // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCBAM2MPILEUP_FILTER,                                     // Short Name
                   CCALCBAM2MPILEUP_FILTER_LONG,                                // Long Name
                   CCALCBAM2MPILEUP_FILTER_DESC,                                // Description
                   CCALCBAM2MPILEUP_FILTER_SAMP,                                // Example
                   CCALCBAM2MPILEUP_FILTER_ONLY,                                // Use only if
                   CCALCBAM2MPILEUP_FILTER_DEFV,                                // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                           // Required  
  
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

  
    SET_OUTPUT_INFO(mpileup_file,                                               // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCBAM2MPILEUP_MPILEUP_FILE,                               // Short Name
                   CCALCBAM2MPILEUP_MPILEUP_FILE_LONG,                          // Long Name
                   CCALCBAM2MPILEUP_MPILEUP_FILE_DESC,                          // Description
                   CCALCBAM2MPILEUP_MPILEUP_FILE_SAMP,                          // Example
                   CCALCBAM2MPILEUP_MPILEUP_FILE_ONLY,                          // Use only if
                   CCALCBAM2MPILEUP_MPILEUP_FILE_DEFV,                          // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcBam2Mpileup::~CCalcBam2Mpileup() {
}

void CCalcBam2Mpileup::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(bam_file)
    DM_INPUT(fasta_ref)
    DM_INPUT(filter)
    DM_INPUT(keep_intermediate_results)
  DM_GET_OUTPUTS
    DM_OUTPUT(mpileup_file)
  DM_END

                   
//  if (bam_files->Size() != 0) {
//    if (mpileup_file->value() == "") {
//      mpileup_file->set_value(CFile::GetPathFileNameWithoutExtension((*bam_files)[0]) + ".mpileup");
//    }  
//  } else {
//    ERROR_MSG << "Input file name missing..." END_MSG;
//  }  

  if (filter->value() != "") {
    WARNING_MSG << "Filtering by chromosome name is not implemented yet... "
              END_MSG;
  }
          
          
  if (mpileup_file->value() == "") {
    mpileup_file->set_value(CFile::GetPathFileNameWithoutExtension(bam_file->value()) + ".mpileup");
  }  
  
  if (keep_intermediate_results->value()) {
    DM_ITERATION_NUMBER(iteration_number)
    DM_ITERATION_VALUE(iteration_value)
    mpileup_file->set_value(CFile::ConcatenateIterationToFilePathName(mpileup_file->value(),
                            iteration_number->value(),
                            iteration_value->value()));
  }
}

void CCalcBam2Mpileup::Calculate(bool dry_run) {
    if (dry_run == true) {
        return;
    }

    if (CFile::Exists(bam_file->value()) == false) {
        ERROR_MSG << "Input file does not exist: "
                << bam_file->value()
                END_MSG;
        return;
    }

    if (CFile::Exists(fasta_ref->value()) == false) {
        ERROR_MSG << "Input fasta reference file does not exist: "
                << fasta_ref->value()
                END_MSG;
        return;
    }

   if (CFile::Exists(mpileup_file->value()) == false) {
    
        char *p_bam_file = new char[bam_file->value().length() + 1];
        strcpy(p_bam_file, bam_file->value().c_str());

        char *p_fasta_ref_file= new char[fasta_ref->value().length() + 1];
        strcpy(p_fasta_ref_file, fasta_ref->value().c_str());

        char *p_mpileup_file = new char[mpileup_file->value().length() + 1];
        strcpy(p_mpileup_file, mpileup_file->value().c_str());


        char *argv[] = {"samtools", "mpileup",
            p_bam_file,
            "-f",
            p_fasta_ref_file,
            "-o",
            p_mpileup_file,
            NULL};
        int argc = sizeof (argv) / sizeof (char*) - 1;

        samtools_main(argc, argv);

        delete []p_bam_file;
        delete []p_fasta_ref_file;
        delete []p_mpileup_file;
   }
   else {
       WARNING_MSG << "The mpileup file '" << mpileup_file->value() << "' already exists. Using the existing one..."
               END_MSG;
   }
}

  // this code works but it needs a FAI file with faidx
  /*
    
  int num_files = 1; // bam_files->Size();
 
  char **file_names = NULL;
  
  file_names = new char*[num_files];
   
//  for (std::size_t i = 0; i < bam_files->Size(); i++) {
//    if (CFile::Exists((*bam_files)[i]) == false) {
//      ERROR_MSG << "Input file does not exist: "
//                << (*bam_files)[i]
//                END_MSG;
//      return;
//    }
//    
//    file_names[i] = new char[(*bam_files)[i].length()+1];
//    strcpy(file_names[i], (*bam_files)[i].c_str());   
//  }
   
    file_names[0] = new char[bam_file->value().length()+1];
    strcpy(file_names[0], bam_file->value().c_str());   
    
  const char *fai = fasta_ref->value().c_str();
  
  mpileup_file->mplp_.fai = fai_load(fai);
  if (mpileup_file->mplp_.fai != NULL) {
    
    mpileup_file->mplp_.fai_fname = new char[fasta_ref->value().length() + 1];
    strcpy(mpileup_file->mplp_.fai_fname, fasta_ref->value().c_str());
    
    mpileup_file->mplp_.output_fname = new char[mpileup_file->value().length() + 1];
    strcpy(mpileup_file->mplp_.output_fname, mpileup_file->value().c_str());
    
    
    mpileup(&(mpileup_file->mplp_), num_files, file_names);
    
    delete []mpileup_file->mplp_.fai_fname;
    delete []mpileup_file->mplp_.output_fname;
    
  } else {
      ERROR_MSG << "Required FAI file for converting BAM file into Mpileup file..."
              END_MSG;
  }
  

  for (std::size_t i = 0; i < num_files; i++) {
    delete []file_names[i];
  }
  
  delete []file_names;
   */

void CCalcBam2Mpileup::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
