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
 *  \brief     CFastaInfo.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CFastaInfo.h"

#include <string>

bool CFastaInfo::GetFileInformation(const std::string & file_name) {
  bool result = false;
  
  if (OpenForRead(file_name)) {
    // =========================================================================
    // Loop for getting the fasta information
    // =========================================================================

    uintmax_t fasta_pos             = 0;
    uintmax_t current_record_bases  = 0;
    char      previous_ch           = '\n';
    const char *end_fasta           = GetLastDataPosition();

    for (const char *fasta = GetFirstDataPosition();
         fasta < end_fasta;
         fasta++, fasta_pos++) {    

      if ((*fasta == '>') && (previous_ch == '\n')) {
        // Description found.

        if (!SequencesIndexEmpty()) {          
          // This start of a description is also the end of a previous sequence.
          // Store the last base position of the current sequence:
          SetLastBasePositionToLastSequence(fasta_pos - 2);

          // Update the maximum number of bases and the same_sizes:
          UpdateCounters(&current_record_bases);
        }

        // Get description chars in a loop:
        while (*fasta != '\n') {
          AddDescriptionCharacter(*fasta);
          fasta++;
          fasta_pos++;
        }

        // Descriptions must be separated by a separator (space at the end):

        AddSeparatorToDescriptions();

        // As the end of the description has been reached, this is also the 
        // start of a new sequence. Let's create a new sequence index and
        // store the position of its first base (+1 for passing through the EOL).
        AddNewSequenceIndex(fasta_pos + 1);
      }

      // Count the current sequence number of bases. The objective is to 
      // get the maximum number of bases per sequence.
      // EOLs can not be taken into account. They are all passed through.
      if (*fasta != '\n') {
        current_record_bases++;
      }

      previous_ch = *fasta;
    }

    // This is the end of the last sequence.
    // Let's store the position of its last base.
    if (!SequencesIndexEmpty()) {
      SetLastBasePositionToLastSequence(fasta_pos - 2);
    }

    // Also, let's update the fasta counters with the information of the last
    // sequence.
    UpdateCounters(&current_record_bases);

    // And finally, add the end character to the descriptions string (an EOL).
    CloseDescriptions();

    result = true;
  }
  
  return result;
}
