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
 *  \brief     CDataDoubleCube.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 9, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATA_MANAGER_DATA_CDATADOUBLECUBE_H_
#define	DATA_MANAGER_DATA_CDATADOUBLECUBE_H_

#include "../IDataCube.h"

class CDataDoubleCube : public IDataCube<double> {
 public:
  CDataDoubleCube()
  : IDataCube(KeyString::DATA_DOUBLE_CUBE,
              KeyString::DATA_DOUBLE) {}
  virtual ~CDataDoubleCube() {}

  IData * clone() const { return new CDataDoubleCube(); /*clone*/ }
};

#endif  // DATA_MANAGER_DATA_CDATADOUBLECUBE_H_

