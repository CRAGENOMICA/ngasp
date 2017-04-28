/*
 * mstatspop, Statistical Analysis using Multiple Populations for Genomic Data.
 * Copyright (c) 2009-2017, Sebastián Ramos Onsins,
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

/*
 * COptionsContainer.h
 *
 *  Created on: May 2, 2012
 *      Author: gvera
 */

/*
 * NOTA: La reserva de memoria de las COption * debe realizarse fuera de esta clase?
 * Yo creo que no!La memoria que necesite cada clase/objeto debe gestionarselo el mismo.
 * Si, si, ya, pero de momento, hacemos un new COption y eso se lo pasamos a push... Ya lo arreglamos cuando este cerrado.
 *
 */

#ifndef COPTIONSCONTAINER_H_
#define COPTIONSCONTAINER_H_

#include <list>
#include <getopt.h>  // struct option

#include "COption.h"
#include "../../IBase.h"

class COptionsContainer : public IBase {
 public:
	COptionsContainer();
	virtual ~COptionsContainer();

 private:
  std::list<COption *> *  options_;

 public:
  inline int GetOptionsCount() { return options_->size(); }
  inline std::list<COption *>::iterator GetFirstOptionIterator() { return options_->begin(); }
  inline std::list<COption *>::iterator GetLastOptionIterator() { return options_->end(); }

 public:
  void DefineGeneralOptions();

	void fillOptions(struct option * _pLongOptions, char * _pShortOptions);// Given a pointer it will populate its contents. MEMORY Allocated previously! & it return the C string required by getopt
	COption *getNthElement(int);		// Retrieves a pointer to the Nth element of the list of Options
	int size(void);		// return just the length of the list
  int size(COption::OPTDIR direction);		// return number of items of COption::OPTDIR type
	std::list<COption *> * 	getMapOptions( void );
	void push( COption * const & );
	COption *pop( void );
  
 public:
  void AddInoutDefinition(std::string class_name,
                          std::string var_name,
                          COption::OPTDIR dir);  
};

#endif /* COPTIONSCONTAINER_H_ */
