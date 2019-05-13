#!/usr/bin/env bash
#Creation of ${MY_Calc} calc

if [ $# -eq 1 ]
then
  MY_Calc=$1
else
  MY_Calc="Dummy"
fi

if [ -f ./source/backend/calculations/Calc/CCalc${MY_Calc}.h ]
then
    read -n 1 -r -p "Calc ${MY_Calc} found will be overwritten. Continue? (y/n): "
    echo    # (optional) move to a new line
    if [[ ! $REPLY =~ ^[Yy]$ ]]
    then
        exit 1
    fi
else
	# creation of control requeriments

	# addition of calc to ./source/backend/language/CStringTable.h
	sed -i -e 's/  _CALC_LAST,/  CALC_'"${MY_Calc}"',\n  CALC_'"${MY_Calc}"'_BRIEF_DESC,\n  CALC_'"${MY_Calc}"'_DESC,\n\n\n  _CALC_LAST,/g' ./source/backend/language/CStringTable.h

	# addition of calc to ./source/backend/language/CStringTable.cpp    
  	sed -i -e 's/  strings_\[ENGLISH_COL\]\[_CALC_LAST\]/  strings_\[ENGLISH_COL\]\[CALC_'"${MY_Calc}"'\] = \"calc_'"${MY_Calc}"'\"\;\n  strings_\[ENGLISH_COL\]\[CALC_'"${MY_Calc}"'_BRIEF_DESC\] = "";\n  strings_\[ENGLISH_COL\]\[CALC_'"${MY_Calc}"'_DESC\] = \"'"${MY_Calc}"' description\";\n\n  strings_\[ENGLISH_COL\]\[_CALC_LAST\]/g' ./source/backend/language/CStringTable.cpp

	# addition of calc to ./source/backend/calculations/CCalcFactory.cpp
	sed -i -e 's|//_CALC_LAST|\#include "Calc/CCalc'"${MY_Calc}"'.h"\n//_CALC_LAST|g' ./source/backend/calculations/CCalcFactory.cpp
	sed -i -e 's|  //data_map_\[KeyString::_CALC_LAST\]|  data_map_\[KeyString::CALC_'"${MY_Calc}"'\] = new CCalc'"${MY_Calc}"'();\n  //data_map_\[KeyString::_CALC_LAST\]|g' ./source/backend/calculations/CCalcFactory.cpp

	echo "File ./source/backend/language/CStringTable.h modified to add ${MY_Calc}"
	echo "File ./source/backend/language/CStringTable.cpp modified to add ${MY_Calc}"
	echo "File ./source/backend/calculations/CCalcFactory.cpp modified to add ${MY_Calc}"
fi

touch ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
touch ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp

#creation of CCalc${MY_Calc}.h
cat << EOF > ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
/* Add your LICENSE & COPYRIGHT note */
/**
*    \\brief 			CCalc${MY_Calc}.h
*    \\details
*    \\author
*    \\version
*    \\date
*/

#ifndef CALCULATIONS_CALCS_CCAL${MY_Calc}_H_
#define CALCULATIONS_CALCS_CCAL${MY_Calc}_H_

#include "../ICalculation.h"
#include "../../data_manager/CDataManager.h"

// Step 1 - Include the definition of the data types you will use, this is one example:
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataBoolean.h"
#include "../../data_manager/Data/CDataFloat.h"

class CCalc${MY_Calc} : public ICalculation {
 public:
  CCalc${MY_Calc}();
  virtual ~CCalc${MY_Calc}();

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
      return new CCalc${MY_Calc}();
  }
};

#endif    // CALCULATIONS_CALCS_CCAL${MY_Calc}_H_

EOF

#creation of CCalc${MY_Calc}.cpp
cat << EOF > ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
/* Add your LICENSE & COPYRIGHT note */
/**
*    \\brief 			CCalc${MY_Calc}.cpp
*    \\details
*    \\author
*    \\version
*    \\date
*/

#include "CCalc${MY_Calc}.h"

#include "../../language/CStringTable.h"

CCalc${MY_Calc}::CCalc${MY_Calc}()
: ICalculation(KeyString::CALC_${MY_Calc},
               KeyString::CALC_${MY_Calc}_BRIEF_DESC,
               KeyString::CALC_${MY_Calc}_DESC,
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

CCalc${MY_Calc}::~CCalc${MY_Calc}() {
}

void CCalc${MY_Calc}::Prepare(void) {
  // Step 4 - Get your inputs and outputs:
  DM_GET_INPUTS
    DM_INPUT(DNAvector)
    DM_INPUT(percentage)
  DM_GET_OUTPUTS
    DM_OUTPUT(total)
  DM_END
}

void CCalc${MY_Calc}::Calculate(bool dry_run) {
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

}

void CCalc${MY_Calc}::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
EOF

echo "File created: ./source/backend/calculations/Calc/CCalc${MY_Calc}.h"
echo "File created: ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp"
