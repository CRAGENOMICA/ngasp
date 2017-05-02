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
 *  \brief     CValuesGFF.cpp
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Apr 17, 2015
 *  \pre
 *  \bug
 *  \warning
 */

#include "CValuesGFF.h"

#include <cstring>

CValuesGFF::CValuesGFF() {

  memset(filename, 0, FILE_NAME_LEN);
  memset(source, 0, SOURCE_LEN);
  memset(feature, 0, FEATURE_LEN);
  memset(strand, 0, STRAND_LEN);
  start = 0;
  end = 0;
  memset(score, 0, SCORE_LEN);
  memset(frame, 0, FRAME_LEN);
  memset(seqname, 0, SEQ_NAME_LEN);
  memset(gene_id, 0, GENE_ID_LEN);
  memset(transcript_id, 0, TRANSCRIPT_ID_LEN);
}

CValuesGFF::~CValuesGFF() {
}

