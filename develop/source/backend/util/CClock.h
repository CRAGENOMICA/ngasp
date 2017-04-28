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
 *  \brief     CClock.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_UTIL_CCLOCK_H_
#define BACKEND_SRC_UTIL_CCLOCK_H_

#include <string>

#include <boost/chrono/chrono.hpp>

class CClock {
 private:
  boost::chrono::system_clock::time_point before_;
  boost::chrono::system_clock::time_point now_;

 public:
  CClock();
  ~CClock();
  
 public:
   void Start(void);
   std::string Stop(bool show_nanoseconds = false);
   
 private:
   std::string To2Digits(int value);
   
};


#endif  // BACKEND_SRC_UTIL_CCLOCK_H_
