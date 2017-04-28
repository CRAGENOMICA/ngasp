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
 *  \brief     CDataStringSet.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 4, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_DATA_MANAGER_DATA_CDATASTRSET_H_
#define BACKEND_SRC_DATA_MANAGER_DATA_CDATASTRSET_H_

#include <iostream>

//!prev_disabled
#include <seqan/sequence.h>
#include <seqan/file.h>
#include <seqan/basic.h>
#include <seqan/seq_io.h>
 
#include <string>
#include <cstdint>

#include "../IData.h"
#include "../../data_manager/common/CDataAccess.h"


class CDataStringSet : public IData {
 public:
  CDataStringSet();
  virtual ~CDataStringSet();

  IData * clone() const { return new CDataStringSet(); /*clone*/ }

 public:
  void Print(PrintMode print_mode) override;
  std::size_t Size(void) const;
  void Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action);
  void Get(CDataAccess *data_access);


 public:
  // typedef seqan::Dna5String TBase;  // ATGCN
   
  //!prev_disabled
  typedef seqan::String<char> TBase;   // ATGCN-Y....
  seqan::StringSet<TBase > data_;

  long int regs_;
  long int reg_length_;

  //!prev_disabled
  typedef seqan::Iterator<seqan::StringSet<CDataStringSet::TBase> >::Type
    TStringSetIterator;

 public:
  //!prev_disabled
  inline TStringSetIterator Begin(void) {
    return seqan::begin(data_);
  }
  inline TStringSetIterator End(void) {
    return seqan::end(data_);
  }
  inline seqan::StringSet<TBase > data(void) { return data_; }
  inline void set_data(seqan::StringSet<TBase > data) { data_ = data; }

  
  
  inline long int  regs(void) const { return regs_; }
  inline void set_regs(long int  regs) { regs_ = regs; }

  inline long int  reg_length(void) const { return reg_length_; }
  inline void set_reg_length(long int  reg_length) { reg_length_ = reg_length; }

  /**
   * JSON
   */
  std::string ToJSON(void) {
    std::string ret;

    // To Be Developed

    return ret;
  }
};

#endif  // BACKEND_SRC_DATA_MANAGER_DATA_CDATASTRSET_H_
