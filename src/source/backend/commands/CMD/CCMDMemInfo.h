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
 *  \brief     CCMDMemInfo.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 28, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDMEMINFO_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDMEMINFO_H_

#include <string>

#include "../ICommand.h"

class CCMDMemInfo : public ICommand {
 public:
  CCMDMemInfo();
  virtual ~CCMDMemInfo();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 private:
  PrintMode print_mode_;

 private:
  std::string PrepareField(std::string text,
                           int column_width,
                           bool is_number,
                           bool selected);


 public:
  inline void set_print_mode(const PrintMode & print_mode) {
    print_mode_ = print_mode;
  }

  inline void set_print_mode(const std::string & print_mode) {
    if (print_mode == "normal") {
      print_mode_ = PrintMode::NORMAL;
    } else {
      if (print_mode == "json") {
        print_mode_ = PrintMode::JSON;
      } else {
        if (print_mode == "ngasp") {
          print_mode_ = PrintMode::NGASP;
        } else {
          if (print_mode == "value") {
            print_mode_ = PrintMode::VALUE;
          } else {
            if (print_mode == "string_value") {
              print_mode_ = PrintMode::STRING_VALUE;
            } else {
              print_mode_ = PrintMode::NORMAL;
            }
          }
        }
      }
    }
  }
  inline PrintMode print_mode(void) const { return print_mode_; }
};

#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDMEMINFO_H_
