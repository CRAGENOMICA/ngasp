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
 *  \brief     CCalcSplitBAM.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      February 24, 2017
 *  \pre
 *  \bug
 *  \warning
 */
#include "CCalcSplitBAM.h"

#include <cmath>
#include <string.h>

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"

#include <export.h>

CCalcSplitBAM::CCalcSplitBAM()
: ICalculation(KeyString::CALC_SPLIT_BAM,
               KeyString::CALC_SPLIT_BAM_BRIEF_DESC,
               KeyString::CALC_SPLIT_BAM_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    
    SET_INPUT_INFO(bam_file_,                                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCSPLIT_BAM_INPUT,                                    // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CCALCSPLIT_BAM_INPUT_DESC,                    // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(chromosomes_,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCSPLIT_BAM_CHROMS,                             // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CCALCSPLIT_BAM_CHROMS_DESC,              // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)  
    SET_INPUT_INFO(exclude_,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCSPLIT_BAM_EXCLUDE,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CCALCSPLIT_BAM_EXCLUDE_DESC,             // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)      
    SET_OUTPUT_INFO(output_bams_,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCSPLIT_BAM_OUTPUT,                              // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CCALCSPLIT_BAM_OUTPUT_DESC,               // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)  
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcSplitBAM::~CCalcSplitBAM() {
}

void CCalcSplitBAM::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(bam_file_)
    DM_INPUT(chromosomes_)
    DM_INPUT(exclude_)
  DM_GET_OUTPUTS
    DM_OUTPUT(output_bams_)
  DM_END

}

void CCalcSplitBAM::Calculate(bool dry_run) {
    if (dry_run == true) {
        return;
    }

    std::string name;
    std::string output_file;
    char *p_bam_file = 0;
    char *p_chromosome_name = 0;
    char *p_output_file = 0;
    

    output_bams_->DeleteMemory();
    
    for (int i = 0; i < chromosomes_->Size(); i++) {
        name = chromosomes_->GetData()[i];
        
        if (exclude_->FindValue(name) == false) {
            output_file = CFile::GetPathFileNameWithoutExtension(bam_file_->value()) + "." + name + ".bam";

            output_bams_->PushBack(output_file);

            if (CFile::Exists(output_file) == false) {
                p_bam_file = new char[bam_file_->value().length() + 1];
                memset(p_bam_file, '\x0', bam_file_->value().length() + 1);
                strcpy(p_bam_file, bam_file_->value().c_str());        

                p_chromosome_name = new char[name.length() + 1];
                memset(p_chromosome_name, '\x0', name.length() + 1);
                strcpy(p_chromosome_name, name.c_str());        

                p_output_file = new char[output_file.length() + 1];
                memset(p_output_file, '\x0', output_file.length() + 1);
                strcpy(p_output_file, output_file.c_str());        
                
                {
                    char *argv[] = {"samtools", "view",
                        "-b",
                        p_bam_file,
                        p_chromosome_name,
                        "-o",
                        p_output_file,
                        NULL};
                    int argc = sizeof (argv) / sizeof (char*) - 1;

                    samtools_main(argc, argv);
                }
            
                delete []p_bam_file;
                delete []p_chromosome_name; 
                delete []p_output_file;
            }
        }
    }   
}

void CCalcSplitBAM::Finalize(void) {
    DM_DEL_ALL_LOCAL_DATA
}

