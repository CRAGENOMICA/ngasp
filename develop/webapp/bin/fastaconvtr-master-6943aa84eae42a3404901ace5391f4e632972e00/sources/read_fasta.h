/*
 *  read_fasta.h
 *  fasta2ms2
 *
 *  Created by Sebastian E. Ramos Onsins on 27/11/2012.
 *
 */

#ifndef READ_FASTA_
#define READ_FASTA_

#ifdef	__cplusplus
extern "C" {
#endif
	
	#include "common.h"
	#include "usegff2.h"
	#include "get_obsdatastats.h"
	#include "zutil.h"
	#include "zindex.h"

	int var_char(FILE *file_input, SGZip *file_input_gz, FILE *file_logerr, SGZip *file_logerr_gz,long int *count,int *c,int *n_sam,long int *n_sit,int *nseq,int *maxsam,char ***names,char **DNA_matr,
				 long int *n_site,int excludelines,char *name_excluded,int *n_excl,int includelines,char *name_ingroups,char *name_outgroup,
				 int outgroup,int ploidy/*, float *fnut*//*, float *CpG*/);
	
	int assigna(FILE *file_input, SGZip *file_input_gz,int *c,int *nseq,int *maxsam,char ***names);
    
    int function_read_tfasta(FILE *file_input, SGZip *file_input_gz, FILE *file_logerr, SGZip *file_logerr_gz,long int init_site,long int end_site,int *n_sam, long int *n_site, char ***names, char **DNA_matr);
	int read_weights_positions_file(FILE *file_ws, SGZip *file_ws_gz,FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz, float **wP, float **wPV, float **wV);
	int read_weights_file(FILE *file_es, SGZip *file_es_gz, FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz, float **wV, long int **Pp, long int *nV);
	int read_coordinates(FILE *file_wcoor, SGZip *file_wcoor_gz, FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz,long int **wgenes, long int *nwindows);
	
#ifdef	__cplusplus
}
#endif

#endif /* READ_FASTA_ */
