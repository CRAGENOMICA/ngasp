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
 *  \brief     CTestR0.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 14, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATATYPES_TYPES_CTESTR0_H_
#define DATATYPES_TYPES_CTESTR0_H_

class CTestR0 {
public:
  CTestR0(int num_sam);
  virtual ~CTestR0();

public:
  int nsam;
  int n;
  double *w;
  double *dw;
  double *d2w;
  double theta;
  long l;
  double var;
  double dvar;
  double d2var;
};

#endif /* DATATYPES_TYPES_CTESTR0_H_ */
