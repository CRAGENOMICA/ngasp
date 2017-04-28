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
 *  \brief     CCalcBamChromosomes.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */
#include "CCalcBamChromosomes.h"

#include <cmath>
#include <string.h>

#include "../../language/CStringTable.h"
#include "../../util/CStringTools.h"

#include <export.h>

CCalcBamChromosomes::CCalcBamChromosomes()
    : ICalculation(KeyString::CALC_BAM_CHROMOSOMES,
                                 KeyString::CALC_BAM_CHROMOSOMES_BRIEF_DESC,
                                 KeyString::CALC_BAM_CHROMOSOMES_DESC,
                                 KeyString::NGASP_AUTHORS,
                                 KeyString::MSTATSPOP_COPYRIGHT,
                                 KeyString::GENERIC_CITATIONS,
                                 KeyString::UNDEFINED_STRING) {
    BEGIN_CALCULATION_INTERFACE_DEFINITION
        SET_INPUT_INFO(bam_file_, // Variable
                UNDEFINED_STRING, // Group
                UNDEFINED_STRING, // Short Name
                UNDEFINED_STRING, // Long Name
                UNDEFINED_STRING, // Description
                UNDEFINED_STRING, // Example
                UNDEFINED_STRING, // Use only if
                UNDEFINED_STRING, // Default value
                UNDEFINED_VALUE, // Min. Value
                UNDEFINED_VALUE, // Max. Value
                OPTTYPE_mandatory) // Required)

            SET_OUTPUT_INFO(chromosomes_, // Variable
                UNDEFINED_STRING, // Group
                UNDEFINED_STRING, // Short Name
                UNDEFINED_STRING, // Long Name
                UNDEFINED_STRING, // Description
                UNDEFINED_STRING, // Example
                UNDEFINED_STRING, // Use only if
                UNDEFINED_STRING, // Default value
                UNDEFINED_VALUE, // Min. Value
                UNDEFINED_VALUE, // Max. Value
                OPTTYPE_mandatory) // Required)
            END_CALCULATION_INTERFACE_DEFINITION
}

CCalcBamChromosomes::~CCalcBamChromosomes() {
}

void CCalcBamChromosomes::Prepare(void) {
    DM_GET_INPUTS
        DM_INPUT(bam_file_)
    DM_GET_OUTPUTS
        DM_OUTPUT(chromosomes_)
    DM_END
}

void CCalcBamChromosomes::Calculate(bool dry_run) {
    if (bam_file_->value() != "") {
        int bam_name_length = bam_file_->value().length() - 4;
        char *p_bam_file = new char[bam_name_length + 1]; // + 1 is the end NULL value
        memset(p_bam_file, '\x0', bam_name_length + 1);
        strncpy(p_bam_file, bam_file_->value().c_str(), bam_name_length);

        {
            char *argv[] = {
                "idxstats",
                p_bam_file,
                NULL
            };

            int argc = sizeof (argv) / sizeof (char*) - 1;

            char **names = (char **) malloc(1 * sizeof (char *));

            if (bam_idxstats_ngasp(argc, argv, names) != 0) {
                ERROR_MSG << "Samtoolslib : bam_idxstats_ngasp returns 0.  Input BAM file name is " << bam_file_->value() END_MSG;
            }

            chromosomes_->PushBack("a");
            chromosomes_->PushBack("b");
            chromosomes_->PushBack("c");
            
            free(names[0]);
            free(names);
        }

        delete []p_bam_file;
    } else {
        ERROR_MSG << "Input BAM file name is null..." END_MSG;
    }


    //  FILE *handle = fopen(bai_file_->value().c_str(), "r");
    //  
    //  if (handle != NULL) {
    //   
    //    // chromosomes_->ReserveMemory(3);
    //    fclose(handle);
    //  }  
}

void CCalcBamChromosomes::Finalize(void) {
    DM_DEL_ALL_LOCAL_DATA
}

