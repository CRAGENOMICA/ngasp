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
 *  \brief     CCMDSyntax.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Aug 31, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include <iostream>

#include <list>
#include <string>

#include "CCMDSyntax.h"
#include "../../language/CStringTable.h"
#include "../CAllCommands.h"
#include "CCMDDim.h"
#include "CCMDCalc.h"
#include "../../util/CFile.h"
#include "../../data_manager/CDataManager.h"

CCMDSyntax::CCMDSyntax()
  : ICommand(CMD_SYNTAX,                                                        // Command Name
             CMD_SYNTAX_ABB,                                                    // Command Abbreviation Name
             CMD_SYNTAX_DESC,                                                   // Brief Description
             UNDEFINED_STRING,                                                  // Long Description
             NGASP_AUTHORS,                                                     // Authors
             UNDEFINED_STRING) {                                                // See also 
}

CCMDSyntax::~CCMDSyntax() {
}

void CCMDSyntax::DefineCommandOptions() {
  BEGIN_COMMAND_INTERFACE_DEFINITION
    SET_OPTION_INFO(UNDEFINED_STRING,                                           // Group
                    DATA_ONE_VALUE,                                             // Data Type
                    SYNTAX_EDITOR_SHORT,                                        // Short Name
                    SYNTAX_EDITOR_LONG,                                         // Long Name
                    SYNTAX_EDITOR_DESC,                                         // Description
                    UNDEFINED_STRING,                                           // Example                                
                    UNDEFINED_STRING,                                           // Use only if
                    UNDEFINED_STRING,                                           // Default value
                    UNDEFINED_VALUE,                                            // Min. Value
                    UNDEFINED_VALUE,                                            // Max. Value
                    ARGTYPE_arg_required,                                       // Argument Required
                    OPTTYPE_mandatory)                                          // Required
  END_COMMAND_INTERFACE_DEFINITION
}

bool CCMDSyntax::Prepare() {
  bool parseResult = true;

  KeyString option = KeyString::UNDEFINED_STRING;
  std::string arguments;

  while (getopt_long_own(&option, &arguments)) {
    switch (option) {
    case KeyString::SYNTAX_EDITOR_SHORT:
      editor_name_ = arguments;
      break;
    default:
      parseResult = false;
      break;
    }
  }

  return (CheckOptions() && parseResult);
}

#define SCREEN_WIDTH 80

void CCMDSyntax::Run() {

  if (CStringTools::ToLower(editor_name_) == "gedit") {
    // GEdit language syntax file for ngaSP:

    std::string buffer;
    std::string keywords;
    std::string types;

    /// All command names:

    for (std::list<ICommand *>::iterator cmd =
        this->manager()->all_commands()->GetFirstCommandIterator();
        cmd != manager()->all_commands()->GetLastCommandIterator();
        cmd++) {
        //if ((STR2((*cmd)->name()) != "") && (STR2((*cmd)->name())[0] != STR(RESERVED_DATA_NAME_PREFIX)[0])) {
          keywords += "      <keyword>";
          keywords += STR2((*cmd)->name());
          keywords += "</keyword>";
          keywords += STR(EOL);

          if (STR2((*cmd)->name()) != STR2((*cmd)->command_abbreviation())) {
            keywords += "      <keyword>";
            keywords += STR2((*cmd)->command_abbreviation());
            keywords += "</keyword>";
            keywords += STR(EOL);
          }
       // }
    }

    /// All calculation names:

    for (std::list<ICommand *>::iterator cmd =
      this->manager()->all_commands()->GetFirstCommandIterator();
      cmd != manager()->all_commands()->GetLastCommandIterator();
      cmd++) {
      if ((*cmd)->name() == KeyString::CMD_CALC) {
        std::list<ICalculation *>::iterator it;
        for (it = manager()->all_calculations()->calculations()->begin();
             it != manager()->all_calculations()->calculations()->end();
             ++it) {
          //if (((*it)->name() != "") && ((*it)->name()[0] != STR(RESERVED_DATA_NAME_PREFIX)[0])) {
            keywords += "      <keyword>";
            keywords += (*it)->name();
            keywords += "</keyword>";
            keywords += STR(EOL);
          //}
        }

//        CCMDCalc *cmd_calc = static_cast<CCMDCalc *>(*cmd);
//        std::list<KeyString>::iterator it;
//        for (it = cmd_calc->all_creatable_types()->begin();
//             it != cmd_calc->all_creatable_types()->end(); ++it) {
//          keywords += "      <keyword>";
//          keywords += STR2(((KeyString)(*it)));
//          keywords += "</keyword>";
//          keywords += STR(EOL);
//        }
      }
    }

  // All command options:
  //
  //  buffer += "    <context id=\"keywords\" style-ref=\"keyword\">";
  //  buffer += STR(EOL);
  //  for (std::list<ICommand *>::iterator cmd =
  //      this->manager()->all_commands()->GetFirstCommandIterator();
  //      cmd != manager()->all_commands()->GetLastCommandIterator();
  //      cmd++) {
  //
  //    for (std::list<COption *>::iterator command_option =
  //         (*cmd)->options()->GetFirstOptionIterator();
  //         command_option != (*cmd)->options()->GetLastOptionIterator();
  //         command_option++ ) {
  //
  //      buffer += "      <keyword>";
  //      buffer += "--" + (*command_option)->long_name();
  //      buffer += "</keyword>";
  //      buffer += STR(EOL);
  //
  //      if ((*command_option)->long_name() != (*command_option)->short_name()) {
  //        buffer += "      <keyword>";
  //        buffer += "-" + (*command_option)->short_name();
  //        buffer += "</keyword>";
  //        buffer += STR(EOL);
  //      }
  //    }
  //  }
  //  buffer += "    </context>";
  //  buffer += STR(EOL);


    /// All data types:

    for (std::list<ICommand *>::iterator cmd =
        this->manager()->all_commands()->GetFirstCommandIterator();
        cmd != manager()->all_commands()->GetLastCommandIterator();
        cmd++) {

      if ((*cmd)->name() == KeyString::CMD_DIM) {

        std::map<std::string, IData *>::iterator it;
        for (it = manager()->data_manager()->repository()->begin();
             it != manager()->data_manager()->repository()->end();
             ++it) {
          if ((it->second->name() != "") && (it->second->name()[0] != STR(RESERVED_DATA_NAME_PREFIX)[0])) {
            keywords += "      <keyword>";
            keywords += it->second->name();
            keywords += "</keyword>";
            keywords += STR(EOL);
          }
        }


//        CCMDDim *cmd_dim = static_cast<CCMDDim *>(*cmd);
//        std::list<KeyString>::iterator it;
//        for (it = cmd_dim->all_creatable_types()->begin();
//             it != cmd_dim->all_creatable_types()->end(); ++it) {
//          types += "      <keyword>";
//          types += STR2(((KeyString)(*it)));
//          types += "</keyword>";
//          types += STR(EOL);
//        }


      }
    }

    buffer += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" + STR(EOL);
    buffer += "<!--" + STR(EOL);
    buffer += " This file is part of GtkSourceView" + STR(EOL);
    buffer += STR(EOL);
    buffer += " Author: CRAG" + STR(EOL);
    buffer += " Copyright (C) 2015 CRAG" + STR(EOL);
    buffer += "-->" + STR(EOL);
    buffer += "<language id=\"ngasp\" _name=\"ngaSP\" version=\"2.0\" _section=\"Sources\">" + STR(EOL);
    buffer += "  <metadata>" + STR(EOL);
    buffer += "    <property name=\"globs\">*" + STR(SCRIPT_FILES_EXTENSION) + "</property>" + STR(EOL);
    buffer += "    <property name=\"line-comment-start\">#</property>" + STR(EOL);
    buffer += "  </metadata>" + STR(EOL);
    buffer += STR(EOL);
    buffer += "  <styles>" + STR(EOL);
    buffer += "    <style id=\"comment\" _name=\"Comment\" map-to=\"def:comment\"/>" + STR(EOL);
    buffer += "    <style id=\"string\" _name=\"String\" map-to=\"def:string\"/>" + STR(EOL);
    buffer += "    <style id=\"command_option\" _name=\"command_option\" map-to=\"def:preprocessor\"/>" + STR(EOL);
    buffer += "    <style id=\"keyword\" _name=\"Keyword\" map-to=\"def:keyword\"/>" + STR(EOL);
    buffer += "    <style id=\"type\" _name=\"Data Type\" map-to=\"def:type\"/>" + STR(EOL);
    buffer += "  </styles>" + STR(EOL);
    buffer += STR(EOL);
    buffer += "  <default-regex-options case-sensitive=\"false\"/>" + STR(EOL);
    buffer += STR(EOL);
    buffer += "  <definitions>" + STR(EOL);
    buffer += STR(EOL);
    buffer += "    <context id=\"line-comment\" style-ref=\"comment\" end-at-line-end=\"true\" class=\"comment\" class-disabled=\"no-spell-check\">" + STR(EOL);
    buffer += "      <start>#</start>" + STR(EOL);
    buffer += "      <include>" + STR(EOL);
    buffer += "        <context ref=\"def:in-line-comment\"/>" + STR(EOL);
    buffer += "      </include>" + STR(EOL);
    buffer += "    </context>" + STR(EOL);
    buffer += STR(EOL);
    buffer += "    <context id=\"string\" style-ref=\"string\" end-at-line-end=\"false\" class=\"string\" class-disabled=\"no-spell-check\">" + STR(EOL);
    buffer += "      <start>\"</start>" + STR(EOL);
    buffer += "      <end>\"</end>" + STR(EOL);
    buffer += "    </context>" + STR(EOL);
    buffer += STR(EOL);
    buffer += "    <context id=\"command_option\" style-ref=\"command_option\">" + STR(EOL);
    buffer += "      <match>\\-+\\w+</match>" + STR(EOL);
    buffer += "    </context>" + STR(EOL);
    buffer += STR(EOL);
    buffer += "    <context id=\"keywords\" style-ref=\"keyword\">" + STR(EOL);
    buffer += keywords;
    buffer += "    </context>" + STR(EOL);
    buffer += STR(EOL);
    buffer += "    <context id=\"types\" style-ref=\"type\">" + STR(EOL);
    buffer += types;
    buffer += "    </context>" + STR(EOL);
    buffer += STR(EOL);
    buffer += "    <context id=\"ngasp\" class=\"no-spell-check\">" + STR(EOL);
    buffer += "      <include>" + STR(EOL);
    buffer += "        <context ref=\"line-comment\"/>" + STR(EOL);
    buffer += "        <context ref=\"string\"/>" + STR(EOL);
    buffer += "        <context ref=\"command_option\"/>" + STR(EOL);
    buffer += "        <context ref=\"keywords\"/>" + STR(EOL);
    buffer += "        <context ref=\"types\"/>" + STR(EOL);
    buffer += "      </include>" + STR(EOL);
    buffer += "    </context>" + STR(EOL);
    buffer += STR(EOL);
    buffer += "  </definitions>" + STR(EOL);
    buffer += STR(EOL);
    buffer += "</language>" + STR(EOL);


    CFile::ReplaceContentBy("/usr/share/gtksourceview-3.0/language-specs/ngasp.lang",
                            buffer);

    NORMAL_MSG << "Done." END_MSG;

  } else {
    // TODO(jjene) Constant
    ERROR_MSG << "Syntax not defined for this editor..." END_MSG;
  }
}

void CCMDSyntax::Finalize() {
  /// Clean the command to reuse it later:
  DM_DEL_ALL_LOCAL_DATA
}

