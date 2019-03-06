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
 *  \brief     CCalcBoxPlotValues.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 27, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcBoxPlotValues.h"

#include <cmath>

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataDoubleVector.h"


CCalcBoxPlotValues::CCalcBoxPlotValues()
: ICalculation(KeyString::CALC_BOX_PLOT_VALUES,
               KeyString::CALC_BOX_PLOT_VALUES_BRIEF_DESC,
               KeyString::CALC_BOX_PLOT_VALUES_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
  // Inputs
    SET_INPUT_INFO(array_,                                                      // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCBOXPLOTVALUES_ARRAY,                                    // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required 
  
  // Outputs
    SET_OUTPUT_INFO(q1_,                                                        // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCBOXPLOTVALUES_Q1,                                       // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  
    SET_OUTPUT_INFO(median_,                                                    // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCBOXPLOTVALUES_MEDIAN,                                   // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  
    SET_OUTPUT_INFO(q3_,                                                        // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCBOXPLOTVALUES_Q3,                                       // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  
    SET_OUTPUT_INFO(min_,                                                       // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCBOXPLOTVALUES_MIN,                                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  
    SET_OUTPUT_INFO(max_,                                                       // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCBOXPLOTVALUES_MAX,                                      // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required

    SET_OUTPUT_INFO(outliers_,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCBOXPLOTVALUES_OUTLIERS,                                 // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required

  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcBoxPlotValues::~CCalcBoxPlotValues() {
}

void CCalcBoxPlotValues::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(array_)
  DM_GET_OUTPUTS
    DM_OUTPUT(q1_)
    DM_OUTPUT(median_)
    DM_OUTPUT(q3_)
    DM_OUTPUT(min_)
    DM_OUTPUT(max_)
    DM_OUTPUT(outliers_)
  DM_END
}

// How to calculate the boxplot:
//   http://stackoverflow.com/questions/19210066/how-do-i-get-box-plot-key-numbers-from-an-array-in-php
// How to calculate outliers:
//   http://www.purplemath.com/modules/boxwhisk3.htm

/**
// Example data set:
10.2 14.1 14.4 14.4 14.4 14.5 14.5 14.6 14.7 14.7 14.7 14.9 15.1 15.9 16.4

// Orther the data set:

10.2 14.1 14.4 14.4 14.4 14.5 14.5 14.6 14.7 14.7 14.7 14.9 15.1 15.9 16.4

// Get the meddian: (Q2 = 14.6)
// It is the number in the middle. If there are tow numbers then do (a+b)/2.

10.2 14.1 14.4 14.4 14.4 14.5 14.5 (14.6) 14.7 14.7 14.7 14.9 15.1 15.9 16.4

// Divide the data set in two parts:

10.2 14.1 14.4 14.4 14.4 14.5 14.5
14.7 14.7 14.7 14.9 15.1 15.9 16.4

// Get the median of each part: (Q1 = 14.4 & Q3 = 14.9)

10.2 14.1 14.4 (14.4) 14.4 14.5 14.5
14.7 14.7 14.7 (14.9) 15.1 15.9 16.4

// Get the interquartile range (IQR = 0.5):

IQR = Q3 - Q1
IQR = 14.9 – 14.4
IQR = 0.5

// Outliers will be any points below Q1 – 1.5×IQR = 14.4 – 0.75 = 13.65 or
// above Q3 + 1.5×IQR = 14.9 + 0.75 = 15.65.
*/
void CCalcBoxPlotValues::Calculate(bool dry_run) {
  if (dry_run) {
    return;
  }

  array_->Sort();

  CDataDoubleVector discarded_values;
  discarded_values.ReserveMemory(1);
  discarded_values[0] = NA_VALUE; //(NA)
  array_->RemoveValues(discarded_values);
  
  median_->set_value(array_->GetMedian());

  CDataDoubleVector lower_values = array_->SplitVector(median_->value(), true);

  CDataDoubleVector higher_values = array_->SplitVector(median_->value(), false);

  q1_->set_value(lower_values.GetMedian());

  q3_->set_value(higher_values.GetMedian());
  
  double iqr = q3_->value() - q1_->value(); // Inner Quartile Range (IQR)

  min_->set_value(q1_->value() - 1.5 * iqr);
  
  max_->set_value(q3_->value() + 1.5 * iqr);
  
  CDataDoubleVector lower_outliers = lower_values.SplitVector(min_->value(), true);

  CDataDoubleVector higher_outliers = higher_values.SplitVector(max_->value(), false);
  
  min_->set_value(lower_values.GetNearestValue(min_->value(), true));
  
  max_->set_value(higher_values.GetNearestValue(max_->value(), false));
  
  outliers_->Copy(lower_outliers);
  outliers_->Append(higher_outliers);
}


void CCalcBoxPlotValues::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
