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
 *  \brief     CExperimentNode.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Sep 10, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CExperimentNode.h"
#include "../util/CStringTools.h"

#include <string>

CExperimentNode::CExperimentNode(int experiment_id) {
	experiment_id_ = experiment_id;
  pipe_manager_.CreatePipes(CStringTools::ToString(experiment_id));
  status_ = INSTANCE_FREE;
}




