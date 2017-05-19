/*
 *  common.h
 *  fasta2ms2
 *
 *  Created by Sebastian E. Ramos Onsins on 27/11/2012.
 *
 */

#ifndef COMMON_
#define COMMON_

#ifdef	__cplusplus
extern "C" {
	#endif
	
	#define _CRT_SECURE_NO_DEPRECATE
	
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <math.h>
	
	#define FASTA2MS2 "#fastaconvtr v0.1beta (20170502) Sebastian E. Ramos-Onsins.\n"

	#define MSP_MAX_FILENAME			(unsigned long) 1024 /**< @brief Maximum Filename Length allowed */
	#define MSP_MAX_GFF_WORDLEN         (unsigned long) 20
	#define MSP_GENETIC_CODETYPE_LEN	(unsigned long) 50	/* e.g. "Nuclear universal" */
	#define MSP_GENCODE_COMBINATIONS    (unsigned long) 64 /* 4^3 */
	#define MSP_GFF_CRITERIA_MSG_LEN    (unsigned long) 20 /* e.g. "MIN" */
	#define MSP_MAX_FILELINE_LEN		(unsigned long) 1024
	#define CHI_INTERVAL 10

	#ifndef NULL
	#define NULL	0
	#endif
	
	#ifdef	__cplusplus
	}
#endif

#endif /* COMMON */
