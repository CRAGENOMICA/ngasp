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
 *  \brief     CCMDIf.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 6, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDIf.h"

#include <string>

#include "../../data_manager/CDataManager.h"
#include "../../language/CStringTable.h"
// #include "../../util/CStringTools.h"
#include "../../data_manager/common/CDataAccess.h"
#include "../../instructions/CController.h"

CCMDIf::CCMDIf()
  : ICommand(CMD_IF,                                                            // Command Name
             CMD_IF_ABB,                                                        // Command Abbreviation Name
             CMD_IF_DESC,                                                       // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  reference_ = new CDataAccess();
  compared_to_ = new CDataAccess();
//  set_comparison_type(CDataAccess::ComparisonType::UNDEFINED);
  set_conjuntion(GrammaticalConjuntion::AND);
  if_condition_evaluation_result_ = true;
}

CCMDIf::~CCMDIf() {
  if (reference_ != NULL) {
    delete reference_;
    reference_ = NULL;
  }

  if (compared_to_ != NULL) {
    delete compared_to_;
    compared_to_ = NULL;
  }
}

void CCMDIf::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    IF_REF_SHORT,                                               // Short Name
                    IF_REF_LONG,                                                // Long Name
                    IF_REF_DESC,                                                // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    IF_EQ_SHORT,                                                // Short Name
                    IF_EQ_LONG,                                                 // Long Name
                    IF_EQ_DESC,                                                 // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    IF_NE_SHORT,                                                // Short Name
                    IF_NE_LONG,                                                 // Long Name
                    IF_NE_DESC,                                                 // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required  
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    IF_LT_SHORT,                                                // Short Name
                    IF_LT_LONG,                                                 // Long Name
                    IF_LT_DESC,                                                 // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    IF_GT_SHORT,                                                // Short Name
                    IF_GT_LONG,                                                 // Long Name
                    IF_GT_DESC,                                                 // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    IF_AND_SHORT,                                               // Short Name
                    IF_AND_LONG,                                                // Long Name
                    IF_AND_DESC,                                                // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_no_argument,                                        // Argument Required
                    OPTTYPE_optional)                                           // Required  
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    IF_OR_SHORT,                                                // Short Name
                    IF_OR_LONG,                                                 // Long Name
                    IF_OR_DESC,                                                 // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_no_argument,                                        // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION

}

bool CCMDIf::Prepare() {
  return true;  // (CheckOptions() && parseResult);
}

void CCMDIf::Run() {
  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  try {
    /**
     * All comparisons must be done because an OR could discard all previous
     * conditions and turn the global condition to true from false.
     */
    while (getopt_long_own(&option, &arguments)) {
      switch (option) {
      case KeyString::IF_REF_SHORT:
        reference_->Set(manager(), arguments);
        break;
      case KeyString::IF_EQ_SHORT:
        set_comparison_type(ComparisonType::EQUAL);
        compared_to_->Set(manager(), arguments);
        Compare();
        break;
      case KeyString::IF_NE_SHORT:
        set_comparison_type(ComparisonType::NOT_EQUAL);
        compared_to_->Set(manager(), arguments);
        Compare();
        break;
      case KeyString::IF_LT_SHORT:
        set_comparison_type(ComparisonType::LESS_THAN);
        compared_to_->Set(manager(), arguments);
        Compare();
        break;
      case KeyString::IF_GT_SHORT:
        set_comparison_type(ComparisonType::GREATER_THAN);
        compared_to_->Set(manager(), arguments);
        Compare();
        break;
      case KeyString::IF_AND_SHORT:
        set_conjuntion(GrammaticalConjuntion::AND);
        break;
      case KeyString::IF_OR_SHORT:
        set_conjuntion(GrammaticalConjuntion::OR);
        break;
      default:
        break;
      }
    }
  }
  catch(...) {
    ERROR_MSG << STR(IF_ERROR_1) END_MSG;
  }

  manager()->instructions_controller()->
                                 set_last_eval(if_condition_evaluation_result_);
}

void CCMDIf::Finalize() {
  /// Clean the command to reuse it later:
  compared_to_->Clear();
  reference_->Clear();
  set_conjuntion(GrammaticalConjuntion::AND);
  if_condition_evaluation_result_ = true;
  
  DM_DEL_ALL_LOCAL_DATA
}


void CCMDIf::Compare(void) {
  if (reference_->data_object() == NULL) {
    ERROR_MSG << "Comparing with NULL object..." END_MSG;  // TODO(jjene) Constant
  } else {
    ComparisonType compare = reference_->data_object()->Compare(reference_,
                                                                compared_to_);
    bool partial_condition_result = true;  // this default value is not used

    if (comparison_type() == ComparisonType::NOT_EQUAL) {
      partial_condition_result = (compare != ComparisonType::EQUAL);
    } else {
      partial_condition_result = (compare == comparison_type());
    }
    
    
    switch(conjuntion()) {
      case GrammaticalConjuntion::AND:
        /**
         * previous value = previous value AND current value
         */
        if_condition_evaluation_result_ = (if_condition_evaluation_result_ &&
                                           partial_condition_result);
        break;
      case GrammaticalConjuntion::OR:
        /**
         * It does not matter the previous value.
         * If current value is true then global condition is true.
         * If current value is false then do nothing.
         */
        if (partial_condition_result == true) {
          if_condition_evaluation_result_ = true;
        } else {
          /// discard
        }
        break;
    }
  }
}
