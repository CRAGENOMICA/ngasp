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
 *  \brief     CConnectorDef.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      October 13, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#ifndef CCONNECTORDEF_H
#define	CCONNECTORDEF_H

#include <string>

enum ConnectorDirection {
  UNDEFINED_CONNECTOR = 0,
  INPUT_CONNECTOR  = 1,
  OUTPUT_CONNECTOR = 2,
  INOUT_CONNECTOR  = 3,
};

class CConnectorDef
{
 private:
  std::string type_;
  std::string name_;
  ConnectorDirection direction_;

 public:
  CConnectorDef() {
    direction_ = UNDEFINED_CONNECTOR;
    type_ = "";
    name_ = "";
  }
  CConnectorDef(const CConnectorDef &orig) {
    direction_ = orig.direction_;
    type_ = orig.type_;
    name_ = orig.name_;
  }
  CConnectorDef(ConnectorDirection direction,
                std::string type,
                std::string name) {
    direction_ = direction;
    type_ = type;
    name_ = name;
  }
  ~CConnectorDef() {
    direction_ = UNDEFINED_CONNECTOR;
    type_ = "";
    name_ = "";
  }

public:
  void set_type(std::string &type) { type_ = type; }
  std::string type(void) { return type_; }

  void set_name(std::string &name) { name_ = name; }
  std::string name(void) { return name_; }

  void set_direction(ConnectorDirection &direction) { direction_ = direction; }
  ConnectorDirection direction(void) { return direction_; }
};

#endif	/* CCONNECTORDEF_H */

