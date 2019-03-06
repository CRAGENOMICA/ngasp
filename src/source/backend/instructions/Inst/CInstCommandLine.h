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
 *  \brief     CInstCommandLine.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_INSTRUCTIONS_INST_CINSTCOMMANDLINE_H_
#define BACKEND_SRC_INSTRUCTIONS_INST_CINSTCOMMANDLINE_H_

#include <string>
#include <list>

#include "../IInstruction.h"

#define PARAMS_SEPARATOR ' '

/**
 * This class stores one command line instruction in this format:
 *   ngaSP {GOS} CMD {COS}.
 *
 * It receives the data from:
 *   1) int argc, char **argv
 *   2) std::string like "ngaSP help"
 *
 * It stores the data in this way:
 *   a) arguments_ = { "ngaSP", "GOS1", "GOSn", "CMD", "COS1", "COSn" }
 *   b) command_name_ = "CMD"
 *   c) general_options_list_ = { "GOS1", "GOSn" }
 *   d) command_arguments_ = { "CMD", "COS1", "COSn" }
 */
class CInstCommandLine: public IInstruction {
 public:
  CInstCommandLine();
  virtual ~CInstCommandLine();

 private:
  std::list<std::string> *arguments_;

 public:
  inline std::list<std::string> *arguments() const { return arguments_; }
  void set_command_arguments(int argc, char **argv);
  void set_command_arguments(const std::string & _szCommand);
  void ClearArguments(void);

 private:
  /**
   * This method returns the position of CMD in:
   *   arguments_ = { "ngaSP", "GOS1", "GOSn", "CMD", "COS1", "COSn" }
   * If a valid command is not found, the method returns end()
   */
  std::list<std::string>::iterator GetCommandPosition();

  /**
   * This method fills:
   *   general_options_list_ = { "GOS1", "GOSn" }
   */
  void ExtractGeneralOptions();

  /**
   * This method fills:
   *   command_arguments_ = { "CMD", "COS1", "COSn" }
   */
  void SetInstruction();
};


#endif  // BACKEND_SRC_INSTRUCTIONS_INST_CINSTCOMMANDLINE_H_
