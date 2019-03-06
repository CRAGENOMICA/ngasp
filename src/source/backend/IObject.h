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
 *  \brief     IObject.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 7, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef IOBJECT_H_
#define IOBJECT_H_

#include <iostream>
#include <string>
#include <sstream>  // ostringstream
#include <typeinfo>
#include <iomanip>  // std::setprecision

#include "language/CStringTable.h"
#include "util/CStringTools.h"
#include "data_manager/common/CDataAccess.h"
#include "CManager.h"

enum SetAction {
  SET_ACTION_UNDEFINED = 0,
  REPLACE_VALUE,
  ADD_VALUE,
  SUBSTRACT_VALUE,
  MULTIPLY_VALUE,
  DIVIDE_VALUE,
  APPEND_INDEX_VALUE
};

enum PrintMode {
    NORMAL = 0,       // Print the variable to be shown in a console
    JSON   = 1,       // Print the variable as a json object
    NGASP  = 2,       // Print the variable as an ngasp command
    VALUE  = 3,       // Print only the value without tables, labels, ...
    STRING_VALUE = 4, // Same as VALUE but with quotes
};

class IObject {
 public:
  IObject();
  IObject(const std::string &name);
  virtual ~IObject();


private:
  IObject *parent_;
  KeyString group_;
  std::string name_;
  KeyString type_;
  KeyString status_;

 public:
  void Copy(const IObject &ref) {
    set_parent(ref.parent());
    set_group(ref.group());
    set_name(ref.name());
    set_type(ref.type_key());
    set_status(ref.status_key());    
  }
  
public:  
  inline IObject *GetPointerToTheObject(void) { return this; }
    
  inline IObject *parent() const { return parent_; }
  inline void set_parent(IObject *parent) { parent_ = parent; }  

  inline KeyString group() const { return group_; }
  inline void set_group(const KeyString group) {
    group_ = group;
  }

  inline std::string name() const { return name_; }
  inline void set_name(const std::string name) { name_ = name; }

  
  inline std::string full_name() const { 
      std::string ret = (parent() != NULL)?(parent()->full_name() + "/"):"";
      return ret + name();
  };
  
  inline std::string type() const { return STR2(type_); }
  KeyString type_key() const { return type_; }
  inline void set_type(const KeyString type) { type_ = type; }

  inline std::string status() const { return STR2(status_); }
  KeyString status_key() const { return status_; }
  inline void set_status(const KeyString status) {
    status_ = status;
  }

 public:
  /**
   * Child classes must override this function for showing its contents.
   * They also must call IObject::Print(); as its first function code line
   * in order to let this object to print the header.
   */
  virtual void Print(PrintMode print_mode) = 0;

  /**
   * Child classes must implement this function.
   * They must return its own size in bytes.
   * @return
   */
  virtual std::size_t Size(void) const = 0;

  /**
   * Child classes must implement this function for setting values to their
   * member variables.
   * @return
   */
  virtual void Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action) = 0;


//  /**
//   * Child classes must implement this function for getting values from their
//   * member variables.
//   * @return
//   */
//  virtual void Get(CDataAccess *data_access) = 0;





 protected:
  //@{
  /**
   * Functions for PRINT
   */
  int PrintHeader(PrintMode print_mode);
  void PrintFooter(PrintMode print_mode);
  void PrintCommon(const std::string &var_name,
                   const std::string &type,
                   const std::ostringstream &value_string,
                   int col_width,
                   PrintMode print_mode);


  // ===========================================================================
  // BASIC TYPES
  // ===========================================================================

  template<class T>
  void PrintValue(const std::string &var_name,
                 const T &value,
                 int col_width,
                 int precision,
                 PrintMode print_mode) {
    if (print_mode == PrintMode::JSON) {
        // std::cout << "\"value\":\"" << value << "\"";
    } else {
        if (print_mode == PrintMode::NGASP) {
            std::cout << value << "\"";
        } else {
            if (print_mode == PrintMode::STRING_VALUE) {
              std::cout << "'";
            }
            
            std::ostringstream value_string;
          //  if ((value == "")&&(T = std::string)) {
          //    value_string << STR(TABLE_EMPTY_FIELD);
          //  }

          //  if value == double or float:
            value_string << std::fixed << std::setprecision(precision) << value;
          //else
          //value_string << value;

            if (print_mode == PrintMode::STRING_VALUE) {
              std::cout << "'";
            }
            
           PrintCommon(var_name, type(), value_string, col_width, print_mode);
        }
    }
  }


  // ===========================================================================
  // VECTORS
  // ===========================================================================
  template<class T>
  void PrintVector(const std::string &var_name,
                   const T *data, std::size_t len,
                   int col_width, int precision,
                   int table_col_width,
                   PrintMode print_mode) {
    if (print_mode == PrintMode::JSON) {
//      std::cout << "\"data\":";
//      std::cout << "[";
//      for (int i=0; i<len; i++) {
//        if (i!=0) std::cout << ",";
//        std::cout << data[i];
//      }
//      std::cout << "]";
    } else {
        if (print_mode == PrintMode::NGASP) {
          for (std::size_t i=0; i<len; i++) {
            if (i!=0) std::cout << ",";
            std::cout << data[i];
          }
          std::cout << "\"";
        } else {
          std::ostringstream value_string;
          if (data != NULL) {
            for (std::size_t i=0; i<len; i++) {
              if (i != 0) {
                value_string << STR(TABLE_ARRAY_SEPARATOR);
              }
              value_string << std::fixed << std::setprecision(precision) << data[i];
              //If char:
              //value_string << std::fixed << data[i];
            }
          } else {
            value_string << STR(TABLE_EMPTY_FIELD);
          }

          PrintCommon(var_name, STR(DATA_FLOAT_VECTOR), value_string, col_width, print_mode);
        }
    }
  }

  template<class T>
  void PrintVectorAsMatrix(const std::string &var_name,
                            const T *data,
                            long int width, long int height,
                            int col_width,
                            int table_col_width,
                            PrintMode print_mode) {
    if (print_mode == PrintMode::JSON) {
//        std::cout << "\"data\":";
//        std::cout << "[";
//        for (long int j=0; j<height; j++) {
//          if (j!=0) std::cout << ",";
//          std::cout << "[";
//          for (long int i=0; i<width; i++) {
//            if (i!=0) std::cout << ",";
//            std::cout << data[j*width + i];
//          }
//          std::cout << "]";
//        }
//        std::cout << "]";
    } else {
        if (print_mode == PrintMode::NGASP) {
            for (long int j=0; j<height; j++) {
              for (long int i=0; i<width; i++) {
                if (i!=0) std::cout << ",";
                std::cout << data[j*width + i];
              }
              std::cout << ";";
            }
            std::cout << "\"";
        } else {
          std::cout << CStringTools::PrepareField(var_name, col_width, false, false);
          std::cout << CStringTools::PrepareField("", col_width, false, false);

          std::ostringstream value_string;
          if (data != NULL) {
            std::cout << STR(EOL);
            for (long int j=0; j<height; j++) {
              value_string << STR(TABLE_COL_MARGIN);
              for (long int i=0; i<width; i++) {
                if (i != 0) {
                  value_string << STR(TABLE_ARRAY_SEPARATOR);
                }
                value_string << CStringTools::ToNDigits(data[j*width + i], table_col_width, ' ');
              }
              value_string << STR(EOL);
            }
          } else {
            value_string << STR(TABLE_COL_MARGIN);
            value_string << STR(TABLE_EMPTY_FIELD);
            value_string << STR(EOL);
          }

          std::cout << value_string.str();
        }
    }
  }

  // ===========================================================================
  // MATRICES
  // ===========================================================================
  template<class T>
  void PrintMatrix(std::string var_name,
                   T **data,
                   std::string type,
                   long int *reg_length, long int regs,
                   int col_width,
                   int table_col_width,
                   PrintMode print_mode = PrintMode::NORMAL) {
    if (print_mode == PrintMode::JSON) {
//      std::cout << "\"data\":";
//      std::cout << "[";
//      for (long int reg = 0; reg < regs; reg++) {
//        if (reg!=0) std::cout << ",";
//        std::cout << "[";
//        for (long int col = 0; col < reg_length[reg]; col++) {
//          if (col!=0) std::cout << ",";
//          std::cout << data[reg][col];
//        }
//        std::cout << "]";
//      }
//      std::cout << "]";
    } else {
        if (print_mode == PrintMode::NGASP) {
          for (long int reg = 0; reg < regs; reg++) {
            for (long int col = 0; col < reg_length[reg]; col++) {
              if (col!=0) std::cout << ",";
              std::cout << data[reg][col];
            }
            std::cout << ";";
          }
          std::cout << "\"";
        } else {
          std::cout << CStringTools::PrepareField(var_name, col_width, false, false);
          std::cout << CStringTools::PrepareField(type, col_width, false, false);

          std::ostringstream value_string;
          if (data != NULL) {
            std::cout << STR(EOL);
             for (long int reg = 0; reg < regs; reg++) {
              value_string << STR(TABLE_COL_MARGIN);
              for (long int col = 0; col < reg_length[reg]; col++) {
                //value_string << CStringTools::ToNDigits(data[reg * reg_length + col]-48, table_col_width, ' ');
                value_string << CStringTools::ToNDigits(data[reg][col], table_col_width, ' ');
              }
              value_string << std::endl; //STR(EOL);
            }
          } else {
            value_string << STR(TABLE_COL_MARGIN);
            value_string << STR(TABLE_EMPTY_FIELD);
            value_string << STR(EOL);
          }

          std::cout << value_string.str();
        }
    }
  }


 protected:
  void EvalSet(CManager *manager, bool set, CDataAccess *this_info, CDataAccess *ref_info);
  void EvalGet(CManager *manager, bool get, CDataAccess *data_access);


  template <class T>
  T *Delete(T *data) {
    if (data != NULL) {
      delete[] data;
      data = NULL;
    }
    return data;
  }

  template <class T>
  T **Delete(T **data, long int regs) {
    if (data != NULL) {
      for (long int i=0; i<regs; i++) {
        delete[] data[i];
        data[i] = NULL;
      }
      delete[] data;
      data = NULL;
    }
    return data;
  }

  template <class T>
  T ***Delete(T ***data, long int tables, long int regs) {
    if (data != NULL) {
      for (long int t=0; t<tables; t++) {
        for (long int i=0; i<regs; i++) {
          delete[] data[t][i];
          data[t][i] = NULL;
        }
        delete[] data[t];
        data[t] = NULL;
      }
      delete[] data;
      data = NULL;
    }
    return data;
  }

};

#endif /* IOBJECT_H_ */
