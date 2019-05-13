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
 *  \brief     CStringTable.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Mar 31, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CStringTable.h"


CStringTable * CStringTable::m_pInstance = NULL;

CStringTable * CStringTable::Instance() {
  if (!m_pInstance) {
    m_pInstance = new CStringTable;
  }
  return m_pInstance;
}

void CStringTable::ResetInstance() {
  /// It works even if the pointer is NULL (does nothing then)
  /// so GetInstance will still work.
  delete m_pInstance;
  m_pInstance = NULL;
}

CStringTable::CStringTable() : IStringTable() {
  //@{
  /// ==========================================================================
  /// This CStringTable Control Constants
  /// ==========================================================================
  strings_[ENGLISH_COL][UNDEFINED_STRING]                                       = "";
  //@}
  //@{
  /// ==========================================================================
  /// Application Information
  /// ==========================================================================
  strings_[ENGLISH_COL][NGASP_APP_NAME]                                         = "ngaSP";
  strings_[ENGLISH_COL][NGASP_APP_EXECUTABLE_NAME]                              = "ngasp";
  strings_[ENGLISH_COL][NGASP_APP_VERSION]                                      = EXTERN_VERSION_STRING;
  strings_[ENGLISH_COL][NGASP_SHORT_DESC]                                       = "The Next Generation Analysis S.P.";
  strings_[ENGLISH_COL][NGASP_COPYRIGHT]                                        = "Copyright and License";
  strings_[ENGLISH_COL][NGASP_COPYRIGHT_DESC]                                   = "CRAG 2015.";
  //@} 
  //@{
  /// ==========================================================================
  /// List of Authors
  /// ==========================================================================
  strings_[ENGLISH_COL][NGASP_AUTHORS]                                          = "Sebastian E. Ramos-Onsins, Joan Jené, Luca Ferretti, Emanuele Raineri, Giacomo Marmorini, William Burgos and Gonzalo Vera.";
  strings_[ENGLISH_COL][GVCF2TFASTA_AUTHORS]                                    = "Jordi Leno.";
  strings_[ENGLISH_COL][MSTATSPOP_AUTHOR]                                       = "Sebastian E. Ramos-Onsins, Joan Jené, Luca Ferretti, Emanuele Raineri, Giacomo Marmorini, William Burgos and Gonzalo Vera.";
  strings_[ENGLISH_COL][GENERIC_COPYRIGHT]                                      = "Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez";
  strings_[ENGLISH_COL][GENERIC_CITATIONS]                                      = "";
  //@}
  //@{
  /// ==========================================================================
  /// EXTERNAL TOOLS
  /// ==========================================================================
  strings_[ENGLISH_COL][BINARY_PATH_INSIDE_DOCKER]                              = "/develop/webapp/bin/";
  strings_[ENGLISH_COL][SNP_CALLER_BINARY]                                      = "sh ghcaller.sh";
  strings_[ENGLISH_COL][MSTATSPOP_BINARY]                                       = "./mstatspop";
  strings_[ENGLISH_COL][FASTA_CONVERTER_BINARY]                                 = "./fastaconvtr";
  strings_[ENGLISH_COL][COLLECT_DATA_COLUMNS_BINARY]                            = "perl collect_data_columns.pl";
  strings_[ENGLISH_COL][CONCATENATE_FILES_BINARY]                               = "cat";
  strings_[ENGLISH_COL][NPSTAT_BINARY]                                          = "./npstat";
  strings_[ENGLISH_COL][VCF2GFASTA_BINARY]                                      = "./vcf2gfasta";
  
  //@}
  //@{
  /// ==========================================================================
  /// MSTATSPOP Information
  /// ==========================================================================
  strings_[ENGLISH_COL][MSTATSPOP_APP_NAME]                                     = "mstatspop";
  strings_[ENGLISH_COL][MSTATSPOP_BRIEF_DESC]                                   = "Variability AnalysIs of multiple populations: Calculation and estimation of statistics and neutrality tests.";
  strings_[ENGLISH_COL][MSTATSPOP_SYNOPSIS]                                     = "-f format -i file -o output -N populations [-G (0/1)] [-u (0/1)] [-T file] [-a file] [-n file] [-P values lines] [-w size [-O nsam samples] [-t permutations] [-s value] [-z size] [-Y length] [-W file] [-E file]] [-l length [-O nsam samples] [-t permutations] [-s value] [-r iterations] [-m file] [-v value] [-F (0/1)] [-q value]] [[-p (1/2)] [-g file] [-c (max/min/first/long)]] [-h]";
  strings_[ENGLISH_COL][MSTATSPOP_DESC]                                         = "\nmstatspop v.0.1beta (20160922)\n"
                                                                                  "Sebastian E. Ramos-Onsins, Luca Ferretti, Emanuele Raineri, Giacomo Marmorini, William Burgos and Gonzalo Vera\n"
                                                                                  "Variability Analyses of multiple populations: Calculation and estimation of statistics and neutrality tests.\n";
  strings_[ENGLISH_COL][MSTATSPOP_COPYRIGHT]                                    = "";
  strings_[ENGLISH_COL][MSTATSPOP_SEE_ALSO]                                     = "https://bioinformatics.cragenomica.es/numgenomics/people/sebas/software/software.html";

  strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_TITLE]                                 = "\n\n\n"
                                                                                  "****************************************************************************\n"
                                                                                  "*  NUCLEOTIDE VARIABILITY, NEUTRALITY TEST AND POPULATION DIFFERENTIATION  *\n"
                                                                                  "****************************************************************************\n";
  //@}
  //@{
  /// ==========================================================================
  /// Presentation messages when executed in STDIN mode
  /// ==========================================================================
  strings_[ENGLISH_COL][INTERACTIVE_MODE_CHAR]                                  = "-";
  strings_[ENGLISH_COL][PRESENTS_WELCOME]                                       = "Welcome to ngaSP.\n\n";
  strings_[ENGLISH_COL][PRESENTS_CONNECTED_TO]                                  = "Connected: ";
  strings_[ENGLISH_COL][PRESENTS_CONNECTION_TO]                                 = "Connection to ";
  strings_[ENGLISH_COL][PRESENTS_CONNECTION_CLOSED]                             = " closed.";
  strings_[ENGLISH_COL][PROMPT]                                                 = "ngaSP> ";
  //@}
  //@{
  /// ==========================================================================
  /// General Options
  /// ==========================================================================
  strings_[ENGLISH_COL][GOS_HELP_SHORT]                                         = "h";
  strings_[ENGLISH_COL][GOS_HELP_LONG]                                          = "help";
  strings_[ENGLISH_COL][GOS_HELP_DESC]                                          = "Show help";
  

  strings_[ENGLISH_COL][GOS_VERSION_SHORT]                                      = "V";
  strings_[ENGLISH_COL][GOS_VERSION_LONG]                                       = "version";
  strings_[ENGLISH_COL][GOS_VERSION_DESC]                                       = "Show version information";

  strings_[ENGLISH_COL][GOS_VERBOSE_SHORT]                                      = "v";
  strings_[ENGLISH_COL][GOS_VERBOSE_LONG]                                       = "verbose";
  strings_[ENGLISH_COL][GOS_VERBOSE_DESC]                                       = "Increase verbose level";

  strings_[ENGLISH_COL][GOS_DRYRUN_SHORT]                                       = "x";
  strings_[ENGLISH_COL][GOS_DRYRUN_LONG]                                        = "dry-run";
  strings_[ENGLISH_COL][GOS_DRYRUN_DESC]                                        = "Examines the source code one step at a time and determines what it will do when run.";
  //@}
  //@{
  /// ==========================================================================
  /// Datas
  /// ==========================================================================
  strings_[ENGLISH_COL][_DATA_FIRST]                                            = "";  // *************************************

  strings_[ENGLISH_COL][DATA_BOOLEAN]                                           = "bool";
  strings_[ENGLISH_COL][DATA_BOOLEAN_VECTOR]                                    = "bool_vector";
  strings_[ENGLISH_COL][DATA_BOOLEAN_MATRIX]                                    = "bool_matrix";
  strings_[ENGLISH_COL][DATA_BOOLEAN_CUBE]                                      = "bool_cube";

  strings_[ENGLISH_COL][DATA_CHAR]                                              = "char";
  strings_[ENGLISH_COL][DATA_CHAR_VECTOR]                                       = "char_vector";
  strings_[ENGLISH_COL][DATA_CHAR_MATRIX]                                       = "char_matrix";
  strings_[ENGLISH_COL][DATA_CHAR_CUBE]                                         = "char_cube";

  strings_[ENGLISH_COL][DATA_INT]                                               = "int";
  strings_[ENGLISH_COL][DATA_INT_VECTOR]                                        = "int_vector";
  strings_[ENGLISH_COL][DATA_INT_MATRIX]                                        = "int_matrix";
  strings_[ENGLISH_COL][DATA_INT_CUBE]                                          = "int_cube";

  strings_[ENGLISH_COL][DATA_INT64]                                             = "int64";
  strings_[ENGLISH_COL][DATA_INT64_VECTOR]                                      = "int64_vector";
  strings_[ENGLISH_COL][DATA_INT64_MATRIX]                                      = "int64_matrix";
  strings_[ENGLISH_COL][DATA_INT64_CUBE]                                        = "int64_cube";

  strings_[ENGLISH_COL][DATA_DOUBLE]                                            = "double";
  strings_[ENGLISH_COL][DATA_DOUBLE_VECTOR]                                     = "double_vector";
  strings_[ENGLISH_COL][DATA_DOUBLE_MATRIX]                                     = "double_matrix";
  strings_[ENGLISH_COL][DATA_DOUBLE_CUBE]                                       = "double_cube";

  strings_[ENGLISH_COL][DATA_FLOAT]                                             = "float";
  strings_[ENGLISH_COL][DATA_FLOAT_VECTOR]                                      = "float_vector";
  strings_[ENGLISH_COL][DATA_FLOAT_MATRIX]                                      = "float_matrix";
  strings_[ENGLISH_COL][DATA_FLOAT_CUBE]                                        = "float_cube";

  strings_[ENGLISH_COL][DATA_STD_STRING]                                        = "string";
  strings_[ENGLISH_COL][DATA_STD_STRING_VECTOR]                                 = "string_vector";
  strings_[ENGLISH_COL][DATA_STD_STRING_MATRIX]                                 = "string_matrix";

  strings_[ENGLISH_COL][DATA_STRING_SET]                                        = "string_set";

                                                                                // All Data Files must end with "_file": (in order to be recognized by the CM as files when registering them)
  strings_[ENGLISH_COL][DATA_SAM]                                               = "sam_file";
  strings_[ENGLISH_COL][DATA_BAM]                                               = "bam_file";
  strings_[ENGLISH_COL][DATA_BAM_INDEX]                                         = "bam_index_file";
  strings_[ENGLISH_COL][DATA_BCF]                                               = "bcf_file";
  strings_[ENGLISH_COL][DATA_VCF]                                               = "vcf_file";
  strings_[ENGLISH_COL][DATA_MPILEUP]                                           = "mpileup_file";
  strings_[ENGLISH_COL][DATA_FASTA]                                             = "fasta_file";
  strings_[ENGLISH_COL][DATA_TEXT_FILE]                                         = "text_file";
  strings_[ENGLISH_COL][DATA_TFASTA]                                            = "t-fasta_file";
  strings_[ENGLISH_COL][DATA_GTF]                                               = "gtf_file";
  strings_[ENGLISH_COL][DATA_BED]                                               = "bed_file";
  strings_[ENGLISH_COL][DATA_GFF]                                               = "gff_file";
  strings_[ENGLISH_COL][DATA_SNP]                                               = "snp_file";
  strings_[ENGLISH_COL][DATA_GFASTA]                                            = "g_fasta_file";
  strings_[ENGLISH_COL][DATA_WEIGHTS]                                           = "weights_file";

      
  strings_[ENGLISH_COL][_DATA_LAST]                                             = "";  // *************************************
  //@}
  //@{
  /// ==========================================================================
  /// Data Manager
  /// ==========================================================================
  /// Variable naming

  strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX]                              = "$";
  strings_[ENGLISH_COL][READ_ONLY_PREFIX]                                       = "(RO)";
  strings_[ENGLISH_COL][CHILD_SEPARATOR]                                        = ".";
  strings_[ENGLISH_COL][VARIABLE_ID]                                            = "$";
  strings_[ENGLISH_COL][VARIABLE_SEPARATOR]                                     = ".";
  strings_[ENGLISH_COL][VARIABLE_POS_START]                                     = "[";
  strings_[ENGLISH_COL][VARIABLE_POS_END]                                       = "]";
  strings_[ENGLISH_COL][VARIABLE_NAME_VALID_1ST]                                = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_.";
  strings_[ENGLISH_COL][VARIABLE_NAME_VALID_CHARS]                              = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789.[,]";

  // Variable parts

  strings_[ENGLISH_COL][VARIABLE_DATA]                                          = "data";
  strings_[ENGLISH_COL][VARIABLE_VALUE]                                         = "value";
  strings_[ENGLISH_COL][VARIABLE_TABLES]                                        = "tables";
  strings_[ENGLISH_COL][VARIABLE_REGS]                                          = "regs";
  strings_[ENGLISH_COL][VARIABLE_LENGTH]                                        = "reg_length";

  /// Data Values

  strings_[ENGLISH_COL][DEFAULT_CHAR]                                           = "\x0";
  strings_[ENGLISH_COL][TRUE_STRING_VALUE]                                      = "TRUE";
  strings_[ENGLISH_COL][FALSE_STRING_VALUE]                                     = "FALSE";

  /// Fixed Data Names

  strings_[ENGLISH_COL][SEED]                                                   = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "seed";
  strings_[ENGLISH_COL][IDUM]                                                   = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "idum";
  strings_[ENGLISH_COL][ALL_COMMAND_LINE]                                       = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "all_command_line";
  strings_[ENGLISH_COL][RANDOMIZE_VALUE]                                        = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "randomize_value";
  strings_[ENGLISH_COL][OUTPUT_FILE]                                            = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "output_file";
  strings_[ENGLISH_COL][OUTPUT]                                                 = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "output";
  strings_[ENGLISH_COL][PRECISION]                                              = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "precision";
  strings_[ENGLISH_COL][TABLE_COL_WIDTH]                                        = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "table_col_width";
  strings_[ENGLISH_COL][ENCODING]                                               = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "encoding";
  strings_[ENGLISH_COL][RESULT]                                                 = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "result";
  strings_[ENGLISH_COL][ITERATION_NUMBER]                  = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "iteration_number";
  strings_[ENGLISH_COL][ITERATION_VALUE]                        = strings_[ENGLISH_COL][RESERVED_DATA_NAME_PREFIX] + "iteration_value";
  //@}
  //@{
  /// ==========================================================================
  /// Generic Errors
  /// ==========================================================================

  /// Related with variables

  strings_[ENGLISH_COL][VARIABLE_NOT_FOUND]                                     = "Variable not found...";
  strings_[ENGLISH_COL][OUT_OF_RANGE]                                           = "Out of range...";
  strings_[ENGLISH_COL][CAST_ERROR]                                             = "Cast error...";
  strings_[ENGLISH_COL][INT_TO_INT64]                                           = "Conversion from int to int64 error...";
  strings_[ENGLISH_COL][END_STRING]                                             = ". ";
  strings_[ENGLISH_COL][END_ERROR]                                              = "...";
  strings_[ENGLISH_COL][MEMORY_ALLOCATION_ERROR]                                = "Bad allocation caught: ";
  strings_[ENGLISH_COL][MEMORY_COPY_ERROR]                                      = "Bad allocation caught (on copy): ";

      
  /// Related with data

  strings_[ENGLISH_COL][DATA_NAME]                                              = "Data: ";
  strings_[ENGLISH_COL][DATA_EXPECTED]                                          = "Expected: ";
  strings_[ENGLISH_COL][BUT_FOUND]                                              = "But found: ";

  /// Related with commands

  strings_[ENGLISH_COL][COMMAND_NOT_FOUND]                                      = " command not found...";
  strings_[ENGLISH_COL][MISSING_OPTIONS]                                        = "Missing options...";
  strings_[ENGLISH_COL][MISSING_OPTION_ARGUMENTS]                               = "Missing option arguments...";
  strings_[ENGLISH_COL][UNKNOWN_OPTION]                                         = "Unknown option...";

  /// Related with calculations

  strings_[ENGLISH_COL][INPUTS_PARAM]                                           = "inputs";
  strings_[ENGLISH_COL][OUTPUTS_PARAM]                                          = "outputs";
  strings_[ENGLISH_COL][NULL_INPUT]                                             = "Trying to set NULL as input to calculation: ";
  strings_[ENGLISH_COL][CALCULATION_NOT_FOUND]                                  = "Calculation not found...";
  strings_[ENGLISH_COL][TOO_MANY_VALUES]                                        = "Too many values...";
  strings_[ENGLISH_COL][TOO_FEW_VALUES]                                         = "Too few values...";
  //@}
  //@{
  /// ==========================================================================
  /// Special characters that user can use when entering data
  /// ==========================================================================
  strings_[ENGLISH_COL][SEPARATORS]                                             = " ,;|"; // blank, "item", "row", "table" separators
  //@}
  //@{
  /// ==========================================================================
  /// Special characters that developer can use when coding their functions
  /// ==========================================================================
  strings_[ENGLISH_COL][SPACE]                                                  = " ";
  strings_[ENGLISH_COL][EOL]                                                    = "\n";
  strings_[ENGLISH_COL][TAB]                                                    = "\t";
  strings_[ENGLISH_COL][TAB3]                                                   = "   ";
  strings_[ENGLISH_COL][TAB6]                                                   = "      ";
  strings_[ENGLISH_COL][BLOCK]                                                  = ":";
  strings_[ENGLISH_COL][IDENTATION]                                             = "        ";
  strings_[ENGLISH_COL][PARAM]                                                  = "-";
  strings_[ENGLISH_COL][LINE_COMMENT_TAG]                                       = "#";
  strings_[ENGLISH_COL][QUOTE]                                                  = "'";
  strings_[ENGLISH_COL][DOUBLE_QUOTE]                                           = "\"";
  strings_[ENGLISH_COL][COMA]                                                   = ",";
  strings_[ENGLISH_COL][SEMI_COLON]                                             = ";";
  strings_[ENGLISH_COL][CONTINUE_LINE]                                          = "_"; // only one char
  
  strings_[ENGLISH_HTML][SPACE]                                                  = "&nbsp;";
  strings_[ENGLISH_HTML][EOL]                                                    = "<br />\n";
  strings_[ENGLISH_HTML][TAB]                                                    = "\t";
  strings_[ENGLISH_HTML][TAB3]                                                   = "&nbsp;&nbsp;&nbsp;";
  strings_[ENGLISH_HTML][TAB6]                                                   = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
  strings_[ENGLISH_HTML][IDENTATION]                                             = "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
  //@}
  //@{
  /// ==========================================================================
  /// Pipes
  /// ==========================================================================
  /// Communication Control Characters

  strings_[ENGLISH_COL][COMMAND_SEPARATOR]                                      = ">";
  strings_[ENGLISH_COL][PARAM_SEPARATOR]                                        = "<";

  /// File

  strings_[ENGLISH_COL][PRE_PIPE_NAME_TO_NGASP]                                 = "ngasp_to_";
  strings_[ENGLISH_COL][PRE_PIPE_NAME_FROM_NGASP]                               = "ngasp_from_";
  strings_[ENGLISH_COL][PRE_OUTPUT_NAME]                                        = "ngasp_";
  strings_[ENGLISH_COL][PIPE_EXTENSION]                                         = ".pipe";
  //@}
  //@{
  /// ==========================================================================
  /// Application Files Configuration
  /// ==========================================================================
  strings_[ENGLISH_COL][TEMP_FOLDER]                                            = "./tmp/";

  /// Mask Name
  
  strings_[ENGLISH_COL][DEFAULT_MASK_FILE_NAME_START]                           = "file";
  strings_[ENGLISH_COL][DEFAULT_MASK_FILE_NAME_END]                             = "_MASK.txt";
  strings_[ENGLISH_COL][MASK_POPS_MARK]                                         = "_npop";
  strings_[ENGLISH_COL][MASK_EXCLUDE_MIS_VARIANTS_MARK]                         = "_ExcludeMissingVariantsmhits";
  strings_[ENGLISH_COL][MASK_INCLUDE_MIS_VARIANTS_MARK]                         = "_IncludeMissingVariantsmhits";
  strings_[ENGLISH_COL][MASK_NO_OUTGROUP_PRESENCE_MARK]                         = "_NOoutg";
  strings_[ENGLISH_COL][MASK_OUTGROUP_PRESENCE_MARK]                            = "_outg";
  strings_[ENGLISH_COL][MASK_PLOIDY_1_MARK]                                     = "_ploidy1";
  strings_[ENGLISH_COL][MASK_PLOIDY_2_MARK]                                     = "_ploidy2";
  
  
  /// Extensions

  strings_[ENGLISH_COL][OUTPUT_EXTENSION]                                       = ".output";
  strings_[ENGLISH_COL][SCRIPT_FILES_EXTENSION]                                 = ".ngasp";
  strings_[ENGLISH_COL][DM_EXPORT_EXTENSION]                                    = ".json";

  /// Application State File

  strings_[ENGLISH_COL][DM_PRE_FILE_NAME]                                       = "dm_state_";
  strings_[ENGLISH_COL][DM_FILE_NAME]                                           = "auto";
  //@}
  //@{
  /// ==========================================================================
  /// Object status (To Be Reviewed)
  /// ==========================================================================
  strings_[ENGLISH_COL][STATUS_BUSY]                                            = "Busy";
  strings_[ENGLISH_COL][STATUS_READY]                                           = "Ready";
  //@}
  //@{
  /// ==========================================================================
  /// Object Types (To Be Reviewed)
  /// ==========================================================================
  strings_[ENGLISH_COL][OBJECT_DATA]                                            = "DATA";
  strings_[ENGLISH_COL][OBJECT_CALC]                                            = "CALCULATION";
  strings_[ENGLISH_COL][OBJECT_SYS]                                             = "SYSTEM";
  strings_[ENGLISH_COL][OBJECT_DAO]                                             = "DAO";
  //@}
  //@{
  /// ==========================================================================
  /// Lost+Found
  /// ==========================================================================
  /// instructions

  strings_[ENGLISH_COL][INSTRUCTION_COMMAND_LINE]                               = "Command Line";
  strings_[ENGLISH_COL][INSTRUCTION_YAML]                                       = "Instruction";

  /// Experiments

  strings_[ENGLISH_COL][EXPERIMENT_DEFAULT_NAME]                                = "default";


  strings_[ENGLISH_COL][CALC_DATAS_SEPARATOR]                                   = ","; // only one char
  //@}
  //@{
  /// ==========================================================================
  /// Obsolete???
  /// ==========================================================================
  /// Objects SYS

  strings_[ENGLISH_COL][SYS_RANDOMIZE_NAME]                                     = "rand";
  strings_[ENGLISH_COL][SYS_RANDOMIZE]                                          = "randomize";
  strings_[ENGLISH_COL][SYS_OUTPUT_NAME]                                        = "out";
  strings_[ENGLISH_COL][SYS_OUTPUT]                                             = "output";

  /// Objects DAO

  strings_[ENGLISH_COL][DAO_FASTA]                                              = "fastaDAO";
  strings_[ENGLISH_COL][DAO_FASTA_DESC]                                         = "FASTA Data Access Object";
  strings_[ENGLISH_COL][DAO_FASTA_NAME]                                         = "fastaDAO";
  strings_[ENGLISH_COL][DAO_MS]                                                 = "msDAO";
  strings_[ENGLISH_COL][DAO_MS_DESC]                                            = "MS Data Access Object";
  strings_[ENGLISH_COL][DAO_MS_NAME]                                            = "msDAO";
  //@}
  
  //@{
  /// ==========================================================================
  /// General Menu Options
  /// ==========================================================================
  /// Numeric options
  
  strings_[ENGLISH_COL][VALUE_0]                                                = "0";
  strings_[ENGLISH_COL][VALUE_1]                                                = "1";
  strings_[ENGLISH_COL][VALUE_2]                                                = "2";
  strings_[ENGLISH_COL][VALUE_3]                                                = "3";
  strings_[ENGLISH_COL][VALUE_4]                                                = "4";
  strings_[ENGLISH_COL][VALUE_5]                                                = "5";
  strings_[ENGLISH_COL][VALUE_6]                                                = "6";
  strings_[ENGLISH_COL][VALUE_7]                                                = "7";
  strings_[ENGLISH_COL][VALUE_8]                                                = "8";
  strings_[ENGLISH_COL][VALUE_9]                                                = "9";
  strings_[ENGLISH_COL][VALUE_10]                                               = "10";
  
  /// Boolean options
  
  strings_[ENGLISH_COL][VALUE_NO]                                               = "No";
  strings_[ENGLISH_COL][VALUE_YES]                                              = "Yes";
  //@}

      
  /// ==========================================================================
  /// Commands (CMD)
  /// ==========================================================================
  strings_[ENGLISH_COL][_COMMAND_FIRST]                                         = "";  // *************************************
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_MSTATSPOP]                                          = strings_[ENGLISH_COL][MSTATSPOP_APP_NAME];
  strings_[ENGLISH_COL][CMD_MSTATSPOP_ABB]                                      = strings_[ENGLISH_COL][MSTATSPOP_APP_NAME];
  strings_[ENGLISH_COL][CMD_MSTATSPOP_DESC]                                     = strings_[ENGLISH_COL][MSTATSPOP_DESC];

  

  strings_[ENGLISH_COL][STANDARD_GROUP_FLAGS]                                   = "Flags:";
  strings_[ENGLISH_COL][MSTATSPOP_GROUP_GENERAL]                                = "General parameters:";
  strings_[ENGLISH_COL][MSTATSPOP_GROUP_GENERAL_OPTIONAL]                       = "Optional general parameters:";
  strings_[ENGLISH_COL][MSTATSPOP_GROUP_FA_TFA]                                 = "Optional parameters for FASTA and TFA input files:";
  strings_[ENGLISH_COL][MSTATSPOP_GROUP_TFA]                                    = "Parameters for TFA input files: (Sliding Window Analysis of Empirical Data)"; //PARAMETERS FOR TFASTA INPUT (-f tfa): 'SLIDING WINDOW ANALYSIS OF EMPIRICAL DATA'";
  strings_[ENGLISH_COL][MSTATSPOP_GROUP_MS]                                     = "Parameters for MS input files: (Simulation Analysis of a Single Region)"; //PARAMETERS FOR MS INPUT (-f ms):'SIMULATION ANALYSIS OF A SINGLE REGION'";
  strings_[ENGLISH_COL][MSTATSPOP_GROUP_FA]                                     = "Parameters for FASTA input files: (Whole Region Analysis)"; //PARAMETERS FOR FASTA INPUT (-f fasta): 'WHOLE REGION ANALYSIS'\n    Optional:";
  strings_[ENGLISH_COL][STANDARD_GROUP_HELP]                                    = "Help:";

  
  
  
  /// Command options:
   
  strings_[ENGLISH_COL][MSTATSPOP_FORMAT_SHORT]                                 = "f";
  strings_[ENGLISH_COL][MSTATSPOP_FORMAT_LONG]                                  = "format";
  strings_[ENGLISH_COL][MSTATSPOP_FORMAT_DESC]                                  = "Input format file";

  strings_[ENGLISH_COL][MSTATSPOP_INPUT_SHORT]                                  = "i";
  strings_[ENGLISH_COL][MSTATSPOP_INPUT_LONG]                                   = "input";
  strings_[ENGLISH_COL][MSTATSPOP_INPUT_DESC]                                   = "Path and name of the input file";

  strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_SHORT]                                 = "o";
  strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_LONG]                                  = "output";
  strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_DESC]                                  = "Output format file";
  
  strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_0_DESC]                                = "extended";
  strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_1_DESC]                                = "single line / window";
  strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_3_DESC]                                = "dadi-like format";
  strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_4_DESC]                                = "single line pairwise distribution";
  strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_5_DESC]                                = "single line freq. variant per line/window";
  strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_6_DESC]                                = "SNP genotype matrix";
  strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_10_DESC]                               = "full extended";
  strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_CALC_DESCRIPTION]                      = "0: " + strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_0_DESC] + ",\n1: " + strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_1_DESC]+ ",\n3: " + strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_3_DESC]+ ",\n4: " + strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_4_DESC]+ ",\n5: " + strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_5_DESC]+ ",\n6: " + strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_6_DESC]+ ",\n10: " + strings_[ENGLISH_COL][MSTATSPOP_OUTPUT_10_DESC];

  strings_[ENGLISH_COL][MSTATSPOP_POP_SHORT]                                    = "N";
  strings_[ENGLISH_COL][MSTATSPOP_POP_LONG]                                     = "N";
  strings_[ENGLISH_COL][MSTATSPOP_POP_DESC]                                     = "Populations";
  strings_[ENGLISH_COL][MSTATSPOP_POP_EXAMPLE]                                  = "[#_pops] [#samples_pop1] ... [#samples_popN]";
  strings_[ENGLISH_COL][MSTATSPOP_POP_CALC_EXAMPLE]                             = "4 2";
  
  /// Command options: General
    
  strings_[ENGLISH_COL][MSTATSPOP_OUTGROUP_SHORT]                               = "G";
  strings_[ENGLISH_COL][MSTATSPOP_OUTGROUP_LONG]                                = "G";
  strings_[ENGLISH_COL][MSTATSPOP_OUTGROUP_DESC]                                = "Last population is outgroup";
    
  strings_[ENGLISH_COL][MSTATSPOP_INCL_UNKNO_SHORT]                             = "u";
  strings_[ENGLISH_COL][MSTATSPOP_INCL_UNKNO_LONG]                              = "include-unknown";
  strings_[ENGLISH_COL][MSTATSPOP_INCL_UNKNO_DESC]                              = "Include unknown positions";
   
  strings_[ENGLISH_COL][MSTATSPOP_PATHNAME_OUTPUT_FILE_SHORT]                   = "T";
  strings_[ENGLISH_COL][MSTATSPOP_PATHNAME_OUTPUT_FILE_LONG]                    = "T";
  strings_[ENGLISH_COL][MSTATSPOP_PATHNAME_OUTPUT_FILE_DESC]                    = "Path and name of the output file";
  strings_[ENGLISH_COL][MSTATSPOP_PATHNAME_OUTPUT_FILE_DEF_VAL]                 = "Standard output";
  

  strings_[ENGLISH_COL][MSTATSPOP_ALT_SFILE_SHORT]                              = "A";
  strings_[ENGLISH_COL][MSTATSPOP_ALT_SFILE_LONG]                               = "A";
  strings_[ENGLISH_COL][MSTATSPOP_ALT_SFILE_DESC]                               = "Alternative Spectrum File. Alternative_spectrum for each population (except outgroup)";
  strings_[ENGLISH_COL][MSTATSPOP_ALT_SFILE_EXAMPLE]                            = "File format: (average absolute values) header plus fr(0,1) fr(0,2) ... fr(0,n-1) theta(0)/nt, fr(1,1) fr(1,2) ... fr(1,n-1) theta(1)/nt...";
  strings_[ENGLISH_COL][MSTATSPOP_ALT_SFILE_ONLY]                               = "Optimal Test";
  
  strings_[ENGLISH_COL][MSTATSPOP_NULL_SFILE_SHORT]                             = "S";
  strings_[ENGLISH_COL][MSTATSPOP_NULL_SFILE_LONG]                              = "S";
  strings_[ENGLISH_COL][MSTATSPOP_NULL_SFILE_DESC]                              = "[Null Spectrum File: null_spectrum for each population (except outgroup)";
  strings_[ENGLISH_COL][MSTATSPOP_NULL_SFILE_EXAMPLE]                           = "(average absolute values) header plus fr(0,1) fr(0,2) ... fr(0,n-1) theta(0)/nt, fr(1,1) fr(1,2) ... fr(1,n-1) theta(1)/nt...";
  strings_[ENGLISH_COL][MSTATSPOP_NULL_SFILE_ONLY]                              = "-A defined";
  strings_[ENGLISH_COL][MSTATSPOP_NULL_SFILE_DEF_VAL]                           = "SNM";
  
  strings_[ENGLISH_COL][MSTATSPOP_R2P_SHORT]                                    = "P";
  strings_[ENGLISH_COL][MSTATSPOP_R2P_LONG]                                     = "P";
  strings_[ENGLISH_COL][MSTATSPOP_R2P_DESC]                                     = "First value is the number of values to include, next are the number of lines to consider";
  strings_[ENGLISH_COL][MSTATSPOP_R2P_EXAMPLE]                                  = "ex: -P 6 1 2 4 8 16 64";
  strings_[ENGLISH_COL][MSTATSPOP_R2P_ONLY]                                     = "Calculation of R2_p";
   
  strings_[ENGLISH_COL][MSTATSPOP_ORDER_SHORT]                                  = "O";
  strings_[ENGLISH_COL][MSTATSPOP_ORDER_LONG]                                   = "order";
  strings_[ENGLISH_COL][MSTATSPOP_ORDER_DESC]                                   = "Order of samples";
  strings_[ENGLISH_COL][MSTATSPOP_ORDER_EXAMPLE]                                = "[#_nsam] [number order of first sample, number 0 is the first sample] [second sample] ...etc. up to nsamples";
  strings_[ENGLISH_COL][MSTATSPOP_ORDER_DEF_VAL]                                = "current order";

  strings_[ENGLISH_COL][MSTATSPOP_PERM_ITE_SHORT]                               = "t";
  strings_[ENGLISH_COL][MSTATSPOP_PERM_ITE_LONG]                                = "t";
  strings_[ENGLISH_COL][MSTATSPOP_PERM_ITE_DESC]                                = "Number of permutations per window (H0: Fst=0)";
  
  strings_[ENGLISH_COL][MSTATSPOP_SEED_SHORT]                                   = "s";
  strings_[ENGLISH_COL][MSTATSPOP_SEED_LONG]                                    = "seed";
  strings_[ENGLISH_COL][MSTATSPOP_SEED_DESC]                                    = "Initial seed for random values";
  strings_[ENGLISH_COL][MSTATSPOP_SEED_DEF_VAL]                                 = "123456";

  /// Command options: For TFASTA Input

  strings_[ENGLISH_COL][MSTATSPOP_WINDOW_SIZE_SHORT]                            = "w";
  strings_[ENGLISH_COL][MSTATSPOP_WINDOW_SIZE_LONG]                             = "window-size";
  strings_[ENGLISH_COL][MSTATSPOP_WINDOW_SIZE_DESC]                             = "Window size";

  strings_[ENGLISH_COL][MSTATSPOP_SLIDE_SIZE_SHORT]                             = "z";
  strings_[ENGLISH_COL][MSTATSPOP_SLIDE_SIZE_LONG]                              = "slide-size";
  strings_[ENGLISH_COL][MSTATSPOP_SLIDE_SIZE_DESC]                              = "Slide size. Must be equal or larger than window size";
  strings_[ENGLISH_COL][MSTATSPOP_SLIDE_SIZE_DEF_VAL]                           = "window size";
    
  strings_[ENGLISH_COL][MSTATSPOP_WINDOW_LENGTHS_SHORT]                         = "Y";
  strings_[ENGLISH_COL][MSTATSPOP_WINDOW_LENGTHS_LONG]                          = "window-length";
  strings_[ENGLISH_COL][MSTATSPOP_WINDOW_LENGTHS_DESC]                          = "Define window lengths";
  strings_[ENGLISH_COL][MSTATSPOP_WINDOW_LENGTHS_VAL_0]                         = "In 'effective' positions";
  strings_[ENGLISH_COL][MSTATSPOP_WINDOW_LENGTHS_VAL_1]                         = "In 'physical' positions";
  strings_[ENGLISH_COL][MSTATSPOP_WINDOW_LENGTHS_CALC_DESC]                     = "0: " + strings_[ENGLISH_COL][MSTATSPOP_WINDOW_LENGTHS_VAL_0] + "\n1: " + strings_[ENGLISH_COL][MSTATSPOP_WINDOW_LENGTHS_VAL_1];

  strings_[ENGLISH_COL][MSTATSPOP_COORDS_FILE_SHORT]                            = "W";
  strings_[ENGLISH_COL][MSTATSPOP_COORDS_FILE_LONG]                             = "coords-file";
  strings_[ENGLISH_COL][MSTATSPOP_COORDS_FILE_DESC]                             = "File with the coordinates of each window [init end] (overwrite options -w and -z)";
  strings_[ENGLISH_COL][MSTATSPOP_COORDS_FILE_DEF_VAL]                          = "One whole window";
  

  strings_[ENGLISH_COL][MSTATSPOP_HEIGHTS_FILE_SHORT]                           = "E";
  strings_[ENGLISH_COL][MSTATSPOP_HEIGHTS_FILE_LONG]                            = "weights-file";
  strings_[ENGLISH_COL][MSTATSPOP_HEIGHTS_FILE_DESC]                            = "Input file with weights for positions:";
  strings_[ENGLISH_COL][MSTATSPOP_HEIGHTS_FILE_EXAMPLE]                         = "Include three columns with a header, first the physical positions (1...end), second the weight for positions and third a boolean weight for the variant (eg. syn variant in nsyn counts is 0.000)";
  strings_[ENGLISH_COL][MSTATSPOP_HEIGHTS_FILE_DEF_VAL]                         = "all 1.000";

  strings_[ENGLISH_COL][MSTATSPOP_SCAFFOLD_NAME_SHORT]                          = "n";
  strings_[ENGLISH_COL][MSTATSPOP_SCAFFOLD_NAME_LONG]                           = "scaffold-name";
  strings_[ENGLISH_COL][MSTATSPOP_SCAFFOLD_NAME_DESC]                           = "Input list of scaffold names:";
  strings_[ENGLISH_COL][MSTATSPOP_SCAFFOLD_NAME_EXAMPLE]                        = "chr10,chr12,chr14";
  strings_[ENGLISH_COL][MSTATSPOP_SCAFFOLD_NAME_DEF_VAL]                        = "";

  /// Command options: For MS Input
   
  strings_[ENGLISH_COL][MSTATSPOP_LENGTH_SHORT]                                 = "l";
  strings_[ENGLISH_COL][MSTATSPOP_LENGTH_LONG]                                  = "length";
  strings_[ENGLISH_COL][MSTATSPOP_LENGTH_DESC]                                  = "Length";

  strings_[ENGLISH_COL][MSTATSPOP_MS_ITERATIONS_SHORT]                          = "r";
  strings_[ENGLISH_COL][MSTATSPOP_MS_ITERATIONS_LONG]                           = "ms-iterations";
  strings_[ENGLISH_COL][MSTATSPOP_MS_ITERATIONS_DESC]                           = "Number of iterations";
  
  strings_[ENGLISH_COL][MSTATSPOP_MASK_SHORT]                                   = "m";
  strings_[ENGLISH_COL][MSTATSPOP_MASK_LONG]                                    = "include-mask-file";
  strings_[ENGLISH_COL][MSTATSPOP_MASK_DESC]                                    = "Include mask_filename";
  strings_[ENGLISH_COL][MSTATSPOP_MASK_EXAMPLE]                                 = "mask_file format: 1st row with 'length' weights, next sample rows x lengths: missing 0, sequenced 1)";
  strings_[ENGLISH_COL][MSTATSPOP_MASK_DEF_VAL]                                 = "No mask. All positions included";
       
  strings_[ENGLISH_COL][MSTATSPOP_RATIOTRANS_SHORT]                             = "v";
  strings_[ENGLISH_COL][MSTATSPOP_RATIOTRANS_LONG]                              = "ratio-trans";
  strings_[ENGLISH_COL][MSTATSPOP_RATIOTRANS_DESC]                              = "Ratio transitions / transversions";
  strings_[ENGLISH_COL][MSTATSPOP_RATIOTRANS_DEF_VAL]                           = "0.5";
  
  strings_[ENGLISH_COL][MSTATSPOP_INCL_OUTGR_SHORT]                             = "F";
  strings_[ENGLISH_COL][MSTATSPOP_INCL_OUTGR_LONG]                              = "include-outgroup";
  strings_[ENGLISH_COL][MSTATSPOP_INCL_OUTGR_DESC]                              = "Force analysis to include outgroup";
  strings_[ENGLISH_COL][MSTATSPOP_INCL_OUTGR_VALUE_0]                           = "Ancestral";

  strings_[ENGLISH_COL][MSTATSPOP_FREQREVMUT_SHORT]                             = "q";
  strings_[ENGLISH_COL][MSTATSPOP_FREQREVMUT_LONG]                              = "freq-reverted-mutation";
  strings_[ENGLISH_COL][MSTATSPOP_FREQREVMUT_DESC]                              = "Frequency of reverted mutation";
  strings_[ENGLISH_COL][MSTATSPOP_FREQREVMUT_ONLY]                              = "-F 1";
  strings_[ENGLISH_COL][MSTATSPOP_FREQREVMUT_DEF_VAL]                           = "0";
  
  
  /// Command options: For FASTA Input
    
  strings_[ENGLISH_COL][MSTATSPOP_PLOIDY_SHORT]                                 = "p";
  strings_[ENGLISH_COL][MSTATSPOP_PLOIDY_LONG]                                  = "ploidy";
  strings_[ENGLISH_COL][MSTATSPOP_PLOIDY_DESC]                                  = "Number of lineages per sequence";
  strings_[ENGLISH_COL][MSTATSPOP_PLOIDY_OPTION_HAPLOID]                        = "1";
  strings_[ENGLISH_COL][MSTATSPOP_PLOIDY_OPTION_DIPLOID]                        = "2";
  strings_[ENGLISH_COL][MSTATSPOP_PLOIDY_CALC_DESC]                             = strings_[ENGLISH_COL][MSTATSPOP_PLOIDY_DESC] + "\n1: Haploid\n2: Diploid";
    
  strings_[ENGLISH_COL][MSTATSPOP_GFF_FILE_SHORT]                               = "g";
  strings_[ENGLISH_COL][MSTATSPOP_GFF_FILE_LONG]                                = "g";
  strings_[ENGLISH_COL][MSTATSPOP_GFF_FILE_DESC]                                = "GFF file";
  strings_[ENGLISH_COL][MSTATSPOP_GFF_FILE_DEF_VAL]                             = "No annotation";
  strings_[ENGLISH_COL][MSTATSPOP_GFF_FILE_EXAMPLE]                             = "Add also: coding, noncoding, synonymous, nonsynonymous, silent, others (or whatever annotated). If synonymous or nonsynonymous or silent then add: Genetic_Code: Nuclear_Universal, mtDNA_Drosophila, mtDNA_Mammals, Other. If Other then introduce the code for the 64 triplets in the order UUU UUC UUA UUG ... etc.";
  
  strings_[ENGLISH_COL][MSTATSPOP_CRITERIA_SHORT]                               = "c";
  strings_[ENGLISH_COL][MSTATSPOP_CRITERIA_LONG]                                = "c";
  strings_[ENGLISH_COL][MSTATSPOP_CRITERIA_DESC]                                = "Criteria to consider transcripts";
  strings_[ENGLISH_COL][MSTATSPOP_CRITERIA_ONLY]                                = "Coding regions";

  strings_[ENGLISH_COL][MSTATSPOP_MASK_PRINT_SHORT]                             = "K";
  strings_[ENGLISH_COL][MSTATSPOP_MASK_PRINT_LONG]                              = "K";
  strings_[ENGLISH_COL][MSTATSPOP_MASK_PRINT_DESC]                              = "Make a MASK file with the valid positions for this fasta. Useful for running ms simulations (1/0)";
  strings_[ENGLISH_COL][MSTATSPOP_MASK_PRINT_DEF_VAL]                           = "0";

    
  /// Command options: Help
 
  strings_[ENGLISH_COL][MSTATSPOP_HELP_SHORT]                                   = "h";
  strings_[ENGLISH_COL][MSTATSPOP_HELP_LONG]                                    = "help";
  strings_[ENGLISH_COL][MSTATSPOP_HELP_DESC]                                    = "Help and exit";

  /// Command options: New & Not done
  strings_[ENGLISH_COL][MSTATSPOP_KIND_LENGTH_SHORT]                  = "k";
  strings_[ENGLISH_COL][MSTATSPOP_LOCATION_MISSING_SHORT]                  = "M";
  strings_[ENGLISH_COL][MSTATSPOP_FIRST_SLIDE_SHORT]                  = "Z";


/*
  strings_[ENGLISH_COL][MSTATSPOP_WEIGHTS_VARIANTS_FILE_SHORT]                  = "e";
  strings_[ENGLISH_COL][MSTATSPOP_WEIGHTS_VARIANTS_FILE_LONG]                   = "weights-variants-FILE";
  strings_[ENGLISH_COL][MSTATSPOP_WEIGHTS_VARIANTS_FILE_DESC]                   = "[input file with weights for variants: include two columns with a header, first the physical positions and second the weight]";

  strings_[ENGLISH_COL][MSTATSPOP_COUNT_TRANSITIONS_SHORT]                      = "T";
  strings_[ENGLISH_COL][MSTATSPOP_COUNT_TRANSITIONS_LONG]                       = "count-transitions";
  strings_[ENGLISH_COL][MSTATSPOP_COUNT_TRANSITIONS_DESC]                       = "[count only transitions (not for ms format)";

  strings_[ENGLISH_COL][MSTATSPOP_COUNT_TRANSVERSION_SHORT]                     = "V";
  strings_[ENGLISH_COL][MSTATSPOP_COUNT_TRANSVERSION_LONG]                      = "count-transversions";
  strings_[ENGLISH_COL][MSTATSPOP_COUNT_TRANSVERSION_DESC]                      = "[count only transversions (not for ms format)";

  strings_[ENGLISH_COL][MSTATSPOP_COUNT_GC_MUTATIONS_SHORT]                     = "G";
  strings_[ENGLISH_COL][MSTATSPOP_COUNT_GC_MUTATIONS_LONG]                      = "count-GC-mutations";
  strings_[ENGLISH_COL][MSTATSPOP_COUNT_GC_MUTATIONS_DESC]                      = "[count only G/C mutations (not for ms format)";

  strings_[ENGLISH_COL][MSTATSPOP_COUNT_AT_MUTATIONS_SHORT]                     = "A";
  strings_[ENGLISH_COL][MSTATSPOP_COUNT_AT_MUTATIONS_LONG]                      = "count-AT-mutations";
  strings_[ENGLISH_COL][MSTATSPOP_COUNT_AT_MUTATIONS_DESC]                      = "[count only A/T mutations (not for ms format)";
  */
  
  /// Command options: Removed
  
  //  strings_[ENGLISH_COL][MSTATSPOP_NUM_COMP_SHORT]                           = "y";
  //  strings_[ENGLISH_COL][MSTATSPOP_NUM_COMP_LONG]                            = "y";
  //  strings_[ENGLISH_COL][MSTATSPOP_NUM_COMP_DESC]                            = "[in case missing: number of comparisons for approximate calculation of covariance. 0 if rough approach]";  // to eliminate

  //  strings_[ENGLISH_COL][MSTATSPOP_FREQ_M_P_SHORT]                           = "x";
  //  strings_[ENGLISH_COL][MSTATSPOP_FREQ_M_P_LONG]                            = "freq-missing-positions";
  //  strings_[ENGLISH_COL][MSTATSPOP_FREQ_M_P_DESC]                            = "[frequency of missing positions (only with -f ms[_e] and -u 1)";  // to eliminate


  //  strings_[ENGLISH_COL][MSTATSPOP_KLENGTH_SHORT]                            = "k";
  //  strings_[ENGLISH_COL][MSTATSPOP_KLENGTH_LONG]                             = "k";
  //  strings_[ENGLISH_COL][MSTATSPOP_KLENGTH_DESC]                             = "[kind of length (only for ms_e format). Except outgroup: 0 All accepted positions even regions with all Ns (default);[1 Only positions with at least one valid nt; 2 At least two valid nt; 3]";  // valorate to eliminate

  //  strings_[ENGLISH_COL][MSTATSPOP_COLUMN_SHORT]                             = "M";
  //  strings_[ENGLISH_COL][MSTATSPOP_COLUMN_LONG]                              = "M";
  //  strings_[ENGLISH_COL][MSTATSPOP_COLUMN_DESC]                              = "[column location (starting from 1] of the Ratio of missing values (only for ms_e format)]";  // eliminate format ms_e


  /// Format File Options

  strings_[ENGLISH_COL][FORMAT_FILE_FASTA]                                      = "fasta";
  strings_[ENGLISH_COL][FORMAT_FILE_MS]                                         = "ms";
  strings_[ENGLISH_COL][FORMAT_FILE_MS_EXTENDED]                                = "ms_x";
  strings_[ENGLISH_COL][FORMAT_FILE_NBRF]                                       = "nbrf";
  strings_[ENGLISH_COL][FORMAT_FILE_TFASTA]                                     = "tfa";

  /// Subset Positions Options

  strings_[ENGLISH_COL][SUBSET_POS_SYNONYMOUS]                                  = "synonymous";
  strings_[ENGLISH_COL][SUBSET_POS_NONSYNONYMOUS]                               = "nonsynonymous";
  strings_[ENGLISH_COL][SUBSET_POS_0_FOLD]                                      = "0-fold";
  strings_[ENGLISH_COL][SUBSET_POS_2_FOLD]                                      = "2-fold";
  strings_[ENGLISH_COL][SUBSET_POS_3_FOLD]                                      = "3-fold";
  strings_[ENGLISH_COL][SUBSET_POS_4_FOLD]                                      = "4-fold";
  strings_[ENGLISH_COL][SUBSET_POS_SILENT]                                      = "silent";
  strings_[ENGLISH_COL][CODE_NAME_OTHER]                                        = "Other";

  /// Criteria Transcript Options

  strings_[ENGLISH_COL][CRITERIA_TRANSCRIPT_MAX]                                = "max";
  strings_[ENGLISH_COL][CRITERIA_TRANSCRIPT_MIN]                                = "min";
  strings_[ENGLISH_COL][CRITERIA_TRANSCRIPT_FIRST]                              = "first";
  strings_[ENGLISH_COL][CRITERIA_TRANSCRIPT_LONG]                               = "long";

  /// Validation Errors

  strings_[ENGLISH_COL][POPULATIONS_NOT_DEF]                                    = "Populations not defined...";
  strings_[ENGLISH_COL][FORCE_AND_OUTGROUP_ERROR]                               = "force_outgroup and outgroup_presence cannot be 1 at the same time...";
  strings_[ENGLISH_COL][OUTGROUP_PRESENCE_ERROR]                                = "Error in -G argument: only the values 0 or 1 are allowed.";
  strings_[ENGLISH_COL][FORCE_OUTGROUP_ERROR]                                   = "Error in -F argument: only the values 0 or 1 are allowed.";
  strings_[ENGLISH_COL][FORMATFILE_FORCE_OUTGROUP_ERROR]                        = "Error. The option -F 1 is only compatible with -f 'ms'.";
  strings_[ENGLISH_COL][SORT_NSAM_ERROR]                                        = "Error: the number of samples defined in -N and -O are different";
  strings_[ENGLISH_COL][OUTPUT_ERROR]                                           = "Output must be a number from 0 to 10...";
  strings_[ENGLISH_COL][FILE_OPEN_ERROR]                                        = "File open error:: ";
  strings_[ENGLISH_COL][FILE_CREATION_ERROR]                                    = "File creation error: ";
  strings_[ENGLISH_COL][MORE_POPS_EXPECTED]                                     = "Expected more populations in input  file...";
  strings_[ENGLISH_COL][MATRIX_POL_EMPTY_ROWS]                                  = "Matrix pol full of empty rows...";
  strings_[ENGLISH_COL][PHYSICAL_LENGTH_ERROR]                                  = "Error in -l argument: only the values 0 or 1 are allowed.";
  strings_[ENGLISH_COL][NPOPS_ERROR]                                            = "Error. The option -N must be included.";
  strings_[ENGLISH_COL][WINDOW_ERROR]                                           = "Error. The option -w or -W must be included with option -f tfa.";
  strings_[ENGLISH_COL][SLIDE_ERROR]                                            = "Error. The value at option -z (slide) must be equal or larger than the number at -w (window)";
  strings_[ENGLISH_COL][LENGTH_ERROR]                                           = "Error. length (-l option) must be defined with ms input file.";
  strings_[ENGLISH_COL][FORMATFILE_AND_NITERDATA_ERROR]                         = "Error. The option ";
  strings_[ENGLISH_COL][ERROR_POSITION_LENGTHS]                                 = "Error: The files of the weights and effect sizes have different position lengths.";
  
  /// Mstatspop Status Messages
    
  strings_[ENGLISH_COL][CALCULATING_PERMUTATION_TESTS]                          = "Calculating permutation test...";
  strings_[ENGLISH_COL][PERMUTATION_TESTS_DONE]                                 = "Permutation test one vs all Done.";
  strings_[ENGLISH_COL][CALCULATING_PERMUTATION_TESTS_PAIR]                     = "Calculating permutation test for all pair-pair comparisons...";

      
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_LOAD_FILE]                                          = "load-instructions-file";
  strings_[ENGLISH_COL][CMD_LOAD_FILE_ABB]                                      = "load";
  strings_[ENGLISH_COL][CMD_LOAD_FILE_DESC]                                     = "This command open and executes an instructions file.";

  /// Command options

  strings_[ENGLISH_COL][FORMAT_YAML]                                            = "yaml";
  strings_[ENGLISH_COL][FORMAT_NGASP]                                           = "ngasp";

  strings_[ENGLISH_COL][LOAD_OPE_FILE_SHORT]                                    = "i";
  strings_[ENGLISH_COL][LOAD_OPE_FILE_LONG]                                     = "input";
  strings_[ENGLISH_COL][LOAD_OPE_FILE_DESC]                                     = "Input file.";

  strings_[ENGLISH_COL][LOAD_OPE_FILE_INPUTS_SHORT]                             = "v";
  strings_[ENGLISH_COL][LOAD_OPE_FILE_INPUTS_LONG]                              = "values";
  strings_[ENGLISH_COL][LOAD_OPE_FILE_INPUTS_DESC]                              = "Input values file.";

  strings_[ENGLISH_COL][LOAD_OPE_FILE_FORMAT_SHORT]                             = "f";
  strings_[ENGLISH_COL][LOAD_OPE_FILE_FORMAT_LONG]                              = "format";
  strings_[ENGLISH_COL][LOAD_OPE_FILE_FORMAT_DESC]                              = "[" + strings_[ENGLISH_COL][FORMAT_YAML] + ", " + strings_[ENGLISH_COL][FORMAT_NGASP] + "]";

  strings_[ENGLISH_COL][LOAD_OPE_FILE_NOT_FOUND]                                = "file not found...";

  strings_[ENGLISH_COL][INCLUDE_VALUES]                                         = "@LOAD_VALUES";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_APP_VERSION]                                        = "version";
  strings_[ENGLISH_COL][CMD_APP_VERSION_ABB]                                    = "ver";
  strings_[ENGLISH_COL][CMD_APP_VERSION_DESC]                                   = "This command show the application version number.";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_VERBOSE]                                            = "verbose";
  strings_[ENGLISH_COL][CMD_VERBOSE_ABB]                                        = "verbose";
  strings_[ENGLISH_COL][CMD_VERBOSE_DESC]                                       = "This function increases / decreases the verbose level of logs.";

  /// Command options

  strings_[ENGLISH_COL][VERBOSE_LEVEL_SHORT]                                    = "l";
  strings_[ENGLISH_COL][VERBOSE_LEVEL_LONG]                                     = "level";
  strings_[ENGLISH_COL][VERBOSE_LEVEL_DESC]                                     = "The verbose level can be set to: silent, normal or debug. By default it is set to normal.";

  strings_[ENGLISH_COL][VERBOSE_LEVEL_MISSING]                                  = "You must indicate the verbose level.";
  strings_[ENGLISH_COL][VERBOSE_LEVEL_UNKNOWN]                                  = "Unknown option set for verbose level.";
  strings_[ENGLISH_COL][VERBOSE_LEVEL_SILENT]                                   = "silent";
  strings_[ENGLISH_COL][VERBOSE_LEVEL_NORMAL]                                   = "normal";
  strings_[ENGLISH_COL][VERBOSE_LEVEL_DEBUG]                                    = "debug";

  strings_[ENGLISH_COL][VERBOSE_TITLE]                                          = "Verbose Level: ";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_APP_HELP]                                           = "help";
  strings_[ENGLISH_COL][CMD_APP_HELP_ABB]                                       = "help";
  strings_[ENGLISH_COL][CMD_APP_HELP_DESC]                                      = "This command shows the application help.";

  strings_[ENGLISH_COL][CMD_APP_HELP_CMD_SHORT]                                 = "n";
  strings_[ENGLISH_COL][CMD_APP_HELP_CMD_LONG]                                  = "";
  strings_[ENGLISH_COL][CMD_APP_HELP_CMD_DESC]                                  = "Show help for an specific command or calculation.";

  strings_[ENGLISH_COL][CMD_APP_HELP_FORMAT_SHORT]                              = "m";
  strings_[ENGLISH_COL][CMD_APP_HELP_FORMAT_LONG]                               = "mode";
  strings_[ENGLISH_COL][CMD_APP_HELP_FORMAT_DESC]                               = "Output format.";

  /// Man texts
  
  strings_[ENGLISH_COL][MAN_NAME]                                               = "NAME";
  strings_[ENGLISH_COL][MAN_SYNOPSIS]                                           = "SYNOPSIS";
  strings_[ENGLISH_COL][MAN_DESCRIPTION]                                        = "DESCRIPTION";
  strings_[ENGLISH_COL][MAN_AUTHOR]                                             = "AUTHOR";
  strings_[ENGLISH_COL][MAN_COPYRIGHT]                                          = "COPYRIGHT";
  strings_[ENGLISH_COL][MAN_SEE_ALSO]                                           = "SEE ALSO";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_DRY_RUN]                                            = "dry-run";
  strings_[ENGLISH_COL][CMD_DRY_RUN_ABB]                                        = "dr";
  strings_[ENGLISH_COL][CMD_DRY_RUN_DESC]                                       = "This command enables and disables the dry-run option. When activated, all instructions are checked but not executed.";

  /// Command options

  strings_[ENGLISH_COL][DRY_RUN_SET_SHORT]                                      = "x";
  strings_[ENGLISH_COL][DRY_RUN_SET_LONG]                                       = "x";
  strings_[ENGLISH_COL][DRY_RUN_SET_DESC]                                       = "true / false.";
  strings_[ENGLISH_COL][DRY_RUN_SET_MISSING]                                    = "You must indicate the true or false.";
  strings_[ENGLISH_COL][DRY_RUN_SET_UNKNOWN]                                    = "Unknown option set for dry-run.";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_RUN]                                                = "run-calculation";
  strings_[ENGLISH_COL][CMD_RUN_ABB]                                            = "run";
  strings_[ENGLISH_COL][CMD_RUN_DESC]                                           = "This command runs calculations";

  /// Command options

  strings_[ENGLISH_COL][RUN_NAME_SHORT]                                         = "n";
  strings_[ENGLISH_COL][RUN_NAME_LONG]                                          = "name";
  strings_[ENGLISH_COL][RUN_NAME_DESC]                                          = "Calculation name.";

  strings_[ENGLISH_COL][RUN_PREPARE_SHORT]                                      = "p";
  strings_[ENGLISH_COL][RUN_PREPARE_LONG]                                       = "prepare";
  strings_[ENGLISH_COL][RUN_PREPARE_DESC]                                       = "Execute Prepare (true / false).";

  strings_[ENGLISH_COL][RUN_CALCULATE_SHORT]                                    = "c";
  strings_[ENGLISH_COL][RUN_CALCULATE_LONG]                                     = "calculate";
  strings_[ENGLISH_COL][RUN_CALCULATE_DESC]                                     = "Execute Calculate (true / false).";

  strings_[ENGLISH_COL][RUN_FINALIZE_SHORT]                                     = "f";
  strings_[ENGLISH_COL][RUN_FINALIZE_LONG]                                      = "finalize";
  strings_[ENGLISH_COL][RUN_FINALIZE_DESC]                                      = "Execute Finalize (true / false).";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_OPEN_DATA_FILE]                                     = "open-data-file";
  strings_[ENGLISH_COL][CMD_OPEN_DATA_FILE_ABB]                                 = "open";
  strings_[ENGLISH_COL][CMD_OPEN_DATA_FILE_DESC]                                = "This command opens a file with data: a fasta file, an ms file, ...";

  /// Command options

  strings_[ENGLISH_COL][OPEN_DATA_FILE_IN_SHORT]                                = "i";
  strings_[ENGLISH_COL][OPEN_DATA_FILE_IN_LONG]                                 = "input";
  strings_[ENGLISH_COL][OPEN_DATA_FILE_IN_DESC]                                 = "";

  strings_[ENGLISH_COL][OPEN_DATA_FILE_TYPE_SHORT]                              = "t";
  strings_[ENGLISH_COL][OPEN_DATA_FILE_TYPE_LONG]                               = "type";
  strings_[ENGLISH_COL][OPEN_DATA_FILE_TYPE_DESC]                               = "";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_DELETE]                                             = "delete";
  strings_[ENGLISH_COL][CMD_DELETE_ABB]                                         = "del";
  strings_[ENGLISH_COL][CMD_DELETE_DESC]                                        = "This command deletes objects from memory.";

  /// Command options

  strings_[ENGLISH_COL][DELETE_DATA_VNAME_SHORT]                                = "n";
  strings_[ENGLISH_COL][DELETE_DATA_VNAME_LONG]                                 = "name";
  strings_[ENGLISH_COL][DELETE_DATA_VNAME_DESC]                                 = "The name of the data object to be deleted.";
  strings_[ENGLISH_COL][DELETE_DATA_RESERVED_NAME]                              = "cannot delete protected data...";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_HISTORY]                                            = "history";
  strings_[ENGLISH_COL][CMD_HISTORY_ABB]                                        = "h";
  strings_[ENGLISH_COL][CMD_HISTORY_DESC]                                       = "This command manages the list of executed instructions.";

  /// Command options

  strings_[ENGLISH_COL][HISTORY_CLEAR_SHORT]                                    = "c";
  strings_[ENGLISH_COL][HISTORY_CLEAR_LONG]                                     = "clear";
  strings_[ENGLISH_COL][HISTORY_CLEAR_DESC]                                     = "Clear history";

  strings_[ENGLISH_COL][HISTORY_RUN_SHORT]                                      = "r";
  strings_[ENGLISH_COL][HISTORY_RUN_LONG]                                       = "run";
  strings_[ENGLISH_COL][HISTORY_RUN_DESC]                                       = "Run instruction from history.";

  /// Output strings

  strings_[ENGLISH_COL][HELP_NAME]                                              = "NAME";
  strings_[ENGLISH_COL][HELP_SYNOPSIS]                                          = "SYNOPSIS";
  strings_[ENGLISH_COL][HELP_DESCRIPTION]                                       = "DESCRIPTION";
  strings_[ENGLISH_COL][HELP_COMMAND_LINE]                                      = "Command Line format";
  strings_[ENGLISH_COL][HELP_COMMAND_LINE_FORMAT_1]                             = strings_[ENGLISH_COL][NGASP_APP_EXECUTABLE_NAME] + " [COMMAND]";
  strings_[ENGLISH_COL][HELP_COMMAND_LINE_FORMAT_2]                             = strings_[ENGLISH_COL][NGASP_APP_EXECUTABLE_NAME] + " " + strings_[ENGLISH_COL][INTERACTIVE_MODE_CHAR];

  /// File

  strings_[ENGLISH_COL][INSTRUCTIONS_HISTORY_FILE]                              = "ngasp.history";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_LOG]                                                = "log";
  strings_[ENGLISH_COL][CMD_LOG_ABB]                                            = "l";
  strings_[ENGLISH_COL][CMD_LOG_DESC]                                           = "This command shows the log file content.";

  /// Command options

  strings_[ENGLISH_COL][LOG_CLEAR_SHORT]                                        = "c";
  strings_[ENGLISH_COL][LOG_CLEAR_LONG]                                         = "clear";
  strings_[ENGLISH_COL][LOG_CLEAR_DESC]                                         = "Clear log messages";

  /// Output strings

  strings_[ENGLISH_COL][WARNING_ID]                                             = "[Warning]";
  strings_[ENGLISH_COL][ERROR_ID]                                               = "[Error]";
  strings_[ENGLISH_COL][DEBUG_ID]                                               = "[Debug]";
  strings_[ENGLISH_COL][NORMAL_ID]                                              = "";

  /// File

  strings_[ENGLISH_COL][LOG_FILE]                                               = "ngasp.log";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_DIM]                                                = "dim";
  strings_[ENGLISH_COL][CMD_DIM_ABB]                                            = "dim";
  strings_[ENGLISH_COL][CMD_DIM_DESC]                                           = "Creates variables of different types.";

  /// Command options

  strings_[ENGLISH_COL][DIM_NAME_SHORT]                                         = "n";
  strings_[ENGLISH_COL][DIM_NAME_LONG]                                          = "name";
  strings_[ENGLISH_COL][DIM_NAME_DESC]                                          = "Variable name.";

  strings_[ENGLISH_COL][DIM_AS_SHORT]                                           = "as";
  strings_[ENGLISH_COL][DIM_AS_LONG]                                            = "as";
  strings_[ENGLISH_COL][DIM_AS_DESC]                                            = "Variable type: ";

  strings_[ENGLISH_COL][DIM_RESERVED_NAME]                                      = "prefix name not allowed...";
  strings_[ENGLISH_COL][DIM_TYPE_UNKNOWN]                                       = "type could not be resolved...";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_CALC]                                               = "calc";
  strings_[ENGLISH_COL][CMD_CALC_ABB]                                           = "calc";
  strings_[ENGLISH_COL][CMD_CALC_DESC]                                          = "Defines calculations of different types.";

  /// Command options

  strings_[ENGLISH_COL][CALC_NAME_SHORT]                                        = "n";
  strings_[ENGLISH_COL][CALC_NAME_LONG]                                         = "name";
  strings_[ENGLISH_COL][CALC_NAME_DESC]                                         = "Calculation name.";

  strings_[ENGLISH_COL][CALC_AS_SHORT]                                          = "as";
  strings_[ENGLISH_COL][CALC_AS_LONG]                                           = "as";
  strings_[ENGLISH_COL][CALC_AS_DESC]                                           = "Calculation type: ";

  strings_[ENGLISH_COL][CALC_RESERVED_NAME]                                     = "prefix name not allowed...";
  strings_[ENGLISH_COL][CALC_TYPE_UNKNOWN]                                      = "type could not be resolved...";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_SET_VALUE]                                          = "set-value";
  strings_[ENGLISH_COL][CMD_SET_VALUE_ABB]                                      = "set";
  strings_[ENGLISH_COL][CMD_SET_VALUE_DESC]                                     = "This command assigns values to variables.";
  
  /// Command options

  strings_[ENGLISH_COL][SET_TO_SHORT]                                           = "t";
  strings_[ENGLISH_COL][SET_TO_LONG]                                            = "to";
  strings_[ENGLISH_COL][SET_TO_DESC]                                            = "Destination variable name.";

  strings_[ENGLISH_COL][SET_EQ_SHORT]                                           = "e";
  strings_[ENGLISH_COL][SET_EQ_LONG]                                            = "eq";
  strings_[ENGLISH_COL][SET_EQ_DESC]                                            = "Origin variable name.";

  strings_[ENGLISH_COL][SET_INC_SHORT]                                          = "a";
  strings_[ENGLISH_COL][SET_INC_LONG]                                           = "add";
  strings_[ENGLISH_COL][SET_INC_DESC]                                           = "Add this value to the destination variable.";

  strings_[ENGLISH_COL][SET_SUB_SHORT]                                          = "s";
  strings_[ENGLISH_COL][SET_SUB_LONG]                                           = "sub";
  strings_[ENGLISH_COL][SET_SUB_DESC]                                           = "Substracts this value from the destination variable.";

  strings_[ENGLISH_COL][SET_MUL_SHORT]                                          = "m";
  strings_[ENGLISH_COL][SET_MUL_LONG]                                           = "mul";
  strings_[ENGLISH_COL][SET_MUL_DESC]                                           = "Multiplies this value to the destination variable.";

  strings_[ENGLISH_COL][SET_DIV_SHORT]                                          = "d";
  strings_[ENGLISH_COL][SET_DIV_LONG]                                           = "div";
  strings_[ENGLISH_COL][SET_DIV_DESC]                                           = "Divides this value from the destination variable.";

  strings_[ENGLISH_COL][SET_VARIABLE_NOT_FOUND]                                 = " cannot be set...";
  strings_[ENGLISH_COL][CAST_NOT_DEVELOPED]                                     = " cast not developed...";
  strings_[ENGLISH_COL][SET_BAD_VALUE]                                          = " bad value...";

  strings_[ENGLISH_COL][GET_DISABLED]                                           = " cannot convert data...";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_APPEND]                                             = "matappend";
  strings_[ENGLISH_COL][CMD_APPEND_ABB]                                         = "matappend";
  strings_[ENGLISH_COL][CMD_APPEND_DESC]                                        = "This command appends a value, a vector or a matrix to a matrix.";
 
  /// Command options

  strings_[ENGLISH_COL][APPEND_TO_SHORT]                                        = "t";
  strings_[ENGLISH_COL][APPEND_TO_LONG]                                         = "to";
  strings_[ENGLISH_COL][APPEND_TO_DESC]                                         = "Destination matrix name.";

  strings_[ENGLISH_COL][APPEND_ADD_SHORT]                                       = "a";
  strings_[ENGLISH_COL][APPEND_ADD_LONG]                                        = "add";
  strings_[ENGLISH_COL][APPEND_ADD_DESC]                                        = "Origin scalar / vector / matrix variable name.";
  
  strings_[ENGLISH_COL][APPEND_INDEX_SHORT]                                     = "i";
  strings_[ENGLISH_COL][APPEND_INDEX_LONG]                                      = "index";
  strings_[ENGLISH_COL][APPEND_INDEX_DESC]                                      = "Identificator of the matrix row.";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_WITH]                                               = "with";
  strings_[ENGLISH_COL][CMD_WITH_ABB]                                           = "with";
  strings_[ENGLISH_COL][CMD_WITH_DESC]                                          = "Selects the memory object to use.";

  /// Command options

  strings_[ENGLISH_COL][WITH_NAME_SHORT]                                        = "n";
  strings_[ENGLISH_COL][WITH_NAME_LONG]                                         = "name";
  strings_[ENGLISH_COL][WITH_NAME_DESC]                                         = "Name of the memory object to be selected.";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_END_WITH]                                           = "end-with";
  strings_[ENGLISH_COL][CMD_END_WITH_ABB]                                       = "end-with";
  strings_[ENGLISH_COL][CMD_END_WITH_DESC]                                      = "End of a 'with' block.";

  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_FOREACH]                                            = "for";
  strings_[ENGLISH_COL][CMD_FOREACH_ABB]                                        = "for";
  strings_[ENGLISH_COL][CMD_FOREACH_DESC]                                       = "for";

  /// Command options

  strings_[ENGLISH_COL][FOREACH_DATA_SHORT]                                     = "";
  strings_[ENGLISH_COL][FOREACH_DATA_LONG]                                      = "data";
  strings_[ENGLISH_COL][FOREACH_DATA_DESC]                                      = "";

  strings_[ENGLISH_COL][FOREACH_NODE_SHORT]                                     = "";
  strings_[ENGLISH_COL][FOREACH_NODE_LONG]                                      = "ite";
  strings_[ENGLISH_COL][FOREACH_NODE_DESC]                                      = "";

  strings_[ENGLISH_COL][FOREACH_FROM_SHORT]                                     = "";
  strings_[ENGLISH_COL][FOREACH_FROM_LONG]                                      = "from";
  strings_[ENGLISH_COL][FOREACH_FROM_DESC]                                      = "";

  strings_[ENGLISH_COL][FOREACH_TO_SHORT]                                       = "";
  strings_[ENGLISH_COL][FOREACH_TO_LONG]                                        = "to";
  strings_[ENGLISH_COL][FOREACH_TO_DESC]                                        = "";

  strings_[ENGLISH_COL][FOREACH_INCREMENT_SHORT]                                = "";
  strings_[ENGLISH_COL][FOREACH_INCREMENT_LONG]                                 = "inc";
  strings_[ENGLISH_COL][FOREACH_INCREMENT_DESC]                                 = "Increment.";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_END_FOREACH]                                        = "end-for";
  strings_[ENGLISH_COL][CMD_END_FOREACH_ABB]                                    = "end-for";
  strings_[ENGLISH_COL][CMD_END_FOREACH_DESC]                                   = "end-for";

  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_PRINT]                                              = "print";
  strings_[ENGLISH_COL][CMD_PRINT_ABB]                                          = "p";
  strings_[ENGLISH_COL][CMD_PRINT_DESC]                                         = "Print memory information.";

  /// Command options

  strings_[ENGLISH_COL][PRINT_NAME_SHORT]                                       = "n";
  strings_[ENGLISH_COL][PRINT_NAME_LONG]                                        = "name";
  strings_[ENGLISH_COL][PRINT_NAME_DESC]                                        = "Name of the memory object to be printed.";

  strings_[ENGLISH_COL][PRINT_TEXT_SHORT]                                       = "t";
  strings_[ENGLISH_COL][PRINT_TEXT_LONG]                                        = "text";
  strings_[ENGLISH_COL][PRINT_TEXT_DESC]                                        = "Print user text.";
  strings_[ENGLISH_COL][PRINT_COLUMN_1]                                         = "Attribute";
  strings_[ENGLISH_COL][PRINT_COLUMN_2]                                         = "Type";
  strings_[ENGLISH_COL][PRINT_COLUMN_3]                                         = "Value";

  strings_[ENGLISH_COL][PRINT_MODE_NORMAL]                                      = "normal";
  strings_[ENGLISH_COL][PRINT_MODE_JSON]                                        = "json";
  strings_[ENGLISH_COL][PRINT_MODE_NGASP]                                       = "ngasp";
  strings_[ENGLISH_COL][PRINT_MODE_HTML]                                        = "english_html";
  strings_[ENGLISH_COL][PRINT_MODE_VALUE]                                       = "value";
  
  strings_[ENGLISH_COL][PRINT_MODE_SHORT]                                       = "m";
  strings_[ENGLISH_COL][PRINT_MODE_LONG]                                        = "mode";
  strings_[ENGLISH_COL][PRINT_MODE_DESC]                                        = strings_[ENGLISH_COL][PRINT_MODE_NORMAL] + ": value is shown in a table. " +
                                                                                strings_[ENGLISH_COL][PRINT_MODE_JSON] + ": value is shown as JSON format. " +
                                                                                strings_[ENGLISH_COL][PRINT_MODE_NGASP] + ": value is shown as a variable definition. " +
                                                                                strings_[ENGLISH_COL][PRINT_MODE_VALUE] + ": only the value is shown.";

  strings_[ENGLISH_COL][PRINT_EOL_SHORT]                                        = "e";
  strings_[ENGLISH_COL][PRINT_EOL_LONG]                                         = "eol";
  strings_[ENGLISH_COL][PRINT_EOL_DESC]                                         = "Writes an end of line at the end.";


  /// Output strings

  strings_[ENGLISH_COL][TABLE_LINE_SEPARATOR]                                   = "────────────────────────────────────────────────────────────────────────────────";
  strings_[ENGLISH_BN][TABLE_LINE_SEPARATOR]                                    = "--------------------------------------------------------------------------------";
  strings_[ENGLISH_HTML][TABLE_LINE_SEPARATOR]                                  = "<hr>";

  strings_[ENGLISH_COL][TABLE_COL_MARGIN]                                       = " ";
  strings_[ENGLISH_COL][TABLE_COL_SEPARATOR]                                    = " ";

  strings_[ENGLISH_COL][TABLE_TEXT_CUT]                                         = "...";
  strings_[ENGLISH_COL][TABLE_FIELD_SELECTED]                                   = "*";
  strings_[ENGLISH_COL][TABLE_UNIT_BYTES]                                       = " bytes";
  strings_[ENGLISH_COL][TABLE_UNIT_KB]                                          = " Kb.";
  strings_[ENGLISH_COL][TABLE_ARRAY_SEPARATOR]                                  = ",";  // Only one char
  strings_[ENGLISH_COL][TABLE_EMPTY_FIELD]                                      = "<EMPTY>";

  strings_[ENGLISH_COL][BOLD_START]                                             = "\033[1m";
  strings_[ENGLISH_COL][BOLD_END]                                               = "\033[0m";
  strings_[ENGLISH_COL][RED_START]                                              = "\033[1;31m";
  strings_[ENGLISH_COL][RED_END]                                                = "\033[0m";
  strings_[ENGLISH_COL][YELLOW_START]                                           = "\033[0;33m";
  strings_[ENGLISH_COL][YELLOW_END]                                             = "\033[0m";
  strings_[ENGLISH_COL][BLUE_START]                                             = "\033[1;34m";
  strings_[ENGLISH_COL][BLUE_END]                                               = "\033[0m";
  strings_[ENGLISH_COL][GREEN_START]                                            = "\033[0;32m";
  strings_[ENGLISH_COL][GREEN_END]                                              = "\033[0m";

  strings_[ENGLISH_BN][BOLD_START]                                              = "[EMPTY ME ON RUNTIME]";
  strings_[ENGLISH_BN][BOLD_END]                                                = "[EMPTY ME ON RUNTIME]";
  strings_[ENGLISH_BN][RED_START]                                               = "[EMPTY ME ON RUNTIME]";
  strings_[ENGLISH_BN][RED_END]                                                 = "[EMPTY ME ON RUNTIME]";
  strings_[ENGLISH_BN][YELLOW_START]                                            = "[EMPTY ME ON RUNTIME]";
  strings_[ENGLISH_BN][YELLOW_END]                                              = "[EMPTY ME ON RUNTIME]";
  strings_[ENGLISH_BN][BLUE_START]                                              = "[EMPTY ME ON RUNTIME]";
  strings_[ENGLISH_BN][BLUE_END]                                                = "[EMPTY ME ON RUNTIME]";
  strings_[ENGLISH_BN][GREEN_START]                                             = "[EMPTY ME ON RUNTIME]";
  strings_[ENGLISH_BN][GREEN_END]                                               = "[EMPTY ME ON RUNTIME]";

  strings_[ENGLISH_HTML][BOLD_START]                                            = "<b>";
  strings_[ENGLISH_HTML][BOLD_END]                                              = "</b>";
  strings_[ENGLISH_HTML][RED_START]                                             = "<font color='red'>";
  strings_[ENGLISH_HTML][RED_END]                                               = "</font>";
  strings_[ENGLISH_HTML][YELLOW_START]                                          = "<font color='yellow'>";
  strings_[ENGLISH_HTML][YELLOW_END]                                            = "</font>";
  strings_[ENGLISH_HTML][BLUE_START]                                            = "<font color='blue'>";
  strings_[ENGLISH_HTML][BLUE_END]                                              = "</font>";
  strings_[ENGLISH_HTML][GREEN_START]                                           = "<font color='green'>";
  strings_[ENGLISH_HTML][GREEN_END]                                             = "</font>";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_MEMORY_INFO]                                        = "memory-info";
  strings_[ENGLISH_COL][CMD_MEMORY_INFO_ABB]                                    = "mem";
  strings_[ENGLISH_COL][CMD_MEMORY_INFO_DESC]                                   = "This command shows information about all data manager objects in memory";

  /// Command options
  strings_[ENGLISH_COL][MEMORY_INFO_PRINT_MODE_SHORT]                           = "m";
  strings_[ENGLISH_COL][MEMORY_INFO_PRINT_MODE_LONG]                            = "mode";
  strings_[ENGLISH_COL][MEMORY_INFO_PRINT_MODE_DESC]                            = strings_[ENGLISH_COL][PRINT_MODE_NORMAL] + ": values are shown in a table. " +
                                                                                strings_[ENGLISH_COL][PRINT_MODE_JSON] + ": values are shown as JSON format. " +
                                                                                strings_[ENGLISH_COL][PRINT_MODE_NGASP] + ": Not used. " +
                                                                                strings_[ENGLISH_COL][PRINT_MODE_VALUE] + ": Not used.";


  strings_[ENGLISH_COL][MEMINFO_HEADER]                                         = "Memory Information";
  strings_[ENGLISH_COL][MEMINFO_FOOTER]                                         = "";
  strings_[ENGLISH_COL][MEMINFO_COL_1]                                          = "Name";
  strings_[ENGLISH_COL][MEMINFO_COL_2]                                          = "Type";
  strings_[ENGLISH_COL][MEMINFO_COL_3]                                          = "Size";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_STOP]                                               = "exit";
  strings_[ENGLISH_COL][CMD_STOP_ABB]                                           = "exit";
  strings_[ENGLISH_COL][CMD_STOP_DESC]                                          = "Stop the application while it is in stdin mode.";

  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_ADD]                                                = "add";
  strings_[ENGLISH_COL][CMD_ADD_ABB]                                            = "add";
  strings_[ENGLISH_COL][CMD_ADD_DESC]                                           = "This command adds a file to DM.";

  /// Command options

  strings_[ENGLISH_COL][ADD_FILE_NAME_SHORT]                                    = "i";
  strings_[ENGLISH_COL][ADD_FILE_NAME_LONG]                                     = "input";
  strings_[ENGLISH_COL][ADD_FILE_NAME_DESC]                                     = "Input file name.";

  strings_[ENGLISH_COL][ADD_NAME_SHORT]                                         = "n";
  strings_[ENGLISH_COL][ADD_NAME_LONG]                                          = "name";
  strings_[ENGLISH_COL][ADD_NAME_DESC]                                          = "Name of the object in Data Manager.";

  strings_[ENGLISH_COL][ADD_NUM_REGS_SHORT]                                     = "r";
  strings_[ENGLISH_COL][ADD_NUM_REGS_LONG]                                      = "regs";
  strings_[ENGLISH_COL][ADD_NUM_REGS_DESC]                                      = "Number of registers.";

  strings_[ENGLISH_COL][SYNTAX_EDITOR_SHORT]                                    = "e";
  strings_[ENGLISH_COL][SYNTAX_EDITOR_LONG]                                     = "editor";
  strings_[ENGLISH_COL][SYNTAX_EDITOR_DESC]                                     = "Editor name. (gedit)";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_IF]                                                 = "if";
  strings_[ENGLISH_COL][CMD_IF_ABB]                                             = "if";
  strings_[ENGLISH_COL][CMD_IF_DESC]                                            = "If.";

  /// Command options

  strings_[ENGLISH_COL][IF_REF_SHORT]                                           = "r";
  strings_[ENGLISH_COL][IF_REF_LONG]                                            = "ref";
  strings_[ENGLISH_COL][IF_REF_DESC]                                            = "Reference.";

  strings_[ENGLISH_COL][IF_EQ_SHORT]                                            = "e";
  strings_[ENGLISH_COL][IF_EQ_LONG]                                             = "eq";
  strings_[ENGLISH_COL][IF_EQ_DESC]                                             = "Equal to.";

  strings_[ENGLISH_COL][IF_NE_SHORT]                                            = "n";
  strings_[ENGLISH_COL][IF_NE_LONG]                                             = "ne";
  strings_[ENGLISH_COL][IF_NE_DESC]                                             = "Not equal to.";

  strings_[ENGLISH_COL][IF_LT_SHORT]                                            = "l";
  strings_[ENGLISH_COL][IF_LT_LONG]                                             = "lt";
  strings_[ENGLISH_COL][IF_LT_DESC]                                             = "Less than.";

  strings_[ENGLISH_COL][IF_GT_SHORT]                                            = "g";
  strings_[ENGLISH_COL][IF_GT_LONG]                                             = "gt";
  strings_[ENGLISH_COL][IF_GT_DESC]                                             = "Greater than.";

  strings_[ENGLISH_COL][IF_AND_SHORT]                                           = "&";
  strings_[ENGLISH_COL][IF_AND_LONG]                                            = "and";
  strings_[ENGLISH_COL][IF_AND_DESC]                                            = "and.";

  strings_[ENGLISH_COL][IF_OR_SHORT]                                            = "|";
  strings_[ENGLISH_COL][IF_OR_LONG]                                             = "or";
  strings_[ENGLISH_COL][IF_OR_DESC]                                             = "or.";

  strings_[ENGLISH_COL][IF_ERROR_1]                                             = "IF. Out of range error...";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_ELSE]                                               = "else";
  strings_[ENGLISH_COL][CMD_ELSE_ABB]                                           = "else";
  strings_[ENGLISH_COL][CMD_ELSE_DESC]                                          = "Else.";

  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_END_IF]                                             = "endif";
  strings_[ENGLISH_COL][CMD_END_IF_ABB]                                         = "endif";
  strings_[ENGLISH_COL][CMD_END_IF_DESC]                                        = "EndIf.";

  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_CONSTANT]                                           = "constant";
  strings_[ENGLISH_COL][CMD_CONSTANT_ABB]                                       = "const";
  strings_[ENGLISH_COL][CMD_CONSTANT_DESC]                                      = "constant.";

  /// Command options

  strings_[ENGLISH_COL][CONSTANT_NAME_SHORT]                                    = "n";
  strings_[ENGLISH_COL][CONSTANT_NAME_LONG]                                     = "name";
  strings_[ENGLISH_COL][CONSTANT_NAME_DESC]                                     = "Constant name.";

  strings_[ENGLISH_COL][CONSTANT_BY_SHORT]                                      = "b";
  strings_[ENGLISH_COL][CONSTANT_BY_LONG]                                       = "by";
  strings_[ENGLISH_COL][CONSTANT_BY_DESC]                                       = "Replace by.";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_RESERVE]                                            = "reserve";
  strings_[ENGLISH_COL][CMD_RESERVE_ABB]                                        = "reserve";
  strings_[ENGLISH_COL][CMD_RESERVE_DESC]                                       = "reserve.";

  /// Command options

  strings_[ENGLISH_COL][RESERVE_NAME_SHORT]                                     = "n";
  strings_[ENGLISH_COL][RESERVE_NAME_LONG]                                      = "name";
  strings_[ENGLISH_COL][RESERVE_NAME_DESC]                                      = "name";

  strings_[ENGLISH_COL][RESERVE_TABLES_SHORT]                                   = "t";
  strings_[ENGLISH_COL][RESERVE_TABLES_LONG]                                    = "tables";
  strings_[ENGLISH_COL][RESERVE_TABLES_DESC]                                    = "tables";

  strings_[ENGLISH_COL][RESERVE_REGS_SHORT]                                     = "r";
  strings_[ENGLISH_COL][RESERVE_REGS_LONG]                                      = "regs";
  strings_[ENGLISH_COL][RESERVE_REGS_DESC]                                      = "regs";

  strings_[ENGLISH_COL][RESERVE_LEN_SHORT]                                      = "l";
  strings_[ENGLISH_COL][RESERVE_LEN_LONG]                                       = "len";
  strings_[ENGLISH_COL][RESERVE_LEN_DESC]                                       = "len";

  strings_[ENGLISH_COL][RESERVE_DEFAULT_SHORT]                                  = "d";
  strings_[ENGLISH_COL][RESERVE_DEFAULT_LONG]                                   = "default";
  strings_[ENGLISH_COL][RESERVE_DEFAULT_DESC]                                   = "default value.";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_SYNTAX]                                             = "syntax";
  strings_[ENGLISH_COL][CMD_SYNTAX_ABB]                                         = "syntax";
  strings_[ENGLISH_COL][CMD_SYNTAX_DESC]                                        = "This command adds to your editor the capability of reading ngasp files.";

  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_SOCKET]                                             = "tcp";
  strings_[ENGLISH_COL][CMD_SOCKET_ABB]                                         = "tcp";
  strings_[ENGLISH_COL][CMD_SOCKET_DESC]                                        = "Sets the application in Local Manager Execution Mode. It can receive commands via TCP protocol.";

  /// Command options

  strings_[ENGLISH_COL][TCP_ADDRESS_SHORT]                                      = "i";
  strings_[ENGLISH_COL][TCP_ADDRESS_LONG]                                       = "ip";
  strings_[ENGLISH_COL][TCP_ADDRESS_DESC]                                       = "IP Address.";

  strings_[ENGLISH_COL][TCP_PORT_SHORT]                                         = "p";
  strings_[ENGLISH_COL][TCP_PORT_LONG]                                          = "port";
  strings_[ENGLISH_COL][TCP_PORT_DESC]                                          = "Port.";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_PIPE]                                               = "pipe";
  strings_[ENGLISH_COL][CMD_PIPE_ABB]                                           = "pipe";
  strings_[ENGLISH_COL][CMD_PIPE_DESC]                                          = "Sets the application in Worker Execution Mode. It can receive commands via named pipe.";

  /// Command options

  strings_[ENGLISH_COL][PIPE_NAME_SHORT]                                        = "n";
  strings_[ENGLISH_COL][PIPE_NAME_LONG]                                         = "name";
  strings_[ENGLISH_COL][PIPE_NAME_DESC]                                         = "Pipe name.";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_OUTPUT]                                             = "output";
  strings_[ENGLISH_COL][CMD_OUTPUT_ABB]                                         = "output";
  strings_[ENGLISH_COL][CMD_OUTPUT_DESC]                                        = "Stop the application while it is in stdin mode.";

  /// Command options

  strings_[ENGLISH_COL][OUTPUT_FILE_NAME_SHORT]                                 = "f";
  strings_[ENGLISH_COL][OUTPUT_FILE_NAME_LONG]                                  = "file";
  strings_[ENGLISH_COL][OUTPUT_FILE_NAME_DESC]                                  = "Redirect output to a file.";

  strings_[ENGLISH_COL][OUTPUT_SCREEN_SHORT]                                    = "s";
  strings_[ENGLISH_COL][OUTPUT_SCREEN_LONG]                                     = "screen";
  strings_[ENGLISH_COL][OUTPUT_SCREEN_DESC]                                     = "Redirect output to the screen.";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_EXEC]                                               = "execute";
  strings_[ENGLISH_COL][CMD_EXEC_ABB]                                           = "exec";
  strings_[ENGLISH_COL][CMD_EXEC_DESC]                                          = "This command executes an external application or system command.";

  /// Command options

  strings_[ENGLISH_COL][EXEC_WORKING_DIR_SHORT]                                 = "p";
  strings_[ENGLISH_COL][EXEC_WORKING_DIR_LONG]                                  = "path";
  strings_[ENGLISH_COL][EXEC_WORKING_DIR_DESC]                                  = "Working directory.";

  strings_[ENGLISH_COL][EXEC_APP_SHORT]                                         = "c";
  strings_[ENGLISH_COL][EXEC_APP_LONG]                                          = "command";
  strings_[ENGLISH_COL][EXEC_APP_DESC]                                          = "Command to be executed.";

  //strings_[ENGLISH_COL][EXEC_TYPE_APP]                                          = "application";
  strings_[ENGLISH_COL][EXEC_TYPE_SYS]                                          = "system";
  
  strings_[ENGLISH_COL][EXEC_TYPE_SHORT]                                        = "t";
  strings_[ENGLISH_COL][EXEC_TYPE_LONG]                                         = "type";
  strings_[ENGLISH_COL][EXEC_TYPE_DESC]                                         = strings_[ENGLISH_COL][EXEC_TYPE_SYS] + "."; //strings_[ENGLISH_COL][EXEC_TYPE_APP] + " / " + strings_[ENGLISH_COL][EXEC_TYPE_SYS] + ".";
  //@}
  //@{
  /// --------------------------------------------------------------------------
  strings_[ENGLISH_COL][CMD_SAVE_STATE]                                         = "save-state";
  strings_[ENGLISH_COL][CMD_SAVE_STATE_ABB]                                     = "save-state";
  strings_[ENGLISH_COL][CMD_SAVE_STATE_DESC]                                    = "This command saves the Data Manager data into file.";
  
  strings_[ENGLISH_COL][CMD_RESET]                                              = "reset-memory";
  strings_[ENGLISH_COL][CMD_RESET_ABB]                                          = "reset";
  strings_[ENGLISH_COL][CMD_RESET_DESC]                                         = "This command clears the system memory.";

    
  /// Command options

  strings_[ENGLISH_COL][SAVE_STATE_TO_FILE_SHORT]                               = "o";
  strings_[ENGLISH_COL][SAVE_STATE_TO_FILE_LONG]                                = "output";
  strings_[ENGLISH_COL][SAVE_STATE_TO_FILE_DESC]                                = "Output file.";
  //@}
  strings_[ENGLISH_COL][_COMMAND_LAST]                                          = "";  // *************************************

  //@{
  /// ==========================================================================
  /// Calculations
  /// ==========================================================================
  strings_[ENGLISH_COL][_CALC_FIRST]                                            = "";  // *************************************

  strings_[ENGLISH_COL][CALC_MSTATSPOP]                                         = "calc_mstatspop";
  strings_[ENGLISH_COL][CALC_MSTATSPOP_BRIEF_DESC]                              = "";
  strings_[ENGLISH_COL][CALC_MSTATSPOP_DESC]                                    = "This is the mstatspop calculation description.";

  strings_[ENGLISH_COL][CALC_OPTIMAL_TESTS]                                     = "optimal-tests";
  strings_[ENGLISH_COL][CALC_OPTIMAL_TESTS_BRIEF_DESC]                          = "";
  strings_[ENGLISH_COL][CALC_OPTIMAL_TESTS_DESC]                                = "This is the Optimal Tests calculation description.";

  strings_[ENGLISH_COL][CALC_R2]                                                = "r2";
  strings_[ENGLISH_COL][CALC_R2_BRIEF_DESC]                                     = "This is the R2 calculation description.";
  strings_[ENGLISH_COL][CALC_R2_DESC]                                           = "This is the R2 calculation description.";
  strings_[ENGLISH_COL][CALC_R2_IPARAM_1_NAME]                                  = "ploidy";
  strings_[ENGLISH_COL][CALC_R2_IPARAM_2_NAME]                                  = "vint_perpop_nsam";
  strings_[ENGLISH_COL][CALC_R2_IPARAM_3_NAME]                                  = "npops";
  strings_[ENGLISH_COL][CALC_R2_IPARAM_4_NAME]                                  = "matrix_pol";
  strings_[ENGLISH_COL][CALC_R2_IPARAM_5_NAME]                                  = "stats_S";
  strings_[ENGLISH_COL][CALC_R2_IPARAM_6_NAME]                                  = "stats_thetaT";
  strings_[ENGLISH_COL][CALC_R2_IPARAM_7_NAME]                                  = "length";
  strings_[ENGLISH_COL][CALC_R2_OPARAM_1_NAME]                                  = "stats_R2";

  
  strings_[ENGLISH_COL][CALC_R2P]                                               = "r2p";
  strings_[ENGLISH_COL][CALC_R2P_BRIEF_DESC]                                    = "";
  strings_[ENGLISH_COL][CALC_R2P_DESC]                                          = "This is the R2p calculation description.";

  strings_[ENGLISH_COL][CALC_FREQ_STATS]                                        = "freq_stats";
  strings_[ENGLISH_COL][CALC_FREQ_STATS_BRIEF_DESC]                             = "";
  strings_[ENGLISH_COL][CALC_FREQ_STATS_DESC]                                   = "This is the Frequency Statistics calculation description.";

  strings_[ENGLISH_COL][CALC_FILE_STATS]                                        = "file_stats";
  strings_[ENGLISH_COL][CALC_FILE_STATS_BRIEF_DESC]                             = "";
  strings_[ENGLISH_COL][CALC_FILE_STATS_DESC]                                   = "This is the MS File Statistics calculation description.";

  strings_[ENGLISH_COL][CALC_MISMATCH]                                          = "mismatch";
  strings_[ENGLISH_COL][CALC_MISMATCH_BRIEF_DESC]                               = "";
  strings_[ENGLISH_COL][CALC_MISMATCH_DESC]                                     = "This is the mismatch calculation description.";

  strings_[ENGLISH_COL][CALC_SXSFSS]                                            = "sxsfss";
  strings_[ENGLISH_COL][CALC_SXSFSS_BRIEF_DESC]                                 = "";
  strings_[ENGLISH_COL][CALC_SXSFSS_DESC]                                       = "This is the sxsfss calculation description.";

  strings_[ENGLISH_COL][CALC_JOINT_FREQ_DIST]                                   = "joint_freq_dist";
  strings_[ENGLISH_COL][CALC_JOINT_FREQ_DIST_BRIEF_DESC]                        = "";
  strings_[ENGLISH_COL][CALC_JOINT_FREQ_DIST_DESC]                              = "This is the Joint Frequency Distribution calculation description.";

  strings_[ENGLISH_COL][CALC_PIWPIAFST]                                         = "piwpiafst";
  strings_[ENGLISH_COL][CALC_PIWPIAFST_BRIEF_DESC]                              = "";
  strings_[ENGLISH_COL][CALC_PIWPIAFST_DESC]                                    = "This is the Piwpiafst calculation description.";

  strings_[ENGLISH_COL][CALC_HWHAFSTH]                                          = "hwhafsth";
  strings_[ENGLISH_COL][CALC_HWHAFSTH_BRIEF_DESC]                               = "";
  strings_[ENGLISH_COL][CALC_HWHAFSTH_DESC]                                     = "This is the Hwhafsth calculation description.";

  strings_[ENGLISH_COL][CALC_FS]                                                = "fs";
  strings_[ENGLISH_COL][CALC_FS_BRIEF_DESC]                                     = "";
  strings_[ENGLISH_COL][CALC_FS_DESC]                                           = "This is the Fs calculation description.";

  strings_[ENGLISH_COL][CALC_PERMUTE]                                           = "permute";
  strings_[ENGLISH_COL][CALC_PERMUTE_BRIEF_DESC]                                = "";
  strings_[ENGLISH_COL][CALC_PERMUTE_DESC]                                      = "This is the Permute calculation description.";

  strings_[ENGLISH_COL][CALC_DNAMATRIX2MATRIXPOL]                               = "dna_matrix_to_matrix_pol";
  strings_[ENGLISH_COL][CALC_DNAMATRIX2MATRIXPOL_BRIEF_DESC]                    = "";
  strings_[ENGLISH_COL][CALC_DNAMATRIX2MATRIXPOL_DESC]                          = "This is the dna_matrix_to_matrix_pol calculation description.";

  strings_[ENGLISH_COL][CALC_FASTA2DNAMATRIX]                                   = "fasta_to_dna_matrix";
  strings_[ENGLISH_COL][CALC_FASTA2DNAMATRIX_BRIEF_DESC]                        = "";
  strings_[ENGLISH_COL][CALC_FASTA2DNAMATRIX_DESC]                              = "This is the fasta_to_dna_matrix calculation description.";

  strings_[ENGLISH_COL][CALC_FASTA2TFASTA]                                      = "calc_fasta_to_tfasta";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_BRIEF_DESC]                           = "";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_DESC]                                 = "This calculation changes the file format from a Fasta file to a T-Fasta file.";

  strings_[ENGLISH_COL][CALC_CREATETFASTAANNOTATION]                            = "create_tfa";
  strings_[ENGLISH_COL][CALC_CREATETFASTAANNOTATION_BRIEF_DESC]                 = "";
  strings_[ENGLISH_COL][CALC_CREATETFASTAANNOTATION_DESC]                       = "It creates a TFasta Annotation file.";

  strings_[ENGLISH_COL][CALC_OPEN_FASTA]                                        = "open_fasta_file";
  strings_[ENGLISH_COL][CALC_OPEN_FASTA_BRIEF_DESC]                             = "";
  strings_[ENGLISH_COL][CALC_OPEN_FASTA_DESC]                                   = "This is the open_fasta_file calculation description.";

  strings_[ENGLISH_COL][CALC_OPEN_TFASTA]                                       = "open_tfasta_file";
  strings_[ENGLISH_COL][CALC_OPEN_TFASTA_BRIEF_DESC]                            = "";
  strings_[ENGLISH_COL][CALC_OPEN_TFASTA_DESC]                                  = "This is the open_tfasta_file calculation description.";
  
  strings_[ENGLISH_COL][CALC_GFF]                                               = "gff";
  strings_[ENGLISH_COL][CALC_GFF_BRIEF_DESC]                                    = "";
  strings_[ENGLISH_COL][CALC_GFF_DESC]                                          = "This is the gff calculation description.";

  strings_[ENGLISH_COL][CALC_MSTATSPOP_OPEN_FASTA]                              = "mstatspop_open_fasta";
  strings_[ENGLISH_COL][CALC_MSTATSPOP_OPEN_FASTA_BRIEF_DESC]                   = "";
  strings_[ENGLISH_COL][CALC_MSTATSPOP_OPEN_FASTA_DESC]                         = "This is the open fasta calculation description.";

  strings_[ENGLISH_COL][CALC_MSTATSPOP_OPEN_MS]                                 = "mstatspop_open_ms";
  strings_[ENGLISH_COL][CALC_MSTATSPOP_OPEN_MS_BRIEF_DESC]                      = "";
  strings_[ENGLISH_COL][CALC_MSTATSPOP_OPEN_MS_DESC]                            = "This is the open ms calculation description.";
  
  strings_[ENGLISH_COL][CALC_OPEN_FREQ_SPECTRUM]                                = "spectrum_file";
  strings_[ENGLISH_COL][CALC_OPEN_FREQ_SPECTRUM_BRIEF_DESC]                     = "";
  strings_[ENGLISH_COL][CALC_OPEN_FREQ_SPECTRUM_DESC]                           = "This is the open frequency spectrum file calculation description.";

  strings_[ENGLISH_COL][CALC_MASK_FILE_MS]                                      = "mask_file_ms";
  strings_[ENGLISH_COL][CALC_MASK_FILE_MS_BRIEF_DESC]                           = "";
  strings_[ENGLISH_COL][CALC_MASK_FILE_MS_DESC]                                 = "This is the ms calculation description.";

  strings_[ENGLISH_COL][CALC_EFFEC_NUC_TCGA_FREQS]                              = "effec_nuc_tcga_freqs";
  strings_[ENGLISH_COL][CALC_EFFEC_NUC_TCGA_FREQS_BRIEF_DESC]                   = "";
  strings_[ENGLISH_COL][CALC_EFFEC_NUC_TCGA_FREQS_DESC]                         = "This is the effective nucleotide TCGA frequencies calculation description.";

  strings_[ENGLISH_COL][CALC_X]                                                 = "calcx";
  strings_[ENGLISH_COL][CALC_X_BRIEF_DESC]                                      = "";
  strings_[ENGLISH_COL][CALC_X_DESC]                                            = "This is the X calculation description.";

  strings_[ENGLISH_COL][CALC_Y]                                                 = "calcy";
  strings_[ENGLISH_COL][CALC_Y_BRIEF_DESC]                                      = "";
  strings_[ENGLISH_COL][CALC_Y_DESC]                                            = "This is the Y calculation description.";

  strings_[ENGLISH_COL][CALC_Z]                                                 = "calcz";
  strings_[ENGLISH_COL][CALC_Z_BRIEF_DESC]                                      = "";
  strings_[ENGLISH_COL][CALC_Z_DESC]                                            = "This is the Z calculation description.";
    
  strings_[ENGLISH_COL][CALC_LENGTHAMNG]                                        = "lengthamng";
  strings_[ENGLISH_COL][CALC_LENGTHAMNG_BRIEF_DESC]                             = "";
  strings_[ENGLISH_COL][CALC_LENGTHAMNG_DESC]                                   = "This is the lengthman calculation description.";

  strings_[ENGLISH_COL][CALC_ARRAY_OPE_X]                                       = "array_ope_x";
  strings_[ENGLISH_COL][CALC_ARRAY_OPE_X_BRIEF_DESC]                            = "";
  strings_[ENGLISH_COL][CALC_ARRAY_OPE_X_DESC]                                  = "This is the array ope X calculation description.";

  strings_[ENGLISH_COL][CALC_MSTATSPOP_OUTPUT]                                  = "mstatspop_output";
  strings_[ENGLISH_COL][CALC_MSTATSPOP_OUTPUT_BRIEF_DESC]                       = "";
  strings_[ENGLISH_COL][CALC_MSTATSPOP_OUTPUT_DESC]                             = "This is the mstatspop output calculation description.";

  strings_[ENGLISH_COL][CALC_ARRAY_SUM_ALL]                                     = "array_sum_all";
  strings_[ENGLISH_COL][CALC_ARRAY_SUM_ALL_BRIEF_DESC]                          = "";
  strings_[ENGLISH_COL][CALC_ARRAY_SUM_ALL_DESC]                                = "This is the array sum all calculation description.";

  strings_[ENGLISH_COL][CALC_DUPLICATE_POPULATIONS]                             = "duplicate_populations";
  strings_[ENGLISH_COL][CALC_DUPLICATE_POPULATIONS_BRIEF_DESC]                  = "";
  strings_[ENGLISH_COL][CALC_DUPLICATE_POPULATIONS_DESC]                        = "This is the duplicate populations calculation description.";

  strings_[ENGLISH_COL][CALC_RANDOMIZE]                                         = "randomize";
  strings_[ENGLISH_COL][CALC_RANDOMIZE_BRIEF_DESC]                              = "";
  strings_[ENGLISH_COL][CALC_RANDOMIZE_DESC]                                    = "This is the randomize calculation description.";

  strings_[ENGLISH_COL][CALC_GCCONTENT]                                         = "calc_gc_content";
  strings_[ENGLISH_COL][CALC_GCCONTENT_BRIEF_DESC]                              = "";
  strings_[ENGLISH_COL][CALC_GCCONTENT_DESC]                                    = "GC_content (or guanine-cytosine content) is the percentage of nitrogenous bases on a DNA molecule that are either guanine or cytosine. GC content is usually expressed as a percentage value, but sometimes as a ratio.";

  strings_[ENGLISH_COL][CALC_OPEN_EFFECTSIZES]                                  = "open_effect_sizes_file";
  strings_[ENGLISH_COL][CALC_OPEN_EFFECTSIZES_BRIEF_DESC]                       = "";
  strings_[ENGLISH_COL][CALC_OPEN_EFFECTSIZES_DESC]                             = "Description.";
    
  strings_[ENGLISH_COL][CALC_OPEN_COORDINATES]                                  = "open_coordinates_file";
  strings_[ENGLISH_COL][CALC_OPEN_COORDINATES_BRIEF_DESC]                       = "";
  strings_[ENGLISH_COL][CALC_OPEN_COORDINATES_DESC]                             = "Description.";
    
  strings_[ENGLISH_COL][CALC_OPEN_WEIGHTPOSITIONS]                              = "open_weight_positions_file";
  strings_[ENGLISH_COL][CALC_OPEN_WEIGHTPOSITIONS_BRIEF_DESC]                   = "";
  strings_[ENGLISH_COL][CALC_OPEN_WEIGHTPOSITIONS_DESC]                         = "Description.";

  strings_[ENGLISH_COL][CALC_EXEC]                                              = "calc_execute";
  strings_[ENGLISH_COL][CALC_EXEC_BRIEF_DESC]                                   = "Execute";
  strings_[ENGLISH_COL][CALC_EXEC_DESC]                                         = "This calculation is used for running external applications or system commands.";
  
  strings_[ENGLISH_COL][CALC_BCF2VCF]                                           = "BCD_To_VCF";
  strings_[ENGLISH_COL][CALC_BCF2VCF_BRIEF_DESC]                                = "";
  strings_[ENGLISH_COL][CALC_BCF2VCF_DESC]                                      = "BCF To VCF Conversor.";

  strings_[ENGLISH_COL][CALC_BAM2BAI]                                           = "calc_create_bam_index";
  strings_[ENGLISH_COL][CALC_BAM2BAI_BRIEF_DESC]                                = "Create BAM Index";
  strings_[ENGLISH_COL][CALC_BAM2BAI_DESC]                                      = "This calculation creates the index of a BAM file (a BAI file).";
  
  strings_[ENGLISH_COL][CALC_GET_SEQ_LEN]                                       = "calc_get_seq_len";
  strings_[ENGLISH_COL][CALC_GET_SEQ_LEN_BRIEF_DESC]                            = "Get Sequence Length";
  strings_[ENGLISH_COL][CALC_GET_SEQ_LEN_DESC]                                  = "This calculation gets a Fasta file and it returns its first sequence's length.";

  strings_[ENGLISH_COL][CALC_GET_MRD]                                           = "calc_get_mrd";
  strings_[ENGLISH_COL][CALC_GET_MRD_BRIEF_DESC]                                = "Mean Read Depth";
  strings_[ENGLISH_COL][CALC_GET_MRD_DESC]                                      = "This calculation gets a list of BAM files and it returns a list of MRD.";

  strings_[ENGLISH_COL][CALC_BAM2MPILEUP]                                       = "calc_BAM_to_Mpileup";
  strings_[ENGLISH_COL][CALC_BAM2MPILEUP_BRIEF_DESC]                            = "BAM To Mpileup";
  strings_[ENGLISH_COL][CALC_BAM2MPILEUP_DESC]                                  = "This calculation changes the file format from a BAM file To a Mpileup file.";

  strings_[ENGLISH_COL][CALC_BAM_CHROMOSOMES]                                   = "bam_chromosomes"; // Desactivated  (I removed the "calc_") because it already exists the same calculation : "calc_get_chrom"
  strings_[ENGLISH_COL][CALC_BAM_CHROMOSOMES_BRIEF_DESC]                        = "BAM Chromosomes";
  strings_[ENGLISH_COL][CALC_BAM_CHROMOSOMES_DESC]                              = "This calculation gets a BAM file and it returns a list of its chromosomes.";

  
  strings_[ENGLISH_COL][CALC_SAM2MPILEUP]                                       = "SAM_to_Mpileup";
  strings_[ENGLISH_COL][CALC_SAM2MPILEUP_BRIEF_DESC]                            = "SAM To Mpileup";
  strings_[ENGLISH_COL][CALC_SAM2MPILEUP_DESC]                                  = "SAM To Mpileup Conversor.";
  
  strings_[ENGLISH_COL][CALC_SNIPCALLER]                                        = "calc_snp_caller";
  strings_[ENGLISH_COL][CALC_SNIPCALLER_BRIEF_DESC]                             = "SNP Caller";
  strings_[ENGLISH_COL][CALC_SNIPCALLER_DESC]                                   = "This calculation in a wrapper that calls the GH Caller external tool.";

  strings_[ENGLISH_COL][CALC_CONCAT_FILES]                                      = "calc_concat_text_files";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_BRIEF_DESC]                           = "Concat Text Files";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_DESC]                                 = "This calculation concatenates two text files. Depending on the given parameters, the operation done is: 1: output = input1 + input2. 2: output = output + input1. 3: output = output + input2.";

  strings_[ENGLISH_COL][CALC_CONCAT_FILE_NAMES]                                 = "calc_concat_file_names";
  strings_[ENGLISH_COL][CALC_CONCAT_FILE_NAMES_BRIEF_DESC]                      = "";
  strings_[ENGLISH_COL][CALC_CONCAT_FILE_NAMES_DESC]                            = "This calculation concatenates names of files. If File 2 is null then Output Names is += File 1. Else, Output Names = File 1 + File 2.";

  strings_[ENGLISH_COL][CALC_GET_FILE_NAME]                                     = "calc_get_file_name";
  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_BRIEF_DESC]                          = "";
  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_DESC]                                = "This calculation gets a File Node and returns only its file name. Its is placed, sometimes, in the middle of a File type node and an String type calculation input for conversion purposes.";

  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS]                                    = "calc_concat_strings";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_BRIEF_DESC]                         = "";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_DESC]                               = "This calculation concatenates two strings. output = intput 1 + input 2.";
  
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS]                              = "calc_collect_data_columns";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_BRIEF_DESC]                   = "";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_DESC]                         = "This calculation is a wrapper that calls the calc_collect_data_columns external tool for filtering the output of the mstatspop calculation output file.";
  
  strings_[ENGLISH_COL][CALC_BOX_PLOT_VALUES]                                   = "calc_boxplot_values";
  strings_[ENGLISH_COL][CALC_BOX_PLOT_VALUES_BRIEF_DESC]                        = "";
  strings_[ENGLISH_COL][CALC_BOX_PLOT_VALUES_DESC]                              = "This calculation receives an array and it returns boxplot values.";
  
  strings_[ENGLISH_COL][CALC_VCF2GFASTA]                                        = "calc_gVCF_to_tFasta";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_BRIEF_DESC]                             = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_DESC]                                   = "This calculation changes the file format from a gVCF file To a T-Fasta file.";

  strings_[ENGLISH_COL][CALC_NPSTAT]                                            = "calc_npstat";
  strings_[ENGLISH_COL][CALC_NPSTAT_BRIEF_DESC]                                 = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_DESC]                                       = "This calculation is a wrapper that calls the npstat external tool.";

  strings_[ENGLISH_COL][CALC_CUT_BED]                                           = "calc_filter_BED";
  strings_[ENGLISH_COL][CALC_CUT_BED_BRIEF_DESC]                                = "";
  strings_[ENGLISH_COL][CALC_CUT_BED_DESC]                                      = "This calculation cuts a BED file.";

  strings_[ENGLISH_COL][CALC_CUT_GTF]                                           = "calc_filter_GTF";
  strings_[ENGLISH_COL][CALC_CUT_GTF_BRIEF_DESC]                                = "";
  strings_[ENGLISH_COL][CALC_CUT_GTF_DESC]                                      = "This calculation cuts a GTF file.";

  strings_[ENGLISH_COL][CALC_GET_CHROM]                                         = "calc_get_chrom";
  strings_[ENGLISH_COL][CALC_GET_CHROM_BRIEF_DESC]                              = "";
  strings_[ENGLISH_COL][CALC_GET_CHROM_DESC]                                    = "Get chromosome names from BAM file (slower) or BAI file (faster).";
  
  strings_[ENGLISH_COL][CALC_EXAMPLE]                                           = "calc_example";
  strings_[ENGLISH_COL][CALC_EXAMPLE_BRIEF_DESC]                                = "";
  strings_[ENGLISH_COL][CALC_EXAMPLE_DESC]                                      = "This is a calculation for debugging purposes.";
  
  strings_[ENGLISH_COL][CALC_LIST_FILES]                                        = "calc_list_files";
  strings_[ENGLISH_COL][CALC_LIST_FILES_BRIEF_DESC]                             = "";
  strings_[ENGLISH_COL][CALC_LIST_FILES_DESC]                                   = "This calculation gets a folder name and it returns a list of files.";
    
  strings_[ENGLISH_COL][CALC_MATRIX2VECTOR]                                     = "calc_matrix_to_vector";
  strings_[ENGLISH_COL][CALC_MATRIX2VECTOR_BRIEF_DESC]                          = "";
  strings_[ENGLISH_COL][CALC_MATRIX2VECTOR_DESC]                                = "This calculation gets a matrix (sometimes an output matrix from a pipeline) and it returns the desired row or column as a Vector type.";

  strings_[ENGLISH_COL][CALC_SPLIT_BAM]                                         = "calc_split_BAM";
  strings_[ENGLISH_COL][CALC_SPLIT_BAM_BRIEF_DESC]                              = "";
  strings_[ENGLISH_COL][CALC_SPLIT_BAM_DESC]                                    = "This calculation gets one BAM file and it splites this file into n BAM files. One BAM file per chromosome.";
    
  strings_[ENGLISH_COL][_CALC_LAST]                                             = "";  // *************************************
  //@}

  strings_[ENGLISH_COL][CCALCCUT_BED_INPUT_BED_FILE]                            = "BED file";
  strings_[ENGLISH_COL][CCALCCUT_BED_INPUT_BED_FILE_DESC]                       = "Input BED file";
  strings_[ENGLISH_COL][CCALCCUT_BED_SELECTION]                                 = "Selection";
  strings_[ENGLISH_COL][CCALCCUT_BED_SELECTION_DESC]                            = "Selection";
  strings_[ENGLISH_COL][CCALCCUT_BED_INPUT_SORTED]                                 = "Input Sorted";
  strings_[ENGLISH_COL][CCALCCUT_BED_INPUT_SORTED_DESC]                            = "If input is sorted, the filtering is done faster.";
  strings_[ENGLISH_COL][CCALCCUT_BED_INPUT_SORTED_DEFV]                            = "False";
  strings_[ENGLISH_COL][CCALCCUT_BED_OUTPUT_BED_FILE]                           = "BED file";
  strings_[ENGLISH_COL][CCALCCUT_BED_OUTPUT_BED_FILE_DESC]                      = "Output BED file";
  strings_[ENGLISH_COL][CCALCCUT_BED_OUTPUT_BED_FILE_DEFV]                      = "";
    
  strings_[ENGLISH_COL][CCALCCUT_GTF_INPUT_GTF_FILE]                            = "GTF file";
  strings_[ENGLISH_COL][CCALCCUT_GTF_INPUT_GTF_FILE_DESC]                       = "Input GTF file";
  strings_[ENGLISH_COL][CCALCCUT_GTF_SELECTION]                                 = "Selection";
  strings_[ENGLISH_COL][CCALCCUT_GTF_SELECTION_DESC]                            = "Selection";
  strings_[ENGLISH_COL][CCALCCUT_GTF_INPUT_SORTED]                                 = "Input Sorted";
  strings_[ENGLISH_COL][CCALCCUT_GTF_INPUT_SORTED_DESC]                            = "If input is sorted, the filtering is done faster.";
  strings_[ENGLISH_COL][CCALCCUT_GTF_INPUT_SORTED_DEFV]                            = "False";
  strings_[ENGLISH_COL][CCALCCUT_GTF_OUTPUT_GTF_FILE]                           = "GTF file";
  strings_[ENGLISH_COL][CCALCCUT_GTF_OUTPUT_GTF_FILE_DESC]                      = "Output GTF file";
  
  strings_[ENGLISH_COL][CCALCGET_CHROM_INPUT_BAM]                               = "BAM File";
  strings_[ENGLISH_COL][CCALCGET_CHROM_INPUT_BAM_DESC]                          = "Input BAM File";
  strings_[ENGLISH_COL][CCALCGET_CHROM_INPUT_BAI]                               = "BAI File";
  strings_[ENGLISH_COL][CCALCGET_CHROM_INPUT_BAI_DESC]                          = "Input BAI File";
  strings_[ENGLISH_COL][CCALCGET_CHROM_CRHOM_NAMES]                             = "Chromosomes";
  strings_[ENGLISH_COL][CCALCGET_CHROM_CRHOM_NAMES_DESC]                        = "Chromosome Names";
      
      
  strings_[ENGLISH_COL][CCALCEXAMPLE_INPUT]                                     = "Input Value";
  strings_[ENGLISH_COL][CCALCEXAMPLE_INPUT_DESC]                                = "Set this value to 9999 and you will get example output data.";
 
  
  strings_[ENGLISH_COL][CCALCBOXPLOTVALUES_ARRAY]                               = "Array";
  strings_[ENGLISH_COL][CCALCBOXPLOTVALUES_Q1]                                  = "Q1";
  strings_[ENGLISH_COL][CCALCBOXPLOTVALUES_MEDIAN]                              = "Q2 Median";
  strings_[ENGLISH_COL][CCALCBOXPLOTVALUES_Q3]                                  = "Q3";
  strings_[ENGLISH_COL][CCALCBOXPLOTVALUES_MIN]                                 = "Min";
  strings_[ENGLISH_COL][CCALCBOXPLOTVALUES_MAX]                                 = "Max";
  strings_[ENGLISH_COL][CCALCBOXPLOTVALUES_OUTLIERS  ]                          = "Outliers";
  
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_BAM_FILES]                             = "BAM File";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_BAM_FILES_LONG]                        = "Path and name of the input BAM file";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_BAM_FILES_DESC]                        = ""; // BAM files separated by coma";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_BAM_FILES_SAMP]                        = ""; // ./data/file1.bam,./data/file2.bam,./data/file3.bam";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_BAM_FILES_ONLY]                        = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_BAM_FILES_DEFV]                        = "";
    
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_FASTA_REF]                             = "Fasta Reference";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_FASTA_REF_LONG]                        = "Path and name of yhe reference fasta file";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_FASTA_REF_DESC]                        = "Fasta file reference";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_FASTA_REF_SAMP]                        = "./data/reference.fa";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_FASTA_REF_ONLY]                        = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_FASTA_REF_DEFV]                        = "";

  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MIN_MQ]                                = "Min MQ";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MIN_MQ_LONG]                           = "Min MQ";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MIN_MQ_DESC]                           = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MIN_MQ_SAMP]                           = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MIN_MQ_ONLY]                           = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MIN_MQ_DEFV]                           = "";

  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MIN_BQ]                                = "Min BQ";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MIN_BQ_LONG]                           = "Min BQ";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MIN_BQ_DESC]                           = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MIN_BQ_SAMP]                           = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MIN_BQ_ONLY]                           = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MIN_BQ_DEFV]                           = "";

  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_DISABLE_BAQ]                                = "Disable BAQ";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_DISABLE_BAQ_LONG]                           = "Disable BAQ";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_DISABLE_BAQ_DESC]                           = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_DISABLE_BAQ_SAMP]                           = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_DISABLE_BAQ_ONLY]                           = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_DISABLE_BAQ_DEFV]                           = "";

  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_FILTER]                                = "Chromosome";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_FILTER_LONG]                           = "Chromosome";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_FILTER_DESC]                           = "Chromosome";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_FILTER_SAMP]                           = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_FILTER_ONLY]                           = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_FILTER_DEFV]                           = "";
  
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MPILEUP_FILE]                          = "Mpileup File";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MPILEUP_FILE_LONG]                     = "Path and name of the Mpileup output file";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MPILEUP_FILE_DESC]                     = "Mpileup file name";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MPILEUP_FILE_SAMP]                     = "./data/output.mpileup";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MPILEUP_FILE_ONLY]                     = "";
  strings_[ENGLISH_COL][CCALCBAM2MPILEUP_MPILEUP_FILE_DEFV]                     = "";
  
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_FILE_1]                               = "First Input File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_FILE_1_LONG]                          = "First Input File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_FILE_1_DESC]                          = "First Input File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_FILE_1_SAMP]                          = "./data/file_1.fa";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_FILE_1_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_FILE_1_DEFV]                          = "";

  strings_[ENGLISH_COL][CALC_CONCAT_FILES_FILE_2]                               = "Second Input File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_FILE_2_LONG]                          = "Second Input File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_FILE_2_DESC]                          = "Second Input File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_FILE_2_SAMP]                          = "./data/file_2.fa";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_FILE_2_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_FILE_2_DEFV]                          = "";

  strings_[ENGLISH_COL][CALC_CONCAT_FILES_OUTPUT]                               = "Output File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_OUTPUT_LONG]                          = "Output File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_OUTPUT_DESC]                          = "Concatenation of the first and second files.";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_OUTPUT_SAMP]                          = "./data/output_file.txt";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_OUTPUT_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_CONCAT_FILES_OUTPUT_DEFV]                          = "";


  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_FILE_1]                              = "File";
  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_FILE_1_LONG]                         = "File";
  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_FILE_1_DESC]                         = "";
  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_FILE_1_SAMP]                         = "";
  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_FILE_1_ONLY]                         = "";
  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_FILE_1_DEFV]                         = "";

  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_NAME]                                = "File Name";
  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_NAME_LONG]                           = "File Name";
  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_NAME_DESC]                           = "";
  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_NAME_SAMP]                           = "";
  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_NAME_ONLY]                           = "";
  strings_[ENGLISH_COL][CALC_GET_FILE_NAME_NAME_DEFV]                           = "";


  strings_[ENGLISH_COL][CALC_BAM2BAI_BAM]                                       = "BAM File";
  strings_[ENGLISH_COL][CALC_BAM2BAI_BAM_LONG]                                  = "Input BAM File";
  strings_[ENGLISH_COL][CALC_BAM2BAI_BAM_DESC]                                  = "";
  strings_[ENGLISH_COL][CALC_BAM2BAI_BAM_SAMP]                                  = "";
  strings_[ENGLISH_COL][CALC_BAM2BAI_BAM_ONLY]                                  = "";
  strings_[ENGLISH_COL][CALC_BAM2BAI_BAM_DEFV]                                  = "";

  strings_[ENGLISH_COL][CALC_BAM2BAI_BAI]                                       = "BAI File";
  strings_[ENGLISH_COL][CALC_BAM2BAI_BAI_LONG]                                  = "Ouput BAI File";
  strings_[ENGLISH_COL][CALC_BAM2BAI_BAI_DESC]                                  = "";
  strings_[ENGLISH_COL][CALC_BAM2BAI_BAI_SAMP]                                  = "";
  strings_[ENGLISH_COL][CALC_BAM2BAI_BAI_ONLY]                                  = "";
  strings_[ENGLISH_COL][CALC_BAM2BAI_BAI_DEFV]                                  = "";

  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_FILE_1]                               = "First Input File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_FILE_1_LONG]                          = "First Input File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_FILE_1_DESC]                          = "First Input File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_FILE_1_SAMP]                          = "./data/file_1.fa";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_FILE_1_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_FILE_1_DEFV]                          = "";

  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_FILE_2]                               = "Second Input File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_FILE_2_LONG]                          = "Second Input File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_FILE_2_DESC]                          = "Second Input File";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_FILE_2_SAMP]                          = "./data/file_2.fa";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_FILE_2_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_FILE_2_DEFV]                          = "";

  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_OUTPUT]                               = "Output File Names";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_OUTPUT_LONG]                          = "Output File Names";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_OUTPUT_DESC]                          = "Output string vector with file names.";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_OUTPUT_SAMP]                          = "./data/file_1.fa,./data/file_2.fa";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_OUTPUT_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_CONCAT_FILEN_OUTPUT_DEFV]                          = "";

  
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_1]                               = "First String";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_1_LONG]                          = "First String";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_1_DESC]                          = "First String";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_1_SAMP]                          = "";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_1_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_1_DEFV]                          = "";

  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_2]                               = "Second String";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_2_LONG]                          = "Second String";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_2_DESC]                          = "Second String";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_2_SAMP]                          = "";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_2_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_2_DEFV]                          = "";

  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_OUTPUT]                               = "Output String";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_OUTPUT_LONG]                          = "Output String";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_OUTPUT_DESC]                          = "Concatenation of the first and second String.";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_OUTPUT_SAMP]                          = "";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_OUTPUT_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_CONCAT_STRINGS_OUTPUT_DEFV]                          = "";

  
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_STATS_FILE]                   = "Statistics File";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_STATS_FILE_LONG]              = "Statistics File";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_STATS_FILE_DESC]              = "This is the mstatspop's statistics file.";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_STATS_FILE_SAMP]              = "./data/statistics.txt";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_STATS_FILE_ONLY]              = "Only for mstatspop's output file.";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_STATS_FILE_DEFV]              = "";
                     
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_REQ_COLUMNS_FILE]             = "Required Columns File";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_REQ_COLUMNS_FILE_LONG]        = "Required Columns File";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_REQ_COLUMNS_FILE_DESC]        = "This file contains the names of the required columns";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_REQ_COLUMNS_FILE_SAMP]        = "./data/required_columns.txt";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_REQ_COLUMNS_FILE_ONLY]        = "";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_REQ_COLUMNS_FILE_DEFV]        = "";

  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_FIL_STATS_FILE]               = "Filtered Statistics File";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_FIL_STATS_FILE_LONG]          = "Filtered Statistics File";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_FIL_STATS_FILE_DESC]          = "This is the mstatspop's statistics file filtered by some columns";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_FIL_STATS_FILE_SAMP]          = "";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_FIL_STATS_FILE_ONLY]          = "";
  strings_[ENGLISH_COL][CALC_COLLECT_DATA_COLUMNS_FIL_STATS_FILE_DEFV]          = "";

  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_INPUT]                                = "Fasta File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_INPUT_LONG]                           = "Input Fasta File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_INPUT_DESC]                           = "Input Fasta File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_INPUT_SAMP]                           = "./data/input.fa";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_INPUT_ONLY]                           = "";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_INPUT_DEFV]                           = "";

  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_GTF]                                  = "GTF File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_GTF_LONG]                             = "Input GTF File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_GTF_DESC]                             = "Input GTF File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_GTF_SAMP]                             = "./data/annotation.gtf";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_GTF_ONLY]                             = "";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_GTF_DEFV]                             = "";
  
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_BED]                                  = "BED File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_BED_LONG]                             = "Input BED File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_BED_DESC]                             = "Input BED File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_BED_SAMP]                             = "./data/masking.bed";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_BED_ONLY]                             = "";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_BED_DEFV]                             = "";
  
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_SAMPLES_ORDER]                        = "Samples Order";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_SAMPLES_ORDER_LONG]                   = "Samples Order";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_SAMPLES_ORDER_DESC]                   = "Number order of first sample, number 0 is the first sample] [second sample] ...etc.";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_SAMPLES_ORDER_SAMP]                   = "21 0 1 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 2 3 20";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_SAMPLES_ORDER_ONLY]                   = "";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_SAMPLES_ORDER_DEFV]                   = "";

  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_COMPRESS_OUT]                         = "Compress Output";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_COMPRESS_OUT_LONG]                    = "Compress Output";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_COMPRESS_OUT_DESC]                    = "";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_COMPRESS_OUT_SAMP]                    = "";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_COMPRESS_OUT_ONLY]                    = "";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_COMPRESS_OUT_DEFV]                    = "False";

  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_OUTPUT]                               = "Transposed Fasta File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_OUTPUT_LONG]                          = "Output T-Fasta File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_OUTPUT_DESC]                          = "Output Transposed Fasta File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_OUTPUT_SAMP]                          = "";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_OUTPUT_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_OUTPUT_DEFV]                          = "";
  
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_WEIGHTS]                              = "Weights File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_WEIGHTS_LONG]                         = "Output Weights File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_WEIGHTS_DESC]                         = "Output Weights File";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_WEIGHTS_SAMP]                         = "";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_WEIGHTS_ONLY]                         = "";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_WEIGHTS_DEFV]                         = "";  
  
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_SCAFFOLD_NAME]                        = "Scaffold Names";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_SCAFFOLD_NAME_LONG]                   = "scaffold-name";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_SCAFFOLD_NAME_DESC]                   = "Input list of scaffold names:";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_SCAFFOLD_NAME_EXAMPLE]                = "chr10,chr12,chr14";
  strings_[ENGLISH_COL][CALC_FASTA2TFASTA_SCAFFOLD_NAME_DEF_VAL]                = "";

  strings_[ENGLISH_COL][CALC_SNP_CALLER_MPILEUP]                                = "Mpileup File";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MPILEUP_LONG]                           = "Input Mpileup";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MPILEUP_DESC]                           = "Input Mpileup";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MPILEUP_SAMP]                           = "./data/input.mpileup";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MPILEUP_ONLY]                           = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MPILEUP_DEFV]                           = "";

  strings_[ENGLISH_COL][CALC_SNP_CALLER_BASEQ]                                  = "baseq";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_BASEQ_LONG]                             = "Base Quality";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_BASEQ_DESC]                             = "Minimum base quality of reads. Reads below threshold are discarded.";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_BASEQ_SAMP]                             = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_BASEQ_ONLY]                             = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_BASEQ_DEFV]                             = "20";

  strings_[ENGLISH_COL][CALC_SNP_CALLER_MINDEP]                                 = "mindep";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MINDEP_LONG]                            = "Minimum Reads";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MINDEP_DESC]                            = "Minimum number of reads. Sites below threshold are coded missing.";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MINDEP_SAMP]                            = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MINDEP_ONLY]                            = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MINDEP_DEFV]                            = "3";

  strings_[ENGLISH_COL][CALC_SNP_CALLER_MAXDEP]                                 = "maxdep";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MAXDEP_LONG]                            = "Maximum Reads";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MAXDEP_DESC]                            = "Maximum number of reads. Sites above threshold are coded missing.";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MAXDEP_SAMP]                            = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MAXDEP_ONLY]                            = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MAXDEP_DEFV]                            = "100";

  strings_[ENGLISH_COL][CALC_SNP_CALLER_MRD]                                    = "mrd";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MRD_LONG]                               = "Mean Read Depth";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MRD_DESC]                               = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MRD_SAMP]                               = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MRD_ONLY]                               = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_MRD_DEFV]                               = "";

  strings_[ENGLISH_COL][CALC_SNP_CALLER_PLATFORM]                               = "Platform";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_PLATFORM_LONG]                          = "Platform";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_PLATFORM_DESC]                          = "Offset to convert base qualities.";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_PLATFORM_SAMP]                          = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_PLATFORM_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_PLATFORM_DEFV]                          = "33";

  strings_[ENGLISH_COL][CALC_SNP_CALLER_OUTGROUP]                               = "Outgroup";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_OUTGROUP_LONG]                          = "Outgroup";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_OUTGROUP_DESC]                          = "Sequence file in fasta format to add to output alignment.";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_OUTGROUP_SAMP]                          = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_OUTGROUP_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_OUTGROUP_DEFV]                          = "none";

  strings_[ENGLISH_COL][CALC_SNP_CALLER_NAMES]                                  = "Names";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_NAMES_LONG]                             = "Names";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_NAMES_DESC]                             = "Comma-separated list of individuals' names, in same order as input.";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_NAMES_SAMP]                             = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_NAMES_ONLY]                             = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_NAMES_DEFV]                             = "";

  strings_[ENGLISH_COL][CALC_SNP_CALLER_FASTA]                                  = "Fasta File";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_FASTA_LONG]                             = "Output Fasta File";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_FASTA_DESC]                             = "Output Fasta File";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_FASTA_SAMP]                             = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_FASTA_ONLY]                             = "";
  strings_[ENGLISH_COL][CALC_SNP_CALLER_FASTA_DEFV]                             = "";


  strings_[ENGLISH_COL][CALC_GCCONTENT_VECTOR]                                  = "Vector";
  strings_[ENGLISH_COL][CALC_GCCONTENT_VECTOR_LONG]                             = "Vector";
  strings_[ENGLISH_COL][CALC_GCCONTENT_VECTOR_DESC]                             = "Vector";
  strings_[ENGLISH_COL][CALC_GCCONTENT_VECTOR_SAMP]                             = "";
  strings_[ENGLISH_COL][CALC_GCCONTENT_VECTOR_ONLY]                             = "";
  strings_[ENGLISH_COL][CALC_GCCONTENT_VECTOR_DEFV]                             = "";  

  strings_[ENGLISH_COL][CALC_GCCONTENT_PERCENTAGE]                              = "Percentage";
  strings_[ENGLISH_COL][CALC_GCCONTENT_PERCENTAGE_LONG]                         = "Percentage";
  strings_[ENGLISH_COL][CALC_GCCONTENT_PERCENTAGE_DESC]                         = "Percentage";
  strings_[ENGLISH_COL][CALC_GCCONTENT_PERCENTAGE_SAMP]                         = "";
  strings_[ENGLISH_COL][CALC_GCCONTENT_PERCENTAGE_ONLY]                         = "";
  strings_[ENGLISH_COL][CALC_GCCONTENT_PERCENTAGE_DEFV]                         = "";  

  strings_[ENGLISH_COL][CALC_GCCONTENT_TOTAL]                                   = "Total";
  strings_[ENGLISH_COL][CALC_GCCONTENT_TOTAL_LONG]                              = "Total";
  strings_[ENGLISH_COL][CALC_GCCONTENT_TOTAL_DESC]                              = "Total";
  strings_[ENGLISH_COL][CALC_GCCONTENT_TOTAL_SAMP]                              = "";
  strings_[ENGLISH_COL][CALC_GCCONTENT_TOTAL_ONLY]                              = "";
  strings_[ENGLISH_COL][CALC_GCCONTENT_TOTAL_DEFV]                              = "";  
  
// ===
  
  strings_[ENGLISH_COL][CCALCARRAYOPEX_PLOIDY]                                  = "Ploidy";
  strings_[ENGLISH_COL][CCALCARRAYOPEX_INCLUDE_UNKNOWN]                         = "Include unknown";
  strings_[ENGLISH_COL][CCALCARRAYOPEX_FORCE_OUTGROUP]                          = "Force outgroup";
  strings_[ENGLISH_COL][CCALCARRAYOPEX_OUTGROUP_PRESENCE]                       = "Outgroup presence";
  strings_[ENGLISH_COL][CCALCARRAYOPEX_VINT_PERPOP_NSAM]                        = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCARRAYOPEX_NPOPS]                                   = "Npops";
  strings_[ENGLISH_COL][CCALCARRAYOPEX_INT_TOTAL_NSAM]                          = "Int total nsam";
  strings_[ENGLISH_COL][CCALCARRAYOPEX_MDW_REG_LENGTHS]                         = "Mdw reg lengths";
  strings_[ENGLISH_COL][CCALCARRAYSUMALL_VECTOR]                                = "Vector";
  strings_[ENGLISH_COL][CCALCARRAYSUMALL_ITEMS]                                 = "Items";
  strings_[ENGLISH_COL][CCALCARRAYSUMALL_TOTAL]                                 = "Total";
  strings_[ENGLISH_COL][CCALCBAM2BAI_BAM_FILE_]                                 = "Bam file ";
  strings_[ENGLISH_COL][CCALCBAM2BAI_BAI_FILE_]                                 = "Bai file ";
 
  strings_[ENGLISH_COL][CALC_NPSTAT_MPILEUP]                                    = "Pileup File";
  strings_[ENGLISH_COL][CALC_NPSTAT_MPILEUP_LONG]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MPILEUP_DESC]                               = "Pileup File";
  strings_[ENGLISH_COL][CALC_NPSTAT_MPILEUP_SAMP]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MPILEUP_ONLY]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MPILEUP_DEFV]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_SAMPLESIZE]                                 = "Sample Size";
  strings_[ENGLISH_COL][CALC_NPSTAT_SAMPLESIZE_LONG]                            = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_SAMPLESIZE_DESC]                            = "Haploid sample size";
  strings_[ENGLISH_COL][CALC_NPSTAT_SAMPLESIZE_SAMP]                            = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_SAMPLESIZE_ONLY]                            = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_SAMPLESIZE_DEFV]                            = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_WINDOWLEN]                                  = "Window Length";
  strings_[ENGLISH_COL][CALC_NPSTAT_WINDOWLEN_LONG]                             = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_WINDOWLEN_DESC]                             = "Window Length";
  strings_[ENGLISH_COL][CALC_NPSTAT_WINDOWLEN_SAMP]                             = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_WINDOWLEN_ONLY]                             = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_WINDOWLEN_DEFV]                             = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MINCOV]                                     = "Minimum Coverage";
  strings_[ENGLISH_COL][CALC_NPSTAT_MINCOV_LONG]                                = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MINCOV_DESC]                                = "Filter on minimum coverage";
  strings_[ENGLISH_COL][CALC_NPSTAT_MINCOV_SAMP]                                = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MINCOV_ONLY]                                = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MINCOV_DEFV]                                = "4";
  strings_[ENGLISH_COL][CALC_NPSTAT_MAXCOV]                                     = "Maximum Coverage";
  strings_[ENGLISH_COL][CALC_NPSTAT_MAXCOV_LONG]                                = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MAXCOV_DESC]                                = "Filter on maximum coverage";
  strings_[ENGLISH_COL][CALC_NPSTAT_MAXCOV_SAMP]                                = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MAXCOV_ONLY]                                = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MAXCOV_DEFV]                                = "100";
  strings_[ENGLISH_COL][CALC_NPSTAT_MINQUAL]                                    = "Minimum Base Quality";
  strings_[ENGLISH_COL][CALC_NPSTAT_MINQUAL_LONG]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MINQUAL_DESC]                               = "Filter on base quality";
  strings_[ENGLISH_COL][CALC_NPSTAT_MINQUAL_SAMP]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MINQUAL_ONLY]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_MINQUAL_DEFV]                               = "10";
  strings_[ENGLISH_COL][CALC_NPSTAT_NOLOWFREQ]                                  = "No Low Freq";
  strings_[ENGLISH_COL][CALC_NPSTAT_NOLOWFREQ_LONG]                             = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_NOLOWFREQ_DESC]                             = "Filter on minimum allele count mac > m";
  strings_[ENGLISH_COL][CALC_NPSTAT_NOLOWFREQ_SAMP]                             = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_NOLOWFREQ_ONLY]                             = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_NOLOWFREQ_DEFV]                             = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_OUTGROUP]                                   = "Outgroup File";
  strings_[ENGLISH_COL][CALC_NPSTAT_OUTGROUP_LONG]                              = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_OUTGROUP_DESC]                              = "Outgroup file in FASTA";
  strings_[ENGLISH_COL][CALC_NPSTAT_OUTGROUP_SAMP]                              = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_OUTGROUP_ONLY]                              = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_OUTGROUP_DEFV]                              = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_ANNOT]                                      = "Annotation File";
  strings_[ENGLISH_COL][CALC_NPSTAT_ANNOT_LONG]                                 = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_ANNOT_DESC]                                 = "Annotation file in GFF3";
  strings_[ENGLISH_COL][CALC_NPSTAT_ANNOT_SAMP]                                 = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_ANNOT_ONLY]                                 = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_ANNOT_DEFV]                                 = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_SNPFILE]                                    = "SNP File";
  strings_[ENGLISH_COL][CALC_NPSTAT_SNPFILE_LONG]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_SNPFILE_DESC]                               = "Consider SNPs only if present in file.snp";
  strings_[ENGLISH_COL][CALC_NPSTAT_SNPFILE_SAMP]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_SNPFILE_ONLY]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_SNPFILE_DEFV]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_OUTFILE]                                    = "Output File";
  strings_[ENGLISH_COL][CALC_NPSTAT_OUTFILE_LONG]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_OUTFILE_DESC]                               = "Output file name";
  strings_[ENGLISH_COL][CALC_NPSTAT_OUTFILE_SAMP]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_OUTFILE_ONLY]                               = "";
  strings_[ENGLISH_COL][CALC_NPSTAT_OUTFILE_DEFV]                               = "";
  
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_VCF]                                    = "gVCF File Name";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_VCF_LONG]                               = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_VCF_DESC]                               = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_VCF_SAMP]                               = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_VCF_ONLY]                               = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_VCF_DEFV]                               = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_FASTAREF]                               = "Fasta Reference";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_FASTAREF_LONG]                          = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_FASTAREF_DESC]                          = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_FASTAREF_SAMP]                          = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_FASTAREF_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_FASTAREF_DEFV]                          = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_NUMSAMPS]                               = "Chromosome";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_NUMSAMPS_LONG]                          = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_NUMSAMPS_DESC]                          = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_NUMSAMPS_SAMP]                          = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_NUMSAMPS_ONLY]                          = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_NUMSAMPS_DEFV]                          = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_GFASTA]                                 = "T-Fasta";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_GFASTA_LONG]                            = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_GFASTA_DESC]                            = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_GFASTA_SAMP]                            = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_GFASTA_ONLY]                            = "";
  strings_[ENGLISH_COL][CALC_VCF2GFASTA_GFASTA_DEFV]                            = "";

                     
  strings_[ENGLISH_COL][CCALCBAMCHROMOSOMES_BAI_FILE_] = "Bai file ";
  strings_[ENGLISH_COL][CCALCBAMCHROMOSOMES_CHROMOSOMES_] = "Chromosomes";
  strings_[ENGLISH_COL][CCALCBCF2VCF_BCF] = "Bcf";
  strings_[ENGLISH_COL][CCALCBCF2VCF_VCF] = "Vcf";
  strings_[ENGLISH_COL][CCALCCREATETFASTAANNOTATION_INPUT_TFASTA_FILE_NAME] = "Input tfasta file name";
  strings_[ENGLISH_COL][CCALCCREATETFASTAANNOTATION_INPUT_GFF_FILE_NAME] = "Input gff file name";
  strings_[ENGLISH_COL][CCALCCREATETFASTAANNOTATION_ANNOTATION] = "Annotation";
  strings_[ENGLISH_COL][CCALCCREATETFASTAANNOTATION_GENETIC_CODE] = "Genetic code";
  strings_[ENGLISH_COL][CCALCCREATETFASTAANNOTATION_OUTPUT_TFA_FILE_NAME] = "Output tfa file name";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_DNA_MATRIX] = "Dna matrix";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_INCLUDE_UNKNOWN] = "Include unknown";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_FORCE_OUTGROUP] = "Force outgroup";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_OUTGROUP_PRESENCE] = "Outgroup presence";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_INT_TOTAL_NSAM] = "Int total nsam";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_MATRIX_SIZEPOS] = "Matrix sizepos";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_MATRIX_SEGRPOS] = "Matrix segrpos";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_MATRIX_POL] = "Matrix pol";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_POSITIONS] = "Positions";
  strings_[ENGLISH_COL][CCALCDNAMATRIX2MATRIXPOL_FREQUENCIES] = "Frequencies";
  strings_[ENGLISH_COL][CCALCDUPLICATEPOPULATIONS_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCDUPLICATEPOPULATIONS_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCDUPLICATEPOPULATIONS_OUTGROUP_PRESENCE] = "Outgroup presence";
  strings_[ENGLISH_COL][CCALCDUPLICATEPOPULATIONS_FORMATFILE] = "Formatfile";
  strings_[ENGLISH_COL][CCALCDUPLICATEPOPULATIONS_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCDUPLICATEPOPULATIONS_INT_TOTAL_NSAM] = "Int total nsam";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_NSITES2_POP] = "Nsites2 pop";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_SUM_SAM] = "Sum sam";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_ANX] = "Anx";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_BNX] = "Bnx";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_ANXO] = "Anxo";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_BNXO] = "Bnxo";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_TCGA] = "Tcga";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_STATS_LENGTH] = "Stats length";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_STATS_LENGTH2] = "Stats length2";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_STATS_ANX] = "Stats anx";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_STATS_BNX] = "Stats bnx";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_STATS_ANXO] = "Stats anxo";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_STATS_BNXO] = "Stats bnxo";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_STATS_TCGA] = "Stats tcga";
  strings_[ENGLISH_COL][CCALCEFFECNUCANDTCGAFREQS_STATS_TOTAL_TCGA] = "Stats total tcga";
  strings_[ENGLISH_COL][CCALCEXEC_COMMAND] = "Command";
  strings_[ENGLISH_COL][CCALCEXEC_WORKING_DIRECTORY] = "Working directory";
  strings_[ENGLISH_COL][CCALCEXEC_TYPE] = "Type";
  strings_[ENGLISH_COL][CCALCEXEC_RESULT] = "Result";
  strings_[ENGLISH_COL][CCALCFASTA2DNAMATRIX_FASTA] = "Fasta";
  strings_[ENGLISH_COL][CCALCFASTA2DNAMATRIX_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCFASTA2DNAMATRIX_INCLUDE_UNKNOWN] = "Include unknown";
  strings_[ENGLISH_COL][CCALCFASTA2DNAMATRIX_FORCE_OUTGROUP] = "Force outgroup";
  strings_[ENGLISH_COL][CCALCFASTA2DNAMATRIX_OUTGROUP_PRESENCE] = "Outgroup presence";
  strings_[ENGLISH_COL][CCALCFASTA2DNAMATRIX_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCFASTA2DNAMATRIX_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCFASTA2DNAMATRIX_INT_TOTAL_NSAM] = "Int total nsam";
  strings_[ENGLISH_COL][CCALCFASTA2DNAMATRIX_DNA_MATRIX] = "Dna matrix";
  strings_[ENGLISH_COL][CCALCFASTA2TFASTA_INPUT_FILE_NAME] = "Input file name";
  strings_[ENGLISH_COL][CCALCFASTA2TFASTA_OUTPUT_FILE_NAME] = "Output file name";
  strings_[ENGLISH_COL][CCALCFILESTATS_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCFILESTATS_INCLUDE_UNKNOWN] = "Include unknown";
  strings_[ENGLISH_COL][CCALCFILESTATS_OUTGROUP_PRESENCE] = "Outgroup presence";
  strings_[ENGLISH_COL][CCALCFILESTATS_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCFILESTATS_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCFILESTATS_NAMES] = "Names";
  strings_[ENGLISH_COL][CCALCFILESTATS_N_SITE] = "N site";
  strings_[ENGLISH_COL][CCALCFILESTATS_DNA_MATR] = "DNA matr";
  strings_[ENGLISH_COL][CCALCFILESTATS_MATRIX_SEGRPOS] = "Matrix segrpos";
  strings_[ENGLISH_COL][CCALCFILESTATS_FILE_IN] = "File in";
  strings_[ENGLISH_COL][CCALCFILESTATS_FILE_MAS] = "File mas";
  strings_[ENGLISH_COL][CCALCFILESTATS_OUTPUT] = "Output";
  strings_[ENGLISH_COL][CCALCFILESTATS_FORMATFILE] = "Formatfile";
  strings_[ENGLISH_COL][CCALCFILESTATS_MATRIX_POL] = "Matrix pol";
  strings_[ENGLISH_COL][CCALCFILESTATS_MATRIX_POL_TCGA] = "Matrix pol tcga";
  strings_[ENGLISH_COL][CCALCFILESTATS_LENGTHAMNG] = "Lengthamng";
  strings_[ENGLISH_COL][CCALCFILESTATS_TCGA] = "Tcga";
  strings_[ENGLISH_COL][CCALCFILESTATS_ANX] = "Anx";
  strings_[ENGLISH_COL][CCALCFILESTATS_BNX] = "Bnx";
  strings_[ENGLISH_COL][CCALCFILESTATS_ANXO] = "Anxo";
  strings_[ENGLISH_COL][CCALCFILESTATS_BNXO] = "Bnxo";
  strings_[ENGLISH_COL][CCALCFILESTATS_LENGTH_AL] = "Length al";
  strings_[ENGLISH_COL][CCALCFILESTATS_LENGTH_SEG] = "Length seg";
  strings_[ENGLISH_COL][CCALCFILESTATS_MISSRATIO] = "Missratio";
  strings_[ENGLISH_COL][CCALCFILESTATS_NSITES1_POP] = "Nsites1 pop";
  strings_[ENGLISH_COL][CCALCFILESTATS_NSITES1_POP_OUTG] = "Nsites1 pop outg";
  strings_[ENGLISH_COL][CCALCFILESTATS_NSITES2_POP] = "Nsites2 pop";
  strings_[ENGLISH_COL][CCALCFILESTATS_NSITES2_POP_OUTG] = "Nsites2 pop outg";
  strings_[ENGLISH_COL][CCALCFILESTATS_NSITES3_POP] = "Nsites3 pop";
  strings_[ENGLISH_COL][CCALCFILESTATS_NSITES3_POP_OUTG] = "Nsites3 pop outg";
  strings_[ENGLISH_COL][CCALCFILESTATS_SUM_SAM] = "Sum sam";
  strings_[ENGLISH_COL][CCALCFILESTATS_SVRATIO] = "Svratio";
  strings_[ENGLISH_COL][CCALCFILESTATS_MATRIX_FREQ] = "Matrix freq";
  strings_[ENGLISH_COL][CCALCFILESTATS_MATRIX_POS] = "Matrix pos";
  strings_[ENGLISH_COL][CCALCFILESTATS_MATRIX_SV] = "Matrix sv";
  strings_[ENGLISH_COL][CCALCFILESTATS_MHITBP] = "Mhitbp";
  strings_[ENGLISH_COL][CCALCFILESTATS_N_REALSITE] = "N realsite";
  strings_[ENGLISH_COL][CCALCFILESTATS_NMHITS] = "Nmhits";
  strings_[ENGLISH_COL][CCALCFILESTATS_MATRIX_SIZEPOS] = "Matrix sizepos";
  strings_[ENGLISH_COL][CCALCFILESTATS_N_SAMP] = "N samp";
  strings_[ENGLISH_COL][CCALCFREQSTATS_INCLUDE_UNKNOWN_] = "Include unknown ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_FORCE_OUTGROUP_] = "Force outgroup ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_OUTGROUP_PRESENCE_] = "Outgroup presence ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_VINT_PERPOP_NSAM_] = "Vint perpop nsam ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_NPOPS_] = "Npops ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_MATRIX_POL_] = "Matrix pol ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_N_CCOV_] = "N ccov ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_H1FRQ_] = "H1frq ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_H1FREQ_] = "Stats H1freq ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_LENGTH_] = "Length ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_DFL_] = "Stats Dfl ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_DTAJ_] = "Stats Dtaj ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_EZ_] = "Stats Ez ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_FFL_] = "Stats Ffl ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_HNFW_] = "Stats Hnfw ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_S_] = "Stats S ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_SO_] = "Stats So ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_THETAFL_] = "Stats thetaFL ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_THETAFW_] = "Stats thetaFW ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_THETAL_] = "Stats thetaL ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_THETAS_] = "Stats thetaS ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_THETASA_] = "Stats thetaSA ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_THETASO_] = "Stats thetaSo ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_THETAT_] = "Stats thetaT ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_THETATA_] = "Stats thetaTA ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_THETATO_] = "Stats thetaTo ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_TO_00_] = "Stats To 00 ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_TO_I0_] = "Stats To i0 ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_TO_II_] = "Stats To ii ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_TOH0_00_] = "Stats ToH0 00 ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_TOH0_II_] = "Stats ToH0 ii ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_YACH_] = "Stats Yach ";
  strings_[ENGLISH_COL][CCALCFREQSTATS_STATS_FREQ_] = "Stats freq ";
  strings_[ENGLISH_COL][CCALCFS_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCFS_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCFS_STATS_THETAT] = "Stats thetaT";
  strings_[ENGLISH_COL][CCALCFS_STATS_NHPOP] = "Stats nhpop";
  strings_[ENGLISH_COL][CCALCFS_STATS_FS] = "Stats Fs";
  strings_[ENGLISH_COL][CCALCGCCONTENT_VECTOR] = "Vector";
  strings_[ENGLISH_COL][CCALCGCCONTENT_PERCENTAGE] = "Percentage";
  strings_[ENGLISH_COL][CCALCGCCONTENT_TOTAL] = "Total";
  strings_[ENGLISH_COL][CCALCGFF_INCLUDE_UNKNOWN_] = "Include unknown ";
  strings_[ENGLISH_COL][CCALCGFF_OUTGROUP_PRESENCE_] = "Outgroup presence ";
  strings_[ENGLISH_COL][CCALCGFF_VINT_PERPOP_NSAM_] = "Vint perpop nsam ";
  strings_[ENGLISH_COL][CCALCGFF_NPOPS_] = "Npops ";
  strings_[ENGLISH_COL][CCALCGFF_DNA_MATRIX_] = "Dna matrix ";
  strings_[ENGLISH_COL][CCALCGFF_NAME_FILEINPUTGFF_] = "Name fileinputgff ";
  strings_[ENGLISH_COL][CCALCGFF_SUBSET_POSITIONS_] = "Subset positions ";
  strings_[ENGLISH_COL][CCALCGFF_GENETIC_CODE_] = "Genetic code ";
  strings_[ENGLISH_COL][CCALCGFF_CRITERIA_TRANSCRIPTS_] = "Criteria transcripts ";
  strings_[ENGLISH_COL][CCALCGFF_NSAMUSER_EFF_] = "Nsamuser eff ";
  strings_[ENGLISH_COL][CCALCGFF_N_SITE_] = "N site ";
  strings_[ENGLISH_COL][CCALCGFF_MATRIX_SIZEPOS_] = "Matrix sizepos ";
  strings_[ENGLISH_COL][CCALCGFF_MATRIX_SEGRPOS_] = "Matrix segrpos ";
  strings_[ENGLISH_COL][CCALCGFF_MHITBP_] = "Mhitbp ";
  strings_[ENGLISH_COL][CCALCGFF_NMHITS_] = "Nmhits ";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_MATRIX_POL] = "Matrix pol";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_STATS_NHPOP] = "Stats nhpop";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_STATS_HAPW] = "Stats hapw";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_STATS_HAPA] = "Stats hapa";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_STATS_HAPT] = "Stats hapT";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_STATS_FSTH] = "Stats fsth";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_STATS_FSTH1ALL] = "Stats fsth1all";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_STATS_FREQH] = "Stats freqh";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_STATS_NH] = "Stats nh";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_STATS_GST] = "Stats Gst";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_STATS_FSTHALL] = "Stats fsthALL";
  strings_[ENGLISH_COL][CCALCHWHAFSTH_STATS_GSTALL] = "Stats GstALL";
  strings_[ENGLISH_COL][CCALCJOINTFREQDIST_FORCE_OUTGROUP] = "Force outgroup";
  strings_[ENGLISH_COL][CCALCJOINTFREQDIST_OUTGROUP_PRESENCE] = "Outgroup presence";
  strings_[ENGLISH_COL][CCALCJOINTFREQDIST_NSAM] = "Nsam";
  strings_[ENGLISH_COL][CCALCJOINTFREQDIST_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCJOINTFREQDIST_MATRIX_POL] = "Matrix pol";
  strings_[ENGLISH_COL][CCALCJOINTFREQDIST_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCJOINTFREQDIST_JFD] = "Jfd";
  strings_[ENGLISH_COL][CCALCJOINTFREQDIST_STATS_LINEFREQ] = "Stats linefreq";
  strings_[ENGLISH_COL][CCALCJOINTFREQDIST_NFD] = "Nfd";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_OUTGROUP_PRESENCE] = "Outgroup presence";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_LENGTH_SEG] = "Length seg";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_LENGTHAMNG] = "Lengthamng";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_LENGTH_AL] = "Length al";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_LENGTH_AL_REAL] = "Length al real";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_SVRATIO] = "Svratio";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_NMHITS] = "Nmhits";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_INT_TOTAL_NSAM] = "Int total nsam";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_STATS_LENGTHAMNG] = "Stats lengthamng";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_STATS_TOTAL_LENGTH] = "Stats total length";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_STATS_TOTAL_REAL_LENGTH] = "Stats total real length";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_STATS_TOTAL_SVRATIO] = "Stats total svratio";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_STATS_NMHITS] = "Stats nmhits";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_JFD] = "Jfd";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_NFD] = "Nfd";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_STATS_LINEFREQ] = "Stats linefreq";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_STATS_FREQ] = "Stats freq";
  strings_[ENGLISH_COL][CCALCLENGTHAMNGANDCALCS_STATS_MDSD] = "Stats mdsd";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_INCLUDE_UNKNOWN] = "Include unknown";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_OUTGROUP_PRESENCE] = "Outgroup presence";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_INT_TOTAL_NSAM] = "Int total nsam";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_FILE_MAS] = "File mas";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_NITER] = "Niter";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_LENGTH_AL_REAL] = "Length al real";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_VECTOR_MASK] = "Vector mask";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_MATRIX_MASK] = "Matrix mask";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_SUM_SAM_MASK] = "Sum sam mask";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_LENGTH_MASK] = "Length mask";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_MISSRATIO] = "Missratio";
  strings_[ENGLISH_COL][CCALCMASKFILEMS_LENGTH_AL] = "Length al";
  strings_[ENGLISH_COL][CCALCMISMATCH_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCMISMATCH_NSAM] = "Nsam";
  strings_[ENGLISH_COL][CCALCMISMATCH_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCMISMATCH_MATRIX_POL] = "Matrix pol";
  strings_[ENGLISH_COL][CCALCMISMATCH_STATS_THETAT] = "Stats thetaT";
  strings_[ENGLISH_COL][CCALCMISMATCH_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCMISMATCH_STATS_MDG1] = "Stats mdg1";
  strings_[ENGLISH_COL][CCALCMISMATCH_STATS_MDG2] = "Stats mdg2";
  strings_[ENGLISH_COL][CCALCMISMATCH_STATS_MDSD] = "Stats mdsd";
  strings_[ENGLISH_COL][CCALCMISMATCH_STATS_MDW] = "Stats mdw";
  
  strings_[ENGLISH_COL][CCALCMSTATSPOP_POPULATIONS_INITIAL_] = "Populations (-N)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_PLOIDY_] = "Ploidy (-p)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_INCLUDE_UNKNOWN_] = "Include Unknown (-u)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_FILE_OUT_] = "Output File Name (-T)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_FORCE_OUTGROUP_] = "Force Outgroup (-F)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_OUTGROUP_PRESENCE_] = "Outgroup Presence (-G)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_VINT_PERPOP_NSAM_] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_NPOPS_] = "Number of Populations";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_FORMATFILE_] = "File Format (-f)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_R2I_PLOIDIES_] = "R2i Ploidies (-P)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_FILE_MAS_] = "File Mask (-m)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_NITER_] = "Niter (-t)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_NITERDATA_] = "Niterdata (-r)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_H0FRQ_] = "H0frq";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_H1FRQ_] = "H1frq";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_NUMPLOIDIES_] = "NumPloidies";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_MS_SVRATIO_] = "Ms svratio (-v)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_LENGTH_] = "Length (-l)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_LENGTH_AL_] = "Length al";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_FREQ_REVERT_] = "Freq revert (-q)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_GFFFILES_] = "GFF files";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_FILE_GFF_] = "File GFF (-g)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_SUBSET_POSITIONS_] = "Subset Positions (-g)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CODE_NAME_] = "Code Name (-g)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_GENETIC_CODE_] = "Genetic Code (-g)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_FILE_H0F_] = "File H0f (-S)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_FILE_H1F_] = "File H1f (-A)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CRITERIA_TRANSCRIPT_] = "Criteria Transcript (-c)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_ALL_COMMAND_LINE_] = "All command line";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_FILE_IN_] = "Input File (-i)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_SORT_NSAM_] = "Sort nsam (-O)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_OUTPUT_] = "Output Type (-o)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_SEED_] = "Seed (-s)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_FILE_WPS_] = "File wps (-E)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_FILE_WCOORD_] = "File wcoord (-W)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_WINDOW_] = "Window Size (-w)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_SLIDE_] = "Slide (-z)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_PHYSICAL_LENGTH_] = "Physical Length (-Y)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_FILE_EFFSZ_] = "File Effsz";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_INT_TOTAL_NSAM_ORDER_] = "Int total nsam order";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_MASK_PRINT_] = "Mask print (-K)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_SCAFFOLD_NAME_] = "Scaffold Name (-n)";

  
  //!mstatspop_outputs
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_OUTPUT_]                            = "Statistics";
  
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_SO_OUTPUT_]                   = "S";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_THETA_OUTPUT_]                = "Theta/nt(Wat)";
  
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_THETA_NT_TAJ_OUTPUT_]         = "Theta/nt(Taj)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_THETA_NT_FULI_OUTPUT_]        = "Theta/nt(Fu&Li)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_THETA_NT_FAYWU_OUTPUT_]       = "Theta/nt(Fay&Wu)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_THETA_NT_ZENG_OUTPUT_]        = "Theta/nt(Zeng)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_THETA_NT_ACHAZ_WAT_OUTPUT_]   = "Theta/nt(Achaz,Wat)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_THETA_NT_ACHAZ_TAJ_OUTPUT_]   = "Theta/nt(Achaz,Taj)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_DIVERGENCE_NT_OUTPUT_]        = "Divergence/nt";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_THETA_NT_TAJ_HKY_OUTPUT_]     = "Theta/nt(Taj)HKY";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_KHKY_OUTPUT_]                 = "DivergenceHKY";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_THETA_S_OUTPUT_]              = "Theta/nt(Wat)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_THETA_T_OUTPUT_]              = "Theta/nt(Taj)";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_HAPW_OUTPUT_]                 = "HapW";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_NHPOP_OUTPUT_]                = "nHap";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_DTAJ_OUTPUT_]                 = "Tajima D";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_DFL_OUTPUT_]                  = "Fu&Li D";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_FFL_OUTPUT_]                  = "Fu&Li F";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_NHFW_OUTPUT_]                 = "Fay&Wu norm H";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_EZ_OUTPUT_]                   = "Zeng E";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_YACH_OUTPUT_]                 = "Achaz Y";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_FH_OUTPUT_]                   = "Fh";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_FS_OUTPUT_]                   = "Fs";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_MDSD_OUTPUT_]                 = "SDev";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_MDG1_OUTPUT_]                 = "Skewness";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_MDG2_OUTPUT_]                 = "Kurtosis";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_FST1ALL_OUTPUT_]              = "Fst1";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_FSTH_OUTPUT_]                 = "FstH";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_FSTHKY_OUTPUT_]               = "FstHKY";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_PIWHKY_OUTPUT_]               = "PiWHKY";
  strings_[ENGLISH_COL][CCALCMSTATSPOP_CALC_STATS_PIAHKY_OUTPUT_]               = "PiAHKY";
  
  
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_FILE_IN_] = "File in ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_PLOIDY_] = "Ploidy ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_OUTGROUP_PRESENCE_] = "Outgroup presence ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_NSAMUSER_] = "Nsamuser ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_NPOPS_] = "Npops ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_SORT_NSAM_] = "Sort nsam ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_LENGTH_] = "Length ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_NAMES2_] = "Names2 ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_N_SITE_] = "N site ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_DNA_MATR2_] = "DNA matr2 ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_N_SAMP_] = "N samp ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_MATRIX_SEGRPOS_] = "Matrix segrpos ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_MATRIX_SIZEPOS_] = "Matrix sizepos ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENFASTAFILE_NSAMUSER_EFF_] = "Nsamuser eff ";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_FILE_IN] = "File in";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_INCLUDE_UNKNOWN] = "Include unknown";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_OUTGROUP_PRESENCE] = "Outgroup presence";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_FORCE_OUTGROUP] = "Force outgroup";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_NSAMUSER] = "Nsamuser";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_NSAMTOT] = "Nsamtot";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_KIND_LENGTH] = "Kind length";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_VECTOR_MASK] = "Vector mask";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_SVRATIO] = "Svratio";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_FREQ_REVERT] = "Freq revert";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_FILE_MAS] = "File mas";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_FREQ_MISSING_MS] = "Freq missing ms";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_LOCATION_MISSING_MS] = "Location missing ms";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_FORMATFILE] = "Formatfile";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_MATRIX_POL] = "Matrix pol";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_MATRIX_FREQ] = "Matrix freq";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_MATRIX_POS] = "Matrix pos";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_LENGTH_SEG] = "Length seg";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_MATRIX_SV] = "Matrix sv";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_LENGTH_MASK] = "Length mask";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_LENGTHAMNG] = "Lengthamng";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_NMHITS] = "Nmhits";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_MATRIX_MASK] = "Matrix mask";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_VECTOR_PRIORS] = "Vector priors";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_NPRIORS] = "Npriors";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_SUM_SAM] = "Sum sam";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_SUM_SAM_MASK] = "Sum sam mask";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_NSITES1_POP] = "Nsites1 pop";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_NSITES1_POP_OUTG] = "Nsites1 pop outg";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_NSITES2_POP] = "Nsites2 pop";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_NSITES2_POP_OUTG] = "Nsites2 pop outg";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_NSITES3_POP] = "Nsites3 pop";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_NSITES3_POP_OUTG] = "Nsites3 pop outg";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_ANX] = "Anx";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_BNX] = "Bnx";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_ANXO] = "Anxo";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_BNXO] = "Bnxo";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_MISSRATIO] = "Missratio";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOPENMSFILE_SORT_NSAM] = "Sort nsam";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_MATRIX_POL] = "Matrix pol";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_MATRIX_POL_TCGA] = "Matrix pol tcga";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_POSITIONS] = "Positions";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_SITES] = "Sites";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_SANC] = "Sanc";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_MAINARGC] = "Mainargc";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_FILE_INPUT] = "File input";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_FILE_OUTPUT] = "File output";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_GFFFILES] = "Gfffiles";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_FILE_GFF] = "File GFF";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_SUBSET_POSITIONS] = "Subset positions";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_CODE_NAME] = "Code name";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_GENETIC_CODE] = "Genetic code";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_LENGTH_AL] = "Length al";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_LENGTH_AL_REAL] = "Length al real";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_NITER] = "Niter";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_INCLUDE_UNKNOWN] = "Include unknown";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_FORCE_OUTGROUP] = "Force outgroup";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_THE_OUTGROUP_PRESENCE] = "The outgroup presence";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_INT_TOTAL_NSAM] = "Int total nsam";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_SVRATIO] = "Svratio";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_MISSRATIO] = "Missratio";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_JFD] = "Jfd";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_NFD] = "Nfd";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_H1FRQ] = "H1frq";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_H0FRQ] = "H0frq";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_FILE_H1F] = "File H1f";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_FILE_H0F] = "File H0f";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_VECTOR_PRIORS] = "Vector priors";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_NPRIORS] = "Npriors";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_FORMATFILE] = "Formatfile";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_FREQ_MISSING_MS] = "Freq missing ms";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_NSITES1_POP] = "Nsites1 pop";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_NSITES1_POP_OUTG] = "Nsites1 pop outg";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_NSITES2_POP] = "Nsites2 pop";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_NSITES2_POP_OUTG] = "Nsites2 pop outg";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_NSITES3_POP] = "Nsites3 pop";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_NSITES3_POP_OUTG] = "Nsites3 pop outg";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_LI] = "Li";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_R2I_PLOIDIES] = "R2i ploidies";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_PIW] = "Stats piw";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_PIA] = "Stats pia";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_PIT] = "Stats piT";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_PIANT] = "Stats piant";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_PITNT] = "Stats piTnt";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_FST] = "Stats fst";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_PIWHKY] = "Stats piwHKY";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_PIAHKY] = "Stats piaHKY";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_PITHKY] = "Stats piTHKY";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_FSTHKY] = "Stats fstHKY";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_FST1ALL] = "Stats fst1all";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_GST] = "Stats Gst";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_HAPW] = "Stats hapw";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_HAPA] = "Stats hapa";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_HAPT] = "Stats hapT";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_FSTH] = "Stats fsth";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_FSTH1ALL] = "Stats fsth1all";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_FSTALL] = "Stats fstALL";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_FSTHALL] = "Stats fsthALL";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_GSTALL] = "Stats GstALL";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_S] = "Stats S";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_SO] = "Stats So";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_THETAS] = "Stats thetaS";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_THETASO] = "Stats thetaSo";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_THETAT] = "Stats thetaT";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_THETATO] = "Stats thetaTo";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_THETATHKY] = "Stats thetaTHKY";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_THETAFL] = "Stats thetaFL";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_THETAFW] = "Stats thetaFW";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_THETAL] = "Stats thetaL";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_THETASA] = "Stats thetaSA";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_THETATA] = "Stats thetaTA";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_K] = "Stats K";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_KHKY] = "Stats KHKY";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_DTAJ] = "Stats Dtaj";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_DFL] = "Stats Dfl";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_FFL] = "Stats Ffl";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_HNFW] = "Stats Hnfw";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_EZ] = "Stats Ez";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_YACH] = "Stats Yach";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_R2] = "Stats R2";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_FS] = "Stats Fs";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_RM] = "Stats Rm";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_ZNA] = "Stats ZnA";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_FREQ] = "Stats freq";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_NH] = "Stats nh";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_NHPOP] = "Stats nhpop";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_FREQH] = "Stats freqh";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_LENGTH] = "Stats length";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_LENGTH2] = "Stats length2";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_LENGTHAMNG] = "Stats lengthamng";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TOTAL_LENGTH] = "Stats total length";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TOTAL_REAL_LENGTH] = "Stats total real length";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TOTAL_SVRATIO] = "Stats total svratio";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TOTAL_TCGA] = "Stats total tcga";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TCGA] = "Stats tcga";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_SV] = "Stats sv";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_SVT] = "Stats svT";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_NMHITS] = "Stats nmhits";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_H1FREQ] = "Stats H1freq";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_THETAH1] = "Stats thetaH1";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_H0FREQ] = "Stats H0freq";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_THETAH0] = "Stats thetaH0";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TOH0_II] = "Stats ToH0 ii";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TOH0_00] = "Stats ToH0 00";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TO_II] = "Stats To ii";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TO_00] = "Stats To 00";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TO_I0] = "Stats To i0";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TO_QC_II] = "Stats To Qc ii";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TO_QW_II] = "Stats To Qw ii";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_TO_LC_II] = "Stats To Lc ii";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_MDSD] = "Stats mdsd";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_MDG1] = "Stats mdg1";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_MDG2] = "Stats mdg2";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_MDW] = "Stats mdw";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_LINEFREQ] = "Stats linefreq";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_ANX] = "Stats anx";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_BNX] = "Stats bnx";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_ANXO] = "Stats anxo";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_BNXO] = "Stats bnxo";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_STATS_R2P] = "Stats R2p";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_I] = "Piter i";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_IH] = "Piter ih";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_IGH] = "Piter igh";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_I1] = "Piter i1";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_IH1] = "Piter ih1";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_NITERI] = "Piter niteri";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_NITERIH] = "Piter niterih";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_NITERIGH] = "Piter niterigh";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_NITERI1] = "Piter niteri1";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_NITERIH1] = "Piter niterih1";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_IALL] = "Piter iall";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_IHALL] = "Piter ihall";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_IGHALL] = "Piter ighall";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_NITERIALL] = "Piter niteriall";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_NITERIHALL] = "Piter niterihall";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_PITER_NITERIGHALL] = "Piter niterighall";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_OUTPUT] = "Output";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_NSEED] = "Nseed";
  strings_[ENGLISH_COL][CCALCMSTATSPOPOUTPUT_LENGTH_SEG] = "Length seg";
  strings_[ENGLISH_COL][CCALCOPENCOORDINATESFILE_FILE_WCOORD] = "File wcoord";
  strings_[ENGLISH_COL][CCALCOPENCOORDINATESFILE_WGENES] = "Wgenes";
  strings_[ENGLISH_COL][CCALCOPENCOORDINATESFILE_NWINDOWS] = "Nwindows";
  strings_[ENGLISH_COL][CCALCOPENEFFECTSIZESFILE_FILE_EFFSZ] = "File effsz";
  strings_[ENGLISH_COL][CCALCOPENEFFECTSIZESFILE_WV] = "WV";
  strings_[ENGLISH_COL][CCALCOPENEFFECTSIZESFILE_PP] = "Pp";
  strings_[ENGLISH_COL][CCALCOPENEFFECTSIZESFILE_NV] = "NV";
  strings_[ENGLISH_COL][CCALCOPENEFFECTSIZESFILE_WELIMIT_END] = "Welimit end";
  strings_[ENGLISH_COL][CCALCOPENFASTAFILE_FILE_NAME] = "File name";
  strings_[ENGLISH_COL][CCALCOPENFASTAFILE_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCOPENFASTAFILE_INCLUDE_UNKNOWN] = "Include unknown";
  strings_[ENGLISH_COL][CCALCOPENFASTAFILE_FORCE_OUTGROUP] = "Force outgroup";
  strings_[ENGLISH_COL][CCALCOPENFASTAFILE_OUTGROUP_PRESENCE] = "Outgroup presence";
  strings_[ENGLISH_COL][CCALCOPENFASTAFILE_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCOPENFASTAFILE_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCOPENFASTAFILE_INT_TOTAL_NSAM] = "Int total nsam";
  strings_[ENGLISH_COL][CCALCOPENFASTAFILE_FASTA] = "Fasta";
  strings_[ENGLISH_COL][CCALCOPENFREQSPECFILE_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCOPENFREQSPECFILE_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCOPENFREQSPECFILE_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCOPENFREQSPECFILE_FILE_H1F] = "File H1f";
  strings_[ENGLISH_COL][CCALCOPENFREQSPECFILE_FILE_H0F] = "File H0f";
  strings_[ENGLISH_COL][CCALCOPENFREQSPECFILE_STATS_H1FREQ] = "Stats H1freq";
  strings_[ENGLISH_COL][CCALCOPENFREQSPECFILE_STATS_THETAH1] = "Stats thetaH1";
  strings_[ENGLISH_COL][CCALCOPENFREQSPECFILE_STATS_H0FREQ] = "Stats H0freq";
  strings_[ENGLISH_COL][CCALCOPENFREQSPECFILE_STATS_THETAH0] = "Stats thetaH0";
  strings_[ENGLISH_COL][CCALCOPENFREQSPECFILE_H1FRQ] = "H1frq";
  strings_[ENGLISH_COL][CCALCOPENFREQSPECFILE_H0FRQ] = "H0frq";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_FILE_IN] = "File in";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_NWINDOWS] = "Nwindows";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_WGENES] = "Wgenes";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_WLIMIT_END] = "Wlimit end";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_WP] = "WP";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_WPV] = "WPV";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_OUTGROUP_PRESENCE] = "Outgroup presence";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_NSAMUSER] = "Nsamuser";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_PHYSICAL_LENGTH] = "Physical length";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_WINDOW] = "Window";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_SLIDE] = "Slide";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_SORT_NSAM ] = "Sort nsam ";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_N_SITE] = "N site";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_NAMES] = "Names";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_DNA_MATR] = "DNA matr";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_VECTOR_PRIORS] = "Vector priors";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_MHITBP] = "Mhitbp";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_MATRIX_SIZEPOS] = "Matrix sizepos";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_MATRIX_SEGRPOS] = "Matrix segrpos";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_N_SAMP] = "N samp";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_LI] = "Li";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_NPRIORS] = "Npriors";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_NSAMUSER_EFF] = "Nsamuser eff";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_BEG] = "Beg";
  strings_[ENGLISH_COL][CCALCOPENTFASTAFILE_THE_RESULT] = "The result";
  strings_[ENGLISH_COL][CCALCOPENWEIGHTPOSITIONSFILE_FILE_WS] = "File ws";
  strings_[ENGLISH_COL][CCALCOPENWEIGHTPOSITIONSFILE_WP] = "WP";
  strings_[ENGLISH_COL][CCALCOPENWEIGHTPOSITIONSFILE_WPV] = "WPV";
  strings_[ENGLISH_COL][CCALCOPENWEIGHTPOSITIONSFILE_WV] = "WV";
  strings_[ENGLISH_COL][CCALCOPENWEIGHTPOSITIONSFILE_WLIMIT_END] = "Wlimit end";
  strings_[ENGLISH_COL][CCALCPERMUTE_INT_TOTAL_NSAM] = "Int total nsam";
  strings_[ENGLISH_COL][CCALCPERMUTE_MATRIX_POL] = "Matrix pol";
  strings_[ENGLISH_COL][CCALCPERMUTE_NSAM2] = "Nsam2";
  strings_[ENGLISH_COL][CCALCPERMUTE_PSAM2] = "Psam2";
  strings_[ENGLISH_COL][CCALCPERMUTE_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCPERMUTE_MATRIX_PERM] = "Matrix perm";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_MATRIX_POL] = "Matrix pol";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_MATRIX_SV] = "Matrix sv";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_TCGA] = "Stats tcga";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_LENGTHAMNG] = "Stats lengthamng";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_FLAGHKY] = "Flaghky";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_LENGTH2] = "Stats length2";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_FORMATFILE] = "Formatfile";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_SV] = "Stats sv";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_SVT] = "Stats svT";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_FST] = "Stats fst";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_FST1ALL] = "Stats fst1all";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_FSTHKY] = "Stats fstHKY";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_K] = "Stats K";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_KHKY] = "Stats KHKY";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_PIA] = "Stats pia";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_PIAHKY] = "Stats piaHKY";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_PIT] = "Stats piT";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_PITHKY] = "Stats piTHKY";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_PIWHKY] = "Stats piwHKY";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_PIW] = "Stats piw";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_THETATHKY] = "Stats thetaTHKY";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_PIANT] = "Stats piant";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_PITNT] = "Stats piTnt";
  strings_[ENGLISH_COL][CCALCPIWPIAFST_STATS_FSTALL] = "Stats fstALL";
  strings_[ENGLISH_COL][CCALCR2_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCR2_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCR2_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCR2_MATRIX_POL] = "Matrix pol";
  strings_[ENGLISH_COL][CCALCR2_STATS_S] = "Stats S";
  strings_[ENGLISH_COL][CCALCR2_STATS_THETAT] = "Stats thetaT";
  strings_[ENGLISH_COL][CCALCR2_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCR2_STATS_R2] = "Stats R2";
  strings_[ENGLISH_COL][CCALCR2P_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCR2P_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCR2P_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCR2P_MATRIX_POL] = "Matrix pol";
  strings_[ENGLISH_COL][CCALCR2P_SUM_SAM] = "Sum sam";
  strings_[ENGLISH_COL][CCALCR2P_STATS_S] = "Stats S";
  strings_[ENGLISH_COL][CCALCR2P_STATS_THETAT] = "Stats thetaT";
  strings_[ENGLISH_COL][CCALCR2P_R2I_PLOIDIES] = "R2i ploidies";
  strings_[ENGLISH_COL][CCALCR2P_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCR2P_STATS_R2] = "Stats R2";
  strings_[ENGLISH_COL][CCALCR2P_STATS_R2P] = "Stats R2p";
  strings_[ENGLISH_COL][CCALCRANDOMIZE_RAN] = "Ran";
  strings_[ENGLISH_COL][CCALCSAM2MPILEUP_SAM] = "Sam";
  strings_[ENGLISH_COL][CCALCSAM2MPILEUP_MPILEUP] = "Mpileup";
  strings_[ENGLISH_COL][CCALCSNIPCALLER_CHROMOSOME_REGION] = "Chromosome region";
  strings_[ENGLISH_COL][CCALCSNIPCALLER_OUTPUT_FASTA] = "Output fasta";
  strings_[ENGLISH_COL][CCALCSXSFSS_FORCE_OUTGROUP] = "Force outgroup";
  strings_[ENGLISH_COL][CCALCSXSFSS_OUTGROUP_PRESENCE] = "Outgroup presence";
  strings_[ENGLISH_COL][CCALCSXSFSS_NSAM] = "Nsam";
  strings_[ENGLISH_COL][CCALCSXSFSS_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCSXSFSS_MATRIX_POL] = "Matrix pol";
  strings_[ENGLISH_COL][CCALCSXSFSS_MATRIX_POS] = "Matrix pos";
  strings_[ENGLISH_COL][CCALCSXSFSS_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCSXSFSS_SITES_MATRIX] = "Sites matrix";
  strings_[ENGLISH_COL][CCALCSXSFSS_STATS_SANC] = "Stats sanc";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_FREQ] = "Stats freq";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_TOTAL_LENGTH] = "Stats total length";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_H1FREQ] = "Stats H1freq";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_THETAH1] = "Stats thetaH1";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_H0FREQ] = "Stats H0freq";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_THETAH0] = "Stats thetaH0";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_TOH0_II] = "Stats ToH0 ii";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_TO_II] = "Stats To ii";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_TO_00] = "Stats To 00";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_TO_I0] = "Stats To i0";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_TOH0_00] = "Stats ToH0 00";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_TO_QC_II] = "Stats To Qc ii";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_TO_QW_II] = "Stats To Qw ii";
  strings_[ENGLISH_COL][CCALCTOPTIMALTESTS_STATS_TO_LC_II] = "Stats To Lc ii";
  strings_[ENGLISH_COL][CCALCX_INCLUDE_UNKNOWN] = "Include unknown";
  strings_[ENGLISH_COL][CCALCX_VINT_PERPOP_NSAM] = "Vint perpop nsam";
  strings_[ENGLISH_COL][CCALCX_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCX_INT_TOTAL_NSAM] = "Int total nsam";
  strings_[ENGLISH_COL][CCALCX_VECTOR_MASK] = "Vector mask";
  strings_[ENGLISH_COL][CCALCX_LENGTH] = "Length";
  strings_[ENGLISH_COL][CCALCX_LENGTH_MASK] = "Length mask";
  strings_[ENGLISH_COL][CCALCX_SUM_SAM_MASK] = "Sum sam mask";
  strings_[ENGLISH_COL][CCALCX_NMHITS] = "Nmhits";
  strings_[ENGLISH_COL][CCALCX_FILE_MAS] = "File mas";
  strings_[ENGLISH_COL][CCALCX_LENGTH_AL] = "Length al";
  strings_[ENGLISH_COL][CCALCX_FLAGHKY] = "Flaghky";
  strings_[ENGLISH_COL][CCALCX_SUM_SAM] = "Sum sam";
  strings_[ENGLISH_COL][CCALCX_STATS_LENGTH] = "Stats length";
  strings_[ENGLISH_COL][CCALCX_STATS_LINEFREQ] = "Stats linefreq";
  strings_[ENGLISH_COL][CCALCX_STATS_TOTAL_TCGA] = "Stats total tcga";
  strings_[ENGLISH_COL][CCALCX_STATS_TCGA] = "Stats tcga";
  strings_[ENGLISH_COL][CCALCY_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCY_NPOPS] = "Npops";
  strings_[ENGLISH_COL][CCALCY_STATS_FST1ALL_0] = "Stats fst1all 0";
  strings_[ENGLISH_COL][CCALCY_STATS_FST1ALL_1] = "Stats fst1all 1";
  strings_[ENGLISH_COL][CCALCY_STATS_FSTH1ALL_0] = "Stats fsth1all 0";
  strings_[ENGLISH_COL][CCALCY_STATS_FSTH1ALL_1] = "Stats fsth1all 1";
  strings_[ENGLISH_COL][CCALCY_STATS_FSTALL_0] = "Stats fstALL 0";
  strings_[ENGLISH_COL][CCALCY_STATS_FSTALL_1] = "Stats fstALL 1";
  strings_[ENGLISH_COL][CCALCY_STATS_FSTHALL_0] = "Stats fsthALL 0";
  strings_[ENGLISH_COL][CCALCY_STATS_FSTHALL_1] = "Stats fsthALL 1";
  strings_[ENGLISH_COL][CCALCY_STATS_GSTALL_0] = "Stats GstALL 0";
  strings_[ENGLISH_COL][CCALCY_STATS_GSTALL_1] = "Stats GstALL 1";
  strings_[ENGLISH_COL][CCALCY_PITER_I1] = "Piter i1";
  strings_[ENGLISH_COL][CCALCY_PITER_NITERI1] = "Piter niteri1";
  strings_[ENGLISH_COL][CCALCY_PITER_IH1] = "Piter ih1";
  strings_[ENGLISH_COL][CCALCY_PITER_NITERIH1] = "Piter niterih1";
  strings_[ENGLISH_COL][CCALCY_PITER_IALL] = "Piter iall";
  strings_[ENGLISH_COL][CCALCY_PITER_NITERIALL] = "Piter niteriall";
  strings_[ENGLISH_COL][CCALCY_PITER_IHALL] = "Piter ihall";
  strings_[ENGLISH_COL][CCALCY_PITER_NITERIHALL] = "Piter niterihall";
  strings_[ENGLISH_COL][CCALCY_PITER_IGHALL] = "Piter ighall";
  strings_[ENGLISH_COL][CCALCY_PITER_NITERIGHALL] = "Piter niterighall";
  strings_[ENGLISH_COL][CCALCZ_PLOIDY] = "Ploidy";
  strings_[ENGLISH_COL][CCALCZ_Z] = "Z";
  strings_[ENGLISH_COL][CCALCZ_STATS_FST_0] = "Stats fst 0";
  strings_[ENGLISH_COL][CCALCZ_STATS_FST_1] = "Stats fst 1";
  strings_[ENGLISH_COL][CCALCZ_STATS_FSTH_0] = "Stats fsth 0";
  strings_[ENGLISH_COL][CCALCZ_STATS_FSTH_1] = "Stats fsth 1";
  strings_[ENGLISH_COL][CCALCZ_STATS_GST_0] = "Stats Gst 0";
  strings_[ENGLISH_COL][CCALCZ_STATS_GST_1] = "Stats Gst 1";
  strings_[ENGLISH_COL][CCALCZ_PITER_I] = "Piter i";
  strings_[ENGLISH_COL][CCALCZ_PITER_NITERI] = "Piter niteri";
  strings_[ENGLISH_COL][CCALCZ_PITER_IH] = "Piter ih";
  strings_[ENGLISH_COL][CCALCZ_PITER_NITERIH] = "Piter niterih";
  strings_[ENGLISH_COL][CCALCZ_PITER_IGH] = "Piter igh";
  strings_[ENGLISH_COL][CCALCZ_PITER_NITERIGH] = "Piter niterigh";

  strings_[ENGLISH_COL][CCALC_ALL_KEEP_INTERMEDIATE_RESULTS]                    = "Keep Intermediate Results";
  strings_[ENGLISH_COL][CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_LONG]               = "Keep Intermediate Results";
  strings_[ENGLISH_COL][CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_DESC]               = "This option renames output files with the iteration number and value.";
  strings_[ENGLISH_COL][CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_SAMP]               = "";
  strings_[ENGLISH_COL][CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_ONLY]               = "";
  strings_[ENGLISH_COL][CCALC_ALL_KEEP_INTERMEDIATE_RESULTS_DEFV]               = "False";
 
  
    strings_[ENGLISH_COL][CCALCLIST_FILES_PATH] = "Path";
    strings_[ENGLISH_COL][CCALCLIST_FILES_PATH_DESC] = "";
    strings_[ENGLISH_COL][CCALCLIST_FILES_INCLUDE] = "Include";
    strings_[ENGLISH_COL][CCALCLIST_FILES_INCLUDE_DESC] = ""; //"Regex expression (The scape character is \\\\ instead of \\). For example: (.*)\\\\.txt";
    strings_[ENGLISH_COL][CCALCLIST_FILES_EXCLUDE] = "Exclude";
    strings_[ENGLISH_COL][CCALCLIST_FILES_EXCLUDE_DESC] = "Exclude files separated by coma.";
    strings_[ENGLISH_COL][CCALCLIST_FILES_FILES] = "List of Files";
    strings_[ENGLISH_COL][CCALCLIST_FILES_FILES_DESC] = "List of Files";

    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_MATRIX] = "String Matrix";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_MATRIX_DESC] = "";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_POS] = "Position";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_POS_DESC] = "0-based position.";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_POS_DEFV] = "0 (First Position).";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_COLUMN] = "Column";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_COLUMN_DESC] = "Row is False. Column is True.";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_COLUMN_DEFV] = "False (Row).";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_REMOVE_INDEX] = "Remove Index";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_REMOVE_INDEX_DESC] = "Some matrices have an index row or column. Set to True for not copying it to the vector.";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_REMOVE_INDEX_DEFV] = "False.";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_FLAT_UNIQUE] = "Flattern Unique";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_FLAT_UNIQUE_DESC] = "The output vector contains every matrix elements once.";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_FLAT_UNIQUE_DEFV] = "False.";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_SORT_ITEMS] = "Sort Items";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_SORT_ITEMS_DESC] = "Sort output items.";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_SORT_ITEMS_DEFV] = "False.";    
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_VECTOR] = "String Vector";
    strings_[ENGLISH_COL][CCALCMATRIX2VECTOR_STRING_VECTOR_DESC] = "";
    
    strings_[ENGLISH_COL][CCALCSPLIT_BAM_INPUT] = "BAM File";
    strings_[ENGLISH_COL][CCALCSPLIT_BAM_INPUT_DESC] = "Input BAM file with n chromosomes.";
    strings_[ENGLISH_COL][CCALCSPLIT_BAM_CHROMS] = "Chromosomes";
    strings_[ENGLISH_COL][CCALCSPLIT_BAM_CHROMS_DESC] = "List BAM chromosomes.";
    strings_[ENGLISH_COL][CCALCSPLIT_BAM_EXCLUDE] = "Exclude";
    strings_[ENGLISH_COL][CCALCSPLIT_BAM_EXCLUDE_DESC] = "List of chromosomes to be excluded.";
    strings_[ENGLISH_COL][CCALCSPLIT_BAM_OUTPUT] = "BAM Files";
    strings_[ENGLISH_COL][CCALCSPLIT_BAM_OUTPUT_DESC] = "List of created BAM files with one chromosome per file.";
        

    strings_[ENGLISH_COL][CALC_GET_SEQ_LEN_FASTA]                               = "Fasta File";
    strings_[ENGLISH_COL][CALC_GET_SEQ_LEN_FASTA_DESC]                          = "";
    strings_[ENGLISH_COL][CALC_GET_SEQ_LEN_LEN]                                 = "Sequence Length";
    strings_[ENGLISH_COL][CALC_GET_SEQ_LEN_LEN_DESC]                            = "";

    strings_[ENGLISH_COL][CALC_GET_MRD_BAM_FILES]                               = "BAM Files";
    strings_[ENGLISH_COL][CALC_GET_MRD_BAM_FILES_DESC]                          = "";
    strings_[ENGLISH_COL][CALC_GET_MRD_SEQ_LEN]                                 = "Sequence Length";
    strings_[ENGLISH_COL][CALC_GET_MRD_SEQ_LEN_DESC]                            = "Fasta reference sequence length";
    strings_[ENGLISH_COL][CALC_GET_MRD_MRD]                                     = "MRD";
    strings_[ENGLISH_COL][CALC_GET_MRD_MRD_DESC]                                = "Mean Read Depth";

  IStringTable::FillOtherLanguages();
}

CStringTable::~CStringTable() {
}






  
  

  
  
