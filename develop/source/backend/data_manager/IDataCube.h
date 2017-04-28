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
 *  \brief     IDataCube.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 9, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATA_MANAGER_DATA_IDATACUBE_H_
#define	DATA_MANAGER_DATA_IDATACUBE_H_

#include <vector>
#include <string>
#include <sstream>
#include <assert.h>
#include <iterator>

#include "IData.h"
#include "../data_manager/common/CDataAccess.h"
#include "../util/CStringTools.h"
#include "IDataMatrix.h"


template<class T>
class IDataCube : public IData {
 private:
   std::vector<IDataMatrix<T> > data_;
   
 public:
  IDataCube(KeyString data_type_key,
            KeyString primitive)
  : IData(data_type_key, primitive, CollectionType::CUBE) {
  }

  IDataCube() {}
  
  IDataCube(const IDataCube<T> &ref) {
    Copy(ref);
  }
  
  ~IDataCube() {
    DeleteMemory();
  }

  IData * clone() const {
    return new IDataCube(type_key(),
                         primitive()); /*clone*/
  }
  
// =============================================================================
// ACCESSORS : 3 dimensions (reg_length x regs x tables)
// =============================================================================

 public:
  inline std::size_t tables(void) const { 
    return data_.size(); 
  }

  inline std::size_t regs(void) const { 
    return (data_.size() > 0)?data_.at(0).regs():0;
  }

  inline std::size_t reg_length(void) { 
    return (data_.size() > 0)?data_.at(0).reg_length():0;
  }
  
  /*
   * Size of the data.
   */
  std::size_t Size(void) const {
    std::size_t size = 0;
    
    for (auto it = data_.begin(); it != data_.end(); ++it) {
      size += (*it).Size();
    }

    return size;
  }
  
  /**
   * Input string format: "1 2 3 4;5 6 7 8"
   * Input string format: "1 2;3 4;5 6|1 2;3 4;5 6"
   * Last character is not a separator character
   */
  bool set_data_string(std::string data_string) {
    DeleteMemory();
    
    std::vector<std::string> elems = CStringTools::SplitStrings(
      data_string,
      STR(SEPARATORS)[CollectionType::CUBE]);
    
    // Allocate memory for "elements.size()" tables
    data_.resize(elems.size());
    
    // Every subclass will allocate its own memory:    
    for (std::size_t i = 0; i < elems.size(); i++) {
      data_.at(i).set_data_string(elems.at(i));
    }
      
    return true;
} 
  
 /**
   * From: std::vector = [[1 2 3 4][5 6 7 8]]
   * To:   std::string = "1 2 3 4;5 6 7 8"
   * Last character is not a separator character
   */
  std::string GetDataString(bool with_item_separators = true) {
    std::string ret;

    std::stringstream ss;
    
    for (std::size_t i = 0; i < data_.size(); i++) {
      if ((i != 0) && (with_item_separators)) {
        ss << STR(SEPARATORS)[CollectionType::CUBE];
      }
      ss << data_.at(i).GetDataString(with_item_separators);
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
  }
  
  /*
   * Allocate without initializing the data.
   */
  void ReserveMemory(std::size_t num_tables,
                     std::size_t num_regs,
                     std::size_t reg_len) {
    // Remove the current data
    DeleteMemory();

    // Allocate memory without initializing the data
    data_.resize(num_tables);
    
    for (std::size_t i = 0; i < tables(); i++) {
      data_.at(i).ReserveMemory(num_regs, reg_len);
    }    
  }

  /*
   * Allocate initializing the data.
   */
  void ReserveMemory(std::size_t num_tables,
                     std::size_t num_regs,
                     std::size_t reg_len,
                     T init_default_value) {
    // Remove the current data
    DeleteMemory();

    // Allocate memory without initializing the data
    // The initialization is done in the subclass
    data_.resize(num_tables);

    for (std::size_t i = 0; i < tables(); i++) {
      data_.at(i).ReserveMemory(num_regs, reg_len, init_default_value);
    }    
  }

  /*
   * Reserve more memory preserving the current memory and NOT initializing the
   * new one.
   */
  void ReallocMemory(std::size_t num_tables,
                     std::size_t num_regs,
                     std::size_t reg_len) {
    // Allocate memory without initializing the data
    data_.resize(num_tables);
    
    for (std::size_t i = 0; i < tables(); i++) {
      data_.at(i).ReserveMemory(num_regs, reg_len);
    }  
  }   

  /*
   * Reserve more memory preserving the current memory and initializing the
   * new one.
   */
  void ReallocMemory(std::size_t num_tables,
                     std::size_t num_regs,
                     std::size_t reg_len,
                     T init_default_value) {
    // Allocate memory initializing the data
    data_.resize(num_tables);

    for (std::size_t i = 0; i < tables(); i++) {
      data_.at(i).ReserveMemory(num_regs, reg_len, init_default_value);
    } 
  }   
  
  /**
   * Call this function if you have a cube of numbers and you want 
   * to replace all its values by init_default_value.
   * 
   * But if you create a new cube you can initialize all its elements
   * with "ReserveMemory" or "ReserveMemory". In this case, you do not need
   * to use this function.
   */
  void InitMemory(T init_default_value) {
    for (std::size_t i = 0; i < data_.size(); i++) {
      data_.at(i).InitMemory(init_default_value);
    }    
  }
  
// =============================================================================
// PRINTING DATA
// =============================================================================
  
 public:
  void Print(PrintMode print_mode) {
    int col_with = PrintHeader(print_mode);

    if (print_mode == PrintMode::NORMAL) {
      PrintValue(STR(READ_ONLY_PREFIX)+STR(VARIABLE_TABLES),
                 tables(),
                 col_with,
                 0,
                 print_mode);

      PrintValue(STR(READ_ONLY_PREFIX)+STR(VARIABLE_REGS),
                 regs(),
                 col_with,
                 0,
                 print_mode);

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
  
 public:
  void PrintData(PrintMode print_mode, int col_with = -1) {
    for (std::size_t i = 0; i < regs(); i++) {
      data_.at(i).PrintData(print_mode, col_with);
      
      if (i != regs() - 1) {
        std::cout << " ";
        std::cout << STR(SEPARATORS)[CollectionType::CUBE];
        std::cout << STR(EOL);
      }      
    }   
  }  
 
public:
  // ===========================================================================
  // ITERATION
  // ===========================================================================

  IDataMatrix<T> & operator[](std::size_t z) {
    assert(z < data_.size() && "assert(z < data_.size())");
    return data_.at(z);
  }

  const IDataMatrix<T> & operator[](std::size_t z) const {
    assert(z < data_.size() && "assert(z < data_.size())");
    return data_.at(z);
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
  bool operator==(const IDataCube<T> &ref) {
    return (Compare(ref) == ComparisonType::EQUAL);
  }

  ComparisonType Compare(IDataCube<T> &ref) {
    ComparisonType ret = ComparisonType::EQUAL;
    
    if (Size() == ref.Size()) {
      // Compare every subclass
      for (std::size_t i = 0; ((i < ref.Size()) &&
                               (ret == ComparisonType::EQUAL)); i++) {
        ret = data_[i].Compare(ref[i]);
      }        
    } else {
      ret = ComparisonType::NOT_EQUAL;
    }
    
    return ret;
  }
  
  ComparisonType Compare(CDataAccess *this_info, CDataAccess *ref_info);
  
  // ===========================================================================
  // COPY OBJECTS OF THE SAME CLASS
  // ===========================================================================
public: 
  IDataCube<T>& operator=(const IDataCube<T> &ref) {
    Copy(ref);
    return *this;
  }

  void Copy(const IDataCube<T> &ref) {
    DeleteMemory();
    
    // Copy hicheracy data members
    // ---------------------------

    IData::Copy(ref);
    
    // Copy data
    // ---------
    
    // Allocate memory for a cube of "ref.regs()" tables (matrices)
    data_.resize(ref.regs());
    
    // Copy every subclass
    for (std::size_t i = 0; i < ref.regs(); i++) {
      data_[i].Copy(ref[i]);
    }    
  }

  void Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action);
};

#endif  // DATA_MANAGER_DATA_IDATACUBE_H_

