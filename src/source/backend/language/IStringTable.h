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
 *  \brief     IStringTable.h
 *  \details   This class uses the Singleton pattern.
 *             That means that the class has only one instance, and provide a
 *             global point of access it.
 *             This patter can be used only because this class is ReadOnly and
 *             it won't be a problem when using threads.
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 13, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_LANGUAGE_ISTRINGTABLE_H_
#define BACKEND_SRC_LANGUAGE_ISTRINGTABLE_H_

#include <map>
#include <string>
#include <assert.h>

#include "extern.h"

#define YES          1
#define NO           0

#define FASTA_FILE   0
#define NBRF_FILE    0
#define MS_FILE      1
#define MS_X_FILE    2
#define TFASTA_FILE  3
#define HAPLOID      1
#define DIPLOID      2

#define NA_VALUE     -10000
 
enum OutputEncoding {
  UNDEFINED_ENCODING  = -1,
  ENGLISH_COL  = 0,  // you can use color codes for output like "\033[1m" and
                     // characters like "───"
  ENGLISH_BN   = 1,  // you cannot use colores and you can only use basic ascii
                     //characters like "---".
  ENGLISH_HTML = 2   // you can use html tags.
};

template <class T>
class IStringTable {
 public:
  IStringTable() {
    encoding_ = OutputEncoding::UNDEFINED_ENCODING;
  }
  virtual ~IStringTable() {}

 protected:
  std::map <T, std::string> strings_[3];
  OutputEncoding encoding_;

 protected:
  void FillOtherLanguages(void) {
    
    
    for(auto it = strings_[ENGLISH_COL].begin();
      it != strings_[ENGLISH_COL].end();
      it++) {

      // it->first = key
      // it->second = value

      // If ENGLISH_BN value is "" then set ENGLISH_COL value to ENGLISH_BN.

      if (strings_[ENGLISH_BN][it->first] == "") {
        strings_[ENGLISH_BN][it->first] = it->second;
      }

      // If ENGLISH_HTML value is "" then set ENGLISH_COL value to ENGLISH_HTML.

      if (strings_[ENGLISH_HTML][it->first] == "") {
        strings_[ENGLISH_HTML][it->first] = it->second;
      }

      // Convert this value "[EMPTY ME ON RUNTIME]" to "" at runtime. To every
      // encoding type:

      if (strings_[ENGLISH_COL][it->first] == "[EMPTY ME ON RUNTIME]") {
        strings_[ENGLISH_COL][it->first] = "";
      }
      if (strings_[ENGLISH_BN][it->first] == "[EMPTY ME ON RUNTIME]") {
        strings_[ENGLISH_BN][it->first] = "";
      }
      if (strings_[ENGLISH_HTML][it->first] == "[EMPTY ME ON RUNTIME]") {
        strings_[ENGLISH_HTML][it->first] = "";
      }
    }
  }


 public:
  inline OutputEncoding encoding(void) const {
    return encoding_;
  }

  inline void set_encoding(const OutputEncoding & encoding) {
    encoding_ = encoding;
  }

  inline void set_encoding(const std::string & encoding) {
    if (encoding == "english_col") {
      encoding_ = OutputEncoding::ENGLISH_COL;
    } else {
      if (encoding == "english_bn") {
        encoding_ = OutputEncoding::ENGLISH_BN;
      } else {
        if (encoding == "english_html") {
          encoding_ = OutputEncoding::ENGLISH_HTML;
        }
      }
    }
  }

  inline std::string get_strings(T string_id) {
    assert(encoding_ != OutputEncoding::UNDEFINED_ENCODING && "assert(encoding_ != OutputEncoding::UNDEFINED_ENCODING)");

    return strings_[encoding_][string_id];
  }

  inline char get_char(const T & string_id) {
    assert(encoding_ != OutputEncoding::UNDEFINED_ENCODING && "assert(encoding_ != OutputEncoding::UNDEFINED_ENCODING)");

    char ch = '\x0';
    if (strings_[encoding_][string_id].length() > 0) {
      ch = strings_[encoding_][string_id][0];
    }
    return ch;
  }
};

#endif  // BACKEND_SRC_LANGUAGE_ISTRINGTABLE_H_
