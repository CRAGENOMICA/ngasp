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
 *  \brief     CComparison.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_UTIL_CCOMPARISON_H_
#define CALCULATIONS_UTIL_CCOMPARISON_H_

#define MIN(a,b)  ((a) < (b) ? (a) : (b))
#define MAX(a,b)  ((a) > (b) ? (a) : (b))

class CComparison {
public:
  CComparison();
  virtual ~CComparison();

  static double min(int a, int b) {
    return((a < b)? (a):(b));
  }

  static double max(int a, int b) {
    return((a > b)? (a):(b));
  }

  static int min3(int a, int b, int c) {
    return CComparison::min(CComparison::min(a,b),c);
  }
  static int max3(int a, int b, int c) {
    return CComparison::max(CComparison::max(a,b),c);
  }

};

#endif /* CALCULATIONS_UTIL_CCOMPARISON_H_ */
