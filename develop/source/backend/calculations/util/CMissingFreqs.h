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
 *  \brief     CMissingFreqs.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_UTIL_CMISSINGFREQS_H_
#define CALCULATIONS_UTIL_CMISSINGFREQS_H_


#define INF 10000
#define CONFSIZE 10000 //size of configuration array for Hellman's probability

class CMissingFreqs {
public:
  CMissingFreqs();
  virtual ~CMissingFreqs();

public:
  int min3(int a, int b, int c);
  int max3(int a, int b, int c);
  int myround(float r);
  float lnfact(int n);
  float lnbinomial(int n, int k);
  float lnmultinomial(int n, int k1, int k2);
  float a(int n);
  float beta(int n,int i);
  float ps(int k, int l, int n, float theta);
  float sigma(int i, int j,int n);
  float pe(int k, int l, int n, float theta);
  float cs(int i, int j, int k, int l, int nx, int ny, int nxy,float theta);
  float ce(int i, int j, int k, int l, int nx, int ny, int nxy,float theta);
  float p(int i, int j, int nx, int ny, int nxy, float theta);
  float cov_missing(int i, int j, int nx, int ny, int nxy, float theta);
  float hn(int n);
  void print_conf_matrix(int *conf,int nconf, int n);
  float watterson(int* a, int n);
  float corrected_watterson(int*a, int* r, int n);
  void store_configurations(int n,int s ,int* conf,int *row);
  float pc(int j,int *r,int n);
  int check_conf(int j, int n,int* conf);
  float hellman_prod(int noind, int* r,int* i);
  float hellman_sum(int *conf,int nconf, int noind, int *r);
  float ck(int r);
  int ak(int m,int r);
  float fhat(int* a, float*c, int n,float* var);
  void _log(char *s);
  float tajima_pi(int *a,float *c, int n);
  float watterson_variance(float theta, int l, int* nx, int* ny,int* nxy, float* var_d, float* var_h);
};


#endif /* CALCULATIONS_UTIL_CMISSINGFREQS_H_ */
