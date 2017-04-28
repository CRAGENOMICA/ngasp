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
 *  \brief     CCMDEndForeach.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 6, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDEndForeach.h"

#include "../../instructions/CController.h"
#include "../../data_manager/CDataManager.h"

CCMDEndForeach::CCMDEndForeach()
  : ICommand(CMD_END_FOREACH,                                                   // Command Name
             CMD_END_FOREACH_ABB,                                               // Command Abbreviation Name
             CMD_END_FOREACH_DESC,                                              // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also  
}

CCMDEndForeach::~CCMDEndForeach() {
}

void CCMDEndForeach::DefineCommandOptions() {
}

bool CCMDEndForeach::Prepare() {
  bool parseResult = true;
  return parseResult;
}

void CCMDEndForeach::Run() {
}

/**
 * Code of loop instructions must be in the Finalize function.
 *
 * Else, the next one function to be executed when Run finalizes could be the
 * Finalize function of other instruction.
 */
void CCMDEndForeach::Finalize() {
  manager()->instructions_controller()->SetCurrentInstructionAsLoopEnd();

  /// Clean the command to reuse it later:
  DM_DEL_ALL_LOCAL_DATA
}


