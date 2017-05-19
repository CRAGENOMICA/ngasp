/*
 * get_obsdatastats.h
 *
 *  Created on: Apr 18, 2012
 *      Author: gvera
 */

#ifndef GET_OBSDATASTATS_H_
#define GET_OBSDATASTATS_H_

#include "common.h"
#include "zutil.h"

#ifdef	__cplusplus
extern "C" {
#endif

	int get_obsstats_mod(FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz, int n_samp, long int n_site,
					 long int *n_realsite,char *DNA_matr,double *matrix_sizepos,
					 double *matrix_segrpos,char **matrix_pol,
					 long int **matrix_pos,double *length_al,long int *length_seg,
					 int include_unknown,int outgroup_presence, 
					 float *svratio, long int *nmissing, char *format,
					 int *nsamuser,int npops, double **sum_sam,
					 int **svp, float **pwmatrix_miss, float *CpG, int *CpGp, float *GCs, int *Tp, int *Cp, int *Gp, int *Ap,int *GCp,
					 double **nsites1_pop,double **nsites2_pop,double **nsites3_pop,double **nsites1_pop_outg,double **nsites2_pop_outg,double **nsites3_pop_outg);
	
	int number_of_variants(char *colsam,int nsam, char *varnt, int *nvar, char *varmis, int *nmis, int *nm);

#ifdef	__cplusplus
}
#endif



#endif /* GET_OBSDATASTATS_H_ */
