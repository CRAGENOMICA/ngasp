#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CManager.o \
	${OBJECTDIR}/IBase.o \
	${OBJECTDIR}/IFunction.o \
	${OBJECTDIR}/IObject.o \
	${OBJECTDIR}/calculations/CAllCalculations.o \
	${OBJECTDIR}/calculations/CCalcFactory.o \
	${OBJECTDIR}/calculations/CConnectorDef.o \
	${OBJECTDIR}/calculations/Calc/CCalcArrayOpeX.o \
	${OBJECTDIR}/calculations/Calc/CCalcArraySumAll.o \
	${OBJECTDIR}/calculations/Calc/CCalcBCF2VCF.o \
	${OBJECTDIR}/calculations/Calc/CCalcBam2Bai.o \
	${OBJECTDIR}/calculations/Calc/CCalcBam2Mpileup.o \
	${OBJECTDIR}/calculations/Calc/CCalcBamChromosomes.o \
	${OBJECTDIR}/calculations/Calc/CCalcBoxPlotValues.o \
	${OBJECTDIR}/calculations/Calc/CCalcCollectDataColumns.o \
	${OBJECTDIR}/calculations/Calc/CCalcConcatFiles.o \
	${OBJECTDIR}/calculations/Calc/CCalcConcatStrings.o \
	${OBJECTDIR}/calculations/Calc/CCalcCreateTFastaAnnotation.o \
	${OBJECTDIR}/calculations/Calc/CCalcCutBED.o \
	${OBJECTDIR}/calculations/Calc/CCalcCutGTF.o \
	${OBJECTDIR}/calculations/Calc/CCalcDnaMatrix2MatrixPol.o \
	${OBJECTDIR}/calculations/Calc/CCalcDuplicatePopulations.o \
	${OBJECTDIR}/calculations/Calc/CCalcEffecNucAndTCGAFreqs.o \
	${OBJECTDIR}/calculations/Calc/CCalcExample.o \
	${OBJECTDIR}/calculations/Calc/CCalcExec.o \
	${OBJECTDIR}/calculations/Calc/CCalcFasta2DnaMatrix.o \
	${OBJECTDIR}/calculations/Calc/CCalcFasta2TFasta.o \
	${OBJECTDIR}/calculations/Calc/CCalcFileStats.o \
	${OBJECTDIR}/calculations/Calc/CCalcFreqStats.o \
	${OBJECTDIR}/calculations/Calc/CCalcFs.o \
	${OBJECTDIR}/calculations/Calc/CCalcGCContent.o \
	${OBJECTDIR}/calculations/Calc/CCalcGFF.o \
	${OBJECTDIR}/calculations/Calc/CCalcGetChromosomes.o \
	${OBJECTDIR}/calculations/Calc/CCalcHwhafsth.o \
	${OBJECTDIR}/calculations/Calc/CCalcJointFreqDist.o \
	${OBJECTDIR}/calculations/Calc/CCalcLengthamngAndCalcs.o \
	${OBJECTDIR}/calculations/Calc/CCalcListFiles.o \
	${OBJECTDIR}/calculations/Calc/CCalcMaskFileMs.o \
	${OBJECTDIR}/calculations/Calc/CCalcMatrix2Vector.o \
	${OBJECTDIR}/calculations/Calc/CCalcMismatch.o \
	${OBJECTDIR}/calculations/Calc/CCalcMstatspop.o \
	${OBJECTDIR}/calculations/Calc/CCalcMstatspopOpenFastaFile.o \
	${OBJECTDIR}/calculations/Calc/CCalcMstatspopOpenMsFile.o \
	${OBJECTDIR}/calculations/Calc/CCalcMstatspopOutput.o \
	${OBJECTDIR}/calculations/Calc/CCalcOpenCoordinatesFile.o \
	${OBJECTDIR}/calculations/Calc/CCalcOpenEffectSizesFile.o \
	${OBJECTDIR}/calculations/Calc/CCalcOpenFastaFile.o \
	${OBJECTDIR}/calculations/Calc/CCalcOpenFreqSpecFile.o \
	${OBJECTDIR}/calculations/Calc/CCalcOpenTFastaFile.o \
	${OBJECTDIR}/calculations/Calc/CCalcOpenWeightPositionsFile.o \
	${OBJECTDIR}/calculations/Calc/CCalcPermute.o \
	${OBJECTDIR}/calculations/Calc/CCalcPiwpiafst.o \
	${OBJECTDIR}/calculations/Calc/CCalcR2.o \
	${OBJECTDIR}/calculations/Calc/CCalcR2p.o \
	${OBJECTDIR}/calculations/Calc/CCalcRandomize.o \
	${OBJECTDIR}/calculations/Calc/CCalcSam2Mpileup.o \
	${OBJECTDIR}/calculations/Calc/CCalcSnipCaller.o \
	${OBJECTDIR}/calculations/Calc/CCalcSplitBAM.o \
	${OBJECTDIR}/calculations/Calc/CCalcSxsfss.o \
	${OBJECTDIR}/calculations/Calc/CCalcTOptimalTests.o \
	${OBJECTDIR}/calculations/Calc/CCalcVCFToGFasta.o \
	${OBJECTDIR}/calculations/Calc/CCalcX.o \
	${OBJECTDIR}/calculations/Calc/CCalcY.o \
	${OBJECTDIR}/calculations/Calc/CCalcZ.o \
	${OBJECTDIR}/calculations/Calc/CCalcnpstat.o \
	${OBJECTDIR}/calculations/ICalculation.o \
	${OBJECTDIR}/calculations/util/CComparison.o \
	${OBJECTDIR}/calculations/util/CDnaTools.o \
	${OBJECTDIR}/calculations/util/CMatrixPol.o \
	${OBJECTDIR}/calculations/util/CMissingFreqs.o \
	${OBJECTDIR}/calculations/util/CValuesGFF.o \
	${OBJECTDIR}/commands/CAllCommands.o \
	${OBJECTDIR}/commands/CCommandFactory.o \
	${OBJECTDIR}/commands/CMD/CCMDAdd.o \
	${OBJECTDIR}/commands/CMD/CCMDAppHelp.o \
	${OBJECTDIR}/commands/CMD/CCMDAppend.o \
	${OBJECTDIR}/commands/CMD/CCMDCalc.o \
	${OBJECTDIR}/commands/CMD/CCMDConstant.o \
	${OBJECTDIR}/commands/CMD/CCMDDelete.o \
	${OBJECTDIR}/commands/CMD/CCMDDim.o \
	${OBJECTDIR}/commands/CMD/CCMDDryRun.o \
	${OBJECTDIR}/commands/CMD/CCMDElse.o \
	${OBJECTDIR}/commands/CMD/CCMDEndForeach.o \
	${OBJECTDIR}/commands/CMD/CCMDEndIf.o \
	${OBJECTDIR}/commands/CMD/CCMDEndWith.o \
	${OBJECTDIR}/commands/CMD/CCMDExec.o \
	${OBJECTDIR}/commands/CMD/CCMDForeach.o \
	${OBJECTDIR}/commands/CMD/CCMDHistory.o \
	${OBJECTDIR}/commands/CMD/CCMDIf.o \
	${OBJECTDIR}/commands/CMD/CCMDLoadInstructionsFile.o \
	${OBJECTDIR}/commands/CMD/CCMDLog.o \
	${OBJECTDIR}/commands/CMD/CCMDMemInfo.o \
	${OBJECTDIR}/commands/CMD/CCMDOpenDataFile.o \
	${OBJECTDIR}/commands/CMD/CCMDOutput.o \
	${OBJECTDIR}/commands/CMD/CCMDPipe.o \
	${OBJECTDIR}/commands/CMD/CCMDPrint.o \
	${OBJECTDIR}/commands/CMD/CCMDReserve.o \
	${OBJECTDIR}/commands/CMD/CCMDReset.o \
	${OBJECTDIR}/commands/CMD/CCMDRun.o \
	${OBJECTDIR}/commands/CMD/CCMDSaveState.o \
	${OBJECTDIR}/commands/CMD/CCMDSetValue.o \
	${OBJECTDIR}/commands/CMD/CCMDSocket.o \
	${OBJECTDIR}/commands/CMD/CCMDStop.o \
	${OBJECTDIR}/commands/CMD/CCMDSyntax.o \
	${OBJECTDIR}/commands/CMD/CCMDVerbose.o \
	${OBJECTDIR}/commands/CMD/CCMDVersion.o \
	${OBJECTDIR}/commands/CMD/CCMDWith.o \
	${OBJECTDIR}/commands/CMD/CCMDmstatspop.o \
	${OBJECTDIR}/commands/COS/COption.o \
	${OBJECTDIR}/commands/COS/COptionsContainer.o \
	${OBJECTDIR}/commands/ICommand.o \
	${OBJECTDIR}/data_manager/CDataFactory.o \
	${OBJECTDIR}/data_manager/CDataManager.o \
	${OBJECTDIR}/data_manager/Data/CDataBCF.o \
	${OBJECTDIR}/data_manager/Data/CDataBam.o \
	${OBJECTDIR}/data_manager/Data/CDataBamIndex.o \
	${OBJECTDIR}/data_manager/Data/CDataBoolean.o \
	${OBJECTDIR}/data_manager/Data/CDataBooleanCube.o \
	${OBJECTDIR}/data_manager/Data/CDataBooleanMatrix.o \
	${OBJECTDIR}/data_manager/Data/CDataBooleanVector.o \
	${OBJECTDIR}/data_manager/Data/CDataChar.o \
	${OBJECTDIR}/data_manager/Data/CDataCharCube.o \
	${OBJECTDIR}/data_manager/Data/CDataCharMatrix.o \
	${OBJECTDIR}/data_manager/Data/CDataCharVector.o \
	${OBJECTDIR}/data_manager/Data/CDataDouble.o \
	${OBJECTDIR}/data_manager/Data/CDataDoubleCube.o \
	${OBJECTDIR}/data_manager/Data/CDataDoubleMatrix.o \
	${OBJECTDIR}/data_manager/Data/CDataDoubleVector.o \
	${OBJECTDIR}/data_manager/Data/CDataFasta.o \
	${OBJECTDIR}/data_manager/Data/CDataFloat.o \
	${OBJECTDIR}/data_manager/Data/CDataFloatCube.o \
	${OBJECTDIR}/data_manager/Data/CDataFloatMatrix.o \
	${OBJECTDIR}/data_manager/Data/CDataFloatVector.o \
	${OBJECTDIR}/data_manager/Data/CDataGFF.o \
	${OBJECTDIR}/data_manager/Data/CDataGFasta.o \
	${OBJECTDIR}/data_manager/Data/CDataGTF.o \
	${OBJECTDIR}/data_manager/Data/CDataInt.o \
	${OBJECTDIR}/data_manager/Data/CDataInt64.o \
	${OBJECTDIR}/data_manager/Data/CDataInt64Cube.o \
	${OBJECTDIR}/data_manager/Data/CDataInt64Matrix.o \
	${OBJECTDIR}/data_manager/Data/CDataInt64Vector.o \
	${OBJECTDIR}/data_manager/Data/CDataIntCube.o \
	${OBJECTDIR}/data_manager/Data/CDataIntMatrix.o \
	${OBJECTDIR}/data_manager/Data/CDataIntVector.o \
	${OBJECTDIR}/data_manager/Data/CDataMpileup.o \
	${OBJECTDIR}/data_manager/Data/CDataSNP.o \
	${OBJECTDIR}/data_manager/Data/CDataSam.o \
	${OBJECTDIR}/data_manager/Data/CDataStdString.o \
	${OBJECTDIR}/data_manager/Data/CDataStdStringMatrix.o \
	${OBJECTDIR}/data_manager/Data/CDataStdStringVector.o \
	${OBJECTDIR}/data_manager/Data/CDataStringSet.o \
	${OBJECTDIR}/data_manager/Data/CDataTFasta.o \
	${OBJECTDIR}/data_manager/Data/CDataTextFile.o \
	${OBJECTDIR}/data_manager/Data/CDataVCF.o \
	${OBJECTDIR}/data_manager/Data/CDataWeightsFile.o \
	${OBJECTDIR}/data_manager/IData.o \
	${OBJECTDIR}/data_manager/IDataCube.o \
	${OBJECTDIR}/data_manager/IDataMatrix.o \
	${OBJECTDIR}/data_manager/IDataValue.o \
	${OBJECTDIR}/data_manager/IDataVector.o \
	${OBJECTDIR}/data_manager/common/CDataAccess.o \
	${OBJECTDIR}/data_manager/common/CDataHelper.o \
	${OBJECTDIR}/data_manager/common/CDataSequenceIndex.o \
	${OBJECTDIR}/data_manager/common/CFastaInfo.o \
	${OBJECTDIR}/data_manager/common/CGFFFile.o \
	${OBJECTDIR}/data_manager/common/CGFFRecord.o \
	${OBJECTDIR}/data_manager/common/CMemoryMappedFile.o \
	${OBJECTDIR}/data_manager/common/CTFastaAnnotation.o \
	${OBJECTDIR}/data_manager/common/CTFastaInfo.o \
	${OBJECTDIR}/data_manager/common/CTestLc.o \
	${OBJECTDIR}/data_manager/common/CTestQuad.o \
	${OBJECTDIR}/data_manager/common/CTestQuadWc.o \
	${OBJECTDIR}/data_manager/common/CTestR0.o \
	${OBJECTDIR}/data_manager/common/CTestRinf.o \
	${OBJECTDIR}/instructions/CController.o \
	${OBJECTDIR}/instructions/CFromYaml.o \
	${OBJECTDIR}/instructions/CInstructionFactory.o \
	${OBJECTDIR}/instructions/CInstructionsHistory.o \
	${OBJECTDIR}/instructions/IInstruction.o \
	${OBJECTDIR}/instructions/Inst/CInstCommandLine.o \
	${OBJECTDIR}/instructions/Inst/CInstYAML.o \
	${OBJECTDIR}/ipc/CExperimentNode.o \
	${OBJECTDIR}/ipc/CNamedPipeManager.o \
	${OBJECTDIR}/language/CStringTable.o \
	${OBJECTDIR}/language/CStringTableCalcs.o \
	${OBJECTDIR}/language/IStringTable.o \
	${OBJECTDIR}/messages/CDebugEntry.o \
	${OBJECTDIR}/messages/CErrorEntry.o \
	${OBJECTDIR}/messages/CLogEntry.o \
	${OBJECTDIR}/messages/CLogger.o \
	${OBJECTDIR}/messages/CNormalEntry.o \
	${OBJECTDIR}/messages/CTimeStamp.o \
	${OBJECTDIR}/messages/CWarningEntry.o \
	${OBJECTDIR}/ngaSP_backend.o \
	${OBJECTDIR}/util/CClock.o \
	${OBJECTDIR}/util/CFile.o \
	${OBJECTDIR}/util/CMapTools.o \
	${OBJECTDIR}/util/CStringTools.o \
	${OBJECTDIR}/util/CVectorTools.o \
	${OBJECTDIR}/util/zutil.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-O3 -g3 -pedantic -Wall -ansi -fmessage-length=0 -Wno-long-long -Wno-variadic-macros -std=c++11 -I../../contrib/boost/boost_1_60_0 -I../../contrib/seqan/seqan_2.0.1.0 -DSEQAN_ENABLE_DEBUG=1 -DSEQAN_HAS_ZLIB=1 -DSEQAN_HAS_BZIP2=0 -DSEQAN_HAS_EXECINFO=1 -DSEQAN_ENABLE_TESTING=0 -I../../contrib/htslib-1.3.1 -I../../libs/samtoolslib
CXXFLAGS=-O3 -g3 -pedantic -Wall -ansi -fmessage-length=0 -Wno-long-long -Wno-variadic-macros -std=c++11 -I../../contrib/boost/boost_1_60_0 -I../../contrib/seqan/seqan_2.0.1.0 -DSEQAN_ENABLE_DEBUG=1 -DSEQAN_HAS_ZLIB=1 -DSEQAN_HAS_BZIP2=0 -DSEQAN_HAS_EXECINFO=1 -DSEQAN_ENABLE_TESTING=0 -I../../contrib/htslib-1.3.1 -I../../libs/samtoolslib

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/backend

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/backend: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/backend ${OBJECTFILES} ${LDLIBSOPTIONS} -L../../contrib/boost/boost_1_60_0/stage/lib -l:libboost_iostreams.a ../../contrib/htslib-1.3.1/libhts.a ../../libs/samtoolslib/dist/Debug/GNU-Linux/libsamtoolslib.a -lncurses -ltinfo -pthread -l:libboost_chrono.a -lboost_system -lz

${OBJECTDIR}/CManager.o: CManager.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CManager.o CManager.cpp

${OBJECTDIR}/IBase.o: IBase.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/IBase.o IBase.cpp

${OBJECTDIR}/IFunction.o: IFunction.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/IFunction.o IFunction.cpp

${OBJECTDIR}/IObject.o: IObject.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/IObject.o IObject.cpp

${OBJECTDIR}/calculations/CAllCalculations.o: calculations/CAllCalculations.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/CAllCalculations.o calculations/CAllCalculations.cpp

${OBJECTDIR}/calculations/CCalcFactory.o: calculations/CCalcFactory.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/CCalcFactory.o calculations/CCalcFactory.cpp

${OBJECTDIR}/calculations/CConnectorDef.o: calculations/CConnectorDef.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/CConnectorDef.o calculations/CConnectorDef.cpp

${OBJECTDIR}/calculations/Calc/CCalcArrayOpeX.o: calculations/Calc/CCalcArrayOpeX.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcArrayOpeX.o calculations/Calc/CCalcArrayOpeX.cpp

${OBJECTDIR}/calculations/Calc/CCalcArraySumAll.o: calculations/Calc/CCalcArraySumAll.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcArraySumAll.o calculations/Calc/CCalcArraySumAll.cpp

${OBJECTDIR}/calculations/Calc/CCalcBCF2VCF.o: calculations/Calc/CCalcBCF2VCF.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcBCF2VCF.o calculations/Calc/CCalcBCF2VCF.cpp

${OBJECTDIR}/calculations/Calc/CCalcBam2Bai.o: calculations/Calc/CCalcBam2Bai.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcBam2Bai.o calculations/Calc/CCalcBam2Bai.cpp

${OBJECTDIR}/calculations/Calc/CCalcBam2Mpileup.o: calculations/Calc/CCalcBam2Mpileup.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcBam2Mpileup.o calculations/Calc/CCalcBam2Mpileup.cpp

${OBJECTDIR}/calculations/Calc/CCalcBamChromosomes.o: calculations/Calc/CCalcBamChromosomes.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcBamChromosomes.o calculations/Calc/CCalcBamChromosomes.cpp

${OBJECTDIR}/calculations/Calc/CCalcBoxPlotValues.o: calculations/Calc/CCalcBoxPlotValues.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcBoxPlotValues.o calculations/Calc/CCalcBoxPlotValues.cpp

${OBJECTDIR}/calculations/Calc/CCalcCollectDataColumns.o: calculations/Calc/CCalcCollectDataColumns.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcCollectDataColumns.o calculations/Calc/CCalcCollectDataColumns.cpp

${OBJECTDIR}/calculations/Calc/CCalcConcatFiles.o: calculations/Calc/CCalcConcatFiles.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcConcatFiles.o calculations/Calc/CCalcConcatFiles.cpp

${OBJECTDIR}/calculations/Calc/CCalcConcatStrings.o: calculations/Calc/CCalcConcatStrings.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcConcatStrings.o calculations/Calc/CCalcConcatStrings.cpp

${OBJECTDIR}/calculations/Calc/CCalcCreateTFastaAnnotation.o: calculations/Calc/CCalcCreateTFastaAnnotation.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcCreateTFastaAnnotation.o calculations/Calc/CCalcCreateTFastaAnnotation.cpp

${OBJECTDIR}/calculations/Calc/CCalcCutBED.o: calculations/Calc/CCalcCutBED.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcCutBED.o calculations/Calc/CCalcCutBED.cpp

${OBJECTDIR}/calculations/Calc/CCalcCutGTF.o: calculations/Calc/CCalcCutGTF.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcCutGTF.o calculations/Calc/CCalcCutGTF.cpp

${OBJECTDIR}/calculations/Calc/CCalcDnaMatrix2MatrixPol.o: calculations/Calc/CCalcDnaMatrix2MatrixPol.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcDnaMatrix2MatrixPol.o calculations/Calc/CCalcDnaMatrix2MatrixPol.cpp

${OBJECTDIR}/calculations/Calc/CCalcDuplicatePopulations.o: calculations/Calc/CCalcDuplicatePopulations.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcDuplicatePopulations.o calculations/Calc/CCalcDuplicatePopulations.cpp

${OBJECTDIR}/calculations/Calc/CCalcEffecNucAndTCGAFreqs.o: calculations/Calc/CCalcEffecNucAndTCGAFreqs.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcEffecNucAndTCGAFreqs.o calculations/Calc/CCalcEffecNucAndTCGAFreqs.cpp

${OBJECTDIR}/calculations/Calc/CCalcExample.o: calculations/Calc/CCalcExample.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcExample.o calculations/Calc/CCalcExample.cpp

${OBJECTDIR}/calculations/Calc/CCalcExec.o: calculations/Calc/CCalcExec.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcExec.o calculations/Calc/CCalcExec.cpp

${OBJECTDIR}/calculations/Calc/CCalcFasta2DnaMatrix.o: calculations/Calc/CCalcFasta2DnaMatrix.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcFasta2DnaMatrix.o calculations/Calc/CCalcFasta2DnaMatrix.cpp

${OBJECTDIR}/calculations/Calc/CCalcFasta2TFasta.o: calculations/Calc/CCalcFasta2TFasta.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcFasta2TFasta.o calculations/Calc/CCalcFasta2TFasta.cpp

${OBJECTDIR}/calculations/Calc/CCalcFileStats.o: calculations/Calc/CCalcFileStats.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcFileStats.o calculations/Calc/CCalcFileStats.cpp

${OBJECTDIR}/calculations/Calc/CCalcFreqStats.o: calculations/Calc/CCalcFreqStats.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcFreqStats.o calculations/Calc/CCalcFreqStats.cpp

${OBJECTDIR}/calculations/Calc/CCalcFs.o: calculations/Calc/CCalcFs.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcFs.o calculations/Calc/CCalcFs.cpp

${OBJECTDIR}/calculations/Calc/CCalcGCContent.o: calculations/Calc/CCalcGCContent.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcGCContent.o calculations/Calc/CCalcGCContent.cpp

${OBJECTDIR}/calculations/Calc/CCalcGFF.o: calculations/Calc/CCalcGFF.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcGFF.o calculations/Calc/CCalcGFF.cpp

${OBJECTDIR}/calculations/Calc/CCalcGetChromosomes.o: calculations/Calc/CCalcGetChromosomes.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcGetChromosomes.o calculations/Calc/CCalcGetChromosomes.cpp

${OBJECTDIR}/calculations/Calc/CCalcHwhafsth.o: calculations/Calc/CCalcHwhafsth.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcHwhafsth.o calculations/Calc/CCalcHwhafsth.cpp

${OBJECTDIR}/calculations/Calc/CCalcJointFreqDist.o: calculations/Calc/CCalcJointFreqDist.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcJointFreqDist.o calculations/Calc/CCalcJointFreqDist.cpp

${OBJECTDIR}/calculations/Calc/CCalcLengthamngAndCalcs.o: calculations/Calc/CCalcLengthamngAndCalcs.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcLengthamngAndCalcs.o calculations/Calc/CCalcLengthamngAndCalcs.cpp

${OBJECTDIR}/calculations/Calc/CCalcListFiles.o: calculations/Calc/CCalcListFiles.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcListFiles.o calculations/Calc/CCalcListFiles.cpp

${OBJECTDIR}/calculations/Calc/CCalcMaskFileMs.o: calculations/Calc/CCalcMaskFileMs.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcMaskFileMs.o calculations/Calc/CCalcMaskFileMs.cpp

${OBJECTDIR}/calculations/Calc/CCalcMatrix2Vector.o: calculations/Calc/CCalcMatrix2Vector.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcMatrix2Vector.o calculations/Calc/CCalcMatrix2Vector.cpp

${OBJECTDIR}/calculations/Calc/CCalcMismatch.o: calculations/Calc/CCalcMismatch.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcMismatch.o calculations/Calc/CCalcMismatch.cpp

${OBJECTDIR}/calculations/Calc/CCalcMstatspop.o: calculations/Calc/CCalcMstatspop.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcMstatspop.o calculations/Calc/CCalcMstatspop.cpp

${OBJECTDIR}/calculations/Calc/CCalcMstatspopOpenFastaFile.o: calculations/Calc/CCalcMstatspopOpenFastaFile.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcMstatspopOpenFastaFile.o calculations/Calc/CCalcMstatspopOpenFastaFile.cpp

${OBJECTDIR}/calculations/Calc/CCalcMstatspopOpenMsFile.o: calculations/Calc/CCalcMstatspopOpenMsFile.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcMstatspopOpenMsFile.o calculations/Calc/CCalcMstatspopOpenMsFile.cpp

${OBJECTDIR}/calculations/Calc/CCalcMstatspopOutput.o: calculations/Calc/CCalcMstatspopOutput.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcMstatspopOutput.o calculations/Calc/CCalcMstatspopOutput.cpp

${OBJECTDIR}/calculations/Calc/CCalcOpenCoordinatesFile.o: calculations/Calc/CCalcOpenCoordinatesFile.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcOpenCoordinatesFile.o calculations/Calc/CCalcOpenCoordinatesFile.cpp

${OBJECTDIR}/calculations/Calc/CCalcOpenEffectSizesFile.o: calculations/Calc/CCalcOpenEffectSizesFile.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcOpenEffectSizesFile.o calculations/Calc/CCalcOpenEffectSizesFile.cpp

${OBJECTDIR}/calculations/Calc/CCalcOpenFastaFile.o: calculations/Calc/CCalcOpenFastaFile.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcOpenFastaFile.o calculations/Calc/CCalcOpenFastaFile.cpp

${OBJECTDIR}/calculations/Calc/CCalcOpenFreqSpecFile.o: calculations/Calc/CCalcOpenFreqSpecFile.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcOpenFreqSpecFile.o calculations/Calc/CCalcOpenFreqSpecFile.cpp

${OBJECTDIR}/calculations/Calc/CCalcOpenTFastaFile.o: calculations/Calc/CCalcOpenTFastaFile.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcOpenTFastaFile.o calculations/Calc/CCalcOpenTFastaFile.cpp

${OBJECTDIR}/calculations/Calc/CCalcOpenWeightPositionsFile.o: calculations/Calc/CCalcOpenWeightPositionsFile.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcOpenWeightPositionsFile.o calculations/Calc/CCalcOpenWeightPositionsFile.cpp

${OBJECTDIR}/calculations/Calc/CCalcPermute.o: calculations/Calc/CCalcPermute.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcPermute.o calculations/Calc/CCalcPermute.cpp

${OBJECTDIR}/calculations/Calc/CCalcPiwpiafst.o: calculations/Calc/CCalcPiwpiafst.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcPiwpiafst.o calculations/Calc/CCalcPiwpiafst.cpp

${OBJECTDIR}/calculations/Calc/CCalcR2.o: calculations/Calc/CCalcR2.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcR2.o calculations/Calc/CCalcR2.cpp

${OBJECTDIR}/calculations/Calc/CCalcR2p.o: calculations/Calc/CCalcR2p.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcR2p.o calculations/Calc/CCalcR2p.cpp

${OBJECTDIR}/calculations/Calc/CCalcRandomize.o: calculations/Calc/CCalcRandomize.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcRandomize.o calculations/Calc/CCalcRandomize.cpp

${OBJECTDIR}/calculations/Calc/CCalcSam2Mpileup.o: calculations/Calc/CCalcSam2Mpileup.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcSam2Mpileup.o calculations/Calc/CCalcSam2Mpileup.cpp

${OBJECTDIR}/calculations/Calc/CCalcSnipCaller.o: calculations/Calc/CCalcSnipCaller.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcSnipCaller.o calculations/Calc/CCalcSnipCaller.cpp

${OBJECTDIR}/calculations/Calc/CCalcSplitBAM.o: calculations/Calc/CCalcSplitBAM.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcSplitBAM.o calculations/Calc/CCalcSplitBAM.cpp

${OBJECTDIR}/calculations/Calc/CCalcSxsfss.o: calculations/Calc/CCalcSxsfss.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcSxsfss.o calculations/Calc/CCalcSxsfss.cpp

${OBJECTDIR}/calculations/Calc/CCalcTOptimalTests.o: calculations/Calc/CCalcTOptimalTests.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcTOptimalTests.o calculations/Calc/CCalcTOptimalTests.cpp

${OBJECTDIR}/calculations/Calc/CCalcVCFToGFasta.o: calculations/Calc/CCalcVCFToGFasta.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcVCFToGFasta.o calculations/Calc/CCalcVCFToGFasta.cpp

${OBJECTDIR}/calculations/Calc/CCalcX.o: calculations/Calc/CCalcX.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcX.o calculations/Calc/CCalcX.cpp

${OBJECTDIR}/calculations/Calc/CCalcY.o: calculations/Calc/CCalcY.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcY.o calculations/Calc/CCalcY.cpp

${OBJECTDIR}/calculations/Calc/CCalcZ.o: calculations/Calc/CCalcZ.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcZ.o calculations/Calc/CCalcZ.cpp

${OBJECTDIR}/calculations/Calc/CCalcnpstat.o: calculations/Calc/CCalcnpstat.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/Calc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/Calc/CCalcnpstat.o calculations/Calc/CCalcnpstat.cpp

${OBJECTDIR}/calculations/ICalculation.o: calculations/ICalculation.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/ICalculation.o calculations/ICalculation.cpp

${OBJECTDIR}/calculations/util/CComparison.o: calculations/util/CComparison.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/util/CComparison.o calculations/util/CComparison.cpp

${OBJECTDIR}/calculations/util/CDnaTools.o: calculations/util/CDnaTools.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/util/CDnaTools.o calculations/util/CDnaTools.cpp

${OBJECTDIR}/calculations/util/CMatrixPol.o: calculations/util/CMatrixPol.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/util/CMatrixPol.o calculations/util/CMatrixPol.cpp

${OBJECTDIR}/calculations/util/CMissingFreqs.o: calculations/util/CMissingFreqs.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/util/CMissingFreqs.o calculations/util/CMissingFreqs.cpp

${OBJECTDIR}/calculations/util/CValuesGFF.o: calculations/util/CValuesGFF.cpp
	${MKDIR} -p ${OBJECTDIR}/calculations/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/calculations/util/CValuesGFF.o calculations/util/CValuesGFF.cpp

${OBJECTDIR}/commands/CAllCommands.o: commands/CAllCommands.cpp
	${MKDIR} -p ${OBJECTDIR}/commands
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CAllCommands.o commands/CAllCommands.cpp

${OBJECTDIR}/commands/CCommandFactory.o: commands/CCommandFactory.cpp
	${MKDIR} -p ${OBJECTDIR}/commands
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CCommandFactory.o commands/CCommandFactory.cpp

${OBJECTDIR}/commands/CMD/CCMDAdd.o: commands/CMD/CCMDAdd.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDAdd.o commands/CMD/CCMDAdd.cpp

${OBJECTDIR}/commands/CMD/CCMDAppHelp.o: commands/CMD/CCMDAppHelp.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDAppHelp.o commands/CMD/CCMDAppHelp.cpp

${OBJECTDIR}/commands/CMD/CCMDAppend.o: commands/CMD/CCMDAppend.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDAppend.o commands/CMD/CCMDAppend.cpp

${OBJECTDIR}/commands/CMD/CCMDCalc.o: commands/CMD/CCMDCalc.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDCalc.o commands/CMD/CCMDCalc.cpp

${OBJECTDIR}/commands/CMD/CCMDConstant.o: commands/CMD/CCMDConstant.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDConstant.o commands/CMD/CCMDConstant.cpp

${OBJECTDIR}/commands/CMD/CCMDDelete.o: commands/CMD/CCMDDelete.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDDelete.o commands/CMD/CCMDDelete.cpp

${OBJECTDIR}/commands/CMD/CCMDDim.o: commands/CMD/CCMDDim.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDDim.o commands/CMD/CCMDDim.cpp

${OBJECTDIR}/commands/CMD/CCMDDryRun.o: commands/CMD/CCMDDryRun.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDDryRun.o commands/CMD/CCMDDryRun.cpp

${OBJECTDIR}/commands/CMD/CCMDElse.o: commands/CMD/CCMDElse.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDElse.o commands/CMD/CCMDElse.cpp

${OBJECTDIR}/commands/CMD/CCMDEndForeach.o: commands/CMD/CCMDEndForeach.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDEndForeach.o commands/CMD/CCMDEndForeach.cpp

${OBJECTDIR}/commands/CMD/CCMDEndIf.o: commands/CMD/CCMDEndIf.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDEndIf.o commands/CMD/CCMDEndIf.cpp

${OBJECTDIR}/commands/CMD/CCMDEndWith.o: commands/CMD/CCMDEndWith.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDEndWith.o commands/CMD/CCMDEndWith.cpp

${OBJECTDIR}/commands/CMD/CCMDExec.o: commands/CMD/CCMDExec.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDExec.o commands/CMD/CCMDExec.cpp

${OBJECTDIR}/commands/CMD/CCMDForeach.o: commands/CMD/CCMDForeach.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDForeach.o commands/CMD/CCMDForeach.cpp

${OBJECTDIR}/commands/CMD/CCMDHistory.o: commands/CMD/CCMDHistory.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDHistory.o commands/CMD/CCMDHistory.cpp

${OBJECTDIR}/commands/CMD/CCMDIf.o: commands/CMD/CCMDIf.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDIf.o commands/CMD/CCMDIf.cpp

${OBJECTDIR}/commands/CMD/CCMDLoadInstructionsFile.o: commands/CMD/CCMDLoadInstructionsFile.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDLoadInstructionsFile.o commands/CMD/CCMDLoadInstructionsFile.cpp

${OBJECTDIR}/commands/CMD/CCMDLog.o: commands/CMD/CCMDLog.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDLog.o commands/CMD/CCMDLog.cpp

${OBJECTDIR}/commands/CMD/CCMDMemInfo.o: commands/CMD/CCMDMemInfo.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDMemInfo.o commands/CMD/CCMDMemInfo.cpp

${OBJECTDIR}/commands/CMD/CCMDOpenDataFile.o: commands/CMD/CCMDOpenDataFile.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDOpenDataFile.o commands/CMD/CCMDOpenDataFile.cpp

${OBJECTDIR}/commands/CMD/CCMDOutput.o: commands/CMD/CCMDOutput.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDOutput.o commands/CMD/CCMDOutput.cpp

${OBJECTDIR}/commands/CMD/CCMDPipe.o: commands/CMD/CCMDPipe.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDPipe.o commands/CMD/CCMDPipe.cpp

${OBJECTDIR}/commands/CMD/CCMDPrint.o: commands/CMD/CCMDPrint.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDPrint.o commands/CMD/CCMDPrint.cpp

${OBJECTDIR}/commands/CMD/CCMDReserve.o: commands/CMD/CCMDReserve.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDReserve.o commands/CMD/CCMDReserve.cpp

${OBJECTDIR}/commands/CMD/CCMDReset.o: commands/CMD/CCMDReset.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDReset.o commands/CMD/CCMDReset.cpp

${OBJECTDIR}/commands/CMD/CCMDRun.o: commands/CMD/CCMDRun.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDRun.o commands/CMD/CCMDRun.cpp

${OBJECTDIR}/commands/CMD/CCMDSaveState.o: commands/CMD/CCMDSaveState.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDSaveState.o commands/CMD/CCMDSaveState.cpp

${OBJECTDIR}/commands/CMD/CCMDSetValue.o: commands/CMD/CCMDSetValue.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDSetValue.o commands/CMD/CCMDSetValue.cpp

${OBJECTDIR}/commands/CMD/CCMDSocket.o: commands/CMD/CCMDSocket.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDSocket.o commands/CMD/CCMDSocket.cpp

${OBJECTDIR}/commands/CMD/CCMDStop.o: commands/CMD/CCMDStop.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDStop.o commands/CMD/CCMDStop.cpp

${OBJECTDIR}/commands/CMD/CCMDSyntax.o: commands/CMD/CCMDSyntax.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDSyntax.o commands/CMD/CCMDSyntax.cpp

${OBJECTDIR}/commands/CMD/CCMDVerbose.o: commands/CMD/CCMDVerbose.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDVerbose.o commands/CMD/CCMDVerbose.cpp

${OBJECTDIR}/commands/CMD/CCMDVersion.o: commands/CMD/CCMDVersion.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDVersion.o commands/CMD/CCMDVersion.cpp

${OBJECTDIR}/commands/CMD/CCMDWith.o: commands/CMD/CCMDWith.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDWith.o commands/CMD/CCMDWith.cpp

${OBJECTDIR}/commands/CMD/CCMDmstatspop.o: commands/CMD/CCMDmstatspop.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/CMD
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/CMD/CCMDmstatspop.o commands/CMD/CCMDmstatspop.cpp

${OBJECTDIR}/commands/COS/COption.o: commands/COS/COption.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/COS
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/COS/COption.o commands/COS/COption.cpp

${OBJECTDIR}/commands/COS/COptionsContainer.o: commands/COS/COptionsContainer.cpp
	${MKDIR} -p ${OBJECTDIR}/commands/COS
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/COS/COptionsContainer.o commands/COS/COptionsContainer.cpp

${OBJECTDIR}/commands/ICommand.o: commands/ICommand.cpp
	${MKDIR} -p ${OBJECTDIR}/commands
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/commands/ICommand.o commands/ICommand.cpp

${OBJECTDIR}/data_manager/CDataFactory.o: data_manager/CDataFactory.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/CDataFactory.o data_manager/CDataFactory.cpp

${OBJECTDIR}/data_manager/CDataManager.o: data_manager/CDataManager.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/CDataManager.o data_manager/CDataManager.cpp

${OBJECTDIR}/data_manager/Data/CDataBCF.o: data_manager/Data/CDataBCF.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataBCF.o data_manager/Data/CDataBCF.cpp

${OBJECTDIR}/data_manager/Data/CDataBam.o: data_manager/Data/CDataBam.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataBam.o data_manager/Data/CDataBam.cpp

${OBJECTDIR}/data_manager/Data/CDataBamIndex.o: data_manager/Data/CDataBamIndex.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataBamIndex.o data_manager/Data/CDataBamIndex.cpp

${OBJECTDIR}/data_manager/Data/CDataBoolean.o: data_manager/Data/CDataBoolean.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataBoolean.o data_manager/Data/CDataBoolean.cpp

${OBJECTDIR}/data_manager/Data/CDataBooleanCube.o: data_manager/Data/CDataBooleanCube.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataBooleanCube.o data_manager/Data/CDataBooleanCube.cpp

${OBJECTDIR}/data_manager/Data/CDataBooleanMatrix.o: data_manager/Data/CDataBooleanMatrix.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataBooleanMatrix.o data_manager/Data/CDataBooleanMatrix.cpp

${OBJECTDIR}/data_manager/Data/CDataBooleanVector.o: data_manager/Data/CDataBooleanVector.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataBooleanVector.o data_manager/Data/CDataBooleanVector.cpp

${OBJECTDIR}/data_manager/Data/CDataChar.o: data_manager/Data/CDataChar.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataChar.o data_manager/Data/CDataChar.cpp

${OBJECTDIR}/data_manager/Data/CDataCharCube.o: data_manager/Data/CDataCharCube.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataCharCube.o data_manager/Data/CDataCharCube.cpp

${OBJECTDIR}/data_manager/Data/CDataCharMatrix.o: data_manager/Data/CDataCharMatrix.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataCharMatrix.o data_manager/Data/CDataCharMatrix.cpp

${OBJECTDIR}/data_manager/Data/CDataCharVector.o: data_manager/Data/CDataCharVector.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataCharVector.o data_manager/Data/CDataCharVector.cpp

${OBJECTDIR}/data_manager/Data/CDataDouble.o: data_manager/Data/CDataDouble.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataDouble.o data_manager/Data/CDataDouble.cpp

${OBJECTDIR}/data_manager/Data/CDataDoubleCube.o: data_manager/Data/CDataDoubleCube.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataDoubleCube.o data_manager/Data/CDataDoubleCube.cpp

${OBJECTDIR}/data_manager/Data/CDataDoubleMatrix.o: data_manager/Data/CDataDoubleMatrix.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataDoubleMatrix.o data_manager/Data/CDataDoubleMatrix.cpp

${OBJECTDIR}/data_manager/Data/CDataDoubleVector.o: data_manager/Data/CDataDoubleVector.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataDoubleVector.o data_manager/Data/CDataDoubleVector.cpp

${OBJECTDIR}/data_manager/Data/CDataFasta.o: data_manager/Data/CDataFasta.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataFasta.o data_manager/Data/CDataFasta.cpp

${OBJECTDIR}/data_manager/Data/CDataFloat.o: data_manager/Data/CDataFloat.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataFloat.o data_manager/Data/CDataFloat.cpp

${OBJECTDIR}/data_manager/Data/CDataFloatCube.o: data_manager/Data/CDataFloatCube.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataFloatCube.o data_manager/Data/CDataFloatCube.cpp

${OBJECTDIR}/data_manager/Data/CDataFloatMatrix.o: data_manager/Data/CDataFloatMatrix.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataFloatMatrix.o data_manager/Data/CDataFloatMatrix.cpp

${OBJECTDIR}/data_manager/Data/CDataFloatVector.o: data_manager/Data/CDataFloatVector.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataFloatVector.o data_manager/Data/CDataFloatVector.cpp

${OBJECTDIR}/data_manager/Data/CDataGFF.o: data_manager/Data/CDataGFF.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataGFF.o data_manager/Data/CDataGFF.cpp

${OBJECTDIR}/data_manager/Data/CDataGFasta.o: data_manager/Data/CDataGFasta.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataGFasta.o data_manager/Data/CDataGFasta.cpp

${OBJECTDIR}/data_manager/Data/CDataGTF.o: data_manager/Data/CDataGTF.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataGTF.o data_manager/Data/CDataGTF.cpp

${OBJECTDIR}/data_manager/Data/CDataInt.o: data_manager/Data/CDataInt.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataInt.o data_manager/Data/CDataInt.cpp

${OBJECTDIR}/data_manager/Data/CDataInt64.o: data_manager/Data/CDataInt64.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataInt64.o data_manager/Data/CDataInt64.cpp

${OBJECTDIR}/data_manager/Data/CDataInt64Cube.o: data_manager/Data/CDataInt64Cube.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataInt64Cube.o data_manager/Data/CDataInt64Cube.cpp

${OBJECTDIR}/data_manager/Data/CDataInt64Matrix.o: data_manager/Data/CDataInt64Matrix.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataInt64Matrix.o data_manager/Data/CDataInt64Matrix.cpp

${OBJECTDIR}/data_manager/Data/CDataInt64Vector.o: data_manager/Data/CDataInt64Vector.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataInt64Vector.o data_manager/Data/CDataInt64Vector.cpp

${OBJECTDIR}/data_manager/Data/CDataIntCube.o: data_manager/Data/CDataIntCube.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataIntCube.o data_manager/Data/CDataIntCube.cpp

${OBJECTDIR}/data_manager/Data/CDataIntMatrix.o: data_manager/Data/CDataIntMatrix.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataIntMatrix.o data_manager/Data/CDataIntMatrix.cpp

${OBJECTDIR}/data_manager/Data/CDataIntVector.o: data_manager/Data/CDataIntVector.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataIntVector.o data_manager/Data/CDataIntVector.cpp

${OBJECTDIR}/data_manager/Data/CDataMpileup.o: data_manager/Data/CDataMpileup.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataMpileup.o data_manager/Data/CDataMpileup.cpp

${OBJECTDIR}/data_manager/Data/CDataSNP.o: data_manager/Data/CDataSNP.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataSNP.o data_manager/Data/CDataSNP.cpp

${OBJECTDIR}/data_manager/Data/CDataSam.o: data_manager/Data/CDataSam.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataSam.o data_manager/Data/CDataSam.cpp

${OBJECTDIR}/data_manager/Data/CDataStdString.o: data_manager/Data/CDataStdString.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataStdString.o data_manager/Data/CDataStdString.cpp

${OBJECTDIR}/data_manager/Data/CDataStdStringMatrix.o: data_manager/Data/CDataStdStringMatrix.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataStdStringMatrix.o data_manager/Data/CDataStdStringMatrix.cpp

${OBJECTDIR}/data_manager/Data/CDataStdStringVector.o: data_manager/Data/CDataStdStringVector.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataStdStringVector.o data_manager/Data/CDataStdStringVector.cpp

${OBJECTDIR}/data_manager/Data/CDataStringSet.o: data_manager/Data/CDataStringSet.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataStringSet.o data_manager/Data/CDataStringSet.cpp

${OBJECTDIR}/data_manager/Data/CDataTFasta.o: data_manager/Data/CDataTFasta.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataTFasta.o data_manager/Data/CDataTFasta.cpp

${OBJECTDIR}/data_manager/Data/CDataTextFile.o: data_manager/Data/CDataTextFile.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataTextFile.o data_manager/Data/CDataTextFile.cpp

${OBJECTDIR}/data_manager/Data/CDataVCF.o: data_manager/Data/CDataVCF.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataVCF.o data_manager/Data/CDataVCF.cpp

${OBJECTDIR}/data_manager/Data/CDataWeightsFile.o: data_manager/Data/CDataWeightsFile.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/Data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/Data/CDataWeightsFile.o data_manager/Data/CDataWeightsFile.cpp

${OBJECTDIR}/data_manager/IData.o: data_manager/IData.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/IData.o data_manager/IData.cpp

${OBJECTDIR}/data_manager/IDataCube.o: data_manager/IDataCube.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/IDataCube.o data_manager/IDataCube.cpp

${OBJECTDIR}/data_manager/IDataMatrix.o: data_manager/IDataMatrix.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/IDataMatrix.o data_manager/IDataMatrix.cpp

${OBJECTDIR}/data_manager/IDataValue.o: data_manager/IDataValue.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/IDataValue.o data_manager/IDataValue.cpp

${OBJECTDIR}/data_manager/IDataVector.o: data_manager/IDataVector.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/IDataVector.o data_manager/IDataVector.cpp

${OBJECTDIR}/data_manager/common/CDataAccess.o: data_manager/common/CDataAccess.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CDataAccess.o data_manager/common/CDataAccess.cpp

${OBJECTDIR}/data_manager/common/CDataHelper.o: data_manager/common/CDataHelper.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CDataHelper.o data_manager/common/CDataHelper.cpp

${OBJECTDIR}/data_manager/common/CDataSequenceIndex.o: data_manager/common/CDataSequenceIndex.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CDataSequenceIndex.o data_manager/common/CDataSequenceIndex.cpp

${OBJECTDIR}/data_manager/common/CFastaInfo.o: data_manager/common/CFastaInfo.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CFastaInfo.o data_manager/common/CFastaInfo.cpp

${OBJECTDIR}/data_manager/common/CGFFFile.o: data_manager/common/CGFFFile.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CGFFFile.o data_manager/common/CGFFFile.cpp

${OBJECTDIR}/data_manager/common/CGFFRecord.o: data_manager/common/CGFFRecord.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CGFFRecord.o data_manager/common/CGFFRecord.cpp

${OBJECTDIR}/data_manager/common/CMemoryMappedFile.o: data_manager/common/CMemoryMappedFile.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CMemoryMappedFile.o data_manager/common/CMemoryMappedFile.cpp

${OBJECTDIR}/data_manager/common/CTFastaAnnotation.o: data_manager/common/CTFastaAnnotation.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CTFastaAnnotation.o data_manager/common/CTFastaAnnotation.cpp

${OBJECTDIR}/data_manager/common/CTFastaInfo.o: data_manager/common/CTFastaInfo.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CTFastaInfo.o data_manager/common/CTFastaInfo.cpp

${OBJECTDIR}/data_manager/common/CTestLc.o: data_manager/common/CTestLc.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CTestLc.o data_manager/common/CTestLc.cpp

${OBJECTDIR}/data_manager/common/CTestQuad.o: data_manager/common/CTestQuad.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CTestQuad.o data_manager/common/CTestQuad.cpp

${OBJECTDIR}/data_manager/common/CTestQuadWc.o: data_manager/common/CTestQuadWc.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CTestQuadWc.o data_manager/common/CTestQuadWc.cpp

${OBJECTDIR}/data_manager/common/CTestR0.o: data_manager/common/CTestR0.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CTestR0.o data_manager/common/CTestR0.cpp

${OBJECTDIR}/data_manager/common/CTestRinf.o: data_manager/common/CTestRinf.cpp
	${MKDIR} -p ${OBJECTDIR}/data_manager/common
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data_manager/common/CTestRinf.o data_manager/common/CTestRinf.cpp

${OBJECTDIR}/instructions/CController.o: instructions/CController.cpp
	${MKDIR} -p ${OBJECTDIR}/instructions
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instructions/CController.o instructions/CController.cpp

${OBJECTDIR}/instructions/CFromYaml.o: instructions/CFromYaml.cpp
	${MKDIR} -p ${OBJECTDIR}/instructions
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instructions/CFromYaml.o instructions/CFromYaml.cpp

${OBJECTDIR}/instructions/CInstructionFactory.o: instructions/CInstructionFactory.cpp
	${MKDIR} -p ${OBJECTDIR}/instructions
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instructions/CInstructionFactory.o instructions/CInstructionFactory.cpp

${OBJECTDIR}/instructions/CInstructionsHistory.o: instructions/CInstructionsHistory.cpp
	${MKDIR} -p ${OBJECTDIR}/instructions
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instructions/CInstructionsHistory.o instructions/CInstructionsHistory.cpp

${OBJECTDIR}/instructions/IInstruction.o: instructions/IInstruction.cpp
	${MKDIR} -p ${OBJECTDIR}/instructions
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instructions/IInstruction.o instructions/IInstruction.cpp

${OBJECTDIR}/instructions/Inst/CInstCommandLine.o: instructions/Inst/CInstCommandLine.cpp
	${MKDIR} -p ${OBJECTDIR}/instructions/Inst
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instructions/Inst/CInstCommandLine.o instructions/Inst/CInstCommandLine.cpp

${OBJECTDIR}/instructions/Inst/CInstYAML.o: instructions/Inst/CInstYAML.cpp
	${MKDIR} -p ${OBJECTDIR}/instructions/Inst
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instructions/Inst/CInstYAML.o instructions/Inst/CInstYAML.cpp

${OBJECTDIR}/ipc/CExperimentNode.o: ipc/CExperimentNode.cpp
	${MKDIR} -p ${OBJECTDIR}/ipc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ipc/CExperimentNode.o ipc/CExperimentNode.cpp

${OBJECTDIR}/ipc/CNamedPipeManager.o: ipc/CNamedPipeManager.cpp
	${MKDIR} -p ${OBJECTDIR}/ipc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ipc/CNamedPipeManager.o ipc/CNamedPipeManager.cpp

${OBJECTDIR}/language/CStringTable.o: language/CStringTable.cpp
	${MKDIR} -p ${OBJECTDIR}/language
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/language/CStringTable.o language/CStringTable.cpp

${OBJECTDIR}/language/CStringTableCalcs.o: language/CStringTableCalcs.cpp
	${MKDIR} -p ${OBJECTDIR}/language
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/language/CStringTableCalcs.o language/CStringTableCalcs.cpp

${OBJECTDIR}/language/IStringTable.o: language/IStringTable.cpp
	${MKDIR} -p ${OBJECTDIR}/language
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/language/IStringTable.o language/IStringTable.cpp

${OBJECTDIR}/messages/CDebugEntry.o: messages/CDebugEntry.cpp
	${MKDIR} -p ${OBJECTDIR}/messages
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/messages/CDebugEntry.o messages/CDebugEntry.cpp

${OBJECTDIR}/messages/CErrorEntry.o: messages/CErrorEntry.cpp
	${MKDIR} -p ${OBJECTDIR}/messages
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/messages/CErrorEntry.o messages/CErrorEntry.cpp

${OBJECTDIR}/messages/CLogEntry.o: messages/CLogEntry.cpp
	${MKDIR} -p ${OBJECTDIR}/messages
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/messages/CLogEntry.o messages/CLogEntry.cpp

${OBJECTDIR}/messages/CLogger.o: messages/CLogger.cpp
	${MKDIR} -p ${OBJECTDIR}/messages
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/messages/CLogger.o messages/CLogger.cpp

${OBJECTDIR}/messages/CNormalEntry.o: messages/CNormalEntry.cpp
	${MKDIR} -p ${OBJECTDIR}/messages
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/messages/CNormalEntry.o messages/CNormalEntry.cpp

${OBJECTDIR}/messages/CTimeStamp.o: messages/CTimeStamp.cpp
	${MKDIR} -p ${OBJECTDIR}/messages
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/messages/CTimeStamp.o messages/CTimeStamp.cpp

${OBJECTDIR}/messages/CWarningEntry.o: messages/CWarningEntry.cpp
	${MKDIR} -p ${OBJECTDIR}/messages
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/messages/CWarningEntry.o messages/CWarningEntry.cpp

${OBJECTDIR}/ngaSP_backend.o: ngaSP_backend.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ngaSP_backend.o ngaSP_backend.cpp

${OBJECTDIR}/util/CClock.o: util/CClock.cpp
	${MKDIR} -p ${OBJECTDIR}/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/CClock.o util/CClock.cpp

${OBJECTDIR}/util/CFile.o: util/CFile.cpp
	${MKDIR} -p ${OBJECTDIR}/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/CFile.o util/CFile.cpp

${OBJECTDIR}/util/CMapTools.o: util/CMapTools.cpp
	${MKDIR} -p ${OBJECTDIR}/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/CMapTools.o util/CMapTools.cpp

${OBJECTDIR}/util/CStringTools.o: util/CStringTools.cpp
	${MKDIR} -p ${OBJECTDIR}/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/CStringTools.o util/CStringTools.cpp

${OBJECTDIR}/util/CVectorTools.o: util/CVectorTools.cpp
	${MKDIR} -p ${OBJECTDIR}/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/CVectorTools.o util/CVectorTools.cpp

${OBJECTDIR}/util/zutil.o: util/zutil.c
	${MKDIR} -p ${OBJECTDIR}/util
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/zutil.o util/zutil.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
