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
 *  \brief     IObject.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      May 7, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "IObject.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>  // ostringstream
#include <cstdlib>  // atol


#include "language/CStringTable.h"
#include "util/CStringTools.h"
#include "messages/CLogger.h"
#include "CManager.h"
#include "data_manager/common/CDataAccess.h"
#include "data_manager/IData.h"


IObject::IObject() {
  set_type(KeyString::UNDEFINED_STRING);
  set_name("");
  set_type(KeyString::UNDEFINED_STRING);
  set_status(KeyString::UNDEFINED_STRING);
}

IObject::IObject(const std::string &name) {
  set_type(KeyString::UNDEFINED_STRING);
  set_name(name);
  set_type(KeyString::UNDEFINED_STRING);
  set_status(KeyString::UNDEFINED_STRING);
}

IObject::~IObject() {
}

int IObject::PrintHeader(PrintMode print_mode) {
  if ((print_mode != PrintMode::VALUE) && (print_mode != PrintMode::STRING_VALUE)) {
    if (print_mode == PrintMode::JSON) {
        // std::cout << "{\"id\":\"" << name_ << "\",\"type\":\"" << STR2(type_) << "\",";
    } else {
      if (print_mode == PrintMode::NGASP) {
          if (name_.find("$") == std::string::npos) {
              std::cout << "dim -n " << name_ << " --as " << STR2(type_) << std::endl;
          }
          std::cout << "set --to " << name_ << " --eq \"";
      } else {
        int WIDTH = 80;
        int COLUMNS = 3;

        // Show name and type

        std::cout << STR(SPACE)
                  << STR(BOLD_START)
                  << name_
                  << STR(BOLD_END)
                  << STR(SPACE)
                  << STR(BLOCK)
                  << STR(SPACE)
                  << STR2(type_)
                  << STR(SPACE)
                  << STR(EOL);

        // Calculate the column width:
        int col_width = WIDTH / COLUMNS;

        // Discount the space for column separators:
        col_width -= STR(TABLE_COL_SEPARATOR).length();

        // Discount left and right field margins:
        col_width -= STR(TABLE_COL_MARGIN).length() * 2;

        std::cout << STR(TABLE_LINE_SEPARATOR);
        std::cout << STR(EOL);

        std::cout << STR(BOLD_START);
        std::cout << CStringTools::PrepareField(STR(PRINT_COLUMN_1), col_width, false,
            false);
        std::cout << CStringTools::PrepareField(STR(PRINT_COLUMN_2), col_width, false,
            false);
        std::cout << CStringTools::PrepareField(STR(PRINT_COLUMN_3), col_width, false,
            false);
        std::cout << STR(BOLD_END);
        std::cout << STR(EOL);

        std::cout << STR(TABLE_LINE_SEPARATOR);
        std::cout << STR(EOL);

        return col_width;
      }
    }
  }

  return 0;
}

void IObject::PrintFooter(PrintMode print_mode) {
  if ((print_mode != PrintMode::VALUE) && (print_mode != PrintMode::STRING_VALUE)) {
    if (print_mode == PrintMode::JSON) {
        // std::cout << "}";
    } else {
      if (print_mode == PrintMode::NGASP) {
          std::cout << std::endl;
      } else {
        std::cout << STR(TABLE_LINE_SEPARATOR);
        std::cout << STR(EOL);
      }
    }
  }
}

void IObject::PrintCommon(const std::string &var_name,
                          const std::string &type,
                          const std::ostringstream &value_string,
                          int col_width,
                          PrintMode print_mode) {
  if ((print_mode == PrintMode::JSON) ||
      (print_mode == PrintMode::NGASP)) {

  } else {
    if ((print_mode == PrintMode::VALUE) || (print_mode == PrintMode::STRING_VALUE)) {
      std::cout << value_string.str();
    } else {
      std::cout << CStringTools::PrepareField(var_name, col_width, false, false);
      std::cout << CStringTools::PrepareField(type, col_width, false, false);

      if (value_string.str().size() > static_cast<unsigned int>(col_width)) {
        std::cout << STR(EOL);
        std::cout << STR(TABLE_COL_MARGIN);
        std::cout << value_string.str();
      } else {
        std::cout << STR(TABLE_COL_MARGIN);
        std::cout << value_string.str();
      }

      std::cout << STR(EOL);
    }
  }
}




// =============================================================================

void IObject::EvalSet(CManager *manager,
                      bool set,
                      CDataAccess *this_info,
                      CDataAccess *ref_info) {
  if (!set) {
    *manager->logger() <<
    (*manager->logger()->error_message()
      << STR(QUOTE)
      << ref_info->initial_reference()
      << STR(QUOTE) << " or "
      << this_info->initial_reference()
      << STR(QUOTE)
      << STR(SET_VARIABLE_NOT_FOUND)
    );
  }
}

void IObject::EvalGet(CManager *manager,
                      bool get,
                      CDataAccess *data_access) {
  if ( (data_access->data_variable() == "inputs") ||
       (data_access->data_variable() == "outputs") ) {
    get = true;
  }
  if (!get) {
    *manager->logger() <<
    (*manager->logger()->error_message()
      << STR(QUOTE)
      << data_access->initial_reference()
      << STR(QUOTE)
      << STR(SET_VARIABLE_NOT_FOUND)
    );
  }
}

