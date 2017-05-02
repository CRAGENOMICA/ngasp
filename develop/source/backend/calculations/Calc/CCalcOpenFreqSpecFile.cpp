/*
 * mstatspop, Statistical Analysis using Multiple Populations for Genomic Data.
 * Copyright (c) 2009-2017, Sebastián Ramos Onsins,
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
 *  \brief     CCalcOpenFreqSpecFile.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 13, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcOpenFreqSpecFile.h"

#include <cmath>
#include <cstring>

#include "../CAllCalculations.h"
#include "../../data_manager/common/CDataAccess.h"


#define MSP_MAX_FILELINE_LEN 102400

CCalcOpenFreqSpecFile::CCalcOpenFreqSpecFile()
: ICalculation(KeyString::CALC_OPEN_FREQ_SPECTRUM,
               KeyString::CALC_OPEN_FREQ_SPECTRUM_BRIEF_DESC,
               KeyString::CALC_OPEN_FREQ_SPECTRUM_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO(ploidy,                                                      // Variable
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
    SET_INPUT_INFO(vint_perpop_nsam,                                            // Variable
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
    SET_INPUT_INFO(npops,                                                       // Variable
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
    SET_INPUT_INFO(file_H1f,                                                    // Variable
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
    SET_INPUT_INFO(file_H0f,                                                    // Variable
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
  
    SET_OUTPUT_INFO(stats_H1freq,                                               // Variable
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
    SET_OUTPUT_INFO(stats_thetaH1,                                              // Variable
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
    SET_OUTPUT_INFO(stats_H0freq,                                               // Variable
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
    SET_OUTPUT_INFO(stats_thetaH0,                                              // Variable
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
    SET_OUTPUT_INFO(H1frq,                                                      // Variable
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
    SET_OUTPUT_INFO(H0frq,                                                      // Variable
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

CCalcOpenFreqSpecFile::~CCalcOpenFreqSpecFile() {
}

void CCalcOpenFreqSpecFile::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(ploidy)
    DM_INPUT(vint_perpop_nsam)
    DM_INPUT(npops)
    DM_INPUT(file_H1f)
    DM_INPUT(file_H0f)
  DM_GET_OUTPUTS
    DM_OUTPUT(stats_H1freq)
    DM_OUTPUT(stats_thetaH1)
    DM_OUTPUT(stats_H0freq)
    DM_OUTPUT(stats_thetaH0)
    DM_OUTPUT(H1frq)
    DM_OUTPUT(H0frq)
  DM_END
}

void CCalcOpenFreqSpecFile::Calculate(bool dry_run) {

  
  if(H1frq->value() == 1) {
    /* -------------------------------------------------------------------- */
    /* -a alternative frequency spectrum: sum=S */

    if(H1frq->value() == 1)
    {
      char *cad, *cad1;

      int npf = npops->value()-1;

      FILE *file_H1freq;  //!! Added *******************************************************

      if((file_H1freq = fopen(file_H1f->value().c_str(), "r")) == 0) {
        printf("\n Error opening Alternative frequency spectrum file %s",file_H1f->value().c_str());
        exit(1);
      }

      /* Solo lee la primera linea, y un máximo de caracteres */
      if( ! feof( file_H1freq ) )
      {
        // int MSP_MAX_FILELINE_LEN = 1024;

        /* check for errors */
        /* Cambiar para leer longitudes indeterminadas, no MAX_LEN
         */
        /* antes 1026 y 1024 */
        if((cad = (char *) calloc( MSP_MAX_FILELINE_LEN, sizeof(char))) == 0) {
          printf("Error allocating memory");
          exit(1);
        }

        fgets( cad, MSP_MAX_FILELINE_LEN, file_H1freq);
      }
      else {
        printf("\n Error reading Alternative frequency spectrum file %s", file_H1f->value().c_str());
        exit(1);
      }

      // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      long int *freqs_lengths = new long int[npf];
      for (int x=0; x<npf; x++) {
        freqs_lengths[x] = static_cast<long int>((*vint_perpop_nsam)[x]);
      }

      stats_H1freq->ReserveMemory(npf, freqs_lengths, 0.0);
      stats_thetaH1->ReserveMemory(npf, 0.0);

      stats_H0freq->ReserveMemory(npf, freqs_lengths, 0.0);
      stats_thetaH0->ReserveMemory(npf, 0.0);

      delete[] freqs_lengths;
      freqs_lengths = NULL;
      // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




      for(int x = 0; x < npf; x++)
      {
        // int MSP_MAX_FILELINE_LEN = 1024;

        if( !feof(file_H1freq)) {
          fgets( cad, MSP_MAX_FILELINE_LEN, file_H1freq);
          cad1 = cad; /* REVISAR, copiando punteros! */
        }
        else {
          printf("\n  Error reading Alternative frequency spectrum file %s, line %d",file_H1f->value().c_str(), x + 2);
          exit(1);
        }

        for(int y = 1; y < (*vint_perpop_nsam)[x]; y++)
        {
          if( ((int)strlen(cad1)) > 0) {
            (*stats_H1freq)[x][y] = (double) atof(cad1);
            cad1 = strchr(cad1,'\t');
            while( cad1 && ( *cad1 == ' '|| *cad1 == '\t') ) {
              cad1 += 1;
            }
          }
        }
        (*stats_thetaH1)[x] = atof(cad1);
      }
      free(cad);
      fclose(file_H1freq);
    }
    else {
      H1frq->set_value(0);
    }
  }


  if((H0frq->value() == 1) && (H1frq->value() == 1)) {
    char *cad, *cad1;

    FILE *file_H0freq;

    if((file_H0freq = fopen(file_H0f->value().c_str(),"r")) == 0) {
      printf("\n Error opening NULL frequency spectrum file %s",file_H0f->value().c_str());
      exit(1);
    }
    if(!feof(file_H0freq)) {
      if((cad = (char *)calloc(1026,sizeof(char))) == 0) {
        printf("Error allocating memory");
        exit(1);
      }

      fgets(cad,1024,file_H0freq);  //!BUG Abans file_H1freq
    }
    else {
      printf("\n Error reading NULL frequency spectrum file %s",file_H0f->value().c_str());
      exit(1);
    }

    int npf = npops->value() - 1;

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    long int *freqs_lengths = new long int[npf];
    for (int x=0; x<npf; x++) {
      freqs_lengths[x] = static_cast<long int>((*vint_perpop_nsam)[x]);
    }

    stats_H0freq->ReserveMemory(npf, freqs_lengths, 0.0);
    stats_thetaH0->ReserveMemory(npf, 0.0);

    delete freqs_lengths;
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    for(int x = 0; x < npf; x++) {
      if(!feof(file_H0freq)) {
        fgets(cad,1024,file_H0freq);
        cad1 = cad;
      }
      else {
        printf("\n  Error reading NULL frequency spectrum file %s, line %d",file_H0f->value().c_str(),x+2);
        exit(1);
      }
      for(int y=1;y<(*vint_perpop_nsam)[x];y++) {
        if(((int)strlen(cad1)) > 0) {
          (*stats_H0freq)[x][y] = (double)atof(cad1);
          cad1 = strchr(cad1,'\t');
          while(cad1 && (*cad1 == ' '|| *cad1 == '\t'))
            cad1 += 1;
        }
      }
      (*stats_thetaH0)[x] = atof(cad1);
    }
    free(cad);
    fclose(file_H0freq);
  }
  else {
    H0frq->set_value(0);
    if(H1frq->value()) {
      int npf = npops->value() - 1;
      for(int x = 0; x < npf; x++) {
        for(int y=1;y<(*vint_perpop_nsam)[x];y++) {
          (*stats_H0freq)[x][y] = 1./(double)y;
        }
      }
    }
  }
 
}

void CCalcOpenFreqSpecFile::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}
