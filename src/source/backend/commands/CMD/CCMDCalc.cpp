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
 *  \brief     CCMDCalc.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 6, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDCalc.h"

#include <string>
#include <list>

#include "../../data_manager/CDataManager.h"
#include "../../calculations/CAllCalculations.h"
#include "../../instructions/CController.h"
#include "../../util/CStringTools.h"

CCMDCalc::CCMDCalc()
  : ICommand(CMD_CALC,                                                          // Command Name
             CMD_CALC_ABB,                                                      // Command Abbreviation Name
             CMD_CALC_DESC,                                                     // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also  
  set_name("");
  set_as("");
  //set_all_creatable_types(new std::list<KeyString>());

//  for (int i = KeyString::_CALC_FIRST + 1;
//          i < KeyString::_CALC_LAST; ++i) {
//    KeyString key = static_cast<KeyString>(i);
//    if(CStringTable::Instance()->IsParent(key)) {
//      all_creatable_types_->push_back(key);
//    }
//  }
}

CCMDCalc::~CCMDCalc() {
//  if (all_creatable_types() != NULL) {
//    delete all_creatable_types_;
//    all_creatable_types_ = NULL;
//  }
}

void CCMDCalc::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    CALC_NAME_SHORT,                                            // Short Name
                    CALC_NAME_LONG,                                             // Long Name
                    CALC_NAME_DESC,                                             // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    CALC_AS_SHORT,                                              // Short Name
                    CALC_AS_LONG,                                               // Long Name
                    CALC_AS_DESC,                                               // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  END_COMMAND_INTERFACE_DEFINITION
}

//bool CCMDCalc::ValidateType(const std::string &type) {
//  bool valid = false;
//
//  CCalcFactory calc_factory;
//
//
////  for (std::list<KeyString>::iterator it =
////       all_creatable_types()->begin();
////      ((it != all_creatable_types()->end()) && (valid == false)); ++it) {
////    valid = (STR2(((KeyString)(*it))) == type);
////  }
//
//  std::list<ICalculation *>::iterator it;
//  for (it = manager()->all_calculations()->calculations()->begin();
//       ((it != manager()->all_calculations()->calculations()->end()) &&
//        (valid == false));
//       ++it) {
//    valid = ((*it)->name() == type);
//  }
//
//  return valid;
//}

bool CCMDCalc::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::CALC_NAME_SHORT:
      set_name(arguments);
      break;
    case KeyString::CALC_AS_SHORT:
      set_as(arguments);

//      if (ValidateType(arguments)) {
//        set_as(arguments);
//      } else {
//        ERROR_MSG << STR(CALC_TYPE_UNKNOWN) END_MSG;
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
void CCMDCalc::Run() {
  manager()->all_calculations()->CreateCalcByType(ROOT_PARENT, name(), as());

//  if (name() != "") {
//    if (name().find(STR(RESERVED_DATA_NAME_PREFIX)) == 0) {
//      ERROR_MSG << STR(CALC_RESERVED_NAME) END_MSG;
//    } else {
//      std::string current_experiment = STR(EXPERIMENT_DEFAULT_NAME);
//
//      KeyString key;
//      std::string key_uc;
//      std::string as_uc = CStringTools::ToUpper(as());
//
//      std::list<ICalculation *>::iterator it;
//      for (it = manager()->all_calculations()->calculations()->begin();
//           it != manager()->all_calculations()->calculations()->end();
//           ++it) {
//
//        key = (*it)->type_key();
//        key_uc = CStringTools::ToUpper(STR2(key));
//
//        if (as_uc == key_uc) {
//            manager()->all_calculations()->CreateCalcByKey(name(), key);
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
////            manager()->all_calculations()->CreateCalcByKey(name(), key);
////        }
////      }
//
//
//    }
//  }
}

void CCMDCalc::Finalize() {
  /// Clean the command to reCalc it later:
  set_name("");
  set_as("");
  
  DM_DEL_ALL_LOCAL_DATA
}

