/*
 * mstatspop, Statistical Analysis using Multiple Populations for Genomic Data.
 * Copyright (c) 2009-2017, Sebastián Ramos Onsins,
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
 *  \brief     CTestR0.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 14, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CTestR0.h"

#include <cstddef>

CTestR0::CTestR0(int num_sam) {
  nsam  = num_sam;
  n     = 0;
  w     = new double[num_sam];
  dw    = new double[num_sam];
  d2w   = new double[num_sam];
  theta = 0;
  l     = 0;
  var   = 0;
  dvar  = 0;
  d2var = 0;
}

CTestR0::~CTestR0() {

  if(w!=NULL) {
    delete[] w;
    w=NULL;
  }

  if(dw!=NULL) {
    delete[] dw;
    dw=NULL;
  }

  if(d2w!=NULL) {
    delete[] d2w;
    d2w=NULL;
  }
}
