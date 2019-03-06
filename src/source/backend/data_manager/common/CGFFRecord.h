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
 *  \brief     CGFFFile.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_DATA_MANAGER_COMMON_CGFFRECORD_H_
#define BACKEND_SRC_DATA_MANAGER_COMMON_CGFFRECORD_H_

#include <string>
#include <list>

class CGFFRecord {
 public:
  CGFFRecord() {}
  
  enum class StrandType : char {
       FORWARD = '+',
       REVERSE = '-',
       STRAND_NOT_DEFINED = '.'
  };

  enum class FrameType : char {
       BASE_1_IS_FIRST_CODON_BASE = '0',
       BASE_2_IS_FIRST_CODON_BASE = '1',
       BASE_3_IS_FIRST_CODON_BASE = '2',
       FRAME_NOT_DEFINED = '.'
  };  

 private:
  std::string seqname_;    // name of the chromosome or scaffold; chromosome
                           // names can be given with or without the 'chr' 
                           // prefix. Important note: the seqname must be one 
                           // used within Ensembl, i.e. a standard chromosome 
                           // name or an Ensembl identifier such as a scaffold 
                           // ID, without any additional content such as species
                           // or assembly. See the example GFF output below.
  std::string source_;     // name of the program that generated this feature, 
                           // or the data source (database or project name)
  std::string feature_;    // feature type name, e.g.Gene, Variation, Similarity
  long int start_;          // Start position of the feature, with sequence 
                           // numbering starting at 1.
  long int end_;            // End position of the feature, with sequence 
                           // numbering starting at 1.
  float score_;            // A floating point value.
  StrandType strand_;      // defined as + (forward) or - (reverse).
  FrameType frame_;        // One of '0', '1' or '2'. '0' indicates that the 
                           // first base of the feature is the first base of a 
                           // codon, '1' that the second base is the first base 
                           // of a codon, and so on..
  std::list<std::string> attribute_;  // A semicolon-separated list of tag-value
                           // pairs, providing additional information about each 
                           // feature.
  
 public:
  std::string seqname(void) const { return seqname_; }
  void set_seqname(const std::string & seqname) { seqname_ = seqname; }
  
  std::string source(void) const { return source_; }
  void set_source(const std::string & source) { source_ = source; }
  
  std::string feature(void) const { return feature_; }
  void set_feature(const std::string & feature) { feature_ = feature; }
  
  long int start(void) const { return start_; }
  void set_start(const long int & start) { start_ = start; }
  
  long int end(void) const { return end_; }
  void set_end(const long int & end) { end_ = end; }
  
  float score(void) const { return score_; }
  void set_score(const float & score) { score_ = score; }
  
  StrandType strand(void) const { return strand_; }
  void set_strand(const StrandType & strand) { strand_ = strand; }
  
  FrameType frame(void) const { return frame_; }
  void set_frame(const FrameType & frame) { frame_ = frame; }
  
  std::list<std::string> *attribute() { return &attribute_; }
};

#endif  // BACKEND_SRC_DATA_MANAGER_COMMON_CGFFRECORD_H_
