/* Add your LICENSE & COPYRIGHT note */
/**
*    \brief 			CCMDDummy.h
*    \details
*    \author
*    \version
*    \date
*/

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDDummy_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDDummy_H_

#include "../ICommand.h"

/// ============================================================================
/// DATA TYPES
/// ============================================================================
#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataBoolean.h"
#include "../../data_manager/Data/CDataFloat.h"

/// ============================================================================
/// CALCULATIONS
/// ============================================================================
#include "../../calculations/ICalculation.h"
#include "../../calculations/CAllCalculations.h"
#include "../../calculations/Calc/CCalcDummy.h"

class CCMDDummy : public ICommand {
 public:
  CCMDDummy();
  virtual ~CCMDDummy();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 private:
  CCalcDummy *calc_Dummy_;

  // Inputs
  CDataCharVector *DNAvector_;
  CDataBoolean *percentage_;
  // Outputs
  CDataFloat *total_;

/// ============================================================================
/// COMMAND BEHAVIOURS
/// ============================================================================
  bool run_only_help_;                        /// True if User only wants to watch the command help
};

#endif    // BACKEND_SRC_COMMANDS_CMD_CCMDDummy_H_

