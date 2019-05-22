/* Add your LICENSE & COPYRIGHT note */
/**
*    \brief 			CCMDDummyNODM.h
*    \details
*    \author
*    \version
*    \date
*/

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDDummyNODM_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDDummyNODM_H_

#include "../ICommand.h"

/// ============================================================================
/// DATA TYPES
/// ============================================================================
//#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataBoolean.h"
#include "../../data_manager/Data/CDataFloat.h"

/// ============================================================================
/// CALCULATIONS
/// ============================================================================
#include "../../calculations/ICalculation.h"
#include "../../calculations/CAllCalculations.h"
#include "../../calculations/Calc/CCalcDummy.h"

class CCMDDummyNODM : public ICommand {
 public:
  CCMDDummyNODM();
  virtual ~CCMDDummyNODM();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 private:
  CCalcDummy *calc_Dummy_;

  // Inputs
  CDataCharVector *DNAvector;
  CDataBoolean *percentage;
  // Outputs
  //CDataFloat *total;

/// ============================================================================
/// COMMAND BEHAVIOURS
/// ============================================================================
  bool run_only_help_;                        /// True if User only wants to watch the command help
};

#endif    // BACKEND_SRC_COMMANDS_CMD_CCMDDummyNODM_H_

