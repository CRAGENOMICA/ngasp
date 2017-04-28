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
 *  \brief     CCMDOpenDataFile.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 28, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDOpenDataFile.h"

#include "../../language/CStringTable.h"
#include "../../data_manager/CDataManager.h"

CCMDOpenDataFile::CCMDOpenDataFile()
  : ICommand(CMD_OPEN_DATA_FILE,                                                // Command Name
             CMD_OPEN_DATA_FILE_ABB,                                            // Command Abbreviation Name
             CMD_OPEN_DATA_FILE_DESC,                                           // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
}

CCMDOpenDataFile::~CCMDOpenDataFile() {
}

void CCMDOpenDataFile::DefineCommandOptions() {
}

bool CCMDOpenDataFile::Prepare() {
  return true;
}

void CCMDOpenDataFile::Run() {
  std::cout << "Open Data File" << std::endl;
}

void CCMDOpenDataFile::Finalize() {
  /// Clean the command to reuse it later:
  DM_DEL_ALL_LOCAL_DATA
}

