/*
 * ngasp, a computational solution for performing next generation analysis of 
 * sequence polymorphisms using NGS data.
 * Copyright (c) 2015-2017, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
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
 *  \brief     ICalculation.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "ICalculation.h"

#include <string>
#include <sstream>
#include <cstdarg>
#include <cstdlib>  // rand())

#include "../language/CStringTable.h"
#include "../util/CStringTools.h"
#include "../messages/CLogger.h"
#include "../data_manager/CDataManager.h"

///*
// * *** OBSOLETE CONSTRUCTOR ***
// */
//ICalculation::ICalculation(KeyString name,
//                           KeyString brief_description) : IFunction() {
//  set_group(KeyString::OBJECT_CALC);
//  
//  //TODO: Desactivat perquè el rand() interferia amb el rand() de CCalcRandomize(). Es pot tornar a activar si els tests mstatspop-ngasp han passat correctament
//  //set_name(STR(RESERVED_DATA_NAME_PREFIX) + STR2(type) + CStringTools::ToNDigits(rand() % 9999, 4, '0'));
//  set_name(STR2(name));  //  + CStringTools::ToNDigits(1111, 4, '0')
//  
//  set_type(name);
//  set_brief_description(brief_description);
//  set_status(KeyString::STATUS_READY);
//  inputs_ = NULL;
//  outputs_ = NULL;
//  
//  options()->set_manager(manager());  
//}


ICalculation::ICalculation(KeyString name,
                           KeyString brief_description,
                           KeyString description,
                           KeyString author,
                           KeyString copyright,
                           KeyString citations,
                           KeyString see_also)
  : IFunction(name, 
              brief_description,
              description,
              author,
              copyright,
              citations,
              see_also) {
  set_group(KeyString::OBJECT_CALC);
  
  //TODO: Desactivat perquè el rand() interferia amb el rand() de CCalcRandomize(). Es pot tornar a activar si els tests mstatspop-ngasp han passat correctament
  //set_name(STR(RESERVED_DATA_NAME_PREFIX) + STR2(type) + CStringTools::ToNDigits(rand() % 9999, 4, '0'));
  //set_name(STR(RESERVED_DATA_NAME_PREFIX) + STR2(name) + CStringTools::ToNDigits(1111, 4, '0'));
  set_name(STR2(name));
  
  set_type(name);
  set_brief_description(brief_description);
  set_status(KeyString::STATUS_READY);
  inputs_ = NULL;
  outputs_ = NULL;
  
  options()->set_manager(manager());  
}


ICalculation::~ICalculation() {
  if (inputs_ != NULL) {
    delete inputs_;
    inputs_ = NULL;
  }

  if (outputs_ != NULL) {
    delete outputs_;
    outputs_ = NULL;
  }

}


/*
 * The list of inputs and outputs is initialized with:
 *     first(parent) : ROOT_PARENT
 *     second(name)  : ""
 */
bool ICalculation::SetInputsOutputs(const std::string & variable,
                                    const std::string & value) {

  bool isInputOrOutput = false;

  std::string var = CStringTools::ToLower(variable);

  std::string::size_type capacity = 0;
  std::string::size_type loc = std::string::npos;

  for (int i=0; i<2; i++) { // Iteration 0 for inputs, iteration 1 for outputs:

    if (i==0) { loc = var.find("inputs"); }
    if (i==1) { loc = var.find("outputs"); }

    if (loc != std::string::npos) {
      isInputOrOutput = true;

      std::string val = value;

      CStringTools::RemoveBlanks(val);

      std::vector<std::string> elems = CStringTools::SplitStrings(val,
                                                  STR(CALC_DATAS_SEPARATOR)[0]);

      if (i==0) { capacity = inputs_->size(); }
      if (i==1) { capacity = outputs_->size(); }

      if (elems.size() > capacity) {
        ERROR_MSG << STR(TOO_MANY_VALUES) END_MSG;
      }
      if (elems.size() < capacity) {
        ERROR_MSG << STR(TOO_FEW_VALUES) END_MSG;
      }
      if (elems.size() == capacity) {
        for (std::string::size_type j=0; j<elems.size(); j++) {
          CStringTools::Replace(elems[j], "\"", "");
          if (i==0) {
            inputs_->at(j).first = ROOT_PARENT;
            inputs_->at(j).second = elems[j]; 
          }
          if (i==1) {
            outputs_->at(j).first = ROOT_PARENT;
            outputs_->at(j).second = elems[j]; 
          }
        }
      }
    }
  }

  return isInputOrOutput;
}

void ICalculation::PrintInputsOutputs(int col_with) {
  std::string value;

  for (std::string::size_type i=0; i<inputs_->size(); ++i) {
    std::ostringstream s;
    s << "Input" << (i+1);
    std::string var_name = s.str();
    if (i < inputs_->size()) {
      try {
         value = inputs_->at(i).second;
      }
      catch(...) {
        value = STR(TABLE_EMPTY_FIELD);
      }
    } else {
      value = STR(TABLE_EMPTY_FIELD);
    }
    PrintValue(var_name, value, col_with, 0, PrintMode::NORMAL);
  }

  for (std::string::size_type i=0; i<outputs_->capacity(); ++i) {
    std::ostringstream s;
    s << "Output" << (i+1);
    std::string var_name = s.str();
    if (i < outputs_->size()) {
      try {
         value = outputs_->at(i).second;
      }
      catch(...) {
        value = STR(TABLE_EMPTY_FIELD);
      }
    } else {
      value = STR(TABLE_EMPTY_FIELD);
    }
    PrintValue(var_name, value, col_with, 0, PrintMode::NORMAL);
  }
}

/*
 * The list of inputs and outputs is initialized with:
 *     first(parent) : ROOT_PARENT
 *     second(name)  : ""
 */
void ICalculation::set_num_inputs(int value) {
  if (inputs_ != NULL) {
    delete inputs_;
    inputs_ = NULL;
  }

  inputs_ = new std::vector<std::pair<IObject *, std::string> >(value);
  for (int i=0; i<value; i++) {
    inputs_->at(i).first = ROOT_PARENT;
    inputs_->at(i).second = "";
  }
}

/*
 * The list of inputs and outputs is initialized with:
 *     first(parent) : ROOT_PARENT
 *     second(name)  : ""
 */
void ICalculation::set_num_outputs(int value) {
  if (outputs_ != NULL) {
    delete outputs_;
    outputs_ = NULL;
  }

  outputs_ = new std::vector<std::pair<IObject *, std::string> >(value);
  for (int i=0; i<value; i++) {
    outputs_->at(i).first = ROOT_PARENT;
    outputs_->at(i).second = "";
  }
}

IObject *ICalculation::GetParentInput(int position) {
  IObject *ret = NULL;

  try {
    ret = inputs_->at(position).first;
  }
  catch (std::out_of_range e) {
  }
  
  return ret;
}

IObject *ICalculation::GetParentOutput(int position) {
  IObject *ret = NULL;

  try {
    ret = outputs_->at(position).first;
  }
  catch (std::out_of_range e) {
  }
  
  return ret;
}

std::string ICalculation::GetInputName(int position) {
  std::string ret = "null";

  try {
    ret = inputs_->at(position).second;
  }
  catch (std::out_of_range e) {
  }
  
  if (ret == "") {
    ret = "null";
  }
  
  return ret;
}

std::string ICalculation::GetOutputName(int position) {
  std::string ret = "null";

  try {
    ret = outputs_->at(position).second;
  }
  catch (std::out_of_range e) {
  }

  if (ret == "") {
    ret = "null";
  }

  return ret;
}


bool ICalculation::SetInput(IData *data) {
  bool ret = false;
  if (data != NULL) {
    ret = SetInput(data->parent(), data->name());
  } else {
    ERROR_MSG << STR(NULL_INPUT) << name() END_MSG;
  }
  return ret;
}

// This function sets the input to the first empty vector position.
// If all positions are occupied, all the vector is emptied and the input is
// set in the first vector position.
bool ICalculation::SetInput(IObject *parent,
                            const std::string & name) {
  bool set = false;
  
  /*
   * An initialized input or output has these values:
   *     first(parent) : ROOT_PARENT
   *     second(name)  : ""
   */

  for (std::string::size_type i=0; ((i<inputs_->size()) && (set==false)); i++) {
    if ((inputs_->at(i).first == ROOT_PARENT) && (inputs_->at(i).second == "")) {
      inputs_->at(i).first = parent;
      inputs_->at(i).second = name;
      set = true;
    }
  }
  
  if (set==false) {
    inputs_->at(0).first = parent;
    inputs_->at(0).second = name;
    for (std::string::size_type i=1; i<inputs_->size(); i++) {
      inputs_->at(i).first = ROOT_PARENT;
      inputs_->at(i).second = "";
    }
  }
  return set;
}

bool ICalculation::SetOutput(IData *data) {
  bool ret = false;
  if (data != NULL) {
    ret = SetOutput(data->parent(), data->name());
  } else {
    ERROR_MSG << STR(NULL_INPUT) << name() END_MSG;
  }
  return ret;
}

// This function sets the output to the first empty vector position.
// If all positions are occupied, all the vector is emptied and the output is
// set in the first vector position.
bool ICalculation::SetOutput(IObject *parent,
                             const std::string & name) {
  bool set = false;
  
  /*
   * An initialized input or output has these values:
   *     first(parent) : ROOT_PARENT
   *     second(name)  : ""
   */
  
  for (std::string::size_type i=0; ((i<outputs_->size()) && (set==false)); i++) {
    if ((outputs_->at(i).first == ROOT_PARENT) && (outputs_->at(i).second == "")) {
      outputs_->at(i).first = parent;
      outputs_->at(i).second = name;
      set = true;
    }
  }
  
  if (set==false) {
    outputs_->at(0).first = parent;
    outputs_->at(0).second = name;
    for (std::string::size_type i=1; i<outputs_->size(); i++) {
      outputs_->at(i).first = ROOT_PARENT;
      outputs_->at(i).second = "";
    }
  }
  return set;
}

/**
 * This function returns a JSON description of the calculation.
 * @return JSON string
 */
std::string ICalculation::GetCalcInformation(void) {
  std::string ret, inputs, outputs, name;
  int id_in = 0, id_out = 0;
  std::string field;
  
  bool first_output = true;
  
  for(auto it = options()->GetFirstOptionIterator();
    it != options()->GetLastOptionIterator(); ++it) {
    
    name = (*it)->short_name();
    if ((name != "") && (name.at(name.length()-1) == '_')) {
      name = name.substr(0, name.length()-1);
    }
    
    if ((*it)->direction() == COption::OPTDIR::READ) {
      
      if (it != options()->GetFirstOptionIterator()) {
        inputs += ",";
      }
      inputs += "{";
      inputs += "\"id\":" + CStringTools::ToString(id_in) + ",";

      field = name;
      inputs += "\"name\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

      field = STR2((*it)->data_type());
      inputs += "\"type\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";
      
      field = STR2((*it)->group());
      inputs += "\"group\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

      field = (*it)->long_name();
      inputs += "\"long_name\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";
      
      field = (*it)->description();
      inputs += "\"description\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

      field = STR2((*it)->example());
      inputs += "\"example\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

      field = STR2((*it)->only());
      inputs += "\"only\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

      field = STR2((*it)->def_val());
      inputs += "\"def_val\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

      field = CStringTools::ToString((*it)->min_value());
      inputs += "\"min_value\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

      field = CStringTools::ToString((*it)->max_value());
      inputs += "\"max_value\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

      field = CStringTools::ToString((*it)->mandatory());
      inputs += "\"required\":\"" + CStringTools::ScapeForJSONfield(field) + "\""; //<--- The last one without the coma
  
      inputs += "}";
      id_in++;
      
    } else {
      if ((*it)->direction() == COption::OPTDIR::WRITE) {
        
        if (first_output == false) {
          outputs += ",";
        } else {
            first_output = false;
        }
        outputs += "{";
        outputs += "\"id\":" + CStringTools::ToString(id_out) + ",";
        
        field = name;
        outputs += "\"name\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

        field = STR2((*it)->data_type());
        outputs += "\"type\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

        field = STR2((*it)->group());
        outputs += "\"group\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

        field = (*it)->long_name();
        outputs += "\"long_name\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

        field = (*it)->description();
        outputs += "\"description\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

        field = STR2((*it)->example());
        outputs += "\"example\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

        field = STR2((*it)->only());
        outputs += "\"only\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

        field = STR2((*it)->def_val());
        outputs += "\"def_val\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

        field = CStringTools::ToString((*it)->min_value());
        outputs += "\"min_value\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

        field = CStringTools::ToString((*it)->max_value());
        outputs += "\"max_value\":\"" + CStringTools::ScapeForJSONfield(field) + "\",";

        field = CStringTools::ToString((*it)->mandatory());
        outputs += "\"required\":\"" + CStringTools::ScapeForJSONfield(field) + "\""; //<--- The last one without the coma
        
        outputs += "}";
        id_out++;
      }      
    }
  }
    
  ret += "\"inputs\":[" + inputs + "],";
  ret += "\"outputs\":[" + outputs + "]";
  

  return ret;
}
