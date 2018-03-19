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
 *  \brief     CDataManager.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      April 27, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#include "CDataManager.h"

#include <map>
#include <string>

#include "../language/CStringTable.h"

/// Fixed Data Includes:
#include "Data/CDataInt.h"
#include "Data/CDataInt64.h"
#include "Data/CDataStdString.h"
#include "Data/CDataDouble.h"
#include "Data/CDataBoolean.h"
#include "../util/CFile.h"

CDataManager::CDataManager() {
  set_repository(NULL);
}

CDataManager::~CDataManager() {
  DestroyRepository();
}

void CDataManager::DestroyRepository(void) {
  if(repository()) {
    std::map< std::string, IData *>::iterator it;

    for (it = repository()->begin(); it != repository()->end(); ++it) {
      // Delete the Data object:
      // Do not use the RemoveDataById.
      delete it->second;
      it->second = NULL;
    }
    // Remove all elements from the map:
    repository()->clear();

    // Remove the map object:
    delete repository_;
    set_repository(NULL);
  }
}

void f(void) {
//  std::cout << "ha canviat." << std::endl;
//  CDataStdString *output_file = NULL;
//  output_file = data_manager()->GetDataByName(output_file, STR(OUTPUT_FILE));
//
//  if (output_file->value() == "") {
//    // Restore the output to the original stream:
//    std::cout.rdbuf(output_stream_original_);
//  } else {
//    if (output_file_stream_ != NULL) {
//      delete output_file_stream_;
//      output_file_stream_ = NULL;
//    }
//    // Redirect cout outputs to this file:
//    output_file_stream_ = new std::ofstream(output_file->value());
//    std::cout.rdbuf(output_file_stream_->rdbuf());
//  }
}

void CDataManager::CreateRepository(void) {
  set_repository(new std::map< std::string, IData *>);

  /// ==========================================================================
  /// CREATE FIXED DATAS
  /// ==========================================================================

  // These are global variables. So, their parent is ROOT_PARENT.
  
  /**
   * This is the initial seed value:
   */
  CDataInt64 *nseed = static_cast<CDataInt64 *>(
                        CreateDataByKeyString(
                          ROOT_PARENT,
                          STR(SEED),
                          KeyString::DATA_INT64
                        ));
  
  nseed->set_value(123456);

  /**
   * This value is initialized with nseed but it changes at every call of ran1
   * function:
   */
  CDataInt64 *idum = static_cast<CDataInt64 *>(
                        CreateDataByKeyString(
                          ROOT_PARENT,
                          STR(IDUM),
                          KeyString::DATA_INT64
                        ));
  idum->set_value(-1*nseed->value());

  
  /**
   * This value is initialized with nseed but it changes at every call of ran1
   * function:
   */
  CDataStdString *all_command_line = static_cast<CDataStdString *>(
                        CreateDataByKeyString(
                          ROOT_PARENT,
                          STR(ALL_COMMAND_LINE),
                          KeyString::DATA_STD_STRING
                        ));
  all_command_line->set_value("");
  
  
  /**
   * The output of CCalcRandomize:
   */
  CDataDouble *randomize_value = static_cast<CDataDouble *>(
                        CreateDataByKeyString(
                          ROOT_PARENT,
                          STR(RANDOMIZE_VALUE),
                          KeyString::DATA_DOUBLE
                        ));
  randomize_value->set_value(0.);

  /**
   * For cout:
   */
  CDataStdString *output_file = static_cast<CDataStdString *>(
                        CreateDataByKeyString(
                          ROOT_PARENT,
                          STR(OUTPUT_FILE),
                          KeyString::DATA_STD_STRING
                        ));
  output_file->set_value("");
  output_file->SetOnChange(f);

  /**
   * For cout:
   */
  CDataInt *output = static_cast<CDataInt *>(
                        CreateDataByKeyString(
                          ROOT_PARENT,
                          STR(OUTPUT),
                          KeyString::DATA_INT
                        ));
  output->set_value(0);

  /**
   * Number of decimals on screen:
   */
  CDataInt *precision = static_cast<CDataInt *>(
                        CreateDataByKeyString(
                          ROOT_PARENT,
                          STR(PRECISION),
                          KeyString::DATA_INT
                        ));
  precision->set_value(2);

  /**
   * Width of table columns:
   */
  CDataInt *table_col_width = static_cast<CDataInt *>(
                        CreateDataByKeyString(
                          ROOT_PARENT,
                          STR(TABLE_COL_WIDTH),
                          KeyString::DATA_INT
                        ));
  table_col_width->set_value(4);


  /**
   * Output encoding:
   */
  CDataStdString *encoding = static_cast<CDataStdString *>(
                        CreateDataByKeyString(
                          ROOT_PARENT,
                          STR(ENCODING),
                          KeyString::DATA_STD_STRING
                        ));

    /**
   * Iteration Number:
   */
  CDataInt64 *iteration_number = static_cast<CDataInt64 *>(
                        CreateDataByKeyString(
                          ROOT_PARENT,
                          STR(ITERATION_NUMBER),
                          KeyString::DATA_INT64
                        ));
  iteration_number->set_value(0);

    /**
   * Iteration Value:
   */
  CDataStdString *iteration_value = static_cast<CDataStdString *>(
                        CreateDataByKeyString(
                          ROOT_PARENT,
                          STR(ITERATION_VALUE),
                          KeyString::DATA_STD_STRING
                        ));
  iteration_value->set_value("");

  
#ifdef __APPLE__
    encoding->set_value("english_bn");
#endif
#ifdef __WIN32__
    // Windows doesn't have an easy way to colorize characters in the console.
    // OK
    encoding->set_value("english_bn");
#else // LINUX
    encoding->set_value("english_bn"); // english_col
#endif
  
  CStringTable::Instance()->set_encoding(encoding->value());
  


  /**
   * Calculation result:
   */
  CDataInt *result = static_cast<CDataInt *>(
                        CreateDataByKeyString(
                          ROOT_PARENT,
                          STR(RESULT),
                          KeyString::DATA_INT
                        ));
  result->set_value(0);
}


void CDataManager::AddData(const std::string & name, IData *data) {
    if(data != NULL) {
      data->set_experiment("");
      data->set_name(name);
      data->set_status(KeyString::STATUS_READY);
      // data->set_type(key);
      data->set_manager(manager());

      RemoveDataByName(data->parent(), data->name());
      //!before repository()->insert(std::pair<std::string, IData *>(data->parent() + "_" + data->name(), data));
      repository()->insert(std::pair<std::string, IData *>(data->name(), data));
      //!before manager()->set_with(data->parent(), data->name());
    }

}

IData *CDataManager::GetDataByName(IObject *parent,
                                   const std::string & name) {
  IData *data = NULL;

  std::map< std::string, IData *>::iterator it;
  //!before it = repository()->find(parent + "_" + name);
  it = repository()->find(name);
  if(it != repository()->end()) {
    data = it->second;
  }

  return data;
}

void CDataManager::RemoveDataByParent(IObject *parent) {
  if (repository() != NULL) {
    if (repository()->size() > 0) {
      for (std::map< std::string, IData *>::iterator it = repository()->begin();
           it != repository()->end(); ++it) {
        if ((it->second != NULL) && (it->second->parent() == parent)) {
          // Remove the data object:
          delete it->second;
          it->second = NULL;

          // Remove the map element:
          // Because of this, the function can not be called in a map loop.
          repository()->erase(it);
        }
      }
    }
  }
}

bool CDataManager::RemoveDataByName(IObject *parent,
                                    const std::string & name) {
  bool success = false;

  std::map< std::string, IData *>::iterator it;

  if (name == "*") {
    for (it = repository()->begin(); it != repository()->end(); ++it) {
      if (it->second->name().find("$") == std::string::npos) {
        // Remove the data object:
        delete it->second;
        it->second = NULL;

        // Remove the map element:
        // Because of this, the function can not be called in a map loop.
        repository()->erase(it);
      }
    }
    success = true;

  } else {
    //!before it = repository()->find(parent + "_" + name);
    it = repository()->find(name);
    if(it != repository()->end()) {
      // Remove the data object:
      delete it->second;
      it->second = NULL;

      // Remove the map element:
      // Because of this, the function can not be called in a map loop.
      repository()->erase(it);

      success = true;
    }
  }

  return success;
}

std::string CDataManager::GetStateFileName(std::string state_id) {
    std::string ret = STR(TEMP_FOLDER);
    ret += STR(DM_PRE_FILE_NAME);
    ret += state_id;
    ret += STR(SCRIPT_FILES_EXTENSION);
    return ret;
}

std::string CDataManager::GetExportFileName(std::string state_id) {
    std::string ret = STR(TEMP_FOLDER);
    ret += STR(DM_PRE_FILE_NAME);
    ret += state_id;
    ret += STR(DM_EXPORT_EXTENSION);
    return ret;
}



void CDataManager::SaveState(std::string state_id) {
    COutputDescriptor * od = new COutputDescriptor(true);
    od->name_ = GetStateFileName(state_id);
    od->description_ = "state";
    CFile::Remove(od->name_);
    manager()->logger()->SetNewOutputDescriptor(od);

    // ------------------
    if(repository()) {
        std::map< std::string, IData *>::iterator it;

        for (it = repository()->begin(); it != repository()->end(); ++it) {
            it->second->Print(PrintMode::NGASP);
        }
    }
    // ------------------

    manager()->logger()->WriteFile();
    manager()->logger()->RestorePreviousOutputDescriptor();
}

void CDataManager::ExportToJSON(std::string state_id) {
    COutputDescriptor * od = new COutputDescriptor(true);
    od->name_ = GetStateFileName(state_id);
    od->description_ = "export";
    CFile::Remove(od->name_);
    manager()->logger()->SetNewOutputDescriptor(od);

    // ------------------
    std::cout << "{\"dm\":[";
    if(repository()) {
        std::map< std::string, IData *>::iterator it;

        for (it = repository()->begin(); it != repository()->end(); ++it) {
            if (it != repository()->begin()) {
                std::cout << ",";
            }
            it->second->Print(PrintMode::JSON);
        }
    }
    std::cout << "]}";
    // ------------------

    manager()->logger()->WriteFile();
    manager()->logger()->RestorePreviousOutputDescriptor();
}
