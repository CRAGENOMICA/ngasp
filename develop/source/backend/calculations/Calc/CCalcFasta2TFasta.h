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
 *  \brief     CCalcFasta2TFasta.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Dec 21, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_CALCULATIONS_CALC_CCALCFASTA2TFASTA_H_
#define BACKEND_SRC_CALCULATIONS_CALC_CCALCFASTA2TFASTA_H_

#include <string>
#include <iostream>

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataFasta.h"
#include "../../data_manager/Data/CDataTFasta.h"
#include "../../data_manager/Data/CDataWeightsFile.h"
#include "../../data_manager/Data/CDataGTF.h"
#include "../../data_manager/Data/CDataBed.h"
#include "../../data_manager/Data/CDataBoolean.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataStdStringVector.h"

class CCalcFasta2TFasta : public ICalculation {
 private:
  // Inputs
  CDataFasta *fasta_file;
  CDataGTF *gtf_annotation_file;
  CDataBed *bed_masking_file;
  CDataStdString *samples_order;
  CDataBoolean *compress_output;
  CDataStdStringVector *scaffold_names;

  CDataBoolean *keep_intermediate_results;
            
  // Outputs
  CDataTFasta *tfasta_file;
  CDataWeightsFile *weights_file;
  
 public:
  CCalcFasta2TFasta();
  virtual ~CCalcFasta2TFasta();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcFasta2TFasta(); /*clone*/  }
  
 private:
  void Transform(void);
  inline void FillColumnWithN(uintmax_t *x,
                        uintmax_t *y,
                        uintmax_t *max_bases_x_record,
                        char *output_data_pointer,
                        uintmax_t *width_with_eol) {
    char *tfasta = NULL;

    if (*x != 0) {
      while (*x < *max_bases_x_record) {
        // Fill empty positions with 'N'
        tfasta = output_data_pointer + ((*width_with_eol) * (*x)) + *y;
        *tfasta = 'N';
        *x = *x + 1;
      }
      
      *x = 0;
      *y = *y + 1;
    }
  }  
};

#endif  // BACKEND_SRC_CALCULATIONS_CALC_CCALCFASTA2TFASTA_H_
