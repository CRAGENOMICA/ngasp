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
 *  \brief     CClock.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CClock.h"

#include <string>
#include <sstream>

#include <boost/chrono/chrono.hpp>

CClock::CClock() {
}

CClock::~CClock() {
}


void CClock::Start(void) {
  before_ = boost::chrono::system_clock::now(); 
}

std::string CClock::To2Digits(int value) {
  std::stringstream ss;

  if (value < 10) {
    ss << "0";
  }
  
  ss << value;
  
  return ss.str();
}

std::string CClock::Stop(bool show_nanoseconds) {
  std::string ret;
  
  now_ = boost::chrono::system_clock::now(); 
  
  boost::chrono::nanoseconds t = boost::chrono::duration_cast<boost::chrono::nanoseconds>(now_-before_);
  
  long int total_nanoseconds = t.count();
  long int total_seconds = t.count() / 1000000000;
  long int total_minutes = total_seconds / 60;
  long int total_hours = total_minutes / 60;

  int hours = total_hours;
  int minutes = (total_minutes % 60);
  int seconds = (total_seconds % 60);
  int nanoseconds = (total_nanoseconds % 60);
  
  std::string col = ":";
  
  ret = To2Digits(hours) + col + To2Digits(minutes) + col + To2Digits(seconds);
  
  if (show_nanoseconds) {
    ret += col + To2Digits(nanoseconds);
  }
  
  return ret;
}
