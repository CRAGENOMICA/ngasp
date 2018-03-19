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
 *  \brief     CDataAccess.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CDATAACCESS_H
#define	CDATAACCESS_H

#include <string>
#include <vector>
#include <list>

class CManager;
class IObject;
class IData;
class ICalculation;

/// ============================================================================
/// CONSTANTS
/// ============================================================================
#define MAX_NUM_DIMENSIONS 3


enum ComparisonType {
  UNDEFINED = 0,
  EQUAL,
  NOT_EQUAL,
  LESS_THAN,
  GREATER_THAN
};


class CDataAccess {
 public:
  CDataAccess();
  virtual ~CDataAccess();

 public:
  void Set(CManager *manager, std::string reference);

  /**
   * Removes all access information and VARIANT information.
   */
  void Clear(void);

 private:
  std::vector<long int> ReferencesToPositions(CManager *manager,
                                             std::string pos_references);
  std::list<std::string> SeparateReferences(std::string pos_references);
  int VariableToNumber(CManager *manager, std::string pos_references);

 private:
  // ===========================================================================
  // ACCESS INFORMATION
  // ===========================================================================
  std::string initial_reference_;
  IData *data_object_;
  ICalculation *calc_object_;
  std::string data_variable_;
  std::vector<long int> positions_;
  std::string value_;
  bool value_is_set_;  // it is true when value_ has been set.
                       // This boolean is necessary because value_ could be ""
                       // because it is set to null value.

 public:
  inline IData *data_object(void) { return data_object_; }
  inline void set_data_object(IData *data_object) {
    data_object_ = data_object;
  }

  inline ICalculation *calc_object(void) { return calc_object_; }
  inline void set_calc_object(ICalculation *calc_object) {
    calc_object_ = calc_object;
  }

  inline std::string data_variable(void) {
    return data_variable_;
  }
  inline void set_data_variable(std::string data_variable) {
    data_variable_ = data_variable;
  }

  inline void set_initial_reference(const std::string &initial_reference) {
    initial_reference_ = initial_reference;
  }
  inline std::string initial_reference(void) {
    return initial_reference_;
  }

  inline std::vector<long int> positions(void) { return positions_; }
  inline void set_positions(long int x, long int *y = NULL, long int *z = NULL) {
    positions_.clear();
    positions_.push_back(x);
    if(y != NULL) { positions_.push_back(*y); }
    if(z != NULL) { positions_.push_back(*z); }
  }

  inline std::string value(void) { return value_; }
  inline void set_value(std::string value) { value_ = value; }

  /**
   * True if this CDataSet has been set with any value or object pointer.
   * If it is totally empty it returns False.
   * @return
   */
  inline bool IsSet(void) {
    return (!((data_object_ == NULL) &&
            (calc_object_ == NULL) &&
            (value_is_set_ == false)));
  }

  /**
   * True if a value is set in "value_" field.
   */
  inline bool value_is_set(void) { return value_is_set_; }
  inline void set_value_is_set(bool value_is_set) {
    value_is_set_ = value_is_set;
  }
 };

#endif  // CDATAACCESS_H

