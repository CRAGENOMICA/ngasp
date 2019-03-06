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
 *  \brief     IInstruction.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 9, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_INSTRUCTIONS_IINSTRUCTION_H_
#define BACKEND_SRC_INSTRUCTIONS_IINSTRUCTION_H_

#include <string>
#include <list>

#include "../IBase.h"

class IInstruction : public IBase {
 public:
  IInstruction();
  virtual ~IInstruction();

 public:
  virtual void SetInstruction() = 0;

 protected:
  std::string command_name_;
  std::list<std::string> *command_arguments_;
  std::list<std::string> *general_options_list_;
  int loop_id_;  // identificator of starting loop

 public:
  void ClearCommandArguments(void);
  void ClearGeneralOptions(void);

 public:
  inline void set_command_name(const std::string & command_name) {
    command_name_ = command_name;
  }
  inline std::string command_name(void) const { return command_name_; }

  inline std::list<std::string> *command_arguments() const {
    return command_arguments_;
  }
  virtual void set_command_arguments(int argc, char **argv) = 0;
  virtual void set_command_arguments(const std::string & _szCommand) = 0;

  inline std::list<std::string> *general_options_list() const {
    return general_options_list_;
  }

  inline void set_loop_id(int loop_id) { loop_id_ = loop_id; }
  inline int loop_id(void) { return loop_id_; }

 public:
  /// For compatibility with command "mstatspop v.1":
  /// Used for CInstructionsHistory, too:
  std::string GetAllCommandLine(void);

  /**
   * CONSTANTS
   */
  void ReplaceConstantsInText(
                std::list<std::pair<std::string, std::string> > *constants,
                std::string & text);

  void ReplaceConstants(std::list<std::pair<std::string, std::string> >
                        *constants);
};

#endif  // BACKEND_SRC_INSTRUCTIONS_IINSTRUCTION_H_
