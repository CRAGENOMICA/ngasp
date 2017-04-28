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
 *  \brief     CFastaInfo.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_DATA_MANAGER_COMMON_CFASTAINFO_H_
#define BACKEND_SRC_DATA_MANAGER_COMMON_CFASTAINFO_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <list>


#include "../../language/CStringTable.h"
#include "../CDataManager.h"
#include "../Data/CDataStdString.h"

#include "CDataSequenceIndex.h"
#include "CMemoryMappedFile.h"

class CFastaInfo : public CMemoryMappedFile {
 private:
  std::string file_name_;          // Fasta file name with its path.
  uintmax_t   bases_;              // Maximum number of bases per record.
  std::string descriptions_;       // All descriptions. ">desc1 >desc2 >desc3 \n"
  bool        same_sizes_;         // True if all records have the same number
                                   // of bases.
  std::list<CDataSequenceIndex *> *sequences_index_;
 
  
 public:  
  CFastaInfo() : CMemoryMappedFile() {
    bases_              = 0;
    descriptions_       = "";
    same_sizes_         = true;
    sequences_index_    = new std::list<CDataSequenceIndex *>();
  }
    
  ~CFastaInfo() {
    // Free allocated memory:
    if (sequences_index_ != NULL) {
      for (std::list<CDataSequenceIndex *>::iterator it = sequences_index_->begin();
           it != sequences_index_->end(); it++) {
        delete (*it);
      }
      
      delete sequences_index_;
      sequences_index_ = NULL;
    }
  }

 public:
  bool GetFileInformation(const std::string & file_name);
   
  inline uintmax_t bases(void) const { return bases_; }
  inline void set_bases(const uintmax_t & bases) { 
    bases_ = bases; 
  }
   
  inline std::string descriptions(void) const { return descriptions_; }
  inline void set_descriptions(const std::string & descriptions) { 
    descriptions_ = descriptions; 
  }
  inline void AddDescriptionCharacter(const char & ch) { 
    descriptions_ += ch; 
  }
  inline void AddSeparatorToDescriptions(void) {
    descriptions_ += " "; 
  }
  inline void CloseDescriptions(void) {
    descriptions_ += "\n"; 
  }
   
  inline bool same_sizes(void) const { return same_sizes_; }
  inline void set_same_sizes(const bool & same_sizes) { 
    same_sizes_ = same_sizes; 
  }
  
  std::list<CDataSequenceIndex *> *sequences_index(void) {
    return sequences_index_;
  }
   
  inline bool SequencesIndexEmpty(void) const {
    return sequences_index_->empty();
  }
   
  inline uintmax_t GetNumSequences(void) const {
    return sequences_index_->size();
  }
   
  inline void SetLastBasePositionToLastSequence(uintmax_t position) {
    sequences_index_->back()->set_last_base_position(position);
  }

  inline void AddNewSequenceIndex(const uintmax_t & first_base_position) {
    sequences_index_->push_back(
      new CDataSequenceIndex(first_base_position, 0, 0));
  }
   
  inline void UpdateCounters(uintmax_t *current_record_bases) {
    // =======================================================================
    // Here we do the following:
    // - Count the maximum number of bases per record.
    // - Find out if all records have the same size.
    // =======================================================================
    if (*current_record_bases > bases_) {
      if (bases_ != 0) {
        same_sizes_ = false;
      }
      bases_ = *current_record_bases;
    }
    *current_record_bases = 0;
  }
  
  
  friend std::ostream& operator<<(std::ostream & stream, const CFastaInfo & fasta) {
    stream  << "Fasta file name                  : "
            << fasta.file_name_
            << std::endl
            << "Sequences                        : "
            << fasta.GetNumSequences()
            << std::endl
            << "Max number of bases per sequence : "
            << fasta.bases_
            << std::endl
            << "All sequences have the same size : "
            << (fasta.same_sizes_?"true":"false")
            << std::endl
            << "Descriptions size in bytes       : "
            << fasta.descriptions_.length()
            << std::endl;
    
    return stream;
  } 
};

#endif  // BACKEND_SRC_DATA_MANAGER_COMMON_CFASTAINFO_H_
