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
 *  \brief     CFromYaml.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Nov 16, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CFromYaml.h"

#include <string>
#include <list>
/*!disabled #include "yaml-cpp/yaml.h" */

#include "../util/CStringTools.h"

/*
std::string::size_type CFromYaml::GetListPosition(const std::string list_name,
                                                  const std::string & yaml) {
  return yaml.find(list_name + ":", 0);
}

SLineYaml CFromYaml::GetLine(std::string & yaml) {
  SLineYaml ret;

  std::string line = CStringTools::GetString(yaml, tPosition::GET_LEFT, '\n');
  yaml = CStringTools::GetString(yaml, tPosition::GET_RIGHT, '\n');

  char ch = '\x0';
  ret.level = 0;
  bool counting_spaces = true;
  for (unsigned int i = 0;
       ((i < line.length()) && (counting_spaces)); i++) {
    ch = line.at(i);
    if (ch == ' ') {
      ret.level++;
    } else {
      counting_spaces = false;
      line = line.substr(ret.level);
    }
  }

  std::vector<std::string> vec = CStringTools::SplitStrings(line, ':');
  ret.tag = vec[0];

  if (vec.size() > 1) {
    ret.value = vec[1];
  }

  if (ret.tag.find("- ", 0) != std::string::npos) {
    ret.tag = ret.tag.substr(2);
    ret.level+=2;
  }

  return ret;
}*/

CFromYaml::~CFromYaml() {
  constants_.clear();
  variables_.clear();
  calculations_.clear();
}


std::string CFromYaml::ToNgasp(std::string yaml_file) {
  std::string ret = "", prints;
/*!disabled
  YAML::Node yaml_content = YAML::LoadFile(yaml_file);

  {
    YAML::Node include_file = yaml_content["include"];

    if (include_file.IsScalar()) {
      ret += ToNgasp(include_file.as<std::string>());
    }
  }

  {
    YAML::Node list = yaml_content["constants"];

    if (list.IsSequence()) {
      for (std::size_t i = 0; i < list.size(); i++) {
        if (list[i].IsMap()) {
          ret += STR(CMD_CONSTANT);
          ret += STR(SPACE);
          ret += "--";
          ret += STR(CONSTANT_NAME_LONG);
          ret += STR(SPACE);
          ret += list[i]["name"].as<std::string>();
          ret += STR(SPACE);
          ret += "--";
          ret += STR(CONSTANT_BY_LONG);
          ret += STR(SPACE);
          ret += list[i]["by"].as<std::string>();
          ret += STR(EOL);
        }
      }
    }
  }

  {
    YAML::Node list = yaml_content["variables"];

    if (list.IsSequence()) {
      for (std::size_t i = 0; i < list.size(); i++) {
        if (list[i].IsMap()) {
          ret += STR(CMD_DIM);
          ret += STR(SPACE);
          ret += "--";
          ret += STR(DIM_NAME_LONG);
          ret += STR(SPACE);
          ret += list[i]["name"].as<std::string>();
          ret += STR(SPACE);
          ret += "--";
          ret += STR(DIM_AS_LONG);
          ret += STR(SPACE);
          ret += list[i]["as"].as<std::string>();
          ret += STR(EOL);

          if (list[i]["value"].IsNull() == false) {
            ret += STR(CMD_SET_VALUE);
            ret += STR(SPACE);
            ret += "--";
            ret += STR(SET_TO_LONG);
            ret += STR(SPACE);
            ret += list[i]["name"].as<std::string>();
            ret += STR(SPACE);
            ret += "--";
            ret += STR(SET_EQ_LONG);
            ret += STR(SPACE);
            ret += list[i]["value"].as<std::string>();
            ret += STR(EOL);
          }
        }
      }
    }
  }

  {
    YAML::Node list = yaml_content["values"];

    if (list.IsSequence()) {
      for (std::size_t i = 0; i < list.size(); i++) {
        if (list[i].IsMap()) {
          ret += STR(CMD_SET_VALUE);
          ret += STR(SPACE);
          ret += "--";
          ret += STR(SET_TO_LONG);
          ret += STR(SPACE);
          ret += list[i]["name"].as<std::string>();
          ret += STR(SPACE);
          ret += "--";
          ret += STR(SET_EQ_LONG);
          ret += STR(SPACE);
          ret += list[i]["value"].as<std::string>();
          ret += STR(EOL);
        }
      }
    }
  }

  {
    YAML::Node include_file = yaml_content["experiment"];

    if (include_file.IsScalar()) {
      if (include_file.as<std::string>() == "load") {
        ret += STR(INCLUDE_VALUES);
        ret += STR(EOL);
      }
    }
  }

  {
    YAML::Node list = yaml_content["calculations"];

    if (list.IsSequence()) {
      for (std::size_t i = 0; i < list.size(); i++) {
        if (list[i].IsMap()) {
          ret += STR(CMD_CALC);
          ret += STR(SPACE);
          ret += "--";
          ret += STR(CALC_NAME_LONG);
          ret += STR(SPACE);
          ret += list[i]["name"].as<std::string>();
          ret += STR(SPACE);
          ret += "--";
          ret += STR(CALC_AS_LONG);
          ret += STR(SPACE);
          ret += list[i]["type"].as<std::string>();
          ret += STR(EOL);

          ret += STR(CMD_SET_VALUE);
          ret += STR(SPACE);
          ret += "--";
          ret += STR(SET_TO_LONG);
          ret += STR(SPACE);
          ret += list[i]["name"].as<std::string>();
          ret += STR(VARIABLE_SEPARATOR);
          ret += STR(INPUTS_PARAM);
          ret += STR(SPACE);
          ret += "--";
          ret += STR(SET_EQ_LONG);
          ret += STR(SPACE);
          ret += STR(DOUBLE_QUOTE);

          YAML::Node inputs = list[i]["inputs"];
          if (inputs.IsSequence()) {
            for (std::size_t j = 0; j < inputs.size(); j++) {
              if (j != 0) {
                ret += STR(CALC_DATAS_SEPARATOR);
              }
              ret += inputs[j].as<std::string>();
            }
          }

          ret += STR(DOUBLE_QUOTE);
          ret += STR(EOL);


          ret += STR(CMD_SET_VALUE);
          ret += STR(SPACE);
          ret += "--";
          ret += STR(SET_TO_LONG);
          ret += STR(SPACE);
          ret += list[i]["name"].as<std::string>();
          ret += STR(VARIABLE_SEPARATOR);
          ret += STR(OUTPUTS_PARAM);
          ret += STR(SPACE);
          ret += "--";
          ret += STR(SET_EQ_LONG);
          ret += STR(SPACE);
          ret += STR(DOUBLE_QUOTE);

          prints = "";
          YAML::Node outputs = list[i]["outputs"];
          if (outputs.IsSequence()) {
            for (std::size_t j = 0; j < outputs.size(); j++) {
              if (j != 0) {
                ret += STR(CALC_DATAS_SEPARATOR);
              }
              ret += outputs[j].as<std::string>();

              prints += STR(CMD_PRINT);
              prints += STR(SPACE);
              prints += "--";
              prints += STR(PRINT_NAME_LONG);
              prints += STR(SPACE);
              prints += outputs[j].as<std::string>();
              prints += STR(SPACE);
              prints += "--";
              prints += STR(PRINT_MODE_JSON);
              prints += STR(EOL);
            }
          }

          ret += STR(DOUBLE_QUOTE);
          ret += STR(EOL);
        }

        ret += STR(CMD_RUN);
        ret += STR(SPACE);
        ret += "--";
        ret += STR(RUN_NAME_LONG);
        ret += STR(SPACE);
        ret += list[i]["name"].as<std::string>();
        ret += STR(EOL);

        ret += prints;
      }
    }
  }
*/
  return ret;
}