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
 *  \brief     CGFFFile.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CGFFFile.h"

#include <string>
#include <list>

#include "../../language/CStringTable.h"

#include "../../util/CFile.h"
#include "../../util/CStringTools.h"

CGFFFile::CGFFFile() {
  records_ = new std::list<CGFFRecord *>();
}

CGFFFile::~CGFFFile() {
  // Free allocated memory:
  if (records_ != NULL) {
    for (std::list<CGFFRecord *>::iterator it = records_->begin();
         it != records_->end(); it++) {
      delete (*it);
    }

    delete records_;
    records_ = NULL;
  }  
}

bool CGFFFile::Open(const std::string & file_name) {
  bool result = true;
  
  set_file_name(file_name);
  
  CFile file_gff(file_name);

  if (file_gff.Open()) {
    std::string line;
    while(file_gff.ReadLine(&line) && result) {
      if ((line != "") && (line[0] != STR(LINE_COMMENT_TAG)[0])) {
        result &= AddRecord(line);
      }
    }
  } else {
    result = false;
  }
  
  return result;
}

bool CGFFFile::AddRecord(std::string file_row) {
  bool result = true;

  std::string column;
  std::string::size_type pos;

  CGFFRecord *new_record = new CGFFRecord();

  // Get GFF Column 1: SEQNAME
  pos = file_row.find(STR(TAB), 0);
  if (pos != std::string::npos) {
    new_record->set_seqname(file_row.substr(0, pos));
    file_row = file_row.substr(pos + 1);
    
    // Get GFF Column 2: SOURCE
    pos = file_row.find(STR(TAB), 0);
    if (pos != std::string::npos) {
      new_record->set_source(file_row.substr(0, pos));
      file_row = file_row.substr(pos + 1);

      // Get GFF Column 3: FEATURE
      pos = file_row.find(STR(TAB), 0);
      if (pos != std::string::npos) {
        new_record->set_feature(file_row.substr(0, pos));
        file_row = file_row.substr(pos + 1);

        // Get GFF Column 4: START
        pos = file_row.find(STR(TAB), 0);
        if (pos != std::string::npos) {
          new_record->set_start(CStringTools::ToInt64(file_row.substr(0, pos)));
          file_row = file_row.substr(pos + 1);

          // Get GFF Column 5: END
          pos = file_row.find(STR(TAB), 0);
          if (pos != std::string::npos) {
            new_record->set_end(CStringTools::ToInt64(file_row.substr(0, pos)));
            file_row = file_row.substr(pos + 1);

            // Get GFF Column 6: SCORE
            pos = file_row.find(STR(TAB), 0);
            if (pos != std::string::npos) {
              new_record->set_score(
                CStringTools::ToFloat(file_row.substr(0, pos)));
              file_row = file_row.substr(pos + 1);

              // Get GFF Column 7: STRAND
              pos = file_row.find(STR(TAB), 0);
              if (pos != std::string::npos) {
                new_record->set_strand(
                  static_cast<CGFFRecord::StrandType>(
                    file_row.substr(0, pos)[0]));
                file_row = file_row.substr(pos + 1);

                // Get GFF Column 8: FRAME
                pos = file_row.find(STR(TAB), 0);
                if (pos != std::string::npos) {
                  new_record->set_frame(
                    static_cast<CGFFRecord::FrameType>(
                      file_row.substr(0, pos)[0]));
                  file_row = file_row.substr(pos + 1);

                  // Get GFF Column 9: ATTRIBUTE
                  std::string column_9;
                  column_9 = file_row;
                  file_row = "";

                  while(column_9 != "") {
                    std::string::size_type pos2;
                    std::string couple;

                    // Get couple separated by semi colon
                    pos2 = column_9.find(STR(SEMI_COLON), 0);
                    if (pos2 != std::string::npos) {
                      couple = column_9.substr(0, pos2);
                      column_9 = column_9.substr(pos2 + 1);
                    } else {
                      couple = column_9;
                      column_9 = "";
                    }
                    new_record->attribute()->push_back(couple);
                  }
   
                } else {
                  result = false;
                }    
              } else {
                result = false;
              }    
            } else {
              result = false;
            }    
          } else {
            result = false;
          }
        } else {
          result = false;
        }
      } else {
        result = false;
      }

    } else {
      result = false;
    }
  } else {
    result = false;
  }

  // Store this current record information:

  records_->push_back(new_record);
  
  return result;
}

