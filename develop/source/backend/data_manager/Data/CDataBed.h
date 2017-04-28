/*
 * mstatspop, Statistical Analysis using Multiple Populations for Genomic Data.
 * Copyright (c) 2009-2017, Sebastián Ramos Onsins,
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
 *  \brief     CDataBed.h
 *  \details
 *  \author    jjene
 *  \version   1.0
 *  \date      Jun 1, 2016
 *  \pre
 *  \bug
 *  \warning
 *  \copyright CRAG 2015.
 */

#ifndef DATA_MANAGER_DATA_CDATABED_H_
#define	DATA_MANAGER_DATA_CDATABED_H_

#include <string>

#include "../IDataValue.h"

class CDataBed : public IDataValue<std::string> {
 public:
  void set_value_string(std::string value) {
    set_value(value);
  }   
  
 public:
  CDataBed() : IDataValue(KeyString::DATA_BED, "") {
  }
  
  virtual ~CDataBed() {}

  IData * clone() const { return new CDataBed(); /*clone*/ }
};

#endif  // DATA_MANAGER_DATA_CDATABED_H_
