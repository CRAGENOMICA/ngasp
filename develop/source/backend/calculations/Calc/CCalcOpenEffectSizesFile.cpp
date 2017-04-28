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
 *  \brief     CCalcOpenEffectSizesFile.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 14, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcOpenEffectSizesFile.h"

#include <seqan/seq_io.h>  //!prev_disabled
#include <tgmath.h> //!added floor

#include "../../language/CStringTable.h"
#include "../../calculations/util/CDnaTools.h"
#include "../../data_manager/common/CDataAccess.h"


CCalcOpenEffectSizesFile::CCalcOpenEffectSizesFile()
: ICalculation(KeyString::CALC_OPEN_EFFECTSIZES,
               KeyString::CALC_OPEN_EFFECTSIZES_BRIEF_DESC,
               KeyString::CALC_OPEN_EFFECTSIZES_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(file_effsz,                                                  // Variable
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
    SET_OUTPUT_INFO(Pp,                                                         // Variable
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
    SET_OUTPUT_INFO(nV,                                                         // Variable
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
    SET_OUTPUT_INFO(welimit_end,                                                // Variable
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
  file_es_ = NULL;
}

CCalcOpenEffectSizesFile::~CCalcOpenEffectSizesFile() {
}

void CCalcOpenEffectSizesFile::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(file_effsz)
  DM_GET_OUTPUTS
    DM_OUTPUT(wV)
    DM_OUTPUT(Pp)
    DM_OUTPUT(nV)
    DM_OUTPUT(welimit_end)
  DM_END
}

void CCalcOpenEffectSizesFile::Calculate(bool dry_run) {
  // open the file for effect sizes, if included  // DEPRECATED
  
  if ((file_es_ = fopen(file_effsz->value().c_str(), "r")) == 0) {
    ERROR_MSG << "It is not possible to open the effect sizes file "
              << file_effsz->value()
              END_MSG;
    exit(1);
  }
  
  if(read_weights_file() == 0) {
    ERROR_MSG << "Error processing weights file "
              << file_effsz->value()
              END_MSG;
  }
}

void CCalcOpenEffectSizesFile::Finalize(void) {
  if (file_es_ != NULL) {
    fclose(file_es_);
    file_es_ = NULL;
  }  
  
  DM_DEL_ALL_LOCAL_DATA
}


int CCalcOpenEffectSizesFile::read_weights_file(void) {
    
    long int *effsz_site=0; /*positions*/
    float    *effsz_wght=0; /*effect sizes*/
    long int tot_effszP = 0; /*total values*/
    char *valn=0;
    long int dd;
    double ee;
    int c;
    int x;
    long int xx;
    
    printf("\nReading Effect sizes file...");
    fflush(stdout);
    
    if(file_es_ != 0) {
        if((effsz_site = (long int *)calloc(1000,sizeof(long int))) == 0) {
            ERROR_MSG << "Error: memory not reallocated. get_obsdata.1"
              END_MSG;
            return(0);
        }
        if((effsz_wght = (float *)calloc(1000,sizeof(float))) == 0) {
            ERROR_MSG << "Error: memory not reallocated. get_obsdata.2"
              END_MSG;
        }
        if((valn = (char *)calloc(100,sizeof(char))) == 0) {
            ERROR_MSG << "Error: memory not reallocated. get_obsdata.3"
              END_MSG;
            return(0);
        }
        
        c = fgetc(file_es_);
        while(c != 13 && c != 10 && c != 0 && c != -1)
            c = fgetc(file_es_); /*exclude header*/
        while(c == 13 || c == 10)
            c = fgetc(file_es_);
        if(c==0 || c==-1) {
            file_es_=0;
            // *wV=0;
            wV->DeleteMemory();
            free(effsz_site);
            free(effsz_wght);
            ERROR_MSG << "Error: no effect sizes assigned"
              END_MSG;
            return(0);
        }
        else {
            /*now keep all values: two columns, only numbers or decimals*/
            xx=0;
            while (c != 0 && c != -1) {
                /*POSITION*/
                while(c == 32 || c == 9 || c == 13 || c == 10)
                    c = fgetc(file_es_);
                if(c==-1)
                    break;
                x=0;
                while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100) {
                    valn[x] = c;
                    c = fgetc(file_es_);
                    x++;
                }
                valn[x] = '\0';
                effsz_site[xx] = (double)atof(valn);
                
                /*Effect size*/
                while(c == 32 || c == 9 || c == 13 || c == 10)
                    c = fgetc(file_es_);
                if(c==-1)
                    break;
                x=0;
                while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100) {
                    valn[x] = c;
                    c = fgetc(file_es_);
                    x++;
                }
                valn[x] = '\0';
                effsz_wght[xx] = (double)atof(valn);
                
                xx++;
                dd = (long int)floor((double)xx/(double)1000);
                ee = (double)xx/(double)1000;
                if(dd==ee) {
                    if((effsz_site = (long int *)realloc(effsz_site,((long int)(dd+1)*(long int)1000*sizeof(long int)))) == 0) {
                        file_es_=0;
                        // *wV=0;
                        wV->DeleteMemory();
                        free(effsz_site);free(effsz_wght);
                        ERROR_MSG << "Error: realloc error get_obsdata.11"
                          END_MSG;
                        return(0);
                    }
                    if((effsz_wght = (float *)realloc(effsz_wght,((long int)(dd+1)*(long int)1000*sizeof(float)))) == 0) {
                        file_es_=0;
                        // *wV=0;
                        wV->DeleteMemory();
                        free(effsz_site);free(effsz_wght);
                        ERROR_MSG << "Error: realloc errorget_obsdatavarchar.12"
                          END_MSG;
                        return(0);
                    }
                }
            }
            if(effsz_site[xx]== 0) xx--;
            tot_effszP = xx;/*total number of values added*/
            
            /*now we need to assign this values to the variant positions here observed and include them in wV vector*/
            if(xx>0) {
              Pp->ReserveMemory(xx, 0);
//                if((*Pp = (long int *)calloc(xx,sizeof(long int))) == 0) {
//                    file_es_=0;
//                    // *wV=0;
//                    free(effsz_site);free(effsz_wght);
//                    ERROR_MSG << "Error: memory not reallocated. get_obsdata.3"
//                      END_MSG;
//                    return(0);
//                }
                
                wV->ReserveMemory(xx, 0);
//                if((*wV = (float *)calloc(xx,sizeof(float))) == 0) {
//                    file_es_=0;
//                    // *wV=0;
//                    free(effsz_site);free(effsz_wght);
//                    ERROR_MSG << "Error: memory not reallocated. get_obsdata.2"
//                      END_MSG;
//                    return(0);
//                }
                for( x = 0; x < (int)xx; x++ ) {
                    (*Pp)[x] = effsz_site[x];
                    (*wV)[x] = effsz_wght[x];
                }
                nV->set_value(tot_effszP);
            }
            free(effsz_site);
            free(effsz_wght);
        }
        free(valn);
        welimit_end->set_value(xx);
    }
    /*end collecting data for effect sizes*/
    return 1;
}


