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
 *  \brief     IDataValue.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 11, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "IDataValue.h"

#include "../data_manager/CDataManager.h"
#include "../data_manager/common/CDataAccess.h"
#include "../data_manager/common/CDataHelper.h"
#include "../data_manager/Data/CDataInt.h"
#include "Data/CDataStdString.h"
/*
 * *****************************************************************************
 * This class is a template, so all the code must be in the .h file.
 * Except Set function (and Compare).
 *******************************************************************************
 */

template <class T>
void IDataValue<T>::Set(CDataAccess *this_info,
                        CDataAccess *ref_info,
                        SetAction action) {
  bool set = false;

  set = CDataHelper::Set(this_info, ref_info, action, T());

  if (set == true) {
    CallOnChange();
  }

  EvalSet(manager(), set, this_info, ref_info);
}

template <class T>
ComparisonType IDataValue<T>::Compare(CDataAccess *this_info,
                                      CDataAccess *ref_info) {
  return CDataHelper::Compare(this_info, ref_info, T());
}

template <class T>
ComparisonType IDataValue<T>::Compare(const IDataValue<T> &ref) {
  return CDataHelper::Compare(value(), ref.value());
}

template <class T>
void IDataValue<T>::Print(PrintMode print_mode) {
    int col_with = 0;

    CDataInt *precision = NULL;
    precision = (CDataInt *)manager()->data_manager()->GetDataByName(
                                                                parent(),
                                                                STR(PRECISION));

    col_with = PrintHeader(print_mode);
    
    PrintValue(STR(VARIABLE_VALUE),
               value_,
                col_with,
                precision->value(),
                print_mode);
    PrintFooter(print_mode);
}