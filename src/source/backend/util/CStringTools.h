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
 *  \brief     CStringTools.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 8, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef UTIL_CSTRINGTOOLS_H_
#define UTIL_CSTRINGTOOLS_H_

#include <string>
#include <vector>
#include <sstream>

enum tPosition {
  GET_LEFT,
  GET_RIGHT
};

class CStringTools {
 public:
  CStringTools();
  virtual ~CStringTools();

 public:
  static std::string PrepareField(std::string text,
                                 int column_width,
                                 bool is_number,
                                 bool selected);
  static std::string ToUpper(std::string in);
  static std::string ToLower(std::string in);
  static std::vector<std::string> SplitStrings(std::string text,
                                               char separator);
  static std::vector<long int> SplitNumbers(std::string text,
                                           char separator);
  static void Replace(std::string &var,
                      const std::string &old_text,
                      const std::string &new_text);
  // static std::string ToNDigits(int value, int digits);

  template <class T>
  static std::string ToNDigits(T value, int digits, char filling_char) {
    std::stringstream ss1;
    ss1 << value;
    int remain = digits - ss1.str().length();

    std::stringstream ss2;
    for (int i=0; i<remain; i++) {
      ss2 << filling_char;
    }

    ss2 << ss1.str();

    return ss2.str();
  }

  //1: If you know the destination type, use:
  static int ToInt(const std::string &str_value);
  static long int ToInt64(const std::string &str_value);
  static float ToFloat(const std::string &str_value);
  static double ToDouble(const std::string &str_value);
  
  //2: If you do not know the destination type, use:
  static float ToValue(std::string from_str_value, float to_value);
  static long int ToValue(std::string from_str_value, long int to_value);
  static int ToValue(std::string from_str_value, int to_value);
  static double ToValue(std::string from_str_value, double to_value);
  
  //3: T is not float, long int, int or double.
  //So it is not a number. 
  //It could be an string
  static std::string ToValue(std::string from_str_value, std::string to_value);

  //4: Or it could be a char
  static char ToValue(std::string from_str_value, char to_value);
  
  //5: But if is not a known data then keep the value and do not assign anything:
  //The function returns the "to_value" not the "from_value" in order
  //to keep the same value.
  template <class T>
  static T ToValue(std::string from_str_value, T to_value) {
    return to_value;
  }


  static bool IsNumber(const std::string &str);
  static bool IsVariable(const std::string &str);
  static std::string ToString(char ch) {
    std::string str = "";
    str+=ch;
    return str;
  }
  static bool ToBoolean(const std::string &str_value);
  static char ToChar(const std::string &str_value);

  template<typename T>
  static std::string ToString(T value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
  }

  static void RemoveBlanks(std::string &value);
  static std::string GetString(std::string text,
                        tPosition pos,
                        char separator);

  static std::string GetJSONValue(std::string json, std::string param);
  static std::string ScapeForJSONfield(std::string text);

//  static bool NullValue(const std::string & str_val) {
//    return ((str_val == "") || (str_val == "null"));
//  }
  
//  static bool StartsWith(const std::string &text, const std::string &search);
//  static std::string RemoveStartString(const std::string &text,
//                                       const std::string &start_string);
};

#endif /* UTIL_CSTRINGTOOLS_H_ */
