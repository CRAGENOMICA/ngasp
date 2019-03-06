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
 *  \brief     IFunction.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      April 06, 2016
 *  \pre
 *  \bug
 *  \warning
*/

#ifndef BACKEND_SRC_IFUNCTION_H_
#define BACKEND_SRC_IFUNCTION_H_

#include <string>

#include "language/CStringTable.h"
#include "commands/COS/COptionsContainer.h"

/**
 * @brief This is the interface for "functions". In ngaSP "functions" are
 *        those objects that have inputs and ouputs. For example, calculations
 *        and commands.
 */
class IFunction {
public:
 IFunction() {
      set_function_name(KeyString::UNDEFINED_STRING);
      set_brief_description(KeyString::UNDEFINED_STRING);
      set_description(KeyString::UNDEFINED_STRING);
      set_author(KeyString::UNDEFINED_STRING);
      set_copyright(KeyString::UNDEFINED_STRING);
      set_citations(KeyString::UNDEFINED_STRING);
      set_see_also(KeyString::UNDEFINED_STRING);
      
     set_options(new COptionsContainer());
  }
  
  IFunction(KeyString function_name,
                       KeyString brief_description,
                       KeyString description,
                       KeyString author,
                       KeyString copyright,
                       KeyString citations,
                       KeyString see_also) :IFunction() {
      set_function_name(function_name);
      set_brief_description(brief_description);
      set_description(description);
      set_author(author);
      set_copyright(copyright);
      set_citations(citations);
      set_see_also(see_also);
  }
  
  virtual ~IFunction() {
      if (options_ != NULL) {
          delete options_;
          options_ = NULL;
      }
  }

private:
  KeyString function_name_;
  KeyString brief_description_;
  KeyString description_;
  KeyString author_;
  KeyString copyright_;
  KeyString citations_;
  KeyString see_also_;

  COptionsContainer  *options_;  // function input and output parameters
  
 public:
  inline KeyString function_name() const { return function_name_; }
  inline void set_function_name(const KeyString & function_name) {
    function_name_ = function_name;
  }
  
  inline KeyString brief_description() const {
    return brief_description_;
  }
  inline void set_brief_description(const KeyString brief_description) {
    brief_description_ = brief_description;
  }

  inline KeyString description() const {
    return description_;
  }
  inline void set_description(const KeyString description) {
    description_ = description;
  }
  
  inline KeyString author() const {
    return author_;
  }
  inline void set_author(const KeyString author) {
    author_ = author;
  }
  
  inline KeyString copyright() const {
    return copyright_;
  }
  inline void set_copyright(const KeyString copyright) {
    copyright_ = copyright;
  }
  
  inline KeyString citations() const {
    return citations_;
  }
  inline void set_citations(const KeyString citations) {
    citations_ = citations;
  }
  
  inline KeyString see_also() const {
    return see_also_;
  }
  inline void set_see_also(const KeyString see_also) {
    see_also_ = see_also;
  }
  
  inline COptionsContainer *options() const { 
    return options_; 
  }
  inline void set_options(COptionsContainer *options) {
    options_ = options;
  }  
};

#endif  // BACKEND_SRC_IFUNCTION_H_

