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
 *  \brief     CDataIntVector.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 8, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATA_MANAGER_DATA_CDATADOUBLEVECTOR_H_
#define	DATA_MANAGER_DATA_CDATADOUBLEVECTOR_H_

#include "../IDataVector.h"

class CDataDoubleVector : public IDataVector<double> {
 public:
  CDataDoubleVector()
  : IDataVector(KeyString::DATA_DOUBLE_VECTOR,
                KeyString::DATA_DOUBLE) {}
  virtual ~CDataDoubleVector() {}

  IData * clone() const { return new CDataDoubleVector(); /*clone*/ }
  
 public:
  /**
   * Call Sort() before.
   * @return 
   */
  double GetMedian(void) {
    double median = 0;
    
    std::size_t n = Size();

    if (n > 0) {
        if (n % 2 == 0) {
          median = (operator [](n/2 - 1) + operator [](n/2)) / 2;
        } else {
          median = operator []((n-1)/2);
        }
    }
    return median;
  }
  
  /*
   * Call Sort() before.
   * Example Set n=8: [0][1][2][3]         [4][5][6][7]  n%2 == 0 lower_values = [0..n/2) higher_values = [n/2..n)
   * Example Set n=9: [0][1][2][3]   [4]   [5][6][7][8]  n%2 != 0 lower_values = [0..n-1 / 2) higher_values = [n+1 / 2..n)
   */
  CDataDoubleVector SplitVector(double median, bool lower) {
    CDataDoubleVector ret;
    
    std::size_t n = Size();
    for (std::size_t i = 0; i < n; i++) {
        double value = operator [](i);
        if (lower) {
            if (value < median) {
                ret.PushBack(value);
            }
        } else {
            if (value > median) {
                ret.PushBack(value);
            }            
        }
    }
    
    ret.PushBack(0);
    
    return ret;
  }

  double GetNearestValue(double ref, bool lower) {
    double ret = ref;
    
    std::size_t n = Size();
    
    if (lower) {
      for (std::size_t i = 0; i < n; i++) {
        ret = operator [](i);
        if (ret >= ref) {
            break;
        }
      }
    }

    if (!lower) {
      for (std::size_t i = n - 1; i >= 0; i--) {
        ret = operator [](i);
        if (ret <= ref) {
            break;
        }            
      }
    }
    
    return ret; 
  }
  
};

#endif  // DATA_MANAGER_DATA_CDATADOUBLEVECTOR_H_

