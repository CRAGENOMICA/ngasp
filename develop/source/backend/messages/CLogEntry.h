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
 *  \copyright Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera
 *             Rodríguez, Centre for Research in Agricultural Genomics.
 *             All rights reserved.
 *  \license   LGPL 2.1
 *  \brief     CLogEntry.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 5, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#ifndef BACKEND_SRC_MESSAGES_CLOGENTRY_H_
#define BACKEND_SRC_MESSAGES_CLOGENTRY_H_

#include <sstream>
#include <string>

class CLogEntry { 
 public:
  CLogEntry();
  ~CLogEntry();

 public:
  std::ostringstream stream_;
};

#endif  // BACKEND_SRC_MESSAGES_CLOGENTRY_H_
