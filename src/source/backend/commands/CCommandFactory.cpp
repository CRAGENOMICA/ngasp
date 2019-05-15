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
 *  \brief     CCommandFactory.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCommandFactory.h"

#include "../language/CStringTable.h"

#include "ICommand.h"

#include "CMD/CCMDAdd.h"
#include "CMD/CCMDAppend.h"
#include "CMD/CCMDAppHelp.h"
#include "CMD/CCMDCalc.h"
#include "CMD/CCMDConstant.h"
#include "CMD/CCMDDelete.h"
#include "CMD/CCMDDim.h"
#include "CMD/CCMDDryRun.h"
#include "CMD/CCMDElse.h"
#include "CMD/CCMDEndForeach.h"
#include "CMD/CCMDEndIf.h"
#include "CMD/CCMDEndWith.h"
#include "CMD/CCMDExec.h"
#include "CMD/CCMDForeach.h"
#include "CMD/CCMDHistory.h"
#include "CMD/CCMDIf.h"
#include "CMD/CCMDLoadInstructionsFile.h"
#include "CMD/CCMDLog.h"
#include "CMD/CCMDMemInfo.h"
#include "CMD/CCMDmstatspop.h"
#include "CMD/CCMDOpenDataFile.h"
#include "CMD/CCMDOutput.h"
#include "CMD/CCMDPipe.h"
#include "CMD/CCMDPrint.h"
#include "CMD/CCMDReserve.h"
#include "CMD/CCMDReset.h"
#include "CMD/CCMDRun.h"
#include "CMD/CCMDSaveState.h"
#include "CMD/CCMDSetValue.h"
#include "CMD/CCMDSocket.h"
#include "CMD/CCMDStop.h"
#include "CMD/CCMDSyntax.h"
#include "CMD/CCMDVerbose.h"
#include "CMD/CCMDVersion.h"
#include "CMD/CCMDWith.h"
//_COMMAND_LAST

CCommandFactory::CCommandFactory() {
}

CCommandFactory::~CCommandFactory() {
}

void CCommandFactory::FillListWithAllCommands(std::list<ICommand *> *list) {
    list->push_back(new CCMDAdd());
    list->push_back(new CCMDAppend());
    list->push_back(new CCMDAppHelp());
    list->push_back(new CCMDCalc());
    list->push_back(new CCMDConstant());
    list->push_back(new CCMDDelete());
    list->push_back(new CCMDDim());
    list->push_back(new CCMDDryRun());
    list->push_back(new CCMDElse());
    list->push_back(new CCMDEndForeach());
    list->push_back(new CCMDEndIf());
    list->push_back(new CCMDEndWith());
    list->push_back(new CCMDExec());
    list->push_back(new CCMDForeach());
    list->push_back(new CCMDHistory());
    list->push_back(new CCMDIf());
    list->push_back(new CCMDLoadInstructionsFile());
    list->push_back(new CCMDLog());
    list->push_back(new CCMDMemInfo());
    list->push_back(new CCMDmstatspop());
    list->push_back(new CCMDOpenDataFile());
    list->push_back(new CCMDOutput());
    list->push_back(new CCMDPipe());
    list->push_back(new CCMDPrint());
    list->push_back(new CCMDReserve());
    list->push_back(new CCMDReset());
    list->push_back(new CCMDRun());
    list->push_back(new CCMDSaveState());
    list->push_back(new CCMDSetValue());
    list->push_back(new CCMDSocket());
    list->push_back(new CCMDStop());
    list->push_back(new CCMDSyntax());
    list->push_back(new CCMDVerbose());
    list->push_back(new CCMDVersion());
    list->push_back(new CCMDWith());
    //list _COMMAND_LAST
}

