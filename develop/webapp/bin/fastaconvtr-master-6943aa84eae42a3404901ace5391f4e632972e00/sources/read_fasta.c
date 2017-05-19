/*
 *  read_fasta.c
 *  fasta2ms2
 *
 *  Created by Sebastian E. Ramos Onsins on 27/11/2012.
 *
 */

#include "read_fasta.h"

int read_fasta( FILE *file_input, SGZip *file_input_gz, FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz, char *input_format,int *nsam,
			   long int *lenR,long int *length_al_real, double *length_al, long int *length_seg,
			   long int **matrix_pos, char **matrix_pol, int ploidy, 
			   int gfffiles, char *name_fileinputgff, char *subset_positions, 
			   char *genetic_code, char *criteria_transcript, char *format, int outgroup_presence,
			   double **matrix_sizepos, float *svratio,float *summatrix_sizepos,long int *nmissing, int **mis_pos, float *fnut, 
			   float *CpG, float *GCs, float *wV, int **svp, float ***pwmatrix_miss, FILE *file_es, SGZip *file_es_gz, char *file_in, char *file_out,int refasta,int tfasta,
			   long int *Pp,int **CpGp,int **Ap,int **Cp,int **Gp,int **Tp,int **GCp,int **sort_nsam, int *int_total_nsam_order,int *nsamuser,int npops, double ***sum_sam,
			   double ***nsites1_pop,double ***nsites2_pop,double ***nsites3_pop,double ***nsites1_pop_outg,double ***nsites2_pop_outg,double ***nsites3_pop_outg,
			   float *wP,float *wPV, FILE *file_ws, SGZip *file_ws_gz,long int *wgenes, long int nwindows, int include_unknown,
               long int *masked_wgenes, long int masked_nwindows)
{	
	/*
	 file_input: fasta file, tfasta gzip or not
	 file_output: stdout
     input_format: fasta or tfasta input format file
	 nsam: pointer to number of samples
	 lenR: real physical length
	 length_al_real: pointer to the total physical length in the alignment (Boolean length, include all valid as 1)
	 length_al: pointer to total length after filtering (weighting)
	 length_seg: pointer to the number of variants
	 matrix_pos: pointer to a vector of the number position of each variant
	 matrix_pol: pointer to a vector with the total variants per sample
	 ploidy: 1 or 2
	 gfffiles: 1 include, 0 not
	 name_fileinputgff: name of the GFF file
	 subset_positions: name of the subset in gff (synonymous, coding, etc.)
	 code_name: name of the genetic code (Nuclear_Universal, etc.)
	 genetic_code: in case include a not defined code, include all the code. See usegff.c file.
	 criteria_transcript: 'max' or 'min' are allowed
	 format: 'm' standard ms format; 'e' extended, including missing and gaps; 'x' extended2 missing/gaps + which nucleotides
	 outgroup_presence: if 1, the last POP is the outgroup reference.
	 matrix_sizepos: a pointer to a vector with the weight of each position for a given filter
	 svratio: a pointer to the ratio of transition/transversion
	 **sort_nsam: vector with the order of the samples 
	 *int_total_nsam_order: total samples included and defined in the order flag.
	 *file_es: pointer to the file containing the effect sizes
	 *nsamuser: the number of samples per population
	 npops: the number of populations used
	 fnut: vector with the total frequency of each nucleotide
	 
	 *wV: the weight of the variants or positions included in the matrix <- effsz_wght
	 *Pp: number of each position at the weights for variants (effect size) <- effsz_site

	 *CpG: the total number of CpG for all lines together. Here all positions are always included
	 *CpGp,**Ap,**Cp,**Gp,**Tp,**GC`; CpG,A,C,G,T, GC per position (int)
	 **svp; transitions (1) or transversions (2) per polymorphic position
	 ***sum_sam: real positions per sample (exclude gaps and invalid positions) per position
	 
	 *+*pwmatrix_missing: the up-diagonal pairwise matrix of differences between 2 POPS per position
	 *nsites[123]_pop[_outg]: number of valid positions for each POP per position

	 float *wP=0;weight for each position
     float *wPV=0;weight for the variant at each position
     long int *wgenes; if coordinates file, include nwindows for fasta concatenates
     long int nwindows; if coordinates file, include nwindows for fasta concatenates
     int include_unknown; include missing positions or not
	*/
		
    FILE  *file_fas   	= 0;
    SGZip *file_fas_gz  = 0;

    /*char file_fas_char[MSP_MAX_FILENAME];*/
    FILE *file_weights	=	0;
    SGZip file_weights_gz;
    struct SGZIndex file_weights_gz_index;          /* This is the index for the output gz file. */

    char file_weights_char[MSP_MAX_FILENAME];

	int output = 1;
	
	static char *DNA_matr = 0;
	static char *DNA_matr2 = 0;
	static char **names = 0; /* limit of the name of the lines to 50 characters. be careful */
	static char **names2 = 0; /* limit of the name of the lines to 50 characters. be careful */
	/*static double *matrix_sizepos = 0;*/ /*size of each position, 0 not include, >0 include, Syn/Nsyn positions are allowed*/
	static double *matrix_segrpos = 0; /*always 1 except in those biallelic positions that are not desired (e.g., choose syn but we do not want nsyn)*/
	
	long int count,xx;
	int c;
	int n_sam/*,ns*/;
	long int n_sit;
	int nseq;
	int maxsam;
	int n_excl = 0;
	int n_samp;
	long int n_site;
	
	int x;
	
	/*all these variables are zero because are not used here*/
	int excludelines = 0;
	char *name_excluded = 0;
	int includelines = 0;
	char *name_ingroups = 0;
	char *name_outgroup = 0;
	int outgroup = 0;
	int nsamtot = 0;
	/*!--- Not used int nsamuser_eff = 0; */
	
	long int dd;
	int flag_change_sort; /*in case the order of samples is not consecutive*/
	
    long int init_site,end_site;
    long int yy;
	
    FILE *file_mask;
    SGZip file_mask_gz;

    char mask_name[MSP_MAX_FILENAME];
    char w;
    
    /*printf("\nReading input file...");*/
    fflush(stdout);
    fzprintf(file_logerr,file_logerr_gz,"\nReading input file...");
    
	count = 0;
	c = 0;
	n_sam = 0;
	n_sit = 0;
	nseq  = 0;
	maxsam= 128;
	n_samp= 0;
	n_site= 0;
	n_excl= 0;
    
    init_site = 1;
    end_site = -1;
    
    /*
	if(format[0] == 'm') include_unknown = 0;
	else include_unknown = 1;
    */
    
    if(names == 0) { /* only initialize once. Check */
        if((names = (char **)calloc(128,sizeof(char *))) == 0) {
            fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.1 \n");
            return(0);
        }
        for(x=0;x<128;x++) {
            if((names[x] = (char *)calloc(50,sizeof(char))) == 0) {
                fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.2 \n");
                return(0);
            }
        }
        if((DNA_matr = (char *)calloc(10000,sizeof(char))) == 0) {
            for(x=0;x<128;x++) free(names[x]);
            free(names);
            fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.3 \n");
            return(0);
        }
    }
        
    if(input_format[0] == 'f') {
        /* ok for diploid or haploid */
        c = fzgetc(file_input, file_input_gz);
        while (c != 0 && c != -1/* && n_sam < nsamuser_eff*/) {
            while(c == 32 || c == 9 || c == 13 || c == 10 || c == '*' || c=='#') c = fzgetc(file_input, file_input_gz);
            n_sit = 0;
            if(!(var_char(file_input,file_input_gz,file_logerr,file_logerr_gz,&count,&c,&n_sam,&n_sit,&nseq,&maxsam,&names,&DNA_matr,&n_site,
                          excludelines,name_excluded,&n_excl,includelines,name_ingroups,name_outgroup,outgroup,ploidy/*,fnut*//*,CpG*/)))
                return 0;
            if(n_sam == 32167) {
                fzprintf(file_output,file_output_gz,"Only 32167 samples per loci are allowed.\n");
                break;
            }
        }
        n_samp = n_sam;
    }
    if(input_format[0] == 't') {
        /*READ TFASTA FILE*/
        if(function_read_tfasta(file_input,file_input_gz,file_logerr,file_logerr_gz,init_site,end_site,&n_sam,&n_site,&names,&DNA_matr)==0) {
            fzprintf(file_logerr,file_logerr_gz,"Unable reading tfasta file\n");
            exit(1);
        }
        n_samp = n_sam;
    }
    
	/*n_site: number of total sites in the sequence*/
	/*length_al_real: number of effective positions accounted after eliminating mhits, gaps in all samples, not counted positions, etc*/
	
	/*modify the order of samples using option flag O*/
	/*ordering data: in case O is not a flag included*/
	flag_change_sort = 0;
	if(*int_total_nsam_order == 0) {
		*int_total_nsam_order = nsamtot = n_samp;
		if((sort_nsam[0] = (int *) calloc( (unsigned long)n_samp, sizeof(int) )) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"Error allocating memory");
			exit(1);
		}
		for( x = 0; x < n_samp; x++ ) {
			sort_nsam[0][ x ] = x;
		}
	} 
	else { 
		for(x=0;x<n_samp;x++) {
			if(sort_nsam[0][x] != x) {
				flag_change_sort = 1;
				break;
			}
		}
	}
    nsamtot = n_sam; /*number of samples*/
    
	if(flag_change_sort == 1) {
		nsamtot = *int_total_nsam_order; 
		/*define duplicated matr (we re-use DNAmatrix2 and we delete again once DNA matrix is redefined)*/
		if ((DNA_matr2 = (char *)calloc(n_site*(long int)n_samp,sizeof(char))) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.23d \n");
			for(x=0;x<n_sam;x++) free(names[x]);
			free(names);
			free(DNA_matr);
			return(0);
		}
		if((names2 = (char **)calloc(n_samp,sizeof(char *))) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.1s2 \n");
			for(x=0;x<n_sam;x++) free(names[x]);
			free(names);
			free(DNA_matr);
			return(0);
		}
		for(x=0;x<n_samp;x++) {
			if((names2[x] = (char *)calloc(50,sizeof(char))) == 0) {
				fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.22 \n");
				for(x=0;x<n_sam;x++) free(names[x]);
				free(names);
				free(DNA_matr);
				return(0);
			}
            /*copy duplicated data*/
            strncpy(names2[x],names[x],50);
        }
        /*copy duplicated data*/
        strncpy(DNA_matr2+(long int)n_site*(long int)0,DNA_matr+(long int)n_site*(long int)0,(long int)n_site*n_samp);
		/*end define and duplicate*/
		
		/*include data in *DNA_matr and in *names[] in the correct order*/
		if(input_format[0] == 'f') {
            for(x=0;x<nsamtot;x++) {
                strncpy(DNA_matr+(long int)n_site*(long int)x,DNA_matr2+(long int)n_site*(long int)(sort_nsam[0][x]),n_site);
                strncpy(names[x],names2[sort_nsam[0][x]],50);
            }
        }
        if(input_format[0] == 't') {
            for(x=0;x<nsamtot;x++) {
                for(xx=0;xx<n_site;xx++) {
                    DNA_matr [(((long int)n_samp*(unsigned long)xx)+(unsigned long)x)] =
                    DNA_matr2[(((long int)n_samp*(unsigned long)xx)+(unsigned long)sort_nsam[0][x])];
                }
                strncpy(names[x],names2[sort_nsam[0][x]],50);
            }
        }
		/*delete duplicated matr*/
		for(x=0;x<n_samp;x++) free(names2[x]);
		free(names2);
		free(DNA_matr2);
		
		/*erase lines no used*/
		if(nsamtot > n_sam) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: too low samples in the file according to defined in -N flag.\n");
			for(x=0;x<n_sam;x++) free(names[x]);
			free(names);
			free(DNA_matr);
			return(0);
		}
		/*for(x=nsamtot;x<n_sam;x++) free(names[x]);*/
        n_samp = nsamtot;
	}
	/*end option flag O*/
	
    if(ploidy==2)
		nsamtot *= 2; /*of ploidy=2 double samples*/
	*nsam = nsamtot;

	/*!--- Not used nsamuser_eff = (nsamtot)/ploidy ; */
		
	if(n_samp * ploidy < nsamtot) return(0);
	if(n_samp == 0 || n_site == 0) return(0);
	else {
		if(n_samp > 32167) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: too much samples. Only 32167 samples per loci are allowed.\n");
			return(0);
		}
		/*init matrix_sizepos*/
		/*if(*matrix_sizepos == 0) {*/
			if((*matrix_sizepos = (double *)malloc(n_site*sizeof(double))) == 0) {
				fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.2");
				for(x=0;x<n_sam;x++) free(names[x]);
				free(names);
				free(DNA_matr);
				return(0);
			}
			if((matrix_segrpos = (double *)malloc(n_site*sizeof(double))) == 0) {
				fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.2");
				for(x=0;x<n_sam;x++) free(names[x]);
				free(names);
				free(DNA_matr);
				free(*matrix_sizepos);
				return(0);
			}
		/*}*/
		for(xx=0;xx<n_site;xx++) {
			matrix_sizepos[0][xx] = (double)1;
			matrix_segrpos[xx] = (double)1;
		}
        if(ploidy==2 && input_format[0] == 'f'){
			if ((DNA_matr2 = (char *)calloc(n_site*(long int)n_samp*2,sizeof(char))) == 0) {
				fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.23 \n");
				for(x=0;x<n_sam;x++) free(names[x]);
				free(names);
				free(DNA_matr);
				free(*matrix_sizepos);
				free(matrix_segrpos);
				return(0);
			}
			if((names2 = (char **)calloc(n_samp*2,sizeof(char *))) == 0) {
				fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.12 \n");
				return(0);
			}
			for(x=0;x<n_samp*2;x++) {
				if((names2[x] = (char *)calloc(50,sizeof(char))) == 0) {
					fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.22 \n");
					return(0);
				}
			}
			for(x=0;x<n_samp;x++) {
				strncpy(DNA_matr2+(long int)n_site*(unsigned long)x*2,DNA_matr+(long int)n_site*(unsigned long)x,n_site);
				strncpy(DNA_matr2+(long int)n_site*(unsigned long)(x*2+1),DNA_matr+(long int)n_site*(unsigned long)x,n_site);	
				
				strncpy(names2[x*2],names[x],50);
				strncpy(names2[x*2+1],names[x],50);
				strncat(names2[x*2],".1\0",50);
				strncat(names2[x*2+1],".2\0",50);
			}
			for(xx=0;xx<n_site;xx++) {
				for(x=0;x<n_samp;x++) {
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 'w') {
						DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] = '1';
						DNA_matr2[(long int)n_site*(unsigned long)(x*2+1) + xx] = '4';
						/*fnut[0] += 1;*/
						/*fnut[3] += 1;*/
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 'm') {
						DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] = '2';
						DNA_matr2[(long int)n_site*(unsigned long)(x*2+1) + xx] = '4';
						/*fnut[1] += 1;*/
						/*fnut[3] += 1;*/
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 'r') {
						DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] = '3';
						DNA_matr2[(long int)n_site*(unsigned long)(x*2+1) + xx] = '4';
						/*fnut[2] += 1;*/
						/*fnut[3] += 1;*/
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 'y') {
						DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] = '1';
						DNA_matr2[(long int)n_site*(unsigned long)(x*2+1) + xx] = '2';
						/*fnut[0] += 1;*/
						/*fnut[1] += 1;*/
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 'k') {
						DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] = '1';
						DNA_matr2[(long int)n_site*(unsigned long)(x*2+1) + xx] = '3';
						/*fnut[0] += 1;*/
						/*fnut[2] += 1;*/
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 's') {
						DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] = '2';
						DNA_matr2[(long int)n_site*(unsigned long)(x*2+1) + xx] = '3';
						/*fnut[1] += 1;*/
						/*fnut[2] += 1;*/
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 't') {
						DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] = '1';
						DNA_matr2[(long int)n_site*(unsigned long)(x*2+1) + xx] = '5';
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 'c') {
						DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] = '2';
						DNA_matr2[(long int)n_site*(unsigned long)(x*2+1) + xx] = '5';
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 'g') {
						DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] = '3';
						DNA_matr2[(long int)n_site*(unsigned long)(x*2+1) + xx] = '5';
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 'a') {
						DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] = '4';
						DNA_matr2[(long int)n_site*(unsigned long)(x*2+1) + xx] = '5';
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 'T') {
						/*fnut[0] += 1;*/					
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 'C') {
						/*fnut[1] += 1;*/					
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 'G') {
						/*fnut[2] += 1;*/					
					}
					if(DNA_matr2[(long int)n_site*(unsigned long)x*2 + xx] == 'A') {
						/*fnut[3] += 1;*/					
					}
				}
			}
			n_samp *= 2;
		}
		else {
			if((DNA_matr2 = (char *)calloc((long int)n_site*n_samp,sizeof(char))) == 0) {
				fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.23 \n");
				for(x=0;x<n_sam;x++) free(names[x]);
				free(names);
				free(DNA_matr);
				free(*matrix_sizepos);
				free(matrix_segrpos);
				return(0);
			}
			if((names2 = (char **)calloc(n_samp*1,sizeof(char *))) == 0) {
				fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.12 \n");
				return(0);
			}
			for(x=0;x<n_samp*1;x++) {
				if((names2[x] = (char *)calloc(50,sizeof(char))) == 0) {
					fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.22 \n");
					return(0);
				}
			}
            for(x=0;x<n_samp*1;x++) {
                if(input_format[0] == 'f') {
                    strncpy(DNA_matr2+(long int)n_site*(unsigned long)x,DNA_matr+(long int)n_site*(unsigned long)x,n_site);
                }
                if(input_format[0] == 't') {
                    for(xx=0;xx<n_site;xx++) { /*transpose (...)*/
                        DNA_matr2[(((long int)n_site*(unsigned long)x)+(unsigned long)xx)] =
                        DNA_matr [(((long int)n_samp*(unsigned long)xx)+(unsigned long)x)];
                    }
                }
                strncpy(names2[x],names[x],50);
            }
		}
        /*mask data*/
        if(masked_nwindows>0) {
            for(x=0;x<n_samp;x++) {
                for(yy=0;yy<masked_nwindows;yy++) {
                    if(n_site > masked_wgenes[2*yy+1]) {
                        for(xx=masked_wgenes[2*yy+0];xx<=masked_wgenes[2*yy+1];xx++) {
                            DNA_matr2[(long int)n_site*(unsigned long)x+xx] = '5';
                        }
                    }
                }
            }
        }
        
        /*here include a function to filter positions: to read gff files (if necessary)*/
		if(gfffiles == 1) {
			/*include**name_fileinputgff,*subset_positions,ifgencode,*codename,*genetic_code,*matrix_sizepos,n_samp,n_site,*DNA_matr*/
			/*the function read the gff file and cut the DNA_matr, also gives the number of positions in matrix_sizepos and count the total in n_site*/
			/*modify values in matrix_sizepos*/
			/*also modify values in matrix_segrpos, only for syn/nsyn variants (that is, in case counting syn positions but the variant is nsyn, reject it)*/
			if(use_gff(name_fileinputgff,subset_positions,genetic_code,*matrix_sizepos,n_samp,n_site,DNA_matr2,matrix_segrpos,
					   file_output/*,mainargc*/,file_output_gz,file_logerr,file_logerr_gz,include_unknown,criteria_transcript,output,outgroup_presence,*nsam-1) == 0) {
                /*in case option -G call the start and end of each gene: NOT DONE YET*/
				/*if error realloc DNA_matr*/
				for(x=0;x<n_sam;x++) free(names[x]);
				free(names);
				free(DNA_matr);
				free(DNA_matr2);
				free(*matrix_sizepos);
				free(matrix_segrpos);
				return(0);
			}
		}
		else {
			if(file_ws != 0) {
				/*define the weights*/
				for(xx=0;xx<n_site;xx++) {
					matrix_sizepos[0][xx] = (double)wP [xx];
					matrix_segrpos[xx]    = (double)wPV[xx]/* * wV[nsit-1]*/;
                    /*
                    if((double)wP[xx]>(double)0 && wP[xx]<(double)0.1)
                        printf("%ld: %f\n",xx,wP[xx]);
                    */
				}
			}
		}
		/*rewrite fasta files of the specific filtered region (by gff, excluding experiments using sil/syn/nsyn)*/
		if(refasta == 1) {
            fzprintf(file_logerr,file_logerr_gz,"\nRewrite fasta file for specific regions...");
            fflush(stdout);
            /*
            memset(file_fas_char, 0, MSP_MAX_FILENAME);
			strcpy(file_fas_char, file_in);
			strcat(file_fas_char,"_fasta");
			strcat(file_fas_char,".fas");
			if( (file_fas = fzopen( file_fas_char, "w", file_fas_gz)) == 0) {
				fzprintf(file_output,file_output_gz,"\n It is not possible to write the fasta file %s.", file_fas_char);
			}
			else {
            */
                file_fas = file_output;
                file_fas_gz = file_output_gz;

                if(nwindows>0) {
                    for(x=0;x<n_samp;x++) {
                        fzprintf(file_fas,file_fas_gz,">%s\n",names2[x]);
                        for(yy=0;yy<nwindows;yy++) {
                            for(xx=wgenes[2*yy+0];xx<=wgenes[2*yy+1];xx++) {
                                if(DNA_matr2[(long int)n_site*(unsigned long)x+xx] == '1') {
                                    fzprintf(file_fas,file_fas_gz,"T");
                                }
                                if(DNA_matr2[(long int)n_site*(unsigned long)x+xx] == '2') {
                                    fzprintf(file_fas,file_fas_gz,"C");
                                }
                                if(DNA_matr2[(long int)n_site*(unsigned long)x+xx] == '3') {
                                    fzprintf(file_fas,file_fas_gz,"G");
                                }
                                if(DNA_matr2[(long int)n_site*(unsigned long)x+xx] == '4') {
                                    fzprintf(file_fas,file_fas_gz,"A");
                                }
                                if(DNA_matr2[(long int)n_site*(unsigned long)x+xx] == '5') {
                                    fzprintf(file_fas,file_fas_gz,"N");
                                }
                                if(DNA_matr2[(long int)n_site*(unsigned long)x+xx] == '6') {
                                    fzprintf(file_fas,file_fas_gz,"-");
                                }
                            }
                        }
                        fzprintf(file_fas,file_fas_gz,"\n");
                    }
                    fzclose(file_fas,file_fas_gz);
                }
                else {
                    for(x=0;x<n_samp;x++) {
                        fzprintf(file_fas,file_fas_gz,">%s\n",names2[x]);
                        for(xx=0;xx<n_site;xx++) {
                            if(DNA_matr2[(long int)n_site*(unsigned long)x+xx] == '1') {
                                fzprintf(file_fas,file_fas_gz,"T");
                            }
                            if(DNA_matr2[(long int)n_site*(unsigned long)x+xx] == '2') {
                                fzprintf(file_fas,file_fas_gz,"C");
                            }
                            if(DNA_matr2[(long int)n_site*(unsigned long)x+xx] == '3') {
                                fzprintf(file_fas,file_fas_gz,"G");
                            }
                            if(DNA_matr2[(long int)n_site*(unsigned long)x+xx] == '4') {
                                fzprintf(file_fas,file_fas_gz,"A");
                            }
                            if(DNA_matr2[(long int)n_site*(unsigned long)x+xx] == '5') {
                                fzprintf(file_fas,file_fas_gz,"N");
                            }
                            if(DNA_matr2[(long int)n_site*(unsigned long)x+xx] == '6') {
                                fzprintf(file_fas,file_fas_gz,"-");
                            }
                        }
                        fzprintf(file_fas,file_fas_gz,"\n");
                    }
                    fzclose(file_fas,file_fas_gz);
                    
                    if(gfffiles == 1 || file_es != 0) {
                        memset(file_weights_char, 0, MSP_MAX_FILENAME);
                        if(file_out[0]=='\0') strcpy(file_weights_char, file_in);
                        else strcpy(file_weights_char, file_out);
                        sprintf(file_weights_char,"%s_npops%d_nsam%d",file_weights_char,(npops>0?npops:1),nsamtot);
                        if(gfffiles == 1) {
                            strcat(file_weights_char,"_");
                            strcat(file_weights_char,subset_positions);
                            strcat(file_weights_char,"_");
                            strcat(file_weights_char,criteria_transcript);
                        }
                        if(file_ws != 0) {
                            strcat(file_weights_char,"_IncludedWeightFile");
                        }
                        if(include_unknown) strcat(file_weights_char,"_IncludeMissingVariantsmhits");
                        else strcat(file_weights_char,"_ExcludeMissingVariantsmhits");
                        if(outgroup_presence==0) strcat(file_weights_char,"_NOoutg");
                        if(outgroup_presence==1) strcat(file_weights_char,"_outg");
                        if(ploidy==1) strcat(file_weights_char,"_ploidy1");
                        if(ploidy==2) strcat(file_weights_char,"_ploidy2");
                        strcat(file_weights_char,"_WEIGHTS.gz");
                        if( (file_weights = fzopen( file_weights_char, "w", &file_weights_gz)) == 0) {
                            fzprintf(file_output,file_output_gz,"\n It is not possible to write the weigths file %s.", file_weights_char);
                            exit(1);
                        }
                        file_weights_gz.index = &file_weights_gz_index;

                        if(gfffiles == 0 && (file_es != 0)) fzprintf(file_weights,&file_weights_gz,"#POSITION\tWEIGHTVARX");
                        if(gfffiles == 1 && (file_es == 0)) fzprintf(file_weights,&file_weights_gz,"#POSITION\tWEIGHTPOS\tWEIGHTVAR");
                        if(gfffiles == 1 && (file_es != 0)) fzprintf(file_weights,&file_weights_gz,"#POSITION\tWEIGHTPOS\tWEIGHTVAR\tWEIGHTVARX");
                        fzprintf(file_weights,&file_weights_gz,"\n");
                        
                        for(xx=0;xx<n_site;xx++) {
                            if(gfffiles == 1 || file_es != 0) fzprintf(file_weights,&file_weights_gz,"%ld\t",xx+1);
                            if(gfffiles == 1) {
                                /*fzprintf(file_weights,&file_weights_gz,"\t");*/
                                fzprintf(file_weights,&file_weights_gz, "%.3f\t",matrix_sizepos[0][xx]);
                                /*if(matrix_sizepos[0][xx] == 0.0) fzprintf(file_weights,&file_weights_gz,"%.3f\t",(double)0);
                                else */fzprintf(file_weights,&file_weights_gz,"%.3f\t",matrix_segrpos[xx]);
                            }
                            dd=0;
                            if(file_es != 0) {
                                fzprintf(file_weights,&file_weights_gz,"\t");
                                if(Pp[dd] == xx+1) {
                                    fzprintf(file_weights,&file_weights_gz,"%.3e\t",wV[dd]);
                                    dd++;
                                }
                                else
                                    fzprintf(file_weights,&file_weights_gz,"NA\t");
                            }
                            if(gfffiles == 1 || file_es != 0) fzprintf(file_weights,&file_weights_gz,"\n");
                        }
                        if(gfffiles == 1 || file_es != 0) fzclose(file_weights,&file_weights_gz);
                    }
               }
            /*}*/
		}

		/*PRINT TFASTA: IT SHOULD NOT BE HERE THIS "FUNCTION"!!*/
		/*PRINT TFASTA: IT SHOULD NOT BE HERE THIS "FUNCTION"!!*/
		/*PRINT TFASTA: IT SHOULD NOT BE HERE THIS "FUNCTION"!!*/
		/*PRINT TFASTA: IT SHOULD NOT BE HERE THIS "FUNCTION"!!*/
		/*PRINT TFASTA: IT SHOULD NOT BE HERE THIS "FUNCTION"!!*/
		/*PRINT TFASTA: IT SHOULD NOT BE HERE THIS "FUNCTION"!!*/
		/*PRINT TFASTA: IT SHOULD NOT BE HERE THIS "FUNCTION"!!*/
		/*PRINT TFASTA: IT SHOULD NOT BE HERE THIS "FUNCTION"!!*/

		if(tfasta == 1) {
            /*printf("\nWriting tfasta file...");*/
            fflush(stdout);
            fzprintf(file_logerr,file_logerr_gz,"\nWriting tfasta file...");
            /*
			memset(file_fas_char, 0, MSP_MAX_FILENAME);
			strcpy(file_fas_char, file_in);
			strcat(file_fas_char,"_");
			strcat(file_fas_char,subset_positions);
			strcat(file_fas_char,"_");
			strcat(file_fas_char,criteria_transcript);
			if(outgroup_presence==0) strcat(file_fas_char,"_outg0");
			if(outgroup_presence==1) strcat(file_fas_char,"_outg1");
			if(ploidy==1) strcat(file_fas_char,"_ploidy1");
			if(ploidy==2) strcat(file_fas_char,"_ploidy2");
			strcat(file_fas_char,".tfa");
			if( (file_fas = fzopen( file_fas_char, "w", file_fas_gz)) == 0) {
				fzprintf(file_output,file_output_gz,"\n It is not possible to write the tfasta file %s.", file_fas_char);
			}
			else {
			*/
                file_fas = file_output;
                file_fas_gz = file_output_gz;

                /*fzprintf(file_fas,file_fas_gz,"#PLOIDY: ");
                for(x=0;x<n_samp;x++) {
                    fzprintf(file_fas,file_fas_gz,"%d ",ploidy);
                }
                fzprintf(file_fas,file_fas_gz,"\n");*/
                fzprintf(file_fas,file_fas_gz,"#NAMES: ");
				for(x=0;x<n_samp;x++) {
					fzprintf(file_fas,file_fas_gz,">%s ",names2[x]);
				}
				fzprintf(file_fas,file_fas_gz,"\n");
				/*if(gfffiles == 0 && file_es == 0) */fzprintf(file_fas,file_fas_gz,"#POSITION\tGENOTYPES");
                fzprintf(file_fas,file_fas_gz,"\n");
            
                if(gfffiles == 1 || file_es != 0) {
                    memset(file_weights_char, 0, MSP_MAX_FILENAME);
                    if(file_out[0]=='\0') strcpy(file_weights_char, file_in);
                    else strcpy(file_weights_char, file_out);
                    sprintf(file_weights_char,"%s_npops%d_nsam%d",file_weights_char,(npops>0?npops:1),nsamtot);
                    if(gfffiles == 1) {
                        strcat(file_weights_char,"_");
                        strcat(file_weights_char,subset_positions);
                        strcat(file_weights_char,"_");
                        strcat(file_weights_char,criteria_transcript);
                    }
                    if(file_ws != 0) {
                        strcat(file_weights_char,"_IncludedWeightFile");
                    }
                    if(include_unknown) strcat(file_weights_char,"_IncludeMissingVariantsmhits");
                    else strcat(file_weights_char,"_ExcludeMissingVariantsmhits");
                    if(outgroup_presence==0) strcat(file_weights_char,"_NOoutg");
                    if(outgroup_presence==1) strcat(file_weights_char,"_outg");
                    if(ploidy==1) strcat(file_weights_char,"_ploidy1");
                    if(ploidy==2) strcat(file_weights_char,"_ploidy2");
                    strcat(file_weights_char,"_WEIGHTS.gz");
                    if( (file_weights = fzopen( file_weights_char, "w", &file_weights_gz)) == 0) {
                        fzprintf(file_output,file_output_gz,"\n It is not possible to write the weigths file %s.", file_weights_char);
                        exit(1);
                    }
                    file_weights_gz.index = &file_weights_gz_index;
                    if(gfffiles == 0 && (file_es != 0)) fzprintf(file_weights,&file_weights_gz,"#POSITION\tWEIGHTVARX");
                    if(gfffiles == 1 && (file_es == 0)) fzprintf(file_weights,&file_weights_gz,"#POSITION\tWEIGHTPOS\tWEIGHTVAR");
                    if(gfffiles == 1 && (file_es != 0)) fzprintf(file_weights,&file_weights_gz,"#POSITION\tWEIGHTPOS\tWEIGHTVAR\tWEIGHTVARX");
                    fzprintf(file_weights,&file_weights_gz,"\n");
                }
				dd = 0;

				for(xx=0;xx<n_site;xx++) {
                    fzprintf(file_fas,file_fas_gz,"%ld\t",xx+1);
                    if(gfffiles == 1 || file_es != 0) fzprintf(file_weights,&file_weights_gz,"%ld\t",xx+1);
					for(x=0;x<n_samp;x++) {
						/*if(x != 0 && ploidy == 1) fzprintf(file_fas,file_fas_gz,",");*/
						/*if(x != 0 && ploidy == 2 && x/2 == (float)x/2.0) fzprintf(file_fas,file_fas_gz,",");*/
						switch (DNA_matr2[(long int)n_site*(unsigned long)x+xx]) {
							case '1':
								fzprintf(file_fas,file_fas_gz,"T");
								break;
							case '2':
								fzprintf(file_fas,file_fas_gz,"C");
								break;
							case '3':
								fzprintf(file_fas,file_fas_gz,"G");
								break;
							case '4':
								fzprintf(file_fas,file_fas_gz,"A");
								break;
							case '5':
								fzprintf(file_fas,file_fas_gz,"N");
								break;
							case '6':
								fzprintf(file_fas,file_fas_gz,"-");
								break;
							default:
								fzprintf(file_fas,file_fas_gz,"%c",DNA_matr2[(long int)n_site*(unsigned long)x+xx]);
								break;
						}
					}
					if(gfffiles == 1) {
						/*fzprintf(file_weights,&file_weights_gz,"\t");*/
						fzprintf(file_weights,&file_weights_gz,"%.3f\t",matrix_sizepos[0][xx]);
						/*if(matrix_sizepos[0][xx] == 0.0) fzprintf(file_weights,&file_weights_gz,"%.3f\t",(double)0);
						else */fzprintf(file_weights,&file_weights_gz,"%.3f\t",matrix_segrpos[xx]);
					}
					if(file_es != 0) {
						fzprintf(file_weights,&file_weights_gz,"\t");
						if(Pp[dd] == xx+1) {
							fzprintf(file_weights,&file_weights_gz,"%.3e\t",wV[dd]);
							dd++;
						}
						else 
							fzprintf(file_weights,&file_weights_gz,"NA\t");
					}
                    fzprintf(file_fas,file_fas_gz,"\n");
                    if(gfffiles == 1 || file_es != 0) fzprintf(file_weights,&file_weights_gz,"\n");
				}
			/*}
			fzclose(file_fas,file_fas_gz);
			*/
            if(gfffiles == 1 || file_es != 0) fzclose(file_weights,&file_weights_gz);
		}
		if(format[0] == 't' || format[0] == 'f' || format[0] == '0') 
			return(1);
		
		/*END PRINT TFASTA*/
		/*END PRINT TFASTA*/
		/*END PRINT TFASTA*/
		/*END PRINT TFASTA*/
		/*END PRINT TFASTA*/
		/*END PRINT TFASTA*/
		/*END PRINT TFASTA*/
		/*END PRINT TFASTA*/
		/*END PRINT TFASTA*/
		/*END PRINT TFASTA*/
		/*END PRINT TFASTA*/
		/*END PRINT TFASTA*/
		
        /***** print MASK in a file ******/
        memset(mask_name, 0, MSP_MAX_FILENAME);
        if(file_out[0]=='\0') strcpy(mask_name, file_in);
        else strcpy(mask_name, file_out);
        sprintf(mask_name,"%s_npops%d_nsam%d",mask_name,npops,nsamtot);
        if(gfffiles == 1) {
            strcat(mask_name,"_");
            strcat(mask_name,subset_positions);
            strcat(mask_name,"_");
            strcat(mask_name,criteria_transcript);
        }
        if(file_ws != 0) {
            strcat(mask_name,"_IncludedWeightFile");
        }
        if(include_unknown) strcat(mask_name,"_IncludeMissingVariantsmhits");
        else strcat(mask_name,"_ExcludeMissingVariantsmhits");
        if(outgroup_presence==0) strcat(mask_name,"_NOoutg");
        if(outgroup_presence==1) strcat(mask_name,"_outg");
        if(ploidy==1) strcat(mask_name,"_ploidy1");
        if(ploidy==2) strcat(mask_name,"_ploidy2");
        strcat(mask_name,"_MASK.txt");
        if((file_mask = fzopen(mask_name,"w",&file_mask_gz)) == 0) {
            fzprintf(file_logerr,file_logerr_gz,"Error in mask file %s.",mask_name);
            exit(1);
        }
        for(xx=0;xx<n_site;xx++) {
            fzprintf(file_mask,&file_mask_gz,"%.3f ",matrix_sizepos[0][xx]); /*print the value of each position*/
        }
        fzprintf(file_mask,&file_mask_gz,"\n");
        for(x=0;x<nsamtot/ploidy;x++) {
            for(xx=0;xx<n_site;xx++) {
                w = *(DNA_matr+(((long int)n_site*(unsigned long)x)+(unsigned long)xx));
                if(w >= 48+5) fzprintf(file_mask,&file_mask_gz,"0");/*missing*/
                else fzprintf(file_mask,&file_mask_gz,"1");/*normal*/
            }
            fzprintf(file_mask,&file_mask_gz,"\n");
            if(ploidy==2) {
                for(xx=0;xx<n_site;xx++) {
                    w = *(DNA_matr+(((long int)n_site*(unsigned long)x)+(unsigned long)xx));
                    if(w >= 48+5) fzprintf(file_mask,&file_mask_gz,"0");/*missing*/
                    else fzprintf(file_mask,&file_mask_gz,"1");/*normal*/
                }
                fzprintf(file_mask,&file_mask_gz,"\n");
            }
        }

        fzclose(file_mask,&file_mask_gz); /*!added*/
        /****** end print MASK file ******/

        /*count positions with missing values after weighting regions*/
		/*init*/
		summatrix_sizepos[0] = 0.;
		fnut[0]=fnut[1]=fnut[2]=fnut[3]=(float)0;
		*mis_pos = (int *)calloc(n_site,sizeof(int));
		for(xx=0;xx<n_site;xx++) mis_pos[0][xx] = 0;
		/*find missing*/
		for(xx=0;xx<n_site;xx++) {
			for(x=0;x<nsamtot;x++) {
				switch(DNA_matr2[(unsigned long)n_site*(unsigned long)x + xx]) {
					case '1':
						fnut[0] += matrix_sizepos[0][xx];
						break;
					case '2':
						fnut[1] += matrix_sizepos[0][xx];
						break;
					case '3':
						fnut[2] += matrix_sizepos[0][xx];
						break;
					case '4':
						fnut[3] += matrix_sizepos[0][xx];
						break;
					case '8':
						mis_pos[0][xx] += 1; 
						break;
					case '9':
						mis_pos[0][xx] += 1; 
						break;
					default:
						mis_pos[0][xx] += 1; 
						break;
				}
			}
			mis_pos[0][xx] *= matrix_sizepos[0][xx];
			summatrix_sizepos[0] += matrix_sizepos[0][xx];
		}
		
		
		/*Define the arrays to use in the next function*/
		if((*CpGp = (int *)calloc(n_site,sizeof(int))) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.00 \n");
			return(0);
		}
		if((*Tp = (int *)calloc(n_site,sizeof(int))) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.00 \n");
			return(0);
		}
		if((*Cp = (int *)calloc(n_site,sizeof(int))) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.00 \n");
			return(0);
		}
		if((*Gp = (int *)calloc(n_site,sizeof(int))) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.00 \n");
			return(0);
		}
		if((*Ap = (int *)calloc(n_site,sizeof(int))) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.00 \n");
			return(0);
		}
		if((*GCp = (int *)calloc(n_site,sizeof(int))) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.00 \n");
			return(0);
		}
		if((*svp = (int *)calloc(n_site,sizeof(int))) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_fasta.00 \n");
			return(0);
		}
		if((*nsites1_pop = (double **)calloc((unsigned long)n_site,sizeof(double *))) == NULL) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.6 \n");
			exit(1);
		}
		if((*nsites2_pop = (double **)calloc((unsigned long)n_site,sizeof(double *))) == NULL) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.7 \n");
			exit(1);
		}
		if((*nsites3_pop = (double **)calloc((unsigned long)n_site,sizeof(double *))) == NULL) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.8 \n");
			exit(1);
		}
		if((*nsites1_pop_outg = (double **)calloc((unsigned long)n_site,sizeof(double *))) == NULL) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.9 \n");
			exit(1);
		}
		if((*nsites2_pop_outg = (double **)calloc((unsigned long)n_site,sizeof(double *))) == NULL) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.10 \n");
			exit(1);
		}
		if((*nsites3_pop_outg = (double **)calloc((unsigned long)n_site,sizeof(double *))) == NULL) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.11 \n");
			exit(1);
		}
		
		if((*sum_sam = (double **)calloc((unsigned long)n_site,sizeof(double *))) == NULL) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.12 \n");
			exit(1);
		}
		if((*pwmatrix_miss = (float **)calloc((unsigned long)n_site,sizeof(float *))) == NULL) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.12 \n");
			exit(1);
		}
        if(npops==0) {
            npops = 1;
            nsamuser[0] = n_samp;
        }
		for(x=0;x<n_site;x++) {
			if((sum_sam[0][x] = (double *)calloc((unsigned long)n_samp,sizeof(double))) == NULL) {
				fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.13 \n");
				exit(1);
			}
			/*if(format[0] != 'm') {*/
 				if((pwmatrix_miss[0][x] = (float *)calloc((unsigned long)(npops-outgroup_presence)*(npops-outgroup_presence-1)/2,sizeof(float))) == NULL) {
					fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.13 \n");
					exit(1);
				}
				if((nsites1_pop[0][x] = (double *)calloc((unsigned long)npops-outgroup_presence,sizeof(double))) == NULL) {
					fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.6 \n");
					exit(1);
				}
				if((nsites2_pop[0][x] = (double *)calloc((unsigned long)npops-outgroup_presence,sizeof(double))) == NULL) {
					fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.7 \n");
					exit(1);
				}
				if((nsites3_pop[0][x] = (double *)calloc((unsigned long)npops-outgroup_presence,sizeof(double))) == NULL) {
					fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.8 \n");
					exit(1);
				}
				if((nsites1_pop_outg[0][x] = (double *)calloc((unsigned long)npops-outgroup_presence,sizeof(double))) == NULL) {
					fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.9 \n");
					exit(1);
				}
				if((nsites2_pop_outg[0][x] = (double *)calloc((unsigned long)npops-outgroup_presence,sizeof(double))) == NULL) {
					fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.10 \n");
					exit(1);
				}
				if((nsites3_pop_outg[0][x] = (double *)calloc((unsigned long)npops-outgroup_presence,sizeof(double))) == NULL) {
					fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.11 \n");
					exit(1);
				}
			/*}*/
		}
		
		/*function to analyze all data*/
		if(get_obsstats_mod(file_output,file_output_gz,file_logerr,file_logerr_gz,n_samp,n_site,length_al_real,DNA_matr2,*matrix_sizepos,matrix_segrpos,matrix_pol,matrix_pos,length_al,
							length_seg,include_unknown,outgroup_presence,svratio,nmissing,format,nsamuser,npops,*sum_sam,svp,
							*pwmatrix_miss,CpG, *CpGp, GCs, *Tp, *Cp, *Gp, *Ap,*GCp, *nsites1_pop,
							*nsites2_pop,*nsites3_pop,*nsites1_pop_outg,*nsites2_pop_outg,*nsites3_pop_outg) == 0) {
			for(x=0;x<n_sam;x++) free(names[x]);
			free(names);
			free(DNA_matr);
			free(DNA_matr2);
			free(*matrix_sizepos);
			free(matrix_segrpos);			
			return(0);
		}
        /*
		for(xx=0;xx<n_site;xx++) {
			matrix_sizepos[0][xx] *= matrix_segrpos[xx]; 
		}
        */
        if(gfffiles == 1) {
            memset(file_weights_char, 0, MSP_MAX_FILENAME);
            if(file_out[0]=='\0') strcpy(file_weights_char, file_in);
            else strcpy(file_weights_char, file_out);
            sprintf(file_weights_char,"%s_npops%d_nsam%d",file_weights_char,npops,nsamtot);
            strcat(file_weights_char,"_");
            strcat(file_weights_char,subset_positions);
            strcat(file_weights_char,"_");
            strcat(file_weights_char,criteria_transcript);
            if(include_unknown) strcat(file_weights_char,"_IncludeMissingmhits");
            else strcat(file_weights_char,"_ExcludeMissingmhits");
            if(outgroup_presence==0) strcat(file_weights_char,"_NOoutg");
            if(outgroup_presence==1) strcat(file_weights_char,"_outg");
            if(ploidy==1) strcat(file_weights_char,"_ploidy1");
            if(ploidy==2) strcat(file_weights_char,"_ploidy2");
            strcat(file_weights_char,"_WEIGHTS.gz");
            if( (file_weights = fzopen( file_weights_char, "w", &file_weights_gz)) == 0) {
                fzprintf(file_output,file_output_gz,"\n It is not possible to write the weigths file %s.", file_weights_char);
                exit(1);
            }
            file_weights_gz.index = &file_weights_gz_index;
            fzprintf(file_weights,&file_weights_gz,"#POSITION\tWEIGHTPOS\tWEIGHTVAR");
            fzprintf(file_weights,&file_weights_gz,"\n");

            for(xx=0;xx<n_site;xx++) {
                fzprintf(file_weights,&file_weights_gz,"%ld\t",xx+1);
                fzprintf(file_weights,&file_weights_gz,"%.3f\t",matrix_sizepos[0][xx]);
                /*if(matrix_sizepos[0][xx] == 0.0) fzprintf(file_weights,&file_weights_gz,"%.3f\t",(double)0);
                 else */fzprintf(file_weights,&file_weights_gz,"%.3f\t",matrix_segrpos[xx]);
                fzprintf(file_weights,&file_weights_gz,"\n");
            }
            fzclose(file_weights,&file_weights_gz);
        }
        *lenR = n_site;
	}
	
	return(1);
}


int var_char(FILE *file_input, SGZip *file_input_gz,FILE *file_logerr, SGZip *file_logerr_gz,long int *count,int *c,int *n_sam,long int *n_sit,int *nseq,int *maxsam,char ***names,char **DNA_matr,
			 long int *n_site,int excludelines,char *name_excluded,int *n_excl,int includelines,char *name_ingroups,char *name_outgroup,
			 int outgroup,int ploidy/*, float *fnut*//*, float *CpG*/)
{
    int  aa = 0;
    int  bb = 0;
    long int  dd;
    double ee;
    char *strin;
    /*long int t;*/
	/*float Cp = 0.0;*/
    
    aa = assigna(file_input,file_input_gz,c,nseq,maxsam,names);
	if(aa == 1) {
		if(outgroup > 0) {
			if(((strin = strstr(names[0][*nseq-1],name_outgroup)) == 0)) {
				if(excludelines > 0) {
					if(((strin = strstr(names[0][*nseq-1],name_excluded)) != 0)) {
						*nseq -= 1;
						*n_excl += 1;
						*c = fzgetc(file_input, file_input_gz);
						while(*c != '*' && *c != -1 && *c != 0 && *c != '>')
							*c = fzgetc(file_input, file_input_gz);
						aa = 0;
					}
				}
				if(includelines > 0) {
					if(((strin = strstr(names[0][*nseq-1],name_ingroups)) == 0)) {
						*nseq -= 1;
						*n_excl += 1;
						*c = fzgetc(file_input, file_input_gz);
						while(*c != '*' && *c != -1 && *c != 0 && *c != '>')
							*c = fzgetc(file_input, file_input_gz);
						aa = 0;
					}
				}
			}
		}
		else {
			if(excludelines > 0) {
				if(((strin = strstr(names[0][*nseq-1],name_excluded)) != 0)) {
					*nseq -= 1;
					*n_excl += 1;
					*c = fzgetc(file_input, file_input_gz);
					while(*c != '*' && *c != -1 && *c != 0 && *c != '>')
						*c = fzgetc(file_input, file_input_gz);
					aa = 0;
				}
			}
			if(includelines > 0) {
				if(((strin = strstr(names[0][*nseq-1],name_ingroups)) == 0)) {
					*nseq -= 1;
					*n_excl += 1;
					*c = fzgetc(file_input, file_input_gz);
					while(*c != '*' && *c != -1 && *c != 0 && *c != '>')
						*c = fzgetc(file_input, file_input_gz);
					aa = 0;
				}
			}
		}
	}
    if(aa == 1) {
		/*Cp = 0.0;*/
        while(bb == 0) {
            dd = (long int)floor((double)*count/(double)10000);
            ee = (double)*count/(double)10000;
            
            if(dd == ee) {
				/*
                if((t=(((long int)dd+(long int)1)*(long int)10000)) > 2147483647) {
                    puts("Error: too much positions.\n");
                    return(0);
                }
				*/
                if((*DNA_matr = realloc(*DNA_matr,((long int)dd+(long int)1)*(long int)10000*sizeof(char))) == 0) {
                    puts("Error: realloc error varchar.1\n");
                    return(0);
                }    
            }
            switch(*c/* = fzgetc(file_input,file_input_gz)*/) {
                case 'T':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '1';
					/*fnut[0] += 1;*/
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 't':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '1';
					if(ploidy==2) 
						DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 't';
					/*fnut[0] += 1;*/
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'U':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '1';
 					/*fnut[0] += 1;*/
                   *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'u':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '1';
					if(ploidy==2) 
						DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 't';
					/*fnut[0] += 1;*/
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'C':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '2';
 					/*fnut[1] += 1;*/
                   *count += 1;
                    *n_sit += 1;
					/*Cp = 1.0;*/
                    break;
                case 'c':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '2';
					if(ploidy==2) 
						DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'c';
 					/*fnut[1] += 1;*/
                   *count += 1;
                    *n_sit += 1;
					/*Cp = 1.0;*/
                    break;
                case 'G':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '3';
					/*fnut[2] += 1;*/
                    *count += 1;
                    *n_sit += 1;
					/*if(Cp == 1.0) *CpG += 1.0;*/
					/*if(Cp == 0.5) *CpG += 0.5;*/
                    break;
                case 'g':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '3';
					if(ploidy==2) 
						DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'g';
 					/*fnut[2] += 1;*/
					*count += 1;
                    *n_sit += 1;
					/*if(Cp == 1.0) *CpG += 1.0;*/
					/*if(Cp == 0.5) *CpG += 0.5;*/
                    break;
                case 'A':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '4';
					/*fnut[3] += 1;*/
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'a':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '4';
					if(ploidy==2) 
						DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'a';
					/*fnut[3] += 1;*/
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 0:
                    bb = 1; /*in FASTA case*/
					/*Cp = 0.0;*/
                    break;
                case -1:
                    bb = 1; /*in FASTA case*/
					/*Cp = 0.0;*/
                    break;
                case 10:
                    break;
                case 13:
                    break;
                case 32:
                    break;
                case '*': /* in NBRF case*/
                    bb = 1;
					/*Cp = 0.0;*/
                    break;
                case '>': /* in FASTA case*/
                    bb = 1;
					/*Cp = 0.0;*/
                    break;
				case 'N':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'n':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case '?':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
				case '-':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '6';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
					/*degenerated are converted to N*/
                case 'W':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'w';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'w':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'w';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'M':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'm';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.5;*/
                    break;
                case 'm':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'm';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.5;*/
                    break;
                case 'R':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'r';
                    *count += 1;
                    *n_sit += 1;
					/*if(Cp == 1.0) *CpG += 0.5;*/
					/*if(Cp == 0.5) *CpG += 0.25;*/
                    break;
                case 'r':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'r';
                    *count += 1;
                    *n_sit += 1;
					/*if(Cp == 1.0) *CpG += 0.5;*/
					/*if(Cp == 0.5) *CpG += 0.25;*/
                    break;
                case 'Y':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'y';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.5;*/
                    break;
                case 'y':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'y';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.5;*/
                    break;
                case 'K':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'k';
                    *count += 1;
                    *n_sit += 1;
					/*if(Cp == 1.0) *CpG += 0.5;*/
					/*if(Cp == 0.5) *CpG += 0.25;*/
                    break;
                case 'k':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 'k';
                    *count += 1;
                    *n_sit += 1;
					/*if(Cp == 1.0) *CpG += 0.5;*/
					/*if(Cp == 0.5) *CpG += 0.25;*/
                    break;
                case 'S':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 's';
                    *count += 1;
                    *n_sit += 1;
					/*if(Cp == 1.0) *CpG += 0.5;*/
					/*if(Cp == 0.5) *CpG += 0.25;*/
					/*if(Cp == 0.0) *CpG += 0.5;*/
                    break;
                case 's':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = 's';
                    *count += 1;
                    *n_sit += 1;
					/*if(Cp == 1.0) *CpG += 0.5;*/
					/*if(Cp == 0.5) *CpG += 0.25;*/
					/*if(Cp == 0.0) *CpG += 0.5;*/
                    break;
                case 'b':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'B':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'd':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'D':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'h':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'H':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
				case 'v':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
                case 'V':
                    DNA_matr[0][(((long int)*n_site*(unsigned long)*n_sam)+(unsigned long)*n_sit)] = '5';
                    *count += 1;
                    *n_sit += 1;
					/*Cp = 0.0;*/
                    break;
				default:
                    fzprintf(file_logerr,file_logerr_gz,"Unexpected value in file");
                    fzprintf(file_logerr,file_logerr_gz,"%d",*c);
                    return(0);
                    break;
            }
            if(*c !='>'/*|| *c != 0 || *c != -1*/) *c = fzgetc(file_input, file_input_gz);
        }
        *n_sam += 1;
        if(*n_site == 0) *n_site = *n_sit;
        else if(*n_site != *n_sit) {
            fzprintf(file_logerr,file_logerr_gz,"The number of sites are not equal in all lines in the alignment.");
            return(0);
        }
    }
    return 1;
}

int assigna(FILE *file_input, SGZip *file_input_gz,int *c,int *nseq,int *maxsam,char ***names)
{
    int N_VAR = 2;
    char var_file[2][50]  =
    {
        { ">"},
        { ">DL;"},
    };
	
    int i_;
    int j;
    int nn;
    int x;
    int c0; 
    
    j = 0;
    for(i_=0;i_<N_VAR;i_++) {
        while((var_file[i_][j]) == *c && (var_file[i_][j]) != '\0' && c != '\0') {
            *c = fzgetc(file_input, file_input_gz);
            j++;
        }
    }
    if(j<4 && j>0) i_= 1;/*FASTA*/
    else if(j==4) i_= 2;/*NBRF*/
	else {
		i_=0;/*NO ACCEPTED*/
		if(*c != 0 && *c != -1) *c = fzgetc(file_input, file_input_gz);
	}
	
    if((i_ == 2  && *c != 0 && *c != -1)) { /* NBRF files */
        nn = 0;
        while(*c != '\0' && *c != 13 && *c != 10 && nn < 50-2) {
            if(*c != '\t' && *c != 32) {
				names[0][*nseq][nn] = (char)*c;
				nn++;
			}
			*c = fzgetc(file_input, file_input_gz);
        }
        names[0][*nseq][nn] = '\0';
        *nseq += 1;
        if(*nseq == *maxsam) {
            *maxsam += 32;
            if(*maxsam > 32767) {
                puts("\n Sorry, no more samples are allowed.");
				return 0;
            }
            if ((*names = (char **)realloc(*names,*maxsam*sizeof(char *))) == 0) {
                puts("\nError: memory not reallocated. assigna.1 \n");
                return(0);
            }
            for(x=*nseq;x<*maxsam;x++) {
                if ((names[0][x] = (char *)calloc(50,sizeof(char))) == 0) {
                    puts("\nError: memory not reallocated. assigna.2 \n");
                    return(0);
                }
            }
        }
        /*use unix or macos or dos format. begin*/
        while(*c != '\0' && *c != 13 && *c != 10 && *c != -1 && *c != 0  && *c>0)
            *c = fzgetc(file_input, file_input_gz);
		
        c0 = *c;
        *c = fzgetc(file_input, file_input_gz);
        if(c0 == 13 && *c == 10) *c = fzgetc(file_input, file_input_gz);
        while(*c != 10 && *c != 13 && *c != -1 && c != 0) 
            *c = fzgetc(file_input, file_input_gz);
        if(*c == -1 || *c == 0) {
            puts("\n Unexpected end of file");
            return(0);
        }
        c0 = *c;
        *c = fzgetc(file_input, file_input_gz);
        if(c0 == 13 && *c == 10) *c = fzgetc(file_input, file_input_gz);
        if(*c == -1 || *c == 0) {
            puts("\n Unexpected end of file");
            return(0);
        }
        /*use unix or macos or dos format. end*/
        
        return(1);
    }
    else {	
        if(i_ == 1 && *c != 0 && *c != -1) {	/* FASTA files */
            nn = 0;
            while(*c != '\0' && *c != 13 && *c != 10 && nn < 50-2) {
				if(*c != '\t' && *c != 32) {
					names[0][*nseq][nn] = (char)*c;
					nn++;
				}
				*c = fzgetc(file_input, file_input_gz);
            }
            names[0][*nseq][nn] = '\0';
            *nseq += 1;
            if(*nseq == *maxsam) {
                *maxsam += 32;
                if(*maxsam > 32767) {
                    puts("\n Sorry, no more samples are allowed.");
					return 0;
                }
                if ((*names = (char **)realloc(*names,*maxsam*sizeof(char *))) == 0) {
                    puts("\nError: memory not reallocated. assigna.1 \n");
                    return(0);
                }
                for(x=*nseq;x<*maxsam;x++) {
                    if ((names[0][x] = (char *)calloc(50,sizeof(char))) == 0) {
                        puts("\nError: memory not reallocated. assigna.2 \n");
                        return(0);
                    }
                }
            }
            /*use Unix / MacOS / DOS format. begin*/
            while(*c != '\0' && *c != 13 && *c != 10 && *c != -1 && *c != 0  && *c>0)
                *c = fzgetc(file_input, file_input_gz);
			
            c0 = *c;
            *c = fzgetc(file_input, file_input_gz);
            if(c0 == 13 && *c == 10) *c = fzgetc(file_input, file_input_gz);
            if(*c == -1 || *c == 0) {
                puts("\n Unexpected end of file");
                return 0;
            }
            /*use Unix / MacOS / DOS format. end*/
            return(1);
        }
        else return(0);
    }
    return 0;
}


int read_coordinates(FILE *file_wcoor, SGZip *file_wcoor_gz, FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz, long int **wgenes, long int *nwindows) {
    
    char *valn=0;
    int c,x;
    long int xx;
    long int dd;
    double ee;
    
    /*printf("\nReading coordinates file...");*/
    fflush(stdout);
    fzprintf(file_logerr,file_logerr_gz,"\nReading coordinates file...");
   
    if((valn = (char *)calloc(100,sizeof(char))) == 0) {
        fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_coordinates.00 \n");
        return(0);
    }
    if((*wgenes = (long int *)calloc(10000,sizeof(long int))) == 0) {
        fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. read_coordinates.0 \n");
        return(0);
    }
    
    *nwindows = 0;
    c = fzgetc(file_wcoor, file_wcoor_gz);
    if(c=='#') {
        while(c != 13 && c != 10 && c != 0 && c != -1)
            c = fzgetc(file_wcoor, file_wcoor_gz); /*exclude header*/
    }
    while(c == 13 || c == 10)
        c = fzgetc(file_wcoor, file_wcoor_gz);
    if(c==0 || c==-1 || c < 1) {
        fzprintf(file_logerr,file_logerr_gz,"\nError: no coordinates assigned, read_coordinates.2 \n");
        free(*wgenes);
        file_wcoor=0;
        return(0);
    }
    else {
        xx=0;
        while (c != 0 && c != -1) {
            /*now keep all values: two columns, only numbers*/
            /*first column is the name of the scaffold*/
            while(c == 32 || c == 9 || c == 13 || c == 10)
                c = fgetc(file_wcoor);
            if(c==-1)
                break;
            x=0;
            while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100 && c>0) {
                valn[x] = c;
                c = fgetc(file_wcoor);
                x++;
            }
            valn[x] = '\0';/*scaffold name*/
            /*KEEP POSITIONS (first initial position, then end, next region and so on)*/
            while(c == 32 || c == 9 || c == 13 || c == 10)
                c = fzgetc(file_wcoor, file_wcoor_gz);
            if(c==-1)
                break;
            x=0;
            while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100 && c>0) {
                valn[x] = c;
                c = fzgetc(file_wcoor, file_wcoor_gz);
                x++;
            }
            valn[x] = '\0';
            wgenes[0][xx] = (long int)atof(valn)-1;
            
            xx++;
            while(c == 32 || c == 9 || c == 13 || c == 10)
                c = fgetc(file_wcoor);
            if(c==-1)
                break;
            x=0;
            while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100 && c>0) {
                valn[x] = c;
                c = fgetc(file_wcoor);
                x++;
            }
            valn[x] = '\0';
            wgenes[0][xx] = (long int)round((double)atof(valn));

            xx++;
            dd = (long int)floor((double)xx/(double)10000);
            ee = (double)xx/(double)10000;
            if(dd==ee) {
                if((*wgenes = realloc(*wgenes,((long int)(dd+1)*(long int)10000*(long int)sizeof(long int)))) == 0) {
                    puts("Error: realloc error read_coordinates.1\n");
                    free(*wgenes);
                    return(0);
                }    
            }
        }
        if(xx == 0) {
            fzprintf(file_logerr,file_logerr_gz,"\nError: no coordinates assigned, read_coordinates.2 \n");
            free(*wgenes);
            file_wcoor=0;
            return(0);
        }
        *nwindows = (xx)/2;
    }		
    free(valn);
    return 1;
}

int read_weights_positions_file(FILE *file_ws, SGZip *file_ws_gz,FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz, float **wP, float **wPV, float **wV) {
    
	/*!--- Not used long int position; */
    char *valn=0;
    long int dd;
    double ee;
    int c;
    int x;
    long int xx;
	
    /*read weights file*/
    /*printf("\nReading weight file...");*/
    fflush(stdout);
    fzprintf(file_logerr,file_logerr_gz,"\nReading weight file...");

    /*keep wP, wPV, wV (not used yet) for all positions, do not need to keep positions: all are correlative*/
    if(file_ws != 0) {
        if((*wP = (float *)calloc(1000,sizeof(float))) == 0) {
            fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.14 \n");
            return(0);
        }
        if((*wPV = (float *)calloc(1000,sizeof(float))) == 0) {
            fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.25 \n");
            return(0);
        }
        if((*wV = (float *)calloc(1000,sizeof(float))) == 0) {
            fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.23 \n");
            return(0);
        }
        if((valn = (char *)calloc(100,sizeof(char))) == 0) {
            fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.34 \n");
            return(0);
        }
        c = fzgetc(file_ws, file_ws_gz);
        while(c != 13 && c != 10 && c != 0 && c != -1)
            c = fzgetc(file_ws, file_ws_gz); /*exclude header*/
        while(c == 13 || c == 10)
            c = fzgetc(file_ws, file_ws_gz);
        if(c==0 || c==-1 || c < 1) {
            file_ws=0;
            *wP=0;
            *wPV=0;
            *wV=0;
            free(*wP);
            free(*wPV);
            free(*wV);
            fzprintf(file_logerr,file_logerr_gz,"\nError: no weights assigned \n");
            return(0);
        }
        else {
            /*now keep all values: three or four columns, only numbers or decimals*/
            xx=0;
            while (c != 0 && c != -1) {
                /*POSITION*/
                while(c == 32 || c == 9 || c == 13 || c == 10)
                    c = fzgetc(file_ws, file_ws_gz);
                if(c==0 || c==-1 || c < 1)
                    break;
                x=0;
                while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100 && c>0) {
                    valn[x] = c;
                    c = fzgetc(file_ws, file_ws_gz);
                    x++;
                }
                valn[x] = '\0';
                /*!--- Not used position = atol(valn); */
                
                /*Weight Position*/
                while(c == 32 || c == 9)/* || c == 13 || c == 10)*/
                    c = fzgetc(file_ws, file_ws_gz);
                if(c==0 || c==-1 || c < 1)
                    break;
                x=0;
                while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100 && c>0) {
                    valn[x] = c;
                    c = fzgetc(file_ws, file_ws_gz);
                    x++;
                }
                valn[x] = '\0';
                wP[0][xx] = (double)atof(valn);

                /*Weight Variant*/
                while(c == 32 || c == 9)/* || c == 13 || c == 10)*/
                    c = fzgetc(file_ws, file_ws_gz);
                if(c==0 || c==-1 || c < 1)
                    break;
                x=0;
                while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100 && c>0) {
                    valn[x] = c;
                    c = fzgetc(file_ws, file_ws_gz);
                    x++;
                }
                valn[x] = '\0';
                wPV[0][xx] = (double)atof(valn);
                
                while(c == 32 || c == 9) c = fzgetc(file_ws, file_ws_gz);
                if(!(c == 13 || c == 10 || c == 0 || c == -1)) {
                    /*Effect size*/
                    while(c == 32 || c == 9)/* || c == 13 || c == 10)*/
                        c = fzgetc(file_ws, file_ws_gz);
                    if(c==0 || c==-1 || c < 1)
                        break;
                    x=0;
                    while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100 && c>0) {
                        valn[x] = c;
                        c = fzgetc(file_ws, file_ws_gz);
                        x++;
                    }
                    valn[x] = '\0';
                    wV[0][xx] = atof(valn);
                } 
				else {
					wV[0][xx] = 1.0; /*if undefined the value is 1.0 for all*/
				}
                
                xx++;
                dd = (long int)floor((double)xx/(double)1000);
                ee = (double)xx/(double)1000;
                if(dd==ee) {
                    if((*wP = realloc(*wP,((long int)(dd+1)*(long int)1000*sizeof(float)))) == 0) {
                        file_ws=0;*wP=0;*wPV=0;*wV=0;
                        free(*wP);free(*wPV);free(*wV);
                        puts("Error: realloc error get_obsdata.11\n");
                        return(0);
                    }
                    if((*wPV = realloc(*wPV,((long int)(dd+1)*(long int)1000*sizeof(float)))) == 0) {
                        file_ws=0;*wP=0;*wPV=0;*wV=0;
                        free(*wP);free(*wPV);free(*wV);
                        puts("Error: realloc error get_obsdata.11\n");
                        return(0);
                    }
                    if((*wV = realloc(*wV,((long int)(dd+1)*(long int)1000*sizeof(float)))) == 0) {
                        file_ws=0;*wP=0;*wPV=0;*wV=0;
                        free(*wP);free(*wPV);free(*wV);
                        puts("Error: realloc error get_obsdata.11\n");
                        return(0);
                    }
                }
            }
        }
        free(valn);
    }
    else return(0);
    
    return(1);
}


int read_weights_file(FILE *file_es, SGZip *file_es_gz, FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz, float **wV, long int **Pp, long int *nV) {

	long int *effsz_site=0; /*positions*/
	float    *effsz_wght=0; /*effect sizes*/
	long int tot_effszP = 0; /*total values*/
	char *valn=0;
	long int dd;
	double ee;
	int c;
	int x;
	long int xx;

    /*printf("\nReading Effect sizes file...");*/
    fflush(stdout);
    fzprintf(file_logerr,file_logerr_gz,"\nReading Effect sizes file...");
    
    if(file_es != 0) {
		if((effsz_site = (long int *)calloc(1000,sizeof(long int))) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.1 \n");
			return(0);
		}
		if((effsz_wght = (float *)calloc(1000,sizeof(float))) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.2 \n");
			return(0);
		}
		if((valn = (char *)calloc(100,sizeof(char))) == 0) {
			fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.3 \n");
			return(0);
		}

		c = fzgetc(file_es, file_es_gz);

		while(c != 13 && c != 10 && c != 0 && c != -1)
			c = fzgetc(file_es, file_es_gz); /*exclude header*/

		while(c == 13 || c == 10) 
			c = fzgetc(file_es, file_es_gz);

		if(c==0 || c==-1 || c < 1) {
			file_es=0;
			*wV=0;
			free(effsz_site);
			free(effsz_wght);
            fzprintf(file_logerr,file_logerr_gz,"\nError: no effect sizes assigned \n");
            return(0);
		}
		else {
			/*now keep all values: two columns, only numbers or decimals*/
			xx=0;
			while (c != 0 && c != -1) {
				/*POSITION*/
				while(c == 32 || c == 9 || c == 13 || c == 10) 
					c = fzgetc(file_es, file_es_gz);
				if(c==-1)
					break;
				x=0;
				while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100 && c>0) {
					valn[x] = c;
					c = fzgetc(file_es, file_es_gz);
					x++;
				}
				valn[x] = '\0';
				effsz_site[xx] = (double)atof(valn);
				
				/*Effect size*/
				while(c == 32 || c == 9 || c == 13 || c == 10) 
					c = fzgetc(file_es, file_es_gz);
				if(c==-1)
					break;
				x=0;
				while(c != 32 && c != 9 && c != 13 && c != 10 && c!=0 && c!=-1 && x < 100 && c>0) {
					valn[x] = c;
					c = fzgetc(file_es, file_es_gz);
					x++;
				}
				valn[x] = '\0';
				effsz_wght[xx] = (double)atof(valn);
				
				xx++;
				dd = (long int)floor((double)xx/(double)1000);
				ee = (double)xx/(double)1000;
				if(dd==ee) {
					if((effsz_site = realloc(effsz_site,((long int)(dd+1)*(long int)1000*sizeof(long int)))) == 0) {
                        file_es=0;*wV=0;
                        free(effsz_site);free(effsz_wght);
						puts("Error: realloc error get_obsdata.11\n");
						return(0);
					}    
					if((effsz_wght = realloc(effsz_wght,((long int)(dd+1)*(long int)1000*sizeof(float)))) == 0) {
                        file_es=0;*wV=0;
                        free(effsz_site);free(effsz_wght);
                        puts("Error: realloc errorget_obsdatavarchar.12\n");
						return(0);
					}    
				}
			}
			if(effsz_site[xx]== 0) xx--;
			tot_effszP = xx;/*total number of values added*/
			
			/*now we need to assign this values to the variant positions here observed and include them in wV vector*/
			if(xx>0) {
				if((*Pp = (long int *)calloc(xx,sizeof(long int))) == 0) {
                    file_es=0;*wV=0;
                    free(effsz_site);free(effsz_wght);
                    fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.3 \n");
					return(0);
				}
				if((*wV = (float *)calloc(xx,sizeof(float))) == 0) {
                    file_es=0;*wV=0;
                    free(effsz_site);free(effsz_wght);
                    fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsdata.2 \n");
					return(0);
				}
				for( x = 0; x < (int)xx; x++ ) {
					Pp[0][x] = effsz_site[x];
					wV[0][x] = effsz_wght[x];
				}
				*nV = tot_effszP;
			}
			free(effsz_site);
			free(effsz_wght);
		}
        free(valn);
	}
	/*end collecting data for effect sizes*/
	return 1;
}


int function_read_tfasta(FILE *file_input, SGZip *file_input_gz, FILE *file_logerr, SGZip *file_logerr_gz, long int init_site,long int end_site,int *n_sam, long int *n_site, char ***names, char **DNA_matr)
{
    char c[1];
    char *cc;
    char line[32767*2];
    int col=0;
    int nseq=0;
    int x;
    static int maxsam=128;
    long int position;
    long int end_position=0;
    long int dd,ee,count;
    
    /*if names and number of samples are defined then skip the definition of names*/
    *c = fzgetc(file_input, file_input_gz);
    if(*c == 0 || *c==-1  || *c=='\xff' || *c=='\xfe') return(-1);
    line[col] = *c;
    col++;
    
    while(*c=='#') {
        /*parse comments*/
        while(*c != 0 && *c!=-1 && *c!=10 && *c!=13 && *c!='\xff' && *c!='\xfe') {
            *c = fzgetc(file_input, file_input_gz);
            line[col] = *c;
            col++;
        }
        line[col] = '\0';
        if((cc=strstr(line, "#NAMES:")) != 0) {
            /*collect names*/
            nseq = 0;
            cc = strtok (line,">\n\r ");
            while (cc != NULL)
            {
                if(strstr(cc,"#NAMES:") == 0) {
                    strcpy(names[0][nseq],cc);
                    nseq++;
                    if(nseq == maxsam) {
                        maxsam += 32;
                        if(maxsam > 32767) {
                            puts("\n Sorry, no more than 32767 samples are allowed.");
                            return 0;
                        }
                        if ((*names = (char **)realloc(names,maxsam*sizeof(char *))) == 0) {
                            puts("\nError: memory not reallocated. assigna.1 \n");
                            return(0);
                        }
                        for(x=nseq;x<maxsam;x++) {
                            if ((names[0][x] = (char *)calloc(50,sizeof(char))) == 0) {
                                puts("\nError: memory not reallocated. assigna.2 \n");
                                return(0);
                            }
                        }
                    }
                }
                cc = strtok(NULL, ">\n\r ");
            }
            *n_sam = nseq;
        }
        col=0;
        *c = fzgetc(file_input, file_input_gz);
        line[col] = *c;
        col++;
    }
    
    /*include in DNAmatrix the positions from the init_site to the end_site (if defined)*/
    col = 0;
    while(*c != 0 && *c!=-1 && *c!=10 && *c!=13 && *c != 9 && *c != 32) {
        line[col] = *c;
        col++;
        *c = fzgetc(file_input, file_input_gz);
    }
	if(*c == 0 || *c==-1  || *c=='\xff' || *c=='\xfe') return(-1);
	
    line[col] = '\0';
    position = atol(line);
    if(end_site == -1) end_position = init_site + 1;
    while(position < init_site) {
        while(!(*c==10 || *c==13 || *c == -1 || *c == 0 || *c=='\xff' || *c=='\xfe')) *c = fzgetc(file_input, file_input_gz);
        if(*c < 0 || *c==10 || *c==13 || *c == -1 || *c == 0 || *c=='\xff' || *c=='\xfe') {
            while(*c==10 || *c==13) *c = fzgetc(file_input, file_input_gz);
            col = 0;
            while(*c != 0 && *c!=-1 && *c!=10 && *c!=13 && *c != 9 && *c != 32 && *c!='\xff' && *c!='\xfe' && *c>0) {
                line[col] = *c;
                col++;
                *c = fzgetc(file_input, file_input_gz);
            }
            line[col] = '\0';
            position = atol(line);
            if(end_site == -1) end_position = position + 1;
        }
    }
    *c = fzgetc(file_input, file_input_gz);
    *n_site = 0;
    col = 0;
    count=0;
    while (*n_site < end_position) {
        switch(*c) {
            case 'T':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '1';
                col += 1;
                count += 1;
                break;
            case 't':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '1';
                col += 1;
                count += 1;
                break;
            case 'U':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '1';
                col += 1;
                count += 1;
                break;
            case 'u':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '1';
                col += 1;
                count += 1;
                break;
            case 'C':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '2';
                col += 1;
                count += 1;
                break;
            case 'c':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '2';
                col += 1;
                count += 1;
                break;
            case 'G':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '3';
                col += 1;
                count += 1;
                break;
            case 'g':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '3';
                col += 1;
                count += 1;
                break;
            case 'A':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '4';
                col += 1;
                count += 1;
                break;
            case 'a':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '4';
                col += 1;
                count += 1;
                break;
            case 0:
                break;
            case -1:
                break;
            case 10:
                break;
            case 13:
                break;
            case 32:
                break;
            case 9:
                break;
            case 'N':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'n':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case '?':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case '-':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '6';
                col += 1;
                count += 1;
                break;
                /*gaps are converted to N*/
            case 'W':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = 'w';
                col += 1;
                count += 1;
                break;
            case 'w':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = 'w';
                col += 1;
                count += 1;
                break;
            case 'M':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = 'm';
                col += 1;
                count += 1;
                break;
            case 'm':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = 'm';
                col += 1;
                count += 1;
                break;
            case 'R':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = 'r';
                col += 1;
                count += 1;
                break;
            case 'r':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = 'r';
                col += 1;
                count += 1;
                break;
            case 'Y':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = 'y';
                col += 1;
                count += 1;
                break;
            case 'y':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = 'y';
                col += 1;
                count += 1;
                break;
            case 'K':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = 'k';
                col += 1;
                count += 1;
                break;
            case 'k':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = 'k';
                col += 1;
                count += 1;
                break;
            case 'S':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = 's';
                col += 1;
                count += 1;
                break;
            case 's':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = 's';
                col += 1;
                count += 1;
                break;
            case 'b':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'B':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'd':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'D':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'h':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'H':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'v':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            case 'V':
                DNA_matr[0][(((long int)nseq*(unsigned long)*n_site)+(unsigned long)col)] = '5';
                col += 1;
                count += 1;
                break;
            default:
                fzprintf(file_logerr,file_logerr_gz,"Unexpected value in tfa file: position %ld, sample %d: ",position,col);
                fzprintf(file_logerr,file_logerr_gz,"%c\n",*c);
                return(0);
                break;
        }
        if(*c == -1 || *c == 0) break;
        *c = fzgetc(file_input, file_input_gz);
        if(*c < 0 || *c==10 || *c==13 || *c == -1 || *c == 0) {
            while(*c==10 || *c==13) *c = fzgetc(file_input, file_input_gz);
            col = 0;
            while(*c != 0 && *c!=-1 && *c!=10 && *c!=13 && *c != 9 && *c != 32 && *c>0) {
                line[col] = *c;
                col++;
                *c = fzgetc(file_input, file_input_gz);
            }
            line[col] = '\0';
            col = 0;
            position = atol(line);
            *n_site += 1;
            if(end_site == -1) end_position = position + 1;
        }
        /*realloc DNAmatr if nnecessary*/
        dd = (long int)floor((double)count/(double)10000);
        ee = (double)count/(double)10000;
        if(dd == ee) {
            if((*DNA_matr = realloc(*DNA_matr,((long int)dd+(long int)1)*(long int)10000*sizeof(char))) == 0) {
                puts("Error: realloc error varchar.1\n");
                return(0);
            }
        }
    }
    /*return n_site,n_sam,DNA matrix and names in pointers*/
    
    return(1);
}
