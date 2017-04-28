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
 *  \brief   CFromYaml.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Nov 16, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_INSTRUCTIONS_FROMYAMEL_H_
#define BACKEND_SRC_INSTRUCTIONS_FROMYAMEL_H_

#include <string>
#include <list>

#include "../IBase.h"

struct SConstantYaml {
  std::string name;
  std::string by;
};

struct SVariableYaml {
  std::string name;
  std::string as;
  std::string value;
};

struct SCalculationYaml {
  std::string name;
  std::string type;
  std::string inputs;
  std::string outputs;
};

//struct SLineYaml {
//  SLineYaml() {
//    level = 0;
//    item_start = false;
//  }
//  SLineYaml(const SLineYaml & other) {
//    tag = other.tag;
//    value = other.value;
//    level = other.level;
//    item_start = other.item_start;
//  }
//  std::string tag;
//  std::string value;
//  int level;
//  bool item_start;
//};

class CFromYaml : public IBase {
 public:
  CFromYaml() {}
  virtual ~CFromYaml();

 public:
  std::list<std::string> constants_;
  std::list<std::string> variables_;
  std::list<std::string> calculations_;

 public:
  std::string ToNgasp(std::string yaml);

// private:
//  SLineYaml GetLine(std::string & yaml);
//  std::string::size_type GetListPosition(const std::string list_name,
//                                         const std::string & yaml);
};

#endif  // BACKEND_SRC_INSTRUCTIONS_FROMYAMEL_H_
