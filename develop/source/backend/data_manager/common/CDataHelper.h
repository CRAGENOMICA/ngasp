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
 *  \brief     CDataHelper.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 30, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CDATAHELPER_H
#define	CDATAHELPER_H

#include <string>
#include <sstream>

#include "../../language/CStringTable.h"
#include "CDataAccess.h"
#include "../IDataValue.h"
#include "../IDataVector.h"
#include "../IDataMatrix.h"
#include "../IDataCube.h"

class CDataHelper {
 public:
  CDataHelper();
  virtual ~CDataHelper();

  template <class T>
  static
  ComparisonType Compare(T a, T b) {
    ComparisonType ret = ComparisonType::UNDEFINED;

    if (a == b) {
      ret = ComparisonType::EQUAL;
    } else {
      if (a > b) {
        ret = ComparisonType::GREATER_THAN;
      } else {
        ret = ComparisonType::LESS_THAN;
      }
    }

    return ret;
  }


  /**
   *
   * @param data_info
   * @param variable: Value of an IData member (length, regs, ...). It is Read Only.
   * @param Type: Type of the IData object and the type of the return reference.
   * @return reference: pointer to a data position value pointer to value_.
   */
  template <class T>
  static
  T *GetReferenceValue(CDataAccess *data_info, std::string &variable, T Type) {
    T *ret = NULL;

    IDataValue<T>  *data_value  = NULL;
    IDataVector<T> *data_vector = NULL;
    IDataMatrix<T> *data_matrix = NULL;
    IDataCube<T>   *data_cube   = NULL;

    /// This variable is set to true when user tries to access to a vector,
    /// matrix or cube position of size 0 (not allocated).
    bool null_data = false;

    if (data_info->value_is_set() == true) {
      variable = CStringTools::ToString(data_info->value());
    } else {
      if (data_info->data_object() == NULL) {
        std::cout << STR(VARIABLE_NOT_FOUND) << std::endl;  // TODO(jjene) MSG
      } else {
        switch(data_info->data_object()->collection()) {
          case CollectionType::PRIMITIVE:
            data_value = static_cast<IDataValue<T> *>(data_info->data_object());
            ret = &(data_value->value_);
            break;
          case CollectionType::VECTOR:
            data_vector = static_cast<IDataVector<T> *>(data_info->data_object());
            if (data_info->positions().size() == CollectionType::VECTOR) {
              ret = &((*data_vector)[data_info->positions().at(0)]);
              null_data = (ret == NULL);
            } else {
              if (data_info->data_variable() == "") {
                ret = NULL;
                variable = "";
              } else {
                if (data_info->data_variable() == STR(VARIABLE_LENGTH)) {
                  variable = CStringTools::ToString(data_vector->reg_length());
                }
              }
            }
            break;
          case CollectionType::MATRIX:
            data_matrix = static_cast<IDataMatrix<T> *>(data_info->data_object());
            if (data_info->positions().size() == CollectionType::MATRIX) {
              ret = &((*data_matrix)[data_info->positions().at(0)][data_info->positions().at(1)]);
              null_data = (ret == NULL);
            } else {
              if (data_info->data_variable() == "") {
                ret = NULL;
                variable = "";
              } else {
                if (data_info->data_variable() == STR(VARIABLE_REGS)) {
                  variable = CStringTools::ToString(data_matrix->regs());
                } else {
                  if (data_info->data_variable() == STR(VARIABLE_LENGTH)) {
                    variable = CStringTools::ToString(data_matrix->reg_length());
                  }
                }
              }
            }
            break;
          case CollectionType::CUBE:
            data_cube = static_cast<IDataCube<T> *>(data_info->data_object());
            if (data_info->positions().size() == CollectionType::CUBE) {
              ret = &((*data_cube)[data_info->positions().at(0)][data_info->positions().at(1)][data_info->positions().at(2)]);
              null_data = (ret == NULL);
            } else {
              if (data_info->data_variable() == "") {
                ret = NULL;
                variable = "";
              } else {
                if (data_info->data_variable() == STR(VARIABLE_TABLES)) {
                  variable = CStringTools::ToString(data_cube->tables());
                } else {
                  if (data_info->data_variable() == STR(VARIABLE_REGS)) {
                    variable = CStringTools::ToString(data_cube->regs());
                  } else {
                    if (data_info->data_variable() == STR(VARIABLE_LENGTH)) {
                      variable = CStringTools::ToString(data_cube->reg_length());
                    }
                  }
                }
              }
            }
            break;
          default:
            break;
        }
      }
    }

    if (null_data) {
      std::cout << "Access to data of size 0..." << std::endl;
    }

    return ret;
  }

  enum DataHelperAction {
    COMPARE_TO_OBJECT,
    COMPARE_TO_STRING,
    COPY_FROM_OBJECT,
    COPY_FROM_STRING
  };

  template <class T>
  static
  ComparisonType CopyOrCompare(DataHelperAction action,
                               CDataAccess *this_info,
                               CDataAccess *ref_info,
                               const std::string &this_variable,
                               const std::string &ref_variable,
                               T type) {
    ComparisonType ret = ComparisonType::UNDEFINED;

    IDataValue<T>  *this_obj_value  = NULL;
    IDataValue<T>  *ref_obj_value  = NULL;
    IDataVector<T> *this_obj_vector = NULL;
    IDataVector<T> *ref_obj_vector = NULL;
    IDataMatrix<T> *this_obj_matrix = NULL;
    IDataMatrix<T> *ref_obj_matrix = NULL;
    IDataCube<T>   *this_obj_cube   = NULL;
    IDataCube<T>   *ref_obj_cube   = NULL;

    if (this_info->data_object() == NULL) {
      // TODO(jjene) Constant
      std::cout << "Data not in Data Manager..." << std::endl;
    }
    else {
      switch(this_info->data_object()->collection()) {
      case CollectionType::PRIMITIVE:
        this_obj_value = static_cast<IDataValue<T> *>(this_info->data_object());
        ref_obj_value = static_cast<IDataValue<T> *>(ref_info->data_object());
        switch(action) {
          case COPY_FROM_OBJECT:
            this_obj_value->Copy(*ref_obj_value);
            break;
          case COPY_FROM_STRING:
            this_obj_value->set_value_string(ref_variable);
            break;
          case COMPARE_TO_OBJECT:
            ret = this_obj_value->Compare(*ref_obj_value);
            break;
          default:
            break;
        }
        break;
      case CollectionType::VECTOR:
        this_obj_vector = static_cast<IDataVector<T> *>(this_info->data_object());
        ref_obj_vector = static_cast<IDataVector<T> *>(ref_info->data_object());
        switch(action) {
          case COPY_FROM_OBJECT:
            this_obj_vector->Copy(*ref_obj_vector);
            break;
          case COPY_FROM_STRING:
            this_obj_vector->set_data_string(ref_variable);
            break;
          case COMPARE_TO_OBJECT:
            ret = this_obj_vector->Compare(*ref_obj_vector);
            break;
          case COMPARE_TO_STRING:
            ret = CDataHelper::Compare(
            (this_variable == "")?this_obj_vector->GetDataString():this_variable,
            (ref_variable == "")?ref_obj_vector->GetDataString():ref_variable
            );
            break;
          default:
            break;
        }
        break;
      case CollectionType::MATRIX:
        this_obj_matrix = static_cast<IDataMatrix<T> *>(this_info->data_object());
        ref_obj_matrix = static_cast<IDataMatrix<T> *>(ref_info->data_object());
        switch(action) {
          case COPY_FROM_OBJECT:
            this_obj_matrix->Copy(*ref_obj_matrix);
            break;
          case COPY_FROM_STRING:
            this_obj_matrix->set_data_string(ref_variable);
            break;
          case COMPARE_TO_OBJECT:
            ret = this_obj_matrix->Compare(*ref_obj_matrix);
            break;
          case COMPARE_TO_STRING:
            ret = CDataHelper::Compare(
            (this_variable == "")?this_obj_matrix->GetDataString():this_variable,
            (ref_variable == "")?ref_obj_matrix->GetDataString():ref_variable
            );
            break;
          default:
            break;
        }
        break;
      case CollectionType::CUBE:
        this_obj_cube = static_cast<IDataCube<T> *>(this_info->data_object());
        ref_obj_cube = static_cast<IDataCube<T> *>(ref_info->data_object());
        switch(action) {
          case COPY_FROM_OBJECT:
            this_obj_cube->Copy(*ref_obj_cube);
            break;
          case COPY_FROM_STRING:
            this_obj_cube->set_data_string(ref_variable);
            break;
          case COMPARE_TO_OBJECT:
            ret = this_obj_cube->Compare(*ref_obj_cube);
            break;
          case COMPARE_TO_STRING:
            ret = CDataHelper::Compare(
            (this_variable == "")?this_obj_cube->GetDataString():this_variable,
            (ref_variable == "")?ref_obj_cube->GetDataString():ref_variable
            );
            break;
          default:
            break;
        }
        break;
      default:
        break;
      }
    }

    return ret;
  }

  static
  bool IsADataOrValueField(std::string variable, CollectionType data_type_key) {
    bool ret = false;

    switch(data_type_key) {
      case CollectionType::PRIMITIVE:
        ret = ((variable == "") || (variable == STR(VARIABLE_VALUE)));
        break;
      case CollectionType::VECTOR:
      case CollectionType::MATRIX:
      case CollectionType::CUBE:
        ret = ((variable == "") || (variable == STR(VARIABLE_DATA)));
        break;
      default:
        break;
    }
    return ret;
  }

  /**
   * Example of same master types ("data", "value"):
   *    mat1 = mat2
   *    vec1.data = vec2.data
   *    vec1 == vec2.data
   *    x.value == y.value
   *    x = y.value
   *
   * Not same master types:
   *    vec1.reg_length = vec.reg_length
   *    vec = y
   */
  template <class T>
  static
  bool BothReferencesOfTheSameMasterType(CDataAccess *this_info,
                                         T *this_value,
                                         const std::string &this_variable,
                                         CDataAccess *ref_info,
                                         T *ref_value,
                                         const std::string &ref_variable) {
    return (
      /**
       * Null because it is not pointer to vector/matrix/cube a position:
       */
      (this_value == NULL) &&
      (ref_value == NULL) &&

      /**
       * Both are of the same type:
       */
      (this_info->data_object()->collection() ==
       ref_info->data_object()->collection()) &&

      /**
       * Both are ferering to STR(VARIABLE_VALUE) or STR(VARIABLE_DATA)
       */
      (CDataHelper::IsADataOrValueField(this_variable,
                                      this_info->data_object()->collection())
                                      == true) &&
      (CDataHelper::IsADataOrValueField(ref_variable,
                                      ref_info->data_object()->collection())
                                      == true)
      );
  }

  /**
   * Temporary solution:
   *
   * Substract dec to val.
   * val can only be int / long int / float / double
   */
  static void ArithmeticalOperation(std::string value_str, double &val, SetAction action) {
    double dec = 0;
    std::istringstream ss1(value_str);
    ss1 >> dec;

    switch(action) {
      case SetAction::REPLACE_VALUE: val = dec; break;
      case SetAction::ADD_VALUE: val += dec; break;
      case SetAction::SUBSTRACT_VALUE: val -= dec; break;
      case SetAction::MULTIPLY_VALUE: val *= dec; break;
      case SetAction::DIVIDE_VALUE: val /= dec; break;
      default: break;
    }
  }
  static void ArithmeticalOperation(std::string value_str, int &val, SetAction action) {
    double aux = static_cast<double>(val);
    ArithmeticalOperation(value_str, aux, action);
    val = static_cast<int>(aux);
  }
  static void ArithmeticalOperation(std::string value_str, long int &val, SetAction action) {
    double aux = static_cast<double>(val);
    ArithmeticalOperation(value_str, aux, action);
    val = static_cast<long int>(aux);
  }
  static void ArithmeticalOperation(std::string value_str, float &val, SetAction action) {
    double aux = static_cast<double>(val);
    ArithmeticalOperation(value_str, aux, action);
    val = static_cast<float>(aux);
  }
  static void ArithmeticalOperation(std::string value_str, std::string &val, SetAction action) {
    switch(action) {
      case SetAction::REPLACE_VALUE: val = value_str; break;
      case SetAction::ADD_VALUE: val += value_str; break;
      default: break;
    }
  }
  static void ArithmeticalOperation(std::string value_str, bool &val, SetAction action) {
    value_str = CStringTools::ToUpper(value_str);
    bool value = true;
    if ((value_str == "TRUE") || (value_str == "1")) {
      value = true;
    }
    if ((value_str == "FALSE") || (value_str == "0")) {
      value = false;
    }
    switch(action) {
      case SetAction::REPLACE_VALUE: val = value; break;
      default: break;
    }
  }
  static void ArithmeticalOperation(std::string value_str, char &val, SetAction action) {
    char ch = '\x0';
    if (value_str != "") {
      ch = value_str.at(0);
    }
    switch(action) {
      case SetAction::REPLACE_VALUE: val = ch; break;
      default: break;
    }
  }


  template <class T>
  static
  bool Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action, T type) {
    bool set = false;

    /**
     * GetReferenceValue uses the information about where to get the data and
     * where to put the data and it returns pointers to these two paces:
     */
    std::string this_variable;
    std::string ref_variable;

    T *this_value = CDataHelper::GetReferenceValue(this_info, this_variable, T());
    T *ref_value = CDataHelper::GetReferenceValue(ref_info, ref_variable, T());

    /**
     * When all references are empty and both objects are of the same type that
     * means that one IData must be copied to the other IData:
     */

    if ((this_info->data_object() != NULL) &&
        (ref_info->data_object() != NULL) &&
        (CDataHelper::BothReferencesOfTheSameMasterType(this_info,
                                                        this_value,
                                                        this_variable,
                                                        ref_info,
                                                        ref_value,
                                                        ref_variable))) {
      CDataHelper::CopyOrCompare(DataHelperAction::COPY_FROM_OBJECT,
                                 this_info,
                                 ref_info,
                                 "",
                                 "",
                                 type);
      set = true;
    } else {
      if (this_value != NULL) {
        /**
         * Copy to a data position or value:
         */
        if (ref_value != NULL) {
          ref_variable = CStringTools::ToString(*ref_value);
        }

        /**
         * Convert data from string to T:
         */
        ArithmeticalOperation(
                              ref_variable,
                              (*this_value),
                              action);

        set = true;
      } else {
        /**
         * Copy from string to the whole object: (for example:
         * the string "1 2 3 4" to a vector.
         */

        // ---------------------------------------------------------------------
        // This does not work
        // ---------------------------------------------------------------------
        /*
        if (ref_value != NULL) {
          ref_variable = *ref_value;
        }
        */
        // ---------------------------------------------------------------------

        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Alternative way to do the same but ugly:
        // Call again to GetReferenceValue but ensuring that the function knows
        // that we want an output of type "std::string".
        // TODO(jjene) To be improved.
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        std::string type_string = "";
        std::string *str_ref_value = NULL;
        str_ref_value = CDataHelper::GetReferenceValue(ref_info,
                                                       ref_variable,
                                                       type_string);
        if (str_ref_value != NULL) {
          ref_variable = *str_ref_value;
        }
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        CDataHelper::CopyOrCompare(DataHelperAction::COPY_FROM_STRING,
                                   this_info,
                                   ref_info,
                                   this_variable,
                                   ref_variable,
                                   type);
        set = true;
      }
    }
    return set;
  }

  template <class T>
  static
  ComparisonType Compare(CDataAccess *this_info, CDataAccess *ref_info, T type) {
    ComparisonType ret = ComparisonType::UNDEFINED;

    std::string this_variable;
    std::string ref_variable;

    /**
     * GetReferenceValue uses CDataAccess information for getting one pointer
     * for every place that it is the data:
     */
    T *this_value = CDataHelper::GetReferenceValue(this_info, this_variable, T());
    T *ref_value = CDataHelper::GetReferenceValue(ref_info, ref_variable, T());

    /**
     * When all references are empty and both objects are of the same type that
     * means that one IData must be compared with the other IData:
     */
    if ((this_info->data_object() != NULL) &&
        (ref_info->data_object() != NULL) &&
        (CDataHelper::BothReferencesOfTheSameMasterType(this_info,
                                                        this_value,
                                                        this_variable,
                                                        ref_info,
                                                        ref_value,
                                                        ref_variable))) {
      ret = CDataHelper::CopyOrCompare(DataHelperAction::COMPARE_TO_OBJECT,
                                       this_info,
                                       ref_info,
                                       this_variable,
                                       ref_variable,
                                       type);
    } else {
      /*
       * In both cases, the data could be (in this order): in ref_value or
       * in ref_variable.
       */

      if (this_value != NULL) {
        this_variable = CStringTools::ToString(*this_value);
      }

      if (ref_value != NULL) {
        ref_variable = CStringTools::ToString(*ref_value);
      }


      /**
       * Comparison between A and B: where one of them is an string and the
       * other is the whole object:
       *
       * For example:
       *     if vec == "1 2 3 4"
       *     if mat == "1 2;3 4"
       *     if "1 2 3 4" == vec
       *     if "1 2;3 4" == mat
       *
       * In this case, the one that is not an string is converted to an string
       * to be compared.
       *
       * Trick: one of them has *_value = NULL and
       *        the other has *_variable != NULL.
       */
      if (((this_value == NULL) && (ref_value == NULL) && (ref_variable != "")) ||
          ((ref_value == NULL) && (this_value == NULL) && (this_variable != ""))) {
        ret = CDataHelper::CopyOrCompare(DataHelperAction::COMPARE_TO_STRING,
                                         this_info,
                                         ref_info,
                                         this_variable,
                                         ref_variable,
                                         type);
      } else {
        /**
         * Comparison between two values.
         * Let's convert them to their original types "T".
         */
//       if ((this_variable != "") && (ref_variable != "")) {
        if (typeid(std::string) == typeid(T)) {
          ret = CDataHelper::Compare(this_variable, ref_variable);
        } else {
          T a = T();
          T b = T();
          std::istringstream ss1(this_variable);
          ss1 >> a;
          std::istringstream ss2(ref_variable);
          ss2 >> b;

          ret = CDataHelper::Compare(a, b);
        }
      }
//      }

    }

    return ret;
  }
 };

#endif
