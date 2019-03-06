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
 *  \brief     CDataGFF.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      September 19, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATA_MANAGER_DATA_CDATAGFF_H_
#define	DATA_MANAGER_DATA_CDATAGFF_H_

#include <string>

#include "../IDataValue.h"

class CDataGFF : public IDataValue<std::string> {
 public:
  void set_value_string(std::string value) {
    set_value(value);
  } 
 
 public:
  CDataGFF() : IDataValue(KeyString::DATA_GFF, "") {
  }
  
  virtual ~CDataGFF() {}

  IData * clone() const { return new CDataGFF(); /*clone*/ }
};

#endif  // DATA_MANAGER_DATA_CDATAGFF_H_
