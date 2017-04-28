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
 *  \brief     CCalcOpenCoordinatesFile.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 14, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcOpenCoordinatesFile.h"

#include <seqan/seq_io.h>  //!prev_disabled
#include <tgmath.h> //!added floor

#include "../../language/CStringTable.h"
#include "../../calculations/util/CDnaTools.h"
#include "../../data_manager/common/CDataAccess.h"


CCalcOpenCoordinatesFile::CCalcOpenCoordinatesFile()
: ICalculation(KeyString::CALC_OPEN_COORDINATES,
               KeyString::CALC_OPEN_COORDINATES_BRIEF_DESC,
               KeyString::CALC_OPEN_COORDINATES_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(file_wcoord,                                                 // Variable
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
  
    SET_OUTPUT_INFO(wgenes,                                                     // Variable
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
    SET_OUTPUT_INFO(nwindows,                                                   // Variable
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
    
  file_wcoor_ = NULL;
}

CCalcOpenCoordinatesFile::~CCalcOpenCoordinatesFile() {
}

void CCalcOpenCoordinatesFile::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(file_wcoord)
  DM_GET_OUTPUTS
    DM_OUTPUT(wgenes)
    DM_OUTPUT(nwindows)
  DM_END  
}

void CCalcOpenCoordinatesFile::Calculate(bool dry_run) {
  FILE *file_output = manager()->foutput();
  
	// Opening coordinates file
  if ((file_wcoor_ = fopen(file_wcoord->value().c_str(), "r")) == 0) {
    ERROR_MSG
      << "It is not possible to open the coordinates file "
      << file_wcoord->value()
      END_MSG;
  }
  
  if (read_coordinates(file_output) == 0) {
    ERROR_MSG
      << "Error processing coordinates file "
      << file_wcoord->value()
      END_MSG;
  }
}

void CCalcOpenCoordinatesFile::Finalize(void) {
  if (file_wcoor_ != NULL) {
    fclose(file_wcoor_);
    file_wcoor_ = NULL;
  }  
  
  DM_DEL_ALL_LOCAL_DATA
}



int CCalcOpenCoordinatesFile::read_coordinates(FILE *file_output) {

    char *valn=0;
    int c,x;
    long int xx;
    long int dd;
    double ee;
    long int prevwin = 0;
       
    /*!----------------------------------
     printf("\nReading coordinates file...");
     fflush(stdout);
     ------------------------------------*/
    //!++++++++++++++++++++++++++++++++++++
    fprintf(file_output, "\nReading coordinates file...");
    fflush(file_output);
    //!++++++++++++++++++++++++++++++++++++
    
    if((valn = (char *)calloc(100,sizeof(char))) == 0) {
        ERROR_MSG << "Error: memory not reallocated. read_coordinates.00" END_MSG;
        return(0);
    }
    
    wgenes->ReserveMemory(1000, 0);
//    if((*wgenes = (long int *)calloc(1000,sizeof(long int))) == 0) {
//        fprintf(file_output,"\nError: memory not reallocated. read_coordinates.0 \n");
//        return(0);
//    }
    
    nwindows->set_value(0);
    c = fgetc(file_wcoor_);
    if(c=='#') {
        while(c != 13 && c != 10 && c != 0 && c != -1)
            c = fgetc(file_wcoor_); /*exclude header*/
    }
    while(c == 13 || c == 10)
        c = fgetc(file_wcoor_);
    if(c==0 || c==-1) {
        ERROR_MSG << "Error: no coordinates assigned, read_coordinates.2"
                  END_MSG;
        wgenes->DeleteMemory();
        file_wcoor_=0;
        return(0);
    }
    else {
        xx=0;
        while (c != 0 && c != -1) {
            /*now keep all values: two columns, only numbers*/
            /*KEEP POSITIONS (first initial position, then end, next region and so on)*/
            while(c == 32 || c == 9 || c == 13 || c == 10)
                c = fgetc(file_wcoor_);
            if(c==-1)
                break;
            x=0;
            while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100) {
                valn[x] = c;
                c = fgetc(file_wcoor_);
                x++;
            }
            valn[x] = '\0';
            wgenes[0][xx] = (long int)round((double)atof(valn));
            if(wgenes[0][xx] <= prevwin) {
                ERROR_MSG << "Error: file with coordinates has overlapped or unsorted window positions:" << wgenes[0][xx] END_MSG;                
                exit(1);
            }
            prevwin = wgenes[0][xx];
            
            xx++;
            dd = (long int)floor((double)xx/(double)1000);
            ee = (double)xx/(double)1000;
            if(dd==ee) {
                wgenes->ReallocMemory((long int)(dd+1)*1000, 0);
//                if((*wgenes = realloc(*wgenes,((long int)(dd+1)*(long int)1000*sizeof(long int)))) == 0) {
//                    ERROR_MSG << "Error: realloc error read_coordinates.1" END_MSG;
//                    wgenes->DeleteMemory();
//                    return(0);
//                }    
            }
        }
        if(xx == 0) {
            ERROR_MSG << "Error: no coordinates assigned, read_coordinates.2" END_MSG;
            wgenes->DeleteMemory();
            file_wcoor_=0;
            return(0);
        }
        nwindows->set_value((xx)/2);
    }		
    free(valn);
    return 1;
    
    
//    char *valn=0;
//    int c,x;
//    long int xx;
//    long int dd;
//    double ee;
//    long int prevwin = 0;
//    bool order_ok = true;
//    bool first_coord_value_ok = true;
//    bool first_time = true;
//    long int previous_value = 0;
//    
//    
//    /*!----------------------------------
//     printf("\nReading coordinates file...");
//     fflush(stdout);
//     ------------------------------------*/
//    //!++++++++++++++++++++++++++++++++++++
//    fprintf(file_output, "\nReading coordinates file...");
//    fflush(file_output);
//    //!++++++++++++++++++++++++++++++++++++
//     
//    
//    if((valn = (char *)calloc(100,sizeof(char))) == 0) {
//        ERROR_MSG << "Error: memory not reallocated. read_coordinates.00"
//                  END_MSG;
//        return(0);
//    }
//    
//    wgenes->ReserveMemory(1000, 0);
//    
////    if((*wgenes = (long int *)calloc(1000,sizeof(long int))) == 0) {
////        fprintf(file_output,"\nError: memory not reallocated. read_coordinates.0 \n");
////        return(0);
////    }
//    
//    nwindows->set_value(0);
//    c = fgetc(file_wcoor_);
//    if(c=='#') {
//        while(c != 13 && c != 10 && c != 0 && c != -1)
//            c = fgetc(file_wcoor_); /*exclude header*/
//    }
//    while(c == 13 || c == 10)
//        c = fgetc(file_wcoor_);
//    if(c==0 || c==-1) {
//        ERROR_MSG << "Error: no coordinates assigned, read_coordinates.2"
//                  END_MSG;
//        // free(*wgenes);
//        wgenes->DeleteMemory();
//        file_wcoor_=0;
//        return(0);
//    }
//    else {
//        xx=0;
//        while (c != 0 && c != -1 && order_ok && first_coord_value_ok) {
//            /*now keep all values: two columns, only numbers*/
//            /*KEEP POSITIONS (first initial position, then end, next region and so on)*/
//            while(c == 32 || c == 9 || c == 13 || c == 10)
//                c = fgetc(file_wcoor_);
//            if(c==-1)
//                break;
//            x=0;
//            while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100) {
//                valn[x] = c;
//                c = fgetc(file_wcoor_);
//                x++;
//            }
//            valn[x] = '\0';
//            (*wgenes)[xx] = (long int)round((double)atof(valn));
//            
//            if (first_time) {
//              if ((*wgenes)[0] <= 0) {
//                first_coord_value_ok = false;
//              }
//              first_time = false;
//            }
//            
//            if ((*wgenes)[xx] < previous_value) {
//              order_ok = false;
//            } else {
//              previous_value = (*wgenes)[xx];
//            }
//            
//            xx++;
//            dd = (long int)floor((double)xx/(double)1000);
//            ee = (double)xx/(double)1000;
//            if(dd==ee) {
//              wgenes->ReallocMemory((long int)(dd+1)*1000, 0);
////                if((*wgenes = realloc(*wgenes,((long int)dd*(long int)1000*sizeof(long int)))) == 0) {
////                    puts("Error: realloc error read_coordinates.1\n");
////                    free(*wgenes);
////                    return(0);
////                }    
//            }
//        }
//        
//        if((xx == 0)||(order_ok == false)||(first_coord_value_ok == false)) {
//          if(xx == 0) {
//              ERROR_MSG << "Error: no coordinates assigned, read_coordinates.2" END_MSG;
//          }
//          if(order_ok == false) {
//              ERROR_MSG << "Error: order overlapped window or order incorrect." END_MSG;
//          }
//          if(first_coord_value_ok == false) {
//              ERROR_MSG << "Error: first coordinate value should be greater or equal to one." END_MSG;
//          }
//          
//          wgenes->DeleteMemory();
//          file_wcoor_=0;
//          return(0);
//        }
//        
//        
//        nwindows->set_value((xx)/2);
//    }		
//    free(valn);
//    return 1;
}

