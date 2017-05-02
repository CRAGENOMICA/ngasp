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
 *  \brief     CCalcMstatspopOutput.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 14, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcMstatspopOutput.h"

#include <cmath>

#include <cstring>
#include <cinttypes>  // PRId64
#include <string>

#include <cstdlib>
#include <cmath>
#include <cstdio>

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"

#define SET_INPUT_INFO_ALL_UNDEFINED(x) SET_INPUT_INFO(x,UNDEFINED_STRING,UNDEFINED_STRING,UNDEFINED_STRING,UNDEFINED_STRING,UNDEFINED_STRING,UNDEFINED_STRING,UNDEFINED_STRING,UNDEFINED_VALUE,UNDEFINED_VALUE,OPTTYPE_mandatory)

CCalcMstatspopOutput::CCalcMstatspopOutput()
: ICalculation(KeyString::CALC_MSTATSPOP_OUTPUT,
               KeyString::CALC_MSTATSPOP_OUTPUT_BRIEF_DESC,
               KeyString::CALC_MSTATSPOP_OUTPUT_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {  
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    SET_INPUT_INFO_ALL_UNDEFINED(matrix_pol)
    SET_INPUT_INFO_ALL_UNDEFINED(matrix_pol_tcga)
    SET_INPUT_INFO_ALL_UNDEFINED(positions)
    SET_INPUT_INFO_ALL_UNDEFINED(sites)
    SET_INPUT_INFO_ALL_UNDEFINED(sanc)
    SET_INPUT_INFO_ALL_UNDEFINED(mainargc)
    SET_INPUT_INFO_ALL_UNDEFINED(file_input)
    SET_INPUT_INFO_ALL_UNDEFINED(file_output)
    SET_INPUT_INFO_ALL_UNDEFINED(gfffiles)
    SET_INPUT_INFO_ALL_UNDEFINED(file_GFF)
    SET_INPUT_INFO_ALL_UNDEFINED(subset_positions)
    SET_INPUT_INFO_ALL_UNDEFINED(code_name)
    SET_INPUT_INFO_ALL_UNDEFINED(genetic_code)
    SET_INPUT_INFO_ALL_UNDEFINED(length)
    SET_INPUT_INFO_ALL_UNDEFINED(length_al)
    SET_INPUT_INFO_ALL_UNDEFINED(length_al_real)
    SET_INPUT_INFO_ALL_UNDEFINED(niter)
    SET_INPUT_INFO_ALL_UNDEFINED(ploidy)
    SET_INPUT_INFO_ALL_UNDEFINED(include_unknown)
    SET_INPUT_INFO_ALL_UNDEFINED(force_outgroup)
    SET_INPUT_INFO_ALL_UNDEFINED(the_outgroup_presence)
    SET_INPUT_INFO_ALL_UNDEFINED(vint_perpop_nsam)
    SET_INPUT_INFO_ALL_UNDEFINED(npops)
    SET_INPUT_INFO_ALL_UNDEFINED(int_total_nsam)
    SET_INPUT_INFO_ALL_UNDEFINED(svratio)
    SET_INPUT_INFO_ALL_UNDEFINED(missratio)
    SET_INPUT_INFO_ALL_UNDEFINED(jfd)
    SET_INPUT_INFO_ALL_UNDEFINED(nfd)
    SET_INPUT_INFO_ALL_UNDEFINED(H1frq)
    SET_INPUT_INFO_ALL_UNDEFINED(H0frq)
    SET_INPUT_INFO_ALL_UNDEFINED(file_H1f)
    SET_INPUT_INFO_ALL_UNDEFINED(file_H0f)
    SET_INPUT_INFO_ALL_UNDEFINED(vector_priors)
    SET_INPUT_INFO_ALL_UNDEFINED(npriors)
    SET_INPUT_INFO_ALL_UNDEFINED(formatfile)
    SET_INPUT_INFO_ALL_UNDEFINED(freq_missing_ms)
    SET_INPUT_INFO_ALL_UNDEFINED(nsites1_pop)
    SET_INPUT_INFO_ALL_UNDEFINED(nsites1_pop_outg)
    SET_INPUT_INFO_ALL_UNDEFINED(nsites2_pop)
    SET_INPUT_INFO_ALL_UNDEFINED(nsites2_pop_outg)
    SET_INPUT_INFO_ALL_UNDEFINED(nsites3_pop)
    SET_INPUT_INFO_ALL_UNDEFINED(nsites3_pop_outg)
    SET_INPUT_INFO_ALL_UNDEFINED(li)
    SET_INPUT_INFO_ALL_UNDEFINED(r2i_ploidies)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_piw)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_pia)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_piT)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_piant)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_piTnt)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_fst)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_piwHKY)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_piaHKY)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_piTHKY)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_fstHKY)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_fst1all)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_Gst)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_hapw)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_hapa)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_hapT)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_fsth)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_fsth1all)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_fstALL)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_fsthALL)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_GstALL)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_S)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_So)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_thetaS)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_thetaSo)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_thetaT)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_thetaTo)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_thetaTHKY)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_thetaFL)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_thetaFW)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_thetaL)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_thetaSA)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_thetaTA)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_K)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_KHKY)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_Dtaj)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_Dfl)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_Ffl)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_Hnfw)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_Ez)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_Yach)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_FH)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_R2)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_Fs)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_Rm)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_ZnA)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_freq)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_nh)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_nhpop)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_freqh)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_length)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_length2)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_lengthamng)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_total_length)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_total_real_length)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_total_svratio)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_total_tcga)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_tcga)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_sv)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_svT)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_nmhits)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_H1freq)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_thetaH1)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_H0freq)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_thetaH0)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_ToH0_ii)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_ToH0_00)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_To_ii)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_To_00)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_To_i0)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_To_Qc_ii)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_To_Qw_ii)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_To_Lc_ii)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_mdsd)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_mdg1)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_mdg2)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_mdw)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_linefreq)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_anx)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_bnx)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_anxo)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_bnxo)
    SET_INPUT_INFO_ALL_UNDEFINED(stats_R2p)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_i)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_ih)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_igh)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_i1)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_ih1)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_niteri)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_niterih)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_niterigh)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_niteri1)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_niterih1)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_iall)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_ihall)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_ighall)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_niteriall)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_niterihall)
    SET_INPUT_INFO_ALL_UNDEFINED(piter_niterighall)
    SET_INPUT_INFO_ALL_UNDEFINED(output)
    SET_INPUT_INFO_ALL_UNDEFINED(nseed)
    SET_INPUT_INFO_ALL_UNDEFINED(length_seg)
  
    // Empty
  END_CALCULATION_INTERFACE_DEFINITION
}

CCalcMstatspopOutput::~CCalcMstatspopOutput() {
}

void CCalcMstatspopOutput::Prepare(void) {
  DM_GET_INPUTS
    DM_INPUT(matrix_pol)
    DM_INPUT(matrix_pol_tcga)
    DM_INPUT(positions)
    DM_INPUT(sites)
    DM_INPUT(sanc)
    DM_INPUT(mainargc)
    DM_INPUT(file_input)
    DM_INPUT(file_output)
    DM_INPUT(gfffiles)
    DM_INPUT(file_GFF)
    DM_INPUT(subset_positions)
    DM_INPUT(code_name)
    DM_INPUT(genetic_code)
    DM_INPUT(length)
    DM_INPUT(length_al)
    DM_INPUT(length_al_real)
    DM_INPUT(niter)
    DM_INPUT(ploidy)
    DM_INPUT(include_unknown)
    DM_INPUT(force_outgroup)
    DM_INPUT(the_outgroup_presence)
    DM_INPUT(vint_perpop_nsam)
    DM_INPUT(npops)
    DM_INPUT(int_total_nsam)
    DM_INPUT(svratio)
    DM_INPUT(missratio)
    DM_INPUT(jfd)
    DM_INPUT(nfd)
    DM_INPUT(H1frq)
    DM_INPUT(H0frq)
    DM_INPUT(file_H1f)
    DM_INPUT(file_H0f)
    DM_INPUT(vector_priors)
    DM_INPUT(npriors)
    DM_INPUT(formatfile)
    DM_INPUT(freq_missing_ms)
    DM_INPUT(nsites1_pop)
    DM_INPUT(nsites1_pop_outg)
    DM_INPUT(nsites2_pop)
    DM_INPUT(nsites2_pop_outg)
    DM_INPUT(nsites3_pop)
    DM_INPUT(nsites3_pop_outg)
    DM_INPUT(li)
    DM_INPUT(r2i_ploidies)
    DM_INPUT(stats_piw)
    DM_INPUT(stats_pia)
    DM_INPUT(stats_piT)
    DM_INPUT(stats_piant)
    DM_INPUT(stats_piTnt)
    DM_INPUT(stats_fst)
    DM_INPUT(stats_piwHKY)
    DM_INPUT(stats_piaHKY)
    DM_INPUT(stats_piTHKY)
    DM_INPUT(stats_fstHKY)
    DM_INPUT(stats_fst1all)
    DM_INPUT(stats_Gst)
    DM_INPUT(stats_hapw)
    DM_INPUT(stats_hapa)
    DM_INPUT(stats_hapT)
    DM_INPUT(stats_fsth)
    DM_INPUT(stats_fsth1all)
    DM_INPUT(stats_fstALL)
    DM_INPUT(stats_fsthALL)
    DM_INPUT(stats_GstALL)
    DM_INPUT(stats_S)
    DM_INPUT(stats_So)
    DM_INPUT(stats_thetaS)
    DM_INPUT(stats_thetaSo)
    DM_INPUT(stats_thetaT)
    DM_INPUT(stats_thetaTo)
    DM_INPUT(stats_thetaTHKY)
    DM_INPUT(stats_thetaFL)
    DM_INPUT(stats_thetaFW)
    DM_INPUT(stats_thetaL)
    DM_INPUT(stats_thetaSA)
    DM_INPUT(stats_thetaTA)
    DM_INPUT(stats_K)
    DM_INPUT(stats_KHKY)
    DM_INPUT(stats_Dtaj)
    DM_INPUT(stats_Dfl)
    DM_INPUT(stats_Ffl)
    DM_INPUT(stats_Hnfw)
    DM_INPUT(stats_Ez)
    DM_INPUT(stats_Yach)
    DM_INPUT(stats_FH)
    DM_INPUT(stats_R2)
    DM_INPUT(stats_Fs)
    DM_INPUT(stats_Rm)
    DM_INPUT(stats_ZnA)
    DM_INPUT(stats_freq)
    DM_INPUT(stats_nh)
    DM_INPUT(stats_nhpop)
    DM_INPUT(stats_freqh)
    DM_INPUT(stats_length)
    DM_INPUT(stats_length2)
    DM_INPUT(stats_lengthamng)
    DM_INPUT(stats_total_length)
    DM_INPUT(stats_total_real_length)
    DM_INPUT(stats_total_svratio)
    DM_INPUT(stats_total_tcga)
    DM_INPUT(stats_tcga)
    DM_INPUT(stats_sv)
    DM_INPUT(stats_svT)
    DM_INPUT(stats_nmhits)
    DM_INPUT(stats_H1freq)
    DM_INPUT(stats_thetaH1)
    DM_INPUT(stats_H0freq)
    DM_INPUT(stats_thetaH0)
    DM_INPUT(stats_ToH0_ii)
    DM_INPUT(stats_ToH0_00)
    DM_INPUT(stats_To_ii)
    DM_INPUT(stats_To_00)
    DM_INPUT(stats_To_i0)
    DM_INPUT(stats_To_Qc_ii)
    DM_INPUT(stats_To_Qw_ii)
    DM_INPUT(stats_To_Lc_ii)
    DM_INPUT(stats_mdsd)
    DM_INPUT(stats_mdg1)
    DM_INPUT(stats_mdg2)
    DM_INPUT(stats_mdw)
    DM_INPUT(stats_linefreq)
    DM_INPUT(stats_anx)
    DM_INPUT(stats_bnx)
    DM_INPUT(stats_anxo)
    DM_INPUT(stats_bnxo)
    DM_INPUT(stats_R2p)
    DM_INPUT(piter_i)
    DM_INPUT(piter_ih)
    DM_INPUT(piter_igh)
    DM_INPUT(piter_i1)
    DM_INPUT(piter_ih1)
    DM_INPUT(piter_niteri)
    DM_INPUT(piter_niterih)
    DM_INPUT(piter_niterigh)
    DM_INPUT(piter_niteri1)
    DM_INPUT(piter_niterih1)
    DM_INPUT(piter_iall)
    DM_INPUT(piter_ihall)
    DM_INPUT(piter_ighall)
    DM_INPUT(piter_niteriall)
    DM_INPUT(piter_niterihall)
    DM_INPUT(piter_niterighall)
    DM_INPUT(output)
    DM_INPUT(nseed)
    DM_INPUT(length_seg)
  DM_GET_OUTPUTS
    // Empty
  DM_END
}

void CCalcMstatspopOutput::Calculate(bool dry_run) {
  FILE *file_out = manager()->foutput();
  long int niterdata = li->value() + 1;
  
  int x=0;
  int y=0;
  int z,z1,z2,np,oo,ss,xx;
  long int zz;
  int sumnsam;
  int *initsq1 = NULL;
  double mean_z1,mean_z2;

  double cv;
  //double delta,der;
  double sf;
  /*
  double an;
  double bn;
  int j;
  */
  /*long int freqo[4];*/
  //char ancestral[1];  //!removed because it is not used
  long int fabsmatsize;

  int outgroup_presence = the_outgroup_presence->value() +
                          force_outgroup->value();

  const char *tripletsU[] =
  {
    "UUU",/*0*/  "UUC",/*1*/  "UUA",/*2*/  "UUG",/*3*/  "UCU",/*4*/  "UCC",/*5*/  "UCA",/*6*/  "UCG",/*7*/
    "UAU",/*8*/  "UAC",/*9*/  "UAA",/*10*/ "UAG",/*11*/ "UGU",/*12*/ "UGC",/*13*/ "UGA",/*14*/ "UGG",/*15*/
    "CUU",/*16*/ "CUC",/*17*/ "CUA",/*18*/ "CUG",/*19*/ "UCU",/*20*/ "CCC",/*21*/ "CCA",/*22*/ "CCG",/*23*/
    "CAU",/*24*/ "CAC",/*25*/ "CAA",/*26*/ "CAG",/*27*/ "CGU",/*28*/ "CGC",/*29*/ "CGA",/*30*/ "CGG",/*31*/
    "AUU",/*32*/ "AUC",/*33*/ "AUA",/*34*/ "AUG",/*35*/ "ACU",/*36*/ "ACC",/*37*/ "ACA",/*38*/ "ACG",/*39*/
    "AAU",/*40*/ "AAC",/*41*/ "AAA",/*42*/ "AAG",/*43*/ "AGU",/*44*/ "AGC",/*45*/ "AGA",/*46*/ "AGG",/*47*/
    "GUU",/*48*/ "GUC",/*49*/ "GUA",/*50*/ "GUG",/*51*/ "GCU",/*52*/ "GCC",/*53*/ "GCA",/*54*/ "GCG",/*55*/
    "GAU",/*56*/ "GAC",/*57*/ "GAA",/*58*/ "GAG",/*59*/ "GGU",/*60*/ "GGC",/*61*/ "GGA",/*62*/ "GGG",/*63*/
  };

  char nt1[1];
  char nt2[1];

  nt1[0] = '\x0';  //!added
  nt2[0] = '\x0';  //!added
  
/**< WTF is that LUCA_CRs???? */
#if LUCA_CRs == 1
  double luca_cvo2, luca_cvo1, luca_cv0, luca_cv1;
  double luca_dero2, luca_dero1, luca_der0, luca_der1;

  double luca_mean_z1, luca_mean_z2;
  double luca_cso2, luca_cso1, luca_cs0, luca_cs1;
  double luca_cro2, luca_cro1, luca_cr0, luca_cr1;

  double luca_cvo2d, luca_cvo1d, luca_cv0d, luca_cv1d;
  double luca_dero2d, luca_dero1d, luca_der0d, luca_der1d;

  double luca_cso2d, luca_cso1d, luca_cs0d, luca_cs1d;
  double luca_cro2d, luca_cro1d, luca_cr0d, luca_cr1d;
#endif

  initsq1 = (int *)calloc(npops->value(),sizeof(int));
  sumnsam = 0;
  for(x=0;x<npops->value();x++) {
    initsq1[x] = sumnsam;
    sumnsam += (*vint_perpop_nsam)[x];
  }

  if ((*output == 0) || (*output == 10)) {
    if(file_out == 0) file_out = stdout;
    fprintf(file_out,"\nInput file: %s",file_input->value().c_str());
    if(ploidy->value() == DIPLOID) fprintf(file_out,"\nEach sample represents two chromosomes ('.1' and '.2') IUPAC symbols must be used. Haplotype based analysis NOT SHOWN.");
    /*fprintf(file_out,"\nOutput file: %s\n",file_output->value().c_str());*/
    if(H1frq->value()) {
      fprintf(file_out,"\nH1 model frequency file: %s",file_H1f->value().c_str());
      if(H0frq->value()) {
        fprintf(file_out,"\nH0 model frequency file: %s",file_H0f->value().c_str());
      }
    }
    /**/
    if(npriors->value()) {
      fprintf(file_out,"\nPriors:\n");
      for(x=0;x<npriors->value();x++) {
        fprintf(file_out,"prior%02d: %f\t",x,(*vector_priors)[x]);
      }
    }
    /**/
    if(gfffiles->value() == 1) {
      fprintf(file_out,"\nGFF file: %s",file_GFF->value().c_str());
      fprintf(file_out,"\nPositions studied: %s",(*subset_positions).GetDataString(false));
      if(strcmp(subset_positions->GetDataString(false),"synonymous")==0 || strcmp(subset_positions->GetDataString(false),"nonsynonymous")==0 || strcmp(subset_positions->GetDataString(false),"silent")==0)
        fprintf(file_out,"\nGenetic Code: %s",(*code_name).GetDataString(false));
      if(strcmp(code_name->GetDataString(false),"Other")==0) {
        fputs("\nGenetic Code assigned to each triplet:\n",file_out);
        for(x=0;x<64;x++) {
          fprintf(file_out,"[%c%c%c] = %c\n",tripletsU[x][0],tripletsU[x][1],tripletsU[x][2],(*genetic_code)[x]);
        }
      }
    }
    fprintf(file_out,"\n\nInclude Unknown positions [1/0]: %d",include_unknown->value());
    fprintf(file_out,"\nLenght of the Total alignment (including gaps): %ld",length->value());
    fprintf(file_out,"\nLenght of the Total alignment (excluding fixed gaps but counting all positions as 1, eg. Syn positions < 1 count as 1): %ld",length_al_real->value());
    fprintf(file_out,"\nmultiple hits: %ld",stats_nmhits->value());
    fprintf(file_out,"\nLenght of the Selected alignment (including unknown bp if selected): %.2f",length_al->value());
    fprintf(file_out,"\nNumber of Variant (biallelic) sites (including unknown bp if selected and excluding codons with more than two variants, if selected): %ld",length_seg->value());

    if(svratio->value() > NA_VALUE) fprintf(file_out,"\nRatio_S/V: %.3f\n",svratio->value());
    else fprintf(file_out,"\nRatio_S/V: NA\n");

    if(include_unknown->value() ==1) fprintf(file_out,"Ratio_Missing: %.6f",missratio->value());
    else fprintf(file_out,"Ratio_Missing: NA");

    fprintf(file_out,"\n\nNumber of populations: %" PRId64 "",npops->value()-!outgroup_presence);
    if(ploidy->value() == DIPLOID) fprintf(file_out,"\nNumber of samples (duplicated) for each population:");

    fprintf(file_out,"\nNumber of samples for each population:");
    for(x=0;x<npops->value()-!outgroup_presence;x++) {
      fprintf(file_out,"\nnsam[%d]: %d",x,(*vint_perpop_nsam)[x]);
    }
    /*if(missratio > 0.) {*/
      /*
      fprintf(file_out,"\nEffective Number of samples for each population:");
      for(x=0;x<npops->value()-!outgroup_presence;x++) {
        fprintf(file_out,"\nEff_nsam[%d]: %d",x,(int)ceil(stats_length[x]/(double)length_al- 1E-5));
      }
      */
      fprintf(file_out,"\n\nEffective length for each population (with at least one sequence, two or three sequences per pop) and excluding or including outgroup (if defined):");
      for(x=0;x<npops->value()-1;x++) {
        /*if(outgroup_presence==1) {fprintf(file_out,"\nEff_length1_pop[%d]: %.2f\tEff_length2_pop[%d]: %.2f\tEff_length3_pop[%d]: %.2f\tEff_length1_pop_outg[%d]: %.2f\tEff_length2_pop_outg[%d]: %.2f\tEff_length3_pop_outg[%d]: %.2f",x,(double)nsites1_pop[x],x,(double)nsites2_pop[x],x,(double)nsites3_pop[x],x,(double)nsites1_pop_outg[x],x,(double)nsites2_pop_outg[x],x,(double)nsites3_pop_outg[x]);}*/
        if(outgroup_presence==1) {fprintf(file_out,"\nEff_length1_pop_outg[%d]: %.2f\tEff_length2_pop_outg[%d]: %.2f\tEff_length3_pop_outg[%d]: %.2f",x,(double)(*nsites1_pop_outg)[x],x,(double)(*nsites2_pop_outg)[x],x,(double)(*nsites3_pop_outg)[x]);}
				if(outgroup_presence==0) {fprintf(file_out,"\nEff_length1_pop[%d]: %.2f\tEff_length2_pop[%d]: %.2f\tEff_length3_pop[%d]: %.2f\tEff_length1_pop_outg[%d]: NA\tEff_length2_pop_outg[%d]: NA\tEff_length3_pop_outg[%d]: NA",x,(double)(*nsites1_pop)[x],x,(double)(*nsites2_pop)[x],x,(double)(*nsites3_pop)[x],x,x,x);}
      }
    /*}*/

    fprintf(file_out,"\n\nSTATISTICS:\n");

    fprintf(file_out,"\nEstimates of variability for each population (an and bn for the variant positions):\n");
    if(outgroup_presence == 1) {
      np = npops->value()-1;
      for(x=0;x<np;x++) {
        if((*vint_perpop_nsam)[x] > 1) {
          /*
          fprintf(file_out,"Sw[%d]: %d\t",x,(int)stats_S[x]);
          fprintf(file_out,"Thetaw(Wat)[%d]: %f\t",x,stats_thetaS[x]);
          fprintf(file_out,"Thetaw(Taj)[%d]: %f\t",x,stats_thetaT[x]);
          */
          fprintf(file_out,"S[%d]: %d\t",x,(int)(*stats_So)[x]);
          fprintf(file_out,"Theta(Wat)[%d]: %f\t",x,(*stats_thetaSo)[x]);
          fprintf(file_out,"Theta(Taj)[%d]: %f\t",x,(*stats_thetaTo)[x]);
          fprintf(file_out,"Theta(Fu&Li)[%d]: %f\t",x,(*stats_thetaFL)[x]);
          fprintf(file_out,"Theta(Fay&Wu)[%d]: %f\t",x,(*stats_thetaFW)[x]);
          fprintf(file_out,"Theta(Zeng)[%d]: %f\t",x,(*stats_thetaL)[x]);
          fprintf(file_out,"Theta(Achaz,Wat)[%d]: %f\t",x,(*stats_thetaSA)[x]);
          fprintf(file_out,"Theta(Achaz,Taj)[%d]: %f\t",x,(*stats_thetaTA)[x]);
          fprintf(file_out,"Divergence[%d]: %f\t",x,(*stats_K)[x]);
          if((*stats_S)[x]>0) {
            fprintf(file_out,"an_x[%d]: %f\t",x,(*stats_anx)[x]/*(double)stats_S[x]/(double)stats_thetaS[x]*/);
            fprintf(file_out,"bn_x[%d]: %f\t",x,(*stats_bnx)[x]);
            fprintf(file_out,"an_xo[%d]: %f\t",x,(*stats_anxo)[x]);
            fprintf(file_out,"bn_xo[%d]: %f\t",x,(*stats_bnxo)[x]);
          }
          else {
            fprintf(file_out,"an_x[%d]: NA\t",x);
            fprintf(file_out,"bn_x[%d]: NA\t",x);
            fprintf(file_out,"an_xo[%d]: NA\t",x);
            fprintf(file_out,"bn_xo[%d]: NA\t",x);
          }
          fprintf(file_out,"\n");
        }
        else {
          fprintf(file_out,"Sw[%d]: NA\t",x);
          fprintf(file_out,"Thetaw(Wat)[%d]: NA\t",x);
          fprintf(file_out,"Thetaw(Taj)[%d]: NA\t",x);
          fprintf(file_out,"S[%d]: NA\t",x);
          fprintf(file_out,"Theta(Wat)[%d]: NA\t",x);
          fprintf(file_out,"Theta(Taj)[%d]: NA\t",x);
          fprintf(file_out,"Theta(Fu&Li)[%d]: NA\t",x);
          fprintf(file_out,"Theta(Fay&Wu)[%d]: NA\t",x);
          fprintf(file_out,"Theta(Zeng)[%d]: NA\t",x);
          fprintf(file_out,"Theta(Achaz,Wat)[%d]: NA\t",x);
          fprintf(file_out,"Theta(Achaz,Taj)[%d]: NA\t",x);
          fprintf(file_out,"Divergence[%d]: %f\t",x,(*stats_K)[x]);
          fprintf(file_out,"an_x[%d]: NA\t",x);
          fprintf(file_out,"bn_x[%d]: NA\t",x);
          fprintf(file_out,"an_xo[%d]: NA\t",x);
          fprintf(file_out,"bn_xo[%d]: NA\t",x);
          fprintf(file_out,"\n");
        }
      }
    }
    else {
      np = npops->value()-1;
      for(x=0;x<np;x++) {
        if((*vint_perpop_nsam)[x] > 1) {
          fprintf(file_out,"S[%d]: %d\t",x,(int)(*stats_S)[x]);
          fprintf(file_out,"Theta(Wat)[%d]: %f\t",x,(*stats_thetaS)[x]);
          fprintf(file_out,"Theta(Taj)[%d]: %f\t",x,(*stats_thetaT)[x]);
          fprintf(file_out,"Theta(Fu&Li)[%d]: %f\t",x,(*stats_thetaFL)[x]);
          fprintf(file_out,"Theta(Achaz,Wat)[%d]: %f\t",x,(*stats_thetaSA)[x]);
          fprintf(file_out,"Theta(Achaz,Taj)[%d]: %f\t",x,(*stats_thetaTA)[x]);
          if((*stats_S)[x]>0) {
            fprintf(file_out,"an_x[%d]: %f\t",x,(*stats_anx)[x]/*(double)stats_S[x]/(double)stats_thetaS[x]*/);
            fprintf(file_out,"bn_x[%d]: %f\t",x,(*stats_bnx)[x]);
            fprintf(file_out,"an_xo[%d]: %f\t",x,(*stats_anxo)[x]);
            fprintf(file_out,"bn_xo[%d]: %f\t",x,(*stats_bnxo)[x]);
          }
          else {
            fprintf(file_out,"an_x[%d]: NA\t",x);
            fprintf(file_out,"bn_x[%d]: NA\t",x);
            fprintf(file_out,"an_xo[%d]: NA\t",x);
            fprintf(file_out,"bn_xo[%d]: NA\t",x);
          }
          fprintf(file_out,"\n");
        }
        else {
          fprintf(file_out,"S[%d]: NA\t",x);
          fprintf(file_out,"Theta(Wat)[%d]: NA\t",x);
          fprintf(file_out,"Theta(Taj)[%d]: NA\t",x);
          fprintf(file_out,"Theta(Fu&Li)[%d]: NA\t",x);
          fprintf(file_out,"Theta(Achaz,Wat)[%d]: NA\t",x);
          fprintf(file_out,"Theta(Achaz,Taj)[%d]: NA\t",x);
          fprintf(file_out,"an_x[%d]: NA\t",x);
          fprintf(file_out,"bn_x[%d]: NA\t",x);
          fprintf(file_out,"an_xo[%d]: NA\t",x);
          fprintf(file_out,"bn_xo[%d]: NA\t",x);
          /*fprintf(file_out,"theta_square[%d]: NA\n",x);*/
          fprintf(file_out,"\n");
        }
      }
    }
    if(formatfile->value() != MS_X_FILE) {
      fprintf(file_out,"\nEstimates of NUCLEOTIDE variability for each population (if missing, corrected by the averaged effective positions):\n");
      if(outgroup_presence == 1) {
        np = npops->value()-1;
        for(x=0;x<np;x++) {
          if((*vint_perpop_nsam)[x] > 1) {
            /*
            fprintf(file_out,"Sw[%d]: %d\t",x,(int)stats_S[x]);
            fprintf(file_out,"Thetaw/nt(Wat)[%d]: %f\t",x,stats_thetaS[x]/(double)nsites2_pop[x]);
            fprintf(file_out,"Thetaw/nt(Taj)[%d]: %f\t",x,stats_thetaT[x]/(double)nsites2_pop[x]);
            */
            fprintf(file_out,"S[%d]: %d\t",x,(int)(*stats_So)[x]);
						if((*nsites2_pop_outg)[x] > 0) fprintf(file_out,"Theta/nt(Wat)[%d]: %f\t",x,(*stats_thetaSo)[x]/(double)(*nsites2_pop_outg)[x]);
                        else fprintf(file_out,"Theta/nt(Wat)[%d]: NA\t",x);
						if((*nsites2_pop_outg)[x] > 0) fprintf(file_out,"Theta/nt(Taj)[%d]: %f\t",x,(*stats_thetaTo)[x]/(double)(*nsites2_pop_outg)[x]);
                        else fprintf(file_out,"Theta/nt(Taj)[%d]: NA\t",x);
						if((*nsites2_pop_outg)[x] > 0) fprintf(file_out,"Theta/nt(Fu&Li)[%d]: %f\t",x,(*stats_thetaFL)[x]/(double)(*nsites2_pop_outg)[x]);
                        else fprintf(file_out,"Theta/nt(Fu&Li)[%d]: NA\t",x);
						if((*nsites2_pop_outg)[x] > 0) fprintf(file_out,"Theta/nt(Fay&Wu)[%d]: %f\t",x,(*stats_thetaFW)[x]/(double)(*nsites2_pop_outg)[x]);
                        else fprintf(file_out,"Theta/nt(Fay&Wu)[%d]: NA\t",x);
						if((*nsites2_pop_outg)[x] > 0) fprintf(file_out,"Theta/nt(Zeng)[%d]: %f\t",x,(*stats_thetaL)[x]/(double)(*nsites2_pop_outg)[x]);
                        else fprintf(file_out,"Theta/nt(Zeng)[%d]: NA\t",x);
						if((*nsites3_pop_outg)[x] > 0) fprintf(file_out,"Theta/nt(Achaz,Wat)[%d]: %f\t",x,(*stats_thetaSA)[x]/(double)(*nsites3_pop_outg)[x]);
                        else fprintf(file_out,"Theta/nt(Achaz,Wat)[%d]: NA\t",x);
						if((*nsites3_pop_outg)[x] > 0) fprintf(file_out,"Theta/nt(Achaz,Taj)[%d]: %f\t",x,(*stats_thetaTA)[x]/(double)(*nsites3_pop_outg)[x]);
                        else fprintf(file_out,"Theta/nt(Achaz,Taj)[%d]: NA\t",x);
						if((*nsites1_pop_outg)[x] > 0) fprintf(file_out,"Divergence[%d]: %f\t",x,(*stats_K)[x]/(double)(*nsites1_pop_outg)[x]);
                        else fprintf(file_out,"Divergence/nt[%d]: NA\t",x);
//            if(nsites2_pop_outg[x] > 0) fprintf(file_out,"Theta/nt(Wat)[%d]: %f\t",x,(*stats_thetaSo)[x]/(double)(*nsites2_pop_outg)[x]);
//            if(nsites2_pop_outg[x] > 0) fprintf(file_out,"Theta/nt(Taj)[%d]: %f\t",x,(*stats_thetaTo)[x]/(double)(*nsites2_pop_outg)[x]);
//            if(nsites2_pop_outg[x] > 0) fprintf(file_out,"Theta/nt(Fu&Li)[%d]: %f\t",x,(*stats_thetaFL)[x]/(double)(*nsites2_pop_outg)[x]);
//            if(nsites2_pop_outg[x] > 0) fprintf(file_out,"Theta/nt(Fay&Wu)[%d]: %f\t",x,(*stats_thetaFW)[x]/(double)(*nsites2_pop_outg)[x]);
//            if(nsites2_pop_outg[x] > 0) fprintf(file_out,"Theta/nt(Zeng)[%d]: %f\t",x,(*stats_thetaL)[x]/(double)(*nsites2_pop_outg)[x]);            
//            //!added 23_feb_2016
//            if((*vint_perpop_nsam)[x] > 2) {
//              fprintf(file_out,"Theta/nt(Achaz,Wat)[%d]: %f\t",x,(*stats_thetaSA)[x]/(double)(*nsites3_pop_outg)[x]);
//              fprintf(file_out,"Theta/nt(Achaz,Taj)[%d]: %f\t",x,(*stats_thetaTA)[x]/(double)(*nsites3_pop_outg)[x]);
//            }
//            else {
//              fprintf(file_out,"Theta/nt(Achaz,Wat)[%d]: NA\t",x);
//              fprintf(file_out,"Theta/nt(Achaz,Taj)[%d]: NA\t",x);
//            }
//            
//            fprintf(file_out,"Divergence[%d]: %f\t",x,(*stats_K)[x]/(double)(*nsites1_pop_outg)[x]);
            if((*stats_thetaTHKY)[x] > NA_VALUE && missratio->value() == 0.) fprintf(file_out,"Theta/nt(Taj)HKY[%d]: %f\t",x,(*stats_thetaTHKY)[x]);
            else fprintf(file_out,"Theta/nt(Taj)HKY[%d]: NA\t",x);
            if((*stats_KHKY)[x] > NA_VALUE && missratio->value() == 0.) fprintf(file_out,"DivergenceHKY[%d]: %f\n",x,(*stats_KHKY)[x]);
            else fprintf(file_out,"DivergenceHKY[%d]: NA\n",x);
          }
          else {
            fprintf(file_out,"S[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Wat)[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Taj)[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Fu&Li)[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Fay&Wu)[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Zeng)[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Achaz,Wat)[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Achaz,Taj)[%d]: NA\t",x);
            fprintf(file_out,"Divergence/nt[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Taj)HKY[%d]: NA\t",x);
            fprintf(file_out,"DivergenceHKY[%d]: NA\n",x);
          }
        }
      }
      else {
        np = npops->value()-1;
        for(x=0;x<np;x++) {
          if((*vint_perpop_nsam)[x] > 1) {
						fprintf(file_out,"S[%d]: %d\t",x,(int)(*stats_S)[x]);
						if((*nsites2_pop_outg)[x] > 0) fprintf(file_out,"Theta/nt(Wat)[%d]: %f\t",x,(*stats_thetaS)[x]/(double)(*nsites2_pop)[x]);
                        else fprintf(file_out,"Theta/nt(Wat)[%d]: NA\t",x);
						if((*nsites2_pop_outg)[x] > 0) fprintf(file_out,"Theta/nt(Taj)[%d]: %f\t",x,(*stats_thetaT)[x]/(double)(*nsites2_pop)[x]);
                        else fprintf(file_out,"Theta/nt(Taj)[%d]: NA\t",x);
						if((*nsites2_pop_outg)[x] > 0) fprintf(file_out,"Theta/nt(Fu&Li)[%d]: %f\t",x,(*stats_thetaFL)[x]/(double)(*nsites2_pop)[x]);
                        else fprintf(file_out,"Theta/nt(Fu&Li)[%d]: NA\t",x);
						if((*nsites3_pop_outg)[x] > 0) fprintf(file_out,"Theta/nt(Achaz,Wat)[%d]: %f\t",x,(*stats_thetaSA)[x]/(double)(*nsites3_pop)[x]);
                        else fprintf(file_out,"Theta/nt(Achaz,Wat)[%d]: NA\t",x);
						if((*nsites3_pop_outg)[x] > 0) fprintf(file_out,"Theta/nt(Achaz,Taj)[%d]: %f\t",x,(*stats_thetaTA)[x]/(double)(*nsites3_pop)[x]);
                        else fprintf(file_out,"Theta/nt(Taj)HKY[%d]: NA\n",x);
						if((*stats_thetaTHKY)[x] > -10000 && missratio->value() == 0.) fprintf(file_out,"Theta/nt(Taj)HKY[%d]: %f\t",x,(*stats_thetaTHKY)[x]);
						else fprintf(file_out,"Theta/nt(Taj)HKY[%d]: NA\t",x);
						fprintf(file_out,"\n");            
            
            
            
//            fprintf(file_out,"S[%d]: %d\t",x,(int)(*stats_S)[x]);
//            fprintf(file_out,"Theta/nt(Wat)[%d]: %f\t",x,(*stats_thetaS)[x]/(double)(*nsites2_pop)[x]);
//            fprintf(file_out,"Theta/nt(Taj)[%d]: %f\t",x,(*stats_thetaT)[x]/(double)(*nsites2_pop)[x]);
//            fprintf(file_out,"Theta/nt(Fu&Li)[%d]: %f\t",x,(*stats_thetaFL)[x]/(double)(*nsites2_pop)[x]);
//            
//            //!added 23_feb_2016
//            if((*vint_perpop_nsam)[x] > 2) {
//              fprintf(file_out,"Theta/nt(Achaz,Wat)[%d]: %f\t",x,(*stats_thetaSA)[x]/(double)(*nsites3_pop)[x]);
//              fprintf(file_out,"Theta/nt(Achaz,Taj)[%d]: %f\t",x,(*stats_thetaTA)[x]/(double)(*nsites3_pop)[x]);
//            } else {
//              fprintf(file_out,"Theta/nt(Achaz,Wat)[%d]: NA\t",x);
//              fprintf(file_out,"Theta/nt(Achaz,Taj)[%d]: NA\t",x);
//            }
//            
//            if((*stats_thetaTHKY)[x] > NA_VALUE && missratio->value() == 0.) fprintf(file_out,"Theta/nt(Taj)HKY[%d]: %f\t",x,(*stats_thetaTHKY)[x]);
//            else fprintf(file_out,"Theta/nt(Taj)HKY[%d]: NA\t",x);
//            fprintf(file_out,"\n");
          }
          else {
            fprintf(file_out,"S[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Wat)[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Taj)[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Fu&Li)[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Achaz,Wat)[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Achaz,Taj)[%d]: NA\t",x);
            fprintf(file_out,"Theta/nt(Taj)HKY[%d]: NA\n",x);
            fprintf(file_out,"\n");
          }
        }
      }
    }
    if(include_unknown->value() == 0 && ploidy->value() == HAPLOID) {
      fprintf(file_out,"\nHaplotype diversity and number of haplotypes for each population:\n");
      np = npops->value()-1;
      for(x=0;x<np;x++) {
        if((*vint_perpop_nsam)[x]>1) {
          fprintf(file_out,"HapW[%d]: %f\tnHap[%d]: %d",x,(*stats_hapw)[x],x,(*stats_nhpop)[x]);
          fprintf(file_out,"\n");
        }
        else {
          fprintf(file_out,"HapW[%d]: NA\tnHap[%d]: 1",x,x);
          fprintf(file_out,"\n");
        }
      }
    }
    fprintf(file_out,"\nNeutrality tests for each population:\n");
    if(outgroup_presence == 1) {
      np = npops->value()-1;
      for(x=0;x<np;x++) {
        if((*stats_Dtaj)[x] > NA_VALUE)
          fprintf(file_out,"Tajima D[%d]: %f\t",x,(*stats_Dtaj)[x]);
        else fprintf(file_out,"Tajima D[%d]: NA\t",x);
        if((*stats_Dfl)[x] > NA_VALUE)
          fprintf(file_out,"Fu&Li D[%d]: %f\t",x,(*stats_Dfl)[x]);
        else  fprintf(file_out,"Fu&Li D[%d]: NA\t",x);
        if((*stats_Ffl)[x] > NA_VALUE)
          fprintf(file_out,"Fu&Li F[%d]: %f\t",x,(*stats_Ffl)[x]);
        else fprintf(file_out,"Fu&Li F[%d]: NA\t",x);
        if((*stats_Hnfw)[x] > NA_VALUE)
          fprintf(file_out,"Fay&Wu norm H[%d]: %f\t",x,(*stats_Hnfw)[x]);
        else fprintf(file_out,"Fay&Wu norm H[%d]: NA\t",x);
        if((*stats_thetaT)[x]-(*stats_thetaFW)[x] != NA_VALUE)
          fprintf(file_out,"Fay&WuH[%d]:\t%f\t",x,(*stats_thetaT)[x]-(*stats_thetaFW)[x]);
        else fprintf(file_out,"Fay&WuH[%d]: NA\t",x);
        if((*stats_Ez)[x] > NA_VALUE)
          fprintf(file_out,"Zeng E[%d]: %f\t",x,(*stats_Ez)[x]);
        else fprintf(file_out,"Zeng E[%d]: NA\t",x);
        if((*stats_Yach)[x] > NA_VALUE)
          fprintf(file_out,"Achaz Y[%d]: %f\t",x,(*stats_Yach)[x]);
        else fprintf(file_out,"Achaz Y[%d]: NA\t",x);
/**/
        if((*stats_FH)[x] > NA_VALUE)
            fprintf(file_out,"WH[%d]: %f\t",x,(*stats_FH)[x]);
        else fprintf(file_out,"WH[%d]: NA\t",x);
/**/
        
        if(ploidy->value() == HAPLOID) {
          /*
          if(stats_R2[x] > NA_VALUE)
            fprintf(file_out,"R2[%d]: %f\t",x,stats_R2[x]);
          else fprintf(file_out,"R2[%d]: NA\t",x);
          */
          if(include_unknown->value() == 0) {
            if((*stats_Fs)[x] > NA_VALUE && missratio->value() < 1e-6)
              fprintf(file_out,"Fs[%d]: %f\t",x,(*stats_Fs)[x]);
            else fprintf(file_out,"Fs[%d]: NA\t",x);
          }
        }/*
        else {
          if(stats_R2[x] > NA_VALUE)
            fprintf(file_out,"R2d[%d]: %f\t",x,stats_R2[x]);
          else fprintf(file_out,"R2d[%d]: NA\t",x);
        }
        */
        for(xx=0;xx<(*r2i_ploidies)[0];xx++) {
          if((*stats_R2p)[xx][x] > NA_VALUE) {
            if((*r2i_ploidies)[0]==1 && ploidy->value() == HAPLOID) fprintf(file_out,"R2[%d]: %f\t",x,(*stats_R2p)[xx][x]);
            if((*r2i_ploidies)[0]==1 && ploidy->value() == DIPLOID) fprintf(file_out,"R2d[%d]: %f\t",x,(*stats_R2p)[xx][x]);
            if((*r2i_ploidies)[0]!=1) fprintf(file_out,"R2p%d[%d]: %f\t",(*r2i_ploidies)[xx+1],x,(*stats_R2p)[xx][x]);
          } else {
            if((*r2i_ploidies)[0]==1 && ploidy->value() == HAPLOID) fprintf(file_out,"R2[%d]: NA\t",x);
            if((*r2i_ploidies)[0]==1 && ploidy->value() == DIPLOID) fprintf(file_out,"R2d[%d]: NA\t",x);
            if((*r2i_ploidies)[0]!=1) fprintf(file_out,"R2p%d[%d]: NA\t",(*r2i_ploidies)[xx+1],x);

          }
        }

        /*fprintf(file_out,"Fay&WuH[%d]:\t%f\t",x,stats_thetaT[x]-stats_thetaFW[x]);*/
        /*fprintf(file_out,"Fay&WuH2[%d]:\t%f\t",x,2.*(stats_thetaT[x]-stats_thetaL[x]));*/
        fprintf(file_out,"\n");
      }
    }
    else {
      np = npops->value()-1;
      for(x=0;x<np;x++) {
        if((*stats_Dtaj)[x] > NA_VALUE)
          fprintf(file_out,"Tajima D[%d]: %f\t",x,(*stats_Dtaj)[x]);
        else fprintf(file_out,"Tajima D[%d]: NA\t",x);
        if((*stats_Dfl)[x] > NA_VALUE)
          fprintf(file_out,"Fu&Li D*[%d]: %f\t",x,(*stats_Dfl)[x]);
        else  fprintf(file_out,"Fu&Li D*[%d]: NA\t",x);
        if((*stats_Ffl)[x] > NA_VALUE)
          fprintf(file_out,"Fu&Li F*[%d]: %f\t",x,(*stats_Ffl)[x]);
        else fprintf(file_out,"Fu&Li F*[%d]: NA\t",x);
        if((*stats_Yach)[x] > NA_VALUE)
          fprintf(file_out,"Achaz Y*[%d]: %f\t",x,(*stats_Yach)[x]);
        else fprintf(file_out,"Achaz Y*[%d]: NA\t",x);
        if(ploidy->value() == HAPLOID) {
          /*
          if(stats_R2[x] > NA_VALUE)
            fprintf(file_out,"R2[%d]: %f\t",x,stats_R2[x]);
          else fprintf(file_out,"R2[%d]: NA\t",x);
          */
          if(include_unknown->value() == 0) {
            if((*stats_Fs)[x] > NA_VALUE && missratio->value() < 1e-6)
              fprintf(file_out,"Fs[%d]: %f\t",x,(*stats_Fs)[x]);
            else fprintf(file_out,"Fs[%d]: NA\t",x);
          }
        }/*
        else {
          if(stats_R2[x] > NA_VALUE)
            fprintf(file_out,"R2d[%d]: %f\t",x,stats_R2[x]);
          else fprintf(file_out,"R2d[%d]: NA\t",x);
        }*/
        for(xx=0;xx<(*r2i_ploidies)[0];xx++) {
          if((*stats_R2p)[xx][x] > NA_VALUE) {
            if((*r2i_ploidies)[0]==1 && ploidy->value() == HAPLOID) fprintf(file_out,"R2[%d]: %f\t",x,(*stats_R2p)[xx][x]);
            if((*r2i_ploidies)[0]==1 && ploidy->value() == DIPLOID) fprintf(file_out,"R2d[%d]: %f\t",x,(*stats_R2p)[xx][x]);
            if((*r2i_ploidies)[0]!=1) fprintf(file_out,"R2p%d[%d]: %f\t",(*r2i_ploidies)[xx+1],x,(*stats_R2p)[xx][x]);
          } else {
            if((*r2i_ploidies)[0]==1 && ploidy->value() == HAPLOID) fprintf(file_out,"R2[%d]: NA\t",x);
            if((*r2i_ploidies)[0]==1 && ploidy->value() == DIPLOID) fprintf(file_out,"R2d[%d]: NA\t",x);
            if((*r2i_ploidies)[0]!=1) fprintf(file_out,"R2p%d[%d]: NA\t",(*r2i_ploidies)[xx+1],x);

          }
        }

        fprintf(file_out,"\n");
      }
    }

    if(H1frq->value()/* && missratio == 0.*/) {
      if(outgroup_presence == 1) {
        fprintf(file_out,"\nAlternative Expected Frequency Spectrum of variants for each population:");
        for(x=0;x<npops->value()-1;x++) {
          fprintf(file_out,"\n");
          for(y=1;y<(*vint_perpop_nsam)[x];y++) {
            fprintf(file_out,"frH1[%d,%d]: %.5f\t",x,y,(*stats_H1freq)[x][y]);
          }
        }
        fprintf(file_out,"\nOptimal tests given SNM as null model: To[inf,inf], To[0,0], To[inf,0]");/*, ToQc[inf,inf], ToQw[inf,inf], ToLc[inf,inf].");*/
        for(x=0;x<npops->value()-1;x++) {
          fprintf(file_out,"\n");
          if((*stats_To_ii)[x] > NA_VALUE)
            fprintf(file_out,"To_ii[%d]: %f\t",x,(*stats_To_ii)[x]);
          else  fprintf(file_out,"To_ii[%d]: NA\t",x);
          if((*stats_To_00)[x] > NA_VALUE)
            fprintf(file_out,"To_00[%d]: %f\t",x,(*stats_To_00)[x]);
          else  fprintf(file_out,"To_00[%d]: NA\t",x);
          if((*stats_To_i0)[x] > NA_VALUE)
            fprintf(file_out,"To_i0[%d]: %f\t",x,(*stats_To_i0)[x]);
          else  fprintf(file_out,"To_i0[%d]: NA\t",x);
        #if TO_NEW
          if(stats_To_Qc_ii[x] > NA_VALUE)
            fprintf(file_out,"To_Qc_ii[%d]: %f\t",x,stats_To_Qc_ii[x]);
          else  fprintf(file_out,"To_Qc_ii[%d]: NA\t",x);
          if(stats_To_Qw_ii[x] > NA_VALUE)
            fprintf(file_out,"To_Qw_ii[%d]: %f\t",x,stats_To_Qw_ii[x]);
          else  fprintf(file_out,"To_Qw_ii[%d]: NA\t",x);
          if(stats_To_Lc_ii[x] > NA_VALUE)
            fprintf(file_out,"To_Lc_ii[%d]: %f\t",x,stats_To_Lc_ii[x]);
          else  fprintf(file_out,"To_Lc_ii[%d]: NA\t",x);
        #endif
        }
        fprintf(file_out,"\n");
        if(H0frq->value()) {
          fprintf(file_out,"\nNULL Expected Frequency Spectrum of variants for each population:");
          for(x=0;x<npops->value()-1;x++) {
            fprintf(file_out,"\n");
            for(y=1;y<(*vint_perpop_nsam)[x];y++) {
              fprintf(file_out,"frH1[%d,%d]: %.5f\t",x,y,(*stats_H0freq)[x][y]);
            }
          }
          fprintf(file_out,"\nOptimal tests given the null expected frequency Spectrum as null model: ToH0[inf,inf], ToH0[inf,0].");
          for(x=0;x<npops->value()-1;x++) {
            fprintf(file_out,"\n");
            if((*stats_ToH0_ii)[x] > NA_VALUE)
              fprintf(file_out,"To_H0_ii[%d]: %f\t",x,(*stats_ToH0_ii)[x]);
            else  fprintf(file_out,"To_H0_ii[%d]: NA\t",x);
            if((*stats_ToH0_00)[x] > NA_VALUE)
              fprintf(file_out,"To_H0_i0[%d]: %f\t",x,(*stats_ToH0_00)[x]);
            else  fprintf(file_out,"To_H0_i0[%d]: NA\t",x);
          }
          fprintf(file_out,"\n");
        }
      }
    }

    fprintf(file_out,"\nVariants assigned to exclusive, fixed, polymorphic but fixed in rest of pops, and shared.\n");
    fprintf(file_out,"Ss[rest] are shared variants between populations but fixed within:\n");
    if(npops->value()>2 && outgroup_presence == 1) {
      for(x=0;x<npops->value()-1;x++) {
        fprintf(file_out,"Sx[%d]: %ld\t",x,(*sanc)[x*4+0]);
        fprintf(file_out,"Sf[%d]: %ld\t",x,(*sanc)[x*4+1]);
        fprintf(file_out,"Sxf[%d,rest]: %ld\t",x,(*sanc)[x*4+2]);
        fprintf(file_out,"Ss[%d]: %ld\n",x,(*sanc)[x*4+3]);
      }
      fprintf(file_out,"Sx[outg]: %ld\t",(*sanc)[(npops->value()-1)*4+0]);
      fprintf(file_out,"Sf[outg]: %ld\t",(*sanc)[(npops->value()-1)*4+1]);
      fprintf(file_out,"Ss[outg,rest]: %ld\t",(*sanc)[(npops->value()-1)*4+2]);
      if(npops->value() > 3) fprintf(file_out,"Ss[rest]:\t%ld\n",(*sanc)[(npops->value()-1)*4+3]);
      else fprintf(file_out,"Ss[rest]:\tNA\n");
    }
    else {
      if(npops->value()>2 && outgroup_presence == 0) {
        for(x=0;x<npops->value()-1;x++) {
          fprintf(file_out,"Sx[%d]: %ld\t",x,(*sanc)[x*4+0]/* + (*sanc)[x*4+2]*/);
          fprintf(file_out,"Sf[%d]: %ld\t",x,(*sanc)[x*4+1]);
          fprintf(file_out,"Ss[%d]: %ld\n",x,(*sanc)[x*4+3]);
        }
        fprintf(file_out,"Ss[rest]: %ld\n",(*sanc)[(npops->value()-1)*4+3]);
      }
      else {
        if(npops->value() > 1) {
          x = 0;
          fprintf(file_out,"Sx[%d]: %ld\t",x,(*sanc)[x*4+0]);
          x = 1;
          fprintf(file_out,"Sx[%d]: %ld\t",x,(*sanc)[x*4+0]);
          x=0;
          fprintf(file_out,"Sf: %ld\t",(*sanc)[x*4+1]);
          fprintf(file_out,"Ss: %ld\n",(*sanc)[x*4+3]);
        }
        else
          fprintf(file_out,"Sx[%d]: %ld\n",x,(*sanc)[0*4+0]);
      }
    }
    /*if(ploidy->value() == HAPLOID && include_unknown->value() == 0) { */
      fprintf(file_out,"\nmismatch distribution statistics:\n");
      for(x=0;x<npops->value()-1/*!outgroup_presence*/;x++) {
        if((*vint_perpop_nsam)[x] > 2) {
          fprintf(file_out,"SDev[%d]: %f\t",x,(*stats_mdsd)[x]);
          if((*stats_mdg1)[x] > NA_VALUE) fprintf(file_out,"Skewness[%d]: %f\t",x,(*stats_mdg1)[x]); //.
          else fprintf(file_out,"Skewness[%d]: NA\t",x);
        }
        else {
          fprintf(file_out,"SDev[%d]: NA\t",x);
          fprintf(file_out,"Skewness[%d]: NA\t",x);
        }
        if((*vint_perpop_nsam)[x] > 3) {
          if((*stats_mdg2)[x] > NA_VALUE) fprintf(file_out,"Kurtosis[%d]: %f\t",x,(*stats_mdg2)[x]); //.
          else fprintf(file_out,"Kurtosis[%d]: NA\t",x);
        }
        else
          fprintf(file_out,"Kurtosis[%d]: NA\t",x);

        fprintf(file_out,"\n");
      }
    /*}*/
    if(npops->value()-1/*!outgroup_presence*/ > 1) {
      fprintf(file_out,"\nFst (calculated as 1-piw/pia): OUTGROUP NOT CONSIDERED (results may be different from above)\n"); /*ANALYSIS using estimator from Hudson, Slatkin and Maddison (Genetics, 1992) and Gst' from Nei (1987)*/
      fprintf(file_out,"\nseed: %ld",nseed->value());
      if(npops->value()-1/*!outgroup_presence*/ > 2) {
        fprintf(file_out,"\nFst(nucleotide) and FstH(haplotype)for the whole populations (except outgroup)");/* and Gst' */
        if(niter->value()) fprintf(file_out," and P-values using %ld iterations with permutation test:\n",niter->value());
        else fprintf(file_out,"\n");
        if(stats_fstALL->value() > NA_VALUE) {
          if(niter->value() && piter_niteriall > 0)
            fprintf(file_out,"Fst: %f\t P-value: %f\t",stats_fstALL->value(),(double)piter_iall->value()/(double)piter_niteriall->value());
          else
            fprintf(file_out,"Fst: %f\t P-value: NA\t",stats_fstALL->value());
        }
        else {
          if(niter->value() && piter_niteriall > 0)
            fprintf(file_out,"Fst: NA\t P-value: NA\t");
          else
            fprintf(file_out,"Fst: NA\t P-value: NA\t");
        }
        if(ploidy->value() == HAPLOID && include_unknown->value() == 0) {
          if(stats_fsthALL->value() > NA_VALUE) {
            if(niter->value() && piter_niterihall > 0)
              fprintf(file_out,"FstH: %f\t P-value: %f\t",stats_fsthALL->value(),(double)piter_ihall->value()/(double)piter_niterihall->value());
            else
              fprintf(file_out,"FstH: %f\t P-value: NA\t",stats_fsthALL->value());
          }
          else {
            if(niter->value() && piter_niterihall > 0)
              fprintf(file_out,"FstH: NA\t P-value: NA\t");
            else
              fprintf(file_out,"FstH: NA\t P-value: NA\t");
          }
          /*
          if(stats_GstALL->value() > NA_VALUE) {
            if(niter && piter_niterighall > 0)
              fprintf(file_out,"Gst': %f\t P-value: %f\t",stats_GstALL->value(),(double)piter_ighall/(double)piter_niterighall);
            else
              fprintf(file_out,"Gst': %f\t P-value: NA\t",stats_GstALL->value());
          }
          else {
            if(niter && piter_niterighall > 0)
              fprintf(file_out,"Gst': NA\t P-value: NA\t");
            else
              fprintf(file_out,"Gst': NA\t P-value: NA\t");
          }
           */
        }
        fprintf(file_out,"\n");

        fprintf(file_out,"\nFst(nucleotide) and FstH(haplotype) of each population ACROSS ALL the rest (except outgroup)");
        if(niter->value()) fprintf(file_out," and P-values using %ld iterations with permutation test:\n",niter->value());
        else fprintf(file_out,"\n");
        for(x=0;x<npops->value()-1;x++) {
          if((*stats_fst1all)[x] > NA_VALUE) {
            if(niter->value() && (*piter_niteri1)[x] > 0)
              fprintf(file_out,"Fst1[%d,rest]: %f\t P-value: %f\t",x,(*stats_fst1all)[x],(double)(*piter_i1)[x]/(double)(*piter_niteri1)[x]);
            else
              fprintf(file_out,"Fst1[%d,rest]: %f\t P-value: NA\t",x,(*stats_fst1all)[x]);
          }
          else {
            if(niter->value() && (*piter_niteri1)[x] > 0)
              fprintf(file_out,"Fst1[%d,rest]: NA\t P-value: NA\t",x);
            else
              fprintf(file_out,"Fst1[%d,rest]: NA\t P-value: NA\t",x);
          }
          if(ploidy->value() == HAPLOID && include_unknown->value() == 0) {
            if((*stats_fsth1all)[x] > NA_VALUE) {
              if(niter->value() && (*piter_niterih1)[x] > 0)
                fprintf(file_out,"Fst1H[%d,rest]: %f\t P-value: %f\t",x,(*stats_fsth1all)[x],(double)(*piter_ih1)[x]/(double)(*piter_niterih1)[x]);
              else
                fprintf(file_out,"Fst1H[%d,rest]: %f\t P-value: NA\t",x,(*stats_fsth1all)[x]);
            }
            else {
              if(niter->value() && (*piter_niterih1)[x] > 0)
                fprintf(file_out,"Fst1H[%d,rest]: NA\t P-value: NA\t",x);
              else
                fprintf(file_out,"Fst1H[%d,rest]: NA\t P-value: NA\t",x);
            }
          }
          fprintf(file_out,"\n");
        }
      }

      fprintf(file_out,"\nFst(nucleotide), FstH(haplotype)"); /* and Gst' BETWEEN populations*/
      if(niter->value()) fprintf(file_out," and P-values using %ld iterations with permutation test:\n",niter->value());
      else fprintf(file_out,"\n");
      z=0;
      for(x=0;x<npops->value()-1;x++) {
        for(y=x+1;y<npops->value()-0;y++) {
          if(y==npops->value()-1) {z++;continue;}
          if((*stats_fst)[z] > NA_VALUE) {
            if(niter->value() && (*piter_niteri)[z] > 0)
              fprintf(file_out,"Fst[%d,%d]: %f\t P-value: %f\t",x,y,(*stats_fst)[z],(double)(*piter_i)[z]/(double)(*piter_niteri)[z]);
            else
              fprintf(file_out,"Fst[%d,%d]: %f\t P-value: NA\t",x,y,(*stats_fst)[z]);
          }
          else {
            if(niter->value() && (*piter_niteri)[z] > 0)
              fprintf(file_out,"Fst[%d,%d]: NA\t P-value: NA\t",x,y);
            else
              fprintf(file_out,"Fst[%d,%d]: NA\t P-value: NA\t",x,y);
          }
          fprintf(file_out,"\n");
          z++;
        }
      }
      fprintf(file_out,"\n");
      z=0;
      for(x=0;x<npops->value()-2;x++) { /*NOTE THE HAPLOTYPE VALUES GOES FROM 0 to npops->value()-1 BUT FREQUENCY GOES FROM 0 to npops->value()!!!!!!*/
        for(y=x+1;y<npops->value()-1;y++) {
          if(y==npops->value()-1) {z++;continue;}
          if(ploidy->value() == HAPLOID && include_unknown->value() == 0) {
            if((*stats_fsth)[z] > NA_VALUE) {
              if(niter->value() && (*piter_niterih)[z] > 0)
                fprintf(file_out,"FstH[%d,%d]: %f\t P-value: %f\t",x,y,(*stats_fsth)[z],(double)(*piter_ih)[z]/(double)(*piter_niterih)[z]);
              else
                fprintf(file_out,"FstH[%d,%d]: %f\t P-value: NA\t",x,y,(*stats_fsth)[z]);
            }
            else {
              if(niter->value() && (*piter_niterih)[z] > 0)
                fprintf(file_out,"FstH[%d,%d]: NA\t P-value: NA\t",x,y);
              else
                fprintf(file_out,"FstH[%d,%d]: NA\t P-value: NA\t",x,y);
            }
            /*
            if(stats_Gst[z] > NA_VALUE) {
              if(niter && piter_niterigh[z] > 0)
                fprintf(file_out,"Gst'[%d,%d]: %f\t P-value: %f\t",x,y,stats_Gst[z],(double)piter_igh[z]/(double)piter_niterigh[z]);
              else
                fprintf(file_out,"Gst'[%d,%d]: %f\t P-value: NA\t",x,y,stats_Gst[z]);
            }
            else {
              if(niter && piter_niterigh[z] > 0)
                fprintf(file_out,"Gst'[%d,%d]: NA\t P-value: NA\t",x,y);
              else
                fprintf(file_out,"Gst'[%d,%d]: NA\t P-value: NA\t",x,y);
            }
             */
            fprintf(file_out,"\n");
          }
          z++;
        }
      }

      if(include_unknown->value() == 0) {
        fprintf(file_out,"\nFst corrected with HKY (Hasegawa, Kishino, and Yano. 1985): \n"); /*ANALYSIS using estimator from Hudson, Slatkin and Maddison (Genetics, 1992) */
        if(npops->value() > 2) {
          z=0;
          for(x=0;x<npops->value()-1;x++) {
            for(y=x+1;y<npops->value()-0;y++) {
              if(y==npops->value()-1) {z++;continue;}
              if((*stats_fstHKY)[z] > NA_VALUE) {
                fprintf(file_out,"FstHKY[%d,%d]: %f\tPiWHKY[%d]: %f\tPiWHKY[%d]: %f\tPiAHKY[%d,%d]: %f\tPiTHKY[%d,%d]: %f\t",
                    x,y,(*stats_fstHKY)[z],x,(*stats_piwHKY)[x],y,(*stats_piwHKY)[y],x,y,(*stats_piaHKY)[z],x,y,(*stats_piTHKY)[z]);
              }
              else {
                fprintf(file_out,"FstHKY[%d,%d]: NA\t",x,y);
                if((*stats_piwHKY)[x] > NA_VALUE) {
                  fprintf(file_out,"PiWHKY[%d]: %f\t",x,(*stats_piwHKY)[x]);
                }
                else fprintf(file_out,"PiWHKY[%d]: NA\t",x);
                if((*stats_piwHKY)[y] > NA_VALUE) {
                  fprintf(file_out,"PiWHKY[%d]: %f\t",y,(*stats_piwHKY)[y]);
                }
                else fprintf(file_out,"PiWHKY[%d]: NA\t",y);
                if((*stats_piaHKY)[z] > NA_VALUE) {
                  fprintf(file_out,"PiAHKY[%d,%d]: %f\tPiTHKY[%d,%d]: %f\t",x,y,(*stats_piaHKY)[z],x,y,(*stats_piTHKY)[z]);
                }
                else fprintf(file_out,"PiAHKY[%d,%d]: NA\tPiTHKY[%d,%d]: NA\t",x,y,x,y);
              }
              fprintf(file_out,"\n");
              z++;
            }
          }
        }
      }
    }

    if(include_unknown->value() == 0) {
      fprintf(file_out,"\nNucleotide and haplotype diversity WITHIN populations:\n");
      for(x=0;x<npops->value()-1/*!outgroup_presence*/;x++) {
        if((*vint_perpop_nsam)[x]>1) {
          fprintf(file_out,"PiW[%d]: %f\t",x,(*stats_piw)[x]);
          if(ploidy->value() == HAPLOID && include_unknown->value() == 0) fprintf(file_out,"HapW[%d]: %f\t",x,(*stats_hapw)[x]);
          fprintf(file_out,"\n");
        }
        else {
          fprintf(file_out,"PiW[%d]: NA\t",x);
          if(ploidy->value() == HAPLOID && include_unknown->value() == 0) fprintf(file_out,"HapW[%d]: NA\t",x);
          fprintf(file_out,"\n");
        }
      }
      if(npops->value()-1/*!outgroup_presence*/ > 1) {
        fprintf(file_out,"\nNucleotide and haplotype diversity BETWEEN populations and TOTAL:\n");
        z=0;
        for(x=0;x<npops->value()-1;x++) {
          for(y=x+1;y<npops->value()-0;y++) {
            if(y==npops->value()-1) {z++;continue;}
            if((*stats_piant)[z] > NA_VALUE) {
              fprintf(file_out,"PiA[%d,%d]: %f\tPiA/nt[%d,%d]: %f\tPiT[%d,%d]: %f\tPiT/nt[%d,%d]: %f\t",x,y,(*stats_pia)[z],x,y,(*stats_piant)[z],x,y,(*stats_piT)[z],x,y,(*stats_piTnt)[z]);
            }
            else {
              fprintf(file_out,"PiA[%d,%d]: %f\tPiA/nt[%d,%d]: NA\tPiT[%d,%d]: %f\tPiT/nt[%d,%d]: NA\t",x,y,(*stats_pia)[z],x,y,x,y,(*stats_piT)[z],x,y);
            }
            fprintf(file_out,"\n");
            z++;
          }
        }
        fprintf(file_out,"\n");
        z=0;
        for(x=0;x<npops->value()-2;x++) {
          for(y=x+1;y<npops->value()-1;y++) {
            if(y==npops->value()-1) {z++;continue;}
            if(ploidy->value() == HAPLOID && include_unknown->value() == 0) {
              fprintf(file_out,"HapA[%d,%d]: %f\tHapT[%d,%d]: %f\t",x,y,(*stats_hapa)[z],x,y,(*stats_hapT)[z]);
              fprintf(file_out,"\n");
            }
            z++;
          }
        }
      }
    }
    else {
      fprintf(file_out,"\nNucleotide and haplotype diversity WITHIN populations:\n");
      for(x=0;x<npops->value()-1/*!outgroup_presence*/;x++) {
        if((*vint_perpop_nsam)[x]>1) {
          fprintf(file_out,"PiW[%d]: %f\tPiW/nt[%d]: %f\t",x,(*stats_piw)[x],x,(*stats_thetaT)[x]/(double)length_al->value());
          fprintf(file_out,"\n");
        }
        else {
          fprintf(file_out,"PiW[%d]: NA\tPiW/nt[%d]: NA\t",x,x);
          fprintf(file_out,"\n");
        }
      }
      if(npops->value()-1/*!outgroup_presence*/ > 1) {
        fprintf(file_out,"\nNucleotide and haplotype diversity BETWEEN populations:\n");
        z=0;
        for(x=0;x<npops->value()-1;x++) {
          for(y=x+1;y<npops->value()-0;y++) {
            if(y==npops->value()-1) {z++;continue;}
            if((*stats_piant)[z] > NA_VALUE) {
              fprintf(file_out,"PiA[%d,%d]: %f\tPiA/nt[%d,%d]: %f\tPiT[%d,%d]: %f\tPiT/nt[%d,%d]: %f\t",x,y,(*stats_pia)[z],x,y,(*stats_piant)[z],x,y,(*stats_piT)[z],x,y,(*stats_piTnt)[z]);
            }
            else {
              fprintf(file_out,"PiA[%d,%d]: %f\tPiA/nt[%d,%d]: NA\tPiT[%d,%d]: %f\tPiT/nt[%d,%d]: NA\t",x,y,(*stats_pia)[z],x,y,x,y,(*stats_piT)[z],x,y);
            }
            fprintf(file_out,"\n");
            z++;
          }
        }
        fprintf(file_out,"\n");
        z=0;
        for(x=0;x<npops->value()-2;x++) {
          for(y=x+1;y<npops->value()-1;y++) {
            if(y==npops->value()-1) {z++;continue;}
            if(ploidy->value() == HAPLOID && include_unknown->value() == 0) {
              fprintf(file_out,"HapA[%d,%d]: %f\tHapT[%d,%d]: %f\t",x,y,(*stats_hapa)[z],x,y,(*stats_hapT)[z]);
              fprintf(file_out,"\n");
            }
            z++;
          }
        }
      }
    }

    fprintf(file_out,"\nFrequency of variants for each population:");
    if(npops->value()-!outgroup_presence > 1) {
      for(x=0;x<npops->value()-1/*!outgroup_presence*/;x++) {
        fprintf(file_out,"\n");
        if(outgroup_presence == 1) {
          for(y=1;y<(*vint_perpop_nsam)[x];y++) {
            fprintf(file_out,"fr[%d,%d]: %ld\t",x,y,(*stats_freq)[x][y]);
          }
        }
        else {
          for(y=1;y<=floor((*vint_perpop_nsam)[x]/2);y++) {
            fprintf(file_out,"fr[%d,%d]: %ld\t",x,y,(*stats_freq)[x][y]);
          }
        }
      }
    }
    else {
      fprintf(file_out,"\n");
      for(y=1;y<=floor((*vint_perpop_nsam)[0]/2);y++) {
        fprintf(file_out,"fr[0,%d]: %ld\t",y,(*stats_freq)[0][y]);
      }
    }
    fprintf(file_out,"\n");
    if(ploidy->value() == HAPLOID && include_unknown->value() == 0) {
      fprintf(file_out,"\nFrequency of each haplotype in the populations:");
      for(x=0;x<npops->value()-1/*!outgroup_presence*/;x++) {
        fprintf(file_out,"\n");
        for(y=0;y<stats_nh->value();y++) { ///******* problem!: in case force an outgroup we may have one more haplotype that is not real *********/
          fprintf(file_out,"frH[%d,hap%02d]: %ld\t",x,y,(*stats_freqh)[x][y]);
        }
      }
    }
    fprintf(file_out,"\n\nPositions of each variant (negative indicates it contains any missing 'N' values):");

    if(npops->value()-!outgroup_presence>1) {
      for(x=0;x<npops->value()-1;x++) {
        fprintf(file_out,"\nSx[%d]: ",x);
        y=0;
        zz = (*sites)[y*4*npops->value()+4*x+0];
        while(zz!=0) {
          if(y >= length_seg->value()) break;
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if(formatfile->value() == TFASTA_FILE) {
              if(zz < 0) { fprintf(file_out,"%ld ",zz-(long int)(*vector_priors)[0]+1); }
              else { fprintf(file_out,"%ld ",zz+(long int)(*vector_priors)[0]-1); }
            }
            else { fprintf(file_out,"%ld ",zz); }
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
          y++;
          zz = (*sites)[y*4*npops->value()+4*x+0];
        }
        if(outgroup_presence == 0) {
          y=0;
          zz = (*sites)[y*4*npops->value()+4*x+2];
          while(zz!=0) {
            if(y >= length_seg->value()) break;
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if(formatfile->value() == TFASTA_FILE) {
              if(zz < 0) { fprintf(file_out,"%ld ",zz-(long int)(*vector_priors)[0]+1); }
              else { fprintf(file_out,"%ld ",zz+(long int)(*vector_priors)[0]-1); }
            }
            else { fprintf(file_out,"%ld ",zz); }
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            y++;
            zz = (*sites)[y*4*npops->value()+4*x+2];
          }
        }
        fprintf(file_out,"\nSf[%d]: ",x);
        y=0;
        zz = (*sites)[y*4*npops->value()+4*x+1];
        while(zz!=0) {
          if(y >= length_seg->value()) break;
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if(formatfile->value() == TFASTA_FILE) {
              if(zz < 0) { fprintf(file_out,"%ld ",zz-(long int)(*vector_priors)[0]+1); }
              else { fprintf(file_out,"%ld ",zz+(long int)(*vector_priors)[0]-1); }
            }
            else { fprintf(file_out,"%ld ",zz); }
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
          y++;
          zz = (*sites)[y*4*npops->value()+4*x+1];
        }
        if(outgroup_presence == 1) {
          fprintf(file_out,"\nSxf[%d]: ",x);
          y=0;
          zz = (*sites)[y*4*npops->value()+4*x+2];
          while(zz!=0) {
            if(y >= length_seg->value()) break;
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if(formatfile->value() == TFASTA_FILE) {
              if(zz < 0) { fprintf(file_out,"%ld ",zz-(long int)(*vector_priors)[0]+1); }
              else { fprintf(file_out,"%ld ",zz+(long int)(*vector_priors)[0]-1); }
            }
            else { fprintf(file_out,"%ld ",zz); }
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            y++;
            zz = (*sites)[y*4*npops->value()+4*x+2];
          }
        }
        fprintf(file_out,"\nSs[%d]: ",x);
        y=0;
        zz = (*sites)[y*4*npops->value()+4*x+3];
        while(zz!=0) {
          if(y >= length_seg->value()) break;
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if(formatfile->value() == TFASTA_FILE) {
              if(zz < 0) { fprintf(file_out,"%ld ",zz-(long int)(*vector_priors)[0]+1); }
              else { fprintf(file_out,"%ld ",zz+(long int)(*vector_priors)[0]-1); }
            }
            else { fprintf(file_out,"%ld ",zz); }
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
          y++;
          zz = (*sites)[y*4*npops->value()+4*x+3];
        }
      }
      x = npops->value()-1;
      fprintf(file_out,"\nSs[rest]: ");
      y=0;
      zz = (*sites)[y*4*npops->value()+4*x+3];
      while(zz!=0) {
        if(y >= length_seg->value()) break;
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if(formatfile->value() == TFASTA_FILE) {
              if(zz < 0) { fprintf(file_out,"%ld ",zz-(long int)(*vector_priors)[0]+1); }
              else { fprintf(file_out,"%ld ",zz+(long int)(*vector_priors)[0]-1); }
            }
            else { fprintf(file_out,"%ld ",zz); }
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        y++;
        zz = (*sites)[y*4*npops->value()+4*x+3];
      }
      if(outgroup_presence == 1) {
        x = npops->value()-1;
        fprintf(file_out,"\nSx[outg]: ");
        y=0;
        zz = (*sites)[y*4*npops->value()+4*x+0];
        while(zz!=0) {
          if(y >= length_seg->value()) break;
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if(formatfile->value() == TFASTA_FILE) {
              if(zz < 0) { fprintf(file_out,"%ld ",zz-(long int)(*vector_priors)[0]+1); }
              else { fprintf(file_out,"%ld ",zz+(long int)(*vector_priors)[0]-1); }
            }
            else { fprintf(file_out,"%ld ",zz); }
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
          y++;
          zz = (*sites)[y*4*npops->value()+4*x+0];
        }
        fprintf(file_out,"\nSf[outg]: ");
        y=0;
        zz = (*sites)[y*4*npops->value()+4*x+1];
        while(zz!=0) {
          if(y >= length_seg->value()) break;
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if(formatfile->value() == TFASTA_FILE) {
              if(zz < 0) { fprintf(file_out,"%ld ",zz-(long int)(*vector_priors)[0]+1); }
              else { fprintf(file_out,"%ld ",zz+(long int)(*vector_priors)[0]-1); }
            }
            else { fprintf(file_out,"%ld ",zz); }
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
          y++;
          zz = (*sites)[y*4*npops->value()+4*x+1];
        }
        fprintf(file_out,"\nSf[outg,rest]: ");
        y=0;
        zz = (*sites)[y*4*npops->value()+4*x+2];
        while(zz!=0) {
          if(y >= length_seg->value()) break;
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if(formatfile->value() == TFASTA_FILE) {
              if(zz < 0) { fprintf(file_out,"%ld ",zz-(long int)(*vector_priors)[0]+1); }
              else { fprintf(file_out,"%ld ",zz+(long int)(*vector_priors)[0]-1); }
            }
            else { fprintf(file_out,"%ld ",zz); }
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
          y++;
          zz = (*sites)[y*4*npops->value()+4*x+2];
        }
      }
    }
    else {
      x = 0;
      fprintf(file_out,"\nSx[%d]: ",x);
      y=0;
      zz = (*sites)[y*4*npops->value()+4*x+0];
      while(zz!=0) {
        if(y >= length_seg->value()) break;
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            if(formatfile->value() == TFASTA_FILE) {
              if(zz < 0) { fprintf(file_out,"%ld ",zz-(long int)(*vector_priors)[0]+1); }
              else { fprintf(file_out,"%ld ",zz+(long int)(*vector_priors)[0]-1); }
            }
            else { fprintf(file_out,"%ld ",zz); }
            // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        y++;
        zz = (*sites)[y*4*npops->value()+4*x+0];
      }
    }

    oo = 1;
    fprintf(file_out,"\n\nJoint frequency distribution for each variant and population (No included variants that are missing or polymorphic in the outgroup):");
    fprintf(file_out,"\n");
    for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"\tpop[%d]",x);
    for(zz=0;zz<length_seg->value();zz++) {
      ss=0; for(x=0;x<npops->value()-oo;x++) {ss += (*nfd)[x][zz];}
      if(ss) {
        // ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
        if(formatfile->value() ==3) {
          if((*positions)[zz] < 0) { fprintf(file_out,"\nSNP[%ld]",(*positions)[zz]-(long int)(*vector_priors)[0]+1); }
          else { fprintf(file_out,"\nSNP[%ld]",(*positions)[zz]+(long int)(*vector_priors)[0]-1); }
        }
        else { fprintf(file_out,"\nSNP[%ld]",(*positions)[zz]); }
        // ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
        
        for(x=0;x<npops->value()-oo;x++) {
          fprintf(file_out,"\t%.3f",(*jfd)[x][zz]);
        }
      }
    }
    fprintf(file_out,"\n");
    if(missratio->value() > 0.) {
      fprintf(file_out,"\n\nNumber of samples for each variant and population (No included variants are missing or polymorphic in the outgroup):");
      fprintf(file_out,"\n");
      for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"\tpop[%d]",x);
      for(zz=0;zz<length_seg->value();zz++) {
        ss=0; for(x=0;x<npops->value()-oo;x++) {ss += (*nfd)[x][zz];}
        if(ss) {
        // ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
        if(formatfile->value() ==3) {
          if((*positions)[zz] < 0) { fprintf(file_out,"\nSNP[%ld]",(*positions)[zz]-(long int)(*vector_priors)[0]+1); }
          else { fprintf(file_out,"\nSNP[%ld]",(*positions)[zz]+(long int)(*vector_priors)[0]-1); }
        }
        else { fprintf(file_out,"\nSNP[%ld]",(*positions)[zz]); }
        // ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
        
        for(x=0;x<npops->value()-oo;x++) {
            fprintf(file_out,"\t%d",(*nfd)[x][zz]);
          }
        }
      }
    }
    fprintf(file_out,"\n");
    if(include_unknown->value() == 0) {
      if(ploidy->value() == HAPLOID) {
        fprintf(file_out,"\n\nFrequency of variants for each line and population:");
        if(outgroup_presence==0) {
          for(x=0;x<npops->value()-oo;x++) {
            if((*vint_perpop_nsam)[x] > 1) {
              fprintf(file_out,"\nPop[%d]\n\t",x);
              for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) fprintf(file_out,"line[%d]\t",ss-initsq1[x]);
              fprintf(file_out,"\n");
              for(z1=1;z1<=(long int)floor((*vint_perpop_nsam)[x]/2);z1++) {
                fprintf(file_out,"freq[%d]:\t",z1);
                for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                  fprintf(file_out,"%ld\t",(long int)(*stats_linefreq)[ss][z1]);
                }
                fprintf(file_out,"\n");
              }
            }
          }
        }
        else {
          for(x=0;x<npops->value()-oo;x++) {
            if((*vint_perpop_nsam)[x] > 1) {
              fprintf(file_out,"\nPop[%d]\n\t",x);
              for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) fprintf(file_out,"line[%d]\t",ss-initsq1[x]);
              fprintf(file_out,"\n");
              for(z1=1;z1<(*vint_perpop_nsam)[x];z1++) {
                fprintf(file_out,"freq[%d]:\t",z1);
                for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                  fprintf(file_out,"%ld\t",(long int)(*stats_linefreq)[ss][z1]);
                }
                fprintf(file_out,"\n");
              }
            }
          }
        }
      }
    }

    if((*output) == 10) {
      if(npops->value()-!outgroup_presence==1) oo = 0;
      else oo = 1;
      /*header*/
      fprintf(file_out,"\n#dadi format for joint frequency spectrum.\n");
      /*fprintf(file_out,"#Note: All alleles are defined arbitrarily to A and T.\n");*/
      fprintf(file_out,"Ref_int\tRef_out\tAllele1\t");
      for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"Pop_%03d\t",x);
      fprintf(file_out,"Allele2\t");
      for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"Pop_%03d\t",x);
      fprintf(file_out,"Position");
      fprintf(file_out, "\n");
      /*table*/
      for(zz=0;zz<length_seg->value();zz++) {
        ss=0; sf = 0.0; for(x=0;x<npops->value()-oo;x++) {ss += (*nfd)[x][zz]; sf += (*jfd)[x][zz];}
        if(ss && sf > 0.0 && sf < 1.0) {
					/*Define nucleotide*/
                    for(y=0;y<sumnsam;y++) {
                        if((*matrix_pol)[zz*sumnsam+y] == '0') {
                            if((*matrix_pol_tcga)[zz*sumnsam+y] == '1')
                                nt1[0] = 'T';
                            if((*matrix_pol_tcga)[zz*sumnsam+y] == '2')
                                nt1[0] = 'C';
                            if((*matrix_pol_tcga)[zz*sumnsam+y] == '3')
                                nt1[0] = 'G';
                            if((*matrix_pol_tcga)[zz*sumnsam+y] == '4')
                                nt1[0] = 'A';
                            break;
                        }
                    }
                    for(y=0;y<sumnsam;y++) {
                        if((*matrix_pol)[zz*sumnsam+y] == '1') {
                            if((*matrix_pol_tcga)[zz*sumnsam+y] == '1')
                                nt2[0] = 'T';
                            if((*matrix_pol_tcga)[zz*sumnsam+y] == '2')
                                nt2[0] = 'C';
                            if((*matrix_pol_tcga)[zz*sumnsam+y] == '3')
                                nt2[0] = 'G';
                            if((*matrix_pol_tcga)[zz*sumnsam+y] == '4')
                                nt2[0] = 'A';
                            break;
                        }
                    }
					fprintf(file_out, "-%c-\t",nt1[0]);
					if(outgroup_presence) fprintf(file_out, "-%c-\t",nt2[0]);
					else fprintf(file_out, "---\t");
					/*Allele1*/
					fprintf(file_out, "%c\t",nt1[0]);
					for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"%.0f\t",((*jfd)[x][zz])*(*nfd)[x][zz]);
					/*Allele2*/
					fprintf(file_out, "%c\t",nt2[0]);
					for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"%.0f\t",(1.0-(*jfd)[x][zz])*(*nfd)[x][zz]);
					/*position*/
					if(formatfile->value()==3) { fprintf(file_out,"%ld",labs((*positions)[zz])+(long int)(*vector_priors)[0]-1); }
          else { fprintf(file_out,"%ld",labs((*positions)[zz])); }
					fprintf(file_out,"\n");
        }
      }
      /*fprintf(file_out,"\n");*/

      fprintf(file_out,"\n\nAll pairwise comparisons (mismatch distribution) per population:");
      for(x=0;x<npops->value()-oo;x++) {
        fprintf(file_out,"\npop[%d:%ld combinations]:",x,(long int)((*vint_perpop_nsam)[x])*((*vint_perpop_nsam)[x]-1)/2);
        for(zz=0;zz<(*vint_perpop_nsam)[x]*((*vint_perpop_nsam)[x]-1)/2;zz++) {
          if(ploidy->value() == HAPLOID) {fprintf(file_out,"\t%.2f",(*stats_mdw)[x][zz]);}
          if(ploidy->value() == DIPLOID) {fprintf(file_out,"\tNA");}
        }
      }
      if(ploidy->value() == HAPLOID) {
        fprintf(file_out,"\n\nFrequency of SNPs of each line :");
        if(outgroup_presence==0) {
          for(x=0;x<npops->value()-oo;x++) {
            fprintf(file_out,"\n\npop[%d]",x);
            for(ss=1;ss<=(int)floor((*vint_perpop_nsam)[x]/2);ss++) fprintf(file_out,"\tfreq[%d]",ss);
            for(z=initsq1[x];z<initsq1[x]+(*vint_perpop_nsam)[x];z++) {
              fprintf(file_out,"\nline[%d]:",z);
              for(ss=1;ss<=(long int)floor((*vint_perpop_nsam)[x]/2);ss++) {
                fprintf(file_out,"\t%.3f",(*stats_linefreq)[z][ss]);
              }
            }
          }
        }
        else {
          for(x=0;x<npops->value()-oo;x++) {
            fprintf(file_out,"\n\npop[%d]",x);
            for(ss=1;ss<(*vint_perpop_nsam)[x];ss++) fprintf(file_out,"\tfreq[%d]",ss);
            for(z=initsq1[x];z<initsq1[x]+(*vint_perpop_nsam)[x];z++) {
              fprintf(file_out,"\nline[%d]:",z);
              for(ss=1;ss<(*vint_perpop_nsam)[x];ss++) {
                fprintf(file_out,"\t%.3f",(*stats_linefreq)[z][ss]);
              }
            }
          }
        }
        /*
        fprintf(file_out,"\n\nCovariance matrix of SNPs frequency per line based on SNM:");
        if(outgroup_presence==0) {
          for(x=0;x<npops->value()-oo;x++) {
            fprintf(file_out,"\n\npop[%d]:",x);
            for(ss=1;ss<=(long int)floor((*vint_perpop_nsam)[x]/2);ss++) fprintf(file_out,"\tfreq[%d]",ss);
            for(z1=1;z1<=(long int)floor((*vint_perpop_nsam)[x]/2);z1++) {
              fprintf(file_out,"\nfreq[%d]",z1);
              for(z2=1;z2<=(long int)floor((*vint_perpop_nsam)[x]/2);z2++) {
                cv = 0.;
                for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                  mean_z1 = mean_z2 = stats_thetaS[x]/(*vint_perpop_nsam)[x];
                  if(!((float)z1 == floor((*vint_perpop_nsam)[x]/2) && (float)z1 == (float)(*vint_perpop_nsam)[x]/2.))
                    mean_z1 *= 2.;
                  if(!((float)z2 == floor((*vint_perpop_nsam)[x]/2) && (float)z2 == (float)(*vint_perpop_nsam)[x]/2.))
                    mean_z2 *= 2.;

                  cv += ((*stats_linefreq)[ss][z1] - mean_z1) *
                      ((*stats_linefreq)[ss][z2] - mean_z2);
                }
                fprintf(file_out,"\t%.3f",cv/(*vint_perpop_nsam)[x]);
              }
            }
          }
        }
        else {
          for(x=0;x<npops->value()-oo;x++) {
            fprintf(file_out,"\n\npop[%d]:",x);
            for(ss=1;ss<(*vint_perpop_nsam)[x];ss++) fprintf(file_out,"\tfreq[%d]",ss);
            for(z1=1;z1<(*vint_perpop_nsam)[x];z1++) {
              fprintf(file_out,"\nfreq[%d]",z1);
              for(z2=1;z2<(*vint_perpop_nsam)[x];z2++) {
                cv = 0.;
                for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                  cv += ((*stats_linefreq)[ss][z1] - (stats_thetaS[x]/(*vint_perpop_nsam)[x])) *
                      ((*stats_linefreq)[ss][z2] - (stats_thetaS[x]/(*vint_perpop_nsam)[x]));
                }
                fprintf(file_out,"\t%.3f",cv/(*vint_perpop_nsam)[x]);
              }
            }
          }
        }
        fprintf(file_out,"\n\nCovariance matrix of SNPs frequency per line based on empirical data:");
        if(outgroup_presence==0) {
          for(x=0;x<npops->value()-oo;x++) {
            fprintf(file_out,"\n\npop[%d]:",x);
            for(ss=1;ss<=(long int)floor((*vint_perpop_nsam)[x]/2);ss++) fprintf(file_out,"\tfreq[%d]",ss);
            for(z1=1;z1<=(long int)floor((*vint_perpop_nsam)[x]/2);z1++) {
              fprintf(file_out,"\nfreq[%d]",z1);
              for(z2=1;z2<=(long int)floor((*vint_perpop_nsam)[x]/2);z2++) {
                cv = 0.;
                for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                  mean_z1 = stats_freq[x][z1] * z1/(*vint_perpop_nsam)[x];
                  if(!((float)z1 == floor((*vint_perpop_nsam)[x]/2) && (float)z1 == (float)(*vint_perpop_nsam)[x]/2.))
                    mean_z1 += stats_freq[x][z1] * z1/(*vint_perpop_nsam)[x];
                  mean_z2 = stats_freq[x][z2] * z2/(*vint_perpop_nsam)[x];
                  if(!((float)z2 == floor((*vint_perpop_nsam)[x]/2) && (float)z2 == (float)(*vint_perpop_nsam)[x]/2.))
                    mean_z2 += stats_freq[x][z2] * z2/(*vint_perpop_nsam)[x];

                  cv += ((*stats_linefreq)[ss][z1] - mean_z1) *
                      ((*stats_linefreq)[ss][z2] - mean_z2);
                }
                fprintf(file_out,"\t%.3f",cv/(*vint_perpop_nsam)[x]);
              }
            }
          }
        }
        else {
          for(x=0;x<npops->value()-oo;x++) {
            fprintf(file_out,"\n\npop[%d]:",x);
            for(ss=1;ss<(*vint_perpop_nsam)[x];ss++) fprintf(file_out,"\tfreq[%d]",ss);
            for(z1=1;z1<(*vint_perpop_nsam)[x];z1++) {
              fprintf(file_out,"\nfreq[%d]",z1);
              for(z2=1;z2<(*vint_perpop_nsam)[x];z2++) {
                cv = 0.;
                for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                  cv += ((*stats_linefreq)[ss][z1] - (stats_freq[x][z1] * z1/(*vint_perpop_nsam)[x])) *
                      ((*stats_linefreq)[ss][z2] - (stats_freq[x][z2] * z2/(*vint_perpop_nsam)[x]));
                }
                fprintf(file_out,"\t%.3f",cv/(*vint_perpop_nsam)[x]);
              }
            }
          }
        }
        */
      }
    }
    fprintf(file_out,"\n");
    /*
    if (file_output->value().c_str()[0])
      fprintf(file_out,"\nResults sent to file %s\nProgram finished succesfully.\n",file_output->value().c_str());
    */fflush(file_out);
  }
  else { /*single stdout line*/
		if((*output) == 6) {
			/*Matrix SNPs*/
			fprintf(file_out,"#Run: %ld",niterdata);
			fprintf(file_out,"\n#SNP chr");
			for(x=0;x<npops->value()-!outgroup_presence;x++) { for(y=0;y<(*vint_perpop_nsam)[x];y++) { fprintf(file_out," ind%03d%03d",x,y);}}
			fprintf(file_out,"\n");
            if(force_outgroup->value()==1 || outgroup_presence == 0) oo = 1; else oo = 0;
			/*table*/
			for(zz=0;zz<length_seg->value();zz++) {
				//ancestral[0] = 0;  //!removed because it is not used
				if((*positions)[zz]<=0) fabsmatsize = -(*positions)[zz];
				else fabsmatsize = (*positions)[zz];
				fprintf(file_out,"%-9ld %-9c",fabsmatsize,'0');
				
				/*calculate the ancestral sequence if outgroup*/
				/*
                if(outgroup_presence+force_outgroup->value()==1) {
					freqo[0]=freqo[1]=freqo[2]=freqo[3]=0;
					for(y=sumnsam-nsam[npops-1];y<sumnsam;y++) {
                        if((*matrix_pol)[zz*sumnsam+y] == '0') {
                            freqo[1] += 1;freqo[0] += 1;
                        }
						if((*matrix_pol)[zz*sumnsam+y] == '1') {
                            freqo[2] += 1;freqo[0] += 1;
                        }
						if((*matrix_pol)[zz*sumnsam+y] == '-') {
                            freqo[3] += 1;}
					}
					if(freqo[0]) {
						if(freqo[1] != freqo[0] && freqo[1] != 0) {
							ancestral[0] = (char)0;
						}
						else {
							if(freqo[1] == freqo[0]) {
								ancestral[0] = '0';
							}
							if(freqo[2] == freqo[0]) {
								ancestral[0] = '1';
							}	
						}
					}
					else ancestral[0] = (char)0;
				}
                */
				/*print genotype, including the outgroup if exist*/
				for(y=0;y<sumnsam/*-oo*/;y++) {
                    if((*matrix_pol)[zz*sumnsam+y] == '0') {
                        if((*matrix_pol_tcga)[zz*sumnsam+y] == '1')
                            nt1[0] = 'T';
                        if((*matrix_pol_tcga)[zz*sumnsam+y] == '2')
                            nt1[0] = 'C';
                        if((*matrix_pol_tcga)[zz*sumnsam+y] == '3')
                            nt1[0] = 'G';
                        if((*matrix_pol_tcga)[zz*sumnsam+y] == '4')
                            nt1[0] = 'A';
                    }
                    if((*matrix_pol)[zz*sumnsam+y] == '1') {
                        if((*matrix_pol_tcga)[zz*sumnsam+y] == '1')
                            nt2[0] = 'T';
                        if((*matrix_pol_tcga)[zz*sumnsam+y] == '2')
                            nt2[0] = 'C';
                        if((*matrix_pol_tcga)[zz*sumnsam+y] == '3')
                            nt2[0] = 'G';
                        if((*matrix_pol_tcga)[zz*sumnsam+y] == '4')
                            nt2[0] = 'A';
                    }
					if((*matrix_pol)[zz*sumnsam+y] == '0') fprintf(file_out," %c",nt1[0]);
                    if((*matrix_pol)[zz*sumnsam+y] == '1') fprintf(file_out," %c",nt2[0]);
                    if((*matrix_pol)[zz*sumnsam+y] == '-') fprintf(file_out," N");
                    /*
                    if(ancestral[0] == (*matrix_pol)[zz*sumnsam+y]) fprintf(file_out," 0");
					else {
						if((*matrix_pol)[zz*sumnsam+y] == '-') fprintf(file_out," 9");
						else {
							if(ancestral[0] == 0) fprintf(file_out," %c",(*matrix_pol)[zz*sumnsam+y]);
							else {
								if(ancestral[0] != (*matrix_pol)[zz*sumnsam+y]) fprintf(file_out," 1");
							}
						}
					}
                    */
				}
				fprintf(file_out,"\n");
			}
			/**/
    }
    else {
      if((*output) == 3) {
        if(npops->value()-!outgroup_presence==1) oo = 0;
        else oo = 1;
        /*header*/
        fprintf(file_out,"#mstatspop output for dadi format of joint frequency spectrum.\n");
        fprintf(file_out,"#Input file: %s\n",file_input->value().c_str());
        fprintf(file_out,"#Note: All alleles are defined arbitrarily to A and T.\n");
        fprintf(file_out,"Ref_int\tRef_out\tAllele1\t");
        for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"Pop_%03d\t",x);
        fprintf(file_out,"Allele2\t");
        for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"Pop_%03d\t",x);
        fprintf(file_out,"Position\t");
        if(*(file_input->value().c_str())) fprintf(file_out,"Location");
        /*table*/
        for(zz=0;zz<length_seg->value();zz++) {
          ss=0; sf = 0.0; for(x=0;x<npops->value()-oo;x++) {ss += (*nfd)[x][zz]; sf += (*jfd)[x][zz];}
          if(ss && sf > 0.0 && sf < 1.0*(npops->value()-oo)) {
            fprintf(file_out,"\n");
            /*Define nucleotide*/
                        for(y=0;y<sumnsam;y++) {
                            if((*matrix_pol)[zz*sumnsam+y] == '0') {
                                if((*matrix_pol_tcga)[zz*sumnsam+y] == '1')
                                    nt1[0] = 'T';
                                if((*matrix_pol_tcga)[zz*sumnsam+y] == '2')
                                    nt1[0] = 'C';
                                if((*matrix_pol_tcga)[zz*sumnsam+y] == '3')
                                    nt1[0] = 'G';
                                if((*matrix_pol_tcga)[zz*sumnsam+y] == '4')
                                    nt1[0] = 'A';
                                break;
                            }
                        }
                        for(y=0;y<sumnsam;y++) {
                            if((*matrix_pol)[zz*sumnsam+y] == '1') {
                                if((*matrix_pol_tcga)[zz*sumnsam+y] == '1')
                                    nt2[0] = 'T';
                                if((*matrix_pol_tcga)[zz*sumnsam+y] == '2')
                                    nt2[0] = 'C';
                                if((*matrix_pol_tcga)[zz*sumnsam+y] == '3')
                                    nt2[0] = 'G';
                                if((*matrix_pol_tcga)[zz*sumnsam+y] == '4')
                                    nt2[0] = 'A';
                                break;
                            }
                        }
                        fprintf(file_out, "-%c-\t",nt1[0]);
                        if(outgroup_presence) fprintf(file_out, "-%c-\t",nt2[0]);
                        else fprintf(file_out, "---\t");
                        /*Allele1*/
                        fprintf(file_out, "%c\t",nt1[0]);
                        for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"%.0f\t",((*jfd)[x][zz])*(*nfd)[x][zz]);
                        /*Allele2*/
                        fprintf(file_out, "%c\t",nt2[0]);
                        for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"%.0f\t",(1.0-(*jfd)[x][zz])*(*nfd)[x][zz]);
                        /*position*/
                        fprintf(file_out,"%ld",labs((*positions)[zz]));
                        if(file_input->value() != "") fprintf(file_out,"%s",file_input->value().c_str());
					}
				}
  
				fprintf(file_out,"\n");
      }
      else {
        if(file_out == 0) file_out = stdout;
        if(file_input->value() != "")
          fprintf(file_out,"infile:\t%s\t",file_input->value().c_str());
        else
          fprintf(file_out,"infile:\tNA\t");
        if(gfffiles->value() == 1) {
          fprintf(file_out,"GFFfile:\t%s\t",file_GFF->value().c_str());
          fprintf(file_out,"subset_pos:\t%s\t",(*subset_positions).GetDataString(false));
          if(strcmp(subset_positions->GetDataString(false),"synonymous")==0 || strcmp(subset_positions->GetDataString(false),"nonsynonymous")==0 || strcmp(subset_positions->GetDataString(false),"silent")==0)
            fprintf(file_out,"genetic_code:\t%s\t",(*code_name).GetDataString(false));
        }
        /**/
        if(npriors->value()) {
                 if(formatfile->value() != TFASTA_FILE) {
                        for(x=0;x<npriors->value();x++) {
                            fprintf(file_out,"prior%02d:\t%f\t",x,(*vector_priors)[x]);
                        }
                    }
                    if(formatfile->value() == TFASTA_FILE) {
                        fprintf(file_out,"start_window:\t%f\t",(*vector_priors)[0]);
                        fprintf(file_out,"end_window:\t%f\t",(*vector_priors)[1]);
                    }
        }
        /**/
        if(H1frq->value()) {
          fprintf(file_out,"H1file:\t%s\t",file_H1f->value().c_str());
          if(H0frq->value()) {
            fprintf(file_out,"H0file:\t%sºt",file_H0f->value().c_str());  //!BUG ºt instead of \t
          }
        }
				fprintf(file_out,"missing:\t%d\t",include_unknown->value());
				fprintf(file_out,"iteration:\t%ld\t",niterdata);
				fprintf(file_out,"npermutations:\t%ld\t",niter->value());
				if(formatfile->value()==FASTA_FILE || formatfile->value()==TFASTA_FILE) fprintf(file_out,"seed:\t%ld\t",nseed->value());
				else fprintf(file_out,"seed:\tna\t");
				if(formatfile->value()==FASTA_FILE || formatfile->value()==TFASTA_FILE) fprintf(file_out,"Length:\t%.2f\t",length_al->value());
				else fprintf(file_out,"Length:\t%.2f\t",length_al->value());
				fprintf(file_out,"Lengtht:\t%ld\t",length_al_real->value());
				fprintf(file_out,"mh:\t%ld\t",stats_nmhits->value());
				if(svratio->value() > NA_VALUE) fprintf(file_out,"Ratio_S/V:\t%.3f\t",svratio->value());
				else fprintf(file_out,"Ratio_S/V:\tNA\t");
				if(include_unknown->value() == 1) fprintf(file_out,"Ratio_Missing:\t%f\t",missratio->value());
        else fprintf(file_out,"Ratio_Missing:\tNA\t");
				fprintf(file_out,"Variants:\t%ld\t",length_seg->value());
				
				fprintf(file_out,"npops:\t%ld\t",npops->value()-!outgroup_presence);     //!replaced %d by %ld
				for(x=0;x<npops->value()-!outgroup_presence;x++) {
					fprintf(file_out,"nsam[%d]:\t%d\t",x,(*vint_perpop_nsam)[x]);
				}
				for(x=0;x<npops->value()-1;x++) {
                    /*if(outgroup_presence==1) {fprintf(file_out,"Eff_length1_pop[%d]:\t%.2f\tEff_length2_pop[%d]:\t%.2f\tEff_length3_pop[%d]:\t%.2f\tEff_length1_pop_outg[%d]:\t%.2f\tEff_length2_pop_outg[%d]:\t%.2f\tEff_length3_pop_outg[%d]:\t%.2f\t",x,(double)nsites1_pop[x],x,(double)nsites2_pop[x],x,(double)nsites3_pop[x],x,(double)nsites1_pop_outg[x],x,(double)nsites2_pop_outg[x],x,(double)nsites3_pop_outg[x]);}*/
                    if(outgroup_presence==1) {fprintf(file_out,"Eff_length1_pop_outg[%d]:\t%.2f\tEff_length2_pop_outg[%d]:\t%.2f\tEff_length3_pop_outg[%d]:\t%.2f\t",x,(double)(*nsites1_pop_outg)[x],x,(double)(*nsites2_pop_outg)[x],x,(double)(*nsites3_pop_outg)[x]);}
					if(outgroup_presence==0) {fprintf(file_out,"Eff_length1_pop[%d]:\t%.2f\tEff_length2_pop[%d]:\t%.2f\tEff_length3_pop[%d]:\t%.2f\tEff_length1_pop_outg[%d]:\tNA\tEff_length2_pop_outg[%d]:\tNA\tEff_length3_pop_outg[%d]:\tNA\t",x,(double)(*nsites1_pop)[x],x,(double)(*nsites2_pop)[x],x,(double)(*nsites3_pop)[x],x,x,x);}
				}
				oo = 1;

        if((*output) == 11) {
          if(ploidy->value() == HAPLOID) {
            if(outgroup_presence==0) {
              for(x=0;x<npops->value()-oo;x++) {
                fprintf(file_out,"Cov_Star_pop[%d]:\t",x);
                for(z1=1;z1<=(long int)floor((*vint_perpop_nsam)[x]/2);z1++) {
                  for(z2=1;z2<=(long int)floor((*vint_perpop_nsam)[x]/2);z2++) {
                    cv = 0.;
                    for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                      mean_z1 = mean_z2 = 0.;
                      if(z1 == 1) mean_z1 = (*stats_thetaT)[x]/2.;
                      if(z2 == 1) mean_z2 = (*stats_thetaT)[x]/2.;

                      cv += ((*stats_linefreq)[ss][z1] - mean_z1) *
                      ((*stats_linefreq)[ss][z2] - mean_z2);
                    }
                    cv = cv/(double)(*vint_perpop_nsam)[x];
    #if DENCOV_CORRECTION == 1
                    if(stats_freq[x][z2] * stats_freq[x][z1] > 0.) {
                      if(z1==z2) delta =1.;
                      else delta=0.;
                      cv = cv - delta * (double)z1/(double)(*vint_perpop_nsam)[x] * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1];
                      if((der = (stats_freq[x][z1]*(stats_freq[x][z2]-delta))) != 0.)
                        cv = cv/der;
                    }
                    else cv = 0.;
    #endif
                    fprintf(file_out,"%.6f\t",cv);
                  }
                }
              }
            }
            else {
              for(x=0;x<npops->value()-oo;x++) {
                fprintf(file_out,"Cov_Star_pop[%d]:\t",x);
                for(z1=1;z1<(*vint_perpop_nsam)[x];z1++) {
                  for(z2=1;z2<(*vint_perpop_nsam)[x];z2++) {
                    cv = 0.;
                    for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                      mean_z1 = mean_z2 = 0.;
                      if(z1 == 1) mean_z1 = (*stats_thetaT)[x]/2.;
                      if(z2 == 1) mean_z2 = (*stats_thetaT)[x]/2.;
                      cv += ((*stats_linefreq)[ss][z1] - mean_z1) *
                      ((*stats_linefreq)[ss][z2] - mean_z2);
                    }
                    cv = cv/(double)(*vint_perpop_nsam)[x];
    #if DENCOV_CORRECTION == 1
                    if(stats_freq[x][z2] * stats_freq[x][z1] > 0.) {
                      if((der = (stats_freq[x][z1]*stats_freq[x][z2]))!=0.)
                        cv = cv/der;
                    }
                    else cv = 0.;
    #endif
                    fprintf(file_out,"%.6f\t",cv);
                  }
                }
              }
            }
            fprintf(file_out,"\n");
          }
        }
        if((*output) == 9) {
          if(ploidy->value() == HAPLOID) {
            if(outgroup_presence==0) {
              for(x=0;x<npops->value()-oo;x++) {
                fprintf(file_out,"linefreq_pop[%d]:\t",x);
                for(z1=1;z1<=(long int)floor((*vint_perpop_nsam)[x]/2);z1++) {
                  for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                    fprintf(file_out,"%ld\t",(long int)(*stats_linefreq)[ss][z1]);
                  }
                }
              }
            }
            else {
              for(x=0;x<npops->value()-oo;x++) {
                fprintf(file_out,"linefreq_pop[%d]:\t",x);
                for(z1=1;z1<(*vint_perpop_nsam)[x];z1++) {
                  for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                    fprintf(file_out,"%ld\t",(long int)(*stats_linefreq)[ss][z1]);
                  }
                }
              }
            }
            fprintf(file_out,"\n");
          }
        }
        if((*output) == 8) {
          if(ploidy->value() == HAPLOID && include_unknown->value() == 0) {
            for(y=0;y<stats_nh->value()-!outgroup_presence;y++) {
              for(x=0;x<npops->value()-1;x++) {
                fprintf(file_out,"frHap[%d,hap%02d]:\t%ld\t",x,y,(*stats_freqh)[x][y]);
              }
            }
            for(y=stats_nh->value()-!outgroup_presence;y<sumnsam;y++) {
              for(x=0;x<npops->value()-1;x++) {
                fprintf(file_out,"frHap[%d,hap%02d]:\t0\t",x,y);
              }
            }
          }
          fprintf(file_out,"\n");
        }
        if((*output) == 70) {
          if(ploidy->value() == HAPLOID) {
            if(outgroup_presence==0) {
              for(x=0;x<npops->value()-oo;x++) {
                #if MATRIXCOV == 1
                fprintf(file_out,"Cov_EMP_pop[%d]:\t",x);
                for(z1=1;z1<=(long int)floor((*vint_perpop_nsam)[x]/2);z1++) {
                  for(z2=1;z2<=(long int)floor((*vint_perpop_nsam)[x]/2);z2++) {
                    cv = 0.;
                    for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                      mean_z1 = stats_freq[x][z1] * (float)z1/(float)(*vint_perpop_nsam)[x];
                      if(!((float)z1 == floor((*vint_perpop_nsam)[x]/2) && (float)z1 == (float)(*vint_perpop_nsam)[x]/2.))
                        mean_z1 += stats_freq[x][z1] * (float)z1/(float)(*vint_perpop_nsam)[x];
                      mean_z2 = stats_freq[x][z2] * (float)z2/(float)(*vint_perpop_nsam)[x];
                      if(!((float)z2 == floor((*vint_perpop_nsam)[x]/2) && (float)z2 == (float)(*vint_perpop_nsam)[x]/2.))
                        mean_z2 += stats_freq[x][z2] * (float)z2/(float)(*vint_perpop_nsam)[x];

                      cv += ((*stats_linefreq)[ss][z1] - mean_z1) *
                          ((*stats_linefreq)[ss][z2] - mean_z2);
                    }
                    cv = cv/(double)(*vint_perpop_nsam)[x];
                    #if DENCOV_CORRECTION == 1
                    if(stats_freq[x][z2] * stats_freq[x][z1] > 0.) {
                      if(z1==z2) delta =1.;
                      else delta=0.;
                      cv = cv - delta * (double)z1/(double)(*vint_perpop_nsam)[x] * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1];
                      if((der = (stats_freq[x][z1]*(stats_freq[x][z2]-delta))) != 0.)
                      cv = cv/der;
                    }
                    else cv = 0.;
                    #endif
                    fprintf(file_out,"%.6f\t",cv);
                  }
                }
                #endif
                #if LUCA_CRs == 1
                /*LUCA: here I calculate the statistics for folded tests with different weights 1/i^2,1/i,1,i*/
                luca_cvo2=0.; luca_cvo1=0.; luca_cv0=0.; luca_cv1=0.;
                luca_dero2=0.; luca_dero1=0.; luca_der0=0.; luca_der1=0.;
                luca_cvo2d=0.; luca_cvo1d=0.; luca_cv0d=0.; luca_cv1d=0.;
                luca_dero2d=0.; luca_dero1d=0.; luca_der0d=0.; luca_der1d=0.;
                for(z1=1;z1<=(long int)floor((*vint_perpop_nsam)[x]/2);z1++) {
                  for(z2=1;z2<=(long int)floor((*vint_perpop_nsam)[x]/2);z2++) {
                    for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                      mean_z1 = stats_freq[x][z1] * (float)z1/(float)(*vint_perpop_nsam)[x];
                      if(!((float)z1 == floor((*vint_perpop_nsam)[x]/2) && (float)z1 == (float)(*vint_perpop_nsam)[x]/2.))
                        mean_z1 += stats_freq[x][z1] * (float)z1/(float)(*vint_perpop_nsam)[x];
                      mean_z2 = stats_freq[x][z2] * (float)z2/(float)(*vint_perpop_nsam)[x];
                      if(!((float)z2 == floor((*vint_perpop_nsam)[x]/2) && (float)z2 == (float)(*vint_perpop_nsam)[x]/2.))
                        mean_z2 += stats_freq[x][z2] * (float)z2/(float)(*vint_perpop_nsam)[x];
                      if(z1==z2) delta =1.;
                      else delta=0.;

                      luca_cvo2 += 1/(double)(z1*z1*z2*z2) * (((*stats_linefreq)[ss][z1] - mean_z1) *
                          ((*stats_linefreq)[ss][z2] - mean_z2)
                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                      luca_cvo1 += 1/(double)(z1*z2) * (((*stats_linefreq)[ss][z1] - mean_z1) *
                          ((*stats_linefreq)[ss][z2] - mean_z2)
                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                      luca_cv0 += (((*stats_linefreq)[ss][z1] - mean_z1) *
                          ((*stats_linefreq)[ss][z2] - mean_z2)
                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                      luca_cv1 += (double)(z1*z2) * (((*stats_linefreq)[ss][z1] - mean_z1) *
                          ((*stats_linefreq)[ss][z2] - mean_z2)
                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                      luca_dero2 += 1/(double)(z1*z1*z2*z2) * (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                      luca_dero1 += 1/(double)(z1*z2) * (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                      luca_der0 += (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                      luca_der1 += (double)(z1*z2) * (stats_freq[x][z1]*(stats_freq[x][z2]-delta));

                      if(z1==z2) {
                        luca_cvo2d += 1/(double)(z1*z1*z2*z2) * (((*stats_linefreq)[ss][z1] - mean_z1) *
                                            ((*stats_linefreq)[ss][z2] - mean_z2)
                                            - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                        luca_cvo1d += 1/(double)(z1*z2) * (((*stats_linefreq)[ss][z1] - mean_z1) *
                                          ((*stats_linefreq)[ss][z2] - mean_z2)
                                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                        luca_cv0d += (((*stats_linefreq)[ss][z1] - mean_z1) *
                               ((*stats_linefreq)[ss][z2] - mean_z2)
                               - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                        luca_cv1d += (double)(z1*z2) * (((*stats_linefreq)[ss][z1] - mean_z1) *
                                         ((*stats_linefreq)[ss][z2] - mean_z2)
                                         - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                        luca_dero2d += 1/(double)(z1*z1*z2*z2) * (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                        luca_dero1d += 1/(double)(z1*z2) * (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                        luca_der0d += (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                        luca_der1d += (double)(z1*z2) * (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                      }
                    }
                  }
                }

                luca_cvo2 = luca_cvo2/luca_dero2/(double)(*vint_perpop_nsam)[x];
                luca_cvo1 = luca_cvo1/luca_dero1/(double)(*vint_perpop_nsam)[x];
                luca_cv0 = luca_cv0/luca_der0/(double)(*vint_perpop_nsam)[x];
                luca_cv1 = luca_cv1/luca_der1/(double)(*vint_perpop_nsam)[x];

                luca_cvo2d = luca_cvo2d/luca_dero2d/(double)(*vint_perpop_nsam)[x];
                luca_cvo1d = luca_cvo1d/luca_dero1d/(double)(*vint_perpop_nsam)[x];
                luca_cv0d = luca_cv0d/luca_der0d/(double)(*vint_perpop_nsam)[x];
                luca_cv1d = luca_cv1d/luca_der1d/(double)(*vint_perpop_nsam)[x];

                fprintf(file_out,"CVO2[%d]:\t%.6f\t",x,luca_cvo2);
                fprintf(file_out,"CVO1[%d]:\t%.6f\t",x,luca_cvo1);
                fprintf(file_out,"CV0[%d]:\t%.6f\t",x,luca_cv0);
                fprintf(file_out,"CV1[%d]:\t%.6f\t",x,luca_cv1);
                fprintf(file_out,"CVO2d[%d]:\t%.6f\t",x,luca_cvo2d);
                fprintf(file_out,"CVO1d[%d]:\t%.6f\t",x,luca_cvo1d);
                fprintf(file_out,"CV0d[%d]:\t%.6f\t",x,luca_cv0d);
                fprintf(file_out,"CV1d[%d]:\t%.6f\t",x,luca_cv1d);
                fprintf(file_out,"R2[%d]:\t%.6f\t",x,stats_R2[x]);
                /*end LUCA*/
                #endif
              }
            }
            else {
              for(x=0;x<npops->value()-oo;x++) {
                #if MATRIXCOV == 1
                fprintf(file_out,"Cov_EMP_pop[%d]:\t",x);
                for(z1=1;z1<(*vint_perpop_nsam)[x];z1++) {
                  for(z2=1;z2<(*vint_perpop_nsam)[x];z2++) {
                    cv = 0.;
                    for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                      cv += ((*stats_linefreq)[ss][z1] - (stats_freq[x][z1] * (float)z1/(float)(*vint_perpop_nsam)[x])) *
                          ((*stats_linefreq)[ss][z2] - (stats_freq[x][z2] * (float)z2/(float)(*vint_perpop_nsam)[x]));
                    }
                    cv = cv/(double)(*vint_perpop_nsam)[x];
                    #if DENCOV_CORRECTION == 1
                    if(stats_freq[x][z2] * stats_freq[x][z1] > 0.) {
                      if((der = (stats_freq[x][z1]*stats_freq[x][z2]))!=0.)
                        cv = cv/der;
                    }
                    else cv = 0.;
                    #endif
                    fprintf(file_out,"%.6f\t",cv);
                  }
                }
                #endif
                #if LUCA_CRs == 1
                /*LUCA: here I calculate the statistics for unfolded tests with different weights 1/i^2,1/i,1,i*/
                luca_cvo2=0.; luca_cvo1=0.; luca_cv0=0.; luca_cv1=0.;
                luca_cro2=0.; luca_cro1=0.; luca_cr0=0.; luca_cr1=0.;
                luca_cso2=0.; luca_cso1=0.; luca_cs0=0.; luca_cs1=0.;
                luca_dero2=0.; luca_dero1=0.; luca_der0=0.; luca_der1=0.;
                luca_cvo2d=0.; luca_cvo1d=0.; luca_cv0d=0.; luca_cv1d=0.;
                luca_cro2d=0.; luca_cro1d=0.; luca_cr0d=0.; luca_cr1d=0.;
                luca_cso2d=0.; luca_cso1d=0.; luca_cs0d=0.; luca_cs1d=0.;
                luca_dero2d=0.; luca_dero1d=0.; luca_der0d=0.; luca_der1d=0.;
                for(z1=1;z1<(*vint_perpop_nsam)[x];z1++) {
                  for(z2=1;z2<=(*vint_perpop_nsam)[x]-z1;z2++) {
                    for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                      mean_z1 = (stats_freq[x][z1] * (float)z1/(float)(*vint_perpop_nsam)[x]);
                      mean_z2 = (stats_freq[x][z2] * (float)z2/(float)(*vint_perpop_nsam)[x]);
                      luca_mean_z1 = (stats_freq[x][(*vint_perpop_nsam)[x]-z1] * (float)((*vint_perpop_nsam)[x]-z1)/(float)(*vint_perpop_nsam)[x]);
                      luca_mean_z2 = (stats_freq[x][(*vint_perpop_nsam)[x]-z2] * (float)((*vint_perpop_nsam)[x]-z2)/(float)(*vint_perpop_nsam)[x]);
                      if(z1==z2) delta =1.;
                      else delta=0.;
                      luca_cvo2 += 1/(double)(z1*z1*z2*z2) * (((*stats_linefreq)[ss][z1] - mean_z1) *
                          ((*stats_linefreq)[ss][z2] - mean_z2)
                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                      luca_cvo1 += 1/(double)(z1*z2) * (((*stats_linefreq)[ss][z1] - mean_z1) *
                          ((*stats_linefreq)[ss][z2] - mean_z2)
                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                      luca_cv0 += (((*stats_linefreq)[ss][z1] - mean_z1) *
                          ((*stats_linefreq)[ss][z2] - mean_z2)
                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                      luca_cv1 += (double)(z1*z2) * (((*stats_linefreq)[ss][z1] - mean_z1) *
                          ((*stats_linefreq)[ss][z2] - mean_z2)
                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);

                      luca_dero2 += 1/(double)(z1*z1*z2*z2) * (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                      luca_dero1 += 1/(double)(z1*z2) * (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                      luca_der0 += (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                      luca_der1 += (double)(z1*z2) * (stats_freq[x][z1]*(stats_freq[x][z2]-delta));

                      luca_cso2 += 1/(double)(z1*z1*z2*z2) * (((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z1] - luca_mean_z1) *
                          ((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z2] - luca_mean_z2)
                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][(*vint_perpop_nsam)[x]-z1]);
                      luca_cso1 += 1/(double)(z1*z2) * (((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z1] - luca_mean_z1) *
                          ((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z2] - luca_mean_z2)
                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][(*vint_perpop_nsam)[x]-z1]);
                      luca_cs0 += (((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z1] - luca_mean_z1) *
                          ((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z2] - luca_mean_z2)
                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][(*vint_perpop_nsam)[x]-z1]);
                      luca_cs1 += (double)(z1*z2) * (((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z1] - luca_mean_z1) *
                          ((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z2] - luca_mean_z2)
                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][(*vint_perpop_nsam)[x]-z1]);

                      luca_cro2 += ((double)CComparison::min(z1,z2)/(double)(*vint_perpop_nsam)[x]-(double)(z1*z2)/(double)((*vint_perpop_nsam)[x]*(*vint_perpop_nsam)[x])) *
                      1/(double)(z1*z1*z2*z2) * (stats_freq[x][(*vint_perpop_nsam)[x]-z1]*(stats_freq[x][(*vint_perpop_nsam)[x]-z2]-delta));
                      luca_cro1 += ((double)CComparison::min(z1,z2)/(double)(*vint_perpop_nsam)[x]-(double)(z1*z2)/(double)((*vint_perpop_nsam)[x]*(*vint_perpop_nsam)[x])) *
                      1/(double)(z1*z2) * (stats_freq[x][(*vint_perpop_nsam)[x]-z1]*(stats_freq[x][(*vint_perpop_nsam)[x]-z2]-delta));
                      luca_cr0 += ((double)CComparison::min(z1,z2)/(double)(*vint_perpop_nsam)[x]-(double)(z1*z2)/(double)((*vint_perpop_nsam)[x]*(*vint_perpop_nsam)[x])) *
                      (stats_freq[x][(*vint_perpop_nsam)[x]-z1]*(stats_freq[x][(*vint_perpop_nsam)[x]-z2]-delta));
                      luca_cr1 += ((double)CComparison::min(z1,z2)/(double)(*vint_perpop_nsam)[x]-(double)(z1*z2)/(double)((*vint_perpop_nsam)[x]*(*vint_perpop_nsam)[x])) *
                      (double)(z1*z2) * (stats_freq[x][(*vint_perpop_nsam)[x]-z1]*(stats_freq[x][(*vint_perpop_nsam)[x]-z2]-delta));

                      if(z1==z2) {
                        luca_cvo2d += 1/(double)(z1*z1*z2*z2) * (((*stats_linefreq)[ss][z1] - mean_z1) *
                                            ((*stats_linefreq)[ss][z2] - mean_z2)
                                            - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                        luca_cvo1d += 1/(double)(z1*z2) * (((*stats_linefreq)[ss][z1] - mean_z1) *
                                          ((*stats_linefreq)[ss][z2] - mean_z2)
                                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                        luca_cv0d += (((*stats_linefreq)[ss][z1] - mean_z1) *
                               ((*stats_linefreq)[ss][z2] - mean_z2)
                               - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);
                        luca_cv1d += (double)(z1*z2) * (((*stats_linefreq)[ss][z1] - mean_z1) *
                                         ((*stats_linefreq)[ss][z2] - mean_z2)
                                         - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1]);

                        luca_dero2d += 1/(double)(z1*z1*z2*z2) * (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                        luca_dero1d += 1/(double)(z1*z2) * (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                        luca_der0d += (stats_freq[x][z1]*(stats_freq[x][z2]-delta));
                        luca_der1d += (double)(z1*z2) * (stats_freq[x][z1]*(stats_freq[x][z2]-delta));

                        luca_cso2d += 1/(double)(z1*z1*z2*z2) * (((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z1] - luca_mean_z1) *
                                            ((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z2] - luca_mean_z2)
                                            - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][(*vint_perpop_nsam)[x]-z1]);
                        luca_cso1d += 1/(double)(z1*z2) * (((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z1] - luca_mean_z1) *
                                          ((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z2] - luca_mean_z2)
                                          - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][(*vint_perpop_nsam)[x]-z1]);
                        luca_cs0d += (((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z1] - luca_mean_z1) *
                               ((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z2] - luca_mean_z2)
                               - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][(*vint_perpop_nsam)[x]-z1]);
                        luca_cs1d += (double)(z1*z2) * (((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z1] - luca_mean_z1) *
                                         ((*stats_linefreq)[ss][(*vint_perpop_nsam)[x]-z2] - luca_mean_z2)
                                         - delta * (double)z1 * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][(*vint_perpop_nsam)[x]-z1]);

                        luca_cro2d += ((double)CComparison::min(z1,z2)/(double)(*vint_perpop_nsam)[x]-(double)(z1*z2)/(double)((*vint_perpop_nsam)[x]*(*vint_perpop_nsam)[x])) *
                        1/(double)(z1*z1*z2*z2) * (stats_freq[x][(*vint_perpop_nsam)[x]-z1]*(stats_freq[x][(*vint_perpop_nsam)[x]-z2]-delta));
                        luca_cro1d += ((double)CComparison::min(z1,z2)/(double)(*vint_perpop_nsam)[x]-(double)(z1*z2)/(double)((*vint_perpop_nsam)[x]*(*vint_perpop_nsam)[x])) *
                        1/(double)(z1*z2) * (stats_freq[x][(*vint_perpop_nsam)[x]-z1]*(stats_freq[x][(*vint_perpop_nsam)[x]-z2]-delta));
                        luca_cr0d += ((double)CComparison::min(z1,z2)/(double)(*vint_perpop_nsam)[x]-(double)(z1*z2)/(double)((*vint_perpop_nsam)[x]*(*vint_perpop_nsam)[x])) *
                        (stats_freq[x][(*vint_perpop_nsam)[x]-z1]*(stats_freq[x][(*vint_perpop_nsam)[x]-z2]-delta));
                        luca_cr1d += ((double)CComparison::min(z1,z2)/(double)(*vint_perpop_nsam)[x]-(double)(z1*z2)/(double)((*vint_perpop_nsam)[x]*(*vint_perpop_nsam)[x])) *
                        (double)(z1*z2) * (stats_freq[x][(*vint_perpop_nsam)[x]-z1]*(stats_freq[x][(*vint_perpop_nsam)[x]-z2]-delta));
                      }
                    }
                  }
                }

                luca_cvo2 = luca_cvo2*luca_cro2/luca_cso2/luca_dero2/(double)(*vint_perpop_nsam)[x];
                luca_cvo1 = luca_cvo1*luca_cro1/luca_cso1/luca_dero1/(double)(*vint_perpop_nsam)[x];
                luca_cv0 = luca_cv0*luca_cr0/luca_cs0/luca_der0/(double)(*vint_perpop_nsam)[x];
                luca_cv1 = luca_cv1*luca_cr1/luca_cs1/luca_der1/(double)(*vint_perpop_nsam)[x];

                luca_cvo2d = luca_cvo2d*luca_cro2d/luca_cso2d/luca_dero2d/(double)(*vint_perpop_nsam)[x];
                luca_cvo1d = luca_cvo1d*luca_cro1d/luca_cso1d/luca_dero1d/(double)(*vint_perpop_nsam)[x];
                luca_cv0d = luca_cv0d*luca_cr0d/luca_cs0d/luca_der0d/(double)(*vint_perpop_nsam)[x];
                luca_cv1d = luca_cv1d*luca_cr1d/luca_cs1d/luca_der1d/(double)(*vint_perpop_nsam)[x];

                fprintf(file_out,"CVO2[%d]:\t%.6f\t",x,luca_cvo2);
                fprintf(file_out,"CVO1[%d]:\t%.6f\t",x,luca_cvo1);
                fprintf(file_out,"CV0[%d]:\t%.6f\t",x,luca_cv0);
                fprintf(file_out,"CV1[%d]:\t%.6f\t",x,luca_cv1);

                fprintf(file_out,"CVO2d[%d]:\t%.6f\t",x,luca_cvo2d);
                fprintf(file_out,"CVO1d[%d]:\t%.6f\t",x,luca_cvo1d);
                fprintf(file_out,"CV0d[%d]:\t%.6f\t",x,luca_cv0d);
                fprintf(file_out,"CV1d[%d]:\t%.6f\t",x,luca_cv1d);
                fprintf(file_out,"R2[%d]:\t%.6f\t",x,stats_R2[x]);
                /*end LUCA*/
                #endif
              }
            }
            fprintf(file_out,"\n");
          }
        }
        if((*output) == 60) {
          if(ploidy->value() == HAPLOID) {
            if(outgroup_presence==0) {
              for(x=0;x<npops->value()-oo;x++) {
                fprintf(file_out,"Cov_SNM_pop[%d]:\t",x);
                for(z1=1;z1<=(long int)floor((*vint_perpop_nsam)[x]/2);z1++) {
                  for(z2=1;z2<=(long int)floor((*vint_perpop_nsam)[x]/2);z2++) {
                    cv = 0.;
                    for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                      mean_z1 = mean_z2 = (*stats_thetaS)[x]/(float)(*vint_perpop_nsam)[x];
                      if(!((float)z1 == floor((*vint_perpop_nsam)[x]/2) && (float)z1 == (float)(*vint_perpop_nsam)[x]/2.))
                        mean_z1 *= 2.;
                      if(!((float)z2 == floor((*vint_perpop_nsam)[x]/2) && (float)z2 == (float)(*vint_perpop_nsam)[x]/2.))
                        mean_z2 *= 2.;

                      cv += ((*stats_linefreq)[ss][z1] - mean_z1) *
                          ((*stats_linefreq)[ss][z2] - mean_z2);
                    }
                    cv = cv/(double)(*vint_perpop_nsam)[x];
                    #if DENCOV_CORRECTION == 1
                    if(stats_freq[x][z2] * stats_freq[x][z1] > 0.) {
                      if(z1==z2) delta =1.;
                      else delta=0.;
                      cv = cv - delta * (double)z1/(double)(*vint_perpop_nsam)[x] * (1.-(double)z1/(double)(*vint_perpop_nsam)[x])*stats_freq[x][z1];
                      if((der = (stats_freq[x][z1]*(stats_freq[x][z2]-delta))) != 0.)
                        cv = cv/der;
                    }
                    else cv = 0.;
                    #endif
                    fprintf(file_out,"%.6f\t",cv);
                  }
                }
              }
            }
            else {
              for(x=0;x<npops->value()-oo;x++) {
                fprintf(file_out,"Cov_SNM_pop[%d]:\t",x);
                for(z1=1;z1<(*vint_perpop_nsam)[x];z1++) {
                  for(z2=1;z2<(*vint_perpop_nsam)[x];z2++) {
                    cv = 0.;
                    for(ss=initsq1[x];ss<initsq1[x]+(*vint_perpop_nsam)[x];ss++) {
                      cv += ((*stats_linefreq)[ss][z1] - ((*stats_thetaS)[x]/(float)(*vint_perpop_nsam)[x])) *
                          ((*stats_linefreq)[ss][z2] - ((*stats_thetaS)[x]/(float)(*vint_perpop_nsam)[x]));
                    }
                    cv = cv/(double)(*vint_perpop_nsam)[x];
                    #if DENCOV_CORRECTION == 1
                    if(stats_freq[x][z2] * stats_freq[x][z1] > 0.) {
                      if((der = (stats_freq[x][z1]*stats_freq[x][z2]))!=0.)
                        cv = cv/der;
                    }
                    else cv = 0.;
                    #endif
                    fprintf(file_out,"%.6f\t",cv);
                  }
                }
              }
            }
            fprintf(file_out,"\n");
          }
        }
        if((*output) == 5) {
          if(ploidy->value() == HAPLOID) {
            /*fprintf(file_out,"\n\nFrequency of SNPs in a population that contain each line:");*/
            if(outgroup_presence==0) {
              for(x=0;x<npops->value()-oo;x++) {
                for(z=initsq1[x];z<initsq1[x]+(*vint_perpop_nsam)[x];z++) {
                  for(ss=1;ss<(long int)floor((*vint_perpop_nsam)[x]/2);ss++) {
                    fprintf(file_out,"line_freq[%d,%d]:\t%.3f\t",z,ss,(*stats_linefreq)[z][ss]);
                  }
                }
              }
            }
            else {
              for(x=0;x<npops->value()-oo;x++) {
                for(z=initsq1[x];z<initsq1[x]+(*vint_perpop_nsam)[x];z++) {
                  for(ss=1;ss<(*vint_perpop_nsam)[x];ss++) {
                    fprintf(file_out,"line_freq[%d,%d]:\t%.3f\t",z,ss,(*stats_linefreq)[z][ss]);
                  }
                }
              }
            }
          }
          fprintf(file_out,"\n");
        }
        if((*output) == 4) {
          if(npops->value()-!outgroup_presence==1) oo = 0;
          else oo = 1;
          /*fprintf(file_out,"\nAll pairwise comparisons (mismatch distribution) per population:");*/
          for(x=0;x<npops->value()-oo;x++) {
            fprintf(file_out,"Pairwise_Comparisons_npop[%d:%ld comb]:\t",x,(long int)((*vint_perpop_nsam)[x])*((*vint_perpop_nsam)[x]-1)/2);
            for(zz=0;zz<(*vint_perpop_nsam)[x]*((*vint_perpop_nsam)[x]-1)/2;zz++) {
              if(ploidy->value() == HAPLOID) {fprintf(file_out,"%.1f\t",(*stats_mdw)[x][zz]);}
              if(ploidy->value() == DIPLOID) {fprintf(file_out,"NA\t");}
            }
          }
          fprintf(file_out,"\n");
        }
        if((*output) == 30) {
          if(npops->value()-!outgroup_presence==1) oo = 0;
          else oo = 1;
          /*fprintf(file_out,"\n");*/
          /*for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"\tFREQpop[%d]",x);*/
          /*if(missratio->value() > 0.) {for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"\tSAMPpop[%d]",x);}*/
          for(zz=0;zz<length_seg->value();zz++) {
            ss=0; for(x=0;x<npops->value()-oo;x++) {ss += (*nfd)[x][zz];}
            if(ss) {
              fprintf(file_out,"\tSNP[%ld]",(*positions)[zz]);
              for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"\t%.3f",(*jfd)[x][zz]);
              if(missratio->value() > 0.) {for(x=0;x<npops->value()-oo;x++) fprintf(file_out,"\t%d",(*nfd)[x][zz]);}
            }
          }
          fprintf(file_out,"\n");
        }
        if((*output) == 2) {
          /*ffprintf(file_out,file_out,"\nFrequency of variants for each population:");*/
          if(outgroup_presence == 1) {
            for(x=0;x<npops->value()-1;x++) {
              fprintf(file_out,"\tnsam[%d]:\t%d\tS[%d]:\t%ld",x,(*vint_perpop_nsam)[x],x,(long int)(*stats_S)[x]);
              for(y=1;y<(*vint_perpop_nsam)[x];y++) {
                fprintf(file_out,"\tfr[%d,%d]:\t%ld",x,y,(*stats_freq)[x][y]);
              }
            }
          }
          else {
            for(x=0;x<npops->value()-1;x++) {
              fprintf(file_out,"\tnsam[%d]:\t%d\tS[%d]:\t%ld",x,(*vint_perpop_nsam)[x],x,(long int)(*stats_S)[x]);
              for(y=1;y<=floor((*vint_perpop_nsam)[x]/2);y++) {
                fprintf(file_out,"\tfr[%d,%d]:\t%ld",x,y,(*stats_freq)[x][y]);
              }
            }
          }
          /*fprintf(file_out,"\n");

           if(npops->value()>1) {
           for(x=0;x<npops->value()-oo;x++) {
           fprintf(file_out,"%d\t%ld\t",(*vint_perpop_nsam)[x],(long int)stats_S[x]);
           for(y=1;y<(*vint_perpop_nsam)[x];y++) {
           fprintf(file_out,"%ld\t",stats_freq[x][y]);
           }
           }
           }
           else {
           x=0;
           fprintf(file_out,"%d\t%ld\t",(*vint_perpop_nsam)[x],(long int)stats_S[x]);
           for(y=1;y<=floor((*vint_perpop_nsam)[0]/2);y++) {
           fprintf(file_out,"%ld\t",stats_freq[0][y]);
           }
           }
           */
          fprintf(file_out,"\n");
        }
        if((*output) == 1) {
           /*
           if(outgroup_presence == 1) {
            np = npops->value()-1;
            for(x=0;x<np;x++) {
              if((*vint_perpop_nsam)[x] > 1) {
                fprintf(file_out,"S[%d]:\t%d\t",x,(int)stats_S[x]);
                fprintf(file_out,"Theta(Wat)[%d]:\t%f\t",x,stats_thetaS[x]);
                fprintf(file_out,"Theta(Taj)[%d]:\t%f\t",x,(*stats_thetaT)[x]);
                fprintf(file_out,"Theta(Fu&Li)[%d]:\t%f\t",x,stats_thetaFL[x]);
                fprintf(file_out,"Theta(Fay&Wu)[%d]:\t%f\t",x,stats_thetaFW[x]);
                fprintf(file_out,"Theta(Zeng)[%d]:\t%f\t",x,stats_thetaL[x]);
                fprintf(file_out,"Theta(Achaz,Wat)[%d]:\t%f\t",x,stats_thetaSA[x]);
                fprintf(file_out,"Theta(Achaz,Taj)[%d]:\t%f\t",x,(*stats_thetaT)A[x]);
                if((*stats_thetaT)HKY[x] > NA_VALUE && missratio->value() == 0.) fprintf(file_out,"Theta(Taj)HKY[%d]:\t%f\t",x,(*stats_thetaT)HKY[x]*length_al);
                else fprintf(file_out,"Theta(Taj)HKY[%d]:\tNA\t",x);
              }
              else {
                fprintf(file_out,"S[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Wat)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Taj)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Fu&Li)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Fay&Wu)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Zeng)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Achaz,Wat)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Achaz,Taj)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Taj)HKY[%d]:\tNA\t",x);
              }
              if(force_outgroup->value()==0) fprintf(file_out,"Divergence[%d]:\t%f\t",x,stats_K[x]);
              else fprintf(file_out,"Divergence[%d]:\tNA\t",x);
              if(stats_KHKY[x] > NA_VALUE && missratio->value() == 0.) fprintf(file_out,"DivergenceHKY[%d]:\t%f\t",x,stats_KHKY[x]*length_al);
              else fprintf(file_out,"DivergenceHKY[%d]:\tNA\t",x);
            }
          }
          else {
            np = npops->value()-1;
            for(x=0;x<np;x++) {
              if((*vint_perpop_nsam)[x] > 1) {
                fprintf(file_out,"S[%d]:\t%d\t",x,(int)stats_S[x]);
                fprintf(file_out,"Theta(Wat)[%d]:\t%f\t",x,stats_thetaS[x]);
                fprintf(file_out,"Theta(Taj)[%d]:\t%f\t",x,(*stats_thetaT)[x]);
                fprintf(file_out,"Theta(Fu&Li)[%d]:\t%f\t",x,stats_thetaFL[x]);
                fprintf(file_out,"Theta(Achaz,Wat)[%d]:\t%f\t",x,stats_thetaSA[x]);
                fprintf(file_out,"Theta(Achaz,Taj)[%d]:\t%f\t",x,(*stats_thetaT)A[x]);
                if(stats_thetaTHKY[x] > NA_VALUE && missratio->value() == 0.) fprintf(file_out,"Theta(Taj)HKY[%d]:\t%f\t",x,stats_thetaT[x]*length_al);
                else fprintf(file_out,"Theta(Taj)HKY[%d]:\tNA\t",x);
              }
              else {
                fprintf(file_out,"S[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Wat)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Taj)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Fu&Li)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Achaz,Wat)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Achaz,Taj)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Taj)HKY[%d]:\tNA\t",x);
              }
            }
          }
          *//**/
          if(outgroup_presence == 1) {
            np = npops->value()-1;
            for(x=0;x<np;x++) {
              if((*vint_perpop_nsam)[x] > 1) {
                /*
                fprintf(file_out,"Sw[%d]:\t%d\t",x,(int)stats_S[x]);
                fprintf(file_out,"Thetaw(Wat)[%d]:\t%f\t",x,stats_thetaS[x]);
                fprintf(file_out,"Thetaw(Taj)[%d]:\t%f\t",x,stats_thetaT[x]);
                */
                fprintf(file_out,"S[%d]:\t%d\t",x,(int)(*stats_So)[x]);
                fprintf(file_out,"Theta(Wat)[%d]:\t%f\t",x,(*stats_thetaSo)[x]);
                fprintf(file_out,"Theta(Taj)[%d]:\t%f\t",x,(*stats_thetaTo)[x]);
                fprintf(file_out,"Theta(Fu&Li)[%d]:\t%f\t",x,(*stats_thetaFL)[x]);
                fprintf(file_out,"Theta(Fay&Wu)[%d]:\t%f\t",x,(*stats_thetaFW)[x]);
                fprintf(file_out,"Theta(Zeng)[%d]:\t%f\t",x,(*stats_thetaL)[x]);
                fprintf(file_out,"Theta(Achaz,Wat)[%d]:\t%f\t",x,(*stats_thetaSA)[x]);
                fprintf(file_out,"Theta(Achaz,Taj)[%d]:\t%f\t",x,(*stats_thetaTA)[x]);
                if((*stats_thetaTHKY)[x] > NA_VALUE && missratio->value() == 0.) fprintf(file_out,"Theta/nt(Taj)HKY[%d]:\t%f\t",x,(*stats_thetaTHKY)[x]);
                else fprintf(file_out,"Theta/nt(Taj)HKY[%d]:\tNA\t",x);
                if((*stats_S)[x] > 0) {
                  fprintf(file_out,"an_x[%d]:\t%f\t",x,(*stats_anx)[x]/*(double)stats_S[x]/(double)stats_thetaS[x]*/);
                  fprintf(file_out,"bn_x[%d]:\t%f\t",x,(*stats_bnx)[x]);
                  fprintf(file_out,"an_xo[%d]:\t%f\t",x,(*stats_anxo)[x]);
                  fprintf(file_out,"bn_xo[%d]:\t%f\t",x,(*stats_bnxo)[x]);
                }
                else {
                  fprintf(file_out,"an_x[%d]:\tNA\t",x);
                  fprintf(file_out,"bn_x[%d]:\tNA\t",x);
                  fprintf(file_out,"an_xo[%d]:\tNA\t",x);
                  fprintf(file_out,"bn_xo[%d]:\tNA\t",x);
                }
              }
              else {
                /*
                fprintf(file_out,"Sw[%d]:\tNA\t",x);
                fprintf(file_out,"Thetaw(Wat)[%d]:\tNA\t",x);
                fprintf(file_out,"Thetaw(Taj)[%d]:\tNA\t",x);
                */
                fprintf(file_out,"S[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Wat)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Taj)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Fu&Li)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Fay&Wu)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Zeng)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Achaz,Wat)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Achaz,Taj)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Taj)HKY[%d]:\tNA\t",x);
                fprintf(file_out,"an_x[%d]:\tNA\t",x);
                fprintf(file_out,"bn_x[%d]:\tNA\t",x);
                fprintf(file_out,"an_xo[%d]:\tNA\t",x);
                fprintf(file_out,"bn_xo[%d]:\tNA\t",x);
              }
              if(force_outgroup->value()==0) fprintf(file_out,"Divergence[%d]:\t%f\t",x,(*stats_K)[x]);
              else fprintf(file_out,"Divergence[%d]:\tNA\t",x);
              if((*stats_KHKY)[x] > NA_VALUE && missratio->value() == 0.) fprintf(file_out,"DivergenceHKY[%d]:\t%f\t",x,(*stats_KHKY)[x]);
              else fprintf(file_out,"DivergenceHKY[%d]:\tNA\t",x);
            }
          }
          else {
            np = npops->value()-1;
            for(x=0;x<np;x++) {
              if((*vint_perpop_nsam)[x] > 1) {
                fprintf(file_out,"S[%d]:\t%d\t",x,(int)(*stats_S)[x]);
                fprintf(file_out,"Theta(Wat)[%d]:\t%f\t",x,(*stats_thetaS)[x]);
                fprintf(file_out,"Theta(Taj)[%d]:\t%f\t",x,(*stats_thetaT)[x]);
                fprintf(file_out,"Theta(Fu&Li)[%d]:\t%f\t",x,(*stats_thetaFL)[x]);
                fprintf(file_out,"Theta(Achaz,Wat)[%d]:\t%f\t",x,(*stats_thetaSA)[x]);
                fprintf(file_out,"Theta(Achaz,Taj)[%d]:\t%f\t",x,(*stats_thetaTA)[x]);
                if((*stats_thetaTHKY)[x] > NA_VALUE && missratio->value() == 0.) fprintf(file_out,"Theta(Taj)HKY[%d]:\t%f\t",x,(*stats_thetaTHKY)[x]);
                else fprintf(file_out,"Theta(Taj)HKY[%d]:\tNA\t",x);
                if((*stats_S)[x] > 0) {
                  fprintf(file_out,"an_x[%d]:\t%f\t",x,(*stats_anx)[x]/*(double)stats_S[x]/(double)stats_thetaS[x]*/);
                  fprintf(file_out,"bn_x[%d]:\t%f\t",x,(*stats_bnx)[x]);
                  fprintf(file_out,"an_xo[%d]:\t%f\t",x,(*stats_anxo)[x]);
                  fprintf(file_out,"bn_xo[%d]:\t%f\t",x,(*stats_bnxo)[x]);
                }
                else {
                  fprintf(file_out,"an_x[%d]:\tNA\t",x);
                  fprintf(file_out,"bn_x[%d]:\tNA\t",x);
                  fprintf(file_out,"an_xo[%d]:\tNA\t",x);
                  fprintf(file_out,"bn_xo[%d]:\tNA\t",x);
                }
              }
              else {
                fprintf(file_out,"S[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Wat)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Taj)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Fu&Li)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Achaz,Wat)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Achaz,Taj)[%d]:\tNA\t",x);
                fprintf(file_out,"Theta(Taj)HKY[%d]:\tNA\t",x);
                fprintf(file_out,"an_x[%d]:\tNA\t",x);
                fprintf(file_out,"bn_x[%d]:\tNA\t",x);
                fprintf(file_out,"an_xo[%d]:\tNA\t",x);
                fprintf(file_out,"bn_xo[%d]:\tNA\t",x);
              }
            }
          }
          /**/
          np = npops->value()-1;
          for(x=0;x<np;x++) {
            if(include_unknown->value() == 0) {
              if((*vint_perpop_nsam)[x]>1) {
                if(ploidy->value() == HAPLOID && include_unknown->value() == 0)
                  fprintf(file_out,"HapW[%d]:\t%f\tnHap[%d]:\t%d\t",x,(*stats_hapw)[x],x,(*stats_nhpop)[x]);
              }
              else {
                if(ploidy->value() == HAPLOID && include_unknown->value() == 0)
                  fprintf(file_out,"HapW[%d]:\tNA\tnHap[%d]:\t1\t",x,x);
              }
            }
          }
          if(outgroup_presence == 1) {
            np = npops->value()-1;
            for(x=0;x<np;x++) {
              if((*stats_Dtaj)[x] > NA_VALUE)
                fprintf(file_out,"TajimaD[%d]:\t%f\t",x,(*stats_Dtaj)[x]);
              else fprintf(file_out,"TajimaD[%d]:\tNA\t",x);
              if((*stats_Dfl)[x] > NA_VALUE)
                fprintf(file_out,"Fu&LiD[%d]:\t%f\t",x,(*stats_Dfl)[x]);
              else  fprintf(file_out,"Fu&LiD[%d]:\tNA\t",x);
              if((*stats_Ffl)[x] > NA_VALUE)
                fprintf(file_out,"Fu&LiF[%d]:\t%f\t",x,(*stats_Ffl)[x]);
              else fprintf(file_out,"Fu&LiF[%d]:\tNA\t",x);
              if((*stats_Hnfw)[x] > NA_VALUE)
                fprintf(file_out,"Fay&WunormH[%d]:\t%f\t",x,(*stats_Hnfw)[x]);
              else fprintf(file_out,"Fay&WunormH[%d]:\tNA\t",x);
              if((*stats_thetaT)[x]-(*stats_thetaFW)[x] != NA_VALUE)
                fprintf(file_out,"Fay&WuH[%d]:\t%f\t",x,(*stats_thetaT)[x]-(*stats_thetaFW)[x]);
              else fprintf(file_out,"Fay&WuH[%d]: NA\t",x);
              if((*stats_Ez)[x] > NA_VALUE)
                fprintf(file_out,"ZengE[%d]:\t%f\t",x,(*stats_Ez)[x]);
              else fprintf(file_out,"ZengE[%d]:\tNA\t",x);
              if((*stats_Yach)[x] > NA_VALUE)
                fprintf(file_out,"AchazY[%d]:\t%f\t",x,(*stats_Yach)[x]);
              else fprintf(file_out,"AchazY[%d]:\tNA\t",x);
/**/
              if((*stats_FH)[x] > NA_VALUE)
                  fprintf(file_out,"WH[%d]:\t%f\t",x,(*stats_FH)[x]);
              else fprintf(file_out,"WH[%d]:\tNA\t",x);
/**/              
              if(ploidy->value() == HAPLOID) {
                /*
                if(stats_R2[x] > NA_VALUE)
                  fprintf(file_out,"R2[%d]:\t%f\t",x,stats_R2[x]);
                else fprintf(file_out,"R2[%d]:\tNA\t",x);
                */
                if(include_unknown->value() == 0) {
                  if((*stats_Fs)[x] > NA_VALUE && missratio->value() < 1e-6)
                    fprintf(file_out,"Fs[%d]:\t%f\t",x,(*stats_Fs)[x]);
                  else fprintf(file_out,"Fs[%d]:\tNA\t",x);
                }
              }/*
              else {
                if(stats_R2[x] > NA_VALUE
                  fprintf(file_out,"R2d[%d]:\t%f\t",x,stats_R2[x]);
                else fprintf(file_out,"R2d[%d]:\tNA\t",x);
              }*/
              for(xx=0;xx<(*r2i_ploidies)[0];xx++) {
                if((*stats_R2p)[xx][x] > NA_VALUE) {
                  if((*r2i_ploidies)[0]==1 && ploidy->value() == HAPLOID) fprintf(file_out,"R2[%d]:\t%f\t",x,(*stats_R2p)[xx][x]);
                  if((*r2i_ploidies)[0]==1 && ploidy->value() == DIPLOID) fprintf(file_out,"R2d[%d]:\t%f\t",x,(*stats_R2p)[xx][x]);
                  if((*r2i_ploidies)[0]!=1) fprintf(file_out,"R2p%d[%d]:\t%f\t",(*r2i_ploidies)[xx+1],x,(*stats_R2p)[xx][x]);
                } else {
                  if((*r2i_ploidies)[0]==1 && ploidy->value() == HAPLOID) fprintf(file_out,"R2[%d]:\tNA\t",x);
                  if((*r2i_ploidies)[0]==1 && ploidy->value() == DIPLOID) fprintf(file_out,"R2d[%d]:\tNA\t",x);
                  if((*r2i_ploidies)[0]!=1) fprintf(file_out,"R2p%d[%d]:\tNA\t",(*r2i_ploidies)[xx+1],x);

                }
              }

              /*fprintf(file_out,"Fay&WuH[%d]:\t%f\t",x,stats_thetaT[x]-stats_thetaFW[x]);*/
              /*fprintf(file_out,"Fay&WuH2[%d]:\t%f\t",x,2.*(stats_thetaT[x]-stats_thetaL[x]));*/
            }
          }
          else {
            np = npops->value()-1;
            for(x=0;x<np;x++) {
              if((*stats_Dtaj)[x] > NA_VALUE)
                fprintf(file_out,"TajimaD[%d]:\t%f\t",x,(*stats_Dtaj)[x]);
              else fprintf(file_out,"TajimaD[%d]:\tNA\t",x);
              if((*stats_Dfl)[x] > NA_VALUE)
                fprintf(file_out,"Fu&LiD*[%d]:\t%f\t",x,(*stats_Dfl)[x]);
              else  fprintf(file_out,"Fu&LiD*[%d]:\tNA\t",x);
              if((*stats_Ffl)[x] > NA_VALUE)
                fprintf(file_out,"Fu&LiF*[%d]:\t%f\t",x,(*stats_Ffl)[x]);
              else fprintf(file_out,"Fu&LiF*[%d]:\tNA\t",x);
              if((*stats_Yach)[x] > NA_VALUE)
                fprintf(file_out,"AchazY*[%d]:\t%f\t",x,(*stats_Yach)[x]);
              else fprintf(file_out,"AchazY*[%d]:\tNA\t",x);
              if(ploidy->value() == HAPLOID) {
                /*
                if(stats_R2[x] > NA_VALUE)
                  fprintf(file_out,"R2[%d]:\t%f\t",x,stats_R2[x]);
                else fprintf(file_out,"R2[%d]:\tNA\t",x);
                */
                if(include_unknown->value() == 0) {
                  if((*stats_Fs)[x] > NA_VALUE && missratio->value() < 1e-6)
                    fprintf(file_out,"Fs[%d]:\t%f\t",x,(*stats_Fs)[x]);
                  else fprintf(file_out,"Fs[%d]:\tNA\t",x);
                }
              }/*
              else {
                if(stats_R2[x] > NA_VALUE)
                  fprintf(file_out,"R2d[%d]:\t%f\t",x,stats_R2[x]);
                else fprintf(file_out,"R2d[%d]:\tNA\t",x);
              }*/
              for(xx=0;xx<(*r2i_ploidies)[0];xx++) {
                if((*stats_R2p)[xx][x] > NA_VALUE) {
                  if((*r2i_ploidies)[0]==1 && ploidy->value() == HAPLOID) fprintf(file_out,"R2[%d]:\t%f\t",x,(*stats_R2p)[xx][x]);
                  if((*r2i_ploidies)[0]==1 && ploidy->value() == DIPLOID) fprintf(file_out,"R2d[%d]:\t%f\t",x,(*stats_R2p)[xx][x]);
                  if((*r2i_ploidies)[0]!=1) fprintf(file_out,"R2p%d[%d]:\t%f\t",(*r2i_ploidies)[xx+1],x,(*stats_R2p)[xx][x]);
                } else {
                  if((*r2i_ploidies)[0]==1 && ploidy->value() == HAPLOID) fprintf(file_out,"R2[%d]:\tNA\t",x);
                  if((*r2i_ploidies)[0]==1 && ploidy->value() == DIPLOID) fprintf(file_out,"R2d[%d]:\tNA\t",x);
                  if((*r2i_ploidies)[0]!=1) fprintf(file_out,"R2p%d[%d]:\tNA\t",(*r2i_ploidies)[xx+1],x);

                }
              }
            }
          }

          if(H1frq->value()/* && missratio->value() == 0.*/) {
            if(outgroup_presence == 1) {
              for(x=0;x<npops->value()-1;x++) {
                if((*stats_To_ii)[x] > NA_VALUE)
                  fprintf(file_out,"To_ii[%d]:\t%f\t",x,(*stats_To_ii)[x]);
                else  fprintf(file_out,"To_ii[%d]:\tNA\t",x);
                if((*stats_To_00)[x] > NA_VALUE)
                  fprintf(file_out,"To_00[%d]:\t%f\t",x,(*stats_To_00)[x]);
                else  fprintf(file_out,"To_00[%d]:\tNA\t",x);
                if((*stats_To_i0)[x] > NA_VALUE)
                  fprintf(file_out,"To_i0[%d]:\t%f\t",x,(*stats_To_i0)[x]);
                else  fprintf(file_out,"To_i0[%d]:\tNA\t",x);
              #if TO_NEW
                if(stats_To_Qc_ii[x] > NA_VALUE)
                  fprintf(file_out,"To_Qc_ii[%d]:\t%f\t",x,stats_To_Qc_ii[x]);
                else  fprintf(file_out,"To_Qc_ii[%d]:\tNA\t",x);
                if(stats_To_Qw_ii[x] > NA_VALUE)
                  fprintf(file_out,"To_Qw_ii[%d]:\t%f\t",x,stats_To_Qw_ii[x]);
                else  fprintf(file_out,"To_Qw_ii[%d]:\tNA\t",x);
                if(stats_To_Lc_ii[x] > NA_VALUE)
                  fprintf(file_out,"To_Lc_ii[%d]:\t%f\t",x,stats_To_Lc_ii[x]);
                else  fprintf(file_out,"To_Lc_ii[%d]:\tNA\t",x);
              #endif
                if(H0frq->value()) {
                  if((*stats_ToH0_ii)[x] > NA_VALUE)
                    fprintf(file_out,"To_H0_ii[%d]:\t%f\t",x,(*stats_ToH0_ii)[x]);
                  else  fprintf(file_out,"To_H0_ii[%d]:\tNA\t",x);
                  if((*stats_ToH0_00)[x] > NA_VALUE)
                    fprintf(file_out,"To_H0_i0[%d]:\t%f\t",x,(*stats_ToH0_00)[x]);
                  else  fprintf(file_out,"To_H0_i0[%d]:\tNA\t",x);
                }
              }
            }
          }
          if(npops->value()>2 && outgroup_presence == 1) {
            for(x=0;x<npops->value()-1;x++) {
              fprintf(file_out,"Sx[%d]:\t%ld\t",x,(*sanc)[x*4+0]);
              fprintf(file_out,"Sf[%d]:\t%ld\t",x,(*sanc)[x*4+1]);
              fprintf(file_out,"Sxf[%d,rest]:\t%ld\t",x,(*sanc)[x*4+2]);
              fprintf(file_out,"Ss[%d]:\t%ld\t",x,(*sanc)[x*4+3]);
            }
            fprintf(file_out,"Sx[outg]:\t%ld\t",(*sanc)[(npops->value()-1)*4+0]);
            fprintf(file_out,"Sf[outg]:\t%ld\t",(*sanc)[(npops->value()-1)*4+1]);
            fprintf(file_out,"Ss[outg,rest]:\t%ld\t",(*sanc)[(npops->value()-1)*4+2]);
            if(npops->value() > 3) fprintf(file_out,"Ss[rest]:\t%ld\t",(*sanc)[(npops->value()-1)*4+3]);
            else fprintf(file_out,"Ss[rest]:\tNA\t");

          }
          else {
            if(npops->value()>2 && outgroup_presence == 0) {
              for(x=0;x<npops->value()-1;x++) {
                fprintf(file_out,"Sx[%d]:\t%ld\t",x,(*sanc)[x*4+0] /*+ (*sanc)[x*4+2]*/);
                fprintf(file_out,"Sf[%d]:\t%ld\t",x,(*sanc)[x*4+1]);
                fprintf(file_out,"Ss[%d]:\t%ld\t",x,(*sanc)[x*4+3]);
              }
              fprintf(file_out,"Ss[rest]:\t%ld\t",(*sanc)[(npops->value()-1)*4+3]);
            }
            else {
              if(npops->value() > 1) {
                x=0;
                fprintf(file_out,"Sx[%d]:\t%ld\t",x,(*sanc)[x*4+0]);
                x=1;
                fprintf(file_out,"Sx[%d]:\t%ld\t",x,(*sanc)[x*4+0]);
                x=0;
                fprintf(file_out,"Sf:\t%ld\t",(*sanc)[x*4+1]);
                fprintf(file_out,"Ss:\t%ld\t",(*sanc)[x*4+3]);
              }
              else
                fprintf(file_out,"Sx[%d]:\t%ld\t",x,(*sanc)[0*4+0]);
            }
          }

          /*if(ploidy->value() == HAPLOID && include_unknown->value()==0) {*/
            for(x=0;x<npops->value()-1/*!outgroup_presence*/;x++) {
              if((*vint_perpop_nsam)[x] > 2) {
                fprintf(file_out,"MD_SDev[%d]:\t%f\t",x,(*stats_mdsd)[x]);
                if((*stats_mdg1)[x] > NA_VALUE) fprintf(file_out,"MD_Skewness[%d]:\t%f\t",x,(*stats_mdg1)[x]); //.
                else fprintf(file_out,"MD_Skewness[%d]:\tNA\t",x);
              }
              else {
                fprintf(file_out,"MD_SDev[%d]:\tNA\t",x);
                fprintf(file_out,"MD_Skewness[%d]:\tNA\t",x);
              }
              if((*vint_perpop_nsam)[x] > 3) {
                if((*stats_mdg2)[x] > NA_VALUE) fprintf(file_out,"MD_Kurtosis[%d]:\t%f\t",x,(*stats_mdg2)[x]); //.
                else fprintf(file_out,"MD_Kurtosis[%d]:\tNA\t",x);
              }
              else
                fprintf(file_out,"MD_Kurtosis[%d]:\tNA\t",x);
            }
          /*}*/

          if(npops->value()-1/*!outgroup_presence*/ > 1) {
            if(npops->value()-1/*!outgroup_presence*/ > 2) {
              if(stats_fstALL->value() > NA_VALUE) {
                if(niter->value() && piter_niteriall->value() > 0) fprintf(file_out,"Fst:\t%f\t P-value:\t%f\t",stats_fstALL->value(),(double)piter_iall->value()/(double)piter_niteriall->value());
                else fprintf(file_out,"Fst:\t%f\t P-value:\tNA\t",stats_fstALL->value());
              }
              else {
                if(niter && piter_niteriall > 0) fprintf(file_out,"Fst:\tNA\t P-value:\tNA\t");
                else fprintf(file_out,"Fst:\tNA\t P-value:\tNA\t");
              }

              for(x=0;x<npops->value()-1;x++) {
                if((*stats_fst1all)[x] > NA_VALUE) {
                  if(niter->value() && (*piter_niteri1)[x] > 0) fprintf(file_out,"Fst1[%d,rest]:\t%f\t P-value:\t%f\t",x,(*stats_fst1all)[x],(double)(*piter_i1)[x]/(double)(*piter_niteri1)[x]);
                  else fprintf(file_out,"Fst1[%d,rest]:\t%f\t P-value:\tNA\t",x,(*stats_fst1all)[x]);
                }
                else {
                  if(niter && (*piter_niteri1)[x] > 0) fprintf(file_out,"Fst1[%d,%d]:\tNA\t P-value:\tNA\t",x,y);
                  else fprintf(file_out,"Fst1[%d,%d]:\tNA\t P-value:\tNA\t",x,y);
                }
              }
            }
            z = 0;
            for(x=0;x<npops->value()-1;x++) {
              for(y=x+1;y<npops->value()-0;y++) {
                if(y==npops->value()-1) {z++;continue;}
                if((*stats_fst)[z] > NA_VALUE) {
                  if(niter->value() && (*piter_niteri)[z] > 0) fprintf(file_out,"Fst[%d,%d]:\t%f\t P-value:\t%f\t",x,y,(*stats_fst)[z],(double)(*piter_i)[z]/(double)(*piter_niteri)[z]);
                  else fprintf(file_out,"Fst[%d,%d]:\t%f\t P-value:\tNA\t",x,y,(*stats_fst)[z]);
                }
                else {
                  if(niter->value() && (*piter_niteri)[z] > 0) fprintf(file_out,"Fst[%d,%d]:\tNA\t P-value:\tNA\t",x,y);
                  else fprintf(file_out,"Fst[%d,%d]:\tNA\t P-value:\tNA\t",x,y);
                }
                z++;
              }
            }
          }
          if(include_unknown->value() == 0) {
            if(npops->value()-1/*!outgroup_presence*/ > 1) {
              if(npops->value()-1/*!outgroup_presence*/ > 2) {
                z=0;
                for(x=0;x<npops->value()-1;x++) {
                  for(y=x+1;y<npops->value()-0;y++) {
                    if(y==npops->value()-1) {z++;continue;}
                    if((*stats_fstHKY)[z] > NA_VALUE) {
                      fprintf(file_out,"FstHKY[%d,%d]:\t%f\tPiWHKY[%d]:\t%f\tPiWHKY[%d]:\t%f\tPiAHKY[%d,%d]:\t%f\tPiTHKY[%d,%d]:\t%f\t",
                          x,y,(*stats_fstHKY)[z],x,(*stats_piwHKY)[x],y,(*stats_piwHKY)[y],x,y,(*stats_piaHKY)[z],x,y,(*stats_piTHKY)[z]);
                    }
                    else {
                      fprintf(file_out,"FstHKY[%d,%d]:\tNA\t",x,y);
                      if((*stats_piwHKY)[x] > NA_VALUE) {
                        fprintf(file_out,"PiWHKY[%d]:\t%f\t",x,(*stats_piwHKY)[x]);
                      }
                      else fprintf(file_out,"PiWHKY[%d]:\tNA\t",x);
                      if((*stats_piwHKY)[y] > NA_VALUE) {
                        fprintf(file_out,"PiWHKY[%d]:\t%f\t",y,(*stats_piwHKY)[y]);
                      }
                      else fprintf(file_out,"PiWHKY[%d]:\tNA\t",y);
                      if((*stats_piaHKY)[z] > NA_VALUE) {
                        fprintf(file_out,"PiAHKY[%d,%d]:\t%f\tPiTHKY[%d,%d]:\t%f\t",x,y,(*stats_piaHKY)[z],x,y,(*stats_piTHKY)[z]);
                      }
                      else fprintf(file_out,"PiAHKY[%d,%d]:\tNA\tPiTHKY[%d,%d]:\tNA\t",x,y,x,y);
                    }
                    z++;
                  }
                }
              }
            }
          }
          if(ploidy->value() == HAPLOID && include_unknown->value() == 0) {
            for(x=0;x<npops->value()-1/*!outgroup_presence*/;x++) {
              if((*vint_perpop_nsam)[x]>1) fprintf(file_out,"HapW[%d]:\t%f\t",x,(*stats_hapw)[x]);
              else fprintf(file_out,"HapW[%d]:\tNA\t",x);
            }
            if(npops->value()-1/*!outgroup_presence*/ > 1) {
              z=0;
              for(x=0;x<npops->value()-2;x++) {
                for(y=x+1;y<npops->value()-1;y++) {
                  if(y==npops->value()-1) {z++;continue;}
                  fprintf(file_out,"HapA[%d,%d]:\t%f\tHapT[%d,%d]:\t%f\t",x,y,(*stats_hapa)[z],x,y,(*stats_hapT)[z]);
                  z++;
                }
              }
              if(npops->value()-1/*!outgroup_presence*/ > 2) {
                if(stats_fsthALL->value() > NA_VALUE) {
                  if(niter->value() && piter_niterihall->value() > 0) fprintf(file_out,"FstH:\t%f\t P-value:\t%f\t",stats_fsthALL->value(),(double)piter_ihall->value()/(double)piter_niterihall->value());
                  else fprintf(file_out,"FstH:\t%f\t P-value:\tNA\t",stats_fsthALL->value());
                }
                else {
                  if(niter && piter_niterihall > 0) fprintf(file_out,"FstH:\tNA\t P-value:\tNA\t");
                  else fprintf(file_out,"FstH:\tNA\t P-value:\tNA\t");
                }

                for(x=0;x<npops->value()-1;x++) {
                  if((*stats_fsth1all)[x] > NA_VALUE) {
                    if(niter->value() && (*piter_niterih1)[x]) fprintf(file_out,"FstH1[%d,rest]:\t%f\t P-value:\t%f\t",x,(*stats_fsth1all)[x],(double)(*piter_ih1)[x]/(double)(*piter_niterih1)[x]);
                    else fprintf(file_out,"FstH1[%d,rest]:\t%f\t P-value:\tNA\t",x,(*stats_fsth1all)[x]);
                  }
                  else {
                    if(niter->value() && (*piter_niterih1)[x] > 0) fprintf(file_out,"FstH1[%d,rest]:\tNA\t P-value:\tNA\t",x);
                    else fprintf(file_out,"FstH1[%d,rest]:\tNA\t P-value:\tNA\t",x);
                  }
                }
                /*
                if(stats_GstALL->value() > NA_VALUE) {
                  if(niter && piter_niterighall > 0) fprintf(file_out,"Gst':\t%f\t P-value:\t%f\t",stats_GstALL->value(),(double)piter_ighall/(double)piter_niterighall);
                  else fprintf(file_out,"Gst':\t%f\t P-value:\tNA\t",stats_GstALL->value());
                }
                else {
                  if(niter && piter_niterighall > 0) fprintf(file_out,"Gst':\tNA\t P-value:\tNA\t");
                  else fprintf(file_out,"Gst':\tNA\t P-value:\tNA\t");
                }
                 */
              }
              z = 0;
              for(x=0;x<npops->value()-2;x++) {
                for(y=x+1;y<npops->value()-1;y++) {
                  if(y==npops->value()-1 && !outgroup_presence) {z++;continue;}
                  if((*stats_fsth)[z] > NA_VALUE) {
                    if(niter->value() && (*piter_niterih)[z] > 0) fprintf(file_out,"FstH[%d,%d]:\t%f\t P-value:\t%f\t",x,y,(*stats_fsth)[z],(double)(*piter_ih)[z]/(double)(*piter_niterih)[z]);
                    else fprintf(file_out,"FstH[%d,%d]:\t%f\t P-value:\tNA\t",x,y,(*stats_fsth)[z]);
                  }
                  else {
                    if(niter->value() && (*piter_niterih)[z] > 0) fprintf(file_out,"FstH[%d,%d]:\tNA\t P-value:\tNA\t",x,y);
                    else fprintf(file_out,"FstH[%d,%d]:\tNA\t P-value:\tNA\t",x,y);
                  }
                  z++;
                }
              }
              /*
              z = 0;
              for(x=0;x<npops->value()-1;x++) {
                for(y=x+1;y<npops->value();y++) {
                  if(y==npops->value()-1 && !outgroup_presence) {z++;continue;}
                  if(stats_Gst[z] > NA_VALUE) {
                    if(niter && piter_niterigh[z] > 0) fprintf(file_out,"Gst'[%d,%d]:\t%f\t P-value:\t%f\t",x,y,stats_Gst[z],(double)piter_igh[z]/(double)piter_niterigh[z]);
                    else fprintf(file_out,"Gst'[%d,%d]:\t%f\t P-value:\tNA\t",x,y,stats_Gst[z]);
                  }
                  else {
                    if(niter && piter_niterigh[z] > 0) fprintf(file_out,"Gst'[%d,%d]:\tNA\t P-value:\tNA\t",x,y);
                    else fprintf(file_out,"Gst'[%d,%d]:\tNA\t P-value:\tNA\t",x,y);
                  }
                  z++;
                }
              }
               */
            }
          }
          if(include_unknown->value() == 0) {
            for(x=0;x<npops->value()-1/*!outgroup_presence*/;x++) {
              if((*vint_perpop_nsam)[x]>1) fprintf(file_out,"PiW[%d]:\t%f\t",x,(*stats_piw)[x]);
              else fprintf(file_out,"PiW[%d]:\tNA\t",x);
            }
            if(npops->value()-1/*!outgroup_presence*/ > 1) {
              z=0;
              for(x=0;x<npops->value()-1;x++) {
                for(y=x+1;y<npops->value()-0;y++) {
                  if(y==npops->value()-1) {z++;continue;}
                  fprintf(file_out,"PiA[%d,%d]:\t%f\tPiT[%d,%d]:\t%f\t",x,y,(*stats_pia)[z],x,y,(*stats_piT)[z]);
                  z++;
                }
              }
            }
          }
          else {
            for(x=0;x<npops->value()-1/*!outgroup_presence*/;x++) {
              if((*vint_perpop_nsam)[x]>1) fprintf(file_out,"PiW[%d]:\t%f\t",x,(*stats_piw)[x]);
              else fprintf(file_out,"PiW[%d]:\tNA\t",x);
            }
            if(npops->value()-1/*!outgroup_presence*/ > 1) {
              z=0;
              for(x=0;x<npops->value()-1;x++) {
                for(y=x+1;y<npops->value()-0;y++) {
                  if(y==npops->value()-1) {z++;continue;}
                  fprintf(file_out,"PiA[%d,%d]:\t%f\tPiT[%d,%d]:\t%f\t",x,y,(*stats_pia)[z],x,y,(*stats_piT)[z]);
                  z++;
                }
              }
            }
          }
          if(outgroup_presence==1) {
            for(x=0;x<npops->value()-1/*!outgroup_presence*/;x++) {
              for(y=1;y<(*vint_perpop_nsam)[x];y++) {
                fprintf(file_out,"fr[%d,%d]:\t%ld\t",x,y,(*stats_freq)[x][y]);
              }
            }
          }
          else {
            for(x=0;x<npops->value()-1/*!outgroup_presence*/;x++) {
              for(y=1;y<=floor((*vint_perpop_nsam)[x]/2);y++) {
                fprintf(file_out,"fr[%d,%d]:\t%ld\t",x,y,(*stats_freq)[0][y]);
              }
            }
          }
          /*no include because the number of columns is very long*//*
          if(ploidy->value() == HAPLOID && include_unknown->value() == 0) {
            for(y=0;y<stats_nh-!outgroup_presence;y++) {
              for(x=0;x<npops->value()-1;x++) {
                fprintf(file_out,"frHap[%d,hap%02d]:\t%ld\t",x,y,stats_freqh[x][y]);
              }
            }
            for(y=stats_nh-!outgroup_presence;y<sumnsam;y++) {
              for(x=0;x<npops->value()-1;x++) {
                fprintf(file_out,"frHap[%d,hap%02d]:\t0\t",x,y);
              }
            }
          }
          */
          fprintf(file_out,"\n");
        }
      }
    }
  }

  //!added
  if (initsq1 != NULL) {
    free(initsq1);
    initsq1 = NULL;
  }
  /*fflush(file_out);*/
  //return (1);
}


void CCalcMstatspopOutput::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

