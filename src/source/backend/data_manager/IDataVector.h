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
 *  \brief     IDataVector.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 20, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATA_MANAGER_DATA_IDATAVECTOR_H_
#define	DATA_MANAGER_DATA_IDATAVECTOR_H_


#include <vector>
#include <string>
#include <sstream>
#include <assert.h>
#include <iterator>
#include <algorithm>    // std::sort
#include <iterator>

#include "IData.h"
#include "../data_manager/common/CDataAccess.h"
#include "../util/CStringTools.h"
#include "IDataValue.h"
// #include "IDataValue.h"

//// To be abled to get the "precision" global variable:
//class CDataManager;
//#include "Data/CDataInt.h"

/*
 * Attention: 
 *   This class allocates one hidden extra char at the end of the vector.
 *   For example, if you do:
 *      ReserveMemory(4);
 *   Internally, 5 chars are reserved and the last one is set to '\x0'.
 *   If you call Size(), the function will return 4.
 *   Why? because if you call data() the last '\x0' is used to known the end 
 *   of the string. 
 */

template<class T>
class IDataVector : public IData {
 private:
   std::vector<T> data_;
   int EXTRA_CHAR;
   
 public:
     
  void RemoveValues(const IDataVector<T> & values) {
    std::size_t m = values.Size();
    typename std::vector<T>::iterator it;
    
    // Loop list of values to be removed
    for (std::size_t j = 0; j < m; j++) {
      // loop data_ for searching values to be removed
      it = data_.begin();
      while(it != data_.end()) {          
        if ((*it) == values[j]) {
          it = data_.erase(it);
        } else {
          ++it;
        }
      }
    }      
  }
     
  IDataVector(KeyString data_type_key,
              KeyString primitive)
  : IData(data_type_key, primitive, CollectionType::VECTOR) {
      
      if (data_type_key == KeyString::DATA_STD_STRING_VECTOR) {
          EXTRA_CHAR = 0;
      } else {
          EXTRA_CHAR = 1;
      }
  }
  
  IDataVector() {
      EXTRA_CHAR = 1;
  }

  IDataVector(const IDataVector<T> &ref) {
    Copy(ref);
  }
  
  ~IDataVector() {
    DeleteMemory();
  }

  IData * clone() const {
    return new IDataVector(type_key(),
                           primitive()); /*clone*/
  }

// =============================================================================
// ACCESSORS : 1 dimension (reg_length)
// =============================================================================
  
 public:
  /*
   * Size of the data.
   */
  std::size_t Size(void) const {
    return (data_.size()==0)?0:(data_.size() - EXTRA_CHAR);
  }
  
  /*
   * Direct access to the vector data.
   */
  T * GetData(void) {
    return data_.data();
  }

  inline std::size_t reg_length(void) { 
    return this->Size();
  }


  /**
   * Input string format: "1 2 3 4"
   * Last character is not a separator character
   * Result: data_=[1 2 3 4]
   */
  bool set_data_string(std::string data_string) {
    DeleteMemory();
    
    std::vector<std::string> elems = CStringTools::SplitStrings(
      data_string,
      STR(SEPARATORS)[CollectionType::VECTOR]);

    std::size_t i = 0;
    
    try
    {
      if ((elems.size() == 0) && (data_string != "")) {
        data_.resize(1 + EXTRA_CHAR);
        data_.at(0) = CStringTools::ToValue(data_string, data_.at(0));
        if (EXTRA_CHAR>0) { data_.at(1) = '\x0'; }
      } else {
        
        // Allocate memory for "elements.size()" vector elements
        data_.resize(elems.size() + EXTRA_CHAR);
        if (EXTRA_CHAR>0) { data_.at(elems.size()) = '\x0'; }
       
        for (i = 0; i < elems.size(); i++) {
          data_.at(i) = CStringTools::ToValue(elems.at(i), data_.at(i));
        }
      }
    }
    catch(std::invalid_argument e) {
      std::cout << "Exception: " << e.what() << std::endl;
      std::cout << "elems.at(i): " << elems.at(i) << std::endl;
      std::cout << "data_string: " << data_string << std::endl;
    }
    
    return true;
  } 

  /**
   * Input string format: "Joan"
   * Result: data_=[J o a n]
   */
  bool set_text_string(std::string data_string) {
    DeleteMemory();
    
    ReserveMemory(data_string.length());

    for (std::size_t i = 0; i < data_string.length(); i++) {
      data_.at(i) = static_cast<T>(data_string.at(i));
    }
            
    return true;
  }
  
 /**
   * From: std::vector = [1 2 3 4]
   * To:   std::string = "1 2 3 4"
   * Last character is not a separator character
   */
   const char * GetDataString(bool with_item_separators = true) {
    std::string ret;

    std::stringstream ss;
    
    for (std::size_t i = 0; i < data_.size(); i++) {
      if ((i != 0) && (with_item_separators)) {
        ss << STR(SEPARATORS)[CollectionType::VECTOR];
      }
      ss << data_.at(i);
    }
    
    ss << '\0';
    ret = ss.str();
    
    // This is important. Return c_str() converted to std::string ensures that
    // the std::string result can be compared with another std::string.
    return ret.c_str();    
  }
  
// =============================================================================
// MEMORY ALLOCATION
// =============================================================================
  
 public:
  void DeleteMemory(void) {
    data_.clear();
    std::vector<T>().swap(data_);
  }
  
  /*
   * Allocate without initializing the data.
   */
  void ReserveMemory(std::size_t reg_len) {
    // Remove the current data
    DeleteMemory();

    // Allocate memory without initializing the data
    data_.resize(reg_len + EXTRA_CHAR);
    if (EXTRA_CHAR>0) { data_.at(reg_len) = '\x0';  }
  }

  /*
   * Allocate initializing the data.
   */
  void ReserveMemory(std::size_t reg_len, T init_default_value) {
    // Remove the current data
    DeleteMemory();

    // Allocate memory initializing the data
    data_.resize(reg_len + EXTRA_CHAR, init_default_value);
    if (EXTRA_CHAR>0) { data_.at(reg_len) = '\x0'; }
  }

  /*
   * Reserve more memory preserving the current memory and NOT initializing the
   * new one.
   */
  void ReallocMemory(std::size_t reg_len) {
    // Allocate memory without initializing the data
    data_.resize(reg_len + EXTRA_CHAR);
    if (EXTRA_CHAR>0) { data_.at(reg_len) = '\x0'; }
  }    
  
  /*
   * Reserve more memory preserving the current memory and initializing the
   * new one.
   */
  void ReallocMemory(std::size_t reg_len, T init_default_value) {
    // Allocate more memory initializing the new data
    data_.resize(reg_len + EXTRA_CHAR, init_default_value);
    if (EXTRA_CHAR>0) { data_.at(reg_len) = '\x0'; }
  } 

  /**
   * Call this function if you have a vector of numbers and you want 
   * to replace all its values by init_default_value.
   * 
   * But if you create a new vector you can initialize all its elements
   * with "ReserveMemory" or "ReserveMemory". In this case, you do not need
   * to use this function.
   */
  void InitMemory(T init_default_value) {
    for (std::size_t i = 0; i < data_.size(); i++) {
      data_.at(i) = init_default_value;
    }    
  }
  
// =============================================================================
// PRINTING DATA
// =============================================================================
  
 public:
  void Print(PrintMode print_mode) {
    if ((print_mode == PrintMode::VALUE) || (print_mode == PrintMode::STRING_VALUE)) {
//      CDataInt *precision = (CDataInt *)manager()->data_manager()->GetDataByName(
//                                                                    NULL, // precision is a global variable. So, NULL(ROOT_PARENT)
//                                                                    STR(PRECISION));
//    
//      std::cout.precision(precision->value());
        
      std::cout.precision(10);
      std::cout << std::fixed;
      
      for (std::size_t i = 0; i < Size(); i++) {
        std::cout << STR(QUOTE) << data_[i] << STR(QUOTE);
        if (i != Size()-1) {
          std::cout << STR(SEPARATORS)[CollectionType::VECTOR];
        }
      }
    } else {      
      int col_with = PrintHeader(print_mode);

      if (print_mode == PrintMode::NORMAL) {
        PrintValue(STR(READ_ONLY_PREFIX)+STR(VARIABLE_LENGTH),
                   reg_length(),
                   col_with,
                   0,
                   print_mode);
      }

      PrintData(print_mode, col_with);
      std::cout << STR(EOL);

      PrintFooter(print_mode);
    }
  }

  std::string ToJSON(void) {
    std::string ret;

    ret += "{\"id\":\"";
    ret += name();
    ret += "\",\"type\":\"";
    ret += type();
    ret += "\",";

    ret += "\"value\":[";
    
    ret += GetValues();
    
    ret += "]";
    ret += "}";
    
    return ret;
  }

  std::string GetValues(void) {
    std::string ret;

    for (std::size_t i = 0; i < Size(); i++) {
      ret += "\"";
      ret += CStringTools::ToString(data_[i]);
      ret += "\"";
      if (i != Size()-1) {
        ret += STR(SEPARATORS)[CollectionType::VECTOR];
      }
    }
    
    return ret;
  }
  
 public:
  void PrintData(PrintMode print_mode, int col_with = -1) {
    if (col_with == -1) {
      col_with = PrintHeader(print_mode);
    }
    
    //int table_col_width = 1;
    
    std::cout << " ";
    for (std::size_t i = 0; i < Size(); i++) {
      std::cout << data_[i];
      if (i != Size()-1) {
        std::cout << STR(SEPARATORS)[CollectionType::VECTOR];
      }
    }
    
    
//    PrintVector(STR(READ_ONLY_PREFIX)+STR(VARIABLE_DATA),
//                  data_.data(),
//                  reg_length(),
//                  col_with,
//                  0,
//                  table_col_width,
//                  print_mode);
  }

 
public:
  // ===========================================================================
  // ITERATION
  // ===========================================================================

  T& operator[](std::size_t x) {
    //assert(x < data_.size() && "assert(x < data_.size())");
    return data_[x];
  }

  const T& operator[](std::size_t x) const {
    assert(x < data_.size() && "assert(x < data_.size())");
    return data_[x];
  }
 

  T* operator+(std::size_t x) {
    return &(this->operator [](x));
  }  


  class iterator
  {
      public:
          typedef iterator self_type;
          typedef T value_type;
          typedef T& reference;
          typedef T* pointer;
          typedef std::forward_iterator_tag iterator_category;
          typedef int difference_type;
          iterator(pointer ptr) : ptr_(ptr) { }
          self_type operator++() { self_type i = *this; ptr_++; return i; }
          self_type operator++(int junk) { ptr_++; return *this; }
          reference operator*() { return *ptr_; }
          pointer operator->() { return ptr_; }
          bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
          bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
      private:
          pointer ptr_;
  }; 
  
  class const_iterator
  {
      public:
          typedef const_iterator self_type;
          typedef T value_type;
          typedef T& reference;
          typedef T* pointer;
          typedef int difference_type;
          typedef std::forward_iterator_tag iterator_category;
          const_iterator(pointer ptr) : ptr_(ptr) { }
          self_type operator++() { self_type i = *this; ptr_++; return i; }
          self_type operator++(int junk) { ptr_++; return *this; }
          const reference operator*() { return *ptr_; }
          const pointer operator->() { return ptr_; }
          bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
          bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
      private:
          pointer ptr_;
  };

  iterator begin() {
    return iterator(data_.data());
  }

  iterator end() {
    return iterator(data_.data() + reg_length());
  }

  const_iterator begin() const
  {
    return const_iterator(data_.data());
  }

  const_iterator end() const
  {
    return const_iterator(data_.data() + reg_length());
  }
  
  // ===========================================================================
  // COMPARISON
  // ===========================================================================
public:
  bool operator==(const IDataVector<T> &ref) {
    return (Compare(ref) == ComparisonType::EQUAL);
  }

  ComparisonType Compare(IDataVector<T> &ref) {
    ComparisonType ret = ComparisonType::EQUAL;

    if (Size() == ref.Size()) {
      // Compare every item
      for (std::size_t i = 0; ((i < ref.Size()) && 
                               (ret == ComparisonType::EQUAL)); i++) {
        if (data_[i] != ref[i]) {
          ret = ComparisonType::NOT_EQUAL;
        }
      }
    }
    
    return ret;
  }

  ComparisonType Compare(CDataAccess *this_info, CDataAccess *ref_info);
  
  // ===========================================================================
  // COPY OBJECTS OF THE SAME CLASS
  // ===========================================================================
public: 
  IDataVector<T>& operator=(const IDataVector<T> &ref) {
    Copy(ref);
    return *this;
  }

  void Copy(const IDataVector<T> &ref) {
    DeleteMemory();
    
    // Copy hicheracy data members
    // ---------------------------

    IData::Copy(ref);
    
   
    // Copy data
    // ---------

    this->EXTRA_CHAR = ref.EXTRA_CHAR;
    
    // Allocate memory for "ref.Size()" vector elements
    data_.resize(ref.Size() + EXTRA_CHAR);
    
    // Copy every item
    for (std::size_t i = 0; i < ref.Size(); i++) {
      data_[i] = ref[i];
    }
    
    if (EXTRA_CHAR>0) {
        data_.at(ref.Size()) = '\x0';   
    }

    // #include <algorithm>  // equal
    // std::copy(ref.begin(), ref.end(), begin());
  }
  
  void Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action);
  
  
  void Append(IDataVector<T> &ref) {
      std::size_t previous_size = Size();
    // Allocate memory for new ref elements 
    // Note: Size() does not return EXTRA_CHAR. So, EXTRA_CHAR is added at the end:
    data_.resize(previous_size + ref.Size() + EXTRA_CHAR);
    
    // Copy ref elements at the end
    std::size_t j = 0;
    for (std::size_t i = previous_size; i < Size(); i++) {
      data_[i] = ref[j];
      j++;
    }   
    if (EXTRA_CHAR>0) {
        data_.at(Size()) = '\x0';
    }
  }

  void PushBack(const T & new_value) {
    data_.push_back(new_value);
  }
    
 bool   FindValue(const T & new_value) {
     return (std::find(data_.begin(), data_.end(), new_value) != data_.end());
 }
  // Only adds the value if it does not exist
  bool UniquePushBack(const T & new_value) {
      bool bRet = false;
    if (FindValue(new_value) == false) {
      data_.push_back(new_value);
      bRet = true;
    }
      
      return bRet;
  }
  
  void Sort(void) {
    // Example: 5,3,4,1,2,\x0
      
    // using default comparison (operator <):
    std::sort (data_.begin(), data_.begin() + Size());
    // Example: 1,2,3,4,5,\x0

//    // using function as comp
//    std::sort (myvector.begin(), myvector.end(), myfunction);
//
//    // using object as comp
//    std::sort (myvector.begin(), myvector.end(), myobject);
  }
};

#endif  // DATA_MANAGER_DATA_IDATAVECTOR_H_


