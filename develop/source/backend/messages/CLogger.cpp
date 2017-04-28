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
 *  \brief     CLogger.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 5, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#include "CLogger.h"

#include <sstream>
#include <iostream>
#include <stack>

#include "CNormalEntry.h"
#include "CDebugEntry.h"
#include "CWarningEntry.h"
#include "CErrorEntry.h"

#include "../language/CStringTable.h"
#include "../util/CFile.h"
#include "CTimeStamp.h"

CLogger::CLogger() {
  set_mode(NORMAL_MODE);
  normal_message_ = new CNormalEntry();
  debug_message_ = new CDebugEntry();
  warning_message_ = new CWarningEntry();
  error_message_ = new CErrorEntry();
  //cout_redirected_to_string_ = false;
  //backup = NULL;

  // 
  COutputDescriptor * od = new COutputDescriptor(false);
  od->buffer_ = std::cout.rdbuf();
  od->description_ = "cout";
  output_descriptors_.push(od);
}

CLogger::~CLogger() { 
  if (normal_message_ != NULL) {
    delete normal_message_;
    normal_message_ = NULL;
  }
  
  if (debug_message_ != NULL) {
    delete debug_message_;
    debug_message_ = NULL;
  }
  
  if (warning_message_ != NULL) {
    delete warning_message_;
    warning_message_ = NULL;
  }
  
  if (error_message_ != NULL) {
    delete error_message_;
    error_message_ = NULL;
  }
  
  COutputDescriptor *p = NULL;
  while(output_descriptors_.empty() == false) {
    p = output_descriptors_.top();
    delete p;
    p = NULL;
    output_descriptors_.pop();    
  }
}

CLogger& CLogger::operator<<(CNormalEntry &entry) {
#ifdef LOG_MESSAGES  
  entry.stream_ << std::flush;
  
  switch (mode()) {
    case SILENT_MODE:
      break;
    case NORMAL_MODE:
      std::cout << entry.stream_.str() << STR(EOL);
      break;
    case DEBUG_MODE:
      std::cout << entry.stream_.str() << STR(EOL);
      log_file_ << CTimeStamp::GetTimeNow() << STR(SPACE) 
                << STR(NORMAL_ID) << STR(SPACE) 
                << entry.stream_.rdbuf() << STR(EOL);
      WriteLogFile();
      break;
  }
  
  entry.stream_.str("");
  entry.stream_.clear();
#endif  
  return *this;
}

CLogger& CLogger::operator<<(CDebugEntry &entry) {
#ifdef LOG_MESSAGES    
  entry.stream_ << std::flush;
  
  switch (mode()) {
    case SILENT_MODE:
    case NORMAL_MODE:
      break;
    case DEBUG_MODE:
      std::cout << STR(YELLOW_START) << entry.stream_.str() 
                << STR(YELLOW_END) << STR(EOL);
      log_file_ << CTimeStamp::GetTimeNow() << STR(SPACE) 
                << STR(DEBUG_ID) << STR(SPACE) 
                << entry.stream_.rdbuf() << STR(EOL);
      WriteLogFile();
      break;
  }
    
  entry.stream_.str("");
  entry.stream_.clear();
#endif  
  return *this;
}

CLogger& CLogger::operator<<(CWarningEntry &entry) {
#ifdef LOG_MESSAGES  
  entry.stream_ << std::flush;
  
  switch (mode()) {
    case SILENT_MODE:
      break;
    case NORMAL_MODE:
    case DEBUG_MODE:
      std::cout << STR(YELLOW_START) << "Warning: " << entry.stream_.str() 
                << STR(YELLOW_END) << STR(EOL);
      break;
  }

  log_file_ << CTimeStamp::GetTimeNow() << STR(SPACE)
            << STR(WARNING_ID) << STR(SPACE) 
            << entry.stream_.rdbuf() << STR(EOL);
  WriteLogFile();
  
  entry.stream_.str("");
  entry.stream_.clear();
#endif
  return *this;
}

CLogger& CLogger::operator<<(CErrorEntry &entry) {
#ifdef LOG_MESSAGES  
  entry.stream_ << std::flush;
  
  std::cout << STR(RED_START) << "Error: " << entry.stream_.str() 
            << STR(RED_END) << STR(EOL);

  log_file_ << CTimeStamp::GetTimeNow() << STR(SPACE) 
            << STR(ERROR_ID) << STR(SPACE) 
            << entry.stream_.rdbuf() << STR(EOL);
  WriteLogFile();
  
  entry.stream_.str("");
  entry.stream_.clear();
#endif
  return *this;
}

std::string CLogger::ReadLogFile(void) {
  std::string content;
#ifdef LOG_MESSAGES
  CFile log_file(STR(LOG_FILE));

  if (log_file.Open()) {
    std::string message;

    while (log_file.ReadLine(&message)) {
        if (message != "") {
          content += message;
          content += STR(EOL);
        }
    }

    log_file.Close();
  }
#endif  
  return content;
}

void CLogger::ClearLogFile(void) {
#ifdef LOG_MESSAGES  
  CFile::ReplaceContentBy(STR(LOG_FILE), "");  
#endif  
}

void CLogger::WriteLogFile(void) {
#ifdef LOG_MESSAGES  
  CFile::Append(STR(LOG_FILE), log_file_.str());
  
  log_file_.str(std::string());
  log_file_.clear();
#endif
}

// =============================================================================
// Functions for sending the std::cout to a file
// =============================================================================

void CLogger::SetNewOutputDescriptor(COutputDescriptor *od) {
  output_descriptors_.push(od);
  std::cout.rdbuf((od->write_to_file)?
                   od->file_.rdbuf():
                   od->buffer_);
}

void CLogger::RestorePreviousOutputDescriptor(void) {
    COutputDescriptor *p = output_descriptors_.top();
    delete p;
    p = NULL;
    output_descriptors_.pop();    
    
    std::cout.rdbuf((output_descriptors_.top()->write_to_file)?
                    output_descriptors_.top()->file_.rdbuf():
                    output_descriptors_.top()->buffer_);
}

void CLogger::WriteFile(void) {
  CFile::Append(output_descriptors_.top()->name_, 
                output_descriptors_.top()->file_.str());
                output_descriptors_.top()->file_.str(std::string());
  output_descriptors_.top()->file_.str(std::string());
  output_descriptors_.top()->file_.clear();
}
//
//void CLogger::ClearFile(void) {
//  CFile::ReplaceContentBy(output_descriptors_.top()->name_, "");  
//}

