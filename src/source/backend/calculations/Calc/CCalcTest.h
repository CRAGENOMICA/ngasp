/* Add your LICENSE & COPYRIGHT note */
/**
*    \brief 			CCalcTest.h
*    \details
*    \author
*    \version
*    \date
*/

#ifndef CALCULATIONS_CALCS_CCALTest_H_
#define CALCULATIONS_CALCS_CCALTest_H_

#include "../ICalculation.h"
#include "../../data_manager/CDataManager.h"

// Step 1 - Include the data types you use, this is one example:
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataBoolean.h"
#include "../../data_manager/Data/CDataFloat.h"

class CCalcTest : public ICalculation {
 public:
  CCalcTest();
  virtual ~CCalcTest();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

private:
  // Step 2 - Declare your inputs and outputs:
  // Inputs
  CDataCharVector *vector;
  CDataBoolean *percentage;
  // Outputs
  CDataFloat *total;

 public:
  ICalculation* clone() const {
      return new CCalcTest();
  }
};

#endif    // CALCULATIONS_CALCS_CCALTest_H_
