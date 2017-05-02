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
 *  \brief     CInstructionsHistory.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 30, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_INSTRUCTIONS_CINSTRUCTIONSHISTORY_H_
#define BACKEND_SRC_INSTRUCTIONS_CINSTRUCTIONSHISTORY_H_

#include <list>
#include <string>

class CInstructionsHistory {
 public:
  CInstructionsHistory();
  virtual ~CInstructionsHistory();

 private:
  std::list<std::string> *instructions_;

 public:
  inline std::list<std::string> *instructions() const { return instructions_; }
  inline void set_instructions(std::list<std::string> *instructions) {
    instructions_ = instructions;
  }

 public:
  void ClearHistoryFromFile();
  std::string GetInstruction(int id);
  void AddInstruction(const std::string &instruction);

 private:
  void LoadFromFile();
  void ClearHistoryFromMemory();
};

#endif  // BACKEND_SRC_INSTRUCTIONS_CINSTRUCTIONSHISTORY_H_
