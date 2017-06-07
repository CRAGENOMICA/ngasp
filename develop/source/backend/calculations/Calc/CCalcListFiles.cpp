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
 *  \brief     CCalcListFiles.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      February 15, 2017
 *  \pre
 *  \bug
 *  \warning
 */
#include "CCalcListFiles.h"

#include "../../language/CStringTable.h"
#include "../../util/CStringTools.h"

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
#include "boost/regex.hpp"

namespace fs = boost::filesystem;

CCalcListFiles::CCalcListFiles()
: ICalculation(KeyString::CALC_LIST_FILES,
KeyString::CALC_LIST_FILES_BRIEF_DESC,
KeyString::CALC_LIST_FILES_DESC,
KeyString::NGASP_AUTHORS,
KeyString::MSTATSPOP_COPYRIGHT,
KeyString::GENERIC_CITATIONS,
KeyString::UNDEFINED_STRING) {
    
BEGIN_CALCULATION_INTERFACE_DEFINITION
  SET_INPUT_INFO(path_, // Variable
    UNDEFINED_STRING, // Group
    CCALCLIST_FILES_PATH, // Short Name
    UNDEFINED_STRING, // Long Name
    CCALCLIST_FILES_PATH_DESC, // Description
    UNDEFINED_STRING, // ListFiles
    UNDEFINED_STRING, // Use only if
    UNDEFINED_STRING, // Default value
    UNDEFINED_VALUE, // Min. Value
    UNDEFINED_VALUE, // Max. Value
    OPTTYPE_optional) // Required
  SET_INPUT_INFO(include_, // Variable
    UNDEFINED_STRING, // Group
    CCALCLIST_FILES_INCLUDE, // Short Name
    UNDEFINED_STRING, // Long Name
    CCALCLIST_FILES_INCLUDE_DESC, // Description
    UNDEFINED_STRING, // ListFiles
    UNDEFINED_STRING, // Use only if
    UNDEFINED_STRING, // Default value
    UNDEFINED_VALUE, // Min. Value
    UNDEFINED_VALUE, // Max. Value
    OPTTYPE_mandatory) // Required
  SET_INPUT_INFO(exclude_, // Variable
    UNDEFINED_STRING, // Group
    CCALCLIST_FILES_EXCLUDE, // Short Name
    UNDEFINED_STRING, // Long Name
    CCALCLIST_FILES_EXCLUDE_DESC, // Description
    UNDEFINED_STRING, // ListFiles
    UNDEFINED_STRING, // Use only if
    UNDEFINED_STRING, // Default value
    UNDEFINED_VALUE, // Min. Value
    UNDEFINED_VALUE, // Max. Value
    OPTTYPE_optional) // Required

  SET_OUTPUT_INFO(files_, // Variable
    UNDEFINED_STRING, // Group
    CCALCLIST_FILES_FILES, // Short Name
    UNDEFINED_STRING, // Long Name
    CCALCLIST_FILES_FILES_DESC, // Description
    UNDEFINED_STRING, // ListFiles
    UNDEFINED_STRING, // Use only if
    UNDEFINED_STRING, // Default value
    UNDEFINED_VALUE, // Min. Value
    UNDEFINED_VALUE, // Max. Value
    OPTTYPE_mandatory) // Required
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcListFiles::~CCalcListFiles() {
}

void CCalcListFiles::Prepare(void) {
    DM_GET_INPUTS
    DM_INPUT(path_)
    DM_INPUT(include_)
    DM_INPUT(exclude_)
    DM_GET_OUTPUTS
    DM_OUTPUT(files_)
    DM_END
}
/**
 *
 */
void CCalcListFiles::Calculate(bool dry_run) {
    if (dry_run == true) {
        return;
    }

    try {

        boost::progress_timer t(std::clog);

        fs::path full_path(fs::initial_path<fs::path>());

        if (path_->value() == "") {
            path_->set_value("./");
        }

        // Add "/" at the end of the path
        if (path_->value().at(path_->value().size()-1) != '/') {
            path_->add("/");
        }

        std::string include_value = include_->value();
        CStringTools::Replace(include_value, "\\\\.", "\.");

        // Add the dot of the extension (example: from "fa" to ".fa"):
//        if ((include_value != "") && (include_value [0] != '.')){
//            include_->set_value("." + include_value);
//        }
        
        //include_->set_value("^.*\\\\.fa$");
        //const boost::regex my_filter( include_value);

        full_path = fs::system_complete(fs::path(path_->value()));

        if ((fs::exists(full_path)) && (fs::is_directory(full_path))) {

            fs::directory_iterator end_iter;
            std::string cur_extension;
            std::string file_name;
            boost::regex regex_expression (include_value);
            
            for (fs::directory_iterator dir_itr(full_path);
                    dir_itr != end_iter;
                    ++dir_itr) {
                try {

                    if (fs::is_regular_file(dir_itr->status())) {
                        file_name = dir_itr->path().filename().c_str();
                        // file_extension = dir_itr->path().extension().c_str();

                        if (exclude_->FindValue(file_name) == false) {
DEBUG_MSG << file_name << " is not excluded. Let's check with: " << include_value END_MSG;
                            if(boost::regex_match(file_name,  regex_expression, boost::match_default | boost::format_sed) ) {
DEBUG_MSG << "Matched!" END_MSG;
                            //if (file_extension== include_value) {
                                files_->PushBack(path_->value() + file_name);
                            } else {
DEBUG_MSG << "Not matched!" END_MSG;
                            }
                        } else {
DEBUG_MSG << file_name << " is excluded." END_MSG;
                        }
                    }
                } catch (const std::exception & ex) {
                    ERROR_MSG << "CCalcListFiles: '" << ex.what() << "'..." END_MSG;
                }
            }
        } else {
            ERROR_MSG << "Path not found or it is not a directory: '" << path_->value() << "'..." END_MSG;
        }
    }
    catch(...) {
        ERROR_MSG << "Include parameter error..." END_MSG;
    }

    files_->Sort();
}

void CCalcListFiles::Finalize(void) {
    DM_DEL_ALL_LOCAL_DATA
}


