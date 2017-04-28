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
 *  \brief     CCalcRandomize.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CCalcRandomize.h"

#include <cmath>
#include <stdlib.h>  // RAND_MAX

#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/mersenne_twister.hpp>  // mt19937

#include "../../language/CStringTable.h"
#include "../../data_manager/common/CDataAccess.h"

#include "../../calculations/util/CComparison.h"


CCalcRandomize::CCalcRandomize()
: ICalculation(KeyString::CALC_RANDOMIZE,
               KeyString::CALC_RANDOMIZE_BRIEF_DESC,
               KeyString::CALC_RANDOMIZE_DESC,
               KeyString::NGASP_AUTHORS,
               KeyString::MSTATSPOP_COPYRIGHT,
               KeyString::GENERIC_CITATIONS,
               KeyString::UNDEFINED_STRING) {        
  BEGIN_CALCULATION_INTERFACE_DEFINITION
    // Empty
  
    SET_OUTPUT_INFO(ran,                                                        // Variable
                   UNDEFINED_STRING,                                            // Group
                   UNDEFINED_STRING,                                            // Short Name
                   UNDEFINED_STRING,                                            // Long Name
                   UNDEFINED_STRING,                                            // Description
                   UNDEFINED_STRING,                                            // Example
                   UNDEFINED_STRING,                                            // Use only if
                   UNDEFINED_STRING,                                            // Default value
                   UNDEFINED_VALUE,                                             // Min. Value
                   UNDEFINED_VALUE,                                             // Max. Value
                   OPTTYPE_mandatory)                                           // Required
  END_CALCULATION_INTERFACE_DEFINITION
  
  uni = NULL;
}

CCalcRandomize::~CCalcRandomize() {
  if (uni != NULL) {
    delete uni;
    uni = NULL;
  }
}

void CCalcRandomize::Print(PrintMode print_mode) {
  int col_with = PrintHeader(print_mode);
  PrintInputsOutputs(col_with);
  PrintFooter(print_mode);
}

std::size_t CCalcRandomize::Size(void) {
  long int total = sizeof(*this);
  return total;
}

void CCalcRandomize::Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action) {
  bool set = false;
  set = SetInputsOutputs(this_info->data_variable(), ref_info->value());
  EvalSet(manager(), set, this_info, ref_info);
}

void CCalcRandomize::Get(CDataAccess *data_access) {
  bool get = false;
  EvalGet(manager(), get, data_access);
}

void CCalcRandomize::Prepare(void) {
  DM_GET_INPUTS
    // Empty
  DM_GET_OUTPUTS
    DM_OUTPUT(ran)
  DM_END
}

/**
 * Define a uniform random number distribution which produces "double"
 * values between 0 and 1 (0 inclusive, 1 exclusive).
 * 
 * @param seed
 */
void CCalcRandomize::InitSeed(long int seed) {
  // ---------------------------------------------------------------------------
  // MSTATSPOP RANDOM RUMBERS
  // ---------------------------------------------------------------------------
  DM_GET_DATA2(idum, STR(IDUM))
  
  // ---------------------------------------------------------------------------
  // STDLIB RANDOM NUMBERS
  // ---------------------------------------------------------------------------
  // idum->set_value(-seed);
  // srand (idum->value());
  // ---------------------------------------------------------------------------
  
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // BOOST RANDOM NUMBERS
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /*
  generator.seed(static_cast<long int>(seed));  // (std::time(0))
  boost::uniform_real<> uni_dist(0,1);

  if (uni != NULL) {
    delete uni;
    uni = NULL;
  }

  uni = new boost::variate_generator<base_generator_type&, boost::uniform_real<> >(generator, uni_dist);
  */ 
 // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}

void CCalcRandomize::Calculate(bool dry_run) {
// ---------------------------------------------------------------------------
// MSTATSPOP METHOD FOR GENERATING RANDOM NUMBERS
// ---------------------------------------------------------------------------
	long int j,k;
	static long int iv[NTAB],iy=0;
	static double NDIV = (double)1.0/((double)1.0+((double)IM-(double)1.0)/(double)NTAB);
	static double RNMX = ((double)1.0-(double)EPS);
	static double AM = ((double)1.0/(double)IM);
	//double ran;

	//double precisionv(double,int);

	if( (idum->value() <= 0) || (iy == 0) )
	{
		idum->set_value(MAX(-idum->value(),idum->value()));
		for( j=NTAB+7; j>=0; j-- )
		{
			k 		= (long int)((double)idum->value()/(double)IQ);
			idum->set_value(IA*(idum->value()-k*IQ)-IR*k);
			if(idum->value() < 0)
				idum->add(IM);
			if(j < NTAB)
				iv[j] = idum->value();
		}
		iy = iv[0];
	}
	k 		= (long int)((double)idum->value()/(double)IQ);
	idum->set_value(IA*(idum->value()-k*IQ)-IR*k);

	if(idum->value()<0)
		idum->add(IM);

	j 		= (long int)((double)iy*NDIV);
	iy 		= iv[j];
	iv[j] 	= idum->value();
	ran->set_value(MIN((double)AM*(double)iy,(double)RNMX));
	
	//precision of 1e-7
	//
	//ran = precisionv(ran,(int)7);
	//
  
  // ---------------------------------------------------------------------------
  // STDLIB RANDOM NUMBERS
  // ---------------------------------------------------------------------------
  /*
   double random_value = (double)(rand() % NGASP_RAND_MAX) / (double)RAND_MAX;
   ran->set_value(random_value);
  */ 
  // ---------------------------------------------------------------------------
  
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // BOOST RANDOM NUMBERS
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /*
  if (uni != NULL) {
    ran->set_value(uni->operator ()());
  }
  */
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}
/*
void CCalcRandomize::Calculate(bool dry_run) {
  DM_GET_INPUTS
    // Empty
  DM_GET_OUTPUTS
    DM_INOUTPUT2(CDataInt64, idum)
    DM_OUTPUT2(CDataDouble, ran)
  DM_END

}
*/
void CCalcRandomize::Finalize(void) {
  DM_DEL_ALL_LOCAL_DATA
}

