/*
 * ngasp, a computational solution for performing next generation analysis of 
 * sequence polymorphisms using NGS data.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
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
 *  \brief     CDataMpileup.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      April 25, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATA_MANAGER_DATA_CDATAMPILEUP_H_
#define	DATA_MANAGER_DATA_CDATAMPILEUP_H_

#include <string>

#include "../IDataValue.h"

#include <bam_plcmd.h>
#include <export.h>
#include <sam_opts.h>

class CDataMpileup : public IDataValue<std::string> {
 public:
  void set_value_string(std::string value) {
    set_value(value);
  } 
  
  public:
  mplp_conf_t mplp_;
 
 public:
  CDataMpileup() : IDataValue(KeyString::DATA_MPILEUP, "") {
    memset(&mplp_, 0, sizeof(mplp_conf_t));
    mplp_.min_baseQ = 13;
    mplp_.capQ_thres = 0;
    mplp_.max_depth = 250; mplp_.max_indel_depth = 250;
    mplp_.openQ = 40; mplp_.extQ = 20; mplp_.tandemQ = 100;
    mplp_.min_frac = 0.002; mplp_.min_support = 1;
    mplp_.flag = MPLP_NO_ORPHAN | MPLP_REALN | MPLP_SMART_OVERLAPS;
    mplp_.argc = 0;
    mplp_.argv = NULL;
    mplp_.rflag_filter = BAM_FUNMAP | BAM_FSECONDARY | BAM_FQCFAIL | BAM_FDUP;
    mplp_.output_fname = NULL;
    sam_global_args_init(&mplp_.ga);    
  }
  
  virtual ~CDataMpileup() {}

  IData * clone() const { return new CDataMpileup(); /*clone*/ }
};

#endif  // DATA_MANAGER_DATA_CDATAMPILEUP_H_
