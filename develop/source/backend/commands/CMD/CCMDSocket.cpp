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
 *  \brief     CCMDSocket.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Sep 7, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDSocket.h"

#include<iostream>      // cout
#include<stdio.h>       // printf
#include<string.h>      // strlen
#include<string>        // string
#include <unistd.h>   // unlink
#include <chrono>

#ifdef __WIN32__
# include <winsock2.h>     // socket
#else
# include <sys/socket.h>   // socket
# include <arpa/inet.h>     // inet_addr
# include <netdb.h>         // hostent
#endif

#include <list>

#include <cstdlib>      // rand
#include <math.h>       // floor

#include <unistd.h>     // execl

#include <limits>       // GetRAM

#include <thread>         // std::thread
#include <chrono>         // std::chrono::seconds
#include <mutex>          // std::mutex

#include "../../util/CFile.h"
#include "../../util/CStringTools.h"
#include "../../calculations/CAllCalculations.h"
#include "../../commands/CAllCommands.h"
#include "../../data_manager/CDataManager.h"


CCMDSocket::CCMDSocket()
  : ICommand(CMD_SOCKET,                                                        // Command Name
             CMD_SOCKET_ABB,                                                    // Command Abbreviation Name
             CMD_SOCKET_DESC,                                                   // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  ip_ = "127.0.0.1";
  port_ = 6969;
  sock = -1;
  port = 0;
  address = "";
  lm_id_ = "";
  do_work_ = true;
  checking_experiments_status_ = false;
  executing_socket_command_ = false;
}

CCMDSocket::~CCMDSocket() {
  RemoveExperimentsList();

  if (sock != -1) {
    cout_lm("I am closed.");
  }
}

void CCMDSocket::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    TCP_ADDRESS_SHORT,                                          // Short Name
                    TCP_ADDRESS_LONG,                                           // Long Name
                    TCP_ADDRESS_DESC,                                           // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    TCP_PORT_SHORT,                                             // Short Name
                    TCP_PORT_LONG,                                              // Long Name
                    TCP_PORT_DESC,                                              // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDSocket::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::TCP_ADDRESS_SHORT:
      ip_ = arguments;
      break;
    case KeyString::TCP_PORT_SHORT:
      port_ = CStringTools::ToInt(arguments);
      break;
    default:
      parseResult = false;
      break;
    }
  }

  parseResult = CheckOptions() && parseResult;

  if (parseResult) {
    // Connect
    // =======
    conn(ip_, port_);

    // Say "I am here" to the Central Manager
    // ======================================
    cout_lm("I am going to introduce myself.");
    SendMsgToCMNetSocket("", -1, "HELLO", -1, "", CStringTools::ScapeForJSONfield(GetComputerInformation()));
  }

  return parseResult;
}


std::string CCMDSocket::GenerateRandomId(int size) {
  std::string ret;
  std::string possible = "abcdefghijklmnopqrstuvwxyz0123456789";

  for(int i = 0; i < size; i++) {
      //TODO: Desactivat perquè el rand() interferia amb el rand() de CCalcRandomize(). Es pot tornar a activar si els tests mstatspop-ngasp han passat correctament
      // ret += possible[floor(rand() % possible.length())];
  }

  return ret;
}


/**
 * =============================================================================
 * MESSAGES FROM THE CENTRAL MANAGER
 * =============================================================================
 */
void CCMDSocket::Run() {

  std::thread *t_ensure_enrollment = NULL;
  std::thread *t_check_experiments_status = NULL;

  do_work_ = true;

  while(do_work_ == true) {
    std::string received = receive(1024);
    CJSONDataFromCM JSONmessage(received);

    if (JSONmessage.command() != "") {
      if (JSONmessage.command() == "HELLO") {
        // SaveOwnLocalManagerId:
        lm_id_ = JSONmessage.result();
        cout_lm("The Central Manager accepts my friendship. My lm_key is '" + lm_id_ + "'.");
        t_ensure_enrollment = new std::thread(&CCMDSocket::EnsureEnrollment, this);
        t_check_experiments_status = new std::thread(&CCMDSocket::CheckAllExperimentsStatus, this);
      }
      else {
        if (JSONmessage.command() == "RUN") {
          executing_socket_command_ = true;
          ExecuteCommand(&JSONmessage);
          executing_socket_command_ = false;
        }
        else {
          if (JSONmessage.command() == "GET_EXPERIMENT_RESULT") {
            executing_socket_command_ = true;
            GetExperimentResult(&JSONmessage);
            executing_socket_command_ = false;
          }
          else {
            if (JSONmessage.command() == "STATUS") {
              executing_socket_command_ = true;
              GetOwnStatus(&JSONmessage);
              executing_socket_command_ = false;
            }
            else {
              if (JSONmessage.command() == "CLEAN_EXPERIMENT_RESULT") {
                executing_socket_command_ = true;
                CleanExperimentResult(&JSONmessage);
                executing_socket_command_ = false;
              }
              else {
                if (JSONmessage.command() == "CALCULATIONS_LIST") {
                  executing_socket_command_ = true;
                  GetCalculationsList(&JSONmessage);
                  executing_socket_command_ = false;
                } else {
                  if (JSONmessage.command() == "COMMANDS_LIST") {
                    executing_socket_command_ = true;
                    GetCommandsList(&JSONmessage);
                    executing_socket_command_ = false;
                  }
                  else {
                    if (JSONmessage.command() == "DATA_TYPES_LIST") {
                      executing_socket_command_ = true;
                      GetDataTypesList(&JSONmessage);
                      executing_socket_command_ = false;
                    }
                    else {
                      if (JSONmessage.command() == "DATA_MANAGER_VARIABLES") {
                        executing_socket_command_ = true;
                        GetDataManagerVariables(&JSONmessage);
                        executing_socket_command_ = false;
                      }
                      else {
                        if (JSONmessage.command() == "CLOSE_LM") {
                          // when this class is destroyed, all experiments are closed.
                          do_work_ = false;
                        }
                        else {
                          if (JSONmessage.command() == "CLOSE_EXPERIMENT") {
                            // when this class is destroyed, all experiments are closed.
                            executing_socket_command_ = true;
                            CloseTheExperimentBinary(&JSONmessage);
                            executing_socket_command_ = false;
                          }
                          else {
                            cout_lm("The Central Manager is telling me something that I do not understand: " + JSONmessage.command() + ".");
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  // Wait threads to be closed:
  t_ensure_enrollment->join();
  t_check_experiments_status->join();

  delete t_ensure_enrollment;
  delete t_check_experiments_status;
}

void CCMDSocket::RemoveExperimentsList(void) {
  // Delete all list elements:
  for(std::list<CExperimentNode *>::iterator it = experiments_list_.begin();
          it != experiments_list_.end(); ++it) {

    cout_lm("Closing experiment. experiment_id: " + (*it)->experiment_id());

    // Send close signal to the experiment:
    std::string bin_close_command = "RUN";
    bin_close_command += STR(COMMAND_SEPARATOR);
    bin_close_command += (*it)->experiment_id();
    bin_close_command += STR(PARAM_SEPARATOR);
    bin_close_command += STR(CMD_STOP);
    (*it)->pipe_manager()->SendPipeMessageToExperiment(bin_close_command);
    (*it)->pipe_manager()->WaitMessageFromExperiment();

    delete *it;
    it++;
  }
  experiments_list_.clear();
}

void CCMDSocket::Finalize() {
  /// Clean the command to reuse it later:
  ip_ = "127.0.0.1";
  port_ = 6969;
  sock = -1;
  port = 0;
  address = "";

  RemoveExperimentsList();
  
  DM_DEL_ALL_LOCAL_DATA
}

// =============================================================================
// COMPUTER INFORMATION METHODS
// =============================================================================

std::string CCMDSocket::GetComputerInformation(void) {
  std::string ret;
  //!prev_disabled
  int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
  ret = "NumCores: " + CStringTools::ToString(numCPU) + "\n" +
        "MemTotal: " + CStringTools::ToString(GetRAM()/1000000) + "Gb.";
  return ret;
}

long int CCMDSocket::GetRAM() {
    std::string token;
    std::ifstream file("/proc/meminfo");
    while(file >> token) {
        if(token == "MemTotal:") {
            unsigned long mem;
            if(file >> mem) {
                return mem;
            } else {
                return 0;
            }
        }
        // ignore rest of the line
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0; // nothing found
}

// =============================================================================
// CONNECTION METHODS
// =============================================================================

/// Connect to a host on a certain port number
///
bool CCMDSocket::conn(std::string address, int port) {
  //!prev_disabled
  //create socket if it is not already created
  if (sock == -1) {
    //Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
      cout_lm("Could not create socket.");
    }

    cout_lm("I am alive and I want to connect with the Central Manager.");
  } else {
    // OK , nothing
  }

  // setup address structure
  if (inet_addr(address.c_str()) == INADDR_NONE) {
    struct hostent *he;
    struct in_addr **addr_list;

    //resolve the hostname, its not an ip address
    if ((he = gethostbyname(address.c_str())) == NULL) {
      //gethostbyname failed
      herror("gethostbyname");
      cout_lm("Failed to resolve hostname.");

      return false;
    }

    // Cast the h_addr_list to in_addr , since h_addr_list also has the ip
    // address in long format only
    addr_list = (struct in_addr **) he->h_addr_list;

    for (int i = 0; addr_list[i] != NULL; i++) {
      //strcpy(ip , inet_ntoa(*addr_list[i]) );
      server.sin_addr = *addr_list[i];

      cout_lm(address + " resolved to " + inet_ntoa(*addr_list[i]));
      break;
    }
  } else { //plain ip address
    server.sin_addr.s_addr = inet_addr(address.c_str());
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  //Connect to remote server
  if (connect(sock, (struct sockaddr *) &server, sizeof (server)) < 0) {
    cout_lm("connect failed. Error.");
    return 1;
  }

  cout_lm("I have stablish a connection with the Central Manager.");
  
  return true;
}

/// Send data to the Central Manager
///
bool CCMDSocket::SendMsgToCMNetSocket(std::string lm_id,
                                      int response_id,
                                      std::string command,
                                      int experiment_id,
                                      std::string cmd,
                                      std::string result) {
  CJSONDataFromCM JSONmessage(lm_id,
                              response_id,
                              command,
                              experiment_id,
                              cmd,
                              result);

  // The message must end with "\n" because when sending multiple messages to 
  // a Node.js tcp socket, they get streamed as a single message. The end of line
  // character is used to split messages.
  std::string message = JSONmessage.Stringify();
  CStringTools::Replace(message, "\n", "<br />");  // The message can not contain \n
  CStringTools::Replace(message, "\r", "");               // The message can not contain \r
  message +=  "\n";                                                                 // <---- Only  one final "\n"

  cout_lm("(>CM) " + message);

  //!prev_disabled
  try {
    //Send some data
    size_t bytes_to_be_sent = strlen(message.c_str());
    ssize_t bytes_sent = send(sock, message.c_str(), bytes_to_be_sent, 0);
    cout_lm("(>CM) " + std::to_string(bytes_sent) + "/" + std::to_string(bytes_to_be_sent) + " bytes sent.");
    
    if ( bytes_sent < 0) {
      cout_lm("Send failed.");
      return false;
    }
  }
  catch(...) {
    return false;
  }

  return true;
}

/// Receive data from the connected host
/*
 * Cases:
 *   1: "command|"  : Return stored+"command", stored=""
 *   2: "comm"      : stored+="comm", Return ""
 *   3: "and|com"   : Return stored+"and",stored="com"
 *   4: ""          : Return ""
*/
std::string CCMDSocket::receive(int size) {
  static std::string stored = "";
  std::string ret;

  char *cbuffer = new char[size];
  memset(cbuffer, '\x0', size);

  std::string sbuffer;

  //!prev_disabled
  //Receive a reply from the server
  if (recv(sock, cbuffer, sizeof (cbuffer), 0) < 0) {
    puts("recv failed");
  }

  sbuffer = cbuffer;

  if (cbuffer != 0) {
    delete cbuffer;
    cbuffer = 0;
  }

  if (sbuffer != "") {
    if (sbuffer[sbuffer.length()-1] == EOT) {
      // Case 1:
      ret = stored + sbuffer.substr(0, sbuffer.length()-1);
      stored = "";
    } else {
      int t = sbuffer.find(EOT);
      if (t == -1) {
        // Case 2:
        stored += sbuffer;
        ret = "";
      } else {
        // Case 3:
        ret = stored + sbuffer.substr(0, t);
        stored = sbuffer.substr(t+1);
      }
    }
  } else {
    // Case 4:
    ret = "";
  }

  return ret;
}

// =============================================================================
// MESSAGES TO THE CENTRAL MANAGER
// =============================================================================

CExperimentNode *CCMDSocket::FindExperimentById(int experiment_id) {
  // Find the experiment by "bin_key"
  CExperimentNode *experiment = NULL;
  for(std::list<CExperimentNode *>::iterator it = experiments_list_.begin();
          (it != experiments_list_.end() && (experiment == NULL)); ++it) {
    if ((*it)->experiment_id() == experiment_id) {
      experiment = (*it);
    }
  }
  return experiment;
}



void CCMDSocket::ExecuteCommand(CJSONDataFromCM *JSONmessage) {
  cout_lm("I am going to run this command: \"" + JSONmessage->cmd() + "\" on this experiment: " + std::to_string(JSONmessage->experiment_id()));

  std::string result = ExecuteCommand(JSONmessage->experiment_id(), JSONmessage->cmd());

  SendMsgToCMNetSocket(JSONmessage->lm_id(), JSONmessage->response_id(), JSONmessage->command(), JSONmessage->experiment_id(), JSONmessage->cmd(), result);
}

void CCMDSocket::DeleteExperimentOutputFile(int experiment_id) {
    std::string output_file_name = STR(TEMP_FOLDER);
    output_file_name += STR(PRE_OUTPUT_NAME);
    output_file_name += CStringTools::ToString(experiment_id);
    output_file_name += STR(OUTPUT_EXTENSION);
    cout_lm("I am going to delete the experiment output file '" + output_file_name +  "'...");
    if (unlink(output_file_name.c_str()) == 0) {
        cout_lm("File removed.");
    } else {
        cout_lm("File NOT removed...");
    }   
}

void CCMDSocket::CloseTheExperimentBinary(CJSONDataFromCM *JSONmessage) {
  cout_lm("I am going to close the binary: \"" + JSONmessage->cmd() + "\" of this experiment: " + std::to_string(JSONmessage->experiment_id()));

  std::string result = CloseTheExperimentBinary(JSONmessage->experiment_id());
 
  DeleteExperimentOutputFile(JSONmessage->experiment_id());
  
  SendMsgToCMNetSocket(JSONmessage->lm_id(), JSONmessage->response_id(), JSONmessage->command(), JSONmessage->experiment_id(), JSONmessage->cmd(), result);
}
                          

void CCMDSocket::GetOwnStatus(CJSONDataFromCM *JSONmessage) {
  cout_lm("My status is OK.");

  SendMsgToCMNetSocket(JSONmessage->lm_id(), JSONmessage->response_id(), JSONmessage->command(), JSONmessage->experiment_id(), JSONmessage->cmd(), "OK");
}

void CCMDSocket::GetExperimentResult(CJSONDataFromCM *JSONmessage) {
  cout_lm("I am going return the experiment result for: '" + std::to_string(JSONmessage->experiment_id()) + "'.");

  // Find the experiment
  CExperimentNode *experiment = FindExperimentById(JSONmessage->experiment_id());

  std::string result_save;
  if (experiment != NULL) {
    std::string bin_command = "SAVE_COUT_FILE";
    bin_command += STR(COMMAND_SEPARATOR);


    cout_lm("I am going to request the experiment to save the current output. '" + bin_command + "'.");
    experiment->pipe_manager()->SendPipeMessageToExperiment(bin_command);
    result_save = experiment->pipe_manager()->WaitMessageFromExperiment();
  }
  else {
    // The experiment can be closed. It is Ok.
  }

  std::string output_file_name = STR(TEMP_FOLDER);
  output_file_name += STR(PRE_OUTPUT_NAME);
  output_file_name += CStringTools::ToString(JSONmessage->experiment_id());
  output_file_name += STR(OUTPUT_EXTENSION);

  
  std::string buffer;
  if (CFile::ReadAll(output_file_name, buffer)) {
    JSONmessage->set_result(buffer);
  }
  
  cout_lm("I am going to send the output to the CM. File content:");
  cout_lm(JSONmessage->result());

  
  SendMsgToCMNetSocket(JSONmessage->lm_id(), JSONmessage->response_id(), JSONmessage->command(), JSONmessage->experiment_id(), JSONmessage->cmd(), JSONmessage->result());
}

void CCMDSocket::CleanExperimentResult(CJSONDataFromCM *JSONmessage) {
  cout_lm("I am going to clean the experiment result for: '" + std::to_string(JSONmessage->experiment_id()) + "'.");

  // Find the experiment
  CExperimentNode *experiment = FindExperimentById(JSONmessage->experiment_id());

  if (experiment != NULL) {
      
    DeleteExperimentOutputFile(JSONmessage->experiment_id());
      
    std::string bin_command = "CLEAN_EXPERIMENT_RESULT";
    bin_command += STR(COMMAND_SEPARATOR);

    cout_lm("I am going to request the experiment to delete the experiment output file: '" + bin_command + "'.");
    experiment->pipe_manager()->SendPipeMessageToExperiment(bin_command);
    JSONmessage->set_result(experiment->pipe_manager()->WaitMessageFromExperiment());
  }

  SendMsgToCMNetSocket(JSONmessage->lm_id(), JSONmessage->response_id(), JSONmessage->command(), JSONmessage->experiment_id(), JSONmessage->cmd(), JSONmessage->result());
}

CExperimentNode * CCMDSocket::CreateWorker(int experiment_id) {
  // This is going to be the first command executed on this experiment.
  // Create the new experiment reference with its shared memory:
  // And create the pipe:
  
  CExperimentNode *new_experiment = new CExperimentNode(experiment_id);
  experiments_list_.push_back(new_experiment);
  ExperimentsListChanged();


  // Open the experiment:

  std::string open_experiment;

  open_experiment = CFile::GetCurrentWorkingDirectory();
  open_experiment += "/bin/";
  open_experiment += STR(NGASP_APP_EXECUTABLE_NAME);
  open_experiment += STR(SPACE);
  open_experiment += STR(CMD_PIPE);
  open_experiment += STR(SPACE); 
  open_experiment += STR(PARAM);
  open_experiment += STR(PIPE_NAME_SHORT);
  open_experiment += STR(SPACE);
  open_experiment += CStringTools::ToString(experiment_id);
  open_experiment += STR(SPACE);
  open_experiment += "&";

  cout_lm("I am opening a new experiment experiment: ");
  cout_lm(open_experiment.c_str());

  system(open_experiment.c_str());

  cout_lm("system called for opening the experiment.");
  
  return new_experiment;
}

std::string CCMDSocket::ExecuteCommand(int experiment_id, std::string cmd) {
  std::string result;
  
  // Find the experiment by "bin_key"
  CExperimentNode *new_experiment = NULL;
  
//!MPI  WaitWorker()
    
  new_experiment = FindExperimentById(experiment_id);

  if (new_experiment == NULL) {
    new_experiment = CreateWorker(experiment_id);
  }

  if (new_experiment != NULL) {
    std::string bin_command = "RUN";
    bin_command += STR(COMMAND_SEPARATOR);
    bin_command += CStringTools::ToString(experiment_id);
    bin_command += STR(PARAM_SEPARATOR);
    bin_command += cmd;
   
    cout_lm("Sending command to the experiment experiment: '" + bin_command + "'.");

    new_experiment->pipe_manager()->SendPipeMessageToExperiment(bin_command);

    cout_lm("I am waiting response from the experiment...");
    result = new_experiment->pipe_manager()->WaitMessageFromExperiment();
    cout_lm("The experiment says: '" + result + "'.");
    cout_lm("I am going to inform CM about it.");

  } else {
    cout_lm("I do not find any experiment...");
  }

  return result;
}

std::string CCMDSocket::CloseTheExperimentBinary(int experiment_id) {
  std::string result;
  
  CExperimentNode *experiment = NULL;
    
  experiment = FindExperimentById(experiment_id);

  if (experiment != NULL) {
    std::string bin_command = "RUN";
    bin_command += STR(COMMAND_SEPARATOR);
    bin_command += CStringTools::ToString(experiment_id);
    bin_command += STR(PARAM_SEPARATOR);
    bin_command += STR(CMD_STOP);
   
    cout_lm("Asking the experiment for closing itself.");

    experiment->pipe_manager()->SendPipeMessageToExperiment(bin_command);

    cout_lm("I am waiting response from the experiment...");
    result = experiment->pipe_manager()->WaitMessageFromExperiment();
    cout_lm("The experiment says: '" + result + "'.");
    cout_lm(" I am going to inform CM about it.");
    
    // Delete the experiment from the list:
    std::list<CExperimentNode *>::iterator it = experiments_list_.begin();
    CExperimentNode *item_unlisted = NULL;
    while ((it != experiments_list_.end()) && (item_unlisted == NULL)) {
      if ((*it)->experiment_id() == experiment_id) {
        item_unlisted = (*it);
        it = experiments_list_.erase(it);
      }
      else {
          ++it;
      }
    }

    if (item_unlisted != NULL) {
        delete item_unlisted;
        ExperimentsListChanged();
    }
  } else {
    cout_lm("The experiment that it is trying to be closed is already closed...");
  }

  return result;
}

void CCMDSocket::EnsureEnrollment(void) {  // And refresh capabilities
    
  while(do_work_ == true) {
    if (lm_id_ != "") {
      cout_lm("I am going to ensure that the connection with the CentralManager is still on.");
      SendMsgToCMNetSocket(lm_id_, -1, "STILL_HERE", -1, "", CStringTools::ScapeForJSONfield(GetComputerInformation()));
      std::this_thread::sleep_for (std::chrono::seconds(TIME_ENSURE_ENROLLMENT));
    }
  }
}

void CCMDSocket::CheckAllExperimentsStatus(void) {
  while(do_work_ == true) {
    if (lm_id_ != "") {
      if((checking_experiments_status_ == false) &&
         (executing_socket_command_ == false)) {
        checking_experiments_status_ = true;
        mtx.lock();

        bool experiments_list_has_changed = false;

        int num_experiments = experiments_list_.size();

        if (num_experiments > 0) {
          cout_lm("I am going see experiments (" + std::to_string(num_experiments) + ") are still open...");

          std::string status;
          std::string bin_get_status = "STATUS";
          bin_get_status += STR(COMMAND_SEPARATOR);

          for(std::list<CExperimentNode *>::iterator it = experiments_list_.begin();
              it != experiments_list_.end(); ++it) {
            if ((*it)->pipe_manager()->pipe_active() == false) {
              if ((*it)->status() == "CLOSED") {
                cout_lm("Found one experiment closed.");
              } else {
                cout_lm("Closing one experiment because its pipe has been closed.");
                  (*it)->set_status("CLOSED");
                  experiments_list_has_changed = true;
              }
            } else {
              if ((*it)->status() == "...") {
                (*it)->set_status("CONNECTION_LOST");
                cout_lm("I close one experiment because it is not answering.");
                experiments_list_has_changed = true;
              } else {
                (*it)->set_status("...");
                try {
                  cout_lm("I request one experiment...");
                  (*it)->pipe_manager()->SendPipeMessageToExperiment(bin_get_status);
                  status = (*it)->pipe_manager()->WaitMessageFromExperiment();
                  (*it)->set_status(status);
                  cout_lm("The experiment answers: '" + status + "'.");
                }
                catch(...) {
                  (*it)->set_status("CONNECTION_LOST");
                  cout_lm("Connection lost with one experiment.");
                  experiments_list_has_changed = true;
                }
              }
            }
          }
        }

        if (experiments_list_has_changed) {
          ExperimentsListChanged();
        }

        mtx.unlock();
        checking_experiments_status_ = false;
        std::this_thread::sleep_for (std::chrono::seconds(TIME_CHECK_EXPERIMENTS_STATUS));
      }
    }
  }
}

std::string CCMDSocket::GetExperimentsList(void) {
  std::string ret = "[";

  cout_lm("I am returning the experiments list...");

  for(std::list<CExperimentNode *>::iterator it = experiments_list_.begin();
      it != experiments_list_.end(); ++it) {
    if (it != experiments_list_.begin()) {
      ret += ",";
    }

    // At this level, the experiment name is unknown.
    ret += "{";
      ret += "\"experiment_id\":\"";
        ret += CStringTools::ToString((*it)->experiment_id());
        ret += "\",";
      ret += "\"status\":\"";
        ret += (*it)->status();
        ret += "\",";
      ret += "\"other\":\"77\"";
    ret += "}";
  }

  ret += "]";

  return ret;
}

void CCMDSocket::ExperimentsListChanged(void) {
    cout_lm("Let's notify the CM that the experiments list has been changed.");
    SendMsgToCMNetSocket(lm_id_, -1, "EXPERIMENTS_LIST", -1, "", GetExperimentsList());
}

void CCMDSocket::GetCalculationsList(CJSONDataFromCM *JSONmessage) {
    JSONmessage->set_result_is_JSON_format(true);
    SendMsgToCMNetSocket(JSONmessage->lm_id(), JSONmessage->response_id(), JSONmessage->command(), JSONmessage->experiment_id(), JSONmessage->cmd(), manager()->calc_factory()->GetCalcsInformation(manager()));
}

void CCMDSocket::GetCommandsList(CJSONDataFromCM *JSONmessage) {
    JSONmessage->set_result_is_JSON_format(true);
    SendMsgToCMNetSocket(JSONmessage->lm_id(), JSONmessage->response_id(), JSONmessage->command(), JSONmessage->experiment_id(), JSONmessage->cmd(), manager()->all_commands()->GetCommandsInformation(manager()));
}

void CCMDSocket::GetDataTypesList(CJSONDataFromCM *JSONmessage) {
    JSONmessage->set_result_is_JSON_format(true);
    SendMsgToCMNetSocket(JSONmessage->lm_id(), JSONmessage->response_id(), JSONmessage->command(), JSONmessage->experiment_id(), JSONmessage->cmd(), manager()->data_factory()->GetDataTypesInformation());
}

void CCMDSocket::GetDataManagerVariables(CJSONDataFromCM *JSONmessage) {
  JSONmessage->set_result_is_JSON_format(true);

  cout_lm("I am going to get the DM variables from the experiment: '" + std::to_string(JSONmessage->experiment_id()) + "'.");

  // Find the experiment
  CExperimentNode *experiment = FindExperimentById(JSONmessage->experiment_id());

  if (experiment != NULL) {
    std::string bin_command = "DATA_MANAGER_VARIABLES";
    bin_command += STR(COMMAND_SEPARATOR);

    cout_lm("I am going to request the experiment all its DM variables: '" + bin_command + "'.");
    experiment->pipe_manager()->SendPipeMessageToExperiment(bin_command);
    JSONmessage->set_result(experiment->pipe_manager()->WaitMessageFromExperiment());
  }

  SendMsgToCMNetSocket(JSONmessage->lm_id(), JSONmessage->response_id(), JSONmessage->command(), JSONmessage->experiment_id(), JSONmessage->cmd(), JSONmessage->result());
}

void CCMDSocket::cout_lm(std::string m) {
/*    CStringTools::Replace(m, "\n", "<br />");
     std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    std::cout << ms.count() << " LM " << m << std::endl;
 */ 
}


// ...

