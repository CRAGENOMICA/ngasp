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
 *  \brief     CCMDAppend.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Nov 14, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDAppend.h"

#include <string>

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../language/CStringTable.h"
#include "../../util/CStringTools.h"
#include "../../data_manager/common/CDataAccess.h"
#include "../../data_manager/IDataMatrix.h"
#include "../../data_manager/IDataVector.h"
#include "../../data_manager/IDataValue.h"

CCMDAppend::CCMDAppend()
  : ICommand(CMD_APPEND,                                                        // Command Name
             CMD_APPEND_ABB,                                                    // Command Abbreviation Name
             CMD_APPEND_DESC,                                                   // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  to_matrix_info_ = new CDataAccess();
  from_value_info_ = new CDataAccess();
  index_info_ = new CDataAccess();
}

CCMDAppend::~CCMDAppend() {
  if (to_matrix_info_ != NULL) {
    delete to_matrix_info_;
    to_matrix_info_ = NULL;
  }

  if (from_value_info_ != NULL) {
    delete from_value_info_;
    from_value_info_ = NULL;
  }

  if (index_info_ != NULL) {
    delete index_info_;
    index_info_ = NULL;
  }
}
    
void CCMDAppend::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    APPEND_TO_SHORT,                                            // Short Name
                    APPEND_TO_LONG,                                             // Long Name
                    APPEND_TO_DESC,                                             // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required

    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    APPEND_ADD_SHORT,                                           // Short Name
                    APPEND_ADD_LONG,                                            // Long Name
                    APPEND_ADD_DESC,                                            // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
 
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    APPEND_INDEX_SHORT,                                            // Short Name
                    APPEND_INDEX_LONG,                                             // Long Name
                    APPEND_INDEX_DESC,                                             // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required  
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDAppend::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::APPEND_TO_SHORT:
      to_matrix_info_->Set(manager(), arguments);
      break;
    case KeyString::APPEND_ADD_SHORT:
      from_value_info_->Set(manager(), arguments);
      break;
    case KeyString::APPEND_INDEX_SHORT:
      index_info_->Set(manager(), arguments);
      break;
    default:
      parseResult = false;
      break;
    }
  }

  parseResult = ((to_matrix_info_->data_object() != NULL) &&
                 (from_value_info_->data_object() != NULL) &&
                 (index_info_->data_object() != NULL) &&
                 (parseResult));
  
  return (CheckOptions() && parseResult);
}
/*
    void Append(IDataValue<T>  *value,  std::size_t index) {
       IDataVector<T> * new_vector = new IDataVector<T>();

       new_vector[0] = index;
       new_vector[1] = value->value();

       data_.push_back(new_vector);
    }

    void Append(IDataVector<T> *vector, std::size_t index) {
       IDataVector<T> * new_vector = new IDataVector<T>();

       new_vector[0] = index;

       for (std::size_t i = 0; i < vector->Size(); i++) {
           new_vector[i + 1] = vector[i];
       }
       data_.push_back(new_vector);
    }

    void Append(IDataMatrix<T> *matrix, std::size_t index) {
       for (std::size_t r = 0; r < matrix->regs(); r++) {
           Append(matrix[r], index);
       }
    }
 */

void convert_from_to(int64_t a, int &b) {  b = static_cast<int64_t>(b); }
void convert_from_to(int64_t a, int64_t &b) {  b = static_cast<int64_t>(b); }
void convert_from_to(int64_t a, double &b) {  b = static_cast<int64_t>(b); }
void convert_from_to(int64_t a, float &b) {  b = static_cast<int64_t>(b); }
void convert_from_to(int64_t a, std::string &b) {  b = std::to_string(a); }

template<class T>
void CCMDAppend::RunType(T matrix_type) {
  // T index = (((IDataValue<T> *)(index_info_->data_object()))->value());
  
  // I know that "ite" is always "int64" (See CentralManager TranslateType function (cm.js)):
  int64_t ite = (((IDataValue<int64_t> *)(index_info_->data_object()))->value());
  // Now, I have to insert this "ite" of type "int64" into a matrix of type "T":
  //T index = static_cast<T>(ite);
  T index = T();
  convert_from_to(ite, index);

  IDataMatrix<T> *to_matrix = ((IDataMatrix<T> *)(to_matrix_info_->data_object()));
  
  KeyString type = to_matrix_info_->data_object()->type_key();
  
  switch(from_value_info_->data_object()->collection()) {
    case CollectionType::PRIMITIVE:
      to_matrix->Append((IDataValue<T> *)(from_value_info_->data_object()), index, type);
      break;
    case CollectionType::VECTOR:
      to_matrix->Append((IDataVector<T> *)(from_value_info_->data_object()), index, type);
      break;
    case CollectionType::MATRIX:
      to_matrix->Append((IDataMatrix<T> *)(from_value_info_->data_object()), index, type);
      break;
    default:
      break;
  }
}

void CCMDAppend::Run() {
  if(to_matrix_info_->data_object()->type_key() == KeyString::DATA_INT_MATRIX) {
    int only_type = 0;
    RunType(only_type);
  } else {
    if(to_matrix_info_->data_object()->type_key() == KeyString::DATA_INT64_MATRIX) {
      int64_t only_type = 0;
      RunType(only_type);  
    } else {
      if(to_matrix_info_->data_object()->type_key() == KeyString::DATA_FLOAT_MATRIX) {
        float only_type = 0.0;
        RunType(only_type);    
      } else {
        if(to_matrix_info_->data_object()->type_key() == KeyString::DATA_DOUBLE_MATRIX) {
          double only_type = 0.0;
          RunType(only_type);    
        } else {
            if(to_matrix_info_->data_object()->type_key() == KeyString::DATA_STD_STRING_MATRIX) {
              std::string only_type = "";
              RunType(only_type);    
            } else {
              ERROR_MSG << "This command can only be used with types int, int64, double, float and string."  END_MSG;
            }
        }
      }
    }
  }
}

void CCMDAppend::Finalize() {
  /// Clean the command to reuse it later:
  to_matrix_info_->Clear();
  from_value_info_->Clear();
  index_info_->Clear();
  
  DM_DEL_ALL_LOCAL_DATA
}
