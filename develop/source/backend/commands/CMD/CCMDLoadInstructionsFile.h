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
 *  \brief     CCMDLoadInstructionsFile.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      March 30, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDLOADINSTRUCTIONSFILE_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDLOADINSTRUCTIONSFILE_H_

#include <string>

#include "../ICommand.h"
#include "../../util/CFile.h"

class CCMDLoadInstructionsFile : public ICommand {
 public:
  CCMDLoadInstructionsFile();
  ~CCMDLoadInstructionsFile();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 public:
  enum InstructionsFileType {
    UNDEFINED,
    YAML_INSTRUCTIONS_FILE,
    CMD_INSTRUCTIONS_FILE
  };

 private:
  InstructionsFileType format_;
  std::string file_name_;
  std::string values_file_name_;

 public:
  inline void set_format(InstructionsFileType format) { format_ = format; }
  inline InstructionsFileType format() { return format_; }

  inline void set_file_name(std::string file_name) { file_name_ = file_name; }
  inline std::string file_name() { return file_name_; }

  inline void set_values_file_name(std::string values_file_name) {
    values_file_name_ = values_file_name;
  }
  inline std::string values_file_name() { return values_file_name_; }

 private:
    void SendInstruction(std::string & instruction_str);
    void TreatCFile(std::string ngasp_code, bool valfile);
};



#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDLOADINSTRUCTIONSFILE_H_
