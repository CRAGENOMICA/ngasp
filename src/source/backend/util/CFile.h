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
 *  \brief     CFile.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 10, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_UTIL_CFILE_H_
#define BACKEND_SRC_UTIL_CFILE_H_

#include <string>
#include <fstream>

class CFile {
 public:
  explicit CFile(const std::string &file_name);
  virtual ~CFile();

  enum FileStatus {
    CLOSED,
    OPEN,
  };

  bool Open();
  bool Close(void);
  bool ReadLine(std::string *line);
  //std::string ReadAll(void);
  static bool ReadAll(const std::string &file_name, std::string &buffer);
  bool WriteLine(const std::string &line);
  static bool ReplaceContentBy(const std::string &file_name,
                               const std::string &buffer);
  static bool Append(const std::string &file_name,
                     const std::string &buffer);
  static bool Remove(const std::string &file_name);
  static bool CreateDirectories(const std::string &directories);
  static bool Exists(const std::string &file_name);
  static std::string GetCurrentWorkingDirectory(void);
  static std::string GetPathFileNameWithoutExtension(std::string file_name);
  static std::string GetPathFromFileName(std::string file_name);
  static std::string GetFileNameWithoutExtension(std::string file_name);
  static std::string GetExtensionFromFileName(std::string file_name);
  static std::string ConcatenateIterationToFilePathName(std::string file_name, int64_t iteration_number, std::string iteration_value);
  static void MoveToLastAccessedPosition(const std::string & file_name, std::ifstream & file);
  static void StoreLastAccessedPosition(const std::string & file_name, std::ifstream & file, std::streampos last_position);
  
  
 private:
  std::string name_;
  CFile::FileStatus status_;
  std::ifstream fdin_;
  std::ofstream fdout_;

 public:
  inline std::string name(void) const { return name_; }
  inline void set_name(const std::string &name) { name_ = name; }

  inline FileStatus status(void) const { return status_; }
  inline void set_status(FileStatus status) { status_ = status; }

  inline std::ifstream::pos_type GetFileSize(void) const {
    std::ifstream in(name(), std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
  }
};


#endif  // BACKEND_SRC_UTIL_CFILE_H_
