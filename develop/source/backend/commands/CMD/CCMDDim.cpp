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
 *  \brief     CCMDDim.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 6, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDDim.h"

#include <string>
#include <list>

#include "../../data_manager/CDataManager.h"
#include "../../calculations/CAllCalculations.h"
#include "../../instructions/CController.h"
#include "../../util/CStringTools.h"

CCMDDim::CCMDDim()
  : ICommand(CMD_DIM,                                                           // Command Name
             CMD_DIM_ABB,                                                       // Command Abbreviation Name
             CMD_DIM_DESC,                                                      // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also    
  set_name("");
  set_as("");
  //set_all_creatable_types(new std::list<KeyString>());

//  for (int i = KeyString::_DATA_FIRST + 1;
//          i < KeyString::_DATA_LAST; ++i) {
//    KeyString key = static_cast<KeyString>(i);
//    if(CStringTable::Instance()->IsParent(key)) {
//      all_creatable_types_->push_back(key);
//    }
//  }
}

CCMDDim::~CCMDDim() {
//  if (all_creatable_types() != NULL) {
//    delete all_creatable_types_;
//    all_creatable_types_ = NULL;
//  }
}

void CCMDDim::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    DIM_NAME_SHORT,                                             // Short Name
                    DIM_NAME_LONG,                                              // Long Name
                    DIM_NAME_DESC,                                              // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    DIM_AS_SHORT,                                               // Short Name
                    DIM_AS_LONG,                                                // Long Name
                    DIM_AS_DESC,                                                // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  END_COMMAND_INTERFACE_DEFINITION
}

//bool CCMDDim::ValidateType(const std::string &type) {
//  bool valid = false;
//
////  for (std::list<KeyString>::iterator it =
////       all_creatable_types()->begin();
////      ((it != all_creatable_types()->end()) && (valid == false)); ++it) {
////    valid = (STR2(((KeyString)(*it))) == type);
////  }
//
//  std::map<std::string, IData *>::iterator it;
//  for (it = manager()->data_manager()->repository()->begin();
//       ((it != manager()->data_manager()->repository()->end()) &&
//        (valid == false));
//       ++it) {
//    valid = (it->second->name() == type);
//  }
//
//
//  return valid;
//}

bool CCMDDim::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::DIM_NAME_SHORT:
      set_name(arguments);
      break;
    case KeyString::DIM_AS_SHORT:
      set_as(arguments);

//      if (ValidateType(arguments)) {
//        set_as(arguments);
//      } else {
//        ERROR_MSG << STR(DIM_TYPE_UNKNOWN) END_MSG;
//        parseResult = false;
//      }
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

/*
 * User can only create ROOT_PARENT calculations, so this command
 * only creates ROOT_PARENT calculations.
 */
void CCMDDim::Run() {
  manager()->data_manager()->CreateDataByType(ROOT_PARENT, name(), as());

//  if (name() != "") {
//    if (name().find(STR(RESERVED_DATA_NAME_PREFIX)) == 0) {
//      ERROR_MSG << STR(DIM_RESERVED_NAME) END_MSG;
//    } else {
//      std::string current_experiment = STR(EXPERIMENT_DEFAULT_NAME);
//
//      KeyString key;
//      std::string key_uc;
//      std::string as_uc = CStringTools::ToUpper(as());
//
//
//      std::map<std::string, IData *>::iterator it;
//      for (it = manager()->data_manager()->repository()->begin();
//           it != manager()->data_manager()->repository()->end();
//           ++it) {
//        key = it->second->type_key();
//        key_uc = CStringTools::ToUpper(STR2(key));
//
//        if (as_uc == key_uc) {
//          manager()->data_manager()->CreateDataByKeyString(name(), key);
//        }
//      }
//
////      for (std::list<KeyString>::iterator it =
////           all_creatable_types()->begin();
////          it != all_creatable_types()->end(); ++it) {
////        key = ((KeyString)(*it));
////        key_uc = CStringTools::ToUpper(STR2(key));
////
////        if (as_uc == key_uc) {
////          manager()->data_manager()->CreateDataByKeyString(name(), key);
////        }
////      }
//    }
//  }
}

void CCMDDim::Finalize() {
  /// Clean the command to reuse it later:
  set_name("");
  set_as("");
  
  DM_DEL_ALL_LOCAL_DATA
}

