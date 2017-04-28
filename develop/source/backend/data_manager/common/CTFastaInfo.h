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
 *  \brief     CTFastaInfo.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_DATA_MANAGER_COMMON_CTFASTAINFO_H_
#define BACKEND_SRC_DATA_MANAGER_COMMON_CTFASTAINFO_H_

#include <cstdint>
#include <string>

#include "CFastaInfo.h"
#include "CMemoryMappedFile.h"

class CTFastaInfo : public CMemoryMappedFile
{
 private:
  uintmax_t   descriptions_size_;  // The whole size of descriptions.
  uintmax_t   columns_;            // Number of individuals.
  uintmax_t   rows_;               // Number of bases (in vertical). It does not
                                   // take into account the first row with
                                   // descriptions.
  
 public:
  CTFastaInfo(const std::string & file_name) : CMemoryMappedFile(file_name) {
    rows_               = 0;
    columns_            = 0;
    descriptions_size_  = 0;
  } 
  
  CTFastaInfo() : CMemoryMappedFile() {
    file_name_          = "";
    rows_               = 0;
    columns_            = 0;
    descriptions_size_  = 0;
  }
  
  bool OpenForWrite(const std::string & file_name, CFastaInfo *fasta_info) {
    rows_               = fasta_info->bases();
    columns_            = fasta_info->GetNumSequences();
    descriptions_size_  = fasta_info->descriptions().length();

    boost::intmax_t new_file_size =
                  descriptions_size()  // this size has the EOL char
                  + ((columns() + 1) * rows());
    
    CMemoryMappedFile::OpenForWrite(file_name, new_file_size);
    
    return is_open_;
  }
 
 public:
  bool GetFileInformation(const std::string & file_name);
  
 public:  
  inline uintmax_t descriptions_size(void) const { return descriptions_size_; }
  inline void set_descriptions_size(const uintmax_t & descriptions_size) { 
    descriptions_size_ = descriptions_size; 
  }

  inline uintmax_t columns(void) const { return columns_; }
  inline void set_columns(const uintmax_t & columns) { 
    columns_ = columns; 
  }

  inline uintmax_t rows(void) const { return rows_; }
  inline void set_rows(const uintmax_t & rows) { 
    rows_ = rows; 
  }
  
  friend std::ostream& operator<<(std::ostream & stream, const CTFastaInfo & tfasta) {
    stream  << "T-Fasta file name                : "
            << tfasta.file_name_
            << std::endl
            << "Columns                          : "
            << tfasta.columns_
            << std::endl
            << "Rows                             : "
            << tfasta.rows_
            << std::endl
            << "Descriptions size in bytes       : "
            << tfasta.descriptions_size_
            << std::endl;
    
    return stream;
  } 
};

#endif  // BACKEND_SRC_DATA_MANAGER_COMMON_CTFASTAINFO_H_
