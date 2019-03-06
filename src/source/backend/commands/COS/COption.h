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
 *  \brief     COption.h
 *  \details
 *  \author    gvera, jjene
 *  \version   1.0
 *  \date      Mar 31, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_COMMANDS_COPTION_H_
#define BACKEND_SRC_COMMANDS_COPTION_H_

#include <string>

#include "../../data_manager/IData.h"
#include "../../language/CStringTable.h"


#include <limits>
const int UNDEFINED_VALUE = std::numeric_limits<int>::max();

// #define UNDEFINED_VALUE -1  // value int imax = std::numeric_limits<int>::max();

//#define INTERFACE_DM_VAR(dir,a,b,c,d,f,g,h,i,j,l) opt = new COption(COption::dir,KeyString::a,KeyString::b,KeyString::c,KeyString::d,KeyString::d,KeyString::f,KeyString::g,KeyString::h,i,j,COption::ARGTYPES::ARGTYPE_undefined,COption::l);options()->push(opt);
//#define GET_VAR_FROM_DM(var) var = manager()->data_manager()->GetDataByName(var, ROOT_PARENT, #var);

// =============================================================================
// CALCULATION INTERFACE (H)
// =============================================================================
#define BEGIN_CALCULATION_INTERFACE private:
#define DECLARE_INPUT(type, var)  type *var;
#define DECLARE_OUTPUT(type, var) type *var;
#define END_CALCULATION_INTERFACE
// =============================================================================

// =============================================================================
// CALCULATION INTERFACE (CPP)
// =============================================================================
#define BEGIN_CALCULATION_INTERFACE_DEFINITION { COption *opt = NULL; 

#define SET_INPUT_INFO(var, group, short_name, long_name, description, example, only, def_val, min_value, max_value, opt_type) options()->AddInoutDefinition(typeid(*this).name(), #var, COption::READ);  opt = new COption(COption::READ, KeyString::group, GetTypeFromUnknownNullVariable(var), KeyString::short_name, KeyString::long_name, KeyString::description, KeyString::example, KeyString::UNDEFINED_STRING, KeyString::only, KeyString::def_val, min_value, max_value, COption::ARGTYPES::ARGTYPE_undefined, COption::OPTTYPES::opt_type); options()->push(opt);
#define SET_OUTPUT_INFO(var, group, short_name, long_name, description, example, only, def_val, min_value, max_value, opt_type) options()->AddInoutDefinition(typeid(*this).name(), #var, COption::WRITE); opt = new COption(COption::WRITE, KeyString::group, GetTypeFromUnknownNullVariable(var), KeyString::short_name, KeyString::long_name, KeyString::description, KeyString::example, KeyString::UNDEFINED_STRING, KeyString::only, KeyString::def_val, min_value, max_value, COption::ARGTYPES::ARGTYPE_undefined, COption::OPTTYPES::opt_type); options()->push(opt);

#define END_CALCULATION_INTERFACE_DEFINITION set_num_inputs(options()->size(COption::OPTDIR::READ)); set_num_outputs(options()->size(COption::OPTDIR::WRITE)); }
// =============================================================================

// =============================================================================
// COMMAND INTERFACE
// =============================================================================
#define BEGIN_COMMAND_INTERFACE_DEFINITION { COption *opt = NULL; 

#define SET_OPTION_INFO(group, data_type, short_name, long_name, description, example, only, def_val, min_value, max_value, arg_type, opt_type) opt = new COption(COption::READ, KeyString::group, KeyString::data_type, KeyString::short_name, KeyString::long_name, KeyString::description, KeyString::example, KeyString::UNDEFINED_STRING, KeyString::only, KeyString::def_val, min_value, max_value, COption::ARGTYPES::arg_type, COption::OPTTYPES::opt_type); options()->push(opt);
#define SET_VALUE_INFO(value, description, example, only, def_val) opt->AddValue(new CValue(KeyString::value, KeyString::description, KeyString::example, KeyString::only, def_val));

#define END_COMMAND_INTERFACE_DEFINITION }
// =============================================================================



/**
 * This function receives a variable like:
 * Unknown *p = NULL;
 * (It must derive at least from IObject)
 * And returns its KeyString type
 */
template<class T> 
KeyString GetTypeFromUnknownNullVariable(T *p) {
  KeyString ret = KeyString::UNDEFINED_STRING;
  T *aux = new T();
  ret = (static_cast<IObject *>(aux))->type_key();
  delete aux;
  return ret;
}

class CValue
{
 private:
  KeyString value_;
  KeyString description_;
  KeyString example_;
  KeyString only_; 
  bool def_val_; 
  
 public:
  CValue() {
    value_ = KeyString::UNDEFINED_STRING;
    description_ = KeyString::UNDEFINED_STRING;
    example_ = KeyString::UNDEFINED_STRING;
    only_ = KeyString::UNDEFINED_STRING;
    def_val_ = false;
  }
  CValue(KeyString value,
         KeyString description,
         KeyString example,
         KeyString only,
         bool def_val) {
    set_value(value);
    set_description(description);
    set_example(example);
    set_only(only);
    set_def_val(def_val);
  } 

 public:
  inline void set_value(const KeyString & value) {
    value_ = value;
  }
  inline KeyString value() const {
    return value_;
  }  
  
  inline void set_description(const KeyString & description) {
    description_ = description;
  }
  inline std::string description() const { return STR2(description_); }

  inline void set_example(const KeyString & example) {
    example_ = example;
  }
  inline KeyString example() const {
    return example_;
  }  

  inline void set_only(const KeyString & only) {
    only_ = only;
  }
  inline KeyString only() const {
    return only_;
  }  
  
  inline void set_def_val(const bool & def_val) {
    def_val_ = def_val;
  }
  inline bool def_val() const {
    return def_val_;
  }   
};

// -G 1          G is the OPTTYPE. It can be OPTTYPE_optional or OPTTYPE_optional
//               1 is the option argument. It can be required or no_argument.
class COption {
 public:
  enum ARGTYPES {
    ARGTYPE_undefined = 0,
    ARGTYPE_no_argument,             // ex.'g':   "-g"
    //ARGTYPE_arg_optional,
    ARGTYPE_arg_required             // ex.'g':   "-g value"
  };
  enum OPTTYPES {
    OPTTYPE_undefined = 0,
    OPTTYPE_mandatory,               // ex.'g':   "-g value [-a value] [-b value]"
    OPTTYPE_mandatory_in_its_group,  // ex.'g':   "-n value [-g value [-a value] [-b value]]"
    OPTTYPE_optional                 // ex.'g':   "[-g value]"
  };
  enum OPTDIR {
    READ  = 0,
    WRITE = 1,
  };
  
 public:
  COption();
// /*
// * *** OBSOLETE CONSTRUCTOR ***
// */
//  COption(KeyString short_name,
//          KeyString long_name,
//          KeyString description,
//          COption::ARGTYPES arg_type,
//          COption::OPTTYPES opt_type);
  
  COption(COption::OPTDIR direction,
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
          COption::OPTTYPES opt_type);  
  virtual ~COption();
  
 private:
  COption::OPTDIR direction_;            /// Option direction: input, output or both
  KeyString group_;        /// Group where this option belongs to
  KeyString data_type_;    /// Type of data
  KeyString short_name_;   /// One letter option, like -i
  KeyString long_name_;    /// Full length option, like --input
  KeyString description_;  /// Description for the help
  KeyString example_;      /// Example of usage
  KeyString citations_;    /// 
  KeyString only_;         /// This option can only be used in this condition
  KeyString def_val_;      /// Default value
  double min_value_;                     /// If the data type is numeric this is the minimum possible value
  double max_value_;                     /// If the data type is numeric this is the maximum possible value
  std::list<CValue *> *values_;          /// List of possible values
  
  
  
  int opt_type_;
  int arg_type_;
  bool mandatory_;                       /// Define whether this option is
                                         /// mandatory or optional for the
                                         /// command
  bool activated_;                       /// Define whether this option has
                                         /// been activated (implicitly or
                                         /// explicitly) by the user

 public:
  inline COption::OPTDIR direction(void) { return direction_; }
  inline void set_direction(const COption::OPTDIR & direction) {
    direction_ = direction;
  }
  
  inline std::list<CValue *> *values(void) { return values_; }
  inline void set_values(std::list<CValue *> *values) {
    values_ = values;
  }
  inline void AddValue(CValue *value) {
    values_->push_back(value);
  }
  
 public:
  inline void set_group(const KeyString & group) {
    group_ = group;
  }
  inline KeyString group() const {
    return group_;
  }  
  inline void set_data_type(const KeyString & data_type) {
    data_type_ = data_type;
  }
  inline KeyString data_type() const {
    return data_type_;
  }  
   
  inline void set_short_name(const KeyString & short_name) {
    short_name_ = short_name;
  }
  inline std::string short_name() const { return STR2(short_name_); }
  inline KeyString short_name_keystring() const {
    return short_name_;
  }

  inline void set_long_name(const KeyString & long_name) {
    long_name_ = long_name;
  }
  inline std::string long_name() const { return STR2(long_name_); }

  inline void set_description(const KeyString & description) {
    description_ = description;
  }
  inline std::string description() const { return STR2(description_); }

  inline void set_example(const KeyString & example) {
    example_ = example;
  }
  inline KeyString example() const {
    return example_;
  }  
  inline void set_citations(const KeyString & citations) {
    citations_ = citations;
  }
  inline KeyString citations() const {
    return citations_;
  }  
  
  inline void set_only(const KeyString & only) {
    only_ = only;
  }
  inline KeyString only() const {
    return only_;
  }  
  
  inline void set_def_val(const KeyString & def_val) {
    def_val_ = def_val;
  }
  inline KeyString def_val() const {
    return def_val_;
  }  
  
  inline void set_arg_type(const int & arg_type) { arg_type_ = arg_type; }
  inline int arg_type() const { return arg_type_; }
  
  inline void set_opt_type(const int & opt_type) { opt_type_ = opt_type; }
  inline int opt_type() const { return opt_type_; }

  inline void set_mandatory(const bool & mandatory) {
    mandatory_ = mandatory;
  }
  inline bool mandatory() const { return mandatory_; }

  inline void set_activated(const bool & activated) { activated_ = activated; }
  inline bool activated() const { return activated_; }
  
  inline void set_min_value(const double & min_value) {
    min_value_ = min_value;
  }   
  inline double min_value() const {
    return min_value_;
  }  

  inline void set_max_value(const double & max_value) {
    max_value_ = max_value;
  }   
  inline double max_value() const {
    return max_value_;
  }    
};

#endif  // BACKEND_SRC_COMMANDS_COPTION_H_
