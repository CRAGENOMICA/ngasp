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
 *  \brief     CCalcMstatspop.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 16, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_CALCULATIONS_CALC_CCALCMSTATSPOP_H_
#define BACKEND_SRC_CALCULATIONS_CALC_CCALCMSTATSPOP_H_

#include <string>

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

/// ============================================================================
/// CALCULATIONS
/// ============================================================================
#include "../../calculations/ICalculation.h"
#include "../../calculations/CAllCalculations.h"
#include "../../calculations/Calc/CCalcOpenFastaFile.h"
#include "../../calculations/Calc/CCalcMstatspopOpenFastaFile.h"
#include "../../calculations/Calc/CCalcMstatspopOpenMsFile.h"
#include "../../calculations/Calc/CCalcFasta2DnaMatrix.h"
#include "../../calculations/Calc/CCalcDnaMatrix2MatrixPol.h"
#include "../../calculations/Calc/CCalcTOptimalTests.h"
#include "../../calculations/Calc/CCalcR2.h"
#include "../../calculations/Calc/CCalcR2p.h"
#include "../../calculations/Calc/CCalcFreqStats.h"
#include "../../calculations/Calc/CCalcMismatch.h"
#include "../../calculations/Calc/CCalcSxsfss.h"
#include "../../calculations/Calc/CCalcJointFreqDist.h"
#include "../../calculations/Calc/CCalcPiwpiafst.h"
#include "../../calculations/Calc/CCalcHwhafsth.h"
#include "../../calculations/Calc/CCalcFs.h"
#include "../../calculations/Calc/CCalcPermute.h"
#include "../../calculations/Calc/CCalcGFF.h"
#include "../../calculations/Calc/CCalcFileStats.h"
#include "../../calculations/Calc/CCalcOpenFreqSpecFile.h"
#include "../../calculations/Calc/CCalcMaskFileMs.h"
#include "../../calculations/Calc/CCalcEffecNucAndTCGAFreqs.h"
#include "../../calculations/Calc/CCalcLengthamngAndCalcs.h"
#include "../../calculations/Calc/CCalcX.h"
#include "../../calculations/Calc/CCalcY.h"
#include "../../calculations/Calc/CCalcZ.h"
#include "../../calculations/Calc/CCalcArrayOpeX.h"
#include "../../calculations/Calc/CCalcMstatspopOutput.h"
#include "../../calculations/Calc/CCalcArraySumAll.h"
#include "../../calculations/Calc/CCalcDuplicatePopulations.h"
#include "../../calculations/Calc/CCalcOpenTFastaFile.h"
#include "../../calculations/Calc/CCalcOpenEffectSizesFile.h"
#include "../../calculations/Calc/CCalcOpenCoordinatesFile.h"
#include "../../calculations/Calc/CCalcOpenWeightPositionsFile.h"

/// ============================================================================
/// DATA TYPES
/// ============================================================================
#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataChar.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataCharMatrix.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataIntMatrix.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataInt64Vector.h"
#include "../../data_manager/Data/CDataInt64Matrix.h"
#include "../../data_manager/Data/CDataFloat.h"
#include "../../data_manager/Data/CDataFloatVector.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataDoubleVector.h"
#include "../../data_manager/Data/CDataDoubleMatrix.h"
#include "../../data_manager/Data/CDataDoubleCube.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataStringSet.h"
#include "../../data_manager/Data/CDataBoolean.h"

/// ============================================================================
/// CONSTANTS
/// ============================================================================
class CCalcMstatspop : public ICalculation {
 public:
  CCalcMstatspop();
  virtual ~CCalcMstatspop();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

public:
  ICalculation* clone() const { return new CCalcMstatspop(); /*clone*/  }

/// ============================================================================
/// CALCS - MSTATSPOP
/// ============================================================================
  CCalcMstatspopOpenFastaFile                 *calc_mstatspop_open_fasta_;
  CCalcMstatspopOpenMsFile                    *calc_mstatspop_open_ms_;
  CCalcTOptimalTests                          *calc_optimal_tests_;
  CCalcR2                                     *calc_r2_;
  CCalcR2p                                    *calc_r2p_;
  CCalcFreqStats                              *calc_freq_stats_;
  CCalcMismatch                               *calc_mismatch_;
  CCalcSxsfss                                 *calc_sxsfss_;
  CCalcJointFreqDist                          *calc_joint_freq_dist_;
  CCalcPiwpiafst                              *calc_piwpiafst_1_,
                                              *calc_piwpiafst_2_,
                                              *calc_piwpiafst_3_;
  CCalcHwhafsth                               *calc_hwhafsth_1_,
                                              *calc_hwhafsth_2_,
                                              *calc_hwhafsth_3_;
  CCalcFs                                     *calc_fs_;
  CCalcPermute                                *calc_permute_2_,
                                              *calc_permute_3_;
  CCalcGFF                                    *calc_gff_;
  CCalcFileStats                              *calc_file_stats_;
  CCalcOpenFreqSpecFile                       *calc_open_freq_spec_file_;
  CCalcMaskFileMs                             *calc_mask_file_ms_;
  CCalcEffecNucAndTCGAFreqs                   *calc_effec_nuc_TCGA_freqs_;
  CCalcLengthamngAndCalcs                     *calc_lengthamng_and_calcs_;
  CCalcX                                      *calc_x_;
  CCalcY                                      *calc_y_;
  CCalcZ                                      *calc_z_;
  CCalcArrayOpeX                              *calc_array_ope_x_;
  CCalcMstatspopOutput                        *calc_mstatspop_output_;
  CCalcArraySumAll                            *calc_array_sum_all_;
  CCalcDuplicatePopulations                   *calc_duplicate_populations_;
  CCalcOpenTFastaFile                         *calc_tfasta_;
  CCalcOpenEffectSizesFile                    *calc_effect_sizes_;
  CCalcOpenCoordinatesFile                    *calc_coordinates_;
  CCalcOpenWeightPositionsFile                *calc_weight_positions_;
  
/// ============================================================================
/// INPUT DATAS
/// ============================================================================
  CDataStdString      *populations_initial_;  ///
  CDataInt            *ploidy_;               ///
  CDataStdString      *file_out_;             ///
  CDataBoolean        *b_include_unknown_;    ///
  CDataBoolean        *b_force_outgroup_;     ///
  CDataBoolean        *b_outgroup_presence_;  ///
  CDataInt            *formatfile_;           ///
  CDataIntVector      *r2i_ploidies_;         ///
  CDataStdString      *file_mas_;             ///
  CDataInt64          *niter_;                ///
  CDataInt64          *niterdata_;            ///
  CDataFloat          *ms_svratio_;           ///
  CDataInt64          *length_;               ///
  CDataFloat          *freq_revert_;          ///
  CDataStdString      *file_GFF_;             ///
  CDataCharVector     *subset_positions_;     ///
  CDataCharVector     *code_name_;            ///
  CDataCharVector     *genetic_code_;         ///
  CDataStdString      *file_H0f_;             ///
  CDataStdString      *file_H1f_;             ///
  CDataCharVector     *criteria_transcript_;  ///
  CDataStdString      *file_in_;              ///
  CDataIntVector      *sort_nsam_;            /// position in the file
  CDataInt            *output_;               ///
  CDataInt64          *seed_;                 ///
  CDataStdString      *file_wps_;             /// weights
  CDataStdString      *file_wcoord_;          /// coordinates
  CDataStdString      *file_effsz_;           /// effect sizes
  CDataInt64          *window_;               ///
  CDataInt64          *slide_;                ///
  CDataInt            *physical_length_;      ///
  CDataBoolean        *b_mask_print_;         ///
  
  CDataBoolean *keep_intermediate_results;
  
/// ============================================================================
/// INPUT TRANSFORMATIONS
/// ============================================================================
  CDataInt *include_unknown_;
  CDataInt *force_outgroup_;
  CDataInt *outgroup_presence_;
  CDataInt *gfffiles_;
  CDataInt *H0frq_;
  CDataInt *H1frq_;
  CDataInt *mask_print_;
  
/// ============================================================================
/// OUTPUT DATAS
/// ============================================================================
  // These are all statistics that will become the calculation outputs.
  // They have all windows information.
  // Note: mstatspop clears its variables for every window iteration. These
  // variables stores all iteration results. For example: "out_stats_So_" 
  // contains all iteration results from "stats_So_".
  
  CDataStdString    *calc_output_;
  CDataDoubleVector *out_stats_So_;           /// S
  CDataDoubleVector *out_stats_thetaSo_;      /// Theta/nt(Wat) *1
  CDataDoubleVector *out_stats_thetaTo_;      /// Theta/nt(Taj) *2
  CDataDoubleVector *out_stats_thetaFL_;      /// Theta/nt(Fu&Li)
  CDataDoubleVector *out_stats_thetaFW_;      /// Theta/nt(Fay&Wu)
  CDataDoubleVector *out_stats_thetaL_;       /// Theta/nt(Zeng)
  CDataDoubleVector *out_stats_thetaSA_;      /// Theta/nt(Achaz,Wat)
  CDataDoubleVector *out_stats_thetaTA_;      /// Theta/nt(Achaz,Taj)
  CDataDoubleVector *out_stats_K_;            /// Divergence/nt
  CDataDoubleVector *out_stats_thetaTHKY_;    /// Theta/nt(Taj)HKY
  CDataDoubleVector *out_stats_KHKY_;         /// DivergenceHKY
  CDataDoubleVector *out_stats_thetaS_;       /// Theta/nt(Wat)  *1
  CDataDoubleVector *out_stats_thetaT_;       /// Theta/nt(Taj)  *2
  CDataDoubleVector *out_stats_hapw_;         /// HapW
  CDataIntVector    *out_stats_nhpop_;        /// nHap
  CDataDoubleVector *out_stats_Dtaj_;         /// Tajima D
  CDataDoubleVector *out_stats_Dfl_;          /// Fu&Li D
  CDataDoubleVector *out_stats_Ffl_;          /// Fu&Li F
  CDataDoubleVector *out_stats_Hnfw_;         /// Fay&Wu norm H
  CDataDoubleVector *out_stats_Ez_;           /// Zeng E
  CDataDoubleVector *out_stats_Yach_;         /// Achaz Y
  CDataDoubleVector *out_stats_FH_;           /// 
  CDataDoubleVector *out_stats_Fs_;           /// Fs
  CDataDoubleVector *out_stats_mdsd_;         /// SDev
  CDataDoubleVector *out_stats_mdg1_;         /// Skewness  
  CDataDoubleVector *out_stats_mdg2_;         /// Kurtosis
  CDataDoubleVector *out_stats_fst1all_;      /// Fst1
  CDataDoubleVector *out_stats_fsth_;         /// FstH
  CDataDoubleVector *out_stats_fstHKY_;       /// FstHKY
  CDataDoubleVector *out_stats_piwHKY_;       /// PiWHKY
  CDataDoubleVector *out_stats_piaHKY_;       /// PiAHKY
  
/// ============================================================================
/// DATAS
/// ============================================================================
  CDataInt64          *npops_;                ///
  CDataIntVector      *vint_perpop_nsam_;     ///
  CDataDouble         *length_al_;            ///
  CDataInt            *int_total_nsam_order_; ///
  CDataInt            *numPloidies_;          ///
  CDataInt            *result_;               /// It stores the calculation result value. Not all calculations use it.
  CDataStringSet      *fasta_;                ///
  CDataIntVector      *vint_perpop_nsam_iter_;  ///
  CDataInt64          *npops_iter_;           ///
  CDataInt64          *int_total_nsam_iter_;  ///
  CDataCharVector     *dna_matrix_;           ///
  CDataDoubleVector   *matrix_sizepos_;       ///
  CDataDoubleVector   *matrix_segrpos_;       ///
  CDataCharVector     *matrix_pol_;           /// the matrix of SNPs alignment data
  CDataCharVector     *matrix_pol_tcga_;      /// the matrix of SNPs alignment data with four nucleotides
  CDataInt64Vector    *frequencies_;          /// frequency of the segregating site
  CDataInt64Vector    *positions_;            /// position of the segregating site
  CDataInt64Vector    *sites_;                ///
  CDataInt64Vector    *sanc_;                 ///
  CDataCharVector     *matrix_perm_;          /// matrix_pol permuted
  CDataIntVector      *nsam2_;                ///
  CDataIntVector      *psam2_;                ///
  CDataInt            *argc_;                 ///
  CDataFloatVector    *vector_mask_;          ///
  CDataDouble         *length_mask_;          ///
  CDataDouble         *length_mask_real_;     ///
  CDataIntVector      *matrix_mask_;          ///
  CDataDoubleVector   *vector_priors_;        ///
  CDataInt            *npriors_;              ///
  CDataDoubleVector   *sum_sam_mask_;         ///
  CDataInt64          *length_seg_;           ///
  CDataInt64Vector    *mhitbp_;               ///
  CDataCharMatrix     *names2_;               ///
  CDataInt64          *n_site_;               ///
  CDataCharVector     *DNA_matr2_;            ///
  CDataInt            *n_samp_;               ///
  CDataInt            *flaghky_;              ///
  CDataInt            *flaghky0_;              ///
  CDataDoubleMatrix   *jfd_;                  ///
  CDataIntMatrix      *nfd_;                  ///
  CDataInt64          *li_;                   ///
  CDataDoubleVector   *anx_;                  ///
  CDataDoubleVector   *bnx_;                  ///
  CDataDoubleVector   *anxo_;                 ///
  CDataDoubleVector   *bnxo_;                 ///
  CDataDoubleMatrix   *lengthamng_;           ///
  CDataDouble         *missratio_;            ///
  CDataDoubleVector   *nsites1_pop_;          ///
  CDataDoubleVector   *nsites2_pop_;          ///
  CDataDoubleVector   *nsites3_pop_;          ///
  CDataDoubleVector   *nsites1_pop_outg_;     ///
  CDataDoubleVector   *nsites2_pop_outg_;     ///
  CDataDoubleVector   *nsites3_pop_outg_;     ///
  CDataDoubleVector   *sum_sam_;              ///
  CDataDouble         *svratio_;              ///
  CDataDoubleMatrix   *tcga_;                 ///
  CDataInt64          *length_al_real_;       ///
  CDataInt64          *nmhits_;               ///
  CDataInt64Vector    *matrix_sv_;            ///
  CDataInt            *z_pos_;                ///
  CDataInt64Vector    *mdw_reg_lengths_;      ///
  CDataInt64          *int_total_nsam_;       ///
  CDataInt            *location_missing_ms_;  /// It was an user input.
  CDataInt            *kind_length_;          /// It was an user input.
  CDataDouble         *freq_missing_ms_;      /// It was an user input.
  CDataInt            *n_ccov_;               /// It was an user input.
  CDataFloatVector    *wV_;                   /// weight at variant (effect sizes). (not yet functional although we can recover)
  CDataInt64Vector    *Pp_;                   /// number of position (for effect sizes). (not used)
  CDataInt64          *nV_;                   /// number of variants at file ov variant weights (effect sizes). (not used)
  CDataInt64Vector    *wgenes_;               /// init and end coordinates
  CDataInt64          *nwindows_;             /// number of fragments
  CDataFloatVector    *wP_;                   /// weight for each position
  CDataFloatVector    *wPV_;                  /// weight for the variant at each position
  CDataInt64          *wlimit_end_;           ///
  CDataInt64          *welimit_end_;          ///
  CDataInt            *nsamuser_eff_;         ///
  CDataInt64          *beg_;                  ///
  
/// ============================================================================
/// STATS
/// ============================================================================
  CDataDoubleVector   *stats_piw_[2];         ///
  CDataDoubleVector   *stats_pia_[2];         ///
  CDataDoubleVector   *stats_piT_[2];         ///
  CDataDoubleVector   *stats_piant_[2];       ///
  CDataDoubleVector   *stats_piTnt_[2];       ///
  CDataDoubleVector   *stats_fst_[2];         ///
  CDataDoubleVector   *stats_piwHKY_[2];      ///
  CDataDoubleVector   *stats_piaHKY_[2];      ///
  CDataDoubleVector   *stats_piTHKY_[2];      ///
  CDataDoubleVector   *stats_fstHKY_[2];      ///
  CDataDoubleVector   *stats_fst1all_[2];     ///
  CDataDoubleVector   *stats_Gst_[2];         ///
  CDataDoubleVector   *stats_hapw_[2];        ///
  CDataDoubleVector   *stats_hapa_[2];        ///
  CDataDoubleVector   *stats_hapT_[2];        ///
  CDataDoubleVector   *stats_fsth_[2];        ///
  CDataDoubleVector   *stats_fsth1all_[2];    ///
  CDataDouble         *stats_fstALL_[2];      ///
  CDataDouble         *stats_fsthALL_[2];     ///
  CDataDouble         *stats_GstALL_[2];      ///
  CDataDoubleVector   *stats_S_[2];           ///
  CDataDoubleVector   *stats_So_[2];          ///
  CDataDoubleVector   *stats_thetaS_[2];      ///
  CDataDoubleVector   *stats_thetaSo_[2];     ///
  CDataDoubleVector   *stats_thetaT_[2];      ///
  CDataDoubleVector   *stats_thetaTo_[2];     ///
  CDataDoubleVector   *stats_thetaTHKY_[2];   ///
  CDataDoubleVector   *stats_thetaFL_[2];     ///
  CDataDoubleVector   *stats_thetaFW_[2];     ///
  CDataDoubleVector   *stats_thetaL_[2];      ///
  CDataDoubleVector   *stats_thetaSA_[2];     ///
  CDataDoubleVector   *stats_thetaTA_[2];     ///
  CDataDoubleVector   *stats_K_[2];           ///
  CDataDoubleVector   *stats_KHKY_[2];        ///
  CDataDoubleVector   *stats_Dtaj_[2];        ///
  CDataDoubleVector   *stats_Dfl_[2];         ///
  CDataDoubleVector   *stats_Ffl_[2];         ///
  CDataDoubleVector   *stats_Hnfw_[2];        ///
  CDataDoubleVector   *stats_Ez_[2];          ///
  CDataDoubleVector   *stats_Yach_[2];        ///
  CDataDoubleVector   *stats_FH_[2];          ///
  CDataDoubleVector   *stats_R2_[2];          ///
  CDataDoubleVector   *stats_Fs_[2];          ///
  CDataInt64Vector    *stats_Rm_[2];          ///
  CDataDoubleVector   *stats_ZnA_[2];         ///
  CDataInt64Matrix    *stats_freq_[2];        ///
  CDataInt            *stats_nh_[2];          ///
  CDataIntVector      *stats_nhpop_[2];       ///
  CDataInt64Matrix    *stats_freqh_[2];       ///
  CDataDoubleVector   *stats_length_[2];      ///
  CDataDoubleVector   *stats_length2_[2];     ///
  CDataDoubleMatrix   *stats_lengthamng_[2];  ///
  CDataDouble         *stats_total_length_[2];       ///
  CDataDouble         *stats_total_real_length_[2];  ///
  CDataDouble         *stats_total_svratio_[2];      ///
  CDataDoubleVector   *stats_total_tcga_[2];  ///
  CDataDoubleMatrix   *stats_tcga_[2];        ///
  CDataDoubleCube     *stats_sv_[2];          ///
  CDataDoubleCube     *stats_svT_[2];         ///
  CDataInt64          *stats_nmhits_[2];      ///
  CDataDoubleMatrix   *stats_H0freq_[2];      /// Optimal Tests ................
  CDataDoubleMatrix   *stats_H1freq_[2];      ///
  CDataDoubleVector   *stats_thetaH0_[2];     ///
  CDataDoubleVector   *stats_thetaH1_[2];     ///
  CDataDoubleVector   *stats_ToH0_ii_[2];     ///
  CDataDoubleVector   *stats_ToH0_00_[2];     ///
  CDataDoubleVector   *stats_To_ii_[2];       ///
  CDataDoubleVector   *stats_To_00_[2];       ///
  CDataDoubleVector   *stats_To_i0_[2];       ///
  CDataDoubleVector   *stats_To_Qc_ii_[2];    ///
  CDataDoubleVector   *stats_To_Qw_ii_[2];    ///
  CDataDoubleVector   *stats_To_Lc_ii_[2];    ///
  CDataDoubleVector   *stats_mdsd_[2];        /// Mismatch .....................
  CDataDoubleVector   *stats_mdg1_[2];        ///
  CDataDoubleVector   *stats_mdg2_[2];        ///
  CDataDoubleMatrix   *stats_mdw_[2];         ///
  CDataDoubleMatrix   *stats_linefreq_[2];    /// JointFreqDist ................
  CDataDoubleVector   *stats_anx_[2];         ///
  CDataDoubleVector   *stats_bnx_[2];         ///
  CDataDoubleVector   *stats_anxo_[2];        ///
  CDataDoubleVector   *stats_bnxo_[2];        ///
  CDataDoubleMatrix   *stats_R2p_[2];         ///

/// ============================================================================
/// PROBS
/// ============================================================================
  CDataInt64Vector    *piter_i_;              ///
  CDataInt64Vector    *piter_ih_;             ///
  CDataInt64Vector    *piter_igh_;            ///
  CDataInt64Vector    *piter_i1_;             ///
  CDataInt64Vector    *piter_ih1_;            ///
  CDataInt64Vector    *piter_niteri_;         ///
  CDataInt64Vector    *piter_niterih_;        ///
  CDataInt64Vector    *piter_niterigh_;       ///
  CDataInt64Vector    *piter_niteri1_;        ///
  CDataInt64Vector    *piter_niterih1_;       ///
  CDataInt64          *piter_iall_;           ///
  CDataInt64          *piter_ihall_;          ///
  CDataInt64          *piter_ighall_;         ///
  CDataInt64          *piter_niteriall_;      ///
  CDataInt64          *piter_niterihall_;     ///
  CDataInt64          *piter_niterighall_;    ///


  
  void ChangeUserInputsIfNecessary(void);
  void AddOneOutgroupIfItIsNotPresent(void);
  void CreateThePopulationsVector(void);
  void MultiplyPopulationsDependingOnPloidy(void);
  void GetSumOfPopulations(void);
  void CalcMdwRegLengths(void);
  void DataMemoryAllocation(long int npops,
                            long int int_total_nsam,
                            int outgroup_presence);
  void DeleteIterationVariables(void);
  void ShowMstatspopInformation(void);
  void Print(std::string message);
  void OpenAlternativeAndFreqSpectrumFile(void);
  void ReadFastaFile(void);
  bool ReadTFastaFile(void);
  void ReadEffectSizesFile(void);
  void ReadCoordinatesFile(void);
  void ReadWeightPositionsFile(void);
  void FilterDnaMatrixWithGFFFile(void);
  void CalculateStats(void);
  void MsMaskFile(void);
  void OpenMsFile(void);
  void CalcX(void);
  void CalEffectiveNucleotidesAndTCGAFreqs(void);
  void IncludeLengthMngAndCalculations(void);
  void CalcSxsfss(void);
  void CalcJointFreqDistribution(void);
  void CalcPiwpiafst_1(void);
  void CalcFrequencyStats(void);
  void CalcOptimalTests(void);
  void CalcR2(void);
  void CalcR2p(void);
  void CalcMismatch(void);
  void CalcHwhafsth_1(void);
  void CalcFs(void);
  void Permute_2(void);
  void CalcPiwpiafst_2(void);
  void CalcHwhafsth_2(void);
  void CalcY(void);
  void Permute_3(void);
  void CalcPiwpiafst_3(void);
  void CalcHwhafsth_3(void);
  void CalcZ(void);
  void PrintOutput(void);
  
  void ConcatenateIterationResults(void);
};

#endif  // BACKEND_SRC_CALCULATIONS_CALC_CCALCMSTATSPOP_H_
