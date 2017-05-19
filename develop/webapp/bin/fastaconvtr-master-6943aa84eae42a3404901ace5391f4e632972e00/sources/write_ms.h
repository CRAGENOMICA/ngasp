/*
 *  write_ms.h
 *  fasta2ms2
 *
 *  Created by Sebastian E. Ramos Onsins on 27/11/2012.
 *  Copyright 2012 CRAG. All rights reserved.
 *
 */

#ifndef WRITE_MS_
#define WRITE_MS_

#ifdef	__cplusplus
extern "C" {
#endif
	
#include "common.h"
#include "zutil.h"
	
	void usage(void);
	double probQ_chisquare(int dgf,  double chisq);

	
#ifdef	__cplusplus
}
#endif

#endif /* WRITE_MS_ */
