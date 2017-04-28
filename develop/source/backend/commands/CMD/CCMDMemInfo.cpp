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
 *  \brief     CCMDMemInfo.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 28, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCMDMemInfo.h"

#include <string>
#include <sstream>
#include <map>
#include <iomanip>  // setprecision
#include <list>

#include "../../language/CStringTable.h"
#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataStdString.h"
#include "../../calculations/CAllCalculations.h"
#include "../../util/CStringTools.h"

CCMDMemInfo::CCMDMemInfo()
  : ICommand(CMD_MEMORY_INFO,                                                   // Command Name
             CMD_MEMORY_INFO_ABB,                                               // Command Abbreviation Name
             CMD_MEMORY_INFO_DESC,                                              // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
  set_print_mode(PrintMode::NORMAL);
}

CCMDMemInfo::~CCMDMemInfo() {
}

void CCMDMemInfo::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    MEMORY_INFO_PRINT_MODE_SHORT,                               // Short Name
                    MEMORY_INFO_PRINT_MODE_LONG,                                // Long Name
                    MEMORY_INFO_PRINT_MODE_DESC,                                // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_optional)                                           // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDMemInfo::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::MEMORY_INFO_PRINT_MODE_SHORT:
      set_print_mode(arguments);
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

#define WIDTH    80
#define COLUMNS  3

void CCMDMemInfo::Run() {

  if (print_mode() == PrintMode::JSON) {
    std::map< std::string, IData *>::iterator it;
    for (it = manager()->data_manager()->repository()->begin();
         it != manager()->data_manager()->repository()->end(); ++it) {
      std::cout << it->second->ToJSON();
    }
  } else {
    // Calculate the column width dynamically:
    int col_width = WIDTH / COLUMNS;

    // Discount the space for column separators:
    col_width -= STR(TABLE_COL_SEPARATOR).length();

    // Discount left and right field margins:
    col_width -= STR(TABLE_COL_MARGIN).length() * 2;


    int col_widths[COLUMNS];
    for (int i = 0; i < COLUMNS; i++) {
      col_widths[i] = col_width;
    }

    col_widths[0] += 14;
    col_widths[1] -= 7;
    col_widths[2] -= 7;

    // ===========================================================================
    // PRINT HEADER
    // ===========================================================================

    std::cout << STR(TABLE_LINE_SEPARATOR);
    std::cout << STR(EOL);

    // std::cout << STR(BOLD_START);
    std::cout << CStringTools::PrepareField(STR(MEMINFO_COL_1), col_widths[0],
            false, false);
    std::cout << CStringTools::PrepareField(STR(MEMINFO_COL_2), col_widths[1],
            false, false);
    std::cout << CStringTools::PrepareField(STR(MEMINFO_COL_3), col_widths[2],
            true, false);
    // std::cout << STR(BOLD_END);
    std::cout << STR(EOL);

    std::cout << STR(TABLE_LINE_SEPARATOR);
    std::cout << STR(EOL);

    // ===========================================================================
    // PRINT DATA OBJECTS
    // ===========================================================================

    float total_size = 0;
    long int current_size = 0;
    std::stringstream current_size_text;

    std::map< std::string, IData *>::iterator it;
    for (it = manager()->data_manager()->repository()->begin();
         it != manager()->data_manager()->repository()->end(); ++it) {

      if (it->second->type_key() == KeyString::DATA_STD_STRING) {
        CDataStdString *p = NULL;
        p = (static_cast<CDataStdString *>(it->second));
        current_size = p->CDataStdString::Size();
      } else {
        current_size = it->second->Size();
      }

      current_size_text.clear();  // clear any bits set
      current_size_text.str(std::string());  // clear
      current_size_text << current_size;

//      std::cout << CStringTools::PrepareField(STR2(it->second->group()),
//          col_widths[0], false, false);
      std::cout << CStringTools::PrepareField(it->second->full_name(), col_widths[0],
          false, (manager()->with() == it->second));
      std::cout << CStringTools::PrepareField(it->second->type(), col_widths[1],
          false, false);
//      std::cout << CStringTools::PrepareField(it->second->status(), col_widths[3],
//          false, false);
      std::cout << CStringTools::PrepareField(current_size_text.str()
          + STR(TABLE_UNIT_BYTES), col_widths[2], true, false);
      std::cout << STR(EOL);

      total_size += current_size;
    }

    // ===========================================================================
    // PRINT CALCULATION OBJECTS
    // ===========================================================================
/*
    for (std::list<ICalculation *>::iterator it =
         manager()->all_calculations()->calculations()->begin();
        it != manager()->all_calculations()->calculations()->end();
        ++it) {
      current_size = (*it)->Size();
      current_size_text.clear();  // clear any bits set
      current_size_text.str(std::string());  // clear
      current_size_text << current_size;

//      std::cout << CStringTools::PrepareField(STR2((*it)->group()), col_widths[0],
//        false, false);
//      std::cout << CStringTools::PrepareField((*it)->name(), col_widths[1],
//        false, (manager()->with() == (*it)));
//      std::cout << CStringTools::PrepareField((*it)->type(), col_widths[2],
//        false, false);
//      std::cout << CStringTools::PrepareField((*it)->status(), col_widths[3],
//        false, false);
      std::cout << CStringTools::PrepareField(current_size_text.str()
        + STR(TABLE_UNIT_BYTES), col_widths[2], true, false);
      std::cout << STR(EOL);

      total_size += current_size;
    }
*/
    // ===========================================================================
    // PRINT FOOTER
    // ===========================================================================

    std::cout << STR(TABLE_LINE_SEPARATOR);
    std::cout << STR(EOL);

    total_size /= 1024;  // Bytes to KB
    std::stringstream total_size_text;
    total_size_text << std::setprecision(1) << total_size;

    std::cout << CStringTools::PrepareField("", col_widths[0], false, false);
    std::cout << CStringTools::PrepareField("", col_widths[1], false, false);
//    std::cout << CStringTools::PrepareField("", col_widths[2], true, false);
//    std::cout << CStringTools::PrepareField("", col_widths[3], true, false);

    std::cout << CStringTools::PrepareField(total_size_text.str()
        + STR(TABLE_UNIT_KB), col_widths[2], true, false);
    std::cout << STR(EOL);

    std::cout << STR(MEMINFO_FOOTER);
  }
}

void CCMDMemInfo::Finalize() {
  /// Clean the command to reuse it later:
  set_print_mode(PrintMode::NORMAL);
  
  DM_DEL_ALL_LOCAL_DATA
}

