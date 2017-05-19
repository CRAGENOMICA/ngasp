#include "main_fasta2ms2.h"
#include "zutil.h"
#include "zindex.h"

int main(int argc, const char * argv[]) {

	int x;
    char format[1];
    char input_format[10];
	int ploidy,outgroup;
	long int slide,window;
	int arg = 0;
	char *f;
	char msformat[10];
	
	int nsam;
	long int lenR,lenT,lenS;
	double lenP;
	long int *vector_pos;
	double *vector_sizepos;
	char *matrix_pol;
	long int nmissing;
	float summatrix_sizepos;
	int *mis_pos; /*vector with the number of Ns in each position*/
	float *fnut;
	int Physical_length;
    int include_unknown;
	int refasta;
	int tfasta;
    long int *wgenes;
    long int nwindows;
    long int *masked_wgenes;
    long int masked_nwindows;
	float CpG=0.0;
	float GCs=0.0;
	float svratio;
	int *CpGp,*Ap,*Cp,*Gp,*Tp,*GCp; /*CpG,A,C,G,T, GC per position 1/0*/
	
	long int *Pp=0; /*number of position (for effect sizes)*//*not used*/
	long int nV=0; /*number of variants at file ov variant weights (effect sizes)*//*not used*/
	float *wV=0;/*weight at variant (effect sizes)*//*not yet functional although we can recover*/
    float *wP=0;/*weight for each position*/
    float *wPV=0;/*weight for the variant at each position*/
	
	int *svp;/* transitions (1) or transversions (2) per polymorphic position*/
	float **pwmatrix_miss;/*pairwise matrix of differences per position*/
	double **sum_sam;
	double **nsites1_pop;
	double **nsites2_pop;
	double **nsites3_pop;
	double **nsites1_pop_outg;
	double **nsites2_pop_outg;
	double **nsites3_pop_outg;
	
	char file_in[ MSP_MAX_FILENAME];
	char file_out[MSP_MAX_FILENAME];
	char file_GFF[MSP_MAX_FILENAME];
	char file_effsz[MSP_MAX_FILENAME];
	char file_Wcoord[MSP_MAX_FILENAME];
    char file_wps[MSP_MAX_FILENAME];
    char file_masked[MSP_MAX_FILENAME];
    char file_log[MSP_MAX_FILENAME];
	
	FILE *file_input	= 	0;
	FILE *file_es   	= 	0;
	FILE *file_output	=	stdout;
	FILE *file_wcoor    =   0;
    FILE *file_ws   	= 	0;
    FILE *file_msk   	= 	0;
    FILE *file_logerr   =   stdout;

    SGZip file_input_gz;
    SGZip file_es_gz;
    SGZip file_output_gz;
    SGZip file_wcoor_gz;
    SGZip file_ws_gz;
    SGZip file_msk_gz;
    SGZip file_logerr_gz;

    struct SGZIndex file_output_gz_index;          /* This is the index for the output gz file. */


	/* GFF variables */
	int 	gfffiles			= 0;
	char 	subset_positions[ MSP_MAX_GFF_WORDLEN ];		
	char 	code_name[ MSP_GENETIC_CODETYPE_LEN ];
	char 	genetic_code[ MSP_GENCODE_COMBINATIONS ];
	char 	criteria_transcript[ MSP_GFF_CRITERIA_MSG_LEN ];
	
	/*sort samples*/
	int int_total_nsam_order=0; /*number of samples. value for ordering the samples in populations in case they are not consecutive*/
	int *sort_nsam=0; /*vector with the position in the file*/
	int sort_index;/*used in the loop*/
	
	/* variables defining more data*/
	int npops = 0;
	/* Number of samples for each population, each element a population */
	int *	vint_perpop_nsam = NULL;
	/* Population index */
	int pop_index = 0;
	/* Sum of all nsam of all populations */
	int int_total_nsam = 0;	

	memset( file_in,  0, MSP_MAX_FILENAME);
	memset( file_out, 0, MSP_MAX_FILENAME);
	memset( file_GFF, 0, MSP_MAX_FILENAME);
	memset( file_effsz,  0, MSP_MAX_FILENAME);
    memset( file_Wcoord, 0, MSP_MAX_FILENAME);
    memset( file_wps, 0, MSP_MAX_FILENAME);
    memset( file_masked, 0, MSP_MAX_FILENAME);
    memset( file_log, 0, MSP_MAX_FILENAME);
	

	/*defaults*/
	format[0] = 't';
	ploidy = 1;
	outgroup = 0;
	slide = 0;
	window = 0;
	refasta = 0;
	tfasta = 0;
    nwindows = 0;
	wgenes = 0;
    masked_nwindows = 0;
    masked_wgenes = 0;
	Physical_length = 1;
    include_unknown = 0;
	strcpy( criteria_transcript,"long\0");
	strcpy( subset_positions,"\0");
    strcpy( input_format,"fasta\0");
    strcpy( msformat,"tfasta\0");
    
    if((vint_perpop_nsam = (int *) calloc( (unsigned long)1, sizeof(int) )) == 0) {
        printf("Error allocating memory");
        exit(1);
    }
    /**/
	
	if( argc > 1 ) 
	{
		arg = 1;
		while(arg < argc)
		{
			if( argv[arg][0] != '-' ) 
			{
                if(argv[arg][0] == '>')
                    break;
                printf(" argument should be -%s ?\n", argv[arg]);
                usage();
                exit(1);
			}
			
			switch (argv[arg][1])
			{
                case 'i' : /* input file*/
                    arg++;
                    strcpy( file_in, argv[arg] );
                    break;
                case 'o' : /* output file */
                    arg++;
                    strcpy( file_out, argv[arg] );
                    if( (file_output = fzopen( file_out, "w", &file_output_gz)) == 0) {
                        fprintf(stdout,"\n It is not possible to write in the output file %s\n", file_out);
                        exit(1);
                    }
                    strcpy(file_log, file_out);
                    strcat(file_log,".log");
                    if( (file_logerr = fzopen( file_log, "w", &file_logerr_gz)) == 0) {
                        fprintf(stdout,"\n It is not possible to write the log file %s.", file_log);
                        exit(1);
                    }

                    file_output_gz.index = &file_output_gz_index;  /* Here, after openning the GZ file, the index is assigned to its output gz file. */

                    /*printf("\nOpen log file...");*/
                    fzprintf(file_logerr,&file_logerr_gz,"\nOpen log file...");
                    break;
                case 'F' : /* F fa or tfa */
                    arg++;
                    input_format[0] = argv[arg][0];
                    if(input_format[0] == 'f') strcpy(input_format,"fasta\0");
                    if(input_format[0] == 't') strcpy(input_format,"tfasta\0");
                    
                    if(input_format[0] != 'f' && input_format[0] != 't') {
                        printf("\n Error in -r argument: only the values 'f' (fasta) and 't' (tfasta) are allowed");
                        usage();
                        exit(1);
                    }
                    break;
				case 'f' : /* f fasta, tfasta, m ms format  */
					arg++;
					format[0] = argv[arg][0];
					if(format[0] == 'm') strcpy(msformat,"ms\0");
					if(format[0] == 'x') strcpy(msformat,"x\0");
					if(format[0] == 't') strcpy(msformat,"tfasta\0");
                    if(format[0] == 'f') {strcpy(msformat,"fasta\0");refasta=1;}
					if(format[0] == '0') strcpy(msformat,"null\0");
						
					if(format[0] != 'm' && format[0] != 'x' && format[0] != 't' && format[0] != 'f' && format[0] != '0') {
						printf("\n Error in -f argument: only the values 'm' (ms), 'f' (fasta), t (tfasta) or 0(nothing) are allowed");
						usage();
						exit(1);
					}
					break;
				case 'p' : /* p Ploidy, 1: haploid, 2: diploid */
					arg++;
					ploidy = (int)atoi(argv[arg]);
					if(ploidy != 1 && ploidy != 2) {
						printf("\n Error in -p argument: only the values 1 or 2 are allowed.");
						usage();
						exit(1);
					}
					break;
				case 'g': /* g GFF file name, AND more words 
						   2nd : synonymous, nonsynonymous, silent or whatever
						   3rd : selected genetic code name or "Other"
						   next 64th's : in case of 'Other', provide 64 IUPAC letters of each codon. 
						   * Check order. 
						   */
					arg++;
					strcpy( file_GFF, argv[arg]);					
					arg++;
					strcpy( subset_positions, argv[arg] );
					
					gfffiles = 1;	
					
					/* Go if known coding option - */
					if( ( strcmp(subset_positions,"synonymous")==0 || 
						 strcmp(subset_positions,"nonsynonymous")==0 || 
						 strcmp(subset_positions,"silent")==0)) 
					{
						arg++;
						strcpy( code_name,argv[arg] ); 
						
						if( strcmp(code_name, "Nuclear_Universal") == 0 ) 
						{
							genetic_code[0] = 'F';
							genetic_code[1] = 'F';
							genetic_code[2] = 'L';
							genetic_code[3] = 'L';
							genetic_code[4] = 'S';
							genetic_code[5] = 'S';
							genetic_code[6] = 'S';
							genetic_code[7] = 'S';
							genetic_code[8] = 'Y';
							genetic_code[9] = 'Y';
							genetic_code[10] = '*';
							genetic_code[11] = '*';
							genetic_code[12] = 'C';
							genetic_code[13] = 'C';
							genetic_code[14] = '*';
							genetic_code[15] = 'W';
							genetic_code[16] = 'L';
							genetic_code[17] = 'L';
							genetic_code[18] = 'L';
							genetic_code[19] = 'L';
							genetic_code[20] = 'P';
							genetic_code[21] = 'P';
							genetic_code[22] = 'P';
							genetic_code[23] = 'P';
							genetic_code[24] = 'H';
							genetic_code[25] = 'H';
							genetic_code[26] = 'Q';
							genetic_code[27] = 'Q';
							genetic_code[28] = 'R';
							genetic_code[29] = 'R';
							genetic_code[30] = 'R';
							genetic_code[31] = 'R';
							genetic_code[32] = 'I';
							genetic_code[33] = 'I';
							genetic_code[34] = 'I';
							genetic_code[35] = 'M';
							genetic_code[36] = 'T';
							genetic_code[37] = 'T';
							genetic_code[38] = 'T';
							genetic_code[39] = 'T';
							genetic_code[40] = 'N';
							genetic_code[41] = 'N';
							genetic_code[42] = 'K';
							genetic_code[43] = 'K';
							genetic_code[44] = 'S';
							genetic_code[45] = 'S';
							genetic_code[46] = 'R';
							genetic_code[47] = 'R';
							genetic_code[48] = 'V';
							genetic_code[49] = 'V';
							genetic_code[50] = 'V';
							genetic_code[51] = 'V';
							genetic_code[52] = 'A';
							genetic_code[53] = 'A';
							genetic_code[54] = 'A';
							genetic_code[55] = 'A';
							genetic_code[56] = 'D';
							genetic_code[57] = 'D';
							genetic_code[58] = 'E';
							genetic_code[59] = 'E';
							genetic_code[60] = 'G';
							genetic_code[61] = 'G';
							genetic_code[62] = 'G';
							genetic_code[63] = 'G';
						}
						else if(strcmp(code_name,"mtDNA_Drosophila")==0) 
						{
							genetic_code[0] = 'F';
							genetic_code[1] = 'F';
							genetic_code[2] = 'L';
							genetic_code[3] = 'L';
							genetic_code[4] = 'S';
							genetic_code[5] = 'S';
							genetic_code[6] = 'S';
							genetic_code[7] = 'S';
							genetic_code[8] = 'Y';
							genetic_code[9] = 'Y';
							genetic_code[10] = '*';
							genetic_code[11] = '*';
							genetic_code[12] = 'C';
							genetic_code[13] = 'C';
							genetic_code[14] = 'W';
							genetic_code[15] = 'W';
							genetic_code[16] = 'L';
							genetic_code[17] = 'L';
							genetic_code[18] = 'L';
							genetic_code[19] = 'L';
							genetic_code[20] = 'P';
							genetic_code[21] = 'P';
							genetic_code[22] = 'P';
							genetic_code[23] = 'P';
							genetic_code[24] = 'H';
							genetic_code[25] = 'H';
							genetic_code[26] = 'Q';
							genetic_code[27] = 'Q';
							genetic_code[28] = 'R';
							genetic_code[29] = 'R';
							genetic_code[30] = 'R';
							genetic_code[31] = 'R';
							genetic_code[32] = 'I';
							genetic_code[33] = 'I';
							genetic_code[34] = 'M';
							genetic_code[35] = 'M';
							genetic_code[36] = 'T';
							genetic_code[37] = 'T';
							genetic_code[38] = 'T';
							genetic_code[39] = 'T';
							genetic_code[40] = 'N';
							genetic_code[41] = 'N';
							genetic_code[42] = 'K';
							genetic_code[43] = 'K';
							genetic_code[44] = 'S';
							genetic_code[45] = 'S';
							genetic_code[46] = 'S';
							genetic_code[47] = 'S';
							genetic_code[48] = 'V';
							genetic_code[49] = 'V';
							genetic_code[50] = 'V';
							genetic_code[51] = 'V';
							genetic_code[52] = 'A';
							genetic_code[53] = 'A';
							genetic_code[54] = 'A';
							genetic_code[55] = 'A';
							genetic_code[56] = 'D';
							genetic_code[57] = 'D';
							genetic_code[58] = 'E';
							genetic_code[59] = 'E';
							genetic_code[60] = 'G';
							genetic_code[61] = 'G';
							genetic_code[62] = 'G';
							genetic_code[63] = 'G';
						}
						else if( strcmp(code_name,"mtDNA_Mammals") == 0 ) 
						{
							genetic_code[0] = 'F';
							genetic_code[1] = 'F';
							genetic_code[2] = 'L';
							genetic_code[3] = 'L';
							genetic_code[4] = 'S';
							genetic_code[5] = 'S';
							genetic_code[6] = 'S';
							genetic_code[7] = 'S';
							genetic_code[8] = 'Y';
							genetic_code[9] = 'Y';
							genetic_code[10] = '*';
							genetic_code[11] = '*';
							genetic_code[12] = 'C';
							genetic_code[13] = 'C';
							genetic_code[14] = 'W';
							genetic_code[15] = 'W';
							genetic_code[16] = 'L';
							genetic_code[17] = 'L';
							genetic_code[18] = 'L';
							genetic_code[19] = 'L';
							genetic_code[20] = 'P';
							genetic_code[21] = 'P';
							genetic_code[22] = 'P';
							genetic_code[23] = 'P';
							genetic_code[24] = 'H';
							genetic_code[25] = 'H';
							genetic_code[26] = 'Q';
							genetic_code[27] = 'Q';
							genetic_code[28] = 'R';
							genetic_code[29] = 'R';
							genetic_code[30] = 'R';
							genetic_code[31] = 'R';
							genetic_code[32] = 'I';
							genetic_code[33] = 'I';
							genetic_code[34] = 'M';
							genetic_code[35] = 'M';
							genetic_code[36] = 'T';
							genetic_code[37] = 'T';
							genetic_code[38] = 'T';
							genetic_code[39] = 'T';
							genetic_code[40] = 'N';
							genetic_code[41] = 'N';
							genetic_code[42] = 'K';
							genetic_code[43] = 'K';
							genetic_code[44] = 'S';
							genetic_code[45] = 'S';
							genetic_code[46] = '*';
							genetic_code[47] = '*';
							genetic_code[48] = 'V';
							genetic_code[49] = 'V';
							genetic_code[50] = 'V';
							genetic_code[51] = 'V';
							genetic_code[52] = 'A';
							genetic_code[53] = 'A';
							genetic_code[54] = 'A';
							genetic_code[55] = 'A';
							genetic_code[56] = 'D';
							genetic_code[57] = 'D';
							genetic_code[58] = 'E';
							genetic_code[59] = 'E';
							genetic_code[60] = 'G';
							genetic_code[61] = 'G';
							genetic_code[62] = 'G';
							genetic_code[63] = 'G';
						}
						else if( strcmp(code_name,"Other") == 0 ) {
							for(x=0;x<64;x++) {
								arg++;
								if(argv[arg][0] == '-') {
									printf("\n Error in -g argument: In case use \"Other\", include the genetic code of the 64 aa values.");
									usage();
									exit(1);
								}
								genetic_code[x] = atoi(argv[arg]);
							}
						}
						else {
							printf(" %s: Unknown code, sorry", code_name);
							exit(1);
						}	
					}
					break;
				case 'c' : /* c Criteria used for analyzing the transcripts */
					/* Basically, max or min */
					arg++;
					strcpy(criteria_transcript,argv[arg]);
					if(strcmp( criteria_transcript, "max")!=0  && 
					   strcmp( criteria_transcript, "min")!=0  && 
					   strcmp( criteria_transcript, "first")!=0   && 
					   strcmp( criteria_transcript, "long")!=0  ) 
					{
						printf("\n Error: the argument -c has only the choices 'max', 'min', 'first' or 'long'.");
						usage();
						exit(1);
					}
					break;
				case 'G' : /* outgroup present or not */
					arg++;
					outgroup = (int)atoi(argv[arg]);
					if(outgroup != 0 && outgroup != 1) {
						printf("\n Error in -o argument: only the values 0 or 1 are allowed.");
						usage();
						exit(1);
					}
					break;
				case 'w' : /* window size (ms format)*/
					arg++;
					window = (long int)atol(argv[arg]);
					break;
				case 's' : /* slide size (ms format)*/
					arg++;
					slide = (long int)atol(argv[arg]);
					break;					
				case 'P' : /* physical length or effective length (only valid positions) */
					arg++;
					Physical_length = (int)atoi(argv[arg]);
					if(Physical_length != 0 && Physical_length != 1) {
						printf("\n Error in -P argument: only the values 0 or 1 are allowed.");
						usage();
						exit(1);
					}
					break;
				/*case 'r' :
					arg++;
					refasta = (int)atoi(argv[arg]);
					if(refasta != 0 && refasta != 1) {
						printf("\n Error in -r argument: only the values 0 or 1 are allowed.");
						usage();
						exit(1);
					}
					break;*/
				case 'O' : /* O the order of each individual in the original data, Warning!, followed by
							O numbers indicating the order (0 is the first) in case samples are not consecutive. Only for fasta data!
							*/
					arg++;
					int_total_nsam_order = atoi(argv[arg]);
					if((sort_nsam = (int *) calloc( (unsigned long)int_total_nsam_order, sizeof(int) )) == 0) {
						printf("Error allocating memory");
						exit(1);
					}
					for( sort_index = 0; sort_index < int_total_nsam_order; sort_index++ ) 
					{
						arg++;
						sort_nsam[ sort_index ] = atoi( argv[arg] );
					}					
					break;
				case 'N' : /* N number of populations, Warning!, followed by
							N numbers indicating the sample size of each population
							*/
                    free(vint_perpop_nsam);

                    arg++;
					npops = atoi(argv[arg]);
					if((vint_perpop_nsam = (int *) calloc( (unsigned long)npops, sizeof(int) )) == 0) {
						printf("Error allocating memory");
						exit(1);
					}
					int_total_nsam = 0;
					for( pop_index = 0; pop_index < npops; pop_index++ ) 
					{
						arg++;
						vint_perpop_nsam[ pop_index ] = atoi( argv[arg] );
						int_total_nsam += vint_perpop_nsam[ pop_index ];
					}					
					break;
				/*case 't' : 
                 arg++;
					tfasta = (int)atoi(argv[arg]);
					if(tfasta != 0 && tfasta != 1) {
						printf("\n Error in -t argument: only the values 0 or 1 are allowed.");
						usage();
						exit(1);
					}
					break;*/
                case 'u' : /* -u missing data considered  */
                    arg++;
                    include_unknown = (int)atoi(argv[arg]);
                    if(include_unknown != 0 && include_unknown != 1) {
                        printf("\n Error in -u argument: only the values 0 or 1 are allowed.");
                        usage();
                        exit(1);
                    }
                    break;
				case 'W' : /* file with the coordinates of each window [init end](overwrite options -w and -s)*/
					arg++;
					strcpy(file_Wcoord, argv[arg] );					
					break;
                case 'E' : /*file with the weight for each position */
                    arg++;
                    strcpy(file_wps, argv[arg]);
                    break;
				case 'e' : /*file with the effect size of each variant */ /*NOT YET INCLUDED IN THE PROGRAM!!!!!*/
					arg++;
					strcpy(file_effsz, argv[arg]);
					break;
                case 'm' : /* file with the coordinates of each window [init end] to be masked by Ns*/
                    arg++;
                    strcpy(file_masked, argv[arg] );
                    break;
				case 'h' : /* h HELP */
					usage();
					exit(0);
					break;
			}
			arg++;
		}
	}
	else {
		usage();
		exit(0);
	}
    
    /*default*/
    /*
    #TO FORBIDE
    # [-g -c] + [-E]
    # [-P] without [-g -c]
    # [-P] without [-E]
    # [-f tfasta] + [-w -s]
    # [-f fasta]  + [-w -s]
    # [-W] + [-w -s]
     */
    if(input_format[0] != 'f' && ploidy != 1) {
        fzprintf(file_output,&file_output_gz,"\n the option -p 2 is only available with fasta IUPAC input format");
        printf("\nThe option -p 2 is only available with fasta IUPAC input format\n");
        exit(1);
    }
	if(file_Wcoord[0]!=0 && (slide > 0 && window>0)) {
        fzprintf(file_output,&file_output_gz,"\n the option -W (coordinates file) is incompatible with definitions of -w (slide) and -s (slide)");
        printf("\nThe option -W (coordinates file) is incompatible with definitions of -w (slide) and -s (slide)\n");
        exit(1);
	}/*
	if(file_Wcoord[0]!=0 && (format[0] == 'f')) {
        fzprintf(file_output,&file_output_gz,"\n the option -W (coordinates file) is only incompatible with output -f m");
        exit(1);
	}
	if((slide > 0 && window>0) && (format[0] == 't' || format[0] == 'f')) {
        fzprintf(file_output,&file_output_gz,"\n the options -w (slide) and -s (slide) is only compatible with the output -f m");
        exit(1);
	}*/
    if(file_wps[0]!=0 && file_GFF[0]!=0) {
        fzprintf(file_output,&file_output_gz,"\n the option -g (gff file) is incompatible with option -E (weighting file)\n");
        exit(1);
    }
    if((format[0]=='t') && (file_Wcoord[0]!=0 || (slide > 0 && window>0) || Physical_length == 0)) {
        printf("\nWarning: The options -W or -w -s or -P are not effective using the output format -f tfasta\n");
    }
    if((format[0]=='f') && ((slide > 0 && window>0) || Physical_length == 0)) {
        printf("\nWarning: The options -w -s or -P are not effective using the output format -f fasta\n");
    }
    if(outgroup==1 && npops==0) {
        fzprintf(file_output,&file_output_gz,"\n the option -G (outgroup) needs to define option -N: the population samples of at least two pops\n");
        printf("\n the option -G (outgroup) needs to define option -N: the population samples of at least two pops\n");
        exit(1);
    }	
    if( format[0] == 'x' && npops==0) {
        fzprintf(file_output,&file_output_gz,"\n the option -f x require the option -N ");
        exit(1);
    }
    if(include_unknown == 1 && format[0]=='m') {
        include_unknown = 0;
        printf("Warning: The option -u 1 is only allowed in case GFF file is defined and the output format is not ms\n");
    }

    /*print all the argv. Header of the ms format*/
	fzprintf(file_output,&file_output_gz,"#fastaconvtr ");
	for(x=1;x<arg;x++) {
		fzprintf(file_output,&file_output_gz,"%s ",argv[x]);
	}
	fzprintf(file_output,&file_output_gz,"\n");
	
	/* Opening files */
	if( file_in[0] == '\0' ) {
		file_input = stdin;
	}
	else {
		if( (file_input = fzopen( file_in, "r", &file_input_gz)) == 0) {
			fzprintf(file_output,&file_output_gz,"\n It is not possible to open the input file %s\n", file_in);
			exit(1);
		}
	}
	/*open the file for weigth for positions, if included*/
	if( file_wps[0] == '\0') {
		file_ws = 0;
	}
	else {
		if( (file_ws = fzopen( file_wps, "r", &file_ws_gz)) == 0) {
			fzprintf(file_output,&file_output_gz,"\n It is not possible to open the weighting file %s\n", file_wps);
			exit(1);
		}
		if(read_weights_positions_file(file_ws,&file_ws_gz,file_output,&file_output_gz, file_logerr, &file_logerr_gz,&wP,&wPV,&wV) == 0) {
			fzprintf(file_output,&file_output_gz,"Error processing weighting file %s\n", file_wps);
			exit(1);
		}
	}
	/*open the file for effect sizes, if included*/
	if( file_effsz[0] == '\0') {
		file_es = 0;
		wV = 0;
	}
	else {
		if( (file_es = fzopen( file_effsz, "r", &file_es_gz)) == 0) {
			fzprintf(file_output,&file_output_gz,"\n It is not possible to open the effect sizes file %s\n", file_effsz);
			exit(1);
		}
		if(read_weights_file(file_es,&file_es_gz,file_output,&file_output_gz, file_logerr, &file_logerr_gz,&wV,&Pp,&nV) == 0) {
			fzprintf(file_output,&file_output_gz,"Error processing effect sizes file %s\n", file_effsz);
			exit(1);
		}
	}
	/* Opening coordinates file */
	if( file_Wcoord[0] == '\0' ) {
		file_wcoor = 0;
		nwindows = 0;
	}
	else {
		if( (file_wcoor = fzopen( file_Wcoord, "r", &file_wcoor_gz)) == 0) {
			fzprintf(file_output,&file_output_gz,"\n It is not possible to open the coordinates file %s\n", file_Wcoord);
			exit(1);
		}
		if(read_coordinates(file_wcoor,&file_wcoor_gz,file_output,&file_output_gz, file_logerr, &file_logerr_gz,&wgenes,&nwindows) == 0) {
			fzprintf(file_output,&file_output_gz,"Error processing coordinates file %s\n", file_Wcoord);
			exit(1);
		}
		window = -1; 
		slide = -1;
	}
    /* Opening mask coordinates file */
    if( file_masked[0] == '\0' ) {
        file_msk = 0;
        masked_nwindows = 0;
    }
    else {
        if( (file_msk = fzopen( file_masked, "r", &file_msk_gz)) == 0) {
            fzprintf(file_output,&file_output_gz,"\n It is not possible to open the masked coordinates file %s\n", file_masked);
            exit(1);
        }
        if(read_coordinates(file_msk,&file_msk_gz,file_output,&file_output_gz, file_logerr, &file_logerr_gz,&masked_wgenes,&masked_nwindows) == 0) {
            fzprintf(file_output,&file_output_gz,"Error processing masked coordinates file %s\n", file_masked);
            exit(1);
        }
    }
	
	
	/* Definition of a File Stream Buffer, for buffered IO */
	if( (f = (char *)malloc((unsigned long)BUFSIZ*10)) == NULL ) {
		fzprintf(file_output,&file_output_gz,"\nError: memory not reallocated. get_obsdata.4 \n");
		exit(1);
	}
	setbuf(file_input,f);
	
	/*Define arrays and vectors*/
	
	if((fnut = (float *)calloc((unsigned long)4,sizeof(float))) == NULL) {
		fzprintf(file_output,&file_output_gz,"\nError: memory not reallocated. get_obsdata.5 \n");
		exit(1);
	}
	if(format[0] == 't') 
		tfasta = 1;
	if(read_fasta(file_input,&file_input_gz,file_output,&file_output_gz, file_logerr, &file_logerr_gz,input_format,&nsam,&lenR,&lenT,&lenP,&lenS,&vector_pos,&matrix_pol,ploidy,gfffiles,
				  file_GFF,subset_positions,genetic_code,criteria_transcript,format,outgroup,
				  &vector_sizepos,&svratio,&summatrix_sizepos,&nmissing,&mis_pos,fnut,&CpG,&GCs,wV,&svp,&pwmatrix_miss,file_es,&file_es_gz,file_in,file_out,refasta,tfasta,
				  Pp,&CpGp,&Ap,&Cp,&Gp,&Tp,&GCp,&sort_nsam,&int_total_nsam_order,vint_perpop_nsam,
				  npops,&sum_sam, &nsites1_pop, &nsites2_pop, &nsites3_pop, &nsites1_pop_outg, &nsites2_pop_outg, &nsites3_pop_outg,wP,wPV,file_ws,&file_ws_gz,wgenes,nwindows,include_unknown,masked_wgenes,masked_nwindows) == 0) {
		fzprintf(file_output,&file_output_gz,"Error processing input data.\n");
		exit(1);
	}
	fzclose(file_input,&file_input_gz);
	if( file_effsz[0] != '\0') 
		fzclose(file_es,&file_es_gz);
	if(format[0] != 'm' && format[0]!= 'x') { /*!added parenthesis */
		/*!removed exit(0);*/
	} else {
		if(slide == 0 && window == 0) {
			slide = lenR;
			window = lenR;
		}
		if(write_msfile(file_output,&file_output_gz, file_logerr, &file_logerr_gz, nsam,lenR,lenT,lenP,lenS,vector_pos,vector_sizepos,matrix_pol,slide,window,svratio,
						summatrix_sizepos,nmissing,mis_pos,format,fnut,Physical_length,CpG,GCs,wV,nV,svp,pwmatrix_miss,tfasta,
						Pp,CpGp,Ap,Cp,Gp,Tp,GCp,wgenes,nwindows,vint_perpop_nsam,npops, sum_sam,
						nsites1_pop, nsites2_pop, nsites3_pop, nsites1_pop_outg, nsites2_pop_outg, nsites3_pop_outg,outgroup) == 0) {
			fzprintf(file_output,&file_output_gz,"Error printing %s ms file.\n",msformat);
			exit(1);
		}
		if(format[0] == 'e' || format[0] == 'x') free(mis_pos);
		free(fnut);

		free(sort_nsam);
	}
    
	/*!added. Here, we ensure that all files are closed before exiting */
	fzclose(file_output, &file_output_gz);
	fzclose(file_input, &file_input_gz);
	fzclose(file_ws, &file_ws_gz);
	fzclose(file_es, &file_es_gz);
	fzclose(file_wcoor, &file_wcoor_gz);
	fzclose(file_msk, &file_msk_gz);

    fzprintf(file_logerr,&file_logerr_gz,"\nProgram Ended\n");
    fzclose(file_logerr, &file_logerr_gz);


    /*
     * Test the just created GZ and INDEX files:
     * -----------------------------------------
    {
		FILE *h = 0;
		SGZip gz;

		h = fzopen("../Examples/output.tfa.gz", "r", &gz);

		if (h != NULL) {

			struct SGZIndex idx;
			load_index_from_file(gz.index_file_name, &idx);

		  long int row_num = 0;
			while (fzseek(h, &gz, &idx, NULL, &row_num, false) == GZ_OK) {

				char ch = ' ';
				while((!fzeof(h, &gz)) && (ch != '\n') && (ch != '\x0')) {
					ch = fzgetc(h, &gz);
					printf("%c", ch);
				}

				row_num++;
			}

			unload_all_index_positions(&idx);

			fzclose(h, &gz);
		}
		exit(0);
    }
    */


    return 0;
}
void usage(void) 
{
	printf(FASTA2MS2);
	printf("\nFlags:\n");
    printf("      -F [input format file: f (fasta), t (tfasta)]\n");/*fasta or tfasta formats are only available*/
    printf("      -i [path and name of the input file (text or gz)]\n");
    printf("      -f [output format file: t (tfasta), f (fasta), m (ms), 0(nothing)]\n");
    printf("      -o [path and name of the output file (preferentially .gz except ms files)]\n");
    printf("   OPTIONAL PARAMETERS:\n");
    printf("      -h [help and exit]\n");
    printf("      -P [define window lengths in 'physical' positions (1) or in 'effective' positions (0)]. DEFAULT: 1\n");
    printf("      -O [#_nsam] [Reorder samples: number order of first sample, number 0 is the first sample] [second sample] ...etc.\n");
    printf("      -W [for ms and fasta outputs, file with the coordinates of each window: (one header plus nlines with init end]\n");/*new!*/
    printf("      -N [#_pops] [#samples_pop1] ... [#samples_popN] (necessary in case to indicate the outgroup population)\n");
    printf("      -G [outgroup included (1) or not (0), last population (1/0)]. DEFAULT: 0\n");
    printf("      -u [Missing counted (1) or not (0) in weights given GFF annotation]. DEFAULT: 0\n");
    printf("      -m [masking regions: file indicating the start and the end of regions to be masked by Ns]\n");
    printf("     Outputing ms format:\n");
    printf("      -w [window size]. DEFAULT: Total_length\n");
    printf("      -s [slide size]. DEFAULT: Total_length\n");
    printf("     Inputing fasta format:\n");
    printf("      -p [if fasta input, haplotype:1 (single sequence) genotype:2 (two mixed sequences in IUPAC). DEFAULT: 1\n");
    printf("     Annotation file and weight options:\n");
    printf("      -g [GFF_file]\n");
    printf("         [add also: coding,noncoding,synonymous,nonsynonymous,silent, others (whatever annotated)]\n");
    printf("         [if 'synonymous', 'nonsynonymous', 'silent' add: Genetic_Code: Nuclear_Universal,mtDNA_Drosophila,mtDNA_Mammals,Other]\n");
    printf("         [if 'Other', introduce the single letter code for the 64 triplets in the order UUU UUC UUA UUG ... etc.]\n");
    printf("      -c [in case use coding regions, criteria to consider transcripts (max/min/first/long)]. DEFAULT: long\n");
    printf("      -E [instead -g & -c, input file with weights for positions: include three columns with a header, first the physical positions (1...end), second the weight for positions and third a boolean weight for the variant (eg. syn variant but nsyn position)]\n");
    /*printf("      -r [rewrite the fasta file for selected region (not valid for silent/syn/nsyn) (1/0)]\n");*/
    /*printf("      -t [rewrite the fasta transposed file including the weight of each position and variant, if available) (1/0)]\n");*//*new!*/
    /*printf("\     -e [input file with effect sizes for variants: include two columns with a header, first the physical positions and second the weight]\n");*/
	printf("\n");
}
