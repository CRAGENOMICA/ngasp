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

/**
 *  \brief     CPipeManager.h
 *  \details
 *  \author    jjene
 *  \version   1.0
 *  \date      Sep 10, 2015
 *  \pre
 *  \bug
 *  \warning
 *  \copyright CRAG 2015.
 */

#include <string>

// http://www.gnu.org/software/libc/manual/html_node/Creating-a-Pipe.html

class CPipeManager {
 private:
  int pipe_[2];

 public:
  CPipeManager() {
    pipe_[0] = -1;
    pipe_[1] = -1;
  }
  ~CPipeManager();

 public:
  void CreatePipe(void);
  void SetPipe(int input_pipe, int output_pipe);
  void WriteToPipe(std::string message);
  std::string ReadFromPipe(void);

 public:
  inline int input_pipe(void) { return pipe_[0]; }
  inline int output_pipe(void) { return pipe_[1]; }

  inline bool pipe_active() {
    return ((input_pipe() != -1) && (output_pipe() != -1));
  }

};

