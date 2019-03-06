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
 *  \brief     CMemoryMappedFile.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Jan 11, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#include "CMemoryMappedFile.h"


bool CMemoryMappedFile::Write(std::string text,
                              char **current_position,
                              const char *end_position) {
  bool result = false;

  if (*current_position + text.length() < end_position) {
    memcpy(*current_position,
           text.c_str(),
           text.length());

    *current_position += text.length();
    result = true;
  }

  return result;
}


unsigned long int CMemoryMappedFile::CalculateTableSpace(unsigned long int rows,
                                                unsigned long int columns,
                                                int cell_size,
                                                std::string column_separator) {
  // Calculate the size of the row.
  unsigned long int result = columns * cell_size;
  
  // Add the space for column separators (for one row).
  if (column_separator != "") {
    result += columns * column_separator.length();
  }

  // Add the end of line space (for one row).
  result += 1;
  
  // Multiply the row space per the total of rows.
  result *= rows;
  
  return result;
}

bool CMemoryMappedFile::WriteCell(std::string text,
                                  unsigned long int row,
                                  unsigned long int col,
                                  unsigned long int columns,
                                  std::size_t cell_size,
                                  std::string column_separator) {
  bool result = false;

  int total_cell_size = cell_size + column_separator.size();
  
  unsigned long int pos = (col * total_cell_size) + 
                 (row * ((columns * total_cell_size) + 1));  // + 1 is the EOL
  
  char *pointer_write = GetFirstReservedPosition() + pos;
  char *end_position  = GetLastReservedPosition();
  
  if (text.length() > cell_size) {
    text = text.substr(0, cell_size);
  }
  
  while (text.length() < cell_size) {
    text += " ";
  }
  text += column_separator;
  if (col == columns - 1) {  // If it is the last column add the EOL
    text += "\n";
  }

  if (pointer_write + text.length() <= end_position) {
    memcpy(pointer_write,
           text.c_str(),
           text.length());

    result = true;
  }
  
  return result;
}


void CMemoryMappedFile::Close(char *current_position,
                              const char *end_position) {
  if ((current_position != NULL) && (end_position != NULL)) {
    for (; current_position < end_position; current_position++) {
      *current_position = '.';
    }
  }
  
  destination_data_.close();
  is_open_ = false;
}
