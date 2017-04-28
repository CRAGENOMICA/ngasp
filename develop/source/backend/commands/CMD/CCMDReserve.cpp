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
 *  \brief     CCMDReserve.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Aug 3, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDReserve.h"

#include <string>
#include <list>

#include "../../data_manager/CDataManager.h"
#include "../../calculations/CAllCalculations.h"
#include "../../instructions/CController.h"
#include "../../util/CStringTools.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/common/CDataHelper.h"

CCMDReserve::CCMDReserve()
  : ICommand(CMD_RESERVE,                                                       // Command Name
             CMD_RESERVE_ABB,                                                   // Command Abbreviation Name
             CMD_RESERVE_DESC,                                                  // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  name_ = "";
  tables_ = new CDataAccess();
  regs_ = new CDataAccess();
  len_ = new CDataAccess();
  default_value_ = new CDataAccess();

}

CCMDReserve::~CCMDReserve() {
  if (tables_ != NULL) {
    delete tables_;
    tables_ = NULL;
  }
  if (regs_ != NULL) {
    delete regs_;
    regs_ = NULL;
  }
  if (len_ != NULL) {
    delete len_;
    len_ = NULL;
  }
  if (default_value_ != NULL) {
    delete default_value_;
    default_value_ = NULL;
  }
}

void CCMDReserve::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    RESERVE_NAME_SHORT,                                         // Short Name
                    RESERVE_NAME_LONG,                                          // Long Name
                    RESERVE_NAME_DESC,                                          // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required

    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    RESERVE_TABLES_SHORT,                                       // Short Name
                    RESERVE_TABLES_LONG,                                        // Long Name
                    RESERVE_TABLES_DESC,                                        // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    RESERVE_REGS_SHORT,                                         // Short Name
                    RESERVE_REGS_LONG,                                          // Long Name
                    RESERVE_REGS_DESC,                                          // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    RESERVE_LEN_SHORT,                                          // Short Name
                    RESERVE_LEN_LONG,                                           // Long Name
                    RESERVE_LEN_DESC,                                           // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    RESERVE_DEFAULT_SHORT,                                      // Short Name
                    RESERVE_DEFAULT_LONG,                                       // Long Name
                    RESERVE_DEFAULT_DESC,                                       // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  END_COMMAND_INTERFACE_DEFINITION
}


bool CCMDReserve::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::RESERVE_NAME_SHORT:
      name_ = arguments;
      break;
    case KeyString::RESERVE_TABLES_SHORT:
      tables_->Set(manager(), arguments);
      if ((tables_->data_object() != NULL) &&
          (CDataFactory::ValidIndexType(tables_) == false)) {
        parseResult = false;
        ERROR_MSG << tables_->initial_reference()
                  << " is not a valid index type..."
                END_MSG;
      }
      break;
    case KeyString::RESERVE_REGS_SHORT:
      regs_->Set(manager(), arguments);
      if ((regs_->data_object() != NULL) &&
          (CDataFactory::ValidIndexType(regs_) == false)) {
        parseResult = false;
        ERROR_MSG << regs_->initial_reference()
                  << " is not a valid index type..."
                END_MSG;
      }
      break;
    case KeyString::RESERVE_LEN_SHORT:
      /**
       * Len can be:
       *  int variable
       *  int64 variable
       *  int scalar
       *  int64 scalar
       *
       * And it can also be:
       *  int-vector variable
       *  int64-vector variable
       */
      len_->Set(manager(), arguments);
//      if ((len_->data_object() != NULL) &&
//          (CDataFactory::ValidIndexType(len_) == false)) {
//        parseResult = false;
//        ERROR_MSG << len_->initial_reference()
//                  << " is not a valid index type..."
//                END_MSG;
//      }
      break;
    case KeyString::RESERVE_DEFAULT_SHORT:
      default_value_->Set(manager(), arguments);
       break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

/*
 * User can only create ROOT_PARENT variables, so this command
 * only reserves memory for ROOT_PARENT variables.
 */
void CCMDReserve::Run() {
  IData *data = (IData *)manager()->data_manager()->GetDataByName(ROOT_PARENT,
                                                                  name_);
  if (data != NULL) {

    long int tables = 0, regs = 0, len = 0, *pvalue_int64 = NULL;
    int *pvalue_int = NULL;
    std::string default_value, *pvalue_str = NULL;
    std::string var;

    if (tables_->IsSet()) {
      if (CDataFactory::GetType(tables_) == KeyString::DATA_INT) {
        /// int variable
        pvalue_int = CDataHelper::GetReferenceValue(tables_, var, int());
        if (pvalue_int != NULL) { tables = static_cast<long int>(*pvalue_int); }
        else { tables = CStringTools::ToInt64(var); }
      } else {
        /// int64 variable or scalar:
        long int the_type = 0;
        pvalue_int64 = CDataHelper::GetReferenceValue(tables_, var, the_type);
        if (pvalue_int64 != NULL) { tables = *pvalue_int64; }
        else { tables = CStringTools::ToInt64(var); }
      }
    }

    if (regs_->IsSet()) {
      if (CDataFactory::GetType(regs_) == KeyString::DATA_INT) {
        /// int variable
        pvalue_int = CDataHelper::GetReferenceValue(regs_, var, int());
        if (pvalue_int != NULL) { regs = static_cast<long int>(*pvalue_int); }
        else { regs = CStringTools::ToInt64(var); }
      } else {
        /// int64 variable or scalar:
        long int the_type = 0;
        pvalue_int64 = CDataHelper::GetReferenceValue(regs_, var, the_type);
        if (pvalue_int64 != NULL) { regs = *pvalue_int64; }
        else { regs = CStringTools::ToInt64(var); }
      }
    }

    long int *lens = 0;

    if (len_->IsSet()) {
      if ((len_->data_object() != NULL) &&
          (len_->data_object()->type_key() == KeyString::DATA_INT_VECTOR)) {
        CDataIntVector *p = static_cast<CDataIntVector *>(len_->data_object());

        if (p != NULL) {
          lens = new long int[p->reg_length()];

          for (std::size_t i = 0; i < p->reg_length(); i++) {
            lens[i] = static_cast<long int>((*p)[i]);
          }
        }

      } else {
        if ((len_->data_object() != NULL) &&
            (len_->data_object()->type_key() == KeyString::DATA_INT64_VECTOR)) {
          CDataInt64Vector *p = static_cast<CDataInt64Vector *>(len_->data_object());

          if (p != NULL) {
            lens = new long int[p->reg_length()];

            for (std::size_t i = 0; i < p->reg_length(); i++) {
              lens[i] = (*p)[i];
            }
          }

        } else {
          if (CDataFactory::GetType(len_) == KeyString::DATA_INT) {
            /// int variable
            pvalue_int = CDataHelper::GetReferenceValue(len_, var, int());
            if (pvalue_int != NULL) { len = static_cast<long int>(*pvalue_int); }
            else { len = CStringTools::ToInt64(var); }
          } else {
            /// int64 variable or scalar:
            long int the_type = 0;
            pvalue_int64 = CDataHelper::GetReferenceValue(len_, var, the_type);
            if (pvalue_int64 != NULL) { len = *pvalue_int64; }
            else { len = CStringTools::ToInt64(var); }
          }
        }
      }
    }

    if (default_value_->IsSet()) {
      pvalue_str = CDataHelper::GetReferenceValue(default_value_,
                                                  var, std::string());
      if (pvalue_str != NULL) { default_value = *pvalue_str; }
      else { default_value = var; }
    }



    CDataFactory::ReserveMemory(data,
                                tables,
                                regs,
                                len,
                                lens,
                                default_value);

    if (lens != 0) {
      delete[] lens;
      lens = 0;
    }
//
//    long int tables = 0;
//    if (tables_->data_object() != NULL) {
//      tables = tables_->data_object()
//    }
//
//
////    CDataHelper data_helper;
////    data_helper.GetReferenceValue(tables_, var, long int)
//
//    CDataAccess this_info;
//    CDataInt64 *tables_8782783627 = NULL,
//               *regs_8782783627   = NULL,
//               *len_8782783627    = NULL;
//    CDataStdString *default_value_8782783627 = NULL;
//
//    DM_NEW_DATA(tables_8782783627)
//    this_info.set_data_object(tables_8782783627);
//    tables_8782783627->Set(&this_info,
//                           tables_,
//                           SetAction::REPLACE_VALUE);
//    this_info.Clear();
//
//    DM_NEW_DATA(regs_8782783627)
//    this_info.set_data_object(regs_8782783627);
//    regs_8782783627->Set(&this_info,
//                         regs_,
//                         SetAction::REPLACE_VALUE);
//    this_info.Clear();
//
//    DM_NEW_DATA(len_8782783627)
//    this_info.set_data_object(len_8782783627);
//    len_8782783627->Set(&this_info,
//                        len_,
//                        SetAction::REPLACE_VALUE);
//    this_info.Clear();
//
//    DM_NEW_DATA(default_value_8782783627)
//    this_info.set_data_object(default_value_8782783627);
//    default_value_8782783627->Set(&this_info,
//                                  default_value_,
//                                  SetAction::REPLACE_VALUE);
//    this_info.Clear();
//
//    CDataFactory::ReserveMemory(data,
//                                tables_8782783627->value(),
//                                regs_8782783627->value(),
//                                len_8782783627->value(),
//                                default_value_8782783627->value());
//
//    manager()->data_manager()->RemoveDataByName("tables_8782783627");
//    manager()->data_manager()->RemoveDataByName("regs_8782783627");
//    manager()->data_manager()->RemoveDataByName("len_8782783627");
//    manager()->data_manager()->RemoveDataByName("default_value_8782783627");
  }
}

void CCMDReserve::Finalize() {
  /// Clean the command to reuse it later:
  name_ = "";
  tables_->Clear();
  regs_->Clear();
  len_->Clear();
  default_value_->Clear();
  
  DM_DEL_ALL_LOCAL_DATA
}

