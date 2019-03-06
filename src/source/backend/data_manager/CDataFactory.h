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
 *  \brief     CDataFactory.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      April 27, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#ifndef BACKEND_SRC_DATA_MANAGER_CDATAFACTORY_H_
#define BACKEND_SRC_DATA_MANAGER_CDATAFACTORY_H_

#include "../language/CStringTable.h"
#include "IData.h"







class CDataFactory {
 public:
  CDataFactory();
  virtual ~CDataFactory();

  std::map<KeyString, IData *> data_map_;


  IData *GetData(KeyString data_id);
  IData *GetData(std::string type);

//  KeyString GetPrimitiveTypeFrom(KeyString data_id);
//  CollectionType GetCollectionType(KeyString data_id);

  static
  void ReserveMemory(IData *data,
                            long int tables,
                            long int regs,
                            long int length,
                            long int *lens,
                            std::string default_value);
  static bool ValidIndexType(CDataAccess *data);

  static KeyString GetType(CDataAccess *data);

  /**
   * These functions gets a c++ basic type and returns its equivalent
   * in KeyString:
   */
  static KeyString GetTypeOf(char val) {
    return KeyString::DATA_CHAR;
  }

  static KeyString GetTypeOf(int val) {
    return KeyString::DATA_INT;
  }

  static KeyString GetTypeOf(long int val) {
    return KeyString::DATA_INT64;
  }

  static KeyString GetTypeOf(float val) {
    return KeyString::DATA_FLOAT;
  }

  static KeyString GetTypeOf(double val) {
    return KeyString::DATA_DOUBLE;
  }

  static KeyString GetTypeOf(bool val) {
    return KeyString::DATA_BOOLEAN;
  }

  static KeyString GetTypeOf(std::string val) {
    return KeyString::DATA_STD_STRING;
  }

  static bool CompatibleTypes(CDataAccess *to, CDataAccess *from);

  std::string GetDataTypesInformation(void);
};

#endif  // BACKEND_SRC_DATA_MANAGER_CDATAFACTORY_H_
