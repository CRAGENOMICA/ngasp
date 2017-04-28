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
 *  \brief     CTime.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 10, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CTimeStamp.h"

#include <ctime>
#include <sstream>
#include "../util/CStringTools.h"

CTimeStamp::CTimeStamp() {
}

CTimeStamp::~CTimeStamp() {
}

std::string CTimeStamp::GetTimeNow() {
  std::stringstream ss;
  std::string time_string;

  time_t t = time(0);  // get time now
  struct tm * now = localtime(&t);

  ss << (now->tm_year + 1900);
  ss << "-";
  ss << CStringTools::ToNDigits(now->tm_mon + 1, 2, '0');
  ss << "-";
  ss << CStringTools::ToNDigits(now->tm_mday + 1, 2, '0');
  ss << " ";
  ss << CStringTools::ToNDigits(now->tm_hour, 2, '0');
  ss << ":";
  ss << CStringTools::ToNDigits(now->tm_min, 2, '0');
  ss << ":";
  ss << CStringTools::ToNDigits(now->tm_sec, 2, '0');

  time_string = ss.str();

  return time_string;
}


