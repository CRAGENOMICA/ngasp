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
/**
 *  \brief     CValuesGFF.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 17, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef CALCULATIONS_UTIL_CVALUESGFF_H_
#define CALCULATIONS_UTIL_CVALUESGFF_H_

#include <cstring>

#define FILE_NAME_LEN 256
#define SOURCE_LEN 256
#define FEATURE_LEN 256
#define STRAND_LEN 1
#define SCORE_LEN 256
#define FRAME_LEN 1
#define SEQ_NAME_LEN 256
#define GENE_ID_LEN 256
#define TRANSCRIPT_ID_LEN 256

class CValuesGFF {
public:
  CValuesGFF();
  virtual ~CValuesGFF();

public:
  char filename[FILE_NAME_LEN];
  char source[SOURCE_LEN];
  char feature[FEATURE_LEN];
  char strand[STRAND_LEN];
  long int start;
  long int end;
  char score[SCORE_LEN];
  char frame[FRAME_LEN];
  char seqname[SEQ_NAME_LEN];
  char gene_id[GENE_ID_LEN];
  char transcript_id[TRANSCRIPT_ID_LEN];


  static int comp_trcpt_id(const void *a,const void *b)
  {
    int value;
    CValuesGFF *ia = (CValuesGFF *)a;
    CValuesGFF *ib = (CValuesGFF *)b;

    value = strcmp(ia->transcript_id,ib->transcript_id);
    return value;
  }

  static int comp_start_id(const void *a,const void *b)
  {
    CValuesGFF *ia = (CValuesGFF *)a;
    CValuesGFF *ib = (CValuesGFF *)b;

    if(ia->start < ib->start) return(-1);
    if(ia->start > ib->start) return(+1);
    return 0;
  }

  static int comp_end_id(const void *a,const void *b)
  {
    CValuesGFF *ia = (CValuesGFF *)a;
    CValuesGFF *ib = (CValuesGFF *)b;

    if(ia->end < ib->end) return(-1);
    if(ia->end > ib->end) return(+1);
    return 0;
  }

  static int comp_gene_id(const void *a,const void *b)
  {
    int value;
    CValuesGFF *ia = (CValuesGFF *)a;
    CValuesGFF *ib = (CValuesGFF *)b;

    value = strcmp(ia->gene_id,ib->gene_id);
    return value;
  }

};



#endif /* CALCULATIONS_UTIL_CVALUESGFF_H_ */
