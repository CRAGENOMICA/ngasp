#!/bin/sh
#Creation of ${MY_Calc} calc

MY_Calc="Dummy"

#TODO:
#poner control de si ya existen los ficheros 
#añadir posibilidad de modificar MY_Calc por variable

touch ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
touch ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp

echo "/* LICENSE & COPYRIGHT note */" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
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
echo " public:" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  ICalculation* clone() const {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "      return new CCalc${MY_Calc}();" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "  }" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "};" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h
echo "#endif    // CALCULATIONS_CALCS_CCAL${MY_Calc}_H_" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h


echo "/* LICENSE & COPYRIGHT note */" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
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
echo "}" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "CCalc${MY_Calc}::~CCalc${MY_Calc}() {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "void CCalc${MY_Calc}::Prepare(void) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "void CCalc${MY_Calc}::Calculate(bool dry_run) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  if (dry_run == true) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "      return;" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "  }" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "void CCalc${MY_Calc}::Finalize(void) {" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp
echo "}" >> ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp


echo "File created: ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.h"
echo "File created: ./src/source/backend/calculations/Calc/CCalc${MY_Calc}.cpp"
