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
 *  \brief     IData.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      April 27, 2015
 *  \pre
 *  \bug
 *  \warning
*/

#ifndef BACKEND_SRC_DATA_MANAGER_IDATA_H_
#define BACKEND_SRC_DATA_MANAGER_IDATA_H_

#include <string>

#include "../IBase.h"
#include "../language/CStringTable.h"
#include "../IObject.h"
#include "common/CDataAccess.h"

enum CollectionType {
  TYPE_UNDEFINED = -1,
  PRIMITIVE      = 0,  // The value indicate dimensions, too.
  VECTOR         = 1,
  MATRIX         = 2,
  CUBE           = 3,
};

class IData : public IBase, public IObject {
 public:
  IData(const KeyString type,
        const KeyString primitive,
        CollectionType collection);
  IData() {}
  virtual ~IData();
 
 private:
  std::string experiment_;
  KeyString primitive_;
  CollectionType collection_;
  bool auto_created_;

 public:
  void Copy(const IData &ref) {
    // Copy hicheracy data members
    // ---------------------------

    IBase::Copy(ref);
    IObject::Copy(ref);
    
    
    // Copy this data
    // --------------
    
    set_experiment(ref.experiment());
    set_primitive(ref.primitive());
    set_collection(ref.collection());
    set_auto_created(ref.auto_created());
  }
  
 private:
  /**
   * Pointer to a function that must be called when this data changes.
   */
  void (*pOnChange_) (void);

 public:
  void SetOnChange(void (*p)(void)) {
    pOnChange_ = p;
  }
  void CallOnChange(void) {
    if (pOnChange_ != NULL) {
      (*pOnChange_)();
    }
  }

  /**
   *
   */
  virtual ComparisonType Compare(CDataAccess *this_info,
                                 CDataAccess *ref_info) {
    return ComparisonType::UNDEFINED;
  }

  /**
   *
   */
  virtual void add_value(std::string increment) {
  }

  virtual IData * clone() const = 0;  // Used by the Factory

 public:
  inline std::string experiment() const { return experiment_; }
  inline void set_experiment(const std::string experiment) {
    experiment_ = experiment;
  }
  inline void set_primitive(const KeyString & primitive) {
    primitive_ = primitive;
  }
  inline KeyString primitive(void) const { return primitive_; }

  inline void set_collection(const CollectionType & collection) {
    collection_ = collection;
  }
  inline CollectionType collection(void) const { return collection_; }

  inline void set_auto_created(const bool & auto_created) {
    auto_created_ = auto_created;
  }
  inline bool auto_created(void) const { return auto_created_; }
  
  
  /**
   * JSON
   */
  virtual std::string ToJSON(void) { return ""; }
};

#endif  // BACKEND_SRC_DATA_MANAGER_IDATA_H_
