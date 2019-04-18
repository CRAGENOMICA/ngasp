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
    SET_INPUT_INFO(vector,										// Variable
    				 UNDEFINED_STRING,								// Group
    				 CALC_Dummy_VECTOR,								// Short Name
    				 CALC_Dummy_VECTOR_LONG,					// Long Name
    				 CALC_Dummy_VECTOR_DESC,					// Description
    				 CALC_Dummy_VECTOR_SAMP,					// Example
    				 CALC_Dummy_VECTOR_ONLY,					// Use only if
    				 CALC_Dummy_VECTOR_DEFV,					// Default value
    				 UNDEFINED_VALUE,									// Min. value
    				 UNDEFINED_VALUE,									// Max. value
    				 OPTTYPE_mandatory)								// Rquired
    SET_INPUT_INFO(percentage,								// Variable
    				 UNDEFINED_STRING,								// Group
    				 CALC_Dummy_PERCENTAGE,						// Short Name
    				 CALC_Dummy_PERCENTAGE_LONG,			// Long Name
    				 CALC_Dummy_PERCENTAGE_DESC,			// Description
    				 CALC_Dummy_PERCENTAGE_SAMP,			// Example
    				 CALC_Dummy_PERCENTAGE_ONLY,			// Use only if
    				 CALC_Dummy_PERCENTAGE_DEFV,			// Default value
    				 UNDEFINED_VALUE,									// Min. value
    				 UNDEFINED_VALUE,									// Max. value
    				 OPTTYPE_mandatory)								// Rquired
    SET_OUTPUT_INFO(total,										// Variable
    				 UNDEFINED_STRING,								// Group
    				 CALC_Dummy_TOTAL,								// Short Name
    				 CALC_Dummy_TOTAL_LONG,						// Long Name
    				 CALC_Dummy_TOTAL_DESC,						// Description
    				 CALC_Dummy_TOTAL_SAMP,						// Example
    				 CALC_Dummy_TOTAL_ONLY,						// Use only if
    				 CALC_Dummy_TOTAL_DEFV,						// Default value
    				 UNDEFINED_VALUE,									// Min. value
    				 UNDEFINED_VALUE,									// Max. value
    				 OPTTYPE_mandatory)								// Rquired
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcDummy::~CCalcDummy() {
}

void CCalcDummy::Prepare(void) {
  // Step 4 - Get your inputs and outputs:
  DM_GET_INPUTS
    DM_INPUT(vector)
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
  int64_t T = 0
  int64_t C = 0
  int64_t G = 0
  int64_t A = 0

  for (int64_t i = 0; i < vector->Size(); i++) {
    switch(vector[i]) {
      case ’T’:T++;break;
      case ’C’:C++;break;
      case ’G’:G++;break;
      case ’A’:A++;break;
      default:break;
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

}

void CCalcDummy::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
