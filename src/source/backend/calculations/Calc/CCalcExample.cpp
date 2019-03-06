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
 *  \brief     CCalcExample.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      September 28, 2016
 *  \pre
 *  \bug
 *  \warning
 */
#include "CCalcExample.h"

#include <cmath>

#include "../../language/CStringTable.h"

#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataStdString.h"

#include "../../util/CFile.h"

CCalcExample::CCalcExample()
: ICalculation(KeyString::CALC_EXAMPLE,
               KeyString::CALC_EXAMPLE_BRIEF_DESC,
               KeyString::CALC_EXAMPLE_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(input_value_,                                                // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCEXAMPLE_INPUT,                                          // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   CCALCEXAMPLE_INPUT_DESC,                                     // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaSo_,                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_OUTPUT_,                     // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaTo_,                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_NT_TAJ_OUTPUT_,              // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
    SET_OUTPUT_INFO(out_stats_thetaFL_,                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCMSTATSPOP_CALC_STATS_THETA_NT_FULI_OUTPUT_,             // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcExample::~CCalcExample() {
}

void CCalcExample::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(input_value_)
  DM_GET_OUTPUTS
    DM_OUTPUT(out_stats_thetaSo_)
    DM_OUTPUT(out_stats_thetaTo_)
    DM_OUTPUT(out_stats_thetaFL_)
  DM_END
}

/**
 *  GC_Content Formula: https://en.wikipedia.org/wiki/GC-content
 */
void CCalcExample::Calculate(bool dry_run) {

  //if (input_value_->value() == 9999) {
    out_stats_thetaSo_->ReserveMemory(10);
    (*out_stats_thetaSo_)[0]  = 10.2;
    (*out_stats_thetaSo_)[1]  = 14.1;
    (*out_stats_thetaSo_)[2]  = 14.4;
    (*out_stats_thetaSo_)[3]  = 14.4;
    (*out_stats_thetaSo_)[4]  = 14.4;
    (*out_stats_thetaSo_)[5]  = 14.5;
    (*out_stats_thetaSo_)[6]  = 14.5;
    (*out_stats_thetaSo_)[7]  = 14.6;
    (*out_stats_thetaSo_)[8]  = 14.7;
    (*out_stats_thetaSo_)[9]  = 14.7;
    
      
    out_stats_thetaTo_->ReserveMemory(10);
    (*out_stats_thetaTo_)[0]  = 12.2;
    (*out_stats_thetaTo_)[1]  = 10.2;
    (*out_stats_thetaTo_)[2]  = 13.5;
    (*out_stats_thetaTo_)[3]  = 10.8;
    (*out_stats_thetaTo_)[4]  = 10.2;
    (*out_stats_thetaTo_)[5]  = 11.9;
    (*out_stats_thetaTo_)[6]  = 14.1;
    (*out_stats_thetaTo_)[7]  = 10.1;
    (*out_stats_thetaTo_)[8]  = 14.2;
    (*out_stats_thetaTo_)[9]  = 13.1;
      
    out_stats_thetaFL_->ReserveMemory(10);
    (*out_stats_thetaFL_)[0]  = 14.2;
    (*out_stats_thetaFL_)[1]  = 17.1;
    (*out_stats_thetaFL_)[2]  = 10.2;
    (*out_stats_thetaFL_)[3]  = 14.2;
    (*out_stats_thetaFL_)[4]  = 14.1;
    (*out_stats_thetaFL_)[5]  = 16.2;
    (*out_stats_thetaFL_)[6]  = 10.3;
    (*out_stats_thetaFL_)[7]  = 17.2;
    (*out_stats_thetaFL_)[8]  = 10.4;
    (*out_stats_thetaFL_)[8]  = 10.2;
  //}
    

DM_RESULT(result)
result->set_value(0);


/*
 #include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataStdString.h"
 */
std::string output_file_name = "output.txt";

DM_ITERATION_NUMBER(iteration_number)
DM_ITERATION_VALUE(iteration_value)

/*
 #include "../../util/CFile.h"
 */
output_file_name = CFile::ConcatenateIterationToFilePathName(output_file_name,
                                                                                                                                            iteration_number->value(),
                                                                                                                                            iteration_value->value());
}



void CCalcExample::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

