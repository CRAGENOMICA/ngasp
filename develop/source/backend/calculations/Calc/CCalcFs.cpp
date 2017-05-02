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
 *  \brief     CCalcFs.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcFs.h"

#include <cmath>

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"


CCalcFs::CCalcFs()
: ICalculation(KeyString::CALC_FS,
               KeyString::CALC_FS_BRIEF_DESC,
               KeyString::CALC_FS_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {
  BEGIN_CALCULATION_INTERFACE_DEFINITION
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
                   OPTTYPE_mandatory)                                           // Required)
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
                   OPTTYPE_mandatory)                                           // Required)
    SET_INPUT_INFO(stats_thetaT,                                                // Variable
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
    SET_INPUT_INFO(stats_nhpop,                                                 // Variable
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
  
    SET_OUTPUT_INFO(stats_Fs,                                                   // Variable
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

CCalcFs::~CCalcFs() {
}

void CCalcFs::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(vint_perpop_nsam)
    DM_INPUT(npops)
    DM_INPUT(stats_thetaT)
    DM_INPUT(stats_nhpop)
  DM_GET_OUTPUTS
    DM_OUTPUT(stats_Fs)
  DM_END
}

void CCalcFs::Calculate(bool dry_run) {


  int pop1 = 0;

  for( pop1=0; pop1 < npops->value(); pop1++)
  {
    (*stats_Fs)[pop1] = FsFunction( (*vint_perpop_nsam)[pop1],
            (*stats_thetaT)[pop1], (int)(*stats_nhpop)[pop1] );
  }

  //return 1;
}

void CCalcFs::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

double CCalcFs::FsFunction(int Nsample, double pi, int NumAlelos) {
    /* Rozas program */

    double  SumaP;      /**< describir variables please */
    double  RestaP;
    int     AleloI;
    long int i;
    double  ValorFs;
    double *qew;
    double  est_var;

    if(pi == 0.0 || Nsample < 2) return(NA_VALUE);
    est_var = pi;
    qew  = (double *)malloc((long int)Nsample*(long int)Nsample*sizeof(double));

    for(i=0;i<(long int)Nsample*(long int)Nsample;i++)
      qew[i] = -1.0;

    SumaP=RestaP=0.0;
    for (AleloI=1;AleloI<NumAlelos;AleloI++) {
        /* calculo q(n,aleloI)   ecuacion 21 (recurrente con eq. 19 y 20) */
        SumaP += FunEq23Ewens(Nsample, AleloI, est_var, qew);
    }

    if(SumaP > 1.-1E-37) {
      for (AleloI = NumAlelos;AleloI <= Nsample; AleloI++)
            RestaP += FunEq23Ewens(Nsample, AleloI, est_var, qew);
        if(RestaP < 1E-37)
        {
            free(qew);
            return NA_VALUE;
        }
        ValorFs = log((double)RestaP) - log((double)1.0-RestaP);
    }
    else {
        if(SumaP < 1E-37)
        {
            free(qew);
            return NA_VALUE;
        }
        else
            ValorFs = log((double)1.0-(double)SumaP) - log((double)SumaP);
    }
    if (fabs(ValorFs) < 1.0E-15)
        ValorFs = 0.0;

    free(qew);
    return ValorFs;
}

double CCalcFs::FunEq23Ewens(int N,int i,double theta, double *qew_)
{
    long int acceso;
    int jj;
    double ValorN;  /* log del numerador */
    double ValorD;  /* log del denominador */

    acceso= (long int)(N-1) * (long int)N + (long int)i - (long int)1;
    ValorN=0.0;
    ValorD=0.0;
    if (qew_[acceso] < 0.0) {
        if (i==1) {
            /* calculo de qj,1   (i = 1)   Antigua equacion 19  */
            if(N > 2) {
                for (jj=2;jj<N;jj++)
                    ValorN = ValorN + log((double)jj);
            }
            ValorN = ValorN + log(theta);
            for(jj=0;jj<N;jj++)
                ValorD  = ValorD + log((double)theta + (double)jj);
            qew_[acceso] = exp((double)(ValorN - ValorD));
        }
        if(i==N) {
            /* calculo de qj,j   (n = i)   antigua equacion 20 */
            ValorN = log((double)theta) * (double)N;
            for(jj=0;jj<N;jj++)
                ValorD  = ValorD + log((double)theta + (double)jj);
            qew_[acceso] = exp((double)(ValorN - ValorD));
    }
    if(i>1 && i<N) {
            /*  recursividad  */
            qew_[acceso] = FunEq23Ewens(N-1,i,  theta,qew_) * ((double)(N-1)/(theta + (double)N-1.0))
      + FunEq23Ewens(N-1,i-1,theta,qew_) *         (theta/(theta + (double)N-1.0));
        }
    }
    return(qew_[acceso]);
}

