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
 *  \brief     CDataManager.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      April 27, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#ifndef BACKEND_SRC_DATA_MANAGER_CDATAMANAGER_H_
#define BACKEND_SRC_DATA_MANAGER_CDATAMANAGER_H_

#include <map>
#include <string>

#include "IData.h"
#include "../IBase.h"
#include "CDataFactory.h"
#include "../calculations/CAllCalculations.h"

#define READ_ALL_RECORDS -1

#define ROOT_PARENT NULL
#define I_AM_YOUR_PARENT GetPointerToTheObject()

#define DM_NEW_CALC(calc) calc = manager()->all_calculations()->GetNewCalculation(I_AM_YOUR_PARENT, calc, #calc);  // Calculation Developer creates a new calc (B) inside a calc (A). A says I_AM_YOUR_PARENT to B.
#define DM_GET_CALC(calc) calc = manager()->all_calculations()->GetCalculationByName(ROOT_PARENT, #calc);          // Calculation Developer can only get global created calcs. So, ROOT_PARENT.
#define DM_DEL_CALC(calc) manager()->all_calculations()->RemoveCalculationByName(calc->parent(), calc->name());    // To identify the calc to be removed, it is necessary to pass its parent and name.

#define DM_NEW_DATA(var) var = manager()->data_manager()->GetNewData(I_AM_YOUR_PARENT, var, #var);                 // Calculation Developer creates variables inside a calculation. So, the variable's parent is the calculation.
#define DM_NEW_DATA2(var, i) { std::stringstream ss; ss << #var; ss << i; var[i] = manager()->data_manager()->GetNewData(I_AM_YOUR_PARENT, var[i], ss.str()); }  // The same as DM_NEW_DATA.
#define DM_DEL_DATA(var) manager()->data_manager()->RemoveDataByName(var->parent(), var->name());                  // To identify the var to be removed, it is necessary to pass its parent and name.
#define DM_DEL_ALL_LOCAL_DATA manager()->data_manager()->RemoveDataByParent(I_AM_YOUR_PARENT);

#define DM_GET_INPUTS SCounter dm_count_in(manager(), name(), options()->size(COption::OPTDIR::READ));
#define DM_GET_OUTPUTS SCounter dm_count_out(manager(), name(), options()->size(COption::OPTDIR::WRITE));

// If DM_INPUT / DM_OUTPUT can not reach the variable, then it is created (with parent = current calculation).
#define DM_INPUT(var) if (GetInputName(dm_count_in.counter()) == "null") { DM_NEW_DATA(var); var->set_auto_created(true); } else { var = manager()->data_manager()->GetDataByName(var, GetParentInput(dm_count_in.counter()), GetInputName(dm_count_in.counter()) ); if (var == NULL) { DM_NEW_DATA(var) } } dm_count_in.IncCounter(); 
#define DM_INPUT2(T, var) T *var = NULL; DM_INPUT(var)
#define DM_OUTPUT(var) if (GetOutputName(dm_count_out.counter()) == "null") { DM_NEW_DATA(var); var->set_auto_created(true); } else { var = manager()->data_manager()->GetDataByName(var, GetParentOutput(dm_count_out.counter()), GetOutputName(dm_count_out.counter()) ); if (var == NULL) { DM_NEW_DATA(var) } } dm_count_out.IncCounter(); 
#define DM_OUTPUT2(T, var) T *var = NULL; DM_OUTPUT(var)


#define DM_INOUTPUT(var) DM_OUTPUT(var)
#define DM_INOUTPUT2(T, var) DM_OUTPUT2(T, var)

// DM_GET_DATAn can only be used for getting global variables. So, parent is ROOT_PARENT.
#define DM_GET_DATA2(var, name) var = manager()->data_manager()->GetDataByName(var, ROOT_PARENT, name);
#define DM_GET_DATA3(T, var, name) T *var = NULL; var = manager()->data_manager()->GetDataByName(var, ROOT_PARENT, name);
#define DM_END 

#define DM_RESULT(var) CDataInt * var = (CDataInt *)manager()->data_manager()->GetDataByName(ROOT_PARENT, STR(RESULT));
#define DM_ITERATION_NUMBER(var) CDataInt64 * var = (CDataInt64 *)manager()->data_manager()->GetDataByName(ROOT_PARENT, STR(ITERATION_NUMBER));
#define DM_ITERATION_VALUE(var) CDataStdString * var = (CDataStdString *)manager()->data_manager()->GetDataByName(ROOT_PARENT, STR(ITERATION_VALUE));


class CDataManager : public IBase {
 public:
  CDataManager();
  virtual ~CDataManager();

 public:
  template <class T>
  T *GetNewData(IObject *parent, T *var, const std::string & name) {
    T ref;
    return static_cast<T *>(CreateDataByKeyString(parent, name, ref.type_key()));
  }

  IData *CreateDataByType(IObject *parent,
                          const std::string & name,
                          const std::string & type) {
    IData *data = GetDataByName(parent, name);  // Find existing object

    if (data == NULL) {
      if (name.find(STR(RESERVED_DATA_NAME_PREFIX)) != 0) {
        data = manager()->data_factory()->GetData(type);
        if (data != NULL) {
          data->set_parent(parent);
          AddData(name, data);
        }
      } else {
        ERROR_MSG << STR(DIM_RESERVED_NAME) END_MSG;
      }
    } else {
      WARNING_MSG << "Data " << name << " already exists..." END_MSG;
    }

    return data;
  }

  IData *CreateDataByKeyString(IObject *parent,
                               const std::string & name,
                               KeyString key) {
    IData *data = GetDataByName(parent, name);  // Find existing object

    if (data == NULL) {
      data = manager()->data_factory()->GetData(key);
      if (data != NULL) {
        data->set_parent(parent);
        AddData(name, data);
      }
    } else {
      WARNING_MSG << "Data " << name << " already exists..." END_MSG;
    }

    return data;
  }

  void CreateRepository(void);
  void DestroyRepository(void);

  void AddData(const std::string & name, IData *data);

  template <class T>
  T *GetDataByName(T *var, IObject *parent,
                           const std::string & name) {
    T *ret = NULL;
    T ref = T();

    IData *data = GetDataByName(parent, name);
    if(data != NULL) {
      if (data->type() != ref.type()) {
        ERROR_MSG << STR(DATA_NAME) << name << STR(END_STRING)
                  << STR(DATA_EXPECTED) << ref.type() << STR(END_STRING)
                  << STR(BUT_FOUND) << data->type() << STR(END_ERROR)
                  END_MSG;
      } else {
        ret = static_cast<T *>(data);
      }
    } else {
      ERROR_MSG << name << " not found. Maybe input/output not well defined..." END_MSG;
    }
    return ret;
  }
  IData *GetDataByName(IObject *parent,
                       const std::string & name);

  void RemoveDataByParent(IObject *parent);
  bool RemoveDataByName(IObject *parent,
                        const std::string & name);

 private:
  std::map<std::string, IData *> *repository_;

 public:
   inline void set_repository(std::map<std::string, IData *> *repository) {
     repository_ = repository;
   }
   inline std::map<std::string, IData *> *repository(void) const {
     return repository_;
   }

   std::string GetStateFileName(std::string state_id);
   std::string GetExportFileName(std::string state_id);
   void SaveState(std::string state_id);
   void ExportToJSON(std::string state_id);
};

#endif  // BACKEND_SRC_DATA_MANAGER_CDATAMANAGER_H_
