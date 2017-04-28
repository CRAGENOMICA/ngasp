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
 *  \brief     IDataCube.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 9, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "IDataCube.h"

#include <sstream>

#include "../data_manager/common/CDataAccess.h"
#include "../data_manager/common/CDataHelper.h"


/*
 * *****************************************************************************
 * This class is a template, so all the code must be in the .h file.
 *******************************************************************************
 */

template <class T>
ComparisonType IDataCube<T>::Compare(CDataAccess *this_info,
                                       CDataAccess *ref_info) {
  return CDataHelper::Compare(this_info, ref_info, T());
}

template <class T>
void IDataCube<T>::Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action) {
  bool set = false;
  
  set = CDataHelper::Set(this_info, ref_info, action, T());

  if (set == true) {
    CallOnChange();
  }

  EvalSet(manager(), set, this_info, ref_info);
}
