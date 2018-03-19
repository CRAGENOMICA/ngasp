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
 *  \brief     CCMDSocket.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Sep 7, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_COMMANDS_CMD_CCMDSOCKET_H_
#define BACKEND_SRC_COMMANDS_CMD_CCMDSOCKET_H_

// http://www.binarytides.com/code-a-simple-socket-client-class-in-c/
#include <iostream>        // cout
#include <cstdio>          // printf
#include <cstring>         // strlen
#include <string>          // string

#ifdef __WIN32__
# include <winsock2.h>     // socket
#else
# include <sys/socket.h>   // socket
# include <arpa/inet.h>     // inet_addr
# include <netdb.h>         // hostent
#endif

#include <mutex>           // std::mutex
#include <list>

#include "../ICommand.h"
#include "../../ipc/CExperimentNode.h"

#include "../../util/CStringTools.h"

#define EOT '<'
#define TIME_ENSURE_ENROLLMENT 60         // Seconds
#define TIME_CHECK_EXPERIMENTS_STATUS 10  // Seconds

class CJSONDataFromCM {
 private:
  std::string lm_id_;
  int response_id_;
  std::string command_;
  int experiment_id_;
  std::string cmd_;
  std::string result_;
  bool result_is_JSON_format_;

 public:
  inline std::string lm_id(void) { return lm_id_; }
  inline int response_id(void) { return response_id_; }
  inline std::string command(void) { return command_; }
  inline std::string cmd(void) { return cmd_; }
  inline int experiment_id(void) { return experiment_id_; }
  inline std::string result(void) { return result_; }
  inline void set_result(std::string result) { result_ = result; }
  inline bool result_is_JSON_format(void) { return result_is_JSON_format_; }
  inline void set_result_is_JSON_format(bool result_is_JSON_format) {
    result_is_JSON_format_ = result_is_JSON_format;
  }

  CJSONDataFromCM(std::string lm_id,
                  int response_id,
                  std::string command,
                  int experiment_id,
                  std::string cmd,
                  std::string result) {
    lm_id_ = lm_id,
    response_id_ = response_id;
    command_ = command;
    cmd_ = cmd;
    experiment_id_ = experiment_id;
    result_ = result;
    result_is_JSON_format_ = false;
  }

  // Example:
  // {"command":"WELLCOME","data":{"cmd":null,"lm_key":null,"bin_key":null}}
  explicit CJSONDataFromCM(std::string text) {
    if (text != "") {
      lm_id_ = CStringTools::GetJSONValue(text, "lm_id");
      response_id_ = CStringTools::ToInt(CStringTools::GetJSONValue(text, "response_id"));
      command_ = CStringTools::GetJSONValue(text, "command");
      cmd_ = CStringTools::GetJSONValue(text, "cmd");
      experiment_id_ = CStringTools::ToInt(CStringTools::GetJSONValue(text, "experiment_id"));
      result_ = CStringTools::GetJSONValue(text, "result");
      
      // Strings arrive with scaped quotes like:
      //     set-value --to message --eq \"hello\"
      // In our strings we want:
      //     set-value --to message --eq "hello"
      CStringTools::Replace(lm_id_, "\\\"", "\"");
      CStringTools::Replace(command_, "\\\"", "\"");
      CStringTools::Replace(cmd_, "\\\"", "\"");
      CStringTools::Replace(result_, "\\\"", "\"");
    }
  }

  std::string Stringify(void) {
    std::string ret;

    std::string lm_id;
    std::string command;
    std::string cmd;
    std::string result;

    if (lm_id_ == "") { lm_id = "null"; } else { lm_id = "\"" + CStringTools::ScapeForJSONfield(lm_id_) + "\""; }
    if (command_ == "") { command = "null"; } else { command = "\"" + CStringTools::ScapeForJSONfield(command_) + "\""; }
    if (cmd_ == "") { cmd = "null"; } else { cmd = "\"" + CStringTools::ScapeForJSONfield(cmd_) + "\""; }

    if (result_is_JSON_format()) {
      if (result_ == "") { result = "null"; } else { result = result_; }
    } else {
      if (result_ == "") { result = "null"; } else { result = "\"" + CStringTools::ScapeForJSONfield(result_) + "\""; }
    }

    ret  = "{";
    ret += "\"command\":" + command + ",";
    ret +=   "\"data\":{";
    ret +=     "\"lm_id\":" + lm_id + ",";
    ret +=     "\"response_id\":" + CStringTools::ToString(response_id_) + ",";
    ret +=     "\"cmd\":" + cmd + ",";
    ret +=     "\"experiment_id\":" + CStringTools::ToString(experiment_id_) + ",";
    ret +=     "\"result\":" + result + "";
    ret +=   "}";
    ret += "}";

    return ret;
  }
};

class CCMDSocket : public ICommand {
 public:
  CCMDSocket();
  virtual ~CCMDSocket();

  CExperimentNode * CreateWorker(int experiment_id);
  
 private:
  std::string ip_;
  int port_;
  std::string lm_id_;  // It is stored. If the connection is lost we can call
                       // the CM and ask for a reconnection with this id.
 private:
  int sock;
  std::string address;
  int port;
  struct sockaddr_in server;
  bool do_work_;

 private:
  std::mutex mtx;
  std::list<CExperimentNode *> experiments_list_;

 public:
  void DefineCommandOptions();
  bool Prepare();
  void Run();
  void Finalize();

 private:
  bool conn(std::string address, int port);
  bool SendMsgToCMNetSocket(std::string lm_id,
                            int response_id,
                            std::string command,
                            int experiment_id,
                            std::string cmd,
                            std::string result);
  std::string receive(int size = 512);
  std::string GetString(std::string text,
                        tPosition pos,
                        char separator);
  std::string GenerateRandomId(int size);
  void RemoveExperimentsList(void);
  std::string GetComputerInformation(void);
  long int GetRAM();

 private:
  void SendExperimentKey(CJSONDataFromCM *JSONmessage);
  void ExecuteCommand(CJSONDataFromCM *JSONmessage);
  std::string ExecuteCommand(int experiment_id, std::string cmd);
  void CloseTheExperimentBinary(CJSONDataFromCM *JSONmessage);
  std::string CloseTheExperimentBinary(int experiment_id);  
  void GetOwnStatus(CJSONDataFromCM *JSONmessage);
  void GetExperimentResult(CJSONDataFromCM *JSONmessage);
  void CleanExperimentResult(CJSONDataFromCM *JSONmessage);
  std::string GetExperimentsList(void);
  CExperimentNode *FindExperimentById(int experiment_id);
  int GetNextExperimentId(void);
  void GetCalculationsList(CJSONDataFromCM *JSONmessage);
  void GetCommandsList(CJSONDataFromCM *JSONmessage);
  void GetDataTypesList(CJSONDataFromCM *JSONmessage);
  void GetDataManagerVariables(CJSONDataFromCM *JSONmessage);

  void CheckAllExperimentsStatus(void);
  void EnsureEnrollment(void);
  bool checking_experiments_status_;
  bool executing_socket_command_;

  void ExperimentsListChanged(void);

  void DeleteExperimentOutputFile(int experiment_id); 
  
  void cout_lm(std::string m);

 private:
  std::list<std::string> run_commands_list_;
  void RunCommandsThread(void);
  void RemoveCommandsList(void);

};

#endif  // BACKEND_SRC_COMMANDS_CMD_CCMDSOCKET_H_
