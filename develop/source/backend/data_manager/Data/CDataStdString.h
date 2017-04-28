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
 *  \brief     CDataIntVector.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 11, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATA_MANAGER_DATA_CDATASTDSTRING_H_
#define	DATA_MANAGER_DATA_CDATASTDSTRING_H_

#include "../IDataValue.h"
#include "../IDataVector.h"
#include "../IDataMatrix.h"
#include "../IDataCube.h"

#include <string>

class CDataStdString : public IDataValue<std::string> {
 public:
  CDataStdString() : IDataValue(KeyString::DATA_STD_STRING,
                                "") {}
  virtual ~CDataStdString() {}

  IData * clone() const { return new CDataStdString(); /*clone*/ }

  void set_value_string(std::string value) {
    set_value(value);
  }

  std::size_t Size(void) {
    return static_cast<long int>(value().size());
  }

  void Concatenate(std::string text) {
    set_value(value() + text);
  }

//  /**
//   * This function is defined in IDataValue but it has to be redefined here
//   * only for <T> = <std::string> because set_value_string do not work well
//   * with std::string in IDataValue::Set function.
//   * It is all because set_value_string works with "istringstream >>" and
//   * when the string has spaces it only assigns the first word.
//   */
//  void Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action) {
//    bool set = false;
//
//    /**
//     * This class only has the attribute "value" to be changed in this function.
//     */
//    if ((ref_info->data_variable() == STR(VARIABLE_VALUE)) || (ref_info->data_variable() == "")) {
//      /**
//       * Full copy from "string value" to IDataValue:
//       */
//      if ((this_info->value_is_set() == true) &&
//          (this_info->positions().size() == 0) &&
//          (ref_info->positions().size() == 0)) {
//          set_value(this_info->value());
//          set = true;
//      }
//    }
//
//    if (set == true) {
//      CallOnChange();
//      EvalSet(manager(), set, this_info, ref_info);
//    } else {
//      IDataValue<std::string>::Set(this_info, ref_info, action);
//    }
//  }
  
  std::string ToJSON(void) {
    std::string ret;

    ret += "{\"id\":\"";
    ret += name();
    ret += "\",\"type\":\"";
    ret += type();
    ret += "\",";

    ret += "\"value\":\"" + value() + "\"";

    ret += "}";

    return ret;
  }
};

#endif  // DATA_MANAGER_DATA_CDATASTDSTRING_H_
