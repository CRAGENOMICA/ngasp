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
 *  \brief     CMemoryMappedFile.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_DATA_MANAGER_COMMON_CMEMORYMAPPEDFILE_H_
#define BACKEND_SRC_DATA_MANAGER_COMMON_CMEMORYMAPPEDFILE_H_

#include <cstdint>
#include <string>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

class CMemoryMappedFile
{
 protected:
  std::string file_name_;                         // File name with its path.
  bool        is_open_;                           // True if the file is open.
  boost::iostreams::mapped_file_source *source_data_;    // Pointer for reading data.
  boost::iostreams::mapped_file_sink destination_data_;  // Pointer for writing data.
  
 public:
  CMemoryMappedFile(const std::string & file_name) {
    file_name_          = file_name;
    is_open_            = false;
    source_data_        = NULL;
  }
  
  CMemoryMappedFile() {
    file_name_          = "";
    is_open_            = false;
    source_data_        = NULL;
  }

  CMemoryMappedFile(const CMemoryMappedFile & other) {
    file_name_          = other.file_name_;
    is_open_            = other.is_open_;
    source_data_        = other.source_data_;
  }
  
  ~CMemoryMappedFile() {
    if (source_data_ != NULL) {
      source_data_->close();
      delete source_data_;
      source_data_ = NULL;
    }

    set_is_open(false);
  }
  
 public:  
  inline std::string file_name(void) const { return file_name_; }
  inline void set_file_name(const std::string & file_name) { 
    file_name_ = file_name; 
  }

  inline bool is_open(void) const { return is_open_; }
  inline void set_is_open(const bool & is_open) { 
    is_open_ = is_open; 
  }
  
  // This function is only executed if the children class does not have its own
  // operator<< defined.
  friend std::ostream& operator<<(std::ostream & stream,
                                  const CMemoryMappedFile & tfasta) {
    stream  << "File name                        : "
            << tfasta.file_name_
            << std::endl;
    
    return stream;
  } 
  
  // ===========================================================================
  // READING OPERATIONS
  // ===========================================================================
  
  bool OpenForRead(const std::string & file_name) {
    file_name_ = file_name;
    
    try {
      source_data_ = new boost::iostreams::mapped_file_source(
                                                            file_name_.c_str());
      is_open_ = true;
    }
    catch(...) {
      is_open_ = false;
    }
    
    return is_open_;
  }
  
  inline boost::iostreams::mapped_file_source * source_data(void) const {
    return source_data_;
  }
  
  inline const char *GetChar(uintmax_t position) {
    return source_data_->data() + position;
  }
  
  inline const char *GetFirstDataPosition(void) const {
    return source_data_->data();
  }

  inline const char *GetLastDataPosition(void) const {
    return source_data_->data() + source_data_->size();
  }
 
  // ===========================================================================
  // WRITING OPERATIONS
  // ===========================================================================
  
  unsigned long int CalculateTableSpace(unsigned long int rows,
                               unsigned long int columns,
                               int cell_size,
                               std::string column_separator);
  
  bool WriteCell(std::string text,
                 unsigned long int row,
                 unsigned long int col,
                 unsigned long int columns,
                 std::size_t cell_size,
                 std::string column_separator);

  bool OpenForWrite(const std::string & file_name,
                    boost::intmax_t new_file_size) {
    file_name_ = file_name;
    
    boost::iostreams::mapped_file_params param_sink;
    param_sink.path = file_name_;
    param_sink.offset = 0;
    param_sink.new_file_size = new_file_size;
                  
    destination_data_.open(param_sink);

    is_open_ = destination_data_.is_open();
    
    return is_open_;
  }
  
  inline boost::iostreams::mapped_file_sink * destination_data(void) {
    return &destination_data_;
  }
  
  inline char *GetFirstReservedPosition(void) const {
    return destination_data_.data();
  }

  inline char *GetLastReservedPosition(void) const {
    return destination_data_.end();
  }
  
  bool Write(std::string text,
             char **current_position,
             const char *end_position);
  
  void Close(char *current_position = NULL,
             const char *end_position = NULL);
};

#endif  // BACKEND_SRC_DATA_MANAGER_COMMON_CMEMORYMAPPEDFILE_H_
