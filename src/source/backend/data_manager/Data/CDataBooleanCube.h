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
 *  \brief     CDataBooleanCube.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Aug 4, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATA_MANAGER_DATA_CDATABOOLEANCUBE_H_
#define	DATA_MANAGER_DATA_CDATABOOLEANCUBE_H_

#include "../IDataCube.h"

class CDataBooleanCube : public IDataCube<int> {
 public:
  CDataBooleanCube()
  : IDataCube(KeyString::DATA_BOOLEAN_CUBE,
              KeyString::DATA_BOOLEAN) {}
  virtual ~CDataBooleanCube() {}

  IData * clone() const { return new CDataBooleanCube(); /*clone*/ }
};

#endif  // DATA_MANAGER_DATA_CDATABOOLEANCUBE_H_

