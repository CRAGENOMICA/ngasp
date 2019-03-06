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
 *  \brief     CCMDSetValue.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 6, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDSetValue.h"

#include <string>

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../language/CStringTable.h"
#include "../../util/CStringTools.h"
#include "../../data_manager/common/CDataAccess.h"

CCMDSetValue::CCMDSetValue()
  : ICommand(CMD_SET_VALUE,                                                     // Command Name
             CMD_SET_VALUE_ABB,                                                 // Command Abbreviation Name
             CMD_SET_VALUE_DESC,                                                // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  this_info_ = new CDataAccess();
  ref_info_ = new CDataAccess();
  inc_info_ = new CDataAccess();
  action_ = SetAction::SET_ACTION_UNDEFINED;
  changing_encode_value_ = false;
}

CCMDSetValue::~CCMDSetValue() {
  if (this_info_ != NULL) {
    delete this_info_;
    this_info_ = NULL;
  }

  if (ref_info_ != NULL) {
    delete ref_info_;
    ref_info_ = NULL;
  }

  if (inc_info_ != NULL) {
    delete inc_info_;
    inc_info_ = NULL;
  }

  changing_encode_value_ = false;
}

void CCMDSetValue::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    SET_TO_SHORT,                                               // Short Name
                    SET_TO_LONG,                                                // Long Name
                    SET_TO_DESC,                                                // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    SET_EQ_SHORT,                                               // Short Name
                    SET_EQ_LONG,                                                // Long Name
                    SET_EQ_DESC,                                                // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    SET_INC_SHORT,                                              // Short Name
                    SET_INC_LONG,                                               // Long Name
                    SET_INC_DESC,                                               // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    SET_SUB_SHORT,                                              // Short Name
                    SET_SUB_LONG,                                               // Long Name
                    SET_SUB_DESC,                                               // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    SET_MUL_SHORT,                                              // Short Name
                    SET_MUL_LONG,                                               // Long Name
                    SET_MUL_DESC,                                               // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    SET_DIV_SHORT,                                              // Short Name
                    SET_DIV_LONG,                                               // Long Name
                    SET_DIV_DESC,                                               // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDSetValue::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::SET_TO_SHORT:
      this_info_->Set(manager(), arguments);
      if ((this_info_->data_object() == NULL) &&
          (this_info_->calc_object() == NULL)) {
        parseResult = false;
        ERROR_MSG << arguments << STR(SPACE)
                  << STR(VARIABLE_NOT_FOUND)
                  END_MSG;
      }

      /*
       * Special Case:
       * If the variable is "$encoding" then this is some code to be executed
       * in the Run() function.
       */
      if (arguments == "$encoding") {
          changing_encode_value_ = true;
      }
      break;
    case KeyString::SET_EQ_SHORT:
      ref_info_->Set(manager(), arguments);
      if (((ref_info_->data_variable() != "") ||
           (ref_info_->positions().size() != 0)) &&
          (ref_info_->data_object() == NULL) &&
          (this_info_->calc_object() == NULL)) {
        parseResult = false;
        ERROR_MSG << arguments << STR(SPACE)
                  << STR(VARIABLE_NOT_FOUND)
                  END_MSG;
      }
      break;
    case KeyString::SET_INC_SHORT:
      inc_info_->Set(manager(), arguments);
      action_ = SetAction::ADD_VALUE;
      break;
    case KeyString::SET_SUB_SHORT:
      inc_info_->Set(manager(), arguments);
      action_ = SetAction::SUBSTRACT_VALUE;
      break;
    case KeyString::SET_MUL_SHORT:
      inc_info_->Set(manager(), arguments);
      action_ = SetAction::MULTIPLY_VALUE;
      break;
    case KeyString::SET_DIV_SHORT:
      inc_info_->Set(manager(), arguments);
      action_ = SetAction::DIVIDE_VALUE;
      break;
    default:
      parseResult = false;
      break;
    }
  }

  /**
   * Types control:
   */
  if (CDataFactory::CompatibleTypes(this_info_, ref_info_) == false) {
    parseResult = false;
    // TODO(jjene) Constant
    WARNING_MSG << "Variables not of the same type in assignation: "
                << this_info_->initial_reference()
                << " <-- "
                << ref_info_->initial_reference()
                END_MSG;
  }

  return (CheckOptions() && parseResult);
}

void CCMDSetValue::Run() {
  /**
   * Set data value:
   */
  if (this_info_->data_object() != NULL) {
    this_info_->data_object()->Set(this_info_, ref_info_, SetAction::REPLACE_VALUE);

    /*
     * Special Case:
     * If user changes the "$encoding" value,
     * this value must be changed in CStringTable::Instance too.
     */
    if (changing_encode_value_ == true) {
        CDataStdString *encoding = NULL;
        
        // This is a global variable. So, its parent is ROOT_PARENT.
        encoding = (CDataStdString *)manager()->data_manager()->GetDataByName(
                                                                 encoding,
                                                                 ROOT_PARENT,
                                                                 STR(ENCODING));
        CStringTable::Instance()->set_encoding(encoding->value());
    }
  }

  /**
   * Set calc value:
   */
  if (this_info_->calc_object() != NULL) {
    this_info_->calc_object()->Set(this_info_, ref_info_, SetAction::REPLACE_VALUE);
  }

  if (action_ != SetAction::SET_ACTION_UNDEFINED) {
    this_info_->data_object()->Set(this_info_,
                                   inc_info_,
                                   action_);
  }
}

void CCMDSetValue::Finalize() {
  /// Clean the command to reuse it later:
  ref_info_->Clear();
  this_info_->Clear();
  inc_info_->Clear();
  action_ = SetAction::SET_ACTION_UNDEFINED;
  changing_encode_value_ = false;
  
  DM_DEL_ALL_LOCAL_DATA
}
