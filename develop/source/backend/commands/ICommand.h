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
 *  \brief     ICommand.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      March 30, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#ifndef BACKEND_SRC_COMMANDS_ICOMMAND_H_
#define BACKEND_SRC_COMMANDS_ICOMMAND_H_

#include <list>
#include <string>

#include "../IBase.h"
#include "../IFunction.h"
#include "../instructions/IInstruction.h"
#include "../language/CStringTable.h"
#include "../IObject.h"

/**
 * @brief This is the interface for commands.
 */
class ICommand : public IBase, public IFunction, public IObject {
  // This class derives from IObject because only those objects that derive from it
  // can create data manager variables and calculations.
 public:
//  ICommand(KeyString command_name,
//           KeyString command_abbreviation,
//           KeyString brief_description);
  
  ICommand(KeyString command_name,
           KeyString command_abbreviation,
           KeyString brief_description,
           KeyString description,
           KeyString author,
           KeyString see_also);

  virtual ~ICommand();

 public:
  ///@{
  /**
   * Command Instructions
   */
  virtual void DefineCommandOptions() = 0;
  virtual bool Prepare() = 0;
  virtual void Run() = 0;
  virtual void Finalize() = 0;
  //@}

 public:
  bool CheckCommandOptions();

 private:
  //@{
  /**
   * Command Information
   */
  KeyString   name_;
  KeyString   command_abbreviation_;
  std::string experiment_;
  //@}

 public:
  inline KeyString name() const { return name_; }
  inline void set_name(const KeyString & name) {
    name_ = name;
  }

  inline KeyString command_abbreviation() const {
    return command_abbreviation_;
  }
  inline void set_command_abbreviation(
      const KeyString & command_abbreviation) {
    command_abbreviation_ = command_abbreviation;
  }

  inline void set_experiment(std::string experiment) {
    experiment_ = experiment;
  }
  inline std::string experiment() const { return experiment_; }

  
 private:
  //@{
  /**
   * Command Functionality
   */
  bool               ready_to_run_;
  IInstruction       *instruction_;
  //@}

 public:
  inline void set_ready_to_run(bool ready) { ready_to_run_ = ready; }
  inline bool ready_to_run() const { return ready_to_run_; }

  inline IInstruction *instruction() const { return instruction_; }
  void set_instruction(IInstruction *instruction);

 private:
  //@{
  /**
   * Command Options and Arguments
   */
 private:
  std::list<std::string>::iterator options_index_;
  bool options_missing_options_;
  bool options_missing_option_arguments_;
  bool options_unknown_parameter_;
  //@}

 protected:
  bool getopt_long_own(KeyString * option,
                       std::string * arguments);
  bool CheckOptions();

  inline bool options_missing_options() const {
    return options_missing_options_;
  }
  inline bool options_missing_option_arguments() const {
    return options_missing_option_arguments_;
  }
  inline bool options_unknown_parameter() const {
    return options_unknown_parameter_;
  }
  /**
   * @param arguments is a list of words separated by an space
   * @return the first word. It also removes the first word from "arguments"
   */
  std::string GetArgument(std::string *arguments);
  
  

  // These functions are defined because this class derives from IObject.
  // But this class does not need these functions:
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  void Print(PrintMode print_mode) {}
  std::size_t Size(void) const { return 0; }
  void Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action) {}
  void Get(CDataAccess *data_access) {}
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
};

#endif  // BACKEND_SRC_COMMANDS_ICOMMAND_H_

