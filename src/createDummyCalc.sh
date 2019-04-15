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
  	sed -i -e 's/  strings_\[ENGLISH_COL\]\[_CALC_LAST\]/  strings_\[ENGLISH_COL\]\[CALC_'"${MY_Calc}"'\] = \"'"${MY_Calc}"'\"\;\n  strings_\[ENGLISH_COL\]\[CALC_'"${MY_Calc}"'_BRIEF_DESC\] = "";\n  strings_\[ENGLISH_COL\]\[CALC_'"${MY_Calc}"'_DESC\] = \"'"${MY_Calc}"' description\";\n\n  strings_\[ENGLISH_COL\]\[_CALC_LAST\]/g' ./source/backend/language/CStringTable.cpp

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
echo "/* Add your LICENSE & COPYRIGHT note */" > ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "/**" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "*    \\brief 			CCalc${MY_Calc}.h" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "*    \\details" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "*    \\author" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "*    \\version" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "*    \\date" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "*/" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#ifndef CALCULATIONS_CALCS_CCAL${MY_Calc}_H_" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#define CALCULATIONS_CALCS_CCAL${MY_Calc}_H_" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#include \"../ICalculation.h\"" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#include \"../../data_manager/CDataManager.h\"" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "// Step 1 - Include the data types you use, this is one example:" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#include \"../../data_manager/Data/CDataCharVector.h\"" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#include \"../../data_manager/Data/CDataBoolean.h\"" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#include \"../../data_manager/Data/CDataFloat.h\"" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "class CCalc${MY_Calc} : public ICalculation {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo " public:" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  CCalc${MY_Calc}();" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  virtual ~CCalc${MY_Calc}();" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo " public:" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  void Prepare(void);" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  void Calculate(bool dry_run);" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  void Finalize(void);" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "private:" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  // Step 2 - Declare your inputs and outputs:" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  // Inputs" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  CDataCharVector *vector;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  CDataBoolean *percentage;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  // Outputs" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  CDataFloat *total;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo " public:" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  ICalculation* clone() const {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "      return new CCalc${MY_Calc}();" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  }" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "};" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#endif    // CALCULATIONS_CALCS_CCAL${MY_Calc}_H_" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.h




#creation of CCalc${MY_Calc}.cpp
echo "/* Add your LICENSE & COPYRIGHT note */" > ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "/**" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "*    \\brief 			CCalc${MY_Calc}.cpp" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "*    \\details" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "*    \\author" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "*    \\version" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "*    \\date" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "*/" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "#include \"CCalc${MY_Calc}.h\"" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "#include \"../../language/CStringTable.h\"" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CCalc${MY_Calc}::CCalc${MY_Calc}()" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo ": ICalculation(KeyString::CALC_${MY_Calc}," >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "               KeyString::CALC_${MY_Calc}_BRIEF_DESC," >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "               KeyString::CALC_${MY_Calc}_DESC," >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "               KeyString::NGASP_AUTHORS," >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "               KeyString::MSTATSPOP_COPYRIGHT," >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "               KeyString::GENERIC_CITATIONS," >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "               KeyString::UNDEFINED_STRING) {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  // Step 3 - Define here the inputs and outputs of your calculation:" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  BEGIN_CALCULATION_INTERFACE_DEFINITION" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    SET_INPUT_INFO(vector,										// Variable" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 UNDEFINED_STRING,								// Group" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_VECTOR,								// Short Name" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_VECTOR_LONG,					// Long Name" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_VECTOR_DESC,					// Description" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_VECTOR_SAMP,					// Example" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_VECTOR_ONLY,					// Use only if" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_VECTOR_DEFV,					// Default value" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 UNDEFINED_VALUE,									// Min. value" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 UNDEFINED_VALUE,									// Max. value" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 OPTTYPE_mandatory)								// Rquired" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    SET_INPUT_INFO(percentage,								// Variable" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 UNDEFINED_STRING,								// Group" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_PERCENTAGE,						// Short Name" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_PERCENTAGE_LONG,			// Long Name" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_PERCENTAGE_DESC,			// Description" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_PERCENTAGE_SAMP,			// Example" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_PERCENTAGE_ONLY,			// Use only if" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_PERCENTAGE_DEFV,			// Default value" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 UNDEFINED_VALUE,									// Min. value" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 UNDEFINED_VALUE,									// Max. value" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 OPTTYPE_mandatory)								// Rquired" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    SET_OUTPUT_INFO(total,										// Variable" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 UNDEFINED_STRING,								// Group" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_TOTAL,								// Short Name" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_TOTAL_LONG,						// Long Name" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_TOTAL_DESC,						// Description" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_TOTAL_SAMP,						// Example" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_TOTAL_ONLY,						// Use only if" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 CALC_${MY_Calc}_TOTAL_DEFV,						// Default value" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 UNDEFINED_VALUE,									// Min. value" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 UNDEFINED_VALUE,									// Max. value" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    				 OPTTYPE_mandatory)								// Rquired" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  END_CALCULATION_INTERFACE_DEFINITION" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CCalc${MY_Calc}::~CCalc${MY_Calc}() {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "void CCalc${MY_Calc}::Prepare(void) {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  // Step 4 - Get your inputs and outputs:" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  DM_GET_INPUTS" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    DM_INPUT(vector)" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    DM_INPUT(percentage)" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  DM_GET_OUTPUTS" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    DM_OUTPUT(total)" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  DM_END" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "void CCalc${MY_Calc}::Calculate(bool dry_run) {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  if (dry_run == true) {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      return;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  }" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  // Step 5 - Add your calculation. This is one example of GCContent calculation:" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  total->set_value(0);" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  int64_t T = 0" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  int64_t C = 0" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  int64_t G = 0" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  int64_t A = 0" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  for (int64_t i = 0; i < vector->Size(); i++) {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    switch(vector[i]) {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      case ’T’:T++;break;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      case ’C’:C++;break;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      case ’G’:G++;break;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      case ’A’:A++;break;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      default:break;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    }" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  }" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  int64_t numerator = 0;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  int64_t divisor = 0;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  if (percentage->value() == true) {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    numerator = (G+C);" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    divisor = (A+T+G+C);" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  } else {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    numerator = (A+T);" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    divisor = (G+C);" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  }" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  if (divisor != 0) {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    float result = numerator;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    result /= divisor;" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    total->set_value(result);" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  }" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "void CCalc${MY_Calc}::Finalize(void) {" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  DM_DEL_ALL_LOCAL_DATA" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp


echo "File created: ./source/backend/calculations/Calc/CCalc${MY_Calc}.h"
echo "File created: ./source/backend/calculations/Calc/CCalc${MY_Calc}.cpp"
