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
 *  \brief     CDataAccess.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      June 15, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CDataAccess.h"

#include <string>
#include <sstream>
#include <vector>
#include <list>

#include "../IData.h"
//#include "../../util/CStringTools.h"
#include "../../language/CStringTable.h"
#include "../../CManager.h"
//#include "../../IObject.h"
#include "../../data_manager/CDataManager.h"
#include "../../data_manager/IDataValue.h"
#include "../../data_manager/Data/CDataChar.h"
#include "../../data_manager/Data/CDataInt.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataDouble.h"
#include "../../data_manager/Data/CDataFloat.h"

#include "CDataHelper.h"

CDataAccess::CDataAccess() {
  Clear();
}

CDataAccess::~CDataAccess() {
  Clear();
}

void CDataAccess::Clear(void) {
//  set_addressing_type(AccessType::UNDEFINED_ACCESS);
//  set_variable_type(VariableType::UNDEFINED_VARIABLE);
//  set_name("");
//  set_variable("");
//  set_x(-1);
//  set_y(-1);
//  set_length_x(-1);
//  set_length_y(-1);
//
//  set_value("");
//
//  pint_value_ = NULL;
//  pint64_value_ = NULL;
//  pdouble_value_ = NULL;
//  pfloat_value_ = NULL;
//  pchar_value_ = NULL;
//  pbool_value_ = NULL;
//  pstring_value_ = NULL;
//  pobject_value_ = NULL;


  set_data_object(NULL);
  set_calc_object(NULL);
  set_data_variable("");
  positions_.clear();
  set_value("");
  set_value_is_set(false);
  set_initial_reference("");
}





/**
 * Get data name and data variable from reference.
 *
 * -- ---------- -------- ------- -------- ------- -----------------------------
 * #  Reference  DataName DataVar Position Value   Comments
 * -- ---------- -------- ------- -------- ------- -----------------------------
 * 1  \"xxxxx\"  ""       ""      ""       "xxxxx" value_is_set := true
 * 2  999        ""       ""      ""       999     value_is_set := true
 * 3  a          "a"      ""      ""       ""      -
 * 4  a.b[x,y]   "a"      "b"     "3,4"    ""      Position converted into numbers
 * 5  a.b        "a"      "b"     ""       ""      -
 * 6  a[x,y]     "a"      "data"  "3,4"    ""      Position converted into numbers
 */
void CDataAccess::Set(CManager *manager, std::string reference) {
  Clear();

  set_initial_reference(reference);

  std::string::size_type loc_quotes        = std::string::npos;
  std::string::size_type loc_dot           = std::string::npos;
  std::string::size_type loc_bracket_start = std::string::npos;
  std::string::size_type loc_bracket_end   = std::string::npos;

  loc_quotes        = reference.find(STR(DOUBLE_QUOTE), 0);
  loc_dot           = reference.find(STR(VARIABLE_SEPARATOR), 0);
  loc_bracket_start = reference.find(STR(VARIABLE_POS_START), 0);
  loc_bracket_end   = reference.find_last_of(STR(VARIABLE_POS_END));

  std::string data_name;

  if (loc_quotes != std::string::npos) {
    /**
     * =========================================================================
     * It is 1
     * =========================================================================
     */
    CStringTools::Replace(reference, STR(DOUBLE_QUOTE), "");
    value_ = reference;
    reference = "";
    set_value_is_set(true);
  } else {
    if (CStringTools::IsNumber(reference)) {
      /**
       * =======================================================================
       * It is 2
       * =======================================================================
       */
      value_ = reference;
      reference = "";
      set_value_is_set(true);
    } else {
      if (loc_dot == std::string::npos) {
        if ((loc_bracket_start != std::string::npos) &&
            (loc_bracket_end != std::string::npos)) {
          /**
           * ===================================================================
           * It is 6
           * ===================================================================
           */
          std::string pos_references = reference.substr(loc_bracket_start+1,
                                           loc_bracket_end-loc_bracket_start-1);
          data_name = reference.substr(0, loc_bracket_start);
          reference = "";
          positions_ = ReferencesToPositions(manager, pos_references);
          data_variable_ = STR(VARIABLE_DATA);
          set_value_is_set(false);
        } else {
          /**
           * =====================================================================
           * It is 3
           * =====================================================================
           */
          data_name = reference;
          reference = "";
          set_value_is_set(false);
        }
      } else {
        if ((loc_bracket_start != std::string::npos) &&
            (loc_bracket_end != std::string::npos)) {
          /**
           * ===================================================================
           * It is 4
           * ===================================================================
           */
          std::string pos_references = reference.substr(loc_bracket_start+1,
                                           loc_bracket_end-loc_bracket_start-1);
          reference = reference.substr(0, loc_bracket_start);

          /**
           * Split positions:
           *
           * -- ----------
           * #  Position                 Pos[0]      Pos[1] ...
           * -- ------------------------ ----------- -----------
           * 1  "2"                      "2"         ""
           * 2  "2,3"                    "2"         "3"
           * 3  "a.data[3],b.data[2]"    "a.data[3]" "b.data[2]"
           */
          positions_ = ReferencesToPositions(manager, pos_references);
          data_name = reference.substr(0, loc_dot);
          data_variable_ = reference.substr(loc_dot+1);
          reference = "";
          set_value_is_set(false);
        } else {
          if (loc_dot != std::string::npos) {
            /**
             * =================================================================
             * It is 5
             * =================================================================
             */
            data_name = reference.substr(0, loc_dot);
            data_variable_ = reference.substr(loc_dot+1);
            reference = "";
            set_value_is_set(false);
          }
        }
      }
    }
  }

  /*
   * User can only create ROOT_PARENT variables / calculations, so this command
   * only sets value to ROOT_PARENT variables / calculations.
   */  
  if (data_name != "") {
    data_object_ = manager->data_manager()->GetDataByName(ROOT_PARENT, data_name);

    if (data_object_ == NULL) {
      calc_object_ = manager->all_calculations()->GetCalculationByName(ROOT_PARENT, data_name);

      if (calc_object_ == NULL) {
        ERROR_MSG2 << "Not found reference to: " << data_name END_MSG;
      }
    }
  }
}



/**
 * There are a lot of combinations. These are some of them:
 * ----------------------- ------------------- ---------------------------------
 * Example                 pos_references      Return
 * ----------------------- ------------------- ---------------------------------
 * matrix[1,2]             "1,2"               [1][2]
 * matrix[x,y]             "x,y"               [3][4] (x=3 & y=4)
 * matrix[vec[3],mat[3,4]] "vec[3],mat[3,4]"   [5][6] (vec[3]=5 & mat[3,4]=6)
 * cube[5,mat[3,4],vec[2]] "5,mat[3,4],vec[2]" [5][1][2] (mat[3,4]=1 & vec[2]=2)
 */
std::vector<long int>
CDataAccess::ReferencesToPositions(CManager *manager,
                                   std::string pos_references) {
  std::list<std::string> references = SeparateReferences(pos_references);

  std::vector<long int> ret(references.size());

  std::list<std::string>::iterator i = references.begin();
  int pos = 0;

  for (; i != references.end(); ++i) {
    ret.at(pos) = VariableToNumber(manager, *i);
    pos++;
  }

  return ret;
}

/**
 * Separate references by searching COMA.
 * But not all COMA are valid. In this example:
 * "5,mat[3,4],vec[2]" only the coma after 5 and the coma before vec are
 * valids because they are not inside any open brackets.
 *
 * If input is only one reference (for example x) the output is a list with only
 * one reference.
 */
std::list<std::string>
CDataAccess::SeparateReferences(std::string pos_references) {
  std::list<std::string> separated_references;

  if (pos_references != "") {
    int pos_start = 0;
    int pos_end = 0;
    int num_open_brackets = 0;
    unsigned int i = 0;
    for (i = 0; i < pos_references.length(); i++) {
      if (pos_references.at(i) == STR(VARIABLE_POS_START)[0]) {  // '['
        num_open_brackets++;
      } else {
        if (pos_references.at(i) == STR(VARIABLE_POS_END)[0]) {  // ']'
          num_open_brackets--;
        } else {
          if (pos_references.at(i) == STR(COMA)[0]) {  // ','
            if (num_open_brackets == 0) {
              pos_end = i;
              separated_references.push_back(pos_references.substr(pos_start, pos_end));
              pos_start = i+1;
            }
          }
        }
      }
    }

    pos_end = i;
    separated_references.push_back(pos_references.substr(pos_start, pos_end));
  }

  return separated_references;
}

  /**
   * The reference could be:
   * -- ------------- --------------------------- ------------------------------
   * #  Type          Comments                    Trick to recognize it
   * -- ------------- --------------------------- ------------------------------
   * 1  "5"           A number.
   *
   * 2  "a"           A variable (direct).        There are not any '[' or ']' or ','
   *
   * 3  "vector[5]"   A vector position (direct). From '[' all chars are numbers, comas or the final ']'
   *    "matrix[5,5]" A matrix position (direct).
   *    "cube[3,2,4]" A cube position (direct).
   *
   * 4  "a[b]"        Variable inside variable    If not cases 1, 2 or 3 then it is case 4
   *    "a[b[3,3],5]" Variable inside variable
   */

int CDataAccess::VariableToNumber(CManager *manager,
                                  std::string pos_references) {
  int ret = -1;
  bool convert = false;

  if (CStringTools::IsNumber(pos_references)) {
    /**
     * =========================================================================
     * It is 1
     * =========================================================================
     */
    ret = CStringTools::ToInt(pos_references);
  } else {
    if ((pos_references.find(STR(COMA), 0) == std::string::npos) &&
        (pos_references.find(STR(VARIABLE_POS_START), 0) == std::string::npos) &&
        (pos_references.find(STR(VARIABLE_POS_END), 0) == std::string::npos)) {
      /**
       * =======================================================================
       * It is 2
       * =======================================================================
       */
      convert = true;
    } else {
      std::string::size_type loc_bracket_start = std::string::npos;
      loc_bracket_start = pos_references.find(STR(VARIABLE_POS_START), 0);
      std::string var_name = pos_references.substr(0, loc_bracket_start);
      std::string inside_brackets = pos_references.substr(loc_bracket_start+1);

      // Remove last bracket:
      inside_brackets = inside_brackets.substr(0, inside_brackets.length()-1);

      unsigned int i = 0;
      for (i=0; ( (i < inside_brackets.length()) &&
                 ((inside_brackets.at(i) == '0') ||
                  (inside_brackets.at(i) == '1') ||
                  (inside_brackets.at(i) == '2') ||
                  (inside_brackets.at(i) == '3') ||
                  (inside_brackets.at(i) == '4') ||
                  (inside_brackets.at(i) == '5') ||
                  (inside_brackets.at(i) == '6') ||
                  (inside_brackets.at(i) == '7') ||
                  (inside_brackets.at(i) == '8') ||
                  (inside_brackets.at(i) == '9') ||
                  (inside_brackets.at(i) == STR(VARIABLE_POS_START)[0]) ||
                  (inside_brackets.at(i) == STR(VARIABLE_POS_END)[0]) ||
                  (inside_brackets.at(i) == STR(COMA)[0]))); i++) {
      }

      if (i == inside_brackets.length()) {
        /**
         * =====================================================================
         * It is 3
         * =====================================================================
         */
        convert = true;
      } else {
        /**
         * =====================================================================
         * It is 4
         * =====================================================================
         */
        // We have the case 4 but we are going to turn it into the case 3:
        // references like [x,y,z] will be changed to numbers [1,2,3]:

        std::cout << inside_brackets << std::endl;
        std::vector<long int> posss = ReferencesToPositions(manager,
                                                           inside_brackets);

        std::list<std::string> references = SeparateReferences(pos_references);

        pos_references = var_name + STR(VARIABLE_POS_START);

        for (unsigned int t = 0; t < posss.size(); t++) {
          if (t != 0) {
            pos_references += STR(COMA);
          }
          pos_references += CStringTools::ToString(posss.at(t));
        }

        pos_references += STR(VARIABLE_POS_END);

        convert = true;
      }
    }

    if (convert) {
      /**
       * If origin is a Data of 64 bits then destination must be
       * a Data of 64 bits:
       */
      CDataAccess orig;
      orig.Set(manager, pos_references);

//      CDataAccess dest;
//      KeyString basic_type =
//            CDataFactory::GetPrimitiveTypeFrom(orig.data_object()->type_key());
//
//      CDataInt int_var;
//      CDataInt64 int64_var;
//      CDataFloat float_var;
//      CDataDouble double_var;
//
//      switch(basic_type) {
//        case KeyString::DATA_INT:
//          int_var.Set(&orig, &dest, SetAction::REPLACE_VALUE);
//          ret = int_var.value();
//          break;
//        case KeyString::DATA_INT64:
//          int64_var.Set(&orig, &dest, SetAction::REPLACE_VALUE);
//          ret = static_cast<int>(int64_var.value());
//          break;
//        case KeyString::DATA_FLOAT:
//          float_var.Set(&orig, &dest, SetAction::REPLACE_VALUE);
//          ret = static_cast<int>(float_var.value());
//          break;
//        case KeyString::DATA_DOUBLE:
//          double_var.Set(&orig, &dest, SetAction::REPLACE_VALUE);
//          ret = static_cast<int>(double_var.value());
//          break;
//        default:
//          break;
//      }

      std::string var;
      int *pvalue_int = NULL;
      int *pvalue_int64 = NULL;
      int *pvalue_float = NULL;
      int *pvalue_double = NULL;

      switch(CDataFactory::GetType(&orig)) {
        case KeyString::DATA_INT:
          pvalue_int = CDataHelper::GetReferenceValue(&orig, var, int());
          if (pvalue_int != NULL) { ret = static_cast<long int>(*pvalue_int); }
          else { ret = CStringTools::ToInt64(var); }
          break;
        case KeyString::DATA_INT64:
          pvalue_int64 = CDataHelper::GetReferenceValue(&orig, var, int());
          if (pvalue_int64 != NULL) { ret = (*pvalue_int64); }
          else { ret = CStringTools::ToInt64(var); }
          break;
        case KeyString::DATA_FLOAT:
          pvalue_float = CDataHelper::GetReferenceValue(&orig, var, int());
          if (pvalue_float != NULL) { ret = static_cast<long int>(*pvalue_float); }
          else { ret = CStringTools::ToInt64(var); }
          break;
        case KeyString::DATA_DOUBLE:
          pvalue_double = CDataHelper::GetReferenceValue(&orig, var, int());
          if (pvalue_double != NULL) { ret = static_cast<long int>(*pvalue_double); }
          else { ret = CStringTools::ToInt64(var); }
          break;
        default:
          break;
      }



    }
  }

  return ret;
}

//
//    if ((pos_references.find(STR(COMA), 0) == std::string::npos) &&
//        (pos_references.find(STR(VARIABLE_POS_START), 0) == std::string::npos) &&
//        (pos_references.find(STR(VARIABLE_POS_END), 0) == std::string::npos)) {
//      /**
//       * =======================================================================
//       * It is 2
//       * =======================================================================
//       */
//      CDataAccess orig;
//      CDataAccess dest;
//      orig.Set(manager, pos_references);
//
//      CDataInt64 a;
//      a.Set(&orig, &dest);
//
//      ret = a.value();
//    } else {
//      std::string::size_type loc_bracket_start = std::string::npos;
//      loc_bracket_start = pos_references.find(STR(VARIABLE_POS_START), 0);
//      std::string aux = pos_references.substr(loc_bracket_start+1);
//
//      int i = 0;
//      for (i=0; (((aux.at(i) >= '0') && (aux.at(i) >= '9')) ||
//            (aux.at(i) == '[') ||
//            (aux.at(i) == ']') ||
//            (aux.at(i) == ',')); i++);
//
//      if (i == aux.length()) {
//        /**
//         * =====================================================================
//         * It is 3
//         * =====================================================================
//         */
//        CDataAccess orig;
//        CDataAccess dest;
//        orig.Set(manager, pos_references);
//
//        CDataInt64 a;
//        a.Set(&orig, &dest);
//
//        ret = a.value();
//      } else {
//        /**
//         * =====================================================================
//         * It is 4
//         * =====================================================================
//         */
//        CDataAccess orig;
//        CDataAccess dest;
//        orig.Set(manager, pos_references);
//
//        CDataInt64 a;
//        a.Set(&orig, &dest);
//
//        ret = a.value();
//      }
//    }
//  }
//
//  return ret;
//}



///**
// *  @param reference
// *  -- ----------------- ------------ ---------- ----- --------- --- --- ---- ------ -------- ---------
// *  #  Add. Type         Reference    Var. Type  Name  Variable  x   y   Val  pValue length_x  length_y
// *  -- ----------------- ------------ ---------- ----- --------- --- --- ---- ------ -------- ---------
// *  1  WHOLE_OBJECT      "a"          DATA       "a"   ""        -1  -1  ""   *IObject -1        -1
// *  2  NOT_POSSIBLE      ""           UNDEFINED  ""    ""        -1  -1  -    NULL     -1        -1
// *  3  VARIABLE_POSITION "a.b[x]"     VECTOR     "a"   "b"       'x  -1  -    *pVal    -1        -1
// *  4  VARIABLE_POSITION ".b[x]"      VECTOR     with  "b"       'x  -1  -    *pVal    -1        -1
// *  5  VARIABLE_POSITION "a.b[3]"     VECTOR     "a"   "b"       3   -1  ""   *pVal    length    -1    # detect out of range
// *  6  VARIABLE_POSITION ".b[3]"      VECTOR     with  "b"       3   -1  ""   *pVal    length    -1    # detect out of range
// *  7  OBJECT_VARIABLE   "a.b"        VEC/MAT    "a"   "b"       -1  -1  ""   *pVal    length    -1
// *  8  OBJECT_VARIABLE   ".b"         VEC/MAT    with  "b"       -1  -1  ""   *pVal    length    -1
// *  9  DIRECT_VALUE      "5"          VALUE      ""    ""        -1  -1  ref. NULL     -1        -1
// *  10 DIRECT_VALUE      "\"text\""   VALUE      ""    ""        -1  -1  ref. NULL     -1        -1
// *  11 NOT_POSSIBLE      "$%&dsf"     UNDEFINED  ""    ""        -1  -1  ""   NULL     -1        -1
// *  12 NOT_POSSIBLE      "a.b[3"      UNDEFINED  ""    ""        -1  -1  ""   NULL     -1        -1
// *  13 VARIABLE_POSITION "a.b[x][y]"  MATRIX     "a"   "b"       'x  'y  -    *pVal    -1        regs
// *  14 VARIABLE_POSITION ".b[x][y]"   MATRIX     with  "b"       'x  'y  -    *pVal    -1        regs
// *  15 VARIABLE_POSITION "a.b[3][5]"  MATRIX     "a"   "b"       3   5   ""   *pVal    1         regs
// *  16 VARIABLE_POSITION ".b[3][5]"   MATRIX     with  "b"       3   5  ""   *pVal     1         regs
// *  17 INOUTS            "a.inputs"   INOUTS     "a"   "inputs"  -1  -1  ""   NULL    -1    -1
// *  18 INOUTS            ".inputs"    INOUTS     with  "inputs"  -1  -1  ""  NULL     -1    -1
// *
// * 'x and 'y means that variable has been replaced by its value.
// */
//void CDataAccess::Set(CManager *manager, std::string reference) {
//
//  std::string::size_type loc = std::string::npos, loc2 = std::string::npos;
//  std::string str_pos;
//
//  Clear();
//
//  if (reference == "") {
//    /**
//     * =========================================================================
//     * It is 2
//     * =========================================================================
//     */
//    set_addressing_type(AccessType::NOT_POSSIBLE);
//    set_variable_type(CDataAccess::VariableType::UNDEFINED_VARIABLE);
//    // =========================================================================
//  } else {
//    if (CStringTools::IsNumber(reference)) {
//      /**
//       * =======================================================================
//       * It is 9
//       * =======================================================================
//       */
//      set_addressing_type(AccessType::DIRECT_VALUE);
//      set_variable_type(CDataAccess::VariableType::VALUE);
//      set_value(reference);
//      // =======================================================================
//    } else {
//      if ((reference.at(0) == STR(DOUBLE_QUOTE)[0]) &&
//          (reference.at(reference.length()-1) == STR(DOUBLE_QUOTE)[0])) {
//        /**
//         * =====================================================================
//         * It is 10
//         * =====================================================================
//         */
//        set_addressing_type(AccessType::DIRECT_VALUE);
//        set_variable_type(CDataAccess::VariableType::VALUE);
//        set_value(reference.substr(1, reference.length()));
//        // =====================================================================
//      } else {
//        if (CStringTools::IsVariable(reference)) {
//          loc = reference.find(STR(VARIABLE_SEPARATOR), 0);
//          if (loc == std::string::npos) {
//            /**
//             * =================================================================
//             * It is 1
//             * =================================================================
//             */
//            set_addressing_type(AccessType::WHOLE_OBJECT);
//            set_variable_type(CDataAccess::VariableType::DATA);
//            set_name(reference);
//            PointerTo(manager->data_manager()->GetDataByName(name()));
//            set_data_object(manager->data_manager()->GetDataByName(name()));
//            // =================================================================
//          } else {
//            set_name(reference.substr(0, loc));
//            if (name() == "") {
//              // It is one of: 4, 6, 8.
//              set_name(manager->with()->name());
//            }
//
//            set_variable(reference.substr(loc + 1));
//
//            loc = variable().find(STR(VARIABLE_POS_START), 0);
//            loc2 = variable().find(STR(VARIABLE_POS_END), loc);
//
//            // [ ]
//            if ((loc != std::string::npos) &&  (loc2 != std::string::npos)) {
//              // It is one of: 5, 6, 3, 4, 13, 14, 15, 16.
//              set_addressing_type(AccessType::VARIABLE_POSITION);
//
//              str_pos = variable().substr(loc+1, loc2-loc-1);
//              set_variable(variable().substr(0, loc));
//
//              loc = str_pos.find(STR(COMA)[0], 0);
//
//              if (loc == std::string::npos) {
//                // [1] or [x]
//                // It is one of: 5, 6, 3, 4.
//                set_variable_type(CDataAccess::VariableType::VECTOR);
//
//                if (CStringTools::IsNumber(str_pos)) {
//                  /**
//                   * ===========================================================
//                   * Both 5 & 6 can be.
//                   * ===========================================================
//                   */
//                  set_x(CStringTools::ToInt64(str_pos));
//                  set_data_object(manager->data_manager()->GetDataByName(name()));
//                  // ===========================================================
//                } else {
//                  // Both 3 & 4 can be.
//                  // Conversion from [x] to [cte int64]:
//                  CDataAccess pos_as_variable;
//                  pos_as_variable.Set(manager, str_pos);
//                  if (pos_as_variable.IsAccessible()) {
//                    if (pos_as_variable.pint64_value_ != NULL) {
//                      set_x(*(pos_as_variable.pint64_value_));
//                    }
//                    if (pos_as_variable.pint_value_ != NULL) {
//                      set_x(static_cast<long int>(*(pos_as_variable.pint_value_)));
//                      WARNING_MSG2 << STR(INT_TO_INT64) END_MSG;
//                    }
//                  }
//                }
//              } else {
//                // [1,1] or [1,x] or [x,x] or [x,1]
//                // It is one of: 13, 14, 15, 16.
//                set_variable_type(CDataAccess::VariableType::MATRIX);
//                std::string col, row;
//                row = str_pos.substr(0, loc);
//                col = str_pos.substr(loc + 1);
//
//                if ((CStringTools::IsNumber(row)) && (CStringTools::IsNumber(col))) {
//                  // Both 15 & 16 can be.
//                  set_x(CStringTools::ToInt64(row));
//                  set_y(CStringTools::ToInt64(col));
//                } else {
//                  // Both 13 & 14 can be.
//                  // Conversion from [x,y] to [cte int64,cte int64]:
//
//                  // Replace 'x' [x,y] by its value as long int format:
//                  if (CStringTools::IsNumber(row) == false) {
//                    CDataAccess pos_as_variable;
//                    pos_as_variable.Set(manager, row);
//                    if (pos_as_variable.IsAccessible()) {
//                      if (pos_as_variable.pint64_value_ != NULL) {
//                        set_x(*(pos_as_variable.pint64_value_));
//                      }
//                      else {
//                        if (pos_as_variable.pint_value_ != NULL) {
//                          set_x(static_cast<long int>(*(pos_as_variable.pint_value_)));
//                          WARNING_MSG2 << STR(INT_TO_INT64) END_MSG;
//                        }
//                      }
//                    }
//                  }
//
//                  // Replace 'y' [x,y] by its value as long int format:
//                  if (CStringTools::IsNumber(col) == false) {
//                    CDataAccess pos_as_variable;
//                    pos_as_variable.Set(manager, col);
//                    if (pos_as_variable.IsAccessible()) {
//                      if (pos_as_variable.pint64_value_ != NULL) {
//                        set_y(*(pos_as_variable.pint64_value_));
//                      }
//                      else {
//                        if (pos_as_variable.pint_value_ != NULL) {
//                          set_y(static_cast<long int>(*(pos_as_variable.pint_value_)));
//                          WARNING_MSG2 << STR(INT_TO_INT64) END_MSG;
//                        }
//                      }
//                    }
//                  }
//                }
//              }
//
//              IObject *object = manager->with(name());
//              if(object != NULL) {
//                // sets value pointers, length_x/y, variable types, ...:
//                object->Get(this);
//              }
//            } else {
//              if ((loc == std::string::npos) && (loc2 == std::string::npos)) {
//                if ((variable() == STR(INPUTS_PARAM)) ||
//                    (variable() == STR(OUTPUTS_PARAM))) {
//                  // Both 17 and 17 can be.
//                  set_addressing_type(AccessType::INOUTS_ACCESS);
//                  set_variable_type(CDataAccess::VariableType::INOUTS_VARIABLE);
//                } else {
//                  // Both 7 and 8 can be.
//                  set_addressing_type(AccessType::OBJECT_VARIABLE);
//
//                  IObject *object = manager->with(name());
//                  if(object != NULL) {
//                    // sets value pointers, length_x/y, variable types, ...:
//                    object->Get(this);
//                  }
//                }
//              } else {
//                // It is 12.
//                set_addressing_type(AccessType::NOT_POSSIBLE);
//                set_variable_type(CDataAccess::VariableType::UNDEFINED_VARIABLE);
//              }
//            }
//          }
//        } else {
//          // 11
//          set_addressing_type(AccessType::NOT_POSSIBLE);
//          set_variable_type(CDataAccess::VariableType::UNDEFINED_VARIABLE);
//        }
//      }
//    }
//  }
//}

//std::string CDataAccess::GetAllName(void) {
//  std::string all_name = "";
//  std::stringstream ss;
//
//  switch(variable_type()) {
//    case DATA:
//      all_name = name();
//      break;
//    case BASIC:
//      all_name = name() + STR(VARIABLE_SEPARATOR) + variable();
//      break;
//    case VECTOR:
//      ss << name() << STR(VARIABLE_SEPARATOR) << variable()
//                   << STR(VARIABLE_POS_START) << x() << STR(VARIABLE_POS_END);
//      all_name = ss.str();
//      break;
//    case MATRIX:
//      ss << name() << STR(VARIABLE_SEPARATOR) << variable()
//                   << STR(VARIABLE_POS_START) << x() << STR(COMA)
//                   << y() << STR(VARIABLE_POS_END);
//      all_name = ss.str();
//      break;
//    default:
//      all_name = name() + STR(VARIABLE_SEPARATOR) + variable();
//      break;
//  }
//
//  return all_name;
//}
//
//// *************************************************************************
//// *value could be NULL for vectors and matrix. They can be created later.
//// *************************************************************************
//
//int *CDataAccess::SetValueTo(int *value) {
//  if (pint_value_ != NULL) {
//    if ((variable_type() == VariableType::BASIC) ||
//        ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::VARIABLE_POSITION)) ||
//        ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::VARIABLE_POSITION))) {
//      *value = *pint_value_;
//    }
//
//    if ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pint_value_, length_x());
//    }
//
//    if ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pint_value_, length_x() * length_y());
//    }
//  }
//
//  return value;
//}
//
//long int *CDataAccess::SetValueTo(long int *value) {
//  if (pint64_value_ != NULL) {
//    if ((variable_type() == VariableType::BASIC) ||
//        ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::VARIABLE_POSITION)) ||
//        ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::VARIABLE_POSITION))) {
//      *value = *pint64_value_;
//    }
//
//    if ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pint64_value_, length_x());
//    }
//
//    if ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pint64_value_, length_x() * length_y());
//    }
//  }
//
//  return value;
//}
//
//double *CDataAccess::SetValueTo(double *value) {
//  if (pdouble_value_ != NULL) {
//    if ((variable_type() == VariableType::BASIC) ||
//        ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::VARIABLE_POSITION)) ||
//        ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::VARIABLE_POSITION))) {
//      *value = *pdouble_value_;
//    }
//
//    if ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pdouble_value_, length_x());
//    }
//
//    if ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pdouble_value_, length_x() * length_y());
//    }
//  }
//
//  return value;
//}
//
//float *CDataAccess::SetValueTo(float *value) {
//  if (pfloat_value_ != NULL) {
//    if ((variable_type() == VariableType::BASIC) ||
//        ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::VARIABLE_POSITION)) ||
//        ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::VARIABLE_POSITION))) {
//      *value = *pfloat_value_;
//    }
//
//    if ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pfloat_value_, length_x());
//    }
//
//    if ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pfloat_value_, length_x() * length_y());
//    }
//  }
//
//  return value;
//}
//
//
//char *CDataAccess::SetValueTo(char *value) {
//  if (pchar_value_ != NULL) {
//    if ((variable_type() == VariableType::BASIC) ||
//        ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::VARIABLE_POSITION)) ||
//        ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::VARIABLE_POSITION))) {
//      *value = *pchar_value_;
//    }
//
//    if ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pchar_value_, length_x());
//    }
//
//    if ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pchar_value_, length_x() * length_y());
//    }
//  }
//
//  return value;
//}
//
//bool *CDataAccess::SetValueTo(bool *value) {
//  if (pbool_value_ != NULL) {
//    if ((variable_type() == VariableType::BASIC) ||
//        ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::VARIABLE_POSITION)) ||
//        ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::VARIABLE_POSITION))) {
//      *value = *pbool_value_;
//    }
//
//    if ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pbool_value_, length_x());
//    }
//
//    if ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pbool_value_, length_x() * length_y());
//    }
//  }
//
//  return value;
//}
//
//std::string *CDataAccess::SetValueTo(std::string *value) {
//  if (pstring_value_ != NULL) {
//    if ((variable_type() == VariableType::BASIC) ||
//        ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::VARIABLE_POSITION)) ||
//        ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::VARIABLE_POSITION))) {
//      *value = *pstring_value_;
//    }
//
//    if ((variable_type() == VariableType::VECTOR) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pstring_value_, length_x());
//    }
//
//    if ((variable_type() == VariableType::MATRIX) && (addressing_type() == AccessType::OBJECT_VARIABLE)) {
//      value = CopyArray(value, pstring_value_, length_x() * length_y());
//    }
//  }
//
//  return value;
//}
//
//// Not Developed Yet
//IObject *CDataAccess::SetValueTo(IObject *value) {
//  return value;
//}
//
//
///*
// * Comparison Types
// *
// * =============================================================================
// * #   This               Compare With        Example
// * =============================================================================
// *
// * B1  BASIC              VALUE               x.value == 1                        variant <=> VALUE
// * B2  BASIC              BASIC               x.value == y.value                  variant <=> variant
// * B3  BASIC              VECTOR POSITION     x.value == vec[x]                   variant <=> variant
// * B4  BASIC              MATRIX POSITION     x.value == mat[x][y]                variant <=> variant
// *
// * V1  VECTOR VARIABLE    VALUE               vec.data == "1 2 3 4"               variant <=> VALUE
// * V2  VECTOR POSITION    VALUE               vec.data[x] == 1                    variant <=> VALUE
// * V3  VECTOR POSITION    BASIC               vec.data[x] == x.value              variant <=> variant
// * V4  VECTOR POSITION    VECTOR POSITION     vec1.data[x] == vec2.data[x]        variant <=> variant
// * V5  VECTOR POSITION    MATRIX POSITION     vec1.data[x] == mat.data[x][y]      variant <=> variant
// *
// * M1  MATRIX VARIABLE    VALUE               mat.data == "1 2 3 4;5 6 7 8"       variant <=> VALUE ******* NOT WORKING YET. CompareVector must be developed for Matrix
// * M2  MATRIX POSITION    VALUE               mat.data[x][y] == 1                 variant <=> VALUE
// * M3  MATRIX POSITION    BASIC               mat.data[x][y] == x.value           variant <=> variant
// * M4  MATRIX POSITION    VECTOR POSITION     mat.data[x][y] == vec.data[x]       variant <=> variant
// * M5  MATRIX POSITION    MATRIX POSITION     mat1.data[x][y] == mat2.data[x][y]  variant <=> variant
//  */
//
//bool CDataAccess::Compare(CDataAccess *data_access_compare,
//                          CDataAccess::ComparisonType comparison_type) {
//  bool comparison_result = true;
//  bool compare_done = false;
//
//  int         int_value     = 0;
//  long int     int64_value   = 0;
//  double      double_value  = 0;
//  float       float_value   = 0.0f;
//  char        char_value    = '\x0';
//  bool        bool_value    = false;
//  std::string string_value  = "";
//
//  if (data_access_compare->IsVariantEmpty()) {  // B1, V1, V2, M1, M2
//
//    if ((this->variable_type() == CDataAccess::VariableType::VECTOR) &&
//        (this->addressing_type() == CDataAccess::AccessType::OBJECT_VARIABLE)) {
//      // V1
//
//      int value_string_items = 0;
//
//      // VECTOR COMPARISON WITH STRING. data_ = { 1, 2, 3 } <-> "1 2 3"
//      bool compare = CompareVector(data_access_compare->value(), comparison_type, &value_string_items);
//
//      switch(comparison_type) {
//        case CDataAccess::ComparisonType::EQUAL:
//          comparison_result = ((compare) && (value_string_items == length_x()));
//          break;
//        case CDataAccess::ComparisonType::NOT_EQUAL:
//          comparison_result =  !((compare) && (value_string_items == length_x()));
//          break;
//        case CDataAccess::ComparisonType::LESS_THAN:
//          comparison_result = (length_x()<value_string_items);
//          break;
//        case CDataAccess::ComparisonType::GREATER_THAN:
//          comparison_result = (length_x()>value_string_items);
//          break;
//        default:
//          break;
//      }
//
//      compare_done = true;
//    }
//    else {
//      if ((this->variable_type() == CDataAccess::VariableType::MATRIX) &&
//          (this->addressing_type() == CDataAccess::AccessType::OBJECT_VARIABLE)) {
//        // M1
//        // MATRIX COMPARISON WITH STRING. data_ = { ... } <-> "1 2 3;4 5 6"
//
//        std::string matrix_string = data_access_compare->value();
//        std::string matrix_row_string;
//        int matrix_items = 0;
//        int pos = 0;
//
//        bool compare = true;
//
//        while ((matrix_string != "")&&(compare)) {
//          pos = matrix_string.find(STR(SEMI_COLON));
//
//          if (pos!=-1) {
//            matrix_row_string = matrix_string.substr(0, pos);
//            matrix_string = matrix_string.substr(pos + 1);
//          } else {
//            matrix_row_string = matrix_string;
//            matrix_string = "";
//          }
//
//          compare &= CompareVector(matrix_row_string, comparison_type, &matrix_items);
//        }
//
//        switch(comparison_type) {
//          case CDataAccess::ComparisonType::EQUAL:
//            comparison_result = ((compare) && (matrix_items == length_x()*length_y()));
//            break;
//          case CDataAccess::ComparisonType::NOT_EQUAL:
//            comparison_result =  !((compare) && (matrix_items == length_x()*length_y()));
//            break;
//          case CDataAccess::ComparisonType::LESS_THAN:
//            comparison_result = (length_x()*length_y()<matrix_items);
//            break;
//          case CDataAccess::ComparisonType::GREATER_THAN:
//            comparison_result = (length_x()*length_y()>matrix_items);
//            break;
//          default:
//            break;
//        }
//
//        compare_done = true;
//      }
//      else {  // B1, V2, M2
//        std::istringstream ss1(data_access_compare->value());
//
//        switch(GetVariantType()) {
//          case VariantType::INT:
//            ss1 >> int_value;
//            break;
//          case VariantType::INT64:
//            ss1 >> int64_value;
//            break;
//          case VariantType::DOUBLE:
//            ss1 >> double_value;
//            break;
//          case VariantType::FLOAT:
//            ss1 >> float_value;
//            break;
//          case VariantType::CHAR:
//            ss1 >> char_value;
//            break;
//          case VariantType::BOOL:
//            ss1 >> bool_value;
//            break;
//          case VariantType::STRING:
//            ss1 >> string_value;
//            break;
//          default:
//            break;
//        }
//      }
//    }
//  } else {  // B2, B3, B4, V2, V3, V4, V5, M3, M4, M5
//    switch(data_access_compare->GetVariantType()) {
//      case VariantType::INT:
//        int_value = *data_access_compare->pint64_value_;
//        break;
//      case VariantType::INT64:
//        int64_value = *data_access_compare->pint64_value_;
//        break;
//      case VariantType::DOUBLE:
//        double_value = *data_access_compare->pdouble_value_;
//        break;
//      case VariantType::FLOAT:
//        float_value = *data_access_compare->pfloat_value_;
//        break;
//      case VariantType::CHAR:
//        char_value = *data_access_compare->pchar_value_;
//        break;
//      case VariantType::BOOL:
//        bool_value = *data_access_compare->pbool_value_;
//        break;
//      case VariantType::STRING:
//        string_value = *data_access_compare->pstring_value_;
//        break;
//      default:
//        break;
//    }
//  }
//
//
//  if (compare_done == false) {
//    switch(GetVariantType()) {
//      case VariantType::INT:
//        switch(comparison_type) {
//          case CDataAccess::ComparisonType::EQUAL:
//            comparison_result = (int_value == *pint_value_);
//            break;
//          case CDataAccess::ComparisonType::NOT_EQUAL:
//            comparison_result = (int_value != *pint_value_);
//            break;
//          case CDataAccess::ComparisonType::LESS_THAN:
//            comparison_result = (int_value < *pint_value_);
//            break;
//          case CDataAccess::ComparisonType::GREATER_THAN:
//            comparison_result = (int_value > *pint_value_);
//            break;
//          default:
//            break;
//        }
//        break;
//
//      case VariantType::INT64:
//        switch(comparison_type) {
//          case CDataAccess::ComparisonType::EQUAL:
//            comparison_result = (int64_value == *pint64_value_);
//            break;
//          case CDataAccess::ComparisonType::NOT_EQUAL:
//            comparison_result = (int64_value != *pint64_value_);
//            break;
//          case CDataAccess::ComparisonType::LESS_THAN:
//            comparison_result = (int64_value < *pint64_value_);
//            break;
//          case CDataAccess::ComparisonType::GREATER_THAN:
//            comparison_result = (int64_value > *pint64_value_);
//            break;
//          default:
//            break;
//        }
//
//        break;
//      case VariantType::DOUBLE:
//        switch(comparison_type) {
//          case CDataAccess::ComparisonType::EQUAL:
//            comparison_result = (double_value == *pdouble_value_);
//            break;
//          case CDataAccess::ComparisonType::NOT_EQUAL:
//            comparison_result = (double_value != *pdouble_value_);
//            break;
//          case CDataAccess::ComparisonType::LESS_THAN:
//            comparison_result = (double_value < *pdouble_value_);
//            break;
//          case CDataAccess::ComparisonType::GREATER_THAN:
//            comparison_result = (double_value > *pdouble_value_);
//            break;
//          default:
//            break;
//        }
//
//        break;
//      case VariantType::FLOAT:
//        switch(comparison_type) {
//          case CDataAccess::ComparisonType::EQUAL:
//            comparison_result = (float_value == *pfloat_value_);
//            break;
//          case CDataAccess::ComparisonType::NOT_EQUAL:
//            comparison_result = (float_value != *pfloat_value_);
//            break;
//          case CDataAccess::ComparisonType::LESS_THAN:
//            comparison_result = (float_value < *pfloat_value_);
//            break;
//          case CDataAccess::ComparisonType::GREATER_THAN:
//            comparison_result = (float_value > *pfloat_value_);
//            break;
//          default:
//            break;
//        }
//
//        break;
//      case VariantType::CHAR:
//        switch(comparison_type) {
//          case CDataAccess::ComparisonType::EQUAL:
//            comparison_result = (char_value == *pchar_value_);
//            break;
//          case CDataAccess::ComparisonType::NOT_EQUAL:
//            comparison_result = (char_value != *pchar_value_);
//            break;
//          case CDataAccess::ComparisonType::LESS_THAN:
//            comparison_result = (char_value < *pchar_value_);
//            break;
//          case CDataAccess::ComparisonType::GREATER_THAN:
//            comparison_result = (char_value > *pchar_value_);
//            break;
//          default:
//            break;
//        }
//
//        break;
//      case VariantType::BOOL:
//        switch(comparison_type) {
//          case CDataAccess::ComparisonType::EQUAL:
//            comparison_result = (bool_value == *pbool_value_);
//            break;
//          case CDataAccess::ComparisonType::NOT_EQUAL:
//            comparison_result = (bool_value != *pbool_value_);
//            break;
//          case CDataAccess::ComparisonType::LESS_THAN:
//            comparison_result = (bool_value < *pbool_value_);
//            break;
//          case CDataAccess::ComparisonType::GREATER_THAN:
//            comparison_result = (bool_value > *pbool_value_);
//            break;
//          default:
//            break;
//        }
//
//        break;
//      case VariantType::STRING:
//        switch(comparison_type) {
//          case CDataAccess::ComparisonType::EQUAL:
//            comparison_result = (string_value == *pstring_value_);
//            break;
//          case CDataAccess::ComparisonType::NOT_EQUAL:
//            comparison_result = (string_value != *pstring_value_);
//            break;
//          case CDataAccess::ComparisonType::LESS_THAN:
//            comparison_result = (string_value < *pstring_value_);
//            break;
//          case CDataAccess::ComparisonType::GREATER_THAN:
//            comparison_result = (string_value > *pstring_value_);
//            break;
//          default:
//            break;
//        }
//
//        break;
//      default:
//        break;
//    }
//  }
//
//  return comparison_result;
//}
//
///*
// * For MATRIX, this->pint_value_[it] should be something
// * like this->pint_value_[ROW][it]
// */
//bool CDataAccess::CompareVector(std::string value_string,
//                                CDataAccess::ComparisonType comparison_type,
//                                int *items) {
//  bool compare = true;
//
//  int         int_value     = 0;
//  long int     int64_value   = 0;
//  double      double_value  = 0;
//  float       float_value   = 0.0f;
//  char        char_value    = '\x0';
//  bool        bool_value    = false;
//  std::string string_value  = "";
//
//  std::string one_value_string;
//  int pos = 0;
//  long int it = 0;
//
//  for (it=0; ( (it<length_x()) && (value_string!="") && (compare)) ; it++) {
//    pos = value_string.find(STR(TABLE_COL_SEPARATOR));
//
//    if (pos!=-1) {
//      one_value_string = value_string.substr(0, pos);
//      value_string = value_string.substr(pos + 1);
//    } else {
//      one_value_string = value_string;
//      value_string = "";
//    }
//
//    (*items)++;
//
//    if ((comparison_type == CDataAccess::ComparisonType::EQUAL) ||
//        (comparison_type == CDataAccess::ComparisonType::NOT_EQUAL)) {
//      std::istringstream ss1(one_value_string);
//
//      switch(GetVariantType()) {
//        case VariantType::INT:
//          ss1 >> int_value;
//          compare &= (this->pint_value_[it] == int_value);
//          break;
//        case VariantType::INT64:
//          ss1 >> int64_value;
//          compare &= (this->pint64_value_[it] == int64_value);
//          break;
//        case VariantType::DOUBLE:
//          ss1 >> double_value;
//          compare &= (this->pdouble_value_[it] == double_value);
//          break;
//        case VariantType::FLOAT:
//          ss1 >> float_value;
//          compare &= (this->pfloat_value_[it] == float_value);
//          break;
//        case VariantType::CHAR:
//          ss1 >> char_value;
//          compare &= (this->pchar_value_[it] == char_value);
//          break;
//        case VariantType::BOOL:
//          ss1 >> bool_value;
//          compare &= (this->pbool_value_[it] == bool_value);
//          break;
//        case VariantType::STRING:
//          ss1 >> string_value;
//          compare &= (this->pstring_value_[it] == string_value);
//          break;
//        default:
//          break;
//      }
//    }
//
//    // the string has more items than the vector. Let's count how many remain:
//    while (value_string != "") {
//      pos = value_string.find(STR(TABLE_COL_SEPARATOR));
//      if (pos!=-1) { value_string = value_string.substr(pos + 1); }
//      else { value_string = "";}
//      (*items)++;
//    }
//
//  }
//
//  return compare;
//}