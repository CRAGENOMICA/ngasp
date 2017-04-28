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
 *  \brief     CDataStdStringVector.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATA_MANAGER_DATA_CDATASTDSTRINGVECTOR_H_
#define	DATA_MANAGER_DATA_CDATASTDSTRINGVECTOR_H_

#include <string>

#include "../IDataVector.h"

class CDataStdStringVector : public IDataVector<std::string> {
 public:
  CDataStdStringVector() : IDataVector(KeyString::DATA_STD_STRING_VECTOR,
                                       KeyString::DATA_STD_STRING) {}
  virtual ~CDataStdStringVector() {}

  IData * clone() const { return new CDataStdStringVector(); /*clone*/ }
};

#endif  // DATA_MANAGER_DATA_CDATASTDSTRINGVECTOR_H_

