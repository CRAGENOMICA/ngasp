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
 *  \brief     CGFFFile.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_DATA_MANAGER_COMMON_CGFFFILE_H_
#define BACKEND_SRC_DATA_MANAGER_COMMON_CGFFFILE_H_

#include <iostream>
#include <string>
#include <list>

#include "CGFFRecord.h"

class CGFFFile {
 public:
  CGFFFile();
  ~CGFFFile();
  
 private:
  std::string file_name_;                         // File name with its path.
  std::list<CGFFRecord *> *records_;              // File records.
  
 public:
  bool Open(const std::string & file_name);
  
  inline std::string file_name(void) const { return file_name_; }
  inline void set_file_name(const std::string & file_name) { 
    file_name_ = file_name; 
  }
  
  inline std::list<CGFFRecord *> *records(void) const {
    return records_;
  }
  
 private:
  bool AddRecord(std::string file_row);
  
 public:
  friend std::ostream& operator<<(std::ostream & stream, const CGFFFile & gff) {
    stream  << "GFF file name                    : "
            << gff.file_name_
            << std::endl;
    
    return stream;
  } 
};

#endif  // BACKEND_SRC_DATA_MANAGER_COMMON_CGFFFILE_H_
