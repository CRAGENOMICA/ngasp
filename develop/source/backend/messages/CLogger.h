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
 *  \brief     CLogger.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 5, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#ifndef BACKEND_SRC_MESSAGES_CLOGGER_H_
#define BACKEND_SRC_MESSAGES_CLOGGER_H_

#include <sstream>
#include <iostream>
#include <stack>
#include <fstream>

#include "CNormalEntry.h"
#include "CDebugEntry.h"
#include "CWarningEntry.h"
#include "CErrorEntry.h"
#include "../language/CStringTable.h"

// #include "../data_manager/Data/CDataInt.h"

#define LOG_MESSAGES

#define DEBUG_MSG    *manager()->logger() << \
                     (*manager()->logger()->debug_message()
#define NORMAL_MSG   *manager()->logger() << \
                     (*manager()->logger()->normal_message()
#define WARNING_MSG  *manager()->logger() << \
                     (*manager()->logger()->warning_message()
#define ERROR_MSG    manager()->ActivateError(); \
                     *manager()->logger() << \
                     (*manager()->logger()->error_message()

#define END_MSG  ) // Remember: This is not correct: "<< END_MSG"

#define DEBUG_MSG2    *manager->logger() << \
                      (*manager->logger()->debug_message()
#define NORMAL_MSG2   *manager->logger() << \
                      (*manager->logger()->normal_message()
#define WARNING_MSG2  *manager->logger() << \
                      (*manager->logger()->warning_message()
#define ERROR_MSG2    manager->ActivateError(); \
                      *manager->logger() << \
                      (*manager->logger()->error_message()

#define DEBUG_MSG3    *this->logger() << (*this->logger()->debug_message()
#define NORMAL_MSG3   *this->logger() << (*this->logger()->normal_message()
#define WARNING_MSG3  *this->logger() << (*this->logger()->warning_message()
#define ERROR_MSG3    *this->logger() << (*this->logger()->error_message()

#define DEBUG_MSG4    *manager_->logger() << \
                      (*manager_->logger()->debug_message()
#define NORMAL_MSG4   *manager_->logger() << \
                      (*manager_->logger()->normal_message()
#define WARNING_MSG4  *manager_->logger() << \
                      (*manager_->logger()->warning_message()
#define ERROR_MSG4    manager_->ActivateError(); \
                      *manager_->logger() << \
                      (*manager_->logger()->error_message()

// ===========================================================================
// Class for sending the std::cout to a file
// ===========================================================================
class COutputDescriptor {
 public:
  COutputDescriptor() {
      write_to_file = false;
  }
  COutputDescriptor(bool to_file) {
      write_to_file = to_file;
  }
  ~COutputDescriptor() {
  }
  
 public:
  bool write_to_file;
  std::streambuf *buffer_;  // Use this if you want to output the the screen
  std::stringstream file_;  // Use this if you want to output to a file
  std::string name_;        // And if you want to output to a file set here the
                            // file name
  std::string description_;
};

/*
 * Class Usage:
 * (without macros)
 * ================
 *  
 * CLogger logger;
 * logger << (*logger.normal_message() << "My favorite number is " << number);
 * logger << (*logger.debug_message() << "Debug message. number = " << number);
 * 
 * logger.WriteFile();
 */
class CLogger {
 public:
  CLogger();
  ~CLogger();
     
  /// Normal messages are shown always except in SILENT mode.
  /// Normal messages are sent to the log file only in debug mode.
  CLogger& operator<<(CNormalEntry &entry);
  
  /// Debug messages are only shown in DEBUG mode.
  /// Debug messages are sent to the log file only in debug mode.
  CLogger& operator<<(CDebugEntry &entry);
  
  /// Warning messages are shown always except in SILENT mode.
  /// Warning messages are sent to the log file always.
  CLogger& operator<<(CWarningEntry &entry);
  
  /// Error messages are shown always.
  /// Error messages are sent to the log file always.
  CLogger& operator<<(CErrorEntry &entry);

 public:
  CNormalEntry *normal_message_;
  CDebugEntry *debug_message_;
  CWarningEntry *warning_message_;
  CErrorEntry *error_message_;
  
  inline CNormalEntry *normal_message(void) const { return normal_message_; }
  inline CDebugEntry *debug_message(void) const { return debug_message_; }
  inline CWarningEntry *warning_message(void) const { return warning_message_; }
  inline CErrorEntry *error_message(void) const { return error_message_; }
  
 public:
  enum LogMode {
    SILENT_MODE = 1,
    NORMAL_MODE = 2,
    DEBUG_MODE  = 3
  };

  void WriteLogFile(void);
  void ClearLogFile(void);
  std::string ReadLogFile(void);

  
  
 private:
  CLogger::LogMode mode_;
  std::stringstream log_file_;

 public:
  std::stack<COutputDescriptor *> output_descriptors_;
  void SetNewOutputDescriptor(COutputDescriptor *od);
  void RestorePreviousOutputDescriptor(void);
  void WriteFile(void);
//  void ClearFile(void); 
  
  /*
  // ===========================================================================
  // Functions for sending the std::cout to a std::string
  // ===========================================================================
 private:  
  bool cout_redirected_to_string_;
  std::stringstream buffer_;

 public:
  void RedirectCoutToString(void) {
    if (cout_redirected_to_string_ == false) {
      cout_redirected_to_string_ = true;
      std::cout.rdbuf(buffer_.rdbuf());
    }
  }
  std::string GetOutputString(void) {
    return buffer_.str();
  }
  */
  
 
  // ===========================================================================

 public:
  inline void set_mode(const LogMode &mode) { mode_ = mode; }
  inline LogMode mode(void) const { return mode_; }
  inline std::string mode_str(void) const { 
    std::string ret;
    switch(mode_) {
      case LogMode::DEBUG_MODE:
        ret = STR(VERBOSE_LEVEL_DEBUG);
        break;
      case LogMode::NORMAL_MODE:
        ret = STR(VERBOSE_LEVEL_NORMAL);
        break;
      case LogMode::SILENT_MODE:
        ret = STR(VERBOSE_LEVEL_SILENT);
        break;
    }
    return ret; 
  }
};

#endif  // BACKEND_SRC_MESSAGES_CLOGGER_H_
