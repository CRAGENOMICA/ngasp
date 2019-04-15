#!/bin/sh
#Creation of ${MY_Calc} calc

if [ $# -eq 1 ]
then
  MY_Calc=$1
else
  MY_Calc="Dummy"
fi

if [ -f ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h ]
then
    read -p "Calc found will be overwritten. Continue? " -n 1 -r
    echo    # (optional) move to a new line
    if [[ ! $REPLY =~ ^[Yy]$ ]]
    then
        exit 1
    fi
fi

touch ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
touch ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp

echo "/* Add your LICENSE & COPYRIGHT note */" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "/**" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "*    \\brief" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "*    \\details" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "*    \\author" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "*    \\version" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "*    \\date" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "*/" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#ifndef CALCULATIONS_CALCS_CCAL${MY_Calc}_H_" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#define CALCULATIONS_CALCS_CCAL${MY_Calc}_H_" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#include \"../ICalculation.h\"" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "// Step 1 - Include the data types you use, this is one example:" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#include \"../../data_manager/CDataManager.h\"" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#include \"../../data_manager/Data/CDataCharVector.h\"" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#include \"../../data_manager/Data/CDataBoolean.h\"" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#include \"../../data_manager/Data/CDataFloat.h\"" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "class CCalc${MY_Calc} : public ICalculation {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo " public:" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  CCalc${MY_Calc}();" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  virtual ~CCalc${MY_Calc}();" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo " public:" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  void Prepare(void);" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  void Calculate(bool dry_run);" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  void Finalize(void);" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "private:" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  // Step 2 - Declare your inputs and outputs:" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  // Inputs" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  CDataCharVector *vector;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  CDataBoolean *percentage;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  // Outputs" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  CDataFloat *total;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo " public:" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  ICalculation* clone() const {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "      return new CCalc${MY_Calc}();" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  }" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "};" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#endif    // CALCULATIONS_CALCS_CCAL${MY_Calc}_H_" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h


echo "/* Add your LICENSE & COPYRIGHT note */" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "/**" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "*    \\brief" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "*    \\details" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "*    \\author" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "*    \\version" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "*    \\date" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "*/" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "#include \"CCalc${MY_Calc}.h\"" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "#include \"../../language/CStringTable.h\"" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CCalc${MY_Calc}::CCalc${MY_Calc}()" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo ": ICalculation(KeyString::CALC_${MY_Calc}," >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "               KeyString::CALC_${MY_Calc}_BRIEF_DESC," >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "               KeyString::CALC_${MY_Calc}_DESC," >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "               KeyString::NGASP_AUTHORS," >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "               KeyString::MSTATSPOP_COPYRIGHT," >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "               KeyString::GENERIC_CITATIONS," >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "               KeyString::UNDEFINED_STRING) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "// Step 3 - Define here the inputs and outputs of your calculation:" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "BEGIN_CALCULATION_INTERFACE_DEFINITION" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "SET_INPUT_INFO(vector,				// Variable" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "UNDEFINED_STRING,					// Group" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_VECTOR,				// Short Name" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_VECTOR_LONG,			// Long Name" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_VECTOR_DESC,			// Description" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_VECTOR_SAMP,			// Example" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_VECTOR_ONLY,			// Use only if" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_VECTOR_DEFV,			// Default value" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "UNDEFINED_VALUE,					// Min. value" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "UNDEFINED_VALUE,					// Max. value" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "OPTTYPE_mandatory)					// Rquired" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "SET_INPUT_INFO(percentage,			// Variable" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "UNDEFINED_STRING,					// Group" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_PERCENTAGE,			// Short Name" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_PERCENTAGE_LONG,		// Long Name" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_PERCENTAGE_DESC,		// Description" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_PERCENTAGE_SAMP,		// Example" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_PERCENTAGE_ONLY,		// Use only if" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_PERCENTAGE_DEFV,		// Default value" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "UNDEFINED_VALUE,					// Min. value" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "UNDEFINED_VALUE,					// Max. value" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "OPTTYPE_mandatory)					// Rquired" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "SET_OUTPUT_INFO(total,				// Variable" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "UNDEFINED_STRING,					// Group" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_TOTAL,				// Short Name" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_TOTAL_LONG,			// Long Name" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_TOTAL_DESC,			// Description" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_TOTAL_SAMP,			// Example" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_TOTAL_ONLY,			// Use only if" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CALC_${MY_Calc}_TOTAL_DEFV,			// Default value" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "UNDEFINED_VALUE,					// Min. value" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "UNDEFINED_VALUE,					// Max. value" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "OPTTYPE_mandatory)					// Rquired" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "END_CALCULATION_INTERFACE_DEFINITION" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CCalc${MY_Calc}::~CCalc${MY_Calc}() {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "void CCalc${MY_Calc}::Prepare(void) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "// Step 4 - Get your inputs and outputs:" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "DM_GET_INPUTS" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "DM_INPUT(vector)" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "DM_INPUT(percentage)" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "DM_GET_OUTPUTS" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "DM_OUTPUT(total)" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "DM_END" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "void CCalc${MY_Calc}::Calculate(bool dry_run) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  if (dry_run == true) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      return;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  }" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  // Step 5 - Add your calculation. This is one example of GCContent calculation:" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  total->set_value(0);" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  int64_t T = 0" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  int64_t C = 0" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  int64_t G = 0" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  int64_t A = 0" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  for (int64_t i = 0; i < vector->Size(); i++) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    switch(vector[i]) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      case ’T’:T++;break;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      case ’C’:C++;break;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      case ’G’:G++;break;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      case ’A’:A++;break;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      default:break;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    }" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  }" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  int64_t numerator = 0;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  int64_t divisor = 0;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  if (percentage->value() == true) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    numerator = (G+C);" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    divisor = (A+T+G+C);" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  } else {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    numerator = (A+T);" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    divisor = (G+C);" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  }" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  if (divisor != 0) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    float result = numerator;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    result /= divisor;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "    total->set_value(result);" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  }" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "void CCalc${MY_Calc}::Finalize(void) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "DM_DEL_ALL_LOCAL_DATA" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp


echo "File created: ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h"
echo "File created: ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp"
