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
 *  \brief     ICalculation.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_CALCULATIONS_ICALCULATION_H_
#define BACKEND_SRC_CALCULATIONS_ICALCULATION_H_

#include <vector>
#include <string>
#include <sstream>
#include <cstdarg>
#include <stdexcept>

#include "../IBase.h"
#include "../IObject.h"
#include "../IFunction.h"
#include "../language/CStringTable.h"
#include "../data_manager/IData.h"
#include "CConnectorDef.h"

#define PARAMS_SEPARATOR ' '

class ICalculation : public IBase, public IObject, public IFunction {
 public:
  struct SCounter {
    CManager *manager_;
    std::string name_;
    int total_;
    int counter_;
    
    SCounter(CManager *manager, std::string name, int total)
    : manager_(manager), name_(name), total_(total), counter_(0) {}
    ~SCounter() {
      if (counter_ != total_) {
        ERROR_MSG4 << "Number of in/outputs not well defined in calculation "
                   << name_
                   << "("
                   << counter_ 
                   << "/"
                   << total_
                   << ")"
                   << "..." END_MSG;
      }
    }
    inline void IncCounter(void) { counter_++; }
    inline int counter(void) const { return counter_; }
  };

//  ICalculation(KeyString name,
//               KeyString brief_description);
  
  ICalculation(KeyString name,
               KeyString brief_description,
               KeyString description,
               KeyString author,
               KeyString copyright,
               KeyString citations,
               KeyString see_also);

  virtual ~ICalculation();

  virtual void Prepare(void) = 0;
  virtual void Calculate(bool dry_run) = 0;
  virtual void Finalize(void) = 0;

  virtual ICalculation* clone() const = 0;  // Used by the Factory

 protected:
  std::vector<std::pair<IObject *, std::string> > *inputs_;
  std::vector<std::pair<IObject *, std::string> > *outputs_;

 public:
  void set_num_inputs(int value);
  void set_num_outputs(int value);
  inline int num_inputs(void) const { return inputs_->size(); }
  inline int num_outputs(void) const { return outputs_->size(); }
  std::string GetInputName(int position);
  std::string GetOutputName(int position);
  IObject *GetParentInput(int position);
  IObject *GetParentOutput(int position);
  bool SetInput(IData *data);
  bool SetInput(IObject *parent, const std::string & name);
  bool SetOutput(IData *data);
  bool SetOutput(IObject *parent, const std::string & name);

  void PrintInputsOutputs(int col_with);
  std::string GetCalcInformation(void);
  //int GetNumConnections(ConnectorDirection search_type);

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  void Print(PrintMode print_mode) {
    int col_with = PrintHeader(print_mode);
    PrintInputsOutputs(col_with);
    PrintFooter(print_mode);
  }

  std::size_t Size(void) const {
    long int total = sizeof(*this);
    return total;
  }

  void Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action) {
    bool set = false;
    set = SetInputsOutputs(this_info->data_variable(), ref_info->value());
    EvalSet(manager(), set, this_info, ref_info);
  }

  void Get(CDataAccess *data_access) {
    bool get = false;
    EvalGet(manager(), get, data_access);
  }
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 
 protected:
  bool SetInputsOutputs(const std::string &variable, const std::string &value);
};

#endif  // BACKEND_SRC_CALCULATIONS_ICALCULATION_H_
