/*
 *  main_fasta2ms2.h
 *  xcode_project
 *
 *  Created by Sebastian E. Ramos Onsins on 27/11/2012.
 *
 */

#ifndef MAIN_FASTA2MS_
#define MAIN_FASTA2MS_

#ifdef	__cplusplus
extern "C" {
	#endif
	
	#include "common.h"
	#include "zutil.h"

	void usage(void);
/*
	int read_fasta(FILE *, FILE *,int *,long int *, long int *, double *, long int *, 
				   long int**, char **,int,int ,char *,char *,char *,char *, char * ,
				   int , double ** ,float *, long int *, int **,float *,float *,float *, float **,float **, int **,float ***, FILE *,char *,int,int,
				   long int **,int **,int **,int **,int **,int **);
	int write_msfile(FILE *, int ,long int, long int, long int, long int *, double *, 
					 char *, long int ,long int ,float ,float, int *, char *,float *,int,float,float,float *, float *, int *, float **,int,
					 long int *,int *,int *,int *,int *,int *);
*/
	int read_fasta( FILE *file_input, SGZip *file_input_gz, FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz, char *input_format,int *nsam,
				   long int *lenR,long int *length_al_real, double *length_al, long int *length_seg,
				   long int **matrix_pos, char **matrix_pol, int ploidy, 
				   int gfffiles, char *name_fileinputgff, char *subset_positions, 
				   char *genetic_code, char *criteria_transcript, char *format, int outgroup_presence,
				   double **matrix_sizepos, float *svratio, float *summatrix_sizepos,long int *nmissing, int **mis_pos, float *fnut, 
				   float *CpG, float *GCs, float *wV, int **svp, float ***pwmatrix_miss, FILE *file_es, SGZip *file_es_gz, char *file_in, char *file_out,int refasta,int tfasta,
				   long int *Pp,int **CpGp,int **Ap,int **Cp,int **Gp,int **Tp,int **GCp,int **sort_nsam, int *int_total_nsam_order,int *nsamuser,int npops, double ***sum_sam,
				   double ***nsites1_pop,double ***nsites2_pop,double ***nsites3_pop,double ***nsites1_pop_outg,double ***nsites2_pop_outg,double ***nsites3_pop_outg,float *wP,float *wPV,FILE *file_ws, SGZip *file_ws_gz, long int *wgenes, long int nwindows,int include_unknown,long int *masked_wgenes, long int masked_nwindows);
	
	int write_msfile(FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz,int nsam,long int lenR,long int lenT, double lenP,long int lenS, long int *vector_pos, double *vector_sizepos,
					 char *matrix_pol, long int slide, long int window,float svratio,float summatrix_sizepos, long int nmissing, int *mis_pos, char *format, float *fnut, 
					 int Physical_length,float CpG, float GCs,float *wV,long int nV,int *svp,float **pwmatrix_miss,int tfasta,
					 long int *Pp,int *CpGp,int *Ap,int *Cp,int *Gp,int *Tp,int *GCp,long int *wgenes, long int nwindows,int *nsamuser,int npops, double **sum_sam,
					 double **nsites1_pop,double **nsites2_pop,double **nsites3_pop,double **nsites1_pop_outg,double **nsites2_pop_outg,double **nsites3_pop_outg,
					 int outgroup);
	
	int read_weights_file(FILE *file_es, SGZip *file_es_gz, FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz, float **wV, long int **Pp, long int *nV);
	int read_weights_positions_file(FILE *file_ws, SGZip *file_ws_gz,FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz, float **wP, float **wPV, float **wV);
    int read_coordinates(FILE *, SGZip *, FILE *, SGZip *, FILE *file_logerr, SGZip *file_logerr_gz,long int **, long int *);
	
#ifdef	__cplusplus
}
#endif

#endif /* MAIN_FASTA2MS_ */
