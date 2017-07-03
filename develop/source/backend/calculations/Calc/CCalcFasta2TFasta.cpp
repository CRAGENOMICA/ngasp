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
 *  \brief     CCalcFasta2TFasta.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Dec 21, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcFasta2TFasta.h"

#include <string>
#include <list>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

#include "../../language/CStringTable.h"
#include "../../util/CFile.h"
#include "CCalcExec.h"

#include "../../data_manager/common/CDataSequenceIndex.h"
#include "../../data_manager/common/CFastaInfo.h"
#include "../../data_manager/common/CTFastaInfo.h"

#include "../../data_manager/Data/CDataFasta.h"
#include "../../data_manager/Data/CDataTFasta.h"
#include "../../data_manager/Data/CDataGTF.h"
#include "../../data_manager/Data/CDataBed.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../util/CFile.h"


CCalcFasta2TFasta::CCalcFasta2TFasta()
: ICalculation(KeyString::CALC_FASTA2TFASTA,
               KeyString::CALC_FASTA2TFASTA_BRIEF_DESC,
               KeyString::CALC_FASTA2TFASTA_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(fasta_file,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_FASTA2TFASTA_INPUT,                                     // Short Name
                   CALC_FASTA2TFASTA_INPUT_LONG,                                // Long Name
                   CALC_FASTA2TFASTA_INPUT_DESC,                                // Description
                   CALC_FASTA2TFASTA_INPUT_SAMP,                                // Example
                   CALC_FASTA2TFASTA_INPUT_ONLY,                                // Use only if
                   CALC_FASTA2TFASTA_INPUT_DEFV,                                // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)

    SET_INPUT_INFO(gtf_annotation_file,                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_FASTA2TFASTA_GTF,                                       // Short Name
                   CALC_FASTA2TFASTA_GTF_LONG,                                  // Long Name
                   CALC_FASTA2TFASTA_GTF_DESC,                                  // Description
                   CALC_FASTA2TFASTA_GTF_SAMP,                                  // Example
                   CALC_FASTA2TFASTA_GTF_ONLY,                                  // Use only if
                   CALC_FASTA2TFASTA_GTF_DEFV,                                  // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)
  
    SET_INPUT_INFO(bed_masking_file,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_FASTA2TFASTA_BED,                                       // Short Name
                   CALC_FASTA2TFASTA_BED_LONG,                                  // Long Name
                   CALC_FASTA2TFASTA_BED_DESC,                                  // Description
                   CALC_FASTA2TFASTA_BED_SAMP,                                  // Example
                   CALC_FASTA2TFASTA_BED_ONLY,                                  // Use only if
                   CALC_FASTA2TFASTA_BED_DEFV,                                  // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)

    SET_INPUT_INFO(samples_order,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_FASTA2TFASTA_SAMPLES_ORDER,                                       // Short Name
                   CALC_FASTA2TFASTA_SAMPLES_ORDER_LONG,                                  // Long Name
                   CALC_FASTA2TFASTA_SAMPLES_ORDER_DESC,                                  // Description
                   CALC_FASTA2TFASTA_SAMPLES_ORDER_SAMP,                                  // Example
                   CALC_FASTA2TFASTA_SAMPLES_ORDER_ONLY,                                  // Use only if
                   CALC_FASTA2TFASTA_SAMPLES_ORDER_DEFV,                                  // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)

    SET_INPUT_INFO(compress_output,                                            // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_FASTA2TFASTA_COMPRESS_OUT,                                       // Short Name
                   CALC_FASTA2TFASTA_COMPRESS_OUT_LONG,                                  // Long Name
                   CALC_FASTA2TFASTA_COMPRESS_OUT_DESC,                                  // Description
                   CALC_FASTA2TFASTA_COMPRESS_OUT_SAMP,                                  // Example
                   CALC_FASTA2TFASTA_COMPRESS_OUT_ONLY,                                  // Use only if
                   CALC_FASTA2TFASTA_COMPRESS_OUT_DEFV,                                  // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required)

    SET_INPUT_INFO(scaffold_names,                                               // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_FASTA2TFASTA_SCAFFOLD_NAME,                             // Short Name
                   CALC_FASTA2TFASTA_SCAFFOLD_NAME_LONG,                        // Long Name
                   CALC_FASTA2TFASTA_SCAFFOLD_NAME_DESC,                        // Description
                   CALC_FASTA2TFASTA_SCAFFOLD_NAME_EXAMPLE,                     // Example
                   UNDEFINED_STRING,                                            // Use only if
                   CALC_FASTA2TFASTA_SCAFFOLD_NAME_DEF_VAL,                     // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)


    SET_INPUT_INFO(keep_intermediate_results,                                   // Variable
                   UNDEFINED_STRING,                                            // Group
                   CCALC_ALL_KEEP_INTERMEDIATE_RESULTS,                         // Short Name
                   CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_LONG,                    // Long Name
                   CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_DESC,                    // Description
                   CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_SAMP,                    // Example
                   CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_ONLY,                    // Use only if
                   CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_DEFV,                    // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_optional)                                            // Required
  
  SET_OUTPUT_INFO(tfasta_file,                                                  // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_FASTA2TFASTA_OUTPUT,                                    // Short Name
                   CALC_FASTA2TFASTA_OUTPUT_LONG,                               // Long Name
                   CALC_FASTA2TFASTA_OUTPUT_DESC,                               // Description
                   CALC_FASTA2TFASTA_OUTPUT_SAMP,                               // Example
                   CALC_FASTA2TFASTA_OUTPUT_ONLY,                               // Use only if
                   CALC_FASTA2TFASTA_OUTPUT_DEFV,                               // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)

  SET_OUTPUT_INFO(weights_file,                                                 // Variable
                   UNDEFINED_STRING,                                            // Group
                   CALC_FASTA2TFASTA_WEIGHTS,                                   // Short Name
                   CALC_FASTA2TFASTA_WEIGHTS_LONG,                              // Long Name
                   CALC_FASTA2TFASTA_WEIGHTS_DESC,                              // Description
                   CALC_FASTA2TFASTA_WEIGHTS_SAMP,                              // Example
                   CALC_FASTA2TFASTA_WEIGHTS_ONLY,                              // Use only if
                   CALC_FASTA2TFASTA_WEIGHTS_DEFV,                              // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required)

  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcFasta2TFasta::~CCalcFasta2TFasta() {
}

void CCalcFasta2TFasta::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(fasta_file)
    DM_INPUT(gtf_annotation_file)
    DM_INPUT(bed_masking_file)
    DM_INPUT(samples_order)
    DM_INPUT(compress_output)
    DM_INPUT(scaffold_names)

    DM_INPUT(keep_intermediate_results)
  DM_GET_OUTPUTS
    DM_OUTPUT(tfasta_file)
    DM_OUTPUT(weights_file)
  DM_END
  
  if (tfasta_file->value() == "") {
      tfasta_file->set_value(CFile::GetPathFileNameWithoutExtension(fasta_file->value()) + ".tfa" + (compress_output->value()?".gz":""));
  }  
  
  weights_file->set_value(tfasta_file->value() + "_WEIGHTS.txt");
  
  
  if (keep_intermediate_results->value()) {
    DM_ITERATION_NUMBER(iteration_number)
    DM_ITERATION_VALUE(iteration_value)
    tfasta_file->set_value(CFile::ConcatenateIterationToFilePathName(tfasta_file->value(),
                           iteration_number->value(),
                           CFile::GetFileNameWithoutExtension(iteration_value->value())));  
  }
}

void CCalcFasta2TFasta::Calculate(bool dry_run) {
  if (dry_run == true) {
    return;
  }
  
  /// CREATE CALC AND DATAS FOR THE CALCULATION
 
  CCalcExec *calc_execute = NULL;
  DM_NEW_CALC(calc_execute)
  
  CDataStdString *the_command = NULL;
  DM_NEW_DATA(the_command)
 

  std::string command = STR(FASTA_CONVERTER_BINARY) + " -F f -f tfasta -i " + fasta_file->value() + " -f t -o " + tfasta_file->value();


  if (!gtf_annotation_file->auto_created()) {
    command += " -g " + gtf_annotation_file->value() + "  silent Nuclear_Universal";
  }

  if (!bed_masking_file->auto_created())     {
    command += " -m " + bed_masking_file->value();
  }

  if (!samples_order->auto_created())     {
    command += " -O " + samples_order->value();
  }

  if (!scaffold_names->auto_created())     {
    command += " -n ";
    command += scaffold_names->GetDataString();
  }


  the_command->set_value(command);

  
  // the_command->add(" > fasta_converter.log");
  
  CDataStdString *the_working_directory = NULL;
  DM_NEW_DATA(the_working_directory)
  the_working_directory->set_value(STR(BINARY_PATH_INSIDE_DOCKER));
    
  CDataStdString *the_type = NULL;
  DM_NEW_DATA(the_type)
  the_type->set_value(STR(EXEC_TYPE_SYS));
    
  CDataInt *the_result = (CDataInt *)manager()->data_manager()->GetDataByName(ROOT_PARENT, STR(RESULT));  // This is a global variable. So, its parent is ROOT_PARENT.
  
  NORMAL_MSG << "Fasta2TFasta command: "
             << the_command->value()
             END_MSG;
  
  /// ==========================================================================
  /// EXECUTE EXTERNAL APPLICATION OR SYSTEM COMMAND
  /// ==========================================================================
  calc_execute->SetInput(the_command);
  calc_execute->SetInput(the_working_directory);
  calc_execute->SetInput(the_type);
  calc_execute->SetOutput(the_result);
  calc_execute->Prepare();
  calc_execute->Calculate(dry_run);
  calc_execute->Finalize();
  /// ==========================================================================

  /// REMOVE CALC AND "DATAS" CREATED ONLY FOR THIS CALCULATION
  
  DM_DEL_CALC(calc_execute)
  DM_DEL_DATA(the_command)
  DM_DEL_DATA(the_working_directory)
  DM_DEL_DATA(the_type)
}

void CCalcFasta2TFasta::Transform(void) {
  // ***************************************************************************
  // THIS FUNCTION WORKS OK DESPITE IT IS COMMENTED
  // ***************************************************************************
  /*
  // ===========================================================================
  // Open the fasta file as a memory mapped file and get its information.
  // ===========================================================================
  CFastaInfo fasta_info;
  
  if (fasta_info.GetFileInformation(input_file_name->value())) {
  
    // =========================================================================
    // Let's go to create the TFasta memory mapped file with the input file 
    // information.
    // =========================================================================
    
    CTFastaInfo tfasta_info;
    if (tfasta_info.OpenForWrite(output_file_name->value(), &fasta_info)) {
      // Get a pointer to the start of the output tfasta file.
      char *tfasta = tfasta_info.GetFirstReservedPosition();

      // First, copy the descriptions string to the first row of the tfasta:
      memcpy(tfasta,
             fasta_info.descriptions().c_str(),
             fasta_info.descriptions().length());

      // =======================================================================
      // Loop for creating transposing the fasta data to the t-fasta
      // The t-fasta will be accessed sequentially from the first position to
      // the last. And for every position we will find the base in the fasta
      // file.
      // =======================================================================

      uintmax_t current_sequence_number = 0;
      const char *fasta = NULL;
      std::list<CDataSequenceIndex *>::iterator it =
                                          fasta_info.sequences_index()->begin();
      uintmax_t num_sequences = fasta_info.GetNumSequences();

      // Start the loop moving the tfasta pointer to the start of the data 
      // (after the descriptions row).
      for(tfasta = tfasta_info.GetFirstReservedPosition() + 
                   fasta_info.descriptions().length();
          tfasta < tfasta_info.GetLastReservedPosition();
          tfasta++) {

        if (current_sequence_number < num_sequences) {
          // The current output tfasta position is not the last base of the
          // output row.

          // Get the base from the input fasta file.
          if (((*it)->first_base_position() + (*it)->last_index()) <= 
              ((*it)->last_base_position())) {
            // The base can be gotten from the input file (because it exists)
            fasta = fasta_info.GetChar((*it)->first_base_position() +
                               (*it)->last_index());

            // If the base is an EOL, let's pass through it and get the the
            // valid base that has to be after the EOL (or more than one EOL).
            while(*fasta == '\n') {
              (*it)->inc_last_index();
              
              fasta = fasta_info.GetChar((*it)->first_base_position() +
                                         (*it)->last_index());
            }

            // We have a valid base. So let's write it to the output file.
            *tfasta = *fasta;

            // Move the sequence index one char.
            (*it)->inc_last_index();
          } else {
            // If the base cannot be gotten (because it does not exist),
            // a missing will be written to the output tfasta file.
            *tfasta = 'N';
          }

          // Every tfasta position comes from a different sequence number.
          // Let's move the sequence number.
          current_sequence_number++;

          // And let's get the next sequence index information.
          it++;
        } else {
          // The end of an output row has been reached.
          // Let's write the EOL.
          *tfasta = '\n';

          // Restart the counter to the first sequence number.
          current_sequence_number = 0;

          // Get the first sequence.
          it = fasta_info.sequences_index()->begin();
        }
      }

      // Close the output tfasta file so that all data is stored on file.
      tfasta_info.Close();
    }

    // Show the results.
    std::cout << fasta_info;
    std::cout << tfasta_info;
  }
  else {
    ERROR_MSG << STR(FILE_OPEN_ERROR)
              << fasta_info.file_name()
              END_MSG;    
  }
  */
} 

void CCalcFasta2TFasta::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
