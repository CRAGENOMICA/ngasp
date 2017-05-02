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
 *  \brief     CInstructionsHistory.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 30, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CInstructionsHistory.h"

#include <list>
#include <string>
#include <algorithm>

#include "../util/CFile.h"
#include "../language/CStringTable.h"

CInstructionsHistory::CInstructionsHistory() {
  set_instructions(new std::list<std::string>);

  LoadFromFile();
}

CInstructionsHistory::~CInstructionsHistory() {
  if (instructions()) {
    delete instructions_;
    instructions_ = NULL;
  }
}

void CInstructionsHistory::ClearHistoryFromMemory() {
  if (instructions()) {
    instructions()->clear();
  }
}

void CInstructionsHistory::LoadFromFile() {
  ClearHistoryFromMemory();

  CFile history_file(STR(INSTRUCTIONS_HISTORY_FILE));

  if (history_file.Open()) {
    std::string instruction;

    while (history_file.ReadLine(&instruction)) {
        if (instruction != "") {
          instructions()->push_back(instruction);
        }
    }

    history_file.Close();
  }
}
void CInstructionsHistory::ClearHistoryFromFile() {
  ClearHistoryFromMemory();
  CFile::ReplaceContentBy(STR(INSTRUCTIONS_HISTORY_FILE), "");
}

void CInstructionsHistory::AddInstruction(const std::string &instruction) {
  instructions()->push_back(instruction);
  CFile::Append(STR(INSTRUCTIONS_HISTORY_FILE), instruction + STR(EOL));
}

std::string CInstructionsHistory::GetInstruction(int id) {
  std::string instruction;

  int counter = 1;
  for (std::list<std::string>::iterator it = instructions()->begin();
       ((it != instructions()->end()) && (instruction == ""));
       ++it) {
    if (counter == id) {
      instruction = *it;
    }

    counter++;
  }

  instruction.erase(std::remove(instruction.begin(), instruction.end(), '\n'),
                    instruction.end());
  instruction.erase(std::remove(instruction.begin(), instruction.end(), '\r'),
                    instruction.end());

  return instruction;
}

