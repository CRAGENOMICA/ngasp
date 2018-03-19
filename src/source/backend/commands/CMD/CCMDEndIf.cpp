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
 *  \brief     CCMDEndIf.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 6, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDEndIf.h"

#include "../../instructions/CController.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataBoolean.h"

CCMDEndIf::CCMDEndIf()
  : ICommand(CMD_END_IF,                                                       // Command Name
             CMD_END_IF_ABB,                                                    // Command Abbreviation Name
             CMD_END_IF_DESC,                                                   // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also  
}

CCMDEndIf::~CCMDEndIf() {
}

void CCMDEndIf::DefineCommandOptions() {
}

bool CCMDEndIf::Prepare() {
  bool parseResult = true;
  return parseResult;
}

/**
 * THIS COMMAND IS ALREADY FINISHED.
 */
void CCMDEndIf::Run() {
}

void CCMDEndIf::Finalize() {
  /// Clean the command to reuse it later:
  DM_DEL_ALL_LOCAL_DATA
}


