/*
 * mstatspop, Statistical Analysis using Multiple Populations for Genomic Data.
 * Copyright (c) 2009-2017, Sebastián Ramos Onsins,
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

/*
 * COptionsContainer.cpp
 *
 *  Created on: May 2, 2012
 *      Author: gvera
 */

#include "COptionsContainer.h"

#include <string>
#include <iterator>
#include <string.h>  // strncpy
#include <getopt.h>  // struct option

#include "../../language/CStringTable.h"

COptionsContainer::COptionsContainer()
{
	options_ = new std::list<COption *>();
}

COptionsContainer::~COptionsContainer()
{
	if (options_) {
    // Delete all list elements:

    std::list<COption *>::iterator it = options_->begin();
    while (it != options_->end()) {
      delete *it;
      it++;
    }

    // Delete the list:

    options_->clear();
    delete options_;
    options_ = NULL;
	}
}

void COptionsContainer::DefineGeneralOptions() {
  push(new COption(
          COption::OPTDIR::READ,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          KeyString::GOS_HELP_SHORT,
          KeyString::GOS_HELP_LONG,
          KeyString::GOS_HELP_DESC,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          -1,
          -1,
          COption::ARGTYPES::ARGTYPE_no_argument,
          COption::OPTTYPES::OPTTYPE_optional));
  
  push(new COption(
          COption::OPTDIR::READ,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          KeyString::GOS_VERSION_SHORT,
          KeyString::GOS_VERSION_LONG,
          KeyString::GOS_VERSION_DESC,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          -1,
          -1,
          COption::ARGTYPES::ARGTYPE_no_argument,
          COption::OPTTYPES::OPTTYPE_optional));
  
  push(new COption(
          COption::OPTDIR::READ,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          KeyString::GOS_VERBOSE_SHORT,
          KeyString::GOS_VERBOSE_LONG,
          KeyString::GOS_VERBOSE_DESC,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          -1,
          -1,
          COption::ARGTYPES::ARGTYPE_no_argument,
          COption::OPTTYPES::OPTTYPE_optional));
  
  push(new COption(
          COption::OPTDIR::READ,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          KeyString::GOS_DRYRUN_SHORT,
          KeyString::GOS_DRYRUN_LONG,
          KeyString::GOS_DRYRUN_DESC,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          KeyString::UNDEFINED_STRING,
          -1,
          -1,
          COption::ARGTYPES::ARGTYPE_no_argument,
          COption::OPTTYPES::OPTTYPE_optional));
}
/*
 * ----------------------------------------------------------------------------
 * push:
 */
void COptionsContainer::push( COption * const & _newOption )
{
	options_->push_back( _newOption );
}

/**
 * pop : Returns and removes the first COption object from the map of objects
 */
COption * COptionsContainer::pop( void )
{
  COption * _tmpOption = NULL;

  if (options_->size() > 0) {
    _tmpOption = options_->front();
    options_->pop_front();
  }

  return (_tmpOption);
}

/*
 * * ----------------------------------------------------------------------------
 *	Getter for mapOptions objects
 */
std::list<COption *> * COptionsContainer::getMapOptions(void) {
  return options_;
}

/**
 * return just the length of the list
 * @return
 */
int	COptionsContainer::size(void) {
	return( options_->size() );
}

int COptionsContainer::size(COption::OPTDIR direction) {
  int counter = 0;
	std::list<COption *>::iterator opt;
	
  for (opt = options_->begin(); opt != options_->end(); opt++) {
    if ((*opt)->direction() == direction) {
      counter++;
    }
  }

  return counter;
}

// Retrieves a pointer to the Nth element of the list of Options
COption * COptionsContainer::getNthElement( int _idx )
{
	std::list<COption *>::iterator plo;
	int idx = 0;

	if (_idx >= 0){
		// We have to check if options_ is valid
		for (idx=0, plo=options_->begin(); plo != options_->end(); plo++, idx++){
			if (idx == _idx) {
				return((*plo));
			}
		}

		return( NULL );
	}
	else {
		return( NULL );
	}
}


//Given a pointer it will populate its contents. MEMORY Allocated previously!
//and
//It fills the C string required by getopt
void COptionsContainer::fillOptions(  struct option * _pLongOptions, char * _pShortOptions )
{
	std::list<COption *>::iterator plo;
	int idx = 0;
	struct option * strLO;
	char * tmpName = NULL;
	std::string tmpShort = "";

//	getopt.h
//	struct option {
//	   const char *name;
//	   int         has_arg; // three values: no_argument, required_argument, optional_argument
//	   int        *flag;
//	   int         val;
//	};

	strLO = (struct option *) _pLongOptions; // Address of the next structure element - pointer arithmetics
	for( idx=0, plo = options_->begin(); plo != options_->end(); plo++, idx++, strLO++ )
	{
	  int tmpName_size = (*plo)->long_name().size();
		tmpName = new char[tmpName_size + 1];
		strncpy( tmpName, (*plo)->long_name().c_str(), tmpName_size );
		tmpName[tmpName_size] = '\x0'; /* null character manually addded */
		strLO->name = tmpName;


		tmpShort.append((*plo)->short_name().c_str());

		// 2. int has_arg
		switch ( (*plo)->arg_type()) {
			case COption::ARGTYPE_no_argument:
				strLO->has_arg = no_argument;

			break;
			case COption::ARGTYPE_arg_required:
				strLO->has_arg = required_argument;
				tmpShort.append(":");

			break;
//			case COption::ARGTYPE_arg_optional:
//				strLO->has_arg = optional_argument;
//				tmpShort.append( "::" ); // GNU extension for optional args
//
//			break;
			case COption::ARGTYPE_undefined:
				//exit(EXIT_FAILURE);
			break;

			default: // ERROR!
				//exit(EXIT_FAILURE);
			break;
		}
		// 3. & 4.
		strLO->flag = 0;	// We provide a value to identify the option
		strLO->val  = 0;
		if ((*plo)->short_name().length() > 0) {
		  strLO->val = (*plo)->short_name()[0]; //idx;// And the value is the index!
		}
	}

	strncpy(_pShortOptions, tmpShort.c_str(), tmpShort.size());
}


void COptionsContainer::AddInoutDefinition(std::string class_name,
                                           std::string var_name,
                                           COption::OPTDIR dir) {
  //std::cout << class_name << " " << var_name << std::endl;
}
