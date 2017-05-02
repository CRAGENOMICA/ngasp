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
 *  \brief     CCalcTOptimalTests.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 14, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcTOptimalTests.h"

#if inGSL
  #include <gsl_rng.h>
  #include <gsl_randist.h>
  #include <gsl_sf.h>
  #include <gsl_math.h>
  #include <gsl_matrix.h>
  #include <gsl_block.h>
  #include <gsl_linalg.h>
  #include <gsl_blas.h>
//  #include <rng/gsl_rng.h>
//  #include <randist/gsl_randist.h>
//  #include <specfunc/gsl_sf.h>
//  #include <gsl/gsl_math.h>
//  #include <matrix/gsl_matrix.h>
//  #include <block/gsl_block.h>
//  #include <linalg/gsl_linalg.h>
//  #include <blas/gsl_blas.h>
#endif

/* Include libraries */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../data_manager/common/CTestRinf.h"
#include "../../data_manager/common/CTestR0.h"
#include "../../data_manager/common/CTestQuad.h"
#include "../../data_manager/common/CTestLc.h"
#include "../../data_manager/common/CTestQuadWc.h"

CCalcTOptimalTests::CCalcTOptimalTests()
: ICalculation(KeyString::CALC_OPTIMAL_TESTS,
               KeyString::CALC_OPTIMAL_TESTS_BRIEF_DESC,
               KeyString::CALC_OPTIMAL_TESTS_DESC,
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
    SET_INPUT_INFO(stats_freq,                                                  // Variable
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
    SET_INPUT_INFO(stats_total_length,                                          // Variable
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
    SET_INPUT_INFO(stats_H1freq,                                                // Variable
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
    SET_INPUT_INFO(stats_thetaH1,                                               // Variable
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
    SET_INPUT_INFO(stats_H0freq,                                                // Variable
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
    SET_INPUT_INFO(stats_thetaH0,                                               // Variable
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
  
    SET_OUTPUT_INFO(stats_ToH0_ii,                                              // Variable
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
    SET_OUTPUT_INFO(stats_To_ii,                                                // Variable
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
    SET_OUTPUT_INFO(stats_To_00,                                                // Variable
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
    SET_OUTPUT_INFO(stats_To_i0,                                                // Variable
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
    SET_OUTPUT_INFO(stats_ToH0_00,                                              // Variable
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
    SET_OUTPUT_INFO(stats_To_Qc_ii,                                             // Variable
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
    SET_OUTPUT_INFO(stats_To_Qw_ii,                                             // Variable
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
    SET_OUTPUT_INFO(stats_To_Lc_ii,                                             // Variable
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

CCalcTOptimalTests::~CCalcTOptimalTests() {
}

void CCalcTOptimalTests::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(vint_perpop_nsam)
    DM_INPUT(npops)
    DM_INPUT(stats_freq);
    DM_INPUT(stats_total_length);
    DM_INPUT(stats_H1freq);
    DM_INPUT(stats_thetaH1);
    DM_INPUT(stats_H0freq);
    DM_INPUT(stats_thetaH0);  // Used?
  DM_GET_OUTPUTS
    DM_OUTPUT(stats_ToH0_ii);
    DM_OUTPUT(stats_To_ii);
    DM_OUTPUT(stats_To_00);
    DM_OUTPUT(stats_To_i0);
    DM_OUTPUT(stats_ToH0_00);
    DM_OUTPUT(stats_To_Qc_ii);
    DM_OUTPUT(stats_To_Qw_ii);
    DM_OUTPUT(stats_To_Lc_ii);
  DM_END
}

void CCalcTOptimalTests::Calculate(bool dry_run) {


  int x,y;
  double  *mean_freqsptr,
      *data_freqsptr,
      *H0freqsptr,
      mean_S,
      data_S,
      H0_S,
      an,
      thetaw;

  CTestRinf   *omega_test_rinf,
              *omega_test_rinfH0,
              *omega_test_rinfvar0;
  CTestR0     *omega_test_r0,
              *omega_test_r0H0;
  CTestQuad   *omega_test_quad;
  CTestLc     *omega_test_line;
  CTestQuadWc *omega_test_quad_wc;

  for(x=0;x<npops->value()-1;x++)
  {
    int samples = (*vint_perpop_nsam)[x] - 1;

    omega_test_rinf = new CTestRinf(samples);
    omega_test_rinfH0  = new CTestRinf(samples);
    omega_test_rinfvar0 = new CTestRinf(samples);
    omega_test_r0H0 = new CTestR0(samples);
    omega_test_r0 = new CTestR0(samples);
    omega_test_quad = new CTestQuad(samples);
    omega_test_quad_wc = new CTestQuadWc(samples);
    omega_test_line = new CTestLc(samples);


    /*frequency spectrum for H1, H0 and data*/
    mean_freqsptr = new double[(*vint_perpop_nsam)[x]];
    data_freqsptr = new double[(*vint_perpop_nsam)[x]];
    H0freqsptr = new double[(*vint_perpop_nsam)[x]];

    for(int i=0; i<samples; i++) {
      mean_freqsptr[i] = (double)(*stats_H1freq)[x][i+1];
      data_freqsptr[i] = (double)(*stats_freq)[x][i+1];
      H0freqsptr[i] = (double)(*stats_H0freq)[x][i+1];
    }


    mean_S = 0; for(y=0;y<(*vint_perpop_nsam)[x]-1;y++) mean_S += (double)mean_freqsptr[y];
    data_S = 0; for(y=0;y<(*vint_perpop_nsam)[x]-1;y++) data_S += data_freqsptr[y];
    H0_S   = 0; for(y=0;y<(*vint_perpop_nsam)[x]-1;y++) H0_S   += H0freqsptr[y];

    /*NO MISSING VALUES*/
    an     = 0.;for(y=1;y<(*vint_perpop_nsam)[x];y++) an += 1./(double)y;
    thetaw = data_S/(an * stats_total_length->value());/*theta(data)*/

    /*SUM TO 1*/
    for(y=0;y<(*vint_perpop_nsam)[x]-1;y++) mean_freqsptr[y] = mean_freqsptr[y]/mean_S;
    for(y=0;y<(*vint_perpop_nsam)[x]-1;y++) H0freqsptr[y] = H0freqsptr[y]/H0_S;

    /*rinfvarinf_H0nonnull*/
    if(generate_optimal_test_rinf_gennull(omega_test_rinfH0,(*vint_perpop_nsam)[x],mean_freqsptr,H0freqsptr) == (double)NA_VALUE)
      (*stats_ToH0_ii)[x] = (double)NA_VALUE;
    else
      (*stats_ToH0_ii)[x] = optimal_test_rinf(omega_test_rinfH0,data_freqsptr);

    /*rinfvarinf*/
    if(generate_optimal_test_rinf(omega_test_rinf,(*vint_perpop_nsam)[x],mean_freqsptr) == (double)NA_VALUE)
      (*stats_To_ii)[x] = (double)NA_VALUE;
    else
      (*stats_To_ii)[x] = optimal_test_rinf(omega_test_rinf,data_freqsptr);

    /*rinfvar0*/
    if(generate_optimal_test_rinf0(omega_test_rinfvar0,(*vint_perpop_nsam)[x],mean_freqsptr,data_S,stats_total_length->value()) == (double)NA_VALUE)
      (*stats_To_i0)[x] = (double)NA_VALUE;
    else
      (*stats_To_i0)[x] = optimal_test_rinf_rvar0(omega_test_rinfvar0,data_freqsptr);

    /*r0var0*/
    if(generate_optimal_test_r0(omega_test_r0,(*vint_perpop_nsam)[x],mean_freqsptr,data_S,stats_total_length->value()) == (double)NA_VALUE)
      (*stats_To_00)[x] = (double)NA_VALUE;
    else
      (*stats_To_00)[x] = optimal_test_r0(omega_test_r0,data_freqsptr);

    /*r0var0H0nonnull*/
    if(generate_optimal_test_r0_gennull(omega_test_r0H0,(*vint_perpop_nsam)[x],mean_freqsptr,H0freqsptr,data_S,stats_total_length->value()) == (double)NA_VALUE)
      (*stats_ToH0_00)[x] = (double)NA_VALUE;
    else
      (*stats_ToH0_00)[x] = optimal_test_r0(omega_test_r0H0,data_freqsptr);

    /*ALTERNATIVE FREQUENCY SPECTRUM CORRECTION: SUM TO S(data)/theta(H1)*/
    for(y=0;y<(*vint_perpop_nsam)[x]-1;y++)
      mean_freqsptr[y] = mean_freqsptr[y] * mean_S/((*stats_thetaH1)[x]*stats_total_length->value());

    /*rquad*/
    if(generate_optimal_test_quad(omega_test_quad,(*vint_perpop_nsam)[x],mean_freqsptr,thetaw,stats_total_length->value()) == (double)NA_VALUE)
      (*stats_To_Qc_ii)[x] = (double)NA_VALUE;
    else
      (*stats_To_Qc_ii)[x] = optimal_test_quad(omega_test_quad,data_freqsptr);

    /*rquad_wc*/
    if(generate_optimal_test_quad_wc(omega_test_quad_wc,(*vint_perpop_nsam)[x],mean_freqsptr,thetaw,stats_total_length->value()) == (double)NA_VALUE)
      (*stats_To_Qw_ii)[x] = (double)NA_VALUE;
    else
      (*stats_To_Qw_ii)[x] = optimal_test_quad_wc(omega_test_quad_wc,data_freqsptr);

    /*rline*/
    if(generate_optimal_test_lc(omega_test_line,(*vint_perpop_nsam)[x],mean_freqsptr,thetaw,stats_total_length->value()) == (double)NA_VALUE)
      (*stats_To_Lc_ii)[x] = (double)NA_VALUE;
    else
      (*stats_To_Lc_ii)[x] = optimal_test_lc(omega_test_line,data_freqsptr);


    delete[] mean_freqsptr;
    delete[] data_freqsptr;
    delete[] H0freqsptr; //!()

    delete omega_test_rinf;
    delete omega_test_rinfH0;
    delete omega_test_rinfvar0;
    delete omega_test_r0H0;
    delete omega_test_r0;
    delete omega_test_quad;
    delete omega_test_quad_wc;
    delete omega_test_line;
  }

  //return 1;
}

void CCalcTOptimalTests::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

int CCalcTOptimalTests::generate_optimal_test_rinf_gennull( CTestRinf *opt, int n,double *xi_b, double *xi_null )
{
  double den,s,a;
  int i;

  den = 0;
  a = 0;
  s = 0;

  /**< Comprobar que opt-> no es null */
  opt->n = n;

  for(i=1;i<n;i++){
    opt->w[i-1]=(double)(xi_b[i-1]/xi_null[i-1]);
    a+=xi_null[i-1];
    s+=xi_b[i-1];
  }
  if(a==0) return NA_VALUE;
  for(i=1;i<n;i++){
    opt->w[i-1]+=(-s/a);
  }
  for(i=1;i<n;i++)
  {
#if inGSL == 1
    den+=gsl_pow_2(opt->w[i-1])*xi_null[i-1];
#else
    den+=(opt->w[i-1])*(opt->w[i-1])*xi_null[i-1];
#endif

  }
  if(den==0) return NA_VALUE;
  den=sqrt(den/a);
  for(i=1;i<n;i++){
    opt->w[i-1]=opt->w[i-1]/den;
  }
  return 1;
}

/*--------------------------------------------------------------*/

int CCalcTOptimalTests::generate_optimal_test_rinf(CTestRinf *opt,int n,double *xi_b)
{
  double den,s,a;
  int i;

  den=0;
  a=0;
  s=0;
  opt->n=n;
  for(i=1;i<n;i++){
    opt->w[i-1]=(double)i*(xi_b[i-1]);
    a+=1/(double)i;
    s+=xi_b[i-1];
  }
  if(a==0) return NA_VALUE;
  for(i=1;i<n;i++){
    opt->w[i-1]+=(-s/a);
  }
  for(i=1;i<n;i++){
  #if inGSL == 1
    den+=gsl_pow_2(opt->w[i-1])/(double)i;
  #else
    den+=(opt->w[i-1])*(opt->w[i-1])/(double)i;
  #endif
  }
  if(den==0) return NA_VALUE;
  den=sqrt(den/a);
  for(i=1;i<n;i++){
    opt->w[i-1]=opt->w[i-1]/den;
  }
  return 1;
}

/*--------------------------------------------------------------*/

double CCalcTOptimalTests::optimal_test_rinf(CTestRinf *t_rinf, double *xi)
{
  double t;
  int i;
  double s;
  t=0;
  s=0;
  for(i=1;i<(t_rinf->n);i++){
    t+=(t_rinf->w[i-1])*(double)(xi[i-1]);
    s+=xi[i-1];
  };
  if(s==0) return NA_VALUE;
  else return(t/sqrt((double)s));
}

/*--------------------------------------------------------------*/

double CCalcTOptimalTests::optimal_test_rinf2(double *exp_spfr, double *obs_spfr, int n, double S)
{
  int i;
  double an,num1,Sexp,den,To;

  an = num1 = Sexp = 0;
  for(i=1;i<n;i++){
    an += 1./(double)i;
    num1 += exp_spfr[i-1] * obs_spfr[i-1] * (double)i;
    Sexp += exp_spfr[i-1];
  }
  den = 0;
  for(i=1;i<n;i++){
    den += (double)i * (double)pow((exp_spfr[i-1]/Sexp - 1./((double)i*an)),2.);
  }
  To = (num1/Sexp - (double)S/an) / (double)sqrt(S/an * den);
  return To;
}

/*--------------------------------------------------------------*/

/* R=0*/

int CCalcTOptimalTests::generate_optimal_test_r0(CTestR0 *opt,int n, double *xi_b,/* temporary: double theta*/ long sw, long l)
{
/*struct test_r0 *generate_optimal_test_r0 (int n, double *xi_b,long sw, long l){*/

#if inGSL == 1
  double *a,*b,bb,bz,zz,a2;/*a[n+1],b[n]*/  //!removed 's' because it is not used
  int i,j;
  double theta; /*temporary*/
  gsl_matrix *c,*invc,*sigma;
  /*struct test_r0 *opt;*/

  if(n<2 || sw == 0) return NA_VALUE;

  a = (double *)calloc(n+1,sizeof(double));
  b = (double *)calloc(n,sizeof(double));

  a[0]=0;
  a2=0;
  for(i=2;i<=n+1;i++){
    a[i-1]=a[i-2]+1/(double)(i-1);
  }
  for(i=1;i<n;i++){
    a2+=1/(double)(i*i);
    b[i-1]=2*(double)n*(a[n]-a[i-1])/(double)((n-i+1)*(n-i))-2/(double)(n-i);
  }
  b[n-1]=0;
  //s=0;  //!removed because it is not used
  /*opt=(struct test_r0 *)malloc(sizeof(struct test_r0));*/
  opt->n=n;
  opt->l=l;
  theta=(double)sw/(a[n-1]*(double)l); //temporary
  opt->theta=theta;
/*  opt->w=(double *)malloc((n-1)*sizeof(double));*/
/*  opt->dw=(double *)malloc((n-1)*sizeof(double));*/
/*  opt->d2w=(double *)malloc((n-1)*sizeof(double));*/
  c=gsl_matrix_alloc(n-1,n-1);
  invc=gsl_matrix_alloc(n-1,n-1);
  sigma=gsl_matrix_alloc(n-1,n-1);
  //  if (c==NULL||invc==NULL||sigma==NULL) abort();
  gsl_matrix_set_zero(c);
  gsl_matrix_set_zero(sigma);
  for (i=1;i<n;i++){
    gsl_matrix_set(c,i-1,i-1,1/(double)i);
    if (2*i<n) {
      gsl_matrix_set(sigma,i-1,i-1,b[i]);
    }  else {
      if (2*i>n) {
        gsl_matrix_set(sigma,i-1,i-1,b[i-1]-1/gsl_pow_2((double)i));
      }  else {
        gsl_matrix_set(sigma,i-1,i-1,(a[n-1]-a[i-1])*2/(double)(n-i)-1/gsl_pow_2((double)i));
      }
    }
  }
  for (i=1;i<n;i++){
    for (j=1;j<i;j++){
      if (i+j<n) {
        gsl_matrix_set(sigma,i-1,j-1,(b[i]-b[i-1])/2); gsl_matrix_set(sigma,j-1,i-1,(b[i]-b[i-1])/2);
      }  else {
        if (i+j>n) {
          gsl_matrix_set(sigma,i-1,j-1,(b[j-1]-b[j])/2-1/(double)(i*j));
          gsl_matrix_set(sigma,j-1,i-1,(b[j-1]-b[j])/2-1/(double)(i*j));
        }  else {
          gsl_matrix_set(sigma,i-1,j-1,(a[n-1]-a[i-1])/(double)(n-i)+(a[n-1]-a[j-1])/(double)(n-j)-(b[i-1]+b[j])/2-1/(double)(i*j));
          gsl_matrix_set(sigma,j-1,i-1,(a[n-1]-a[i-1])/(double)(n-i)+(a[n-1]-a[j-1])/(double)(n-j)-(b[i-1]+b[j])/2-1/(double)(i*j));
        }
      }
    }
  }
  gsl_matrix_scale(sigma,theta*(double)l/ (1+a2 /(a[n-1]*a[n-1])));
  /*
  //  printf("%u\n",gsl_matrix_ispos(sigma));//d
  //  printf("%u\n",gsl_matrix_isnonneg(c));//d
  */
  gsl_matrix_add(c,sigma);
  /*
  //  printf("%u\n",gsl_matrix_ispos(c));//d
  //  gsl_matrix_scale(c,theta*(double)l);
  */
  gsl_matrix_memcpy(invc,c);
  gsl_linalg_cholesky_decomp(invc);
  /*
  //  gsl_matrix_set_identity(invc);
  //  for (i=1;i<n;i++) {
  //    gsl_linalg_cholesky_svx(c,i);
  //  }
  */
  gsl_linalg_cholesky_invert(invc);
  bb=0.;
  zz=0.;
  bz=0.;
  for(i=1;i<n;i++){
    for(j=1;j<n;j++){
      bb+=(xi_b[i-1])*(xi_b[j-1])*gsl_matrix_get(invc,i-1,j-1);
      bz+=(xi_b[i-1])*(1.0/(double)j)*gsl_matrix_get(invc,i-1,j-1);
      zz+=(1/(double)i)*(1.0/(double)j)*gsl_matrix_get(invc,i-1,j-1);
    }
  }
  opt->var=bb-gsl_pow_2(bz)/zz;
  if(opt->var < 0.) opt->var = 0.;
  opt->var=(opt->var)/a[n-1];
  for(i=1;i<n;i++){
    opt->w[i-1]=0;
    for(j=1;j<n;j++){
      opt->w[i-1]+=(xi_b[j-1])*gsl_matrix_get(invc,i-1,j-1)-(bz/zz)*(1/(double)j)*gsl_matrix_get(invc,i-1,j-1);
    }
  }
  for(i=1;i<n;i++){
    opt->dw[i-1]=0;
    opt->d2w[i-1]=0;
  }
  opt->dvar=0;
  opt->d2var=0;

  free(a);
  free(b);

  gsl_matrix_free(sigma);
  gsl_matrix_free(invc);
  gsl_matrix_free(c);

  return 1;
#else
  return NA_VALUE;
#endif
}

/*--------------------------------------------------------------*/

int CCalcTOptimalTests::generate_optimal_test_r0_gennull(CTestR0 *opt,int n, double *xi_b,double *xi_null, /* temporary: double theta*/ long sw, long l)
{
  /*struct test_r0 *generate_optimal_test_r0 (int n, double *xi_b,long sw, long l){*/
#if inGSL == 1
  double *a,*b,bb,bz,zz,a2;/*a[n+1],b[n]*/  //!removed 's' because it is not used
  int i,j;
  double theta; /*temporary*/
  gsl_matrix *c,*invc,*sigma;
  /*struct test_r0 *opt;*/

  if(n<2 || sw == 0) return NA_VALUE;

  a = (double *)calloc((unsigned long int)n+1,sizeof(double));
  b = (double *)calloc((unsigned long int)n,sizeof(double));

  a[0]=0;
  a2=0;
  for(i=2;i<=n+1;i++){
    a[i-1]=a[i-2]+1/(double)(i-1);
  }
  for(i=1;i<n;i++){
    a2+=1/(double)(i*i);
    b[i-1]=2*(double)n*(a[n]-a[i-1])/(double)((n-i+1)*(n-i))-2/(double)(n-i);
  }
  b[n-1]=0;
  //s=0;  //!removed because it is not used
  /*opt=(struct test_r0 *)malloc(sizeof(struct test_r0));*/
  opt->n=n;
  opt->l=l;
  theta=(double)sw/(a[n-1]*(double)l); //temporary
  opt->theta=theta;
  /*  opt->w=(double *)malloc((n-1)*sizeof(double));*/
  /*  opt->dw=(double *)malloc((n-1)*sizeof(double));*/
  /*  opt->d2w=(double *)malloc((n-1)*sizeof(double));*/
  c=gsl_matrix_alloc(n-1,n-1);
  invc=gsl_matrix_alloc(n-1,n-1);
  sigma=gsl_matrix_alloc(n-1,n-1);
  //  if (c==NULL||invc==NULL||sigma==NULL) abort();
  gsl_matrix_set_zero(c);
  gsl_matrix_set_zero(sigma);
  for (i=1;i<n;i++){
    gsl_matrix_set(c,i-1,i-1,1/(double)i);
    if (2*i<n) {
      gsl_matrix_set(sigma,i-1,i-1,b[i]);
    }  else {
      if (2*i>n) {
        gsl_matrix_set(sigma,i-1,i-1,b[i-1]-1/gsl_pow_2((double)i));
      }  else {
        gsl_matrix_set(sigma,i-1,i-1,(a[n-1]-a[i-1])*2/(double)(n-i)-1/gsl_pow_2((double)i));
      }
    }
  }
  for (i=1;i<n;i++){
    for (j=1;j<i;j++){
      if (i+j<n) {
        gsl_matrix_set(sigma,i-1,j-1,(b[i]-b[i-1])/2); gsl_matrix_set(sigma,j-1,i-1,(b[i]-b[i-1])/2);
      }  else {
        if (i+j>n) {
          gsl_matrix_set(sigma,i-1,j-1,(b[j-1]-b[j])/2-1/(double)(i*j));
          gsl_matrix_set(sigma,j-1,i-1,(b[j-1]-b[j])/2-1/(double)(i*j));
        }  else {
          gsl_matrix_set(sigma,i-1,j-1,(a[n-1]-a[i-1])/(double)(n-i)+(a[n-1]-a[j-1])/(double)(n-j)-(b[i-1]+b[j])/2-1/(double)(i*j));
          gsl_matrix_set(sigma,j-1,i-1,(a[n-1]-a[i-1])/(double)(n-i)+(a[n-1]-a[j-1])/(double)(n-j)-(b[i-1]+b[j])/2-1/(double)(i*j));
        }
      }
    }
  }
  gsl_matrix_scale(sigma,theta*(double)l/ (1+a2 /(a[n-1]*a[n-1])));
  /*
   //  printf("%u\n",gsl_matrix_ispos(sigma));//d
   //  printf("%u\n",gsl_matrix_isnonneg(c));//d
   */
  gsl_matrix_add(c,sigma);
  /*
   //  printf("%u\n",gsl_matrix_ispos(c));//d
   //  gsl_matrix_scale(c,theta*(double)l);
   */
  gsl_matrix_memcpy(invc,c);
  gsl_linalg_cholesky_decomp(invc);
  /*
   //  gsl_matrix_set_identity(invc);
   //  for (i=1;i<n;i++) {
   //    gsl_linalg_cholesky_svx(c,i);
   //  }
   */
  gsl_linalg_cholesky_invert(invc);
  bb=0;
  zz=0;
  bz=0;
  for(i=1;i<n;i++){
    for(j=1;j<n;j++){
      bb+=(xi_b[i-1])*(xi_b[j-1])*gsl_matrix_get(invc,i-1,j-1);
      bz+=(xi_b[i-1])*(xi_null[j-1])*gsl_matrix_get(invc,i-1,j-1);
      zz+=(xi_null[i-1])*(xi_null[j-1])*gsl_matrix_get(invc,i-1,j-1);
    }
  }
  opt->var=bb-gsl_pow_2(bz)/zz;
  if(opt->var < 0.) opt->var = 0.;
  opt->var=(opt->var)/a[n-1];
  for(i=1;i<n;i++){
    opt->w[i-1]=0;
    for(j=1;j<n;j++){
      opt->w[i-1]+=(xi_b[j-1])*gsl_matrix_get(invc,i-1,j-1)-(bz/zz)*(xi_null[j-1])*gsl_matrix_get(invc,i-1,j-1);
    }
  }
  for(i=1;i<n;i++){
    opt->dw[i-1]=0;
    opt->d2w[i-1]=0;
  }
  opt->dvar=0;
  opt->d2var=0;

  free(a);
  free(b);

  gsl_matrix_free(sigma);
  gsl_matrix_free(invc);
  gsl_matrix_free(c);

  return 1;
#else
  return NA_VALUE;
#endif
}

/*--------------------------------------------------------------*/

double CCalcTOptimalTests::optimal_test_r0(CTestR0 *t_r0, double *xi)
{
  double t,a,den;
  long int i;
  double s;
  t=0;
  s=0;
  a=0;
  for(i=1;i<(t_r0->n);i++){
    s+=xi[i-1];
    a+=1/(double)i;
  }
  for(i=1;i<(t_r0->n);i++){
    t+=((t_r0->w[i-1])+(t_r0->dw[i-1])*((double)s/a-(t_r0->theta)))*(double)(xi[i-1]);
  }
  if(a==0.) return NA_VALUE;
  den=sqrt((double)s*((t_r0->var)+(t_r0->dvar)*((double)s/a-(t_r0->theta))));
  if(den==0.) return NA_VALUE;
  return t/den;
}

/*--------------------------------------------------------------*/
/* R=inf but var with R=0*/

/*struct test_rinf *generate_optimal_test_rinf_rvar0 (int n, double *xi_b, long sw, long l) {*/
int CCalcTOptimalTests::generate_optimal_test_rinf0 (CTestRinf *opt,int n, double *xi_b, long sw, long l)
{
#if inGSL == 1
  double den,s,a,theta,*ag,*b,a2;/*ag[n+1],b[n]*/
/*  double sigmaij(int n,int i,int j);*/
  int i,j;
  gsl_matrix *c,*sigma;
/*  struct test_rinf *opt;*/

  if(n<2 || sw == 0) return NA_VALUE;

  ag = (double *)calloc(n+1,sizeof(double));
  b  = (double *)calloc(n,sizeof(double));

  den=0;
  a=0;
    a2=0;
  s=0;
  ag[0]=0;
  for(i=2;i<=n+1;i++){
    ag[i-1]=ag[i-2]+1/(double)(i-1);
  }
  for(i=1;i<n;i++){
    b[i-1]=2*(double)n*(ag[n]-ag[i-1])/(double)((n-i+1)*(n-i))-2/(double)(n-i);
  }
  b[n-1]=0;
/*  opt=(struct test_rinf *)malloc(sizeof(struct test_rinf));*/
  opt->n=n;
/*  opt->w=(double *)malloc((n-1)*sizeof(double));*/
  for(i=1;i<n;i++){
    opt->w[i-1]=(double)i*(xi_b[i-1]);
    a+=1/(double)i;
    a2+=1/(double)(i*i);
    s+=xi_b[i-1];
  }
  theta=(double)sw/(a*(double)l);
  for(i=1;i<n;i++){
    opt->w[i-1]+=(-s/a);
  }
  c=gsl_matrix_alloc(n-1,n-1);
  sigma=gsl_matrix_alloc(n-1,n-1);
  /*  if (c==NULL||invc==NULL||sigma==NULL) abort();*/
  gsl_matrix_set_zero(c);
  gsl_matrix_set_zero(sigma);
  for (i=1;i<n;i++){
    gsl_matrix_set(c,i-1,i-1,1/(double)i);
    if (2*i<n) {
      gsl_matrix_set(sigma,i-1,i-1,b[i]);
    }  else {
      if (2*i>n) {
        gsl_matrix_set(sigma,i-1,i-1,b[i-1]-1/(double)gsl_pow_2((double)i));
      }  else {
        gsl_matrix_set(sigma,i-1,i-1,(ag[n-1]-ag[i-1])*2/(double)(n-i)-1/(double)gsl_pow_2((double)i));
      }
    }
  }
  for (i=1;i<n;i++){
    /*////for (j=1;j<n;j++){ ////*/
    for (j=1;j<i;j++){
      /*////gsl_matrix_set(sigma,i-1,j-1,sigmaij(n,i,j));*/
      if (i+j<n) {
        gsl_matrix_set(sigma,i-1,j-1,(b[i]-b[i-1])/2);
        gsl_matrix_set(sigma,j-1,i-1,(b[i]-b[i-1])/2);
      }  else {
        if (i+j>n) {
          gsl_matrix_set(sigma,i-1,j-1,(b[j-1]-b[j])/2-1/(double)(i*j));
          gsl_matrix_set(sigma,j-1,i-1,(b[j-1]-b[j])/2-1/(double)(i*j));
        }  else {
          gsl_matrix_set(sigma,i-1,j-1,(ag[n-1]-ag[i-1])/(double)(n-i)+(ag[n-1]-ag[j-1])/(double)(n-j)-(b[i-1]+b[j])/2-1/(double)(i*j));
          gsl_matrix_set(sigma,j-1,i-1,(ag[n-1]-ag[i-1])/(double)(n-i)+(ag[n-1]-ag[j-1])/(double)(n-j)-(b[i-1]+b[j])/2-1/(double)(i*j));
        }
      }
    }
  }
  gsl_matrix_scale(sigma,theta*(double)l / (1+a2/(a*a)) );
  /*//  printf("%u\n",gsl_matrix_ispos(sigma));//d
  //  printf("%u\n",gsl_matrix_isnonneg(c));//d
  */
  gsl_matrix_add(c,sigma);
  /*//  printf("%u\n",gsl_matrix_ispos(c));//d
  //  gsl_matrix_scale(c,theta*(double)l);
  */
  gsl_matrix_scale(c,theta*(double)l);

  den=0;
  for(i=1;i<n;i++){
    for(j=1;j<n;j++){
      den+=(opt->w[i-1])*(opt->w[j-1])*gsl_matrix_get(c,i-1,j-1);
    }
  }
  den=(double)sqrt(den);
  if(den==0.) return NA_VALUE;

  for(i=1;i<n;i++){
    opt->w[i-1]=opt->w[i-1]/den;
  }
  gsl_matrix_free(sigma);
  gsl_matrix_free(c);

  free(ag);
  free(b);

  return 1;
#else
  return NA_VALUE;
#endif
}

/*--------------------------------------------------------------*/

double CCalcTOptimalTests::optimal_test_rinf_rvar0 (CTestRinf *t_rinf, double *xi)
{
  double t;
  long i;
  t=0;
  for(i=1;i<(t_rinf->n);i++){
    t+=(t_rinf->w[i-1])*(double)(xi[i-1]);
  }
  return(t);
}

/*--------------------------------------------------------------*/

// R=inf
// Quadratic case

int CCalcTOptimalTests::generate_optimal_test_quad (CTestQuad *opt,int n, double *xi_b,double theta, long l)
{
  double den,s,a,q,m[2][2],v[2],denm;
  int i,j;
  //struct test_quad *opt;
  den=0;
  a=0;
  s=0;
  q=0;
  //opt=(struct test_quad *)malloc(sizeof(struct test_quad));
  opt->n=n;
  //opt->w=(double *)malloc((n-1)*sizeof(double));
  //opt->w2=(double **)malloc((n-1)*sizeof(double *));
  //for(i=1;i<n;i++){
  //  opt->w2[i-1]=(double *)malloc((n-1)*sizeof(double));
  //}
  for(i=1;i<n;i++){
    //xi_b[i-1]=(xi_b[i-1]/(theta*(double)l)); //Rescaling of the input
    a+=theta*(double)l/(double)i;
    s+=theta*(double)l*xi_b[i-1];
#if inGSL == 1
    q+=(double)i*theta*(double)l*gsl_pow_int((double)xi_b[i-1],2);
#else
    q+=(double)i*theta*(double)l*((double)xi_b[i-1]*(double)xi_b[i-1]);
#endif
  }
  if(s==0.) return (NA_VALUE);
  m[0][0]=a*a/2;
  m[1][0]=a*a;
  m[1][1]=2*a*a+a;
  m[0][1]=m[1][0];
  denm=m[0][0]*m[1][1]-m[1][0]*m[0][1];
  for(i=0;i<2;i++){
    for(j=0;j<2;j++){
      m[i][j]=m[i][j]/denm;
    }
  }
  v[0]=m[0][0]*s*(2*a-s+1)+m[0][1]*s*(s/2-a);
  v[1]=m[1][0]*s*(2*a-s+1)+m[1][1]*s*(s/2-a);
  for(i=1;i<n;i++){
#if inGSL == 1
    opt->w[i-1]=(1-(double)i*xi_b[i-1])*s - (0.5)*gsl_pow_int((double)i,2)*gsl_pow_int((double)xi_b[i-1],2) + (a+2)*(double)i*xi_b[i-1] -(2*a+2)*v[0]-(-a-0.5)*v[1];
    opt->w2[i-1][i-1]= (0.5)*gsl_pow_int((double)i,2)*gsl_pow_int((double)xi_b[i-1],2) -(double)i*xi_b[i-1] -(-1)*v[0]-(0.5)*v[1];
#else
    opt->w[i-1]=(1-(double)i*xi_b[i-1])*s - (0.5)*(double)i*(double)i*(double)xi_b[i-1]*(double)xi_b[i-1] + (a+2)*(double)i*xi_b[i-1] -(2*a+2)*v[0]-(-a-0.5)*v[1];
    opt->w2[i-1][i-1]= (0.5)*(double)i*(double)i*(double)xi_b[i-1]*(double)xi_b[i-1] -(double)i*xi_b[i-1] -(-1)*v[0]-(0.5)*v[1];
#endif
    for(j=(i+1);j<n;j++){
      opt->w2[i-1][j-1]=((double)i*(double)j*xi_b[i-1]*xi_b[j-1]-(double)i*xi_b[i-1]-(double)j*xi_b[j-1] -(-2)*v[0]-(1.0)*v[1])/2;
    }
  }
  for(i=1;i<n;i++){
#if inGSL == 1
    den+=(opt->w[i-1])*theta*(double)l*(xi_b[i-1]);
    den+=(opt->w2[i-1][i-1])*theta*(double)l*(xi_b[i-1]+theta*(double)l*(gsl_pow_int((double)xi_b[i-1],2)));
    for(j=(i+1);j<n;j++){
      den+=2*(opt->w2[i-1][j-1])*gsl_pow_int((double)theta,2)*gsl_pow_int((double)l,2)*(xi_b[i-1]*xi_b[j-1]);
    }
#else
    den+=(opt->w[i-1])*theta*(double)l*(xi_b[i-1]);
    den+=(opt->w2[i-1][i-1])*theta*(double)l*(xi_b[i-1]+theta*(double)l*((double)xi_b[i-1]*(double)xi_b[i-1]));
    for(j=(i+1);j<n;j++){
      den+=2*(opt->w2[i-1][j-1])*(double)theta*(double)theta*(double)l*(double)l*(xi_b[i-1]*xi_b[j-1]);
    }
#endif
  }
#if DEBUG_DEN == 0
  if(den <= 0.) return NA_VALUE;
  den=sqrt(den);
#else
  den=1.0;
#endif
  for(i=1;i<n;i++){
    opt->w[i-1]=opt->w[i-1]/den;
    opt->w2[i-1][i-1]= opt->w2[i-1][i-1]/den;
    for(j=i+1;j<n;j++){
      opt->w2[i-1][j-1]= opt->w2[i-1][j-1]/den;
    }
  }
  //return opt;
  return 1;
}

/*--------------------------------------------------------------*/

double CCalcTOptimalTests::optimal_test_quad(CTestQuad *t_quad, double *xi)
{
  double t;
  long i,j;
  t=0;

  for(i=1;i<(t_quad->n);i++){
    t+=(t_quad->w[i-1])*(xi[i-1]);
    //debug//  t+=(t_quad->w[i-1])*10/(double)i;
#if inGSL == 1
    t+=(t_quad->w2[i-1][i-1])*(gsl_pow_int((double)xi[i-1],2));
    //debug//    t+=(t_quad->w2[i-1][i-1])*(10/(double)i+gsl_pow_int(10/(double)i,2));
#else
    t+=(t_quad->w2[i-1][i-1])*(((double)xi[i-1]*(double)xi[i-1]));
    //debug//    t+=(t_quad->w2[i-1][i-1])*(10/(double)i+(100/((double)i*(double)i)));
#endif
    for(j=i+1;j<(t_quad->n);j++){
      t+=2*(t_quad->w2[i-1][j-1])*xi[i-1]*xi[j-1];
      //debug// t+=(t_quad->w2[i-1][j-1])*(100/((double)i*(double)j));
    }
  }
  return(t);
}

/*--------------------------------------------------------------*/

// R=inf
//Linear + constant case (weakly unbiased)

int CCalcTOptimalTests::generate_optimal_test_lc (CTestLc *opt, int n, double *xi_b,double theta, long l)
{
  double den,s,a;
  int i;
  //struct test_lc *opt;
  den=0;
  a=0;
  s=0;
  //opt=(struct test_lc *)malloc(sizeof(struct test_lc));
  opt->n=n;
  //opt->w=(double *)malloc((n-1)*sizeof(double));
  for(i=1;i<n;i++){
    opt->w[i-1]=(double)i*(xi_b[i-1]);
    a+=theta*(double)l/(double)i;
    s+=theta*(double)l*xi_b[i-1];
  }
  for(i=1;i<n;i++){
    opt->w[i-1]+=(-1); //printf("debug %f ",opt->w[i-1]);//debug
  }
  opt->gamma=a-s; //printf("debug %f ",opt->gamma);
  for(i=1;i<n;i++){
    #if inGSL == 1
      den+=(gsl_pow_int((double)opt->w[i-1],2))*(theta*(double)l/(double)i);
    #else
      den+=((opt->w[i-1])*(opt->w[i-1]))*(theta*(double)l/(double)i);
    #endif
  }
#if DEBUG_DEN == 0
  if(den <= 0.) return NA_VALUE;
  den=sqrt(den);
#else
  den=1.0;
#endif
  //printf("debug %f ",den);//debug
  for(i=1;i<n;i++){
    opt->w[i-1]=opt->w[i-1]/den;
  }
  opt->gamma=(opt->gamma)/den;
  //return opt;
  return 1;
}

/*--------------------------------------------------------------*/

double CCalcTOptimalTests::optimal_test_lc( CTestLc *t_lc, double *xi )
{
  double t = 0;
  long i   = 0;

  for( i=1; i<(t_lc->n); i++ )
  {
    t += (t_lc->w[i-1]) * xi[i-1];
    //debug// t+=(t_lc->w[i-1])*10/(double)i;
  }
  t += (t_lc->gamma);

  return(t);
}

/*--------------------------------------------------------------*/

// Quadratic weakly centered case

int CCalcTOptimalTests::generate_optimal_test_quad_wc (CTestQuadWc *opt, int n, double *xi_b,double theta, long l)
{
  double den,s,a,q;
  int i,j;
  //struct test_quad_wc *opt;
  den=0;
  a=0;
  s=0;
  q=0;
  //opt=(struct test_quad_wc *)malloc(sizeof(struct test_quad_wc));
  opt->n=n;
  //opt->w=(double *)malloc((n-1)*sizeof(double));
  //opt->w2=(double **)malloc((n-1)*sizeof(double *));
  //for(i=1;i<n;i++){
  //  opt->w2[i-1]=(double *)malloc((n-1)*sizeof(double));
  //}
  for(i=1;i<n;i++){
    //xi_b[i-1]=(xi_b[i-1]/(theta*(double)l)); //Rescaling of the input
    a+=theta*(double)l/(double)i;
    s+=theta*(double)l*xi_b[i-1];
    #if inGSL == 1
    q+=(double)i*theta*(double)l*gsl_pow_int((double)xi_b[i-1],2);
    #else
    q+=(double)i*theta*(double)l*((double)xi_b[i-1]*(double)xi_b[i-1]);
    #endif
  }
  for(i=1;i<n;i++){
    #if inGSL == 1
    opt->w[i-1]=(1-(double)i*xi_b[i-1])*s - (0.5)*gsl_pow_int((double)i,2)*gsl_pow_int((double)xi_b[i-1],2) - a- (1.5) + (a+2)*(double)i*xi_b[i-1];
    opt->w2[i-1][i-1]= (0.5)*gsl_pow_int((double)i,2)*gsl_pow_int((double)xi_b[i-1],2) -(double)i*xi_b[i-1] +(0.5);
    #else
    opt->w[i-1]=(1-(double)i*xi_b[i-1])*s - (0.5)*((double)i*(double)i)*((double)xi_b[i-1]*(double)xi_b[i-1]) - a- (1.5) + (a+2)*(double)i*xi_b[i-1];
    opt->w2[i-1][i-1]= (0.5)*((double)i*(double)i)*((double)xi_b[i-1]*(double)xi_b[i-1]) -(double)i*xi_b[i-1] +(0.5);
    #endif
    for(j=i+1;j<n;j++){
      opt->w2[i-1][j-1]= (double)i*(double)j*xi_b[i-1]*xi_b[j-1]-(double)i*xi_b[i-1]-(double)j*xi_b[j-1]+1;
    }
  }
  #if inGSL == 1
  opt->gamma= a-a*s-s+(0.5)*(gsl_pow_int((double)a,2)+gsl_pow_int((double)s,2));
  den=2*gsl_pow_int((double)s,2)-2*s*q+gsl_pow_int((double)q,2)/2+gsl_pow_int((double)a,2)/2+a-2*a*s+a*q+q-2*s;
  #else
  opt->gamma= a-a*s-s+(0.5)*(((double)a*(double)a)+((double)s*(double)s));
  den=2*((double)s*(double)s)-2*s*q+((double)q*(double)q)/2+((double)a*(double)a)/2+a-2*a*s+a*q+q-2*s;
  #endif
#if DEBUG_DEN == 0
  if(den <= 0.) return NA_VALUE;
  den=sqrt(den);
#else
  den=1.0;
#endif
  for(i=1;i<n;i++){
    opt->w[i-1]=opt->w[i-1]/den;
    opt->w2[i-1][i-1]= opt->w2[i-1][i-1]/den;
    for(j=i+1;j<n;j++){
      opt->w2[i-1][j-1]= opt->w2[i-1][j-1]/den;
    }
  }
  opt->gamma=opt->gamma/den;
  //return opt;
  return 1;
}

/*--------------------------------------------------------------*/

double CCalcTOptimalTests::optimal_test_quad_wc(CTestQuadWc *t_quad_wc, double *xi)
{
  double t;
  long i,j;
  t=0;

  for(i=1;i<(t_quad_wc->n);i++){
    t+=(t_quad_wc->w[i-1])*xi[i-1];
    //debug// t+=(t_quad_wc->w[i-1])*10/(double)i;
    #if inGSL == 1
    t+=(t_quad_wc->w2[i-1][i-1])*(gsl_pow_int((double)xi[i-1],2));
    //debug//    t+=(t_quad_wc->w2[i-1][i-1])*(10/(double)i+gsl_pow_int(10/(double)i,2));
    #else
    t+=(t_quad_wc->w2[i-1][i-1])*(((double)xi[i-1]*(double)xi[i-1]));
    //debug//    t+=(t_quad_wc->w2[i-1][i-1])*(10/(double)i+(100/((double)i*(double)i)));
    #endif
    for(j=i+1;j<t_quad_wc->n;j++){
      t+=(t_quad_wc->w2[i-1][j-1])*xi[i-1]*xi[j-1];
      //debug// t+=(t_quad_wc->w2[i-1][j-1])*(100/((double)i*(double)j));
    }
  }
  t+=(t_quad_wc->gamma);
  return(t);
}

/*--------------------------------------------------------------*/
