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
 * File:   CNamedPipeManager.h
 * Author: owner
 *
 * Created on 11 / setembre / 2015, 08:18
 */

#ifndef CNAMEDPIPEMANAGER_H
#define	CNAMEDPIPEMANAGER_H

#include <string>
#include <sys/stat.h>

#define MAX_BUF 1024

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



class CNamedPipeManager {
 public:
  CNamedPipeManager();
  CNamedPipeManager(const CNamedPipeManager& orig);
  virtual ~CNamedPipeManager();

private:
  std::string fifo_named_pipe_name_;
  bool active_;

public:
  void CreatePipes(std::string pipe_name);
  void ClosePipes(void);
  void SetPipes(std::string pipe_name);
  //inline void set_pipe_active(bool pipe_active) { active_ = pipe_active; }
  inline bool pipe_active(void) {
//    if ((active_) &&
//        (ExistsFile(GetPipeFileName(1))) &&
//        (ExistsFile(GetPipeFileName(2)))) {
//      active_ = true;
//    } else {
//      active_ = false;
//    }
//    return active_;
      return ((ExistsFile(GetPipeFileName(1))) &&
              (ExistsFile(GetPipeFileName(2))));
  }

  inline std::string fifo_named_pipe_name(void) {
      return fifo_named_pipe_name_;
  }

  inline bool ExistsFile(const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
  }

  inline void SendPipeMessageToExperiment(std::string message) {
    if (pipe_active()) {
      WriteToPipe(1, message);
    }
  }
  inline void SendPipeMessageToLocalManager(std::string message) {
    if (pipe_active()) {
      WriteToPipe(2, message);
    }
  }
//  inline std::string ReadMessageFromExperimentNoWait(void) {
//    return ReadFromPipe(2, false);
//  }
//  inline std::string ReadMessageFromLocalManagerNoWait(void) {
//    return ReadFromPipe(1, false);
//  }
  inline std::string WaitMessageFromExperiment(void) {
    std::string ret;
    if (pipe_active()) {
      ret = ReadFromPipe(2, true);
    }
    return ret;
  }
  inline std::string WaitMessageFromLocalManager(void) {
    std::string ret;
    if (pipe_active()) {
      ret = ReadFromPipe(1, true);
    }
    return ret;
  }

 private:
  std::string GetPipeFileName(int pipe_number);
  std::string ReadFromPipe(int pipe_number, bool wait);
  void WriteToPipe(int pipe_number, std::string message);
};

#endif	/* CNAMEDPIPEMANAGER_H */

