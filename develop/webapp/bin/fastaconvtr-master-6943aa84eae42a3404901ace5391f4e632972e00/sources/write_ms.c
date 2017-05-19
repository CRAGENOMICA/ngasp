/*
 *  write_ms.c
 *  fasta2ms2
 *
 *  Created by Sebastian E. Ramos Onsins on 27/11/2012.
 *
 */

#include "write_ms.h"

int write_msfile(FILE *file_output, SGZip *file_output_gz, FILE *file_logerr, SGZip *file_logerr_gz,int nsam,long int lenR, long int lenT, double lenP, long int lenS, long int *vector_pos, double *vector_sizepos,
				 char *matrix_pol, long int slide, long int window,float svratio,float summatrix_sizepos, long int nmissing, int *mis_pos, char *format, float *fnut, 
				 int Physical_length,float CpG, float GCs,float *wV,long int nV,int *svp,float **pwmatrix_miss,int tfasta,
				 long int *Pp,int *CpGp,int *Ap,int *Cp,int *Gp,int *Tp,int *GCp,long int *wgenes, long int nwindows,int *nsamuser,int npops, double **sum_sam,
				 double **nsites1_pop,double **nsites2_pop,double **nsites3_pop,double **nsites1_pop_outg,double **nsites2_pop_outg,double **nsites3_pop_outg,
				 int outgroup)
{
	 /*
	 FILE *file_output: the ouput file (stdout)
	 int nsam: number of samples
	 long int lenR: total region analyzed (same positions than in GFF file, physical positions in the alignment)
	 long int lenT: number of effective positions (Boolean length, counting each valid position as 1 and otherwise)
	 double lenP: number of effective positions (with the weight)
	 long int lenS: the number of variants
	 long int *vector_pos: the number of each variant position (dim lenS)
	 double *vector_sizepos: the weight of each position, for all the physical positions (dim lenR)
	 char *matrix_pol,: the variants for each sample (dim nsam x lenS)
	 long int slide: how many positions move right each time
	 long int window: size of the window
	 float svratio: transition/transversion ratio
	 long int nmissing: number of missing values across the valid positions 
	 int *mis_pos: number of missing values across the valid positions per position (dim lenR) 
	 char *format: a string indicating the ms format (s: standard, x: extended)
	 float *fnut: total frequency of each numcleotide, for total valid weighted region (dim 4)
	 int Physical_length: : if 1 length counted in physical positions, if 0 counted in valid positions (coding, synonymous, etc) 
	 float CpG: total number of CpGs for total valid weighted region
	 float GCs: total number of GCs for total valid weighted region
	 float *wV: weight for the variants for each position (dim nV)
	 long int nV: number of variants from the file of variant weights
	 int *svp: transition (1) or transversion (2) or nothing (0) for each position (dim lenR)
	 float **pwmatrix_miss: vector of all combinations of populations (NO OUTGROUP) with the valid position among them (per position) (dim lenR x (npop-outgroup x (npop-outgroup-1)/2))
	 int tfasta: print transposed fasta or not
	 int *Pp: position of the weighted variants (per position???)  (dim nV)
	 int *CpGp: number of CpGp per position (max nsam per position) (dim lenR)
	 int *Ap: number of As per position (max nsam per position) (dim lenR)
	 int *Cp: number of As per position (max nsam per position) (dim lenR)
	 int *Gp: number of As per position (max nsam per position) (dim lenR)
	 int *Tp: number of As per position (max nsam per position) (dim lenR)
	 int *GCp: number of GCs per position (max nsam per position) (dim lenR)
	 long int *wgenes: if defined, coordinates of each window (dim nwindows)
	 long int nwindows: number of windows defined in the coordinates file
	 int *nsamuser: number of samples defined by the user, including outgroup if defined (dim npops + 1)
	 int npops: number of populations, including outgroup, if defined
	 double **sum_sam: valid positions per sample and per position (0 to 1) (dim lenR x nsam)
	 double **nsites1_pop: value of the valid weighted position where at least one sample should be in the population (dim lenR x (npop-outgroup))
	 double **nsites2_pop: value of the valid weighted position where at least two samples should be in the population (dim lenR x (npop-outgroup))!
	 double **nsites3_pop: value of the valid weighted position where at least three samples should be in the population (dim lenR x (npop-outgroup))
	 double **nsites1_pop_outg: value of the valid weighted position where at least one sample should be in the population plus outgroup (dim lenR x (npop-outgroup))
	 double **nsites2_pop_outg: value of the valid weighted position where at least two samples should be in the population plus outgroup (dim lenR x (npop-outgroup))
	 double **nsites3_pop_outg: value of the valid weighted position where at least three samples should be in the population plus outgroup (dim lenR x (npop-outgroup))
	 int outgroup: 1 outgroup is the last pop, 0 no outgroup
	 */
	
	long int n,x,y,z,wc;
	long int beg,end;
	long int begS,endS;
	double size,psize,sizeR,sizeRT,sizent;
	float sumfnut=0.;
	float freq_missing,sum_mis_pos;
	int np,ncomb;
	double sizewin;
	long int endy;
	float /*sizesv,*/trs,trv;
	float sizems,sizeT,sizeC,sizeG,sizeA;
	float sizeGC,sizeCpG;
	float *sizen1p,*sizen2p,*sizen3p;
	float *sizen1o,*sizen2o,*sizen3o;
	int np1,np2,ns,pp;
	float *sizepw,*sizensam;
	long int zw=0;
	
    /*printf("\nWriting ms file...");*/
    fflush(stdout);
    fzprintf(file_logerr,file_logerr_gz,"\nWriting ms file...");

    x=(long int)tfasta;/*variable still not used here...*/
	x=(long int)nmissing;/*variable still not used here...*/
	
	/*initial header*/
	fzprintf(file_output,file_output_gz, FASTA2MS2);
	/*line indicating a number of statistics*/
    fzprintf(file_output,file_output_gz, "#Data for TOTAL Alignment. ");
	if(format[0] == 'x') fzprintf(file_output,file_output_gz, "format: msx ");
	else fzprintf(file_output,file_output_gz, "format: ms ");
    fzprintf(file_output,file_output_gz, "length: %ld ",lenR);
	fzprintf(file_output,file_output_gz, "Efflength: %.2f ",lenP); /*weighted length*/
	fzprintf(file_output,file_output_gz, "Booleanlength: %ld ",lenT);/*counting all valid positions as 1 or 0*/
	fzprintf(file_output,file_output_gz, "NumVariants: %ld ",lenS);
	if(nwindows == 0) {
		if(Physical_length == 1) {
			n = (long int)ceil((float)lenR/(float)slide);
		}
		else {
			n=0;
			for(x=0;x<lenR;) {
				size = 0.;
				while(size < (double)slide && x < lenR) {
					size += vector_sizepos[x];
					x++;
				}
				n++;
			}
		}
	} else {
		n = nwindows;
	}
	fzprintf(file_output,file_output_gz, "nwindows: %.0f ",(double)n);
	if(svratio == -10000.0) fzprintf(file_output,file_output_gz, "s/v: NA ");
	else fzprintf(file_output,file_output_gz, "s/v: %.3f ",svratio);
	sum_mis_pos = 0.;
	for(x=0;x<lenR;x++) sum_mis_pos += mis_pos[x];
	/*freq_missing = (float)nmissing/((float)nsam*(float)lenP);*/
	freq_missing = sum_mis_pos/summatrix_sizepos;
	if(format[0] == 'x') fzprintf(file_output,file_output_gz, "FreqMissing: %.4f ",freq_missing); /* (over effective length) */
	sumfnut = fnut[0]+fnut[1]+fnut[2]+fnut[3];
	fzprintf(file_output,file_output_gz, "GfreqT: %.2f GfreqC: %.2f GfreqG: %.2f GfreqA: %.2f ",fnut[0]/sumfnut,fnut[1]/sumfnut,fnut[2]/sumfnut,fnut[3]/sumfnut); 
	fzprintf(file_output,file_output_gz, "GCs: %.3f ",(GCs/(float)nsam)/((float)lenP));
    fzprintf(file_output,file_output_gz, "CpGs: %.3f ",(CpG/(float)nsam)/((float)lenP));
    fzprintf(file_output,file_output_gz, "Cs+Gs: %.3f ",(fnut[1]+fnut[2])/sumfnut);
	if(format[0] == 'x') {
		fzprintf(file_output,file_output_gz, "npops: %d ",npops);
		for(np=0;np<npops;np++) fzprintf(file_output,file_output_gz, "nsam[%d]: %d ",np,nsamuser[np]);
	}
	/*Comment: header in the prior field*/
	if(format[0] == 'x') {
		fzprintf(file_output,file_output_gz, "\n#initial_physical_position, final_physical_position, Efflength, ");
		fzprintf(file_output,file_output_gz, "Boolean length, s/v_ratio, FreqMissing, freqT, freqC, freqG, freqA, freqGCs, freqCpGs");
		for(np=0;np<npops-outgroup;np++) fzprintf(file_output,file_output_gz, "nsites1_pop[%d], nsites2_pop[%d], nsites3_pop[%d], nsites1_pop[%d]_outg, nsites2_pop[%d]_outg, nsites3_pop[%d]_outg, ",np,np,np,np,np,np);
		fzprintf(file_output,file_output_gz, "vector_Efflength_sample, ");
		fzprintf(file_output,file_output_gz, "matrix_length_amng_pops ");
		fzprintf(file_output,file_output_gz, "\n#NOTE: 1,2,3,4 means T,C,G,A, respectively. 8 and 9 means N and missing data. In case allowing missing data, multiple hits are reduced to the two more frequent, otherwise excluded. ");
		fzprintf(file_output,file_output_gz, "\n");
	}
	/*else fzprintf(file_output,file_output_gz, "\n#In priors include the initial physical position, the final and the effective size of the window. Multiple hits excluded.");*/

	/*print in the prior field all the necessary values*/
	/*look for windows: coordinates or sliding window*/
	ncomb = (npops-outgroup)*(npops-outgroup-1)/2;
	if((sizepw = (float *)calloc(ncomb,sizeof(float)))==0) {
		fzprintf(file_output,file_output_gz,"Error allocating memory write.out0");
		exit(1);
	}
	if((sizensam = (float *)calloc(nsam,sizeof(float)))==0) {
		fzprintf(file_output,file_output_gz,"Error allocating memory write.out1");
		exit(1);
	}
	if((sizen1p = (float *)calloc(npops,sizeof(float)))==0) {
		fzprintf(file_output,file_output_gz,"Error allocating memory write.out1");
		exit(1);
	}
	if((sizen2p = (float *)calloc(npops,sizeof(float)))==0) {
		fzprintf(file_output,file_output_gz,"Error allocating memory write.out1");
		exit(1);
	}
	if((sizen3p = (float *)calloc(npops,sizeof(float)))==0) {
		fzprintf(file_output,file_output_gz,"Error allocating memory write.out1");
		exit(1);
	}
	if((sizen1o = (float *)calloc(npops,sizeof(float)))==0) {
		fzprintf(file_output,file_output_gz,"Error allocating memory write.out1");
		exit(1);
	}
	if((sizen2o = (float *)calloc(npops,sizeof(float)))==0) {
		fzprintf(file_output,file_output_gz,"Error allocating memory write.out1");
		exit(1);
	}
	if((sizen3o = (float *)calloc(npops,sizeof(float)))==0) {
		fzprintf(file_output,file_output_gz,"Error allocating memory write.out1");
		exit(1);
	}
	begS = 0;
	wc = 0;
	for(x=0;x<lenR;) {
		/*begin, end and size of the window*/
		if(nwindows==0) {
			beg = y = x;
			endy = lenR;
			sizewin = (double)window;
		}
		else {
			beg = y = wgenes[wc++]; /*!removed -1;*/
			if(beg >= lenR) beg = lenR-1;
			endy = wgenes[wc++];
			if(endy >= lenR) endy = lenR;
			sizewin = (double)endy-(double)beg;
		}
		/*init window*/
		size  = 0.;
		sizeR = 0.;
		sizeRT= 0.;
		trs=trv=0.;
		/*sizesv= 0.;*/
		sizems= 0.;
		sizeT = 0.;
		sizeC = 0.;
		sizeG = 0.;
		sizeA = 0.;
		sizeGC= 0.;
		sizeCpG=0.;
		for(np1=0;np1<npops-outgroup-1;np1++) {
			sizen1p[np1]=0.;
			sizen2p[np1]=0.;
			sizen3p[np1]=0.;
			sizen1o[np1]=0.;
			sizen2o[np1]=0.;
			sizen3o[np1]=0.;
		}
		for(pp=0;pp<(npops-outgroup)*(npops-outgroup-1)/2;pp++) 
			sizepw[pp] = 0.;
		for(ns=0;ns<nsam;ns++) 
			sizensam[ns] = 0.;
		/*calculation*/
		while(y < endy && sizeR <  sizewin) {
			/*calculate size of the window*/
			size += vector_sizepos[y];
			if(Physical_length == 1)
				sizeR += 1.0;
			else
				sizeR += vector_sizepos[y];
			if(vector_sizepos[y]>0.) 
				sizeRT += 1.0;
			/*calculate per window the svratio*/
			if(svp[y]==1) trs+=1.0;
			if(svp[y]==2) trv+=1.0;
			/*calculate freqmissing */
			sizems += mis_pos[y]/(float)nsam;
			/*calculate freqT,C,G,A,GCs,CpGs*/
			sizeT += Tp[y];
			sizeC += Cp[y];
			sizeG += Gp[y];
			sizeA += Ap[y];
			sizeGC += GCp[y];
			sizeCpG +=CpGp[y];
			/*calculate nsites[123]_pop[_outg]*/
			pp=0;
			for(np1=0;np1<npops-outgroup;np1++) {
				sizen1p[np1] +=nsites1_pop[y][np1];
				sizen2p[np1] +=nsites2_pop[y][np1];
				sizen3p[np1] +=nsites3_pop[y][np1];
				sizen1o[np1] +=nsites1_pop_outg[y][np1];
				sizen2o[np1] +=nsites2_pop_outg[y][np1];
				sizen3o[np1] +=nsites3_pop_outg[y][np1];
				/*calculate matrix_length_amng_pops*/
				for(np2=np1+1;np2<npops-outgroup;np2++) {
					sizepw[pp] += pwmatrix_miss[y][pp];
					pp++;
				}
			}
			for(ns=0;ns<nsam;ns++) 
				sizensam[ns] += sum_sam[y][ns];
			/*next position*/
			y++;
		}
		end = y;
		fzprintf(file_output,file_output_gz,"\n// %ld\t%ld\t%.2f",beg+1,end,size);
		if(format[0] == 'x') {
			sizent = sizeT + sizeC + sizeG + sizeA;
			fzprintf(file_output,file_output_gz,"\t%.0f",sizeRT);
			if(trv>0) fzprintf(file_output,file_output_gz,"\t%.2f",trs/trv);
			else fzprintf(file_output,file_output_gz,"\tNA");
			fzprintf(file_output,file_output_gz,"\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f",sizems/size,sizeT/sizent,sizeC/sizent,sizeG/sizent,sizeA/sizent,sizeGC/sizent,sizeCpG/sizent);
			for(np1=0;np1<npops-outgroup;np1++) 
				fzprintf(file_output,file_output_gz,"\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f",sizen1p[np1],sizen2p[np1],sizen3p[np1],sizen1o[np1],sizen2o[np1],sizen3o[np1]);
			for(ns=0;ns<nsam;ns++) 
				fzprintf(file_output,file_output_gz,"\t%.2f",sizensam[ns]);
			for(pp=0;pp<((npops-outgroup)*(npops-1-outgroup)/2);pp++) 
				fzprintf(file_output,file_output_gz,"\t%.2f",sizepw[pp]);
		}
		fzprintf(file_output,file_output_gz,"\n");
		
		/*locate the number of variants in the window*/
		z = begS;
		while(z < lenS && vector_pos[z] < beg) {z++;}
		begS = z;
		while(z < lenS && vector_pos[z] < end) {z++;}
		endS = z;
		fzprintf(file_output,file_output_gz,"segsites: %ld",(endS-begS));
		fzprintf(file_output,file_output_gz,"\n");
		
		/*locate the relative positions in the filtered window*/
        if(format[0] == 'x') {
            fzprintf(file_output,file_output_gz,"positions: ");
            psize = 0.;
            y = beg;
            z = begS;
            while(vector_pos[z] < end && z < endS) {
                if(y == vector_pos[z]) {
                    fzprintf(file_output,file_output_gz,"%.8f ",psize/(size) ); /*size-1.0?: ms accept values from 0 to 1, both included...this is a problem. Please add enough decimals!*/
                    z++;
                }
                psize += vector_sizepos[y];
                y++;
            }
            fzprintf(file_output,file_output_gz,"\n");
        }
        else {
            fzprintf(file_output,file_output_gz,"positions: ");
            z = begS;
            while(z < endS) {
                fzprintf(file_output,file_output_gz,"%.8f ",(double)(vector_pos[z]/*+1*/)/lenR );
                z++;
            }
            fzprintf(file_output,file_output_gz,"\n");
        }
		/*mstatspop should accept a new ms_x format that contains a new vector including the physical position */
		/*Then we wil have physical positions with vector_sizepos[y]*/
		if(format[0] == 'x') {
			fzprintf(file_output,file_output_gz,"physical: ");
			z = begS;
			while(z < endS) {
				fzprintf(file_output,file_output_gz,"%ld ",vector_pos[z]+1 ); 
				z++;
			}
			fzprintf(file_output,file_output_gz,"\n");
			/*include the vectors with the weights of the positions for each real position used!*/
			fzprintf(file_output,file_output_gz,"pos_weight: ");
			z = beg;
			while(z < end) {
				fzprintf(file_output,file_output_gz,"%.2f ",vector_sizepos[z]); 
				z++;
			}
			fzprintf(file_output,file_output_gz,"\n");
			/*include the vectors with the weights of the variants for each real position used!*/
            if(nV > 0) {
                zw=0;
				fzprintf(file_output,file_output_gz,"var_weight: ");
				while(Pp[zw] < beg && zw < nV) zw++;
				z = beg;
				while(z < end) {
					if(Pp[zw] == z+1) {
						fzprintf(file_output,file_output_gz,"%.3e ",wV[zw]); 
						zw++;
					}
					else {
                        fzprintf(file_output,file_output_gz,"NA ");/*"%.2f ",(float)0);*/
					}
					z++;
				}
				fzprintf(file_output,file_output_gz,"\n");
			}
		}
		
		/*print the matrix of variants*/
		if((endS-begS) > 0) {
			for(n=0;n<nsam;n++) {
				for(z=begS;z<endS;z++) {
					fzprintf(file_output,file_output_gz,"%c",matrix_pol[z*nsam+n]);
				}
				fzprintf(file_output,file_output_gz,"\n");
			}
		}
		/*move slide positions*/
		if(nwindows==0) {
			size  = 0.;
			sizeR = 0.;
			while(sizeR < (double)slide && x < lenR) {
				/*size += vector_sizepos[x];*/
				if(Physical_length == 1) sizeR += 1.0;
				else sizeR += vector_sizepos[x];
				x++;
			}
		}
		else {
			x = end+1;
			if(wc == 2*nwindows) 
				break;
		}
		
		/**/fflush(stdout);/**/
	}
	
	fflush(stdout);
	free(sizensam);
	free(sizepw);
	free(sizen1p);
	free(sizen2p);
	free(sizen3p);
	free(sizen1o);
	free(sizen2o);
	free(sizen3o);
	return 1;
}
