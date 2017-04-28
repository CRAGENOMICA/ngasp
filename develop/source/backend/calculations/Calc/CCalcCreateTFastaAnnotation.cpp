/*
 * ngasp, a computational solution for performing next generation analysis of 
 * sequence polymorphisms using NGS data.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
 * Centre for Research in Agricultural Genomics.
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
 *  \brief     CCalcCreateTFastaAnnotation.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcCreateTFastaAnnotation.h"

#include <string>
#include <iostream>

#include "../../language/CStringTable.h"
#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../util/CFile.h"
#include "../../util/CStringTools.h"


CCalcCreateTFastaAnnotation::CCalcCreateTFastaAnnotation()
: ICalculation(KeyString::CALC_CREATETFASTAANNOTATION,
               KeyString::CALC_CREATETFASTAANNOTATION_BRIEF_DESC,
               KeyString::CALC_CREATETFASTAANNOTATION_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(input_tfasta_file_name,                                      // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(input_gff_file_name,                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(annotation,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(genetic_code,                                                // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(output_tfa_file_name,                                        // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)
  
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcCreateTFastaAnnotation::~CCalcCreateTFastaAnnotation() {
}

void CCalcCreateTFastaAnnotation::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(input_tfasta_file_name)
    DM_INPUT(input_gff_file_name)
    DM_INPUT(annotation)
    DM_INPUT(genetic_code)
    DM_INPUT(output_tfa_file_name)
  DM_GET_OUTPUTS
  DM_END
}

void CCalcCreateTFastaAnnotation::Calculate(bool dry_run) {


  CGFFFile            gff_file;
  CTFastaInfo         tfasta_info;
  CTFastaAnnotation   tfa_file;
  
  // ===========================================================================
  // Open the GFF file
  // ===========================================================================
  if (gff_file.Open(input_gff_file_name->value())) {
    
    // =========================================================================
    // Get the TFasta file information
    // =========================================================================
    if (tfasta_info.GetFileInformation(input_tfasta_file_name->value())) {
      
    // =========================================================================
    // Open the TFasta file as a memory mapped file for reading its data
    // =========================================================================
      if (tfasta_info.OpenForRead(input_tfasta_file_name->value())) {

      // =========================================================================
      // Create for writing the TFasta Annotation file as a memory mapped file
      // =========================================================================
        unsigned long int     output_rows      = tfasta_info.rows();                     // Added unsigned <-----
        unsigned long int     output_columns   = 2;                                      // Added unsigned <-----
        int         output_cell_size = 6;
        std::string column_separator = "|";
        
        unsigned long int required_file_space = 
                      tfa_file.CalculateTableSpace(output_rows,
                                                   output_columns,
                                                   output_cell_size,
                                                   column_separator);
  
        if (tfa_file.OpenForWrite(output_tfa_file_name->value(),
                                  required_file_space)) {

          float i = 0.932738463256;
          
          for (unsigned long int row = 0; row < output_rows; row++) {
            for (unsigned long int col = 0; col < output_columns; col++) {

              if (tfa_file.WriteCell(std::to_string(i),
                                 row,
                                 col,
                                 output_columns,
                                 output_cell_size,
                                 column_separator) == false) {
                std::cout << "out of range" << std::endl;
              }
              i++;
            }
          }
          
          // Loop GFF file
          for(std::list<CGFFRecord *>::iterator it = gff_file.records()->begin();
            it != gff_file.records()->end();
            it++) {
            
          }
          
          // Loop TFasta
          const char *end_tfasta = tfasta_info.GetLastDataPosition();
          for (const char *tfasta = tfasta_info.GetFirstDataPosition();
               tfasta < end_tfasta;
               tfasta++) {
//            if (*tfasta == '\n') {
//              std::cout << "EOL" << std::endl;
//            }
          }

//          // Loop TFasta Annotation
//          char *tfa = tfa_file.GetFirstReservedPosition();
//          const char *end_tfa = tfa_file.GetLastReservedPosition();
//          tfa_file.Write("hello", &tfa, end_tfa);
//          tfa_file.Write(std::to_string(10), &tfa, end_tfa);
//          tfa_file.Close(tfa, end_tfa);
          
          tfa_file.Close();

          std::cout << tfasta_info << std::endl;
          std::cout << gff_file << std::endl;
          std::cout << tfa_file << std::endl;
        }
      } else {
        ERROR_MSG << STR(FILE_OPEN_ERROR)
                  << input_tfasta_file_name->value()
                  END_MSG;
      }
    } else {
      ERROR_MSG << STR(FILE_OPEN_ERROR)
                << input_tfasta_file_name->value()
                END_MSG;
    }
  } else {
    ERROR_MSG << STR(FILE_OPEN_ERROR)
              << input_gff_file_name->value()
              END_MSG;
  }
} 

void CCalcCreateTFastaAnnotation::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
