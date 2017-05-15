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
 *  \brief     CCalcGetChromosomes.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      November 18, 2016
 *  \pre
 *  \bug
 *  \warning
 */
#include "CCalcGetChromosomes.h"

#include <cmath>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>


#include "../../language/CStringTable.h"
#include "../../util/CStringTools.h"
#include "../../util/CFile.h"


#include <export.h>

CCalcGetChromosomes::CCalcGetChromosomes()
    : ICalculation(KeyString::CALC_GET_CHROM,
    KeyString::CALC_GET_CHROM_BRIEF_DESC,
    KeyString::CALC_GET_CHROM_DESC,
    KeyString::NGASP_AUTHORS,
    KeyString::MSTATSPOP_COPYRIGHT,
    KeyString::GENERIC_CITATIONS,
    KeyString::UNDEFINED_STRING) {

    BEGIN_CALCULATION_INTERFACE_DEFINITION
        SET_INPUT_INFO(input_bam_file_, // Variable
            UNDEFINED_STRING, // Group
            CCALCGET_CHROM_INPUT_BAM, // Short Name
            UNDEFINED_STRING, // Long Name
            CCALCGET_CHROM_INPUT_BAM_DESC, // Description
            UNDEFINED_STRING, // Example
            UNDEFINED_STRING, // Use only if
            UNDEFINED_STRING, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_optional) // Required)
        SET_OUTPUT_INFO(chrom_names_, // Variable
            UNDEFINED_STRING, // Group
            CCALCGET_CHROM_CRHOM_NAMES, // Short Name
            UNDEFINED_STRING, // Long Name
            CCALCGET_CHROM_CRHOM_NAMES_DESC, // Description
            UNDEFINED_STRING, // GetChromosomes
            UNDEFINED_STRING, // Use only if
            UNDEFINED_STRING, // Default value
            UNDEFINED_VALUE, // Min. Value
            UNDEFINED_VALUE, // Max. Value
            OPTTYPE_optional) // Required
    END_CALCULATION_INTERFACE_DEFINITION
}

CCalcGetChromosomes::~CCalcGetChromosomes() {
}

void CCalcGetChromosomes::Prepare(void) {
    DM_GET_INPUTS
    DM_INPUT(input_bam_file_)
    DM_GET_OUTPUTS
    DM_OUTPUT(chrom_names_)
    DM_END
}

/**
 * 
 */
void CCalcGetChromosomes::Calculate(bool dry_run) {
    if (dry_run == true) {
        return;
    }
    
    std::string bai_file = CFile::GetPathFileNameWithoutExtension(input_bam_file_->value()) + ".bai" ;
    if (CFile::Exists(bai_file) == true) {
        GetNamesFromBAI(input_bam_file_->value());
    } else {
        GetNamesFromBAM(input_bam_file_->value());
    }
}

void CCalcGetChromosomes::GetNamesFromBAM(std::string input_file_name) {
    std::string names_file = input_file_name + ".names";
    std::string names = "";
    std::string tmp_file = input_file_name + ".tmp";

    if (CFile::Exists(names_file) == false) {
        char *p_bam_file = new char[input_file_name.length() + 1];
        strcpy(p_bam_file, input_file_name.c_str());

        char *p_tmp_file = new char[tmp_file.length() + 1];
        strcpy(p_tmp_file, tmp_file.c_str());

        {
            char *argv[] = {"view",
                p_bam_file,
                "-o",
                p_tmp_file,
                NULL};
            int argc = sizeof (argv) / sizeof (char*) - 1;

            main_samview(argc, argv);


            std::ifstream infile(tmp_file);

            std::string line;
            std::string chrom_name;
            int i = 0;
            while (std::getline(infile, line)) {
                std::vector<std::string> elems = CStringTools::SplitStrings(line, '\t');
                chrom_name = elems[2];

                if (chrom_names_->UniquePushBack(chrom_name) == true) {
                    if (i != 0) {
                        names += ",";
                    }
                    names += chrom_name;
                    i++;
                }
            }

            CFile::ReplaceContentBy(names_file, names);

            remove(tmp_file.c_str());
        }

        delete []p_bam_file;
        delete []p_tmp_file;
        
    } else {
        if (CFile::ReadAll(names_file, names) == true) {
            chrom_names_->set_data_string(names);
        }
    }
}

void CCalcGetChromosomes::GetNamesFromBAI(std::string input_file_name) {
    std::string names_file = CFile::GetPathFileNameWithoutExtension(input_file_name) + ".names";
    std::string names = "";

    if (CFile::Exists(names_file) == false) {
        char *p_bam_file = new char[input_file_name.length() + 1];
        strcpy(p_bam_file, input_file_name.c_str());

        char *argv[] = {"idxstats",
            p_bam_file,
            NULL};
        int argc = sizeof (argv) / sizeof (char*) - 1;
        char **the_names = (char **) malloc(1 * sizeof (char *));

        bam_idxstats_ngasp(argc, argv, the_names);
        
        names = *the_names;
        
        if (names != "") {
            CStringTools::Replace(names, "\n", ",");
            if (names == ",") {
                names = "";
            } else {
                if (names.at(names.length()-1) == ',') {
                    names = names.substr(0, names.length()-1); // Remove the last coma
                }
            }
        }
        
        CFile::ReplaceContentBy(names_file, names);
        
        free(the_names[0]);
        free(the_names);
        delete []p_bam_file;
        
    } else {
        if (CFile::ReadAll(names_file, names) == true) {
            chrom_names_->set_data_string(names);
        }
    }
}

void CCalcGetChromosomes::Finalize(void) {
    DM_DEL_ALL_LOCAL_DATA
}
