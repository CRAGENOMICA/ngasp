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
 *  \brief     CController.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CController.h"

#include <iostream>
#include <string>
#include <cstring>    // strcmp
#include <list>
#include <algorithm>  // swap
#include <ios>        // sync_with_stdio
#include <stack>
#include <unistd.h>   // unlink

#include "IInstruction.h"
#include "../language/CStringTable.h"
#include "CInstructionFactory.h"
#include "../util/CStringTools.h"
#include "../data_manager/CDataManager.h"
#include "../data_manager/IData.h"
#include "../util/CFile.h"

#include <iterator>
#include "../commands/ICommand.h"
#include "../commands/CAllCommands.h"

CController::CController() {
  //set_stdin_active(false);
  set_history(new CInstructionsHistory());
  last_loop_id_ = 0;
  current_instruction_ = instructions_list_.begin();
  set_last_eval(true);
}

CController::~CController() {
  // Pop all elements of the queue:
  while (popInstruction()) {
    // Empty loop
  }

  // A common idiom for clearing standard containers is swapping with an empty
  // version of the container
  // Reference:
  // http://stackoverflow.com/questions/709146/how-do-i-clear-the-stdqueue-effi
  // ciently


//  std::list<IInstruction *> empty;
//  std::swap(instructions_list_, empty);

  for (std::list<IInstruction *>::iterator it = instructions_list_.begin();
       it != instructions_list_.end(); ++it) {
    delete (*it);
    (*it) = NULL;
  }

  if (history()) {
    delete history_;
    history_ = NULL;
  }
}



IInstruction *CController::getCurrentInstruction() {
  IInstruction *i = NULL;

  if (current_instruction_ != instructions_list_.end()) {
    i = (*current_instruction_);
  }

  return i;
}

void CController::SetCurrentInstructionAsLoopStart(void) {
  IInstruction *i = (*current_instruction_);

  /**
   * If this instruction is the start of a loop, let's label it with an id:
   */
  if (i->loop_id() == 0) {
      i->set_loop_id(next_loop_id());
  }
}

/**
 *
 * Before calling this function:
 *
 *        Current Instruction Instruction       label (loop_id)
 *        ------------------- -----------       -----
 *                            cmd               x
 *                            for               3
 *                            ...               0
 *                        ->> end-for           0
 *
 * After calling this function:
 *
 *        Current Instruction Instruction       label (loop_id)
 *        ------------------- -----------       -----
 *                        ->> cmd               x  (<- It won't be executed)
 *                            for               3
 *                            ...               0
 *                            end-for           -3
 */
void CController::SetCurrentInstructionAsLoopEnd(void) {
  IInstruction *i = (*current_instruction_);

  /**
   * If this instruction is the end of a loop, let's label it with an -id:
   */
  if (i->loop_id() == 0) {
      i->set_loop_id(-1 * last_loop_id());  // Same start loop id but negative.
  }

  /**
   * Go to the start of the loop:
   */
  while ((current_instruction_ != instructions_list_.begin()) &&
         ((*current_instruction_)->loop_id() != last_loop_id())){
    current_instruction_--;
  }

  /**
   * Positionate the current_instruction to the previous of the start loop.
   * In this way, the next instruction to be executed will be the start loop
   * instruction:
   */
  if (current_instruction_ != instructions_list_.begin()) {
    current_instruction_--;
  }
}

/**
 *
 * Before calling this function:
 *
 *        Current Instruction Instruction       label (loop_id)
 *        ------------------- -----------       -----
 *                        ->> for               3
 *                            ...               0
 *                            end-for           -3
 *                            cmd               0
 *
 * After calling this function:
 *
 *        Current Instruction Instruction       label (loop_id)
 *        ------------------- -----------       -----
 *                            for               0
 *                            ...               0
 *                            end-for           0
 *                        ->> cmd               0
 *
 * The last_loop_id must be changed:
 *
 *    a) If we had this before calling this function:
 *        loop { id=1
 *            loop { id = 2
 *                loop { id = 3 <---
 *                }
 *                loop { id not set yet
 *                }
 *            }
 *        }
 *
 *    b) And now we have this:
 *        loop { id=1
 *            loop { id = 2
 *                loop { id = 0
 *                }
 *                <---
 *                loop { id not set yet
 *                }
 *            }
 *        }
 *
 *    c) The last_loop_id must be last_loop_id - 1
 */
void CController::GetOutOfThisLoop(void) {
  /**
   * Go to the start of the loop:
   */
  while ((current_instruction_ != instructions_list_.begin()) &&
         ((*current_instruction_)->loop_id() == 0)){
    current_instruction_--;
  }

  IInstruction *i = (*current_instruction_);

  /**
   * Set 0 to the start of the loop:
   */
  int end_loop_id = -1 * i->loop_id();
  i->set_loop_id(0);

  /**
   * Go to the end of the loop:
   */
  while ((current_instruction_ != instructions_list_.end()) &&
         ((*current_instruction_)->loop_id() != end_loop_id)){
    current_instruction_++;
    i = (*current_instruction_);
  }

  /**
   * Set 0 to the end of the loop:
   */
  i->set_loop_id(0);

  /**
   * The next instruction to be executed is the next one to 'i'.
   */
//  /**
//   * Get out of the loop. Go to next instruction:
//   */
//  if (current_instruction_ != instructions_list_.end()) {
//    current_instruction_++;
//    i = (*current_instruction_);
//  }

  last_loop_id_ -= 1;
  
  
  /*
   * Example of a loop that it is executed 2 times:
   * 
   * for
   * end-for
   * 
   * for
   * end-for
   * 
   * for
   * 
   * It has 3 "for" and 2 "end-for". The next sentence writes the third missing "end-for":
   */
  
  DEBUG_MSG << "$ " << STR(CMD_END_FOREACH)  END_MSG;  
}

void CController::SkipAllInstructions(void) {
  /**
   * Go to the end:
   */
  while (current_instruction_ != instructions_list_.end()) {
    current_instruction_++;
  }
}


bool CController::popInstruction(void) {
  bool bPopOk = false;

  // Get the object from the queue:
  // if (!instructions_list_.empty()) {
  if (current_instruction_ != instructions_list_.end()) {
    IInstruction *instruction =
        static_cast<IInstruction *>(*current_instruction_);

    if (instruction != NULL) {
      // Add the executed instruction to the history:
      history()->AddInstruction(instruction->GetAllCommandLine());

      // Remove the object from the queue:
      if (bExistActiveLoops() == false) {
//         instructions_list_.pop();
//        // Delete the object from memory:
//        if (instruction != NULL) {
//          delete instruction;
//          instruction = NULL;
//          bPopOk = true;
//        }
      }

      // Move current instruction pointer to the next instruction:
      if (current_instruction_ != instructions_list_.end()) {
        current_instruction_++;

        if (current_instruction_ != instructions_list_.end()) {
          instruction = static_cast<IInstruction*>(*current_instruction_);

          instruction->ReplaceConstants(&constants_);

          ConditionalTasks();
        }
      }
    }
  }

  return bPopOk;
}

/*
 * == ============ ========== ========== ============ =============================
 * #  EXECUTE NEXT CODE       LAST_EVAL	 STACK        ACTION
 * == ============ ========== ========== ============ =============================
 * 01                         YES        {}           Last Eval is YES by default
 * 02 YES          IF TRUE    YES        {YES}        Push previous Last Evaluation
 * 03 YES            IF TRUE  YES        {YES, YES}	  Push previous Last Evaluation
 * 04 NO             ELSE     NO         {YES, YES}	  Inverse Last Evaluation
 * 05 YES            ENDIF    YES        {YES}        Pop Last Evaluation
 * 06 NO           ELSE       NO         {YES}        Inverse Last Evaluation
 * 07 NO             IF TRUE  NO*        {YES,	NO}   Push previous Last Evaluation. But "If" command not done because stack.top is NO.
 * 08 NO             ELSE     NO*        {YES,	NO}   Else not done and inverse not done because stack.top is NO.
 * 09 NO             ENDIF    NO         {YES}        Pop Last Evaluation
 * 10 YES          ENDIF      YES				 {}           Pop Last Evaluation
 * 11 NO           IF FALSE	  NO         {YES}        Push previous Last Evaluation
 * 12 NO             IF TRUE  NO*        {YES, NO}    Push previous Last Evaluation. But "If" command not done because stack.top is NO.
 * 13 NO             ELSE     NO*        {YES, NO}    Else not done and inverse not done because stack.top is NO.
 * 14 NO             ENDIF    NO         {YES}        Pop Last Evaluation
 * 15 YES          ELSE       YES        {YES}        Inverse Last Evaluation
 * 16 NO             IF FALSE NO         {YES,	YES}	Push previous Last Evaluation
 * 17 YES            ELSE     YES        {YES,	YES}  Inverse Last Evaluation
 * 18 YES            ENDIF    YES        {YES}        Pop Last Evaluation
 * 19 YES          ENDIF      YES				 {}           Pop Last Evaluation
 *
 * EXECUTE NEXT is (LAST_EVAL && STACK TOP)
*/
void CController::ConditionalTasks(void) {
  IInstruction *instruction = static_cast<IInstruction*>(*current_instruction_);

  if (instruction->command_name() == STR(CMD_IF)) {
    /// Push previous last evaluation
    if_stack_.push(last_eval());
  }

  if (instruction->command_name() == STR(CMD_ELSE)) {
    if (if_stack_.top() == true) {
      /// Inverse last evaluation
      set_last_eval(!last_eval());
    } else {
      // Case 08: Else not done and inverse not done because stack.top is NO.
    }
  }

  if (instruction->command_name() == STR(CMD_END_IF)) {
    if (if_stack_.empty() == false) {
      /// Pop last evaluation
      set_last_eval(if_stack_.top());
      if_stack_.pop();
    }
  }
}

bool CController::execute_next_instruction(void) {
  bool stack_top = (if_stack_.empty())?true:if_stack_.top();

  return ((last_eval() == true) && (stack_top == true));
}

bool CController::pushInstruction(std::string szCommandLineInstruction) {
  IInstruction *instruction = CInstructionFactory::GetInstruction(
      KeyString::INSTRUCTION_COMMAND_LINE);
  instruction->set_manager(manager());
  instruction->set_command_arguments(szCommandLineInstruction);

  return pushInstruction(instruction);
}

bool CController::pushInstruction(int argc, char *argv[]) {
  IInstruction *instruction = CInstructionFactory::GetInstruction(
      KeyString::INSTRUCTION_COMMAND_LINE);
  instruction->set_manager(manager());
  instruction->set_command_arguments(argc, argv);

  return pushInstruction(instruction);
}

bool CController::pushInstruction(IInstruction *instruction) {
  bool success = true;

  if (instruction->general_options_list()->size() > 0) {
    success = generateNewInstructionsFromGeneralOptions(
        instruction->general_options_list());
  }

  if ((success) && (instruction->command_name() != "")) {
    instructions_list_.push_back(instruction);

// Previously:
//    /// The current instruction pointer is initially set to the first
//    /// instruction here:
//    if (current_instruction_ == instructions_list_.end()) {
//      current_instruction_ = instructions_list_.begin();
//    }
// Now:
//    /// The current instruction pointer is initially set to the this
//    /// instruction if the pointer pointers to .end(). That means two cases:
//    /// case 1: the list is empty and the pointer will pointer to the first one.
//    /// case 1: the list has items (all executed). The pointer will pointer to the last one.
    if (current_instruction_ == instructions_list_.end()) {
      current_instruction_ = instructions_list_.end();
      --current_instruction_;
    }
  } else {
    // This instruction does not have a valid command, so it is deleted:
    delete instruction;
    instruction = NULL;
    success = false;
  }

  return success;
}

bool CController::generateNewInstructionsFromGeneralOptions(
    std::list<std::string> *instruction_general_options) {
  bool success = true;

  for (std::list<std::string>::iterator
      general_option = instruction_general_options->begin();
      ((general_option != instruction_general_options->end()) &&
      (success == true));
      general_option++ ) {
    std::string new_instruction = STR(NGASP_APP_EXECUTABLE_NAME) + STR(SPACE);

    if ((*general_option)[1] == STRC(GOS_HELP_SHORT)) {
      new_instruction += STR(CMD_APP_HELP); //GOS_HELP_SHORT);
      success &= pushInstruction(new_instruction);
    } else {
      if ((*general_option)[1] == STRC(GOS_VERSION_SHORT)) {
        new_instruction += STR(CMD_APP_VERSION); // STR(GOS_VERSION_SHORT);
        success &= pushInstruction(new_instruction);
      } else {
        if ((*general_option)[1] == STRC(GOS_VERBOSE_SHORT)) {
          general_option++;
          if (general_option != instruction_general_options->end()) {
            new_instruction += STR(CMD_VERBOSE); // STR(GOS_VERBOSE_SHORT);
            new_instruction += STR(SPACE);
            new_instruction += "-l";
            new_instruction += STR(SPACE);
            new_instruction += (*general_option);
            success &= pushInstruction(new_instruction);
          } else {
            general_option--;
            ERROR_MSG << STR(VERBOSE_LEVEL_MISSING) END_MSG;
          }
        } else {
          if ((*general_option)[1] == STRC(GOS_DRYRUN_SHORT)) {
            general_option++;
            if (general_option != instruction_general_options->end()) {
              new_instruction += STR(GOS_DRYRUN_SHORT);
              new_instruction += STR(SPACE);
              new_instruction += "-x";
              new_instruction += STR(SPACE);
              new_instruction += (*general_option);
              success &= pushInstruction(new_instruction);
            } else {
              general_option--;
              ERROR_MSG << STR(DRY_RUN_SET_MISSING) END_MSG;
            }
          } else {
            ERROR_MSG << "'" << (*general_option) << "'"
                             << STR(COMMAND_NOT_FOUND) END_MSG;
            success = false;
          }
        }
      }
    }
  }

  return success;
}

bool CController::instructionsWaiting() {
  return (current_instruction_ != instructions_list_.end());
  // return (instructions_list_.size() > 0);
}

bool CController::GetInstructionFromStdin(void) {
  bool success = false;

  std::string instruction;
  std::string line;

  while (!success) {
    line = "";

    // This loop waits the user for a new instruction:
    while (line == "") {
      std::cout << STR(PROMPT);
      std::getline(std::cin, line);
    }

    // Add the instruction to the queue:
    instruction = STR(NGASP_APP_EXECUTABLE_NAME);
    instruction += STR(SPACE);
    instruction += line;
    success = this->pushInstruction(instruction);

    // If the instruction is well formed, success will be true and
    // the while loop will end.
  }

  return success;
}

/*
 ******  *****  **   *
 *    *    *    * *  *
 *   *     *    *  * *
 *    *    *    *   **
 ******  *****  *    *
 */

bool CController::GetInstructionFromPipe(void) {
  bool success = false;

  std::string line = named_pipe_.WaitMessageFromLocalManager();

//static std::string pline = "";
//if (pline != line) {
//  pline = line;
//  std::cout << "ngasp: line: " << line << std::endl;
//} else {
//}

  if (line != "") {
    std::string command = CStringTools::GetString(line, tPosition::GET_LEFT, STR(COMMAND_SEPARATOR)[0]);
    std::string params = CStringTools::GetString(line, tPosition::GET_RIGHT, STR(COMMAND_SEPARATOR)[0]);

    CStringTools::Replace(params, "\n", "");

//    if (command == "SAVE_DATA_MANAGER_STATE") {
//    } else {
    if (command == "DATA_MANAGER_VARIABLES") {
      std::string dm_vars_json = "{data:[";
      std::map< std::string, IData *>::iterator it;
      for (it = manager()->data_manager()->repository()->begin();
           it != manager()->data_manager()->repository()->end(); ++it) {
        if (it != manager()->data_manager()->repository()->begin()) {
          dm_vars_json += ",";
        }
        dm_vars_json += it->second->ToJSON();
      }
      dm_vars_json += "]}";
      named_pipe_.SendPipeMessageToLocalManager(dm_vars_json);
    } else {
    // Before, the log file was save by demand with this event "SAVE_COUT_FILE".
    // Now, the log file is saved before and after every command is executed.
    // So, the LM can access the log file without requesting it to the BIN.
    // Because the BIN is busy running one command from one pipe
    /*if (command == "SAVE_COUT_FILE") {
      manager()->logger()->WriteFile();
      named_pipe_.SendPipeMessageToLocalManager("OK");
    } else {*/
    if (command == "CLEAN_EXPERIMENT_RESULT") {
      // std::cout << "----- Unlink = " << manager()->logger()->cout_file_name().c_str() << std::endl;
      unlink(manager()->logger()->output_descriptors_.top()->name_.c_str());
      named_pipe_.SendPipeMessageToLocalManager("OK");
    } else {
    if (command == "STATUS") {
      if (getCurrentInstruction() == NULL) {
        // All instructions have been executed
        named_pipe_.SendPipeMessageToLocalManager("OPEN");
      } else {
        // There are instructions waiting to be executed
        named_pipe_.SendPipeMessageToLocalManager("WORKING");
      }
    } else {
    if (command == "********** USE ME *********") {
    } else {
    if (command == "DRY_RUN") {
      experiment_id_ = CStringTools::ToInt(CStringTools::GetString(params, tPosition::GET_LEFT, STR(PARAM_SEPARATOR)[0]));
      command = CStringTools::GetString(params, tPosition::GET_RIGHT, STR(PARAM_SEPARATOR)[0]);

      // Add the instruction to the queue:
      std::string instruction;
      instruction = STR(NGASP_APP_EXECUTABLE_NAME);
      instruction += STR(SPACE);
      instruction += command;

      //*****
      std::cout << instruction << std::endl;
      success = true;
      //***** 

      named_pipe_.SendPipeMessageToLocalManager("OK");
    } else {
    if (command == "RUN") {
      experiment_id_ = CStringTools::ToInt(CStringTools::GetString(params, tPosition::GET_LEFT, STR(PARAM_SEPARATOR)[0]));
      command = CStringTools::GetString(params, tPosition::GET_RIGHT, STR(PARAM_SEPARATOR)[0]);

      // Add the instruction to the queue:
      std::string instruction;
      instruction = STR(NGASP_APP_EXECUTABLE_NAME);
      instruction += STR(SPACE);
      instruction += command;

      // *****
      success = pushInstruction(instruction);
      // manager()->logger()->WriteFile();
      // *****

      // std::cout << "----- Number of instructions in the instructions_list = " << instructions_list_.size() << std::endl;
      named_pipe_.SendPipeMessageToLocalManager("OK");
    }}}}}}/*}*/
  }
        
  return success;
}

void CController::AddConstant(const std::string & cte,
                              const std::string & value) {

  bool found = false;
  for (std::list<std::pair<std::string, std::string> >::iterator it
          = constants_.begin(); ((it != constants_.end()) && (!found)); ++it) {
    if ((*it).first == cte) {
       (*it).second = value;
       found = true;
    }
  }

  if (!found) {
      constants_.push_back(std::pair<std::string, std::string>(cte, value));
  }
}


