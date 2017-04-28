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
 *  \brief     CController.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_INSTRUCTIONS_CCONTROLLER_H_
#define BACKEND_SRC_INSTRUCTIONS_CCONTROLLER_H_

#include <string>
#include <list>
#include <stack>

#include "../IBase.h"
#include "IInstruction.h"
#include "CInstructionsHistory.h"

#include "../ipc/CNamedPipeManager.h"

// One second = 1000 ms. It is used for waiting the stdin data:
#define ONE_SECOND 1000

/**
 * All instructions are stored in a list.
 * Every new instruction is stored at the end of the list.
 * All new instructions generated by one instruction are stored following the father instruction. <<---- ??
 * When an start loop instruction appears, it is labeled with a loop id.
 * When an end loop instruction appears, the pointer to instructions is moved
 * to the beggining of its the loop.
 * Instructions can be discarded if they are not in an active loop.
 */

class CController : public IBase {
 public:
  CController();
  ~CController();

 private:
  int experiment_id_;

 private:
  std::list<IInstruction *> instructions_list_;
  std::list<IInstruction *>::iterator current_instruction_;

 public:
  bool generateNewInstructionsFromGeneralOptions(
      std::list<std::string> *instruction_general_options);

  bool pushInstruction(IInstruction *instruction);

  /**
  * This function adds a new command line instruction to the end of the queue.
  */
  bool pushInstruction(std::string szCommandLineInstruction);

  /**
  * This function adds a new command line instruction to the end of the queue.
  */
  bool pushInstruction(int argc, char *argv[]);

  /**
  * This function gets a pointer to the current instruction.
  * You do not need to delete the returned object.
  * To get the next instruction call the popInstruction in order to
  * remove the current instruction and if you call this function you will get a
  * pointer to the new current instruction.
  */
  IInstruction * getCurrentInstruction();

  /**
  * This function removes the current instruction from the queue.
  * It returns true if it succeeded.
  * It returns false if the queue is empty.
  * Do not call this function for getting the next instruction. Call it to
  * destroy it.
  */
  bool popInstruction(void);



  /**
  * This function returns true if the queue has instructions waiting to be
  * executed.
  */
  bool instructionsWaiting();

  /**
  * This function is called when the application is first started and detects
  * from where new instructions are coming from.
  * New instructions could arrive from the stdin, from the command line, etc.
  * This function detects the source of these instructions and send them to
  * the instructions queue.
  */
  void fetchInitialInstructions(int _argc, char *_argv[]);

/**
 * Stdin
 */
 public:
  //bool stdin_active_;  /// Instructions are coming from the standard input
  CNamedPipeManager named_pipe_;
  

 public:
//  inline void set_stdin_active(bool stdin_active) {
//    stdin_active_ = stdin_active;
//  }
//  inline int stdin_active(void) { return stdin_active_; }

  inline void CreateNamedPipe(std::string name) {
    named_pipe_.CreatePipes(name);
  }
//  inline bool pipe_active(void) { return named_pipe_.pipe_active(); }
//  inline void set_pipe_active(bool pipe_active) {
//    named_pipe_.set_pipe_active(pipe_active);
//    if (pipe_active == false) {
//      ClosePipes();
//    }
//  }

  inline std::string GetNamedPipeName(void) {
      return named_pipe_.fifo_named_pipe_name();
  }

  inline void ClosePipes(void) { named_pipe_.ClosePipes(); }

  bool GetInstructionFromStdin(void);
  bool GetInstructionFromPipe(void);

  void SkipAllInstructions(void);

 /**
  * Loops:
  */
 private:
  int last_loop_id_;

 public:
  inline int next_loop_id(void) { return ++last_loop_id_; }
  inline int last_loop_id(void) { return last_loop_id_; }
  inline void close_loop_id(void) { --last_loop_id_; }
  bool bExistActiveLoops(void) { return !(last_loop_id_ == 0); }
  void SetCurrentInstructionAsLoopStart(void);
  void SetCurrentInstructionAsLoopEnd(void);
  void GetOutOfThisLoop(void);

 /**
  * If, Else, EndIf:
  */
 private:
  bool last_eval_;
  std::stack<bool> if_stack_;

 public:
  inline
  void set_last_eval(const bool & last_eval) {
    last_eval_ = last_eval;
  }
  inline bool last_eval(void) const {
    return last_eval_;
  }
  void ConditionalTasks(void);
  bool execute_next_instruction(void);

 /**
  * Constants:
  */
 private:
  std::list<std::pair<std::string, std::string> > constants_;

 public:
    void AddConstant(const std::string & cte, const std::string & value);

 /**
  * History:
  */
 private:
  CInstructionsHistory *history_;

 public:
  inline CInstructionsHistory *history() const { return history_; }
  inline void set_history(CInstructionsHistory *history) {
    history_ = history;
  }
};

#endif  // BACKEND_SRC_INSTRUCTIONS_CCONTROLLER_H_
