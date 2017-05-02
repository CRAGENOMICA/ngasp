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

/*
 * File:   CDnaTools.h
 * Author: jjene
 *
 * Created on May 19, 2015, 3:06 PM
 */

#ifndef CDNATOOLS_H
#define	CDNATOOLS_H

#include <string>
#include <map>
#include <seqan/seq_io.h>  //!prev_disabled

class CDnaTools {
 public:
  CDnaTools();
  virtual ~CDnaTools();

 public:
  enum NitrogenBase {
    Undefined  = 0,
    Thymine    = 1,
    Cytosine   = 2,
    Guanine    = 3,
    Adenine    = 4,
    Missing    = 5,
    Gap        = 6,
    Weak       = 7,
    Amino      = 8,
    Purine     = 9,
    Pyrimidine = 10,
    Keto       = 11,
    Strong     = 12,
  };

 public:
  struct DnaCode {
    char code_ploidy_1_;
    char code_ploidy_2a_;
    char code_ploidy_2b_;
    NitrogenBase base_;

    DnaCode(char code_ploidy_1,
            char code_ploidy_2a,
            char code_ploidy_2b) {
      code_ploidy_1_ = code_ploidy_1;
      code_ploidy_2a_ = code_ploidy_2a;
      code_ploidy_2b_ = code_ploidy_2b;
    }
  };

 private:
  std::map<char, DnaCode *> char2dnacode_;
  std::map<char, NitrogenBase> dnacode2base_;
  std::map<NitrogenBase, char> base2dnacode_;

 public:
  std::map<std::string, std::string> genetic_codes_;

 public:
  inline DnaCode *char2dnacode(char c) const { return char2dnacode_.at(c); }
  inline NitrogenBase dnacode2base(char c) const { return dnacode2base_.at(c); }
  inline char base2dnacode(NitrogenBase b) const {
    return base2dnacode_.at(b);
  }
};

#endif	/* CDNATOOLS_H */
