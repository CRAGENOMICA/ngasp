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
 *  \brief     CAllCalculations.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_CALCULATIONS_CALLCALCULATIONS_H_
#define BACKEND_SRC_CALCULATIONS_CALLCALCULATIONS_H_

#include <cstdint>
#include <list>

#include "../IBase.h"
#include "ICalculation.h"
#include "CCalcFactory.h"

class CAllCalculations : public IBase {
 public:
  CAllCalculations();
  ~CAllCalculations();

 public:
  template <class T>
  T *GetNewCalculation(IObject *parent, T *var, std::string name) {
    T ref;
    return static_cast<T *>(CreateCalcByKey(parent, name, ref.type_key()));
  }


  ICalculation *CreateCalcByType(IObject *parent,
                                 const std::string & name,
                                 std::string type) {
    ICalculation *calc = GetCalculationByName(parent, name);  // Find existing object

    if (calc == NULL) {
      if (name.find(STR(RESERVED_DATA_NAME_PREFIX)) != 0) {
        calc = manager()->calc_factory()->GetCalculation(type);
        if (calc != 0) {
          calc->set_parent(parent);
          AddCalculation(name, calc);
        }
      } else {
        ERROR_MSG << STR(CALC_RESERVED_NAME) END_MSG;
      }
    } else {
      ERROR_MSG << "Calculation " << name << " already exists..." END_MSG;
    }

    return calc;
  }

  ICalculation *CreateCalcByKey(IObject *parent,
                                const std::string & name,
                                KeyString key) {
    ICalculation *calc = GetCalculationByName(parent, name);  // Find existing object

    if (calc == NULL) {
      calc = manager()->calc_factory()->GetCalculation(key);
        if (calc != 0) {
          calc->set_parent(parent);
          AddCalculation(name, calc);
        }
    } else {
      ERROR_MSG << "Calculation " << name << " already exists..." END_MSG;
    }
    return calc;
  }

  void AddCalculation(std::string name, ICalculation *calc);
  bool RemoveCalculationByName(IObject *parent,
                               const std::string & name);
  ICalculation *GetCalculationByName(IObject *parent,
                                     const std::string & name);

 private:
  std::list<ICalculation *> *calculations_;

 public:
  inline std::list<ICalculation *> *calculations(void) { return calculations_; }
  inline void set_calculations(std::list<ICalculation *> *calculations) {
    calculations_ = calculations;
  }
};


#endif  // BACKEND_SRC_CALCULATIONS_CALLCALCULATIONS_H_
