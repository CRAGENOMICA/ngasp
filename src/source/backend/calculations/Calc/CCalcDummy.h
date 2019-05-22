/* Add your LICENSE & COPYRIGHT note */
/**
*    \brief 			CCalcDummy.h
*    \details
*    \author
*    \version
*    \date
*/

#ifndef CALCULATIONS_CALCS_CCALDummy_H_
#define CALCULATIONS_CALCS_CCALDummy_H_

#include "../ICalculation.h"
#include "../../data_manager/CDataManager.h"

// Step 1 - Include the definition of the data types you will use, this is one example:
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataBoolean.h"
#include "../../data_manager/Data/CDataFloat.h"

class CCalcDummy : public ICalculation {
 public:
  CCalcDummy();
  virtual ~CCalcDummy();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

private:
  // Step 2 - Declare your inputs and outputs:
  // Inputs
  CDataCharVector *DNAvector;
  CDataBoolean *percentage;
  // Outputs
  CDataFloat *total;

 public:
  ICalculation* clone() const {
      return new CCalcDummy();
  }
};

#endif    // CALCULATIONS_CALCS_CCALDummy_H_

