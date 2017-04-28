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

/*
 * File:   CDnaTools.cpp
 * Author: jjene
 *
 * Created on May 19, 2015, 3:06 PM
 */

#include "CDnaTools.h"

CDnaTools::CDnaTools() {
  // ===========================================================================
  //         file char | code ploidy 1 | code ploidy 2
  // ===========================================================================
  char2dnacode_['T'] = new DnaCode('1',   '1', '1');
  char2dnacode_['t'] = new DnaCode('1',   '1', '5');
  char2dnacode_['U'] = new DnaCode('1',   '1', '1');
  char2dnacode_['u'] = new DnaCode('1',   '1', '5');
  char2dnacode_['C'] = new DnaCode('2',   '2', '2');
  char2dnacode_['c'] = new DnaCode('2',   '2', '5');
  char2dnacode_['G'] = new DnaCode('3',   '3', '3');
  char2dnacode_['g'] = new DnaCode('3',   '3', '5');
  char2dnacode_['A'] = new DnaCode('4',   '4', '4');
  char2dnacode_['a'] = new DnaCode('4',   '4', '5');
  char2dnacode_['N'] = new DnaCode('5',   '5', '5');
  char2dnacode_['n'] = new DnaCode('5',   '5', '5');
  char2dnacode_['?'] = new DnaCode('5',   '5', '5');
  char2dnacode_['-'] = new DnaCode('6',   '6', '6');
  char2dnacode_['W'] = new DnaCode('w',   '1', '4');
  char2dnacode_['w'] = new DnaCode('w',   '1', '4');
  char2dnacode_['M'] = new DnaCode('m',   '2', '4');
  char2dnacode_['m'] = new DnaCode('m',   '2', '4');
  char2dnacode_['R'] = new DnaCode('r',   '3', '4');
  char2dnacode_['r'] = new DnaCode('r',   '3', '4');
  char2dnacode_['Y'] = new DnaCode('y',   '1', '2');
  char2dnacode_['y'] = new DnaCode('y',   '1', '2');
  char2dnacode_['K'] = new DnaCode('k',   '1', '3');
  char2dnacode_['k'] = new DnaCode('k',   '1', '3');
  char2dnacode_['S'] = new DnaCode('s',   '2', '3');
  char2dnacode_['s'] = new DnaCode('s',   '2', '3');
  char2dnacode_['B'] = new DnaCode('5',   '5', '5');
  char2dnacode_['b'] = new DnaCode('5',   '5', '5');
  char2dnacode_['d'] = new DnaCode('5',   '5', '5');
  char2dnacode_['D'] = new DnaCode('5',   '5', '5');
  char2dnacode_['h'] = new DnaCode('5',   '5', '5');
  char2dnacode_['H'] = new DnaCode('5',   '5', '5');
  char2dnacode_['v'] = new DnaCode('5',   '5', '5');
  char2dnacode_['V'] = new DnaCode('5',   '5', '5');


  // ===========================================================================
  // file char | DnaCode Ploidy 1x |  2xy  | Nitrogen Base
  // ===========================================================================
  dnacode2base_['1'] = NitrogenBase::Thymine;
  dnacode2base_['2'] = NitrogenBase::Cytosine;
  dnacode2base_['3'] = NitrogenBase::Guanine;
  dnacode2base_['4'] = NitrogenBase::Adenine;
  dnacode2base_['5'] = NitrogenBase::Missing;
  dnacode2base_['6'] = NitrogenBase::Gap;
  dnacode2base_['w'] = NitrogenBase::Weak;
  dnacode2base_['m'] = NitrogenBase::Amino;
  dnacode2base_['r'] = NitrogenBase::Purine;
  dnacode2base_['y'] = NitrogenBase::Pyrimidine;
  dnacode2base_['k'] = NitrogenBase::Keto;
  dnacode2base_['s'] = NitrogenBase::Strong;


  // ===========================================================================
  // Nitrogen Base | Nitrogen Base Char Code
  // ===========================================================================
  base2dnacode_[NitrogenBase::Thymine]    = '1';
  base2dnacode_[NitrogenBase::Cytosine]   = '2';
  base2dnacode_[NitrogenBase::Guanine]    = '3';
  base2dnacode_[NitrogenBase::Adenine]    = '4';
  base2dnacode_[NitrogenBase::Missing]    = '5';
  base2dnacode_[NitrogenBase::Gap]        = '6';
  base2dnacode_[NitrogenBase::Weak]       = 'w';
  base2dnacode_[NitrogenBase::Amino]      = 'm';
  base2dnacode_[NitrogenBase::Purine]     = 'r';
  base2dnacode_[NitrogenBase::Pyrimidine] = 'y';
  base2dnacode_[NitrogenBase::Keto]       = 'k';
  base2dnacode_[NitrogenBase::Strong]     = 's';


  // ===========================================================================
  // Genetic Code Name | Genetic Code
  // ===========================================================================
  genetic_codes_["Nuclear_Universal"] =
          "FFLLSSSSYY**CC*WLLLLPPPPHHQQRRRRIIIMTTTTNNKKSSRRVVVVAAAADDEEGGGG";
  genetic_codes_["mtDNA_Drosophila"]  =
          "FFLLSSSSYY**CCWWLLLLPPPPHHQQRRRRIIMMTTTTNNKKSSSSVVVVAAAADDEEGGGG";
  genetic_codes_["mtDNA_Mammals"]     =
          "FFLLSSSSYY**CCWWLLLLPPPPHHQQRRRRIIMMTTTTNNKKSS**VVVVAAAADDEEGGGG";
}

CDnaTools::~CDnaTools() {
  for (std::map<char, DnaCode *>::iterator it = char2dnacode_.begin(); it != char2dnacode_.end(); ++it) {
    if (it->second != NULL) {
      delete it->second;
      it->second = NULL;
    }
  }
}

