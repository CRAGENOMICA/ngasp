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
 *  \brief     CDataWeightsFile.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      February 10, 2017
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATA_MANAGER_DATA_CDATAWEIGHTS_H_
#define	DATA_MANAGER_DATA_CDATAWEIGHTS_H_

#include <string>

#include "../IDataValue.h"

class CDataWeightsFile : public IDataValue<std::string> {
 public:
  void set_value_string(std::string value) {
    set_value(value);
  }   
  
 public:
  CDataWeightsFile() : IDataValue(KeyString::DATA_WEIGHTS, "") {
  }
  
  virtual ~CDataWeightsFile() {}

  IData * clone() const { return new CDataWeightsFile(); /*clone*/ }
};

#endif  // DATA_MANAGER_DATA_CDATAWEIGHTS_H_
