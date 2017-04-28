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
 *  \brief     CDataStringSet.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 4, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CDataStringSet.h"

#include <iostream>
#include <string>
#include <cstdint>

#include "../../language/CStringTable.h"
#include "../IData.h"
#include "../../data_manager/common/CDataAccess.h"


CDataStringSet::CDataStringSet()
: IData(KeyString::DATA_STRING_SET,
        KeyString::DATA_STRING_SET,
        CollectionType::PRIMITIVE) {
}

CDataStringSet::~CDataStringSet() {
}

void CDataStringSet::Print(PrintMode print_mode) {
  int col_width = PrintHeader(print_mode);
  PrintValue(STR(READ_ONLY_PREFIX)+STR(VARIABLE_REGS), regs_, col_width, 0, print_mode);
  PrintValue(STR(READ_ONLY_PREFIX)+STR(VARIABLE_LENGTH), reg_length_, col_width, 0, print_mode);
  std::cout << CStringTools::PrepareField(STR(READ_ONLY_PREFIX)+STR(VARIABLE_DATA), col_width, false, false);
  std::cout << CStringTools::PrepareField("DNA Matrix", col_width, false, false);

  //!prev_disabled 
  bool has_regs = false;
  typedef seqan::Iterator<seqan::StringSet<CDataStringSet::TBase > >::Type TStringSetIterator;

  for (TStringSetIterator it = seqan::begin(data_);
       it != seqan::end(data_);
       ++it)
  {
    std::cout << STR(EOL);
    std::cout << STR(TABLE_COL_MARGIN);
    std::cout << *it;
    has_regs = true;
  }

  if (has_regs == false) {
    std::cout << STR(TABLE_EMPTY_FIELD);
  }
  std::cout << STR(EOL);

  PrintFooter(print_mode);
}

std::size_t CDataStringSet::Size(void) const {
  return (regs_ * reg_length_ * sizeof(CDataStringSet::TBase));
    //!prev_disabled return 0;
}

void CDataStringSet::Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action) {
  bool set = false;
  EvalSet(manager(), set, this_info, ref_info);
}

void CDataStringSet::Get(CDataAccess *data_access) {
  bool get = false;
  EvalGet(manager(), get, data_access);
}