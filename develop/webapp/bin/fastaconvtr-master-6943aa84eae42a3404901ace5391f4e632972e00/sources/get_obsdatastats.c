/*
 *  get_obsdatastats.c
 *  MuLoNeTests
 *
 *  Created by sebas on Mon Feb 24 2003.
 *
 */

#include "get_obsdatastats.h"

int get_obsstats_mod(FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz, int n_samp, long int n_site,
				 long int *n_realsite,char *DNA_matr,double *matrix_sizepos,
				 double *matrix_segrpos,char **matrix_pol,
				 long int **matrix_pos,double *length_al,long int *length_seg,
				 int include_unknown,int outgroup_presence, 
			     float *svratio, long int *nmissing, char *format,
			     int *nsamuser,int npops, double **sum_sam,
				 int **svp, float **pwmatrix_miss, float *CpG, int *CpGp, float *GCs, int *Tp, int *Cp, int *Gp, int *Ap, int *GCp,
				 double **nsites1_pop,double **nsites2_pop,double **nsites3_pop,double **nsites1_pop_outg,double **nsites2_pop_outg,double **nsites3_pop_outg)
{	
	/*
	 file_output: not necessary but ok -> include info into function
	 n_samp: number of samples ->
	 n_site: total positions -> length
	 n_realsite: total effective length  <- value obtained from function <- length_al_real
	 DNA_matr2: the matrix of data ->
	 matrix_sizepos: vector with the weight of the positions ->
	 matrix_segrpos: vector with the total positions, erasing variants not interesting (that is, in case counting syn positions but the variant is nsyn, value is 0) ->
	 matrix_pol: matrix with the value of each position and sample <-
	 matrix_pos: indicates the position of the variant <-
	 length_al: total length of the studied region (if syn/nsyn is fractional) <-
	 length_seg: total number of variants <-
	 npops = 1
	 include_unknown: consider or not missing positions ->
	 outgroup_presence: if 1, the reference (ancestral) is the last poopulation (MODIFY!) in the fasta file. 
	 
	 *CpG: the total number of CpG for all lines together. Here all positions are always included
	 *CpGp,**Ap,**Cp,**Gp,**Tp,**GC`; CpG,A,C,G,T, GC per position (int)
	 **svp; transitions (1) or transversions (2) per polymorphic position
	 **sum_sam: real positions per sample (exclude gaps and invalid positions)
	 
	 *nsamuser: the number of samples per population
	 npops: the number of populations used
	 **pwmatrix_missing: the up-diagonal pairwise matrix of differences between 2 POPS per position
	 **nsites[123]_pop[_outg]: number of valid positions for each POP per position
	 */
	
	long int maxbialsites = 256;
    long int maxnsamp = n_samp;
	
    double algsites;
    long int bial_sites = 0;
    long int mhits = 0;

	int nv;
	int *nm;
	char *varnt,varout[1];
	char *varmis;
	int *nvar;
	int *nmis;
	char *colsam;
	
    int v,w,y,z;
	int x,z2,p,q,cp,y2,v_2;
	int v1,v2; /*!--- Not used nv1; */ /*!--- Not used nv2 */
	
	long int xx,xxx;
    double _sites;
 	int nsamtot;
	
	long int transitions;
	long int transversions;
    
	int *initsq1,sumnsam,inits,endis;
	
    initsq1 = (int *)calloc(npops,sizeof(int));
    sumnsam = 0;
    for(z=0;z<npops;z++) {
		initsq1[z] = sumnsam;
		sumnsam += nsamuser[z];
    }
	nsamtot = 0;
	for(x=0;x<npops;x++)
		nsamtot += nsamuser[x];
		
	*nmissing = 0;
    /* calculate number of samples in outgroup and in the current sample */
	/* if no outgroup, then all sequences are samples */
	if(n_samp < 2) {
		fzprintf(file_logerr,file_logerr_gz," n_samples: %d .",n_samp);
		fzprintf(file_logerr,file_logerr_gz," NOT ENOUGH SAMPLES.");
		if(file_output) {
			fzprintf(file_output,file_output_gz," n_samples: %d .",n_samp);
			fzprintf(file_output,file_output_gz," NOT ENOUGH SAMPLES.");
		}
		return(0);
	}
	
	/* 2D (really 1D) matrix of polymorphisms */
	if((*matrix_pol = (char *) calloc (maxnsamp*maxbialsites, sizeof(char))) == 0) {
		fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.3");
		return(0);
	}
	/* indicates the position and the frequency */
	if((*matrix_pos = (long int *) calloc (maxbialsites, sizeof(long int))) == 0) {
		fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.4");
		return(0);
	}
	/*pointer to the samples of a given position*/
 	if((colsam = (char *) calloc (maxnsamp, sizeof(char))) == 0) {
		fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.col");
		return(0);
	}
 	if((varnt = (char *) calloc (4, sizeof(char))) == 0) {
		fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.col");
		return(0);
	}
 	if((varmis = (char *) calloc (2, sizeof(char))) == 0) {
		fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.col");
		return(0);
	}
 	if((nvar = (int *) calloc (4, sizeof(int))) == 0) {
		fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.col");
		return(0);
	}
 	if((nmis = (int *) calloc (2, sizeof(int))) == 0) {
		fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.col");
		return(0);
	}
 	if((nm = (int *) calloc (1,sizeof(int))) == 0) {
		fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.col");
		return(0);
	}
	
	algsites = (double)n_site; /* algsites: number of aligned positions, excluding gaps and mhits */
    
	
    /* find positions that are biallelic, excluding the rest. */
    /* IMPORTANT: multiple hits are eliminated from analysis, SYN/NSYN MHITS ARE NOT ACCOUNTED*/
 	nsamtot = n_samp;
    _sites = (double)0;
	*n_realsite = (long int)0;
    transitions = 0;
	transversions = 0;
	*CpG = 0;
	*GCs = 0;
	
	for(xx=0;xx<n_site;xx++) {
		/*calculate variants, missing values etc at this position*/
		for(y=0;y<nsamtot;y++) colsam[y] = *(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx));
		nv = number_of_variants(colsam,nsamtot,varnt,nvar,varmis,nmis,nm);
		
        /*eliminate those positions that are not included in analysis*/
        if(matrix_sizepos[xx]*matrix_segrpos[xx] == (double)0) {
            algsites -= (double)1 - matrix_sizepos[xx]*matrix_segrpos[xx] ;
            continue;
        }
		if(include_unknown == 0 && *nm > 0) {
			/*if gap/missing is not allowed, exclude from analysis*/
			algsites -=matrix_sizepos[xx]*matrix_segrpos[xx] ;
			matrix_sizepos[xx] = 0.;
			continue;
		}

		/*loop for populations to count the total number of positions per pop and the matrix of valid positions between pops*/
		if(outgroup_presence == 1) {
			inits   = initsq1[npops-1];
			endis   = initsq1[npops-1]+nsamuser[npops-1];
			/*define as value '0' the value observed in the outgroup population*/
			varout[0] = 0;/* 0 is undefined value. Note is not '0'*/
			for(y=inits;y<endis;y++) {
				w = *(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx));
				if(varout[0] == 0 && w < 48 + 5) {
					varout[0] = w;
					/**/
					z = 0;
					while (z<4 && w!=varnt[z]) {z++;}
					varnt[z] = varnt[0];
					varnt[0] = w;
					v = nvar[0];
					nvar[0] = nvar[z];
					nvar[z] = v;
					/**/
				}
				if(varout[0] != 0 && w < 48 + 5 && w != varout[0]) {
					/*if the outgroup is polymorphic erase from the analysis...*/
					nv = 0;
					algsites -=matrix_sizepos[xx]*matrix_segrpos[xx] ;
					matrix_sizepos[xx] = 0.;
					break;
				}
			}
			if(varout[0] == 0) {
				/*if the outgroup is missing erase from the analysis...*/
				nv = 0;
				algsites -=matrix_sizepos[xx]*matrix_segrpos[xx] ;
				matrix_sizepos[xx] = 0.;
			}
			if(nv==0) 
				continue;
		}

		/*look for biallelic (and missing)*/
        *n_realsite += (long int)1;

		/*count for TCGA and GC per position and for total valid positions*/
		/*count for CpG per position and for total valid*/
		/*count for real positions per sample*/
		for(y=0;y<nsamtot;y++) {
			switch(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx))) {
				case '1':/*T*/
					Tp[xx] += matrix_sizepos[xx]*matrix_segrpos[xx];
					sum_sam[xx][y] += matrix_sizepos[xx]*matrix_segrpos[xx];
					break;
				case '2':/*C*/
					Cp[xx] += matrix_sizepos[xx]*matrix_segrpos[xx];
					sum_sam[xx][y] += matrix_sizepos[xx]*matrix_segrpos[xx];
					xxx = xx +matrix_sizepos[xx]*matrix_segrpos[xx];
					while(xxx < n_site && *(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xxx)) > '4') xxx += 1;
					if(xxx < n_site) {
						if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xxx)) == '3') {
							CpGp[xx] += matrix_sizepos[xx]*matrix_segrpos[xx]; *CpG += matrix_sizepos[xx]*matrix_segrpos[xx];
							GCp[xx] += matrix_sizepos[xx]*matrix_segrpos[xx]; *GCs += matrix_sizepos[xx]*matrix_segrpos[xx];
						}
					}
					break;
				case '3':/*G*/
					Gp[xx] += matrix_sizepos[xx]*matrix_segrpos[xx];
					sum_sam[xx][y] += matrix_sizepos[xx]*matrix_segrpos[xx];
					xxx = xx +1;
					while(xxx < n_site && *(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xxx)) > '4') xxx += 1;
					if(xxx < n_site) {
						if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xxx)) == '2') {
							GCp[xx] += matrix_sizepos[xx]*matrix_segrpos[xx]; *GCs += matrix_sizepos[xx]*matrix_segrpos[xx];
						}
					}
					break;
				case '4':/*A*/
					Ap[xx] += matrix_sizepos[xx]*matrix_segrpos[xx];
					sum_sam[xx][y] += matrix_sizepos[xx]*matrix_segrpos[xx];
					break;
				case '5':/*N*/
					break;
				case '6':/*-*/
					break;
				default:/*Ns*/
					break;
			}
			colsam[y] = *(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx));
		}

		/*count missing positions*/
		if(nv > 0) 
			nmissing[0] += nmis[0] + nmis[1];
        
		switch (nv) {
			case 0: /*all gaps or missing (but *nm>0) or outgroup is missing*/
				algsites -=matrix_sizepos[xx]*matrix_segrpos[xx] ;
				matrix_sizepos[xx] = 0.; /*also eliminate from the analysis*/
                *n_realsite -= (long int)1;
				break;
			case 1: /*no variant, nothing happens*/
				/*
				if(format[0]=='x') {
					if(*nm>0) {
						for(y=0;y<nsamtot;y++) {
							if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx)) == '5')
								matrix_pol[0][((bial_sites*(nsamtot))+y)] = '8'; 
							else if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx)) == '6')
								matrix_pol[0][((bial_sites*(nsamtot))+y)] = '9';
							else {
								matrix_pol[0][((bial_sites*(nsamtot))+y)] = varnt[1];
							}
						}
					}
				}
				*/
				/*count position*/
				_sites += matrix_sizepos[xx]*matrix_segrpos[xx] ;
				algsites -= (double)1 - matrix_sizepos[xx]*matrix_segrpos[xx] ;
				/*count pairwise differences among populations: */
				/*count if at least there is one sample for each population*/
                z = 0;cp=0;p=0;
				for(y=0;y<npops-outgroup_presence;y++) {
					v = 0;
					for(x=z;x<z+nsamuser[y];x++) {
						w = *(DNA_matr+(((long int)n_site*(unsigned long)x)+(unsigned long)xx));	
						if(w >'4') v += 1;
					}
					if(v < nsamuser[y]) nsites1_pop[xx][y] += (matrix_sizepos[xx]);
					if(v < nsamuser[y]-1) nsites2_pop[xx][y] += (matrix_sizepos[xx]);
					if(v < nsamuser[y]-2) nsites3_pop[xx][y] += (matrix_sizepos[xx]);
					if(outgroup_presence == 1) {
						p = 0;
						for(x=nsamtot-1;x>=nsamtot-nsamuser[npops-1];x--) {
							q = *(DNA_matr+(((long int)n_site*(unsigned long)x)+(unsigned long)xx));	
							if(q > '4') p += 1;
						}
						if(p < nsamuser[npops-1] && v < nsamuser[y]) 
							nsites1_pop_outg[xx][y] += (matrix_sizepos[xx]);
						if(p < nsamuser[npops-1] && v < nsamuser[y]-1) 
							nsites2_pop_outg[xx][y] += (matrix_sizepos[xx]);
						if(p < nsamuser[npops-1] && v < nsamuser[y]-2) 
							nsites3_pop_outg[xx][y] += (matrix_sizepos[xx]);
					}
					z2 = z; x= y;
					while(x<y+1) {z2 += nsamuser[x]; x++;}
					for(y2=y+1;y2<npops-outgroup_presence;y2++) {
						v_2 = 0;
						for(x=z2;x<z2+nsamuser[y2];x++) {
							w = *(DNA_matr+(((long int)n_site*(unsigned long)x)+(unsigned long)xx));	
							if(w >'4') v_2 += 1;
						}
						if(outgroup_presence == 1) {
							if(p < nsamuser[npops-1] && v < nsamuser[y] && v_2 < nsamuser[y2])
								pwmatrix_miss[xx][cp] += (matrix_sizepos[xx]);
						}
						else {
							if(v < nsamuser[y] && v_2 < nsamuser[y2]) 
								pwmatrix_miss[xx][cp] += (matrix_sizepos[xx]);
						}
						cp += 1;/*we do all the number of pairwise comparisons*/
						z2 += nsamuser[y2];
					}
					z += nsamuser[y];
				}
				break;
			case 2:
				/*count trans and transv in relation to the highest frequency (or the outgroup)*/
				if((varnt[0] == '1' && varnt[1] == '2') || (varnt[0] == '2' && varnt[1] == '1') || 
				   (varnt[0] == '4' && varnt[1] == '3') || (varnt[0] == '3' && varnt[1] == '4')) {
					transitions += 1; /*T<->C and G<->A; 1234 es TCGA*/
					svp[0][xx] = 1;
				}
				else {
					transversions += 1;
					svp[0][xx] = 2;
				}
				for(y=0;y<nsamtot;y++) {
					if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx)) == varnt[0]) {
						if(format[0]!='x') matrix_pol[0][((bial_sites*(nsamtot))+y)] = '0';
						if(format[0]=='x') matrix_pol[0][((bial_sites*(nsamtot))+y)] = varnt[0];
					}
					else {
						if(include_unknown == 0) { /* and not missing*/
							if(format[0]!='x') matrix_pol[0][((bial_sites*(nsamtot))+y)] = '1';
							if(format[0]=='x') matrix_pol[0][((bial_sites*(nsamtot))+y)] = varnt[1];
						}
						else {/*perhaps missing or gaps*/
							if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx)) == '5')
								matrix_pol[0][((bial_sites*(nsamtot))+y)] = '8'; /*missing*/
							else {
								if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx)) == '6')
									matrix_pol[0][((bial_sites*(nsamtot))+y)] = '9'; /*gap*/
								else {
									if(format[0]!='x') matrix_pol[0][((bial_sites*(nsamtot))+y)] = '1';
									if(format[0]=='x') matrix_pol[0][((bial_sites*(nsamtot))+y)] = varnt[1];
								}
							}
						}
					}
				}
				/*count pairwise differences among populations: */
				/*count if at least there is one sample for each population*/
                z = 0;cp=0;p=0;
				for(y=0;y<npops-outgroup_presence;y++) {
					v = 0;
					for(x=z;x<z+nsamuser[y];x++) {
						w = matrix_pol[0][((bial_sites*(nsamtot))+y)];	
						if(w >'4') v += 1;
					}
					if(v < nsamuser[y]) nsites1_pop[xx][y] += (matrix_sizepos[xx]);
					if(v < nsamuser[y]-1) nsites2_pop[xx][y] += (matrix_sizepos[xx]);
					if(v < nsamuser[y]-2) nsites3_pop[xx][y] += (matrix_sizepos[xx]);
					if(outgroup_presence == 1) {
						p = 0;
						for(x=nsamtot-1;x>=nsamtot-nsamuser[npops-1];x--) {
							q = matrix_pol[0][((bial_sites*(nsamtot))+x)];	
							if(q > '4') p += 1;
						}
						if(p < nsamuser[npops-1] && v < nsamuser[y]) 
							nsites1_pop_outg[xx][y] += (matrix_sizepos[xx]);
						if(p < nsamuser[npops-1] && v < nsamuser[y]-1) 
							nsites2_pop_outg[xx][y] += (matrix_sizepos[xx]);
						if(p < nsamuser[npops-1] && v < nsamuser[y]-2) 
							nsites3_pop_outg[xx][y] += (matrix_sizepos[xx]);
					}
					z2 = z; x= y;
					while(x<y+1) {z2 += nsamuser[x]; x++;}
					for(y2=y+1;y2<npops-outgroup_presence;y2++) {
						v_2 = 0;
						for(x=z2;x<z2+nsamuser[y2];x++) {
							w = matrix_pol[0][((bial_sites*(nsamtot))+x)];	
							if(w >'4') v_2 += 1;
						}
						if(outgroup_presence == 1) {
							if(p < nsamuser[npops-1] && v < nsamuser[y] && v_2 < nsamuser[y2]) 
								pwmatrix_miss[xx][cp] += (matrix_sizepos[xx]);
						}
						else {
							if(v < nsamuser[y] && v_2 < nsamuser[y2]) 
								pwmatrix_miss[xx][cp] += (matrix_sizepos[xx]);
						}
						cp += 1;/*we do all the number of pairwise comparisons*/
						z2 += nsamuser[y2];
					}
					z += nsamuser[y];
				}
				/**/
				matrix_pos[0][bial_sites] = (xx);
				bial_sites++;
				if(bial_sites == maxbialsites) {
					maxbialsites += 128;
					if((*matrix_pol = realloc (*matrix_pol, maxnsamp*maxbialsites*sizeof(char))) == 0) {
						fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.11");
						return(0);
					}
					if((*matrix_pos = realloc(*matrix_pos,(maxbialsites)*sizeof(long int))) == 0) {
						fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.12");
						return(0);
					}
				}
				_sites += matrix_sizepos[xx]*matrix_segrpos[xx];
				algsites -= (double)1 - matrix_sizepos[xx]*matrix_segrpos[xx];
				break;
			default: /*multiple hits. Eliminate the lowest frequency if missing allowed, Otherwise exclude from analysis*/
				if(format[0]!='x') {
					if(include_unknown == 0) {
                        algsites -=matrix_sizepos[xx];
						matrix_sizepos[xx] = 0.;
                        *n_realsite -= (long int)1;/*here we also erase the mhits from the total*/
					}
					else { /*in case missing allowed, include missing positions*/
						if(outgroup_presence == 1) {
							if((w = *(DNA_matr+(((long int)n_site*(unsigned long)(nsamtot-1))+(unsigned long)xx))) >= 48 +5) w = 0;
						} 
						else w = 0;
						/*choose the two more frequent variants, the rest convert to '8'*/
						if(w == 0 && nvar[0] < nvar[1]) {
							v1  = varnt[1]; /*!--- Not used nv1 = nvar[1]; */ v2  = varnt[0]; /*!--- Not used nv2 = nvar[0]; */
						}
						else {/*if outgroup presence: fix the ancestral always in the sample*/
							v1  = varnt[0]; /*!--- Not used nv1 = nvar[0]; */ v2  = varnt[1]; /*!--- Not used nv2 = nvar[1]; */
						}
						for(y=2;y<nv;y++) {
							if(nvar[y] > nvar[1]) {
								v2  = varnt[y]; /*!--- Not used nv2 = nvar[y]; */
								if(w==0 && nvar[y] > nvar[0]) {
									v2  = v1; /*!--- Not used nv2 = nv1; */ v1  = varnt[y]; /*!--- Not used nv1 = nvar[y]; */
								}
							}
						} 
						/*count trans and transv in relation to the highest frequency (or the outgroup)*/
						if((v1 == '1' && v2 == '2') || (v1 == '2' && v2 == '1') || 
						   (v1 == '4' && v2 == '3') || (v1 == '3' && v2 == '4')) {
							transitions += 1; /*T<->C and G<->A; 1234 es TCGA*/
							svp[0][xx] = 1;
						}
						else {
							transversions += 1;
							svp[0][xx] = 2;
						}
						/*now convert to Ns('8') the rest of variants*/
						for(y=0;y<nsamtot;y++) {
							if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx)) == v1)
								matrix_pol[0][((bial_sites*(nsamtot))+y)] = '0';
							else {
								if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx)) == v2)
									matrix_pol[0][((bial_sites*(nsamtot))+y)] = '1';
								else 
									matrix_pol[0][((bial_sites*(nsamtot))+y)] = '8'; /*missing*/ 
							}
						}
						/*count pairwise differences among populations: */
						/*count if at least there is one sample for each population*/
                        z = 0;cp=0;p=0;
						for(y=0;y<npops-outgroup_presence;y++) {
							v = 0;
							for(x=z;x<z+nsamuser[y];x++) {
								w = matrix_pol[0][((bial_sites*(nsamtot))+y)];	
								if(w >'4') v += 1;
							}
							if(v < nsamuser[y]) nsites1_pop[xx][y] += (matrix_sizepos[xx]);
							if(v < nsamuser[y]-1) nsites2_pop[xx][y] += (matrix_sizepos[xx]);
							if(v < nsamuser[y]-2) nsites3_pop[xx][y] += (matrix_sizepos[xx]);
							if(outgroup_presence == 1) {
								p = 0;
								for(x=nsamtot-1;x>=nsamtot-nsamuser[npops-1];x--) {
									q = matrix_pol[0][((bial_sites*(nsamtot))+x)];	
									if(q > '4') p += 1;
								}
								if(p < nsamuser[npops-1] && v < nsamuser[y]) 
									nsites1_pop_outg[xx][y] += (matrix_sizepos[xx]);
								if(p < nsamuser[npops-1] && v < nsamuser[y]-1) 
									nsites2_pop_outg[xx][y] += (matrix_sizepos[xx]);
								if(p < nsamuser[npops-1] && v < nsamuser[y]-2) 
									nsites3_pop_outg[xx][y] += (matrix_sizepos[xx]);
							}
							z2 = z; x= y;
							while(x<y+1) {z2 += nsamuser[x]; x++;}
							for(y2=y+1;y2<npops-outgroup_presence;y2++) {
								v_2 = 0;
								for(x=z2;x<z2+nsamuser[y2];x++) {
									w = matrix_pol[0][((bial_sites*(nsamtot))+x)];	
									if(w >'4') v_2 += 1;
								}
								if(outgroup_presence == 1) {
									if(p < nsamuser[npops-1] && v < nsamuser[y] && v_2 < nsamuser[y2])
										pwmatrix_miss[xx][cp] += (matrix_sizepos[xx]);
								}
								else {
									if(v < nsamuser[y] && v_2 < nsamuser[y2]) 
										pwmatrix_miss[xx][cp] += (matrix_sizepos[xx]);
								}
								cp += 1;/*we do all the number of pairwise comparisons*/
								z2 += nsamuser[y2];
							}
							z += nsamuser[y];
						}
						/**/
						matrix_pos[0][bial_sites] = (xx);
						bial_sites++;
						if(bial_sites == maxbialsites) {
							maxbialsites += 128;
							if((*matrix_pol = realloc (*matrix_pol, maxnsamp*maxbialsites*sizeof(char))) == 0) {
								fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.11");
								return(0);
							}
							if((*matrix_pos = realloc(*matrix_pos,(maxbialsites)*sizeof(long int))) == 0) {
								fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.12");
								return(0);
							}
						}
						_sites += matrix_sizepos[xx]*matrix_segrpos[xx] ;
						algsites -= (double)1 - matrix_sizepos[xx]*matrix_segrpos[xx] ;
					}
				}
				if(format[0]=='x') {
					if(outgroup_presence == 1) {
						if((w = *(DNA_matr+(((long int)n_site*(unsigned long)(nsamtot-1))+(unsigned long)xx))) >= 48 +5) w = 0;
					} 
					else w = 0;
					/*choose the two more frequent variants, the rest convert to '8'*/
					if(w == 0 && nvar[0] < nvar[1]) {
						v1  = varnt[1]; /*!--- Not used nv1 = nvar[1]; */ v2  = varnt[0]; /*!--- Not used nv2 = nvar[0]; */
					}
					else {/*if outgroup presence: fix the ancestral always in the sample*/
						v1  = varnt[0]; /*!--- Not used nv1 = nvar[0]; */ v2  = varnt[1]; /*!--- Not used nv2 = nvar[1]; */
					}
					for(y=2;y<nv;y++) {
						if(nvar[y] > nvar[1]) {
							v2  = varnt[y]; /*!--- Not used nv2 = nvar[y]; */
							if(w==0 && nvar[y] > nvar[0]) {
								v2  = v1; /*!--- Not used nv2 = nv1; */ v1  = varnt[y]; /*!--- Not used nv1 = nvar[y]; */
							}
						}
					} 
					/*count trans and transv in relation to the highest frequency (or the outgroup)*/
					if((v1 == '1' && v2 == '2') || (v1 == '2' && v2 == '1') || 
					   (v1 == '4' && v2 == '3') || (v1 == '3' && v2 == '4')) {
						transitions += 1; /*T<->C and G<->A; 1234 es TCGA*/
						svp[0][xx] = 1;
					}
					else {
						transversions += 1;
						svp[0][xx] = 2;
					}
					/*now convert to Ns('8') the rest of variants*/
					for(y=0;y<nsamtot;y++) {
						if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx)) == v1)
							matrix_pol[0][((bial_sites*(nsamtot))+y)] = v1;
						else {
							if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx)) == v2)
								matrix_pol[0][((bial_sites*(nsamtot))+y)] = v2;
							else 
								matrix_pol[0][((bial_sites*(nsamtot))+y)] = '8'; /*missing*/ 
						}
					}
					/*
					for(y=0;y<nsamtot;y++) {
						if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx)) == '5')
							matrix_pol[0][((bial_sites*(nsamtot))+y)] = '8'; 
						else if(*(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx)) == '6')
							matrix_pol[0][((bial_sites*(nsamtot))+y)] = '9'; 
						else
							matrix_pol[0][((bial_sites*(nsamtot))+y)] = *(DNA_matr+(((long int)n_site*(unsigned long)y)+(unsigned long)xx))-1;
					}
					*/
					/*count pairwise differences among populations: */
					/*count if at least there is one sample for each population*/
                    z = 0;cp=0;p=0;
					for(y=0;y<npops-outgroup_presence;y++) {
						v = 0;
						for(x=z;x<z+nsamuser[y];x++) {
							w = matrix_pol[0][((bial_sites*(nsamtot))+y)];	
							if(w >'4') v += 1;
						}
						if(v < nsamuser[y]) nsites1_pop[xx][y] += (matrix_sizepos[xx]);
						if(v < nsamuser[y]-1) nsites2_pop[xx][y] += (matrix_sizepos[xx]);
						if(v < nsamuser[y]-2) nsites3_pop[xx][y] += (matrix_sizepos[xx]);
						if((matrix_sizepos[xx] > 0)) {
							if(outgroup_presence == 1) {
								p = 0;
								for(x=nsamtot-1;x>=nsamtot-nsamuser[npops-1];x--) {
									q = matrix_pol[0][((bial_sites*(nsamtot))+x)];	
									if(q > '4') p += 1;
								}
								if(p < nsamuser[npops-1] && v < nsamuser[y]) 
									nsites1_pop_outg[xx][y] += (matrix_sizepos[xx]);
								if(p < nsamuser[npops-1] && v < nsamuser[y]-1) 
									nsites2_pop_outg[xx][y] += (matrix_sizepos[xx]);
								if(p < nsamuser[npops-1] && v < nsamuser[y]-2) 
									nsites3_pop_outg[xx][y] += (matrix_sizepos[xx]);
							}
						}
						z2 = z; x= y;
						while(x<y+1) {z2 += nsamuser[x]; x++;}
						for(y2=y+1;y2<npops-outgroup_presence;y2++) {
							v_2 = 0;
							for(x=z2;x<z2+nsamuser[y2];x++) {
								w = matrix_pol[0][((bial_sites*(nsamtot))+x)];	
								if(w >'4') v_2 += 1;
							}
							if((matrix_sizepos[xx] > 0)) {
								if(outgroup_presence == 1) {
									if(p < nsamuser[npops-1] && v < nsamuser[y] && v_2 < nsamuser[y2])
										pwmatrix_miss[xx][cp] += (matrix_sizepos[xx]);
								}
								else {
									if(v < nsamuser[y] && v_2 < nsamuser[y2]) 
										pwmatrix_miss[xx][cp] += (matrix_sizepos[xx]);
								}
							}
							cp += 1;/*we do all the number of pairwise comparisons*/
							z2 += nsamuser[y2];
						}
						z += nsamuser[y];
					}
					/**/
					matrix_pos[0][bial_sites] = (xx);
					bial_sites++;
					if(bial_sites == maxbialsites) {
						maxbialsites += 128;
						if((*matrix_pol = realloc (*matrix_pol, maxnsamp*maxbialsites*sizeof(char))) == 0) {
							fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.11");
							return(0);
						}
						if((*matrix_pos = realloc(*matrix_pos,(maxbialsites)*sizeof(long int))) == 0) {
							fzprintf(file_logerr,file_logerr_gz,"\nError: memory not reallocated. get_obsstat.12");
							return(0);
						}
					}
					_sites += matrix_sizepos[xx]*matrix_segrpos[xx] ;
					algsites -= (double)1 - matrix_sizepos[xx]*matrix_segrpos[xx] ;
				}
				mhits+=nv-2;
				break;
		}
	}
 	if(_sites == (double)0) {
		fzprintf(file_output,file_output_gz,"Not valid sites available in this file: ");
        return 0;
    }
	
	*length_al = /*algsites*/_sites;/*only coincidents in case total positions*/
	*length_seg = bial_sites;
	*svratio = (double)transitions/(double)transversions;
	if(transversions == 0) *svratio = -10000.0;
	
	free(colsam);
	free(nvar);
	free(nmis);
	free(varnt);
	free(varmis);
	free(nm);
	
	return 1;
}

int number_of_variants(char *colsam,int nsam, char *varnt, int *nvar, char *varmis, int *nmis, int *nm)
{
	/*
	 colsam: the values in the column position
	 nsam: number of samples
	 varnt: vector with the symbols found in the column (1,2,3,4)
	 nvar: vector with the frequency of each symbol 
	 varmis: vector with the missing,gaps symbols found (5,6)
	 nmis: vector with the frequency of symbols
	 nm: number of total missing symbols (0,1,2)
	 nv: number of total variant symbols (0,1,2,3,4)
	*/
	
	int t,x,y,nv;
	int c;
	
	nv = 0;
	*nm = 0;
	for(x=0;x<4;x++) {varnt[x]=0;nvar[x]=0;}
	for(x=0;x<2;x++) {varmis[x]=0;nmis[x]=0;}
	
	for(x=0;x<nsam;x++) {
		c = colsam[x];
		if(c < 48+5) { /*nt*/
			if(nv == 0) {
				varnt[nv] = c;
				nvar[nv] += 1;
				nv++;
			}
			else {
				t = 0;
				for(y=0;y<nv;y++) {
					if(varnt[y] == c) {
						nvar[y] += 1;
						t = 1;
						break;
					}
				}
				if(t==0) {
					varnt[nv] = c;
					nvar[nv] += 1;
					nv++;
				}
			}
		}
		/*missing or gap*/
		else { 
			if(*nm == 0) {
				varmis[*nm] = c;
				nmis[*nm] += 1;
				nm[0] = nm[0] + 1;
			}
			else {
				t = 0;
				for(y=0;y<*nm;y++) {
					if(varmis[y] == c) {
						nmis[y] += 1;
						t = 1;
						break;
					}
				}
				if(t==0) {
					varmis[*nm] = c;
					nmis[*nm] += 1;
					nm[0] = nm[0] + 1;
				}
			}
		}
	}
	
	return nv;
}
