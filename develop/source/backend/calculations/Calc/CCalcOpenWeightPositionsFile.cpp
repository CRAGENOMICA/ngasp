/*
 * mstatspop, Statistical Analysis using Multiple Populations for Genomic Data.
 * Copyright (c) 2009-2017, Sebastián Ramos Onsins,
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
 *  \brief     CCalcOpenWeightPositionsFile.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 14, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcOpenWeightPositionsFile.h"

#include <seqan/seq_io.h>  //!prev_disabled
#include <cstdio>
#include <tgmath.h> //!added floor

#include "../../language/CStringTable.h"
#include "../../calculations/util/CDnaTools.h"
#include "../../data_manager/common/CDataAccess.h"


CCalcOpenWeightPositionsFile::CCalcOpenWeightPositionsFile()
: ICalculation(KeyString::CALC_OPEN_WEIGHTPOSITIONS,
               KeyString::CALC_OPEN_WEIGHTPOSITIONS_BRIEF_DESC,
               KeyString::CALC_OPEN_WEIGHTPOSITIONS_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(file_ws,                                                     // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  
    SET_OUTPUT_INFO(wP,                                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_OUTPUT_INFO(wPV,                                                        // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_OUTPUT_INFO(wV,                                                         // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
    SET_OUTPUT_INFO(wlimit_end,                                                 // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcOpenWeightPositionsFile::~CCalcOpenWeightPositionsFile() {
}

void CCalcOpenWeightPositionsFile::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(file_ws)
  DM_GET_OUTPUTS
    DM_OUTPUT(wP)
    DM_OUTPUT(wPV)
    DM_OUTPUT(wV)
    DM_OUTPUT(wlimit_end)
  DM_END
}

void CCalcOpenWeightPositionsFile::Calculate(bool dry_run) {


  FILE *file_output = manager()->foutput();
  
  FILE *f = NULL;
  
  if ((f = fopen(file_ws->value().c_str(), "r")) == 0) {
    ERROR_MSG 
      << "It is not possible to open the file for weights of positions "
      << file_ws->value()
      END_MSG;
  }
  
  if (read_weights_positions_file(file_output, f) == 0) {
    ERROR_MSG
      << "Error processing the weight positions file "
      << file_ws->value()
      END_MSG;
  }
}

void CCalcOpenWeightPositionsFile::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

int CCalcOpenWeightPositionsFile::read_weights_positions_file(FILE *file_output,
                                                              FILE *file_ws) {
    //long int position;  //!removed because it is not used
    char *valn=0;
    long int dd;
    double ee;
    int c;
    int x;
    long int xx;
    
    /*read weights file*/
    /*!----------------------------------
    printf("\nReading weight file...");
    fflush(stdout);
     ------------------------------------*/
    //!++++++++++++++++++++++++++++++++++++
    fprintf(file_output, "\nReading weight file...");
    fflush(file_output);
    //!++++++++++++++++++++++++++++++++++++
    
    /*keep wP, wPV, wV (not used yet) for all positions, do not need to keep positions: all are correlative*/
    if(file_ws != 0) {
        wP->ReserveMemory(1000, 0.0);
        wPV->ReserveMemory(1000, 0.0);
        wV->ReserveMemory(1000, 0.0);
      
//        if((*wP = (float *)calloc(1000,sizeof(float))) == 0) {
//            ERROR_MSG << "Error: memory not reallocated. get_obsdata.14" END_MSG;
//            return(0);
//        }
//        if((*wPV = (float *)calloc(1000,sizeof(float))) == 0) {
//            ERROR_MSG << "Error: memory not reallocated. get_obsdata.25" END_MSG;
//            return(0);
//        }
//        if((*wV = (float *)calloc(1000,sizeof(float))) == 0) {
//            ERROR_MSG << "Error: memory not reallocated. get_obsdata.23" END_MSG;
//            return(0);
//        }
        
        if((valn = (char *)calloc(100,sizeof(char))) == 0) {
            ERROR_MSG << "Error: memory not reallocated. get_obsdata.34" END_MSG;
            return(0);
        }
        c = fgetc(file_ws);
        while(c != 13 && c != 10 && c != 0 && c != -1)
            c = fgetc(file_ws); /*exclude header*/
        while(c == 13 || c == 10)
            c = fgetc(file_ws);
        if(c==0 || c==-1) {
          wP->DeleteMemory();
          wPV->DeleteMemory();
          wV->DeleteMemory();
//            file_ws=0;
//            *wP=0;
//            *wPV=0;
//            *wV=0;
//            free(*wP);
//            free(*wPV);
//            free(*wV);
            ERROR_MSG << "Error: no weights assigned" END_MSG;
            return(0);
        }
        else {
            /*now keep all values: three or four columns, only numbers or decimals*/
            xx=0;
            while (c != 0 && c != -1) {
                /*POSITION*/
                while(c == 32 || c == 9 || c == 13 || c == 10)
                    c = fgetc(file_ws);
                if(c==0 || c==-1)
                    break;
                x=0;
                while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100) {
                    valn[x] = c;
                    c = fgetc(file_ws);
                    x++;
                }
                valn[x] = '\0';
                //position = atol(valn);  //!removed because it is not used
                
                /*Weight Position*/
                while(c == 32 || c == 9)/* || c == 13 || c == 10)*/
                    c = fgetc(file_ws);
                if(c==0 || c==-1)
                    break;
                x=0;
                while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100) {
                    valn[x] = c;
                    c = fgetc(file_ws);
                    x++;
                }
                valn[x] = '\0';
                (*wP)[xx] = (double)atof(valn);
                
                /*Weight Variant*/
                while(c == 32 || c == 9)/* || c == 13 || c == 10)*/
                    c = fgetc(file_ws);
                if(c==0 || c==-1)
                    break;
                x=0;
                while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100) {
                    valn[x] = c;
                    c = fgetc(file_ws);
                    x++;
                }
                valn[x] = '\0';
                (*wPV)[xx] = (double)atof(valn);
                
                while(c == 32 || c == 9) c = fgetc(file_ws);
                if(!(c == 13 || c == 10 || c == 0 || c == -1)) {
                    /*Effect size*/
                    while(c == 32 || c == 9)/* || c == 13 || c == 10)*/
                        c = fgetc(file_ws);
                    if(c==0 || c==-1)
                        break;
                    x=0;
                    while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100) {
                        valn[x] = c;
                        c = fgetc(file_ws);
                        x++;
                    }
                    valn[x] = '\0';
                    (*wV)[xx] = (double)atof(valn);
                }
                else {
                    (*wV)[xx] = 1.0; /*if undefined the value is 1.0 for all*/
                }
                
                xx++;
                dd = (long int)floor((double)xx/(double)1000);
                ee = (double)xx/(double)1000;
                if(dd==ee) {
                    wP->ReallocMemory((dd+1)*1000, 0.0);
                    wPV->ReallocMemory((dd+1)*1000, 0.0);
                    wV->ReallocMemory((dd+1)*1000, 0.0);
                  
//                    if((*wP = realloc(*wP,((long int)(dd+1)*(long int)1000*sizeof(float)))) == 0) {
//                        file_ws=0;*wP=0;*wPV=0;*wV=0;
//                        free(*wP);free(*wPV);free(*wV);
//                        ERROR_MSG << "Error: realloc error get_obsdata.11" END_MSG;
//                        return(0);
//                    }
//                    if((*wPV = realloc(*wPV,((long int)(dd+1)*(long int)1000*sizeof(float)))) == 0) {
//                        file_ws=0;*wP=0;*wPV=0;*wV=0;
//                        free(*wP);free(*wPV);free(*wV);
//                        ERROR_MSG << "Error: realloc error get_obsdata.11" END_MSG;
//                        return(0);
//                    }
//                    if((*wV = realloc(*wV,((long int)(dd+1)*(long int)1000*sizeof(float)))) == 0) {
//                        file_ws=0;*wP=0;*wPV=0;*wV=0;
//                        free(*wP);free(*wPV);free(*wV);
//                        ERROR_MSG << "Error: realloc error get_obsdata.11" END_MSG;
//                        return(0);
//                    }
                }
            }
        }
        free(valn);
        wlimit_end->set_value(xx);
    }
    else return(0);
    
    return(1);
}
