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
 *  \brief     CVectorTools.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 29, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef UTIL_CVECTORTOOLS_H_
#define UTIL_CVECTORTOOLS_H_

#include <string>
#include <map>

class CVectorTools {
 public:
  CVectorTools();
  virtual ~CVectorTools();
};

template <typename T1, typename T2>
struct less_than_key {
    typedef std::pair<T1, T2> type;
    bool operator ()(type const& a, type const& b) const {
        return a.second < b.second;
    }
};

template <typename T1, typename T2>
struct greater_than_key {
    typedef std::pair<T1, T2> type;
    bool operator ()(type const& a, type const& b) const {
        return a.second > b.second;
    }
};

#endif  // UTIL_CVECTORTOOLS_H_

