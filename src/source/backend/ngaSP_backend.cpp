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
 *  \brief     ngaSP_backend.cpp
 *  \details   Main function and loop
 *  \author    Joan Jené, gvera
 *  \version   1.0
 *  \date      March 30, 2015
 *  \pre
 *  \bug
 *  \warning
*/

//                                          _saa,,.     aaaaaa,.
//                                         jWWWWQQf     QQWQWQQQ/
//                                        _QWWT?9Qf     QQQ??9QQQ,
//  ]QQf<mQm,     jmQw,QQQ    _ymQQmw.    ]QQf    '     QQQ   4QQ[
//  ]QQmQQQQQ.   jQQQQmQQQ    ]QQQQQWm    ]QQg,         QQQ   jQQ[
//  ]QQW'-$QQ[  _QQW' 4QQQ    "~  -4QQ>   -QQQQmw,.     QQQ  _mQQ(
//  ]QQf  ]QQf  ]QQf  -QQQ     _aaajQQ[    )$QQQQQg     QQQQQQQQP
//  ]QQf  ]QQf  ]QQf   QQQ    yQQWQQQQf      ~?9QQQc    QQQQQQB?
//  ]QQf  ]QQf  ]QQL  .QQQ   ]QQP  jQQf         ]QQf    QQQ
//  ]QQf  ]QQf  -QQQ, jQQQ   ]QQL _mQQf   ]w,. _yQQ[    QQQ
//  ]QQf  ]QQf   4WQQQ@QQQ   +WQQQQWQQf   ]QQQQQQQ@     QQQ
//  ]QQf  ]QQf    ?WWT'QQQ    )$W@!]QQf   -?VWQQB?`     QQQ
//                   <QQE
//               QwawQQQ(
//              (WWWWWW!


#include <cstdlib>
#include <cstring>

#include <string>         // std::string
#include <iostream>       // std::cout


#include "CManager.h"
#include "messages/CLogger.h"
#include "language/CStringTable.h"
#include "instructions/CController.h"
#include "calculations/CAllCalculations.h"
#include "data_manager/CDataManager.h"
#include "util/CFile.h"
#include "commands/CAllCommands.h"

#include "calculations/Calc/CCalcBoxPlotValues.h"

// #include "data_manager/Data/CDataSam.h"
// #include "data_manager/IDataVector.h"

// #include "data_manager/Data/CDataCharVector.h"

#define MODE_ONLY_MSTATSPOP


// *****************************************************************************
// PROVA
// *****************************************************************************
/*
#include "data_manager/Data/CDataIntVector.h"
#include <algorithm>  // std::for_each
class CCalcSuma
{
 public:
  
  CCalcSuma() {
  }
  
  ~CCalcSuma() {
  }
  
  // =====================================
  // CALCULATE
  // =====================================
  void operator()(int i) { 
    std::cout << i << " ";
  }
  
  void Calculate(int i) {
    std::cout << i << " ";
  }
};
*/
// *****************************************************************************
#include <export.h>
#include <bam.h>

#include <string.h>

void f(char *p) {
  
}

int main(int argc, char *argv[]) {
  /// Initialize folder structure.
  /// ----------------------------

/*
  CDataCharVector vec;
  vec.ReserveMemory(4);
  vec[0] = 'c';
  vec[1] = 'a';
  vec[2] = 's';
  vec[3] = 'a';
   
  CDataCharVector vec2;
  vec2.ReserveMemory(4);
  vec2[0] = '1';
  vec2[1] = '2';
  vec2[2] = '3';
  vec2[3] = '4';

  vec.Append(vec2); 
  printf("%s", vec.GetData());
  exit(0);
*/
    
  CFile::CreateDirectories("./tmp");

  
  /// Initialize the Manager.
  /// -----------------------

  CManager *manager = new CManager();
  manager->Init();
/*
  CCalcBoxPlotValues calc_boxplot_values;
  CDataDoubleVector array;
  CDataDouble q1;
  CDataDouble median;
  CDataDouble q3;
  CDataDouble min;
  CDataDouble max;
  CDataDoubleVector outliers;

  array.set_data_string("14.2 17.1 10.2 14.2 14.1 16.2 10.3 17.2 10.2 0");
 
  calc_boxplot_values.SetInput(&array);
  calc_boxplot_values.SetOutput(&q1);
  calc_boxplot_values.SetOutput(&median);
  calc_boxplot_values.SetOutput(&q3);
  calc_boxplot_values.SetOutput(&min);
  calc_boxplot_values.SetOutput(&max);
  calc_boxplot_values.SetOutput(&outliers);

  calc_boxplot_values.Prepare();
  calc_boxplot_values.Calculate(false);
  calc_boxplot_values.Finalize();
*/
   
  /// Get the desired execution mode.
  /// -------------------------------
  
  if (argc == 1) {
    /// Execution Mode not defined. Showing ngaSP help.
  
#ifndef MODE_ONLY_MSTATSPOP
    char *argv2[] = {"ngasp", "help", NULL};
    int argc2 = sizeof(argv2) / sizeof(char*) - 1;

    manager->set_execution_mode(tExecutionMode::COMMAND_LINE);
    manager->RunCommandLineExecutionMode(argc2, argv2);    

    // manager->set_execution_mode(EXEC_MODE_NOT_DEFINED);
    // manager->all_commands()->set_selected_command(STR(CMD_APP_HELP));
    // (*manager->all_commands()->selected_command())->Run();
#endif    
#ifdef MODE_ONLY_MSTATSPOP
    // char *argv2[] = {"ngasp", "mstatspop", NULL};
    char *argv2[] = {"ngasp", "help", "-c", "mstatspop", NULL};
    int argc2 = sizeof(argv2) / sizeof(char*) - 1;

    manager->set_execution_mode(tExecutionMode::COMMAND_LINE);
    manager->RunCommandLineExecutionMode(argc2, argv2);    
#endif
  } else {
    if (argv[1] == STR(INTERACTIVE_MODE_CHAR)) {
      /// Interactive Shell Execution Mode
  
      manager->set_execution_mode(tExecutionMode::INTERACTIVE_SHELL);
      manager->RunInteractiveShellExecutionMode();
    } else {
      if (argv[1] == STR(CMD_SOCKET)) {
      /// Local Manager Execution Mode
  
        manager->set_execution_mode(tExecutionMode::LOCAL_MANAGER);
        manager->RunLocalManagerExecutionMode(argc, argv);
      } else {
        if (argv[1] == STR(CMD_PIPE)) {
          /// Worker Execution Mode 
          
          manager->set_execution_mode(tExecutionMode::WORKER);
          manager->RunWorkerExecutionMode(argc, argv);
        } else {
          /// Command Line Execution Mode
  
          manager->set_execution_mode(tExecutionMode::COMMAND_LINE);
          manager->RunCommandLineExecutionMode(argc, argv);
        }
      }
    }
  }

  /// Destroy the manager and exit.
  /// -----------------------------

  manager->CleanAndClose();
  delete manager;
  manager = NULL;

  return(EXIT_SUCCESS);
}

