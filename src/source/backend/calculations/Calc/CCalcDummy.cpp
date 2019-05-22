/* Add your LICENSE & COPYRIGHT note */
/**
*    \brief 			CCalcDummy.cpp
*    \details
*    \author
*    \version
*    \date
*/

#include "CCalcDummy.h"

#include "../../language/CStringTable.h"

CCalcDummy::CCalcDummy()
: ICalculation(KeyString::CALC_Dummy,
               KeyString::CALC_Dummy_BRIEF_DESC,
               KeyString::CALC_Dummy_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {

  // Step 3 - Define here the inputs and outputs of your calculation:
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(DNAvector,							// Variable name
    				 UNDEFINED_STRING,					// Group
    				 UNDEFINED_STRING,					// Short Name
    				 UNDEFINED_STRING,					// Long Name
    				 UNDEFINED_STRING,					// Description
    				 UNDEFINED_STRING,					// Example
    				 UNDEFINED_STRING,					// Use only if
    				 UNDEFINED_STRING,					// Default value
    				 UNDEFINED_VALUE,					// Min. value
    				 UNDEFINED_VALUE,					// Max. value
    				 OPTTYPE_mandatory)					// Required
    SET_INPUT_INFO(percentage,							// Variable name
    				 UNDEFINED_STRING,					// Group
    				 UNDEFINED_STRING,					// Short Name
    				 UNDEFINED_STRING,					// Long Name
    				 UNDEFINED_STRING,					// Description
    				 UNDEFINED_STRING,					// Example
    				 UNDEFINED_STRING,					// Use only if
    				 UNDEFINED_STRING,					// Default value
    				 UNDEFINED_VALUE,					// Min. value
    				 UNDEFINED_VALUE,					// Max. value
    				 OPTTYPE_mandatory)					// Required
    SET_OUTPUT_INFO(total,								// Variable name
    				 UNDEFINED_STRING,					// Group
    				 UNDEFINED_STRING,					// Short Name
    				 UNDEFINED_STRING,					// Long Name
    				 UNDEFINED_STRING,					// Description
    				 UNDEFINED_STRING,					// Example
    				 UNDEFINED_STRING,					// Use only if
    				 UNDEFINED_STRING,					// Default value
    				 UNDEFINED_VALUE,					// Min. value
    				 UNDEFINED_VALUE,					// Max. value
    				 OPTTYPE_mandatory)					// Required
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcDummy::~CCalcDummy() {
}

void CCalcDummy::Prepare(void) {
  // Step 4 - Get your inputs and outputs:
  DM_GET_INPUTS
    DM_INPUT(DNAvector)
    DM_INPUT(percentage)
  DM_GET_OUTPUTS
    DM_OUTPUT(total)
  DM_END
}

void CCalcDummy::Calculate(bool dry_run) {
  if (dry_run == true) {
      return;
  }

  // Step 5 - Add your calculation. This is one example of GCContent calculation:
  total->set_value(0);
  int64_t T = 0;
  int64_t C = 0;
  int64_t G = 0;
  int64_t A = 0;

  for (int64_t i = 0; i < DNAvector->Size(); i++) {
    if ((*DNAvector)[i] == 'T') {
    	T++;
    } else if ((*DNAvector)[i] == 'C') {
    	C++;
    } else if ((*DNAvector)[i] == 'G') {
    	G++;
    } else if ((*DNAvector)[i] == 'A') {
	A++;
    }
  }

  int64_t numerator = 0;
  int64_t divisor = 0;
  if (percentage->value() == true) {
    numerator = (G+C);
    divisor = (A+T+G+C);
  } else {
    numerator = (A+T);
    divisor = (G+C);
  }
  if (divisor != 0) {
    float result = numerator;
    result /= divisor;
    total->set_value(result);
  }
  NORMAL_MSG << "total: " << total->value()
  END_MSG;
}

void CCalcDummy::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
