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
 *  \brief     CCMDVersion.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 8, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDVersion.h"

#include <iostream>

#include "../../language/CStringTable.h"
#include "../../data_manager/CDataManager.h"

CCMDVersion::CCMDVersion()
  : ICommand(CMD_APP_VERSION,                                                   // Command Name
             CMD_APP_VERSION_ABB,                                               // Command Abbreviation Name
             CMD_APP_VERSION_DESC,                                              // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
}

CCMDVersion::~CCMDVersion() {
}

void CCMDVersion::DefineCommandOptions() {
}

bool CCMDVersion::Prepare() {
  return true;
}

void CCMDVersion::Run() {
  NORMAL_MSG << STR(NGASP_APP_NAME)
             << STR(SPACE)
             << STR(NGASP_APP_VERSION)
            END_MSG;
}

void CCMDVersion::Finalize() {
  /// Clean the command to reuse it later:
  DM_DEL_ALL_LOCAL_DATA
}


