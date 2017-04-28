/*
 * mstatspop, Statistical Analysis using Multiple Populations for Genomic Data.
 * Copyright (c) 2009-2017, Sebastián Ramos Onsins,
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
 *  \brief     CMatrixPol.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CMatrixPol.h"

#include <cstdint>  // long int

CMatrixPol::CMatrixPol() {
}

CMatrixPol::~CMatrixPol() {
}

int CMatrixPol::ispolmis(char *matrix_pol, int nsam, long j, long int length)
{
  int x,y;
  int a0,a1;

  y=0;
  while((a0 = matrix_pol[j*nsam+y]) == '-' && y < nsam) {
    y++;
  }
  if(y>=nsam-1) {
    return 2; /*all are missings or monomorphic*/
  }

  for(x=(y+1);x<nsam;x++)
  {
    while( (a1 = matrix_pol[j*nsam+x]) == '-' && x < nsam)
      x++;

    if(a0 != a1) {
      return 0; /*polymorphic*/
    }
  }

  return 1; /*monomorphic*/
}
