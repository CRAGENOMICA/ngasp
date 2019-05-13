/*
 * ngaSP: the computational solution for next generation analysis of 
 * Sequence Polymorphisms.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
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
 *  \brief     CCMDmstatspop.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      March 30, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDMSTATSPOP_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDMSTATSPOP_H_

#include <string>

#include "../ICommand.h"

#include "../../calculations/ICalculation.h"
#include "../../calculations/CAllCalculations.h"

/// ============================================================================
/// CALCULATIONS
/// ============================================================================
#include "../../calculations/Calc/CCalcMstatspop.h"

/// ============================================================================
/// DATA TYPES
/// ============================================================================
#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../data_manager/Data/CDataCharVector.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataIntVector.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataFloat.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataBoolean.h"

// CCMDmstatspop
class CCMDmstatspop: public ICommand {
 public:
  CCMDmstatspop();
  ~CCMDmstatspop();

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 private:
/// ============================================================================
/// CALCS
/// ============================================================================
  CCalcMstatspop *calc_mstatspop_;

/// ============================================================================
/// INPUT DATAS
/// ============================================================================
  CDataStdString      *populations_initial_;  ///
  CDataInt            *ploidy_;               ///
  CDataStdString      *out_file_name_;             ///
  CDataBoolean        *b_include_unknown_;    ///
  CDataBoolean        *b_force_outgroup_;     ///
  CDataBoolean        *b_outgroup_presence_;  ///
  CDataStdString      *formatfile_;           ///
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
  //CDataStdString      *file_effsz_;           /// effect sizes
  CDataInt64          *window_;               ///
  CDataInt64          *slide_;                ///
  CDataInt            *physical_length_;      ///
  CDataBoolean        *b_mask_print_;         ///
  CDataStdString      *scaffold_name_;     ///
  
  CDataIntVector      *kind_length_;                                           
  CDataFloat          *freq_missing_ms_;                                    
  CDataInt64          *n_ccov_;                                           
  CDataFloat          *location_missing_ms_;                             
  CDataInt64          *first_slide_;                                     


  CDataBoolean *keep_intermediate_results;
  
/// ============================================================================
/// INPUT TRANSFORMATIONS
/// ============================================================================
/*  CDataInt *include_unknown_;
  CDataInt *force_outgroup_;
  CDataInt *outgroup_presence_;
  CDataInt *gfffiles_;
  CDataInt *H0frq_;
  CDataInt *H1frq_;
  CDataInt *mask_print_;*/
  
/// ============================================================================
/// OUTPUT DATAS
/// ============================================================================
  // These are all statistics that will become the calculation outputs.
  // They have all windows information.
  // Note: mstatspop clears its variables for every window iteration. These
  // variables stores all iteration results. For example: "out_stats_So_" 
  // contains all iteration results from "stats_So_".
  
  CDataTextFile    *calc_output_;

/// ============================================================================
/// DATAS
/// ============================================================================
/*  CDataStdString      *populations_initial_;  ///
  CDataInt            *ploidy_;               ///
  CDataBoolean        *b_include_unknown_;    ///
  CDataStdString      *file_out_;             ///
  CDataBoolean        *b_force_outgroup_;     ///
  CDataBoolean        *b_outgroup_presence_;  ///
  CDataStdString      *formatfile_;           /// Necesario para el wrapper
  //CDataInt            *formatfile_;           ///
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
  CDataStdString      *all_command_line_;     ///
  CDataStdString      *file_in_;              ///
  CDataIntVector      *sort_nsam_;            /// position in the file
  CDataInt            *output_;               ///
  CDataInt64          *seed_;                 ///
  CDataInt64          *idum_;                 ///
  CDataStdString      *file_wps_;             ///
  CDataStdString      *file_wcoord_;          ///
  CDataInt64          *window_;               ///
  CDataInt64          *slide_;                ///
  CDataInt            *physical_length_;      ///
  //CDataStdString      *file_effsz_;           ///
  CDataBoolean        *b_mask_print_;         ///
  
  CDataStdString      *calc_output_;
  CDataDoubleVector   *out_stats_So_;         /// S
  CDataDoubleVector   *out_stats_thetaSo_;    /// Theta/nt(Wat) *1
  CDataDoubleVector   *out_stats_thetaTo_;    /// Theta/nt(Taj) *2
  CDataDoubleVector   *out_stats_thetaFL_;    /// Theta/nt(Fu&Li)
  CDataDoubleVector   *out_stats_thetaFW_;    /// Theta/nt(Fay&Wu)
  CDataDoubleVector   *out_stats_thetaL_;     /// Theta/nt(Zeng)
  CDataDoubleVector   *out_stats_thetaSA_;    /// Theta/nt(Achaz,Wat)
  CDataDoubleVector   *out_stats_thetaTA_;    /// Theta/nt(Achaz,Taj)
  CDataDoubleVector   *out_stats_K_;          /// Divergence/nt
  CDataDoubleVector   *out_stats_thetaTHKY_;  /// Theta/nt(Taj)HKY
  CDataDoubleVector   *out_stats_KHKY_;       /// DivergenceHKY
  CDataDoubleVector   *out_stats_thetaS_;     /// Theta/nt(Wat)  *1
  CDataDoubleVector   *out_stats_thetaT_;     /// Theta/nt(Taj)  *2
  CDataDoubleVector   *out_stats_hapw_;       /// HapW
  CDataIntVector      *out_stats_nhpop_;      /// nHap
  CDataDoubleVector   *out_stats_Dtaj_;       /// Tajima D
  CDataDoubleVector   *out_stats_Dfl_;        /// Fu&Li D
  CDataDoubleVector   *out_stats_Ffl_;        /// Fu&Li F
  CDataDoubleVector   *out_stats_Hnfw_;       /// Fay&Wu norm H
  CDataDoubleVector   *out_stats_Ez_;         /// Zeng E
  CDataDoubleVector   *out_stats_Yach_;       /// Achaz Y
  CDataDoubleVector   *out_stats_FH_;         /// 
  CDataDoubleVector   *out_stats_Fs_;         /// Fs
  CDataDoubleVector   *out_stats_mdsd_;       /// SDev
  CDataDoubleVector   *out_stats_mdg1_;       /// Skewness  
  CDataDoubleVector   *out_stats_mdg2_;       /// Kurtosis
  CDataDoubleVector   *out_stats_fst1all_;    /// Fst1
  CDataDoubleVector   *out_stats_fsth_;       /// FstH
  CDataDoubleVector   *out_stats_fstHKY_;     /// FstHKY
  CDataDoubleVector   *out_stats_piwHKY_;     /// PiWHKY
  //CDataDoubleVector   *out_stats_piaHKY_;     /// PiAHKY          
  */
/// ============================================================================
/// COMMAND BEHAVIOURS
/// ============================================================================
  bool run_only_help_;                        /// True if User only wants to watch the command help
};

#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDMSTATSPOP_H_


