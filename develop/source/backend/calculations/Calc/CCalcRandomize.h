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
 *  \brief     CCalcRandomize.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      July 23, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_CALCS_CCALCRANDOMIZE_H_
#define CALCULATIONS_CALCS_CCALCRANDOMIZE_H_

#include "../ICalculation.h"
#include "../../data_manager/common/CDataAccess.h"

#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/mersenne_twister.hpp>  // mt19937

#include "../../data_manager/CDataManager.h"
#include "../../data_manager/Data/CDataInt64.h"
#include "../../data_manager/Data/CDataDouble.h"

// ---------------------------------------------------------------------------
// MSTATSPOP CONSTANTS
// ---------------------------------------------------------------------------
#define IA 16807
#define IM 2147483647
#define IQ 127773
#define IR 2836
#define NTAB 32
#define EPS (1.2E-07)

#define NGASP_RAND_MAX 32766  // <- RAND_MAX - 1

// http://www.boost.org/doc/libs/1_55_0/libs/random/example/random_demo.cpp
// This is a typedef for a random number generator.
// Try boost::mt19937 or boost::ecuyer1988 instead of boost::minstd_rand
typedef boost::mt19937 base_generator_type;

class CCalcRandomize : public ICalculation {
 private:
  // Inputs
    // Empty
  
  // Outputs
  CDataDouble *ran;
  
 private:
  CDataInt64 *idum;
  
 public:
  CCalcRandomize();
  virtual ~CCalcRandomize();

 public:
  void Prepare(void);
  void Calculate(bool dry_run);
  void Finalize(void);

 public:
  ICalculation* clone() const { return new CCalcRandomize(); /*clone*/  }

 public:
 void Print(PrintMode print_mode) override;
 std::size_t Size(void);
 void Set(CDataAccess *this_info, CDataAccess *ref_info, SetAction action);
 void Get(CDataAccess *data_access);

 private:
  base_generator_type generator;
  boost::variate_generator<base_generator_type&, boost::uniform_real<> > *uni;
  
 public:
  void InitSeed(long int seed);
};

#endif  // CALCULATIONS_CALCS_CCALCRANDOMIZE_H_
