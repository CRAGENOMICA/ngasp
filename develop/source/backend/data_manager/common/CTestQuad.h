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
 *  \brief     CTestQuad.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 14, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATATYPES_TYPES_CTESTQUAD_H_
#define DATATYPES_TYPES_CTESTQUAD_H_

class CTestQuad {
public:
  CTestQuad(int num_sam);
  virtual ~CTestQuad();

public:
  int nsam;
  int n;
  double *w;
  double theta;
  long l;
  double **w2;
};

#endif /* DATATYPES_TYPES_CTESTQUAD_H_ */
