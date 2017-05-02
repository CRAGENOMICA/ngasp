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
 *  \brief     CCalcExec.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      March 9, 2016
 *  \pre
 *  \bug
 *  \warning
 *  \copyright Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera
 *             Rodríguez, Centre for Research in Agricultural Genomics (CRAG).
 *             All rights reserved.
 *  \license   LGPL 2.1
 */
#include "CCalcExec.h"

#include <cmath>

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"

#include <stdlib.h>  // system()
#include <unistd.h>  // execl, execlp, execle, execv, execvp, execvpe - execute a file 
#include <vector>
#include <string>

#include <stdio.h>  /* defines FILENAME_MAX */

#ifdef __WIN32__
#include <direct.h>
#define GetCurrentDir _getcwd
#define SetCurrentDir _chdir
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#define SetCurrentDir chdir
#endif



CCalcExec::CCalcExec()
: ICalculation(KeyString::CALC_EXEC,
               KeyString::CALC_EXEC_BRIEF_DESC,
               KeyString::CALC_EXEC_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(command,                                                     // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCEXEC_COMMAND,                                           // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(working_directory,                                           // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCEXEC_WORKING_DIRECTORY,                                 // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(type,                                                        // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCEXEC_TYPE,                                              // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)

    SET_OUTPUT_INFO(result,                                                     // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALCEXEC_RESULT,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcExec::~CCalcExec() {
}

void CCalcExec::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(command)
    DM_INPUT(working_directory)
    DM_INPUT(type)
  DM_GET_OUTPUTS
    DM_OUTPUT(result)
  DM_END
}

void CCalcExec::Calculate(bool dry_run) {


  int result_value = 1;  // 1 means that return is ERROR. (default value)
                         // 0 means that return is OK.
  
  if (type->value() == "") {
    // If no type is passed then this is the default type value
    type->set_value(STR(EXEC_TYPE_SYS));
  }

  bool do_execute = true; // If something fails then put this flag to false and
                          // the execution will not be done.
  
  
  // ===========================================================================
  // Fix the command line:
  // It is "\"arg0 arg1 arg2 ... argN\"" and should be "arg0 arg1 arg2 ... argN"
  // ===========================================================================

  std::string command_to_execute = command->value();

  if (command_to_execute.at(0) == '"') {
    // Remove first quotes
    command_to_execute = command_to_execute.substr(1);
  }
  if (command_to_execute.at(command_to_execute.length()-1) == '"') {
    // Remove last quotes
    command_to_execute = command_to_execute.substr(0, command_to_execute.length()-1);
  }
    
  // ===========================================================================
  // Before executing the application lets change to the desired working 
  // directory and let's store the current working directory for changing to it
  // at the end.
  // ===========================================================================
  
  std::vector<std::string> args = CStringTools::SplitStrings(command_to_execute, ' ');

  if (args.size() > 0) {
    const int bufferSize = 1024;
    char initialDirectory[bufferSize]; // store the current directory

    if (working_directory->value() != "") {
      // get the current directory, and store it
      if(GetCurrentDir(initialDirectory, bufferSize) == NULL) {
        ERROR_MSG << "Error getting current directory."
                  END_MSG;
        do_execute = false;
      } else {
        // new directory    
        if(SetCurrentDir(working_directory->value().c_str()) != 0) {
            ERROR_MSG << "Error setting current directory: #"
                      << working_directory->value()
                      END_MSG; 
            do_execute = false;
        }
      }
    } else {
      GetCurrentDir(initialDirectory, bufferSize);
    }
    
    if (do_execute) {
      // ===========================================================================
      // If type EXEC_TYPE_APP is selected then "execv()" function is used.
      // ===========================================================================

      if (type->value() == STR(EXEC_TYPE_APP)) {
        std::vector<std::string> command_line_strings = CStringTools::SplitStrings(command_to_execute, ' ');

        const char **argv = new const char* [command_line_strings.size() + 1];

        for (unsigned int i = 0; i < command_line_strings.size(); i++) {
          argv[i] = command_line_strings[i].c_str();
        }
        argv[command_line_strings.size()] = NULL;

        try {
          result_value = execv(argv[0], (char **)argv);
        } catch(...) {
          ERROR_MSG << "Error in execv." END_MSG;           
        }

        if (argv != NULL) {
          delete []argv;
          argv = NULL;
        }
      } else {

      // ===========================================================================
      // If type EXEC_TYPE_SYS is selected then "system()" function is used.
      // ===========================================================================

        if (type->value() == STR(EXEC_TYPE_SYS)) {
          result_value = system(command_to_execute.c_str());
        }
      }

      // ===========================================================================
      // Change to the innitial working directory.
      // ===========================================================================

      if (working_directory->value() != "") {
        // Restore previous directory
        if (SetCurrentDir(initialDirectory) != 0) {
          ERROR_MSG << "Error setting current previous directory: #"
                    << initialDirectory
                    END_MSG;
          do_execute = false;
        }
      }
    }
  }

  result->set_value(result_value);
  
  
  // ===========================================================================
  // Set the result value also to the global result data manager variable
  // ===========================================================================
  CDataInt *global_result = NULL;
  global_result = (CDataInt *)manager()->data_manager()->GetDataByName(parent(),
                                                                STR(RESULT));
  global_result->set_value(result_value);  
}

void CCalcExec::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}


/*
 * 
 * execl( "/bin/ls", "ls", "-l", (char*)0 );
 * 
 * 
 http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c
 #include <string>
#include <iostream>
#include <cstdio>
#include <memory>

std::string exec(const char* cmd) {
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}
 * 
 */
