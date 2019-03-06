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
 *  \brief     CDataSequenceIndex.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_DATA_MANAGER_COMMON_CDATASEQUENCEINDEX_H_
#define BACKEND_SRC_DATA_MANAGER_COMMON_CDATASEQUENCEINDEX_H_

#include <cstdint>

struct CDataSequenceIndex {
 private:
  uintmax_t first_base_position_;
  uintmax_t last_base_position_;
  uintmax_t last_index_;

 public:
  CDataSequenceIndex() { 
    first_base_position_ = 0;
    last_base_position_  = 0;
    last_index_          = 0;
  }
  
  CDataSequenceIndex(uintmax_t first_base_position,
                     uintmax_t last_base_position,
                     uintmax_t last_index) {
    first_base_position_ = first_base_position;
    last_base_position_  = last_base_position;
    last_index_          = last_index;
  }
  
  CDataSequenceIndex(const CDataSequenceIndex & other) {
    first_base_position_ = other.first_base_position();
    last_base_position_  = other.last_base_position();
    last_index_          = other.last_index();
  }
  
  inline uintmax_t first_base_position(void) const {
    return first_base_position_;
  }
  inline void set_first_base_position(const uintmax_t & first_base_position) {
    first_base_position_ = first_base_position;
  }
  
  inline uintmax_t last_base_position(void) const {
    return last_base_position_;
  }
  inline void set_last_base_position(const uintmax_t & last_base_position) {
    last_base_position_ = last_base_position;
  }
  
  inline uintmax_t last_index(void) const {
    return last_index_;
  }
  inline void set_last_index(const uintmax_t & last_index) {
    last_index_ = last_index;
  }
  inline void inc_last_index(void) {
    last_index_++;
  }
};

#endif  // BACKEND_SRC_DATA_MANAGER_COMMON_CDATASEQUENCEINDEX_H_