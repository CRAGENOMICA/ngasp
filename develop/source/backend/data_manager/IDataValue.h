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
 *  \brief     IDataValue.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 11, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATA_MANAGER_DATA_IDATAVALUE_H_
#define	DATA_MANAGER_DATA_IDATAVALUE_H_

#include <string>
#include <sstream>

#include "IData.h"
#include "../calculations/CAllCalculations.h"
#include "../data_manager/common/CDataAccess.h"
#include "../util/CStringTools.h"

template<class T>
class IDataValue : public IData {
  /**
   * CDataHelper needs to access private members of this class directly:
   */
  friend class CDataHelper;
 public:
  IDataValue(KeyString data_type_key,
             T default_value)
  : IData(data_type_key, data_type_key, CollectionType::PRIMITIVE) {
    set_value(default_value);
  }
  virtual ~IDataValue() {}

 private:
  T value_;

  // ===========================================================================
  // ACCESSORS
  // ===========================================================================
 public:
  inline T value(void) const { return value_; }
  /**
   * If you want to set an std:string value use set_value_string instead.
   */
  inline void set_value(T value) {
    value_ = value;
  }
  
  IDataValue <T>& operator=(const T val) {
    set_value(val);
    return (*this);
  }   

  
  inline void set_value_string(std::string value) {
    std::istringstream ss(value);
    ss >> value_;
  }
  inline void add(T inc) {
    value_ += inc;
  }  
  inline void add_value(std::string increment) {
    T inc = T();
    std::istringstream ss(increment);
    ss >> inc;
    value_ += inc;
  }

 public:
  void Print(PrintMode print_mode);

  /**
   * @return the size of the data contained in this class.
   */
  std::size_t Size(void) const {
    return static_cast<long int>(sizeof(T));
  }


  /**
   * Assign any field of any object to any field of this IDataValue:
   */
  void Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action);


  
  /**
   * Copy two IDataValues:
   *
   */
  IDataValue<T>& Copy(const IDataValue<T> &val) {
    set_value(val.value());
    return *this;
  }

 /**
  * Compare this IDataValues with anything:
  *
  * @param this_info: Information about where is the first data.
  * @param ref_info:  Information about where is the second data.
  */
  ComparisonType Compare(CDataAccess *this_info,
                         CDataAccess *ref_info);

  // ===========================================================================
  // COMPARISON
  // ===========================================================================
public:
  // Compare IDataValue with another IDataValue
  bool operator==(const IDataValue<T> &ref) {
    return (value() == ref.value());
  } 

  // Compare IDataValue with a value
  template<class I>
  bool operator==(const I &val) {
    return (value() == val);
  } 
  
  /**
   * Compare two IDataValues:
   */
  ComparisonType Compare(const IDataValue<T> &ref);

  /**
   * JSON
   */
  std::string ToJSON(void) {
    std::string ret;

    ret += "{\"id\":\"";
    ret += name();
    ret += "\",\"type\":\"";
    ret += type();
    ret += "\",";

    ret += "\"value\":\"";
    ret += CStringTools::ToString(value());
    ret += "\"";

    ret += "}";

    return ret;
  }
};

#endif  // DATA_MANAGER_DATA_IDATAVALUE_H_
