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
 *  \brief     IBase.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef BACKEND_SRC_IBASE_H_
#define BACKEND_SRC_IBASE_H_

#include <cstddef>  // NULL Definition

#include "CManager.h"

class IBase {
 public:
  IBase() {
    set_manager(NULL);
  }
  virtual ~IBase();

 private:
  CManager *manager_;

 public:
  void Copy(const IBase &ref) {
    set_manager(ref.manager());
  }
    
 public:
  inline CManager *manager(void) const { return manager_; }
  inline void set_manager(CManager *manager) { manager_ = manager; }
};

#endif  // BACKEND_SRC_IBASE_H_
