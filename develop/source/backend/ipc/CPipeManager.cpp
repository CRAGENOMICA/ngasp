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
 *  \brief     CPipeManager.cpp
 *  \details
 *  \author    jjene
 *  \version   1.0
 *  \date      Sep 10, 2015
 *  \pre
 *  \bug
 *  \warning
 *  \copyright CRAG 2015.
 */

#include "CPipeManager.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "../util/CStringTools.h"

CPipeManager::~CPipeManager() {
}

void CPipeManager::CreatePipe(void) {
	/*!disabled 
  if (pipe (pipe_)) {
    std::cout << "Pipe failed." << std::endl;
  }
  */
}

void CPipeManager::SetPipe(int input_pipe, int output_pipe) {
  pipe_[0] = input_pipe;
  pipe_[1] = output_pipe;
}

/// Read characters from the pipe
///
std::string CPipeManager::ReadFromPipe(void) {
  std::string ret;

  close(output_pipe());

  FILE *stream = NULL;
  int c;

  stream = fdopen(input_pipe(), "r");

  if (stream != NULL) {
    bool do_work = true;
    while (do_work) {
      c = fgetc(stream);
      if (c == EOF) {
        do_work = false;
      }
      else {
        ret += c;
      }
    }

    fclose(stream);
  }

  return ret;
}

/// Write text to the pipe
///
void CPipeManager::WriteToPipe(std::string message) {
  close(input_pipe());

  FILE *stream = NULL;
  stream = fdopen(output_pipe(), "w");

  if (stream != NULL) {
    fprintf(stream, message.c_str());
    fclose(stream);
  }
  else {
    std::cout << "WriteToPipe Error..." << std::endl;
  }
}
