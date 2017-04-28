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
 * File:   CNamedPipeManager.cpp
 * Author: owner
 *
 * Created on 11 / setembre / 2015, 08:18
 */

#include "CNamedPipeManager.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> // unlink, sleep
#include <string>
#include <iostream>
#include <string.h>

#include "../language/CStringTable.h"


/// Example of communication between:
///     Local Manager <-------------------------> ngaSP(id=1)
///
/// 1. Local Manager creates a couple of named pipes with CreatePipes()
///    and as a parameter: the ngaSP id.
///
///                   pipe1:   /tmp/ngasp_to_1.pipe
///                   pipe2:   /tmp/ngasp_from_1.pipe
///
/// 2.
//    Local Manager will use pipe1 to send messages to ngasp.
//    Local Manager will use pipe2 to receive messages from ngasp.
//  3.
//    ngaSP will use pipe1 to receive messages from the LocalManager.
//    ngaSP will use pipe2 to send messages to the LocalManager.

CNamedPipeManager::CNamedPipeManager() {
    active_ = false;
}

CNamedPipeManager::~CNamedPipeManager() {
}

std::string CNamedPipeManager::GetPipeFileName(int pipe_number) {
  std::string ret = STR(TEMP_FOLDER);
  if (pipe_number == 1)
    ret += STR(PRE_PIPE_NAME_TO_NGASP);
  if (pipe_number == 2)
    ret += STR(PRE_PIPE_NAME_FROM_NGASP);
  ret += fifo_named_pipe_name_;
  ret += STR(PIPE_EXTENSION);
  return ret;
}

void CNamedPipeManager::CreatePipes(std::string pipe_name) {
    fifo_named_pipe_name_ = pipe_name;

    ClosePipes();

    //!prev_disabled
    // create both fifo pipes:
    mkfifo(GetPipeFileName(1).c_str(), 0666);
    mkfifo(GetPipeFileName(2).c_str(), 0666);

    active_ = true;
}

void CNamedPipeManager::ClosePipes(void) {
    // remove both fifo pipes:
    if (fifo_named_pipe_name_ != "") {
      unlink(GetPipeFileName(1).c_str());
      unlink(GetPipeFileName(2).c_str());
    }
}

void CNamedPipeManager::SetPipes(std::string pipe_name) {
  fifo_named_pipe_name_ = pipe_name;

  active_ = true;
}

/// Open pipes:
/// ===========
///
/// http://linux.die.net/man/3/open
///
/// If O_NONBLOCK is NOT present in any of Read or Write:
///     The read waits until write is done.
///     The write waits until a process reads.
//
/// If O_NONBLOCK is present in both Read and Write:
///     The read does not wait.
///     The write fails if there is no process reading.

std::string CNamedPipeManager::ReadFromPipe(int pipe_number, bool wait) {
    std::string ret;

    char buf[MAX_BUF];
    memset(buf, '\x0', MAX_BUF);

    int fd = -1;

    if (wait) {
      fd = open(GetPipeFileName(pipe_number).c_str(), O_RDONLY);
    } else {
      fd = open(GetPipeFileName(pipe_number).c_str(), O_RDONLY); // | O_NONBLOCK
    }

    if (fd != -1) {
      read(fd, buf, MAX_BUF);
      ret = buf;
      close(fd);
    }

//    static std::string pret = "xxx";
//    if (pret != ret) {
//      pret = ret;
//      std::cout << "***********************************************************" << std::endl;
//      std::cout << "***********************************************************" << std::endl;
//      std::cout << "ReadFromPipe Pipe number: " << pipe_number << std::endl;
//      std::cout << "File:" << GetPipeFileName(pipe_number).c_str() << std::endl;
//      std::cout << ret << std::endl;
//      std::cout << "***********************************************************" << std::endl;
//      std::cout << "***********************************************************" << std::endl;
//    }

    return ret;
}

void CNamedPipeManager::WriteToPipe(int pipe_number, std::string message) {

//    std::cout << "***********************************************************" << std::endl;
//    std::cout << "***********************************************************" << std::endl;
//    std::cout << "WriteToPipe Pipe number: " << pipe_number << ". Message: " << message << std::endl;
//    std::cout << "File:" << GetPipeFileName(pipe_number).c_str() << std::endl;

    int fd = open(GetPipeFileName(pipe_number).c_str(), O_WRONLY); // | O_NONBLOCK
    if (fd != -1) {
      write(fd, message.c_str(), message.size()+1);
      close(fd);
//    std::cout << "***********************************************************" << std::endl;
//    std::cout << "***********************************************************" << std::endl;
    }
}
