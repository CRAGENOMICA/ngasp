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
 *  \brief     CStringTools.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 8, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CStringTools.h"

#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <boost/algorithm/string.hpp>

#include "../language/CStringTable.h"


CStringTools::CStringTools() {
}

CStringTools::~CStringTools() {
}

/**
 * @param text is the field content to be printed.
 * @param column_width is the space for the field. The space for column
 *       separator has been already discounted even both left and right margins.
 * @param is_number TBD
 * @param selected  TBD
 * @return the field content with the separator prepared to be printed.
 */
std::string CStringTools::PrepareField(std::string text,
                                       int column_width,
                                       bool is_number,
                                       bool selected) {
  std::string field;

  if (selected) {
    field += STR(TABLE_FIELD_SELECTED);
  } else {
    field += STR(TABLE_COL_MARGIN);
  }

  int text_length = text.length();

  if (text_length > column_width) {
    field += text.substr(0, column_width-STR(TABLE_TEXT_CUT).length());
    field += STR(TABLE_TEXT_CUT);
  } else {
    if (is_number) {  // Right alignment
    } else {  // Left alignment
      field += text;
    }
    for (int i = 0; i < column_width-text_length; i++) {
      field += STR(SPACE);
    }
    if (is_number) {  // Right alignment
      field += text;
    } else {  // Left alignment
    }
  }

  field += STR(TABLE_COL_MARGIN);
  field += STR(TABLE_COL_SEPARATOR);

  return field;
}


std::string CStringTools::ToUpper(std::string in) {
  std::string out = in;
  std::transform(out.begin(), out.end(), out.begin(), ::toupper);
  return out;
}

std::string CStringTools::ToLower(std::string in) {
  std::string out = in;
  std::transform(out.begin(), out.end(), out.begin(), ::tolower);
  return out;
}

/**
 * Split the string into a vector of std::string.
 *
 * For example: text = "add string \"this is a string with space!\"";
 * Result: "add"
 *         "string"
 *         "this is a string with space!"
 */
std::vector<std::string> CStringTools::SplitStrings(std::string text,
                                                    char separator) {

  // Split the string:
  std::vector<std::string> elems;
  std::string param;

  for(size_t i=0; i < text.length(); i++) {
    char c = text[i];
    if(c == separator) {  // The end of the current param:
      if (param != "") {
        elems.push_back(param);  // Insert the current param
        param = "";  // Clear the param (We do not want to insert it twice!)
      }
    } else if(c == '\"') {  // Start of a quoted param:
        param = "\"";
        i++;
        while(text[i] != '\"' ) {
          param += text[i];
          i++;
        }
        param += "\"";
        // Empty params are accepted here for "":
        // if (param != "") {
          elems.push_back(param);  // Insert the current param
          param = "";  // Clear the param (We do not want to insert it twice!)
        // }
    } else {
        param += c;
    }
  }

  if (param != "") {
    elems.push_back(param);  // Insert the last param
    param = "";
  }

//  Split the string (without taking into acount quotes):
//
//  std::vector<std::string> elems;
//  std::stringstream ss(text);
//  std::string item;
//  while (std::getline(ss, item, separator)) {
//    elems.push_back(item);
//  }

  return elems;
}

/**
 * Split the string into a vector of numbers.
 */
std::vector<long int> CStringTools::SplitNumbers(std::string text,
                                                char separator) {
  // Split the string:
  std::vector<long int> elems;
  std::stringstream ss(text);
  std::string sitem;
  long int nitem = 0;
  while (std::getline(ss, sitem, separator)) {
    std::istringstream ss(sitem);
    ss >> nitem;
    elems.push_back(nitem);
  }

  return elems;
}


void CStringTools::Replace(std::string &var,
                           const std::string &old_text,
                           const std::string &new_text) {
  boost::replace_all(var, old_text, new_text);
}

int CStringTools::ToInt(const std::string & str_value) {
  int ret = 0;
  std::istringstream ss(str_value);
  ss >> ret;
  return ret;
}

long int CStringTools::ToInt64(const std::string &str_value) {
  long int ret = 0;
  std::istringstream ss(str_value);
  ss >> ret;
  return ret;
}

float CStringTools::ToFloat(const std::string &str_value) {
  float ret = 0.0;
  std::istringstream ss(str_value);
  ss >> ret;
  return ret;
}

double CStringTools::ToDouble(const std::string &str_value) {
  double ret = 0.0;
  std::istringstream ss(str_value);
  ss >> ret;
  return ret;
}

float CStringTools::ToValue(std::string from_str_value, float to_value) {
  return ToFloat(from_str_value);
}

long int CStringTools::ToValue(std::string from_str_value, long int to_value) {
  return CStringTools::ToInt64(from_str_value);
}

int CStringTools::ToValue(std::string from_str_value, int to_value) {
  return CStringTools::ToInt(from_str_value);
}

double CStringTools::ToValue(std::string from_str_value, double to_value) {
  return CStringTools::ToDouble(from_str_value);
}
 
std::string CStringTools::ToValue(std::string from_str_value, std::string to_value) {
  return from_str_value;
}

char CStringTools::ToValue(std::string from_str_value, char to_value) {
  return (from_str_value != "")?from_str_value.at(0):'\x0';
}

bool CStringTools::IsNumber(const std::string &s) {
    bool ret = !s.empty();

    std::string::const_iterator it = s.begin();
    int dots = 0;

    if (ret) {
      while ((it != s.end()) && (ret == true)) {
        if (it == s.begin()) {
          ret = (std::isdigit(*it) || (*it == '.') || (*it == '+') || (*it == '-'));
        } else {
          ret = (std::isdigit(*it) || (*it == '.'));
        }

        if (*it =='.') {
          dots++;
        }

        if (ret) {
          ++it;
        }
      }
    }

    return ((ret == true) && (dots <= 1) && (it == s.end()));
  }

/**
 * str          return
 * -----------  --------
 * a.b[3]       true
 * a            true
 * .b           true
 * .b[3]        true
 *
 */
bool CStringTools::IsVariable(const std::string &str) {
    std::string valid_first_chars = STR(VARIABLE_NAME_VALID_1ST);
    std::string valid_chars       = STR(VARIABLE_NAME_VALID_CHARS);

    std::string::const_iterator it = str.begin();

    bool first_character_ok = false;
    for (std::string::size_type i = 0; ((i < valid_first_chars.size()) && (!first_character_ok)); ++i) {
      if (valid_first_chars.at(i) == (*it)) {
        first_character_ok = true;
      }
    }

    if (first_character_ok) {
      ++it;

      bool valid_char = true;

      while ((it != str.end()) && (valid_char == true)) {
        valid_char = false;
        for (std::string::size_type i = 0; ((i < valid_chars.size()) && (!valid_char)); ++i) {
          if (valid_chars.at(i) == (*it)) {
            valid_char = true;
          }
        }

        ++it;
      }
    }

    return !str.empty() && first_character_ok && it == str.end();
}

bool CStringTools::ToBoolean(const std::string &str_value) {
  bool ret = false;
  if ((str_value == "1") ||
      (ToUpper(str_value) == ToUpper(STR(TRUE_STRING_VALUE)))) {
    ret = true;
  }
  return ret;
}

char CStringTools::ToChar(const std::string &str_value) {
  char ret = '\x0';
  if (str_value != "") {
    ret = str_value.at(0);
  }
  return ret;
}

void CStringTools::RemoveBlanks(std::string &value) {
  CStringTools::Replace(value, " ", "");
  CStringTools::Replace(value, "\r", "");
  CStringTools::Replace(value, "\n", "");
  CStringTools::Replace(value, "\t", "");
}

std::string CStringTools::GetString(std::string text,
                                    tPosition pos,
                                    char separator) {
	std::string ret = text;
	int separator_pos = text.find(separator);

	if (separator_pos != -1) {
		if (pos == tPosition::GET_LEFT) {
			ret = text.substr(0, separator_pos);
		}
		if (pos == tPosition::GET_RIGHT) {
			ret = text.substr(separator_pos+1);
		}
	}

	return ret;
}

// Example:
// json: {"command":"WELLCOME","data":{"cmd":null,"lm_key":null,"bin_key":null}}
// param: command
std::string CStringTools::GetJSONValue(std::string json, std::string param) {
  std::string ret;

  std::string find = "\"" + param + "\":";
  int pos1 = json.find(find);
  if (pos1 != -1) {
    // pos1
    //  |
    //  V
    // {"command":"WELLCOME,BYEBYE","data":{"cmd":null,"lm_key":null,"bin_key":null}}
    // {pos1->"command":"WELLCOME,BYEBYE","data":{"cmd":null,"lm_key":null,"bin_key":null}}

    pos1 += find.length();

    if (json[pos1] == '\"') {
      // Value starts with double quotes


      if (json[pos1 + 1] == '\"') {
        //Example:
        //           pos1
        //            |
        //            V
        // {"command":"","data":{"cmd":null,"lm_key":null,"bin_key":null}}

        ret = "";
      } else {
        //Example:
        //           pos1
        //            |
        //            V
        // {"command":"WELLCOME,BYEBYE","data":{"cmd":null,"lm_key":null,"bin_key":null}}
        
        for (std::size_t i = pos1 + 1; i < json.length(); i++) {
          if (i > 0) {
            if ((json[i-1] != '\\') && (json[i] == '\"')) {
              break; // <------------------------------------ this loop stops when (") is found but not when (\") is found.
            }
          }

          ret += json[i];
        }
      }
    } else {
      // Value does not start with double quotes
      
      //Example:
      //           pos1
      //            |
      //            V
      // {"comm_id":33,"data":{"cmd":null,"lm_key":null,"bin_key":null}}
      for (std::size_t i = pos1; ((i < json.length()) && (json[i] != ',') && (json[i] != '}')); i++) {
        ret += json[i];
      }
    }
    
    if (ret == "null") {
      ret = "";
    }    

    /*    
    int pos_coma = json.find(',', pos1);
    int pos_end_bracket = json.find('}', pos1);

    int pos2 = -1;

    if ((pos_coma == -1) && (pos_end_bracket != -1)) {
      pos2 = pos_end_bracket;
    } else {
      if ((pos_coma != -1) && (pos_end_bracket == -1)) {
        pos2 = pos_coma;
      } else {
        if ((pos_coma != -1) && (pos_end_bracket != -1)) {
          pos2 = (pos_coma < pos_end_bracket)?pos_coma:pos_end_bracket;
        } else {
          // both are == -1
          pos2 = json.length();
        }
      }
    }
 
    // {"command":pos1->"WELLCOME"<-pos2,"data":{"cmd":null,"lm_key":null,"bin_key":null}}
    ret = json.substr(pos1, pos2-pos1);


    if (ret != "") {
      if (ret == "null") {
        // ret = "null"
        ret = "";
        // ret = ""
      } else {
        if ((ret[0] == '"') && (ret[ret.length()-1] == '"')) {
          // ret = "WELLCOME"
          ret = ret.substr(1, ret.length()-2);
          // ret = WELLCOME
        }
      }
    }
*/
  }
  return ret;
}


std::string CStringTools::ScapeForJSONfield(std::string text) {
  CStringTools::Replace(text, "\"", "\\\"");
  CStringTools::Replace(text, "\n",   "<br />");

//  CStringTools::Replace(text, "'", "comillas");
//  CStringTools::Replace(text, "\n", "\\\\n");  // 4 slashes because JSON needs
//                                               // two real slashes and one real
//                                              // 'n' to identify EOL.
//
//  CStringTools::Replace(text, "\"",   "&quot;");
//  CStringTools::Replace(text, "'",   "&apos;");
//  CStringTools::Replace(text, "&",    "&amp;");
//  CStringTools::Replace(text, "<",    "&lt;");
//  CStringTools::Replace(text, ">",    "&gt;");


  return text;
}


//bool CStringTools::StartsWith(const std::string &text, const std::string &search) {
//  return (text.find(search)==0);
//}
//
//std::string CStringTools::RemoveStartString(const std::string &text, const std::string &start_string) {
//  std::string ret = text;
//  if (CStringTools::StartsWith(text, start_string) == true) {
//    ret = text.substr(start_string.length());
//  }
//  return ret;
//}

