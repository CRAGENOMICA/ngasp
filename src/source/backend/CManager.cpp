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
 *  \brief     CManager.cpp
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

#include "CManager.h"

#include <string>
#include <fstream>
#include <thread>         // std::thread
#include <chrono>         // std::chrono::seconds
#include <ctime>          // clock

// About threads:
// http://stackoverflow.com/questions/10998780/stdthread-calling-method-of-class
// Properties > Build > C++ Compiler > Additional Options: -std=c++0x -pthread

#include "calculations/CCalcFactory.h"
#include "data_manager/CDataFactory.h"
#include "messages/CLogger.h"
#include "language/CStringTable.h"
#include "data_manager/CDataManager.h"
#include "commands/CAllCommands.h"
#include "instructions/CController.h"
#include "commands/COS/COptionsContainer.h"
#include "calculations/CAllCalculations.h"
#include "calculations/Calc/CCalcRandomize.h"
#include "data_manager/IDataValue.h"
#include "messages/CTimeStamp.h"

#include "data_manager/Data/CDataStdString.h"

#include "util/CClock.h"

#include "data_manager/Data/CDataInt.h"

CManager::CManager() {
  set_data_factory(NULL);
  set_calc_factory(NULL);
  set_data_manager(NULL);
  set_all_commands(NULL);
  set_instructions_controller(NULL);
  set_logger(NULL);
  set_general_options(NULL);
  set_all_calculations(NULL);

  set_with(NULL);

  output_stream_original_ = std::cout.rdbuf();  /// Get the cout standard
                                                /// output (screen)
  output_file_stream_ = NULL;                   /// The current
  set_foutput(stdout);
}

CManager::~CManager() {
  if (all_commands()) {
    delete all_commands_;
    set_all_commands(NULL);
  }
  if (data_manager()) {
    delete data_manager_;
    set_data_manager(NULL);
  }
  if (logger()) {
    delete logger_;
    set_logger(NULL);
  }
  if (instructions_controller()) {
    delete instructions_controller_;
    set_instructions_controller(NULL);
  }
  if (general_options()) {
    delete general_options_;
    set_general_options(NULL);
  }
  if (all_calculations()) {
    delete all_calculations_;
    set_all_calculations(NULL);
  }
  if (data_factory()) {
    delete data_factory_;
    set_data_factory(NULL);
  }
  if (calc_factory()) {
    delete calc_factory_;
    set_calc_factory(NULL);
  }
  if (output_file_stream_ != NULL) {
    delete output_file_stream_;
    output_file_stream_ = NULL;
    
    std::cout.rdbuf(output_stream_original_);
  }  
}

void CManager::Init() {
  //@{
  execution_mode_ = tExecutionMode::EXEC_MODE_NOT_DEFINED;
  
  CStringTable::Instance()->set_encoding("english_bn");
  
  /// Objects creation:
  set_logger(new CLogger());
  set_calc_factory(new CCalcFactory());
  set_data_factory(new CDataFactory());
  set_data_manager(new CDataManager());
  set_general_options(new COptionsContainer());
  set_all_commands(new CAllCommands());
  set_instructions_controller(new CController());
  set_all_calculations(new CAllCalculations());
  //@}

  //@{
  /// Objects configuration:

  /// Data manager
  data_manager()->set_manager(this);
  data_manager()->CreateRepository();

  /// GOS - Global Options container
  general_options()->set_manager(this);
  general_options()->DefineGeneralOptions();

  /// Commands Repository
  all_commands()->set_manager(this);
  all_commands()->IncludeAllCommands();

  /// Controller
  instructions_controller()->set_manager(this);
  
  /// Calculations Manager
  all_calculations()->set_manager(this);
  //@}

  // By default, this data will be selected:
  set_with(STR(OUTPUT_FILE));
  
  /// ==========================================================================
  /// CREATE FIXED CALCULATIONS
  /// ==========================================================================
  
  // Create the randomize calculation (only one for all)
  // and store it in the Data Manager
  CCalcRandomize *calc_randomize_ = NULL;
  calc_randomize_ = all_calculations()->GetNewCalculation(ROOT_PARENT, calc_randomize_, "calc_randomize_");  // It is a global calculation. So, ROOT_PARENT.
}

bool CManager::PrepareNextInstruction(void) {
  bool next_instruction_prepared = false;

  IInstruction *instruction = instructions_controller()->getCurrentInstruction();

  if (instruction != NULL) {

    instruction->ReplaceConstants(instructions_controller()->Constants());

    /// Get the name of the next command:
    std::string current_command_name = instruction->command_name();

    /// Find the command class by its name:
    all_commands()->set_selected_command(current_command_name);

     // This line shows instructions that are going to be executed:
      DEBUG_MSG3 << "$ " << instruction->GetAllCommandLine() END_MSG;

    /// If the command class is found, prepare it to be executed:
    if (all_commands()->selected_command() !=
        all_commands()->GetLastCommandIterator()) {
      (*all_commands()->selected_command())->set_instruction(instruction);

      if (instructions_controller()->execute_next_instruction() == true) {
        
        next_instruction_prepared = (*all_commands()->selected_command())->Prepare();
      }
     
      if (next_instruction_prepared == true) {
      }
      else {
        // If the instruction preparation fails, remove the instruction
        // from queue:
        instructions_controller()->popInstruction();
      }
    }
  }

  return next_instruction_prepared;
}

void CManager::LaunchNextInstruction(void) {
  IInstruction *instruction = instructions_controller()->getCurrentInstruction();

  if (instruction != NULL) {
      
std::string aux = instruction->GetAllCommandLine();

    /// Run command:
    if (all_commands()->selected_command() !=
        all_commands()->GetLastCommandIterator()) {

        if (instructions_controller()->execute_next_instruction() == true) {
        // This line shows only executed instructions:
        // Problem: I want to see not executed instructions too! (those that do not pass Prepare() function)
        // DEBUG_MSG3 << "$ " << instruction->GetAllCommandLine() END_MSG;
      NORMAL_MSG3 << "selected_command: " << all_commands()->selected_command() END_MSG;

        // =====================================================================
        // Start Clock
        // =====================================================================
        CClock lapse_clock;
        lapse_clock.Start();
        // =====================================================================
        
        (*all_commands()->selected_command())->Run();
        (*all_commands()->selected_command())->Finalize();
        
        // =====================================================================
        // End Clock
        // =====================================================================
        DEBUG_MSG3 << lapse_clock.Stop() END_MSG;
        // =====================================================================
      }

      // When finalized, remove the instruction from queue:
      instructions_controller()->popInstruction();

      // If instructions are executed in pipe mode then export the DM state after
      // each instruction execution in JSON format so that the web interface can
      // access to this information:
      if (execution_mode() == WORKER) {
        data_manager()->ExportToJSON(instructions_controller()->GetNamedPipeName());
      }
    }
  }
}

void CManager::CleanAndClose(void) {
  CStringTable::ResetInstance();
}

// This function is used only with global variables. So, ROOT_PARENT.
void CManager::set_with(const std::string & name) {
  set_with(data_manager()->GetDataByName(ROOT_PARENT, name));
  if (with() == NULL) {
    set_with(all_calculations()->GetCalculationByName(ROOT_PARENT, name));
  }
}

// This function is used only with global variables. So, ROOT_PARENT.
IObject *CManager::with(const std::string & name) const {
  IObject * object = with();  // By default

  if (name != "") {
    object = (IObject *)(data_manager()->GetDataByName(ROOT_PARENT, name));
    if(object == NULL) {
      object = (IObject *)(all_calculations()->GetCalculationByName(ROOT_PARENT, name));
    }
  }

  return object;
}

/// This function executes ONE command line ([GOS]*[CMD]?[COS]*).
///
void CManager::RunCommandLineExecutionMode(int argc, char *argv[]) {
  // add this instruction to the queue
  instructions_controller()->pushInstruction(argc, argv);

  // This loop executes one command line only. But one command line could
  // generate more than one instruction. It's because of this that this is a 
  // while here:
  while (instructions_controller()->instructionsWaiting()) {
    if (PrepareNextInstruction()) {
      LaunchNextInstruction();
    }
  }
}


/// This function shows a prompt to the user and he/she can introduce commands.
/// The application ends when the user enters the CCMDStop command.
///
void CManager::RunInteractiveShellExecutionMode(void) {
  /// Show presentation
  /// -----------------

  NORMAL_MSG3 << STR(EOL)
              << STR(PRESENTS_CONNECTED_TO)
              << CTimeStamp::GetTimeNow()
              << STR(EOL)
              << STR(BOLD_START)
              << STR(PRESENTS_WELCOME)
              << STR(BOLD_END)
              END_MSG;
  
  /// Get and execute instructions in this loop. One after another
  /// ------------------------------------------------------------

  while (execution_mode() == INTERACTIVE_SHELL) {
    /// This function waits for instructions:
    instructions_controller()->GetInstructionFromStdin();
    
    if (instructions_controller()->instructionsWaiting()) {
      if (PrepareNextInstruction() == true) {
        LaunchNextInstruction();
      }
    }
  }
  
  /// Show closure:
  /// -------------

  NORMAL_MSG3 << STR(PRESENTS_CONNECTION_TO)
              << STR(NGASP_APP_NAME)
              << STR(PRESENTS_CONNECTION_CLOSED)
              << STR(EOL)
              << STR(EOL)
              END_MSG;  
}

/// This function opens the CCMDSocket. It has a loop for receiving commands via
/// TCP.
///
void CManager::RunLocalManagerExecutionMode(int argc, char *argv[]) {
  /// Execute the instruction CMDSocket
  /// ---------------------------------

  instructions_controller()->pushInstruction(argc, argv);
        
  if (PrepareNextInstruction() == true) {
    LaunchNextInstruction();
  }  
  
  /// Save application state (data manager variables, values, ...).
  /// -------------------------------------------------------------
  
  data_manager()->SaveState(STR(DM_FILE_NAME)); 
}


void GetWorkerInstructionsThread(CManager *manager) {
  while (manager->execution_mode() == WORKER) {
    if (manager->instructions_controller()->instructionsWaiting() == false) {
      manager->instructions_controller()->GetInstructionFromPipe();  // waits
    }  
  }
}

/// This function executes the CCMDPipe that prepares the system for reading 
/// from a named pipe. Once the CCMDPipe prepares the pipe, a thread is created
/// for getting instructions from the pipe.
/// And then this function executes all instructions.
///
void CManager::RunWorkerExecutionMode(int argc, char *argv[]) {
  /// Execute the instruction CMDPipe
  /// -------------------------------

  instructions_controller()->pushInstruction(argc, argv);
        
  if (PrepareNextInstruction() == true) {
    LaunchNextInstruction();
  } 
  
  /// Get instructions from a named pipe in a separated thread
  /// --------------------------------------------------------

  std::thread threadGetInstructions(
            GetWorkerInstructionsThread,  // This is the thread function
            this);                        // This is the function's parameter  
  
  
  while (execution_mode() == WORKER) {
    if (instructions_controller()->instructionsWaiting()) {
      if (PrepareNextInstruction() == true) {
        LaunchNextInstruction();
        logger()->WriteFile();
      }
    }
  }
  
  /// Wait the thread to be finished:
  /// -------------------------------

  threadGetInstructions.join();  
  
  /// Save application state (data manager variables, values, ...).
  /// -------------------------------------------------------------
  
  data_manager()->SaveState(instructions_controller()->GetNamedPipeName()); 
}

void CManager::RedirectCoutToFile(const std::string &file_name) {
  output_stream_original_ = std::cout.rdbuf(); //save old buf
  
  if (output_file_stream_ != NULL) {
    delete output_file_stream_;
    output_file_stream_ = NULL;
  }
  
  output_file_stream_ = new std::ofstream(file_name);
  
  std::cout.rdbuf(output_file_stream_->rdbuf());
  
  // (mstatspop compatibility)
  //FILE *foutput = fopen(file_name.c_str(), "w+");
  FILE *foutput = freopen(file_name.c_str(), "w+", stdout);
  set_foutput(foutput);
}

void CManager::RedirectCoutToScreenAgain(void) {
  if (output_stream_original_ != NULL) {
    std::cout.rdbuf(output_stream_original_);
  }
  
  if (output_file_stream_ != NULL) {
    delete output_file_stream_;
    output_file_stream_ = NULL;
  }
  
  if (foutput() != NULL) {
    // (mstatspop compatibility)
    fflush(stdout);
    fclose(foutput());
      
    #ifdef __WIN32__
    // https://support.microsoft.com/en-us/kb/58667
    FILE *foutput = freopen("CON", "w", stdout);
    #else
    // http://stackoverflow.com/questions/1908687/how-to-redirect-the-output-back-to-the-screen-after-freopenout-txt-a-stdo
    FILE *foutput = freopen ("/dev/tty", "a", stdout);
    #endif

    set_foutput(foutput);
  }
}
 
void CManager::ActivateError(void) {
  CDataInt *result = (CDataInt *)data_manager()->GetDataByName(ROOT_PARENT, STR(RESULT));  // This is a global variable. So, its parent is ROOT_PARENT.
  result->set_value(1);
}
