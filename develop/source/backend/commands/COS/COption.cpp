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
 *  \brief     COption.cpp
 *  \details
 *  \author    gvera, jjene
 *  \version   1.0
 *  \date      Mar 31, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include <string>

#include "COption.h"

#include "../../language/CStringTable.h"

COption::COption() {
  set_direction(COption::OPTDIR::READ);
  set_data_type(KeyString::UNDEFINED_STRING);
  set_short_name(KeyString::UNDEFINED_STRING);
  set_long_name(KeyString::UNDEFINED_STRING);
  set_description(KeyString::UNDEFINED_STRING);
  set_example(KeyString::UNDEFINED_STRING);
  set_citations(KeyString::UNDEFINED_STRING);
  set_only(KeyString::UNDEFINED_STRING);
  set_def_val(KeyString::UNDEFINED_STRING);
  set_min_value(0.0);
  set_max_value(0.0);
  
  set_opt_type(COption::OPTTYPE_undefined);
  set_arg_type(COption::OPTTYPE_undefined);

  set_mandatory(false);
  set_activated(false);
  set_values(new std::list<CValue *>);
}

//COption::COption(
//    KeyString short_name,
//    KeyString long_name,
//    KeyString description,
//    COption::ARGTYPES arg_type,
//    COption::OPTTYPES opt_type) : COption() {
//  set_short_name(short_name);
//  set_long_name(long_name);
//  set_description(description);
//  set_opt_type(opt_type);
//  set_arg_type(arg_type);
//  set_mandatory((opt_type == COption::OPTTYPE_mandatory)?true:false);
//  set_activated(false);
//}

COption::COption(COption::OPTDIR direction,
                 KeyString group,
                 KeyString data_type,
                 KeyString short_name,
                 KeyString long_name,
                 KeyString description,
                 KeyString example,
                 KeyString citations,
                 KeyString only,
                 KeyString def_val,
                 double min_value,
                 double max_value,
                 COption::ARGTYPES arg_type,
                 COption::OPTTYPES opt_type) : COption() {
  set_direction(direction);
  set_group(group);
  set_data_type(data_type);
  set_short_name(short_name);
  set_long_name(long_name);
  set_description(description);
  set_example(example);
  set_citations(citations);
  set_only(only);
  set_def_val(def_val);
  set_opt_type(opt_type);
  set_arg_type(arg_type);
  set_mandatory((opt_type == COption::OPTTYPE_mandatory)?true:false);
  set_activated(false);  
  set_min_value(min_value);
  set_max_value(max_value);
}
  

COption::~COption() {
  if (values()) {
    // Delete all list elements:
    std::list<CValue *>::iterator it = values()->begin();
    while (it != values()->end()) {
      delete *it;
      it++;
    }

    // Delete the list:
    values()->clear();
    delete values_;
    values_ = NULL;
  }  
}

