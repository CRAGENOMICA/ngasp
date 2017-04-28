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
 *  \brief     CManager.h
 *  \details   This class manages all main objects. For example: the data
 *             manager, all repositories: instructions, commands, general
 *             options, calculations, ... and log messages.
 *  \author    Joan Jené, gvera
 *  \version   1.0
 *  \date      March 30, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#ifndef BACKEND_SRC_CMANAGER_H_
#define BACKEND_SRC_CMANAGER_H_

#include <list>

#include "messages/CLogger.h"

class CCalcFactory;
class CDataFactory;
class CDataManager;
class CAllCommands;
class CController;
class COptionsContainer;
class CAllCalculations;

// #include "IObject.h"
class IObject;

enum tExecutionMode
{
  EXEC_MODE_NOT_DEFINED,
  COMMAND_LINE,
  INTERACTIVE_SHELL,
  CENTRAL_MANAGER,
  LOCAL_MANAGER,
  WORKER
};

class CManager {
 public:
  CManager();
  ~CManager();

 private:
  tExecutionMode execution_mode_;
  
 public:
  inline void set_execution_mode(tExecutionMode mode) {
    execution_mode_ = mode;
  }
  inline tExecutionMode execution_mode(void) { return execution_mode_; }
  
  void Init();
  bool PrepareNextInstruction(void);
  void LaunchNextInstruction(void);
  void CleanAndClose(void);
  void StopExecutionMode(void);
  
 public:  
  void RunCommandLineExecutionMode(int argc, char *argv[]);
  void RunInteractiveShellExecutionMode(void);
  void RunLocalManagerExecutionMode(int argc, char *argv[]);
  void RunWorkerExecutionMode(int argc, char *argv[]);

/// ============================================================================
/// COMPONENTS
/// ============================================================================
 private:
  //@{
  /**
   * This class manages all repositories: data, commands, instructions, general
   * options, calculations and log messages:
   */
  CDataFactory *data_factory_;
  CCalcFactory *calc_factory_;
  CDataManager *data_manager_;
  CAllCommands *all_commands_;
  CController *instructions_controller_;
  CLogger *logger_;
  COptionsContainer *general_options_;
  CAllCalculations *all_calculations_;
  //@}

 public:
  inline CDataManager *data_manager(void) const { return data_manager_; }
  inline void set_data_manager(CDataManager *data_manager) {
    data_manager_ = data_manager;
  }

  inline CAllCommands *all_commands(void) const { return all_commands_; }
  inline void set_all_commands(CAllCommands *all_commands) {
    all_commands_ = all_commands;
  }

  inline CController *instructions_controller(void) const {
    return instructions_controller_;
  }
  inline void set_instructions_controller(CController *
      instructions_controller) {
    instructions_controller_ = instructions_controller;
  }

  inline CLogger *logger(void) const { return logger_; }
  inline void set_logger(CLogger *logger) { logger_ = logger; }

  inline COptionsContainer *general_options(void) const {
    return general_options_;
  }
  inline void set_general_options(COptionsContainer *general_options) {
    general_options_ = general_options;
  }

  inline CAllCalculations *all_calculations(void) const {
    return all_calculations_;
  }
  inline void set_all_calculations(CAllCalculations *all_calculations) {
    all_calculations_ = all_calculations;
  }

  inline CDataFactory *data_factory(void) const {
    return data_factory_;
  }
  inline void set_data_factory(CDataFactory *data_factory) {
    data_factory_ = data_factory;
  }

  inline CCalcFactory *calc_factory(void) const {
    return calc_factory_;
  }
  inline void set_calc_factory(CCalcFactory *calc_factory) {
    calc_factory_ = calc_factory;
  }


/// ============================================================================
/// WITH
/// ============================================================================
 private:
  IObject *with_;  // Pointer to a data object (data, calc, randomize, ...)

 public:
  void set_with(const std::string & name);
  inline void set_with(IObject *with) { with_ = with; }
  inline IObject *with() const { return with_; }
  IObject *with(const std::string & name) const;

/// ============================================================================
/// OUTPUT
/// ============================================================================
 private:
  std::streambuf *output_stream_original_;  /// It pointers to the screen.
  std::ofstream  *output_file_stream_;      /// It pointers to a file (cout).
  FILE           *foutput_;                 /// for fprintf
                                            /// (mstatspop compatibility)
 public:
  inline FILE *foutput(void) { return foutput_; }
  inline void set_foutput(FILE *foutput) {
    foutput_ = foutput;
  }
  void RedirectCoutToFile(const std::string &file_name);
  void RedirectCoutToScreenAgain(void);
  
  
 public:
  void ActivateError(void);
};

#endif  // BACKEND_SRC_CMANAGER_H_
