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
 *  \brief     CAllCalculations.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */


#include "CAllCalculations.h"

#include <cstdint>
#include <list>
#include <iterator>
#include <iostream>

#include "ICalculation.h"
#include "../language/CStringTable.h"


CAllCalculations::CAllCalculations() {
  set_calculations(new std::list<ICalculation *>);
}

CAllCalculations::~CAllCalculations() {
  if (calculations()) {
    // Delete all list elements:
    std::list<ICalculation *>::iterator it = calculations()->begin();
    while (it != calculations()->end()) {
      delete *it;
      it++;
    }

    // Delete the list:
    calculations()->clear();
    delete calculations_;
    calculations_ = NULL;
  }
}

void CAllCalculations::AddCalculation(std::string name, ICalculation *calc) {
  if (calc != NULL) {
    calc->set_name(name);
    calc->set_status(KeyString::STATUS_READY);
    // calc->set_type(key);
    calc->set_manager(manager());

    RemoveCalculationByName(calc->parent(), calc->name());
    calculations()->push_back(calc);
    //!before manager()->set_with(calc->name());
  } else {
    ERROR_MSG << STR(CALC_TYPE_UNKNOWN) END_MSG;
  }
}

bool CAllCalculations::RemoveCalculationByName(IObject *parent,
                                               const std::string & name) {
  bool success = false;

  std::list<ICalculation *>::iterator it_delete = calculations()->end();

  for (std::list<ICalculation *>::iterator it  = calculations()->begin();
       ((it != calculations()->end()) && (it_delete == calculations()->end()));
       ++it ) {
    if (((*it)->name() == name) && ((*it)->parent() == parent)) {
      it_delete = it;
    }
  }

  if (it_delete != calculations()->end()) {
    ICalculation *calc = (*it_delete);
    calculations()->erase(it_delete);

    if (calc != NULL) {
      delete calc;
      calc = NULL;
      success = true;
    }
  }

  return success;
}


ICalculation *CAllCalculations::GetCalculationByName(IObject *parent,
                                                     const std::string & name) {
  ICalculation *calc = NULL;

  for (std::list<ICalculation *>::iterator it  = calculations()->begin();
       ((it != calculations()->end()) && (calc == NULL)); ++it ) {
    if (((*it)->name() == name) && ((*it)->parent() == parent)) {
      calc = (*it);
    }
  }

  return calc;
}



