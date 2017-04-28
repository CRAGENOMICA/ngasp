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
 *  \brief     CCMDForeach.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 11, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDForeach.h"

#include <string>

#include "../../instructions/CController.h"
#include "../../data_manager/CDataManager.h"
#include "../../data_manager/common/CDataAccess.h"
#include "../../data_manager/IDataValue.h"
#include "../../data_manager/Data/CDataInt64.h"

CCMDForeach::CCMDForeach()
  : ICommand(CMD_FOREACH,                                                       // Command Name
             CMD_FOREACH_ABB,                                                   // Command Abbreviation Name
             CMD_FOREACH_DESC,                                                  // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  data_ = new CDataAccess();
  node_ = new CDataAccess();
  from_ = new CDataAccess();
  to_ = new CDataAccess();

  set_increment_value(1);
  set_from_value(0);
  set_to_value(0);
}

CCMDForeach::~CCMDForeach() {
  if (data_ != NULL) {
    delete data_;
    data_ = NULL;
  }

  if (node_ != NULL) {
    delete node_;
    node_ = NULL;
  }

  if (from_ != NULL) {
    delete from_;
    from_ = NULL;
  }

  if (to_ != NULL) {
    delete to_;
    to_ = NULL;
  }
}

void CCMDForeach::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    FOREACH_DATA_SHORT,                                         // Short Name
                    FOREACH_DATA_LONG,                                          // Long Name
                    FOREACH_DATA_DESC,                                          // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    FOREACH_NODE_SHORT,                                         // Short Name
                    FOREACH_NODE_LONG,                                          // Long Name
                    FOREACH_NODE_DESC,                                          // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    FOREACH_FROM_SHORT,                                         // Short Name
                    FOREACH_FROM_LONG,                                          // Long Name
                    FOREACH_FROM_DESC,                                          // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    FOREACH_TO_SHORT,                                           // Short Name
                    FOREACH_TO_LONG,                                            // Long Name
                    FOREACH_TO_DESC,                                            // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    FOREACH_INCREMENT_SHORT,                                    // Short Name
                    FOREACH_INCREMENT_LONG,                                     // Long Name
                    FOREACH_INCREMENT_DESC,                                     // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION

}

bool CCMDForeach::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::FOREACH_DATA_SHORT:
      data_->Set(manager(), arguments);
      break;
    case KeyString::FOREACH_NODE_SHORT:
      node_->Set(manager(), arguments);
      break;
    case KeyString::FOREACH_FROM_SHORT:
      from_->Set(manager(), arguments);
      break;
    case KeyString::FOREACH_TO_SHORT:
      to_->Set(manager(), arguments);
      break;
    case KeyString::FOREACH_INCREMENT_SHORT:
      set_increment_value(CStringTools::ToInt(arguments));
      break;
    default:
      parseResult = false;
      break;
    }
  }


  return (CheckOptions() && parseResult);
}

void CCMDForeach::Run() {
}

#define INC_DATA_VALUE(var, to_var, dest, inc) to_var.Set(manager(), #var); var->Set(&to_var, dest, SetAction::REPLACE_VALUE); var->set_value(var->value() + inc);

/**
 * Code of loop instructions must be in the Finalize function.
 *
 * Else, the next one function to be executed when Run finalizes could be the
 * Finalize function of other instruction.
 */
void CCMDForeach::Finalize() {
  if (manager()->instructions_controller()->getCurrentInstruction()->loop_id()
      == 0) {
    /**
     * This is the First time that this loop is executed:
     */
    manager()->instructions_controller()->SetCurrentInstructionAsLoopStart();

    if (from_->IsSet()) {
      node_->data_object()->Set(node_, from_, SetAction::REPLACE_VALUE);
    }
  } else {
    CDataInt64 *to_less_one = NULL;
    DM_NEW_DATA(to_less_one)

    CDataAccess to_var;
    INC_DATA_VALUE(to_less_one, to_var, to_, -1)

    ComparisonType comp = node_->data_object()->Compare(node_, &to_var);

    bool break_loop = false;

    if (increment_value() > 0) {
      // Increment
      if ((comp == ComparisonType::EQUAL) ||
          (comp == ComparisonType::GREATER_THAN)) {
        break_loop = true;
      }
    } else {
      // Decrement
      if ((comp == ComparisonType::EQUAL) ||
          (comp == ComparisonType::LESS_THAN)) {
        break_loop = true;
      }
    }

    if (break_loop == true) {
      /**
       * End Loop Condition is true, so let's get out of the loop:
       */
      manager()->instructions_controller()->GetOutOfThisLoop();
    } else {
      /**
       * Let's go to do another loop iteration:
       */
      node_->data_object()->add_value(CStringTools::ToString(increment_value()));
    }

    DM_DEL_DATA(to_less_one);

  }

  /// Clean the command to reuse it later:
  data_->Clear();
  node_->Clear();
  from_->Clear();
  to_->Clear();
  set_increment_value(1);
  set_from_value(0);
  set_to_value(0);
  
  DM_DEL_ALL_LOCAL_DATA 
}

