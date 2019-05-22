/*
 * ngaSP: the computational solution for next generation analysis of 
 * Sequence Polymorphisms.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
 * Centre for Research in Agricultural Genomics (CRAG).
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version
 * 2.1 as published by the Free Software Foundation.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 2.1 for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License version 2.1 along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
/**
 *  \brief     CCalcFactory.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcFactory.h"

#include "../language/CStringTable.h"

#include "ICalculation.h"

#include "Calc/CCalcTOptimalTests.h"
#include "Calc/CCalcR2.h"
#include "Calc/CCalcR2p.h"
#include "Calc/CCalcFreqStats.h"
#include "Calc/CCalcMismatch.h"
#include "Calc/CCalcSxsfss.h"
#include "Calc/CCalcJointFreqDist.h"
#include "Calc/CCalcPiwpiafst.h"
#include "Calc/CCalcHwhafsth.h"
#include "Calc/CCalcFs.h"
#include "Calc/CCalcPermute.h"
#include "Calc/CCalcFasta2DnaMatrix.h"
#include "Calc/CCalcDnaMatrix2MatrixPol.h"
#include "Calc/CCalcOpenFastaFile.h"
#include "Calc/CCalcOpenTFastaFile.h"
#include "Calc/CCalcMstatspopOpenFastaFile.h"
#include "Calc/CCalcMstatspopOpenMsFile.h"
#include "Calc/CCalcGFF.h"
#include "Calc/CCalcFileStats.h"
#include "Calc/CCalcOpenFreqSpecFile.h"
#include "Calc/CCalcMaskFileMs.h"
#include "Calc/CCalcEffecNucAndTCGAFreqs.h"
#include "Calc/CCalcLengthamngAndCalcs.h"
#include "Calc/CCalcX.h"
#include "Calc/CCalcY.h"
#include "Calc/CCalcZ.h"
#include "Calc/CCalcArrayOpeX.h"
#include "Calc/CCalcMstatspopOutput.h"
#include "Calc/CCalcArraySumAll.h"
#include "Calc/CCalcDuplicatePopulations.h"
#include "Calc/CCalcMstatspop.h"
#include "Calc/CCalcRandomize.h"
#include "Calc/CCalcGCContent.h"
#include "Calc/CCalcFasta2TFasta.h"
#include "Calc/CCalcCreateTFastaAnnotation.h"
#include "Calc/CCalcOpenEffectSizesFile.h"
#include "Calc/CCalcOpenCoordinatesFile.h"
#include "Calc/CCalcOpenWeightPositionsFile.h"
#include "Calc/CCalcExec.h"
#include "Calc/CCalcBCF2VCF.h"
#include "Calc/CCalcBam2Mpileup.h"
#include "Calc/CCalcSam2Mpileup.h"
#include "Calc/CCalcSnipCaller.h"
#include "Calc/CCalcBam2Bai.h"
#include "Calc/CCalcBamChromosomes.h"
#include "Calc/CCalcConcatFiles.h"
#include "Calc/CCalcCollectDataColumns.h"
#include "Calc/CCalcBoxPlotValues.h"
#include "Calc/CCalcnpstat.h"
#include "Calc/CCalcVCFToGFasta.h"
#include "Calc/CCalcGetChromosomes.h"
#include "Calc/CCalcCutBED.h"
#include "Calc/CCalcCutGTF.h"
#include "Calc/CCalcExample.h"
#include "Calc/CCalcListFiles.h"
#include "Calc/CCalcMatrix2Vector.h"
#include "Calc/CCalcConcatStrings.h"
#include "Calc/CCalcSplitBAM.h"
#include "Calc/CCalcConcatFileNames.h"
#include "Calc/CCalcGetFileName.h"
#include "Calc/CCalcGetSeqLength.h"
#include "Calc/CCalcGetMeanReadDepth.h"
#include "Calc/CCalcDummy.h"n//_CALC_LAST
  
CCalcFactory::CCalcFactory() {
  // ===========================================================================
  // The factory has one empty object of each type.
  // When the factory is asked for a new object it returns a clone of the
  // required one.
  // It also have a copy of each object for retrieving all calcs information to
  // who ask for it. For example: the help command, the web interface, ...
  // And one object of each type must be instancied for accessing their info
  // (name, ...).
  // ===========================================================================
  data_map_[KeyString::CALC_OPTIMAL_TESTS]          = new CCalcTOptimalTests();
  data_map_[KeyString::CALC_R2]                     = new CCalcR2();
  data_map_[KeyString::CALC_R2P]                    = new CCalcR2p();
  data_map_[KeyString::CALC_FREQ_STATS]             = new CCalcFreqStats();
  data_map_[KeyString::CALC_MISMATCH]               = new CCalcMismatch();
  data_map_[KeyString::CALC_SXSFSS]                 = new CCalcSxsfss();
  data_map_[KeyString::CALC_JOINT_FREQ_DIST]        = new CCalcJointFreqDist();
  data_map_[KeyString::CALC_PIWPIAFST]              = new CCalcPiwpiafst();
  data_map_[KeyString::CALC_HWHAFSTH]               = new CCalcHwhafsth();
  data_map_[KeyString::CALC_FS]                     = new CCalcFs();
  data_map_[KeyString::CALC_PERMUTE]                = new CCalcPermute();
  data_map_[KeyString::CALC_FASTA2DNAMATRIX]        = new CCalcFasta2DnaMatrix();
  data_map_[KeyString::CALC_DNAMATRIX2MATRIXPOL]    = new CCalcDnaMatrix2MatrixPol();
  data_map_[KeyString::CALC_OPEN_FASTA]             = new CCalcOpenFastaFile();
  data_map_[KeyString::CALC_OPEN_TFASTA]            = new CCalcOpenTFastaFile();
  data_map_[KeyString::CALC_GFF]                    = new CCalcGFF();
  data_map_[KeyString::CALC_MSTATSPOP_OPEN_FASTA]   = new CCalcMstatspopOpenFastaFile();
  data_map_[KeyString::CALC_MSTATSPOP_OPEN_MS]      = new CCalcMstatspopOpenMsFile();
  data_map_[KeyString::CALC_FILE_STATS]             = new CCalcFileStats();
  data_map_[KeyString::CALC_OPEN_FREQ_SPECTRUM]     = new CCalcOpenFreqSpecFile();
  data_map_[KeyString::CALC_MASK_FILE_MS]           = new CCalcMaskFileMs();
  data_map_[KeyString::CALC_EFFEC_NUC_TCGA_FREQS]   = new CCalcEffecNucAndTCGAFreqs();
  data_map_[KeyString::CALC_LENGTHAMNG]             = new CCalcLengthamngAndCalcs();
  data_map_[KeyString::CALC_X]                      = new CCalcX();
  data_map_[KeyString::CALC_Y]                      = new CCalcY();
  data_map_[KeyString::CALC_Z]                      = new CCalcZ();
  data_map_[KeyString::CALC_ARRAY_OPE_X]            = new CCalcArrayOpeX();
  data_map_[KeyString::CALC_MSTATSPOP_OUTPUT]       = new CCalcMstatspopOutput();
  data_map_[KeyString::CALC_ARRAY_SUM_ALL]          = new CCalcArraySumAll();
  data_map_[KeyString::CALC_DUPLICATE_POPULATIONS]  = new CCalcDuplicatePopulations();
  data_map_[KeyString::CALC_RANDOMIZE]              = new CCalcRandomize();
  data_map_[KeyString::CALC_MSTATSPOP]              = new CCalcMstatspop();
  data_map_[KeyString::CALC_GCCONTENT]              = new CCalcGCContent();
  data_map_[KeyString::CALC_FASTA2TFASTA]           = new CCalcFasta2TFasta();
  data_map_[KeyString::CALC_CREATETFASTAANNOTATION] = new CCalcCreateTFastaAnnotation();
  data_map_[KeyString::CALC_OPEN_EFFECTSIZES]       = new CCalcOpenEffectSizesFile();
  data_map_[KeyString::CALC_OPEN_COORDINATES]       = new CCalcOpenCoordinatesFile();
  data_map_[KeyString::CALC_OPEN_WEIGHTPOSITIONS]   = new CCalcOpenWeightPositionsFile();
  data_map_[KeyString::CALC_EXEC]                   = new CCalcExec();
  data_map_[KeyString::CALC_BCF2VCF]                = new CCalcBCF2VCF();   
  data_map_[KeyString::CALC_BAM2MPILEUP]            = new CCalcBam2Mpileup();   
  data_map_[KeyString::CALC_SAM2MPILEUP]            = new CCalcSam2Mpileup();   
  data_map_[KeyString::CALC_SNIPCALLER]             = new CCalcSnipCaller();   
  data_map_[KeyString::CALC_BAM2BAI]                = new CCalcBam2Bai();   
  data_map_[KeyString::CALC_BAM_CHROMOSOMES]        = new CCalcBamChromosomes();   
  data_map_[KeyString::CALC_CONCAT_FILES]           = new CCalcConcatFiles();   
  data_map_[KeyString::CALC_COLLECT_DATA_COLUMNS]   = new CCalcCollectDataColumns();   
  data_map_[KeyString::CALC_BOX_PLOT_VALUES]        = new CCalcBoxPlotValues();
  data_map_[KeyString::CALC_NPSTAT]                 = new CCalcnpstat();
  data_map_[KeyString::CALC_VCF2GFASTA]             = new CCalcVCFToGFasta();
  data_map_[KeyString::CALC_GET_CHROM]              = new CCalcGetChromosomes();
  data_map_[KeyString::CALC_CUT_BED]                = new CCalcCutBED();
  data_map_[KeyString::CALC_CUT_GTF]                = new CCalcCutGTF();
  data_map_[KeyString::CALC_EXAMPLE]                = new CCalcExample();
  data_map_[KeyString::CALC_LIST_FILES]             = new CCalcListFiles();
  data_map_[KeyString::CALC_MATRIX2VECTOR]          = new CCalcMatrix2Vector();
  data_map_[KeyString::CALC_CONCAT_STRINGS]         = new CCalcConcatStrings();   
  data_map_[KeyString::CALC_SPLIT_BAM]              = new CCalcSplitBAM();
  data_map_[KeyString::CALC_CONCAT_FILE_NAMES]      = new CCalcConcatFileNames();
  data_map_[KeyString::CALC_GET_FILE_NAME]          = new CCalcGetFileName();
  data_map_[KeyString::CALC_GET_SEQ_LEN]            = new CCalcGetSeqLength();
  data_map_[KeyString::CALC_GET_MRD]                = new CCalcGetMeanReadDepth();
  data_map_[KeyString::CALC_Dummy] = new CCalcDummy();n  //data_map_[KeyString::_CALC_LAST]
}

CCalcFactory::~CCalcFactory() {
  std::map<KeyString, ICalculation *>::iterator it;
  for (it = data_map_.begin(); it != data_map_.end(); ++it) {
    // Delete the Data object:
    delete it->second;
    it->second = NULL;
  }
  data_map_.clear();  // Remove all elements from the map
}

ICalculation *CCalcFactory::GetCalculation(
  KeyString calculation_id) {
  ICalculation *original_calc = NULL;
  ICalculation *new_calculation = NULL;

  original_calc = data_map_[calculation_id];

  if (original_calc != NULL) {
    new_calculation = original_calc->clone();
  }
//
//
//
//  switch (calculation_id) {
//  case KeyString::CALC_OPTIMAL_TESTS:
//    new_calculation = new CCalcTOptimalTests();
//    break;
//  case KeyString::CALC_R2:
//    new_calculation = new CCalcR2();
//    break;
//  case KeyString::CALC_R2P:
//    new_calculation = new CCalcR2p();
//    break;
//  case KeyString::CALC_FREQ_STATS:
//    new_calculation = new CCalcFreqStats();
//    break;
//  case KeyString::CALC_MISMATCH:
//    new_calculation = new CCalcMismatch();
//    break;
//  case KeyString::CALC_SXSFSS:
//    new_calculation = new CCalcSxsfss();
//    break;
//  case KeyString::CALC_JOINT_FREQ_DIST:
//    new_calculation = new CCalcJointFreqDist();
//    break;
//  case KeyString::CALC_PIWPIAFST:
//    new_calculation = new CCalcPiwpiafst();
//    break;
//  case KeyString::CALC_HWHAFSTH:
//    new_calculation = new CCalcHwhafsth();
//    break;
//  case KeyString::CALC_FS:
//    new_calculation = new CCalcFs();
//    break;
//  case KeyString::CALC_PERMUTE:
//    new_calculation = new CCalcPermute();
//    break;
//  case KeyString::CALC_FASTA2DNAMATRIX:
//    new_calculation = new CCalcFasta2DnaMatrix();
//    break;
//  case KeyString::CALC_DNAMATRIX2MATRIXPOL:
//    new_calculation = new CCalcDnaMatrix2MatrixPol();
//    break;
//  case KeyString::CALC_OPEN_FASTA:
//    new_calculation = new CCalcOpenFastaFile();
//    break;
//  case KeyString::CALC_GFF:
//    new_calculation = new CCalcGFF();
//    break;
//  case KeyString::CALC_MSTATSPOP_OPEN_FASTA:
//    new_calculation = new CCalcMstatspopOpenFastaFile();
//    break;
//  case KeyString::CALC_MSTATSPOP_OPEN_MS:
//    new_calculation = new CCalcMstatspopOpenMsFile();
//    break;
//  case KeyString::CALC_FILE_STATS:
//    new_calculation = new CCalcFileStats();
//    break;
//  case KeyString::CALC_OPEN_FREQ_SPECTRUM:
//    new_calculation = new CCalcOpenFreqSpecFile();
//    break;
//  case KeyString::CALC_MASK_FILE_MS:
//    new_calculation = new CCalcMaskFileMs();
//    break;
//  case KeyString::CALC_EFFEC_NUC_TCGA_FREQS:
//    new_calculation = new CCalcEffecNucAndTCGAFreqs();
//    break;
//  case KeyString::CALC_LENGTHAMNG:
//    new_calculation = new CCalcLengthamngAndCalcs();
//    break;
//  case KeyString::CALC_X:
//    new_calculation = new CCalcX();
//    break;
//  case KeyString::CALC_Y:
//    new_calculation = new CCalcY();
//    break;
//  case KeyString::CALC_Z:
//    new_calculation = new CCalcZ();
//    break;
//  case KeyString::CALC_ARRAY_OPE_X:
//    new_calculation = new CCalcArrayOpeX();
//    break;
//  case KeyString::CALC_MSTATSPOP_OUTPUT:
//    new_calculation = new CCalcMstatspopOutput();
//    break;
//  case KeyString::CALC_ARRAY_SUM_ALL:
//    new_calculation = new CCalcArraySumAll();
//    break;
//  case KeyString::CALC_DUPLICATE_POPULATIONS:
//    new_calculation = new CCalcDuplicatePopulations();
//    break;
//  case KeyString::CALC_RANDOMIZE:
//    new_calculation = new CCalcRandomize();
//    break;
//  case KeyString::CALC_MSTATSPOP:
//    new_calculation = new CCalcMstatspop();
//    break;
//  case KeyString::CALC_GCCONTENT:
//    new_calculation = new CCalcGCContent();
//    break;
//
//
//  default:
//    new_calculation = NULL;
//  }

  return new_calculation;
}

ICalculation *CCalcFactory::GetCalculation(std::string type) {
  ICalculation *new_calculation = NULL;

  bool calc_found = false;
  std::map<KeyString, ICalculation *>::iterator it;
  for (it = data_map_.begin(); ((it != data_map_.end()) &&
                                (!calc_found)); ++it) {
    if (it->second->type() == type) {
      calc_found = true;
      new_calculation = GetCalculation(it->second->type_key());
    }
  }

  return new_calculation;
}

std::string CCalcFactory::GetCalcsInformation(CManager *manager) {
  std::string ret = "{";
  ret += "\"calculations\":[";

  std::string name, field;

  std::map<KeyString, ICalculation *>::iterator it;
  for (it = data_map_.begin(); it != data_map_.end(); ++it) {
    if ((it->second->name() != "") && (it->second->name().substr(0, 5) == "calc_")) {
      if (it != data_map_.begin()) {
        ret += ",";
      }
      ret += "{";
      name = it->second->name();
      CStringTools::Replace(name, STR(RESERVED_DATA_NAME_PREFIX), "");

      ret += "\"id\":\"" + name + "\",";
           
      field = STR2(it->second->brief_description());
      ret += "\"brief_description\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";
      
      field = STR2(it->second->description());
      ret += "\"description\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

      field = STR2(it->second->author());
      ret += "\"authors\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

      field = STR2(it->second->copyright());
      ret += "\"copyright\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";
      
      field = STR2(it->second->citations());
      ret += "\"citations\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

      field = STR2(it->second->see_also());
      ret += "\"see_also\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";      
      
      it->second->set_manager(manager);

      ret += it->second->GetCalcInformation();
      ret += "}";
    }
  }

  ret += "]";
  ret += "}";

  std::cout << "\n\n";
  std::cout << ret;
  std::cout << "\n\n";
  return ret;
}

std::string CCalcFactory::GetCalculationsList(void) {
  std::string list;
  bool first_calc = true;

  std::map<KeyString, ICalculation *>::iterator it;
  for (it = data_map_.begin();
      it != data_map_.end();
      ++it) {
    if ((it->second->name() != "") && (it->second->name().substr(0, 5) == "calc_")) {
      if (!first_calc) {
        list += "," + STR(SPACE);
      }
      list += it->second->name();
      first_calc = false;
    }
  }

  return list;
}  

