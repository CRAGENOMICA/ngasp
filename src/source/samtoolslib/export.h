/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   export.h
 * Author: jjene
 *
 * Created on April 27, 2016, 9:20 AM
 */

#ifndef EXPORT_H
#define EXPORT_H

// =============================================================================
// Set here all samtools includes that are needed for all functions and structs
// exported below.
// =============================================================================

#ifdef __cplusplus
extern "C" {
#endif

// =============================================================================
// structs defined in .c files can not be included by ngasp. So that, set 
// them here and include this file in ngasp to get access to these structs.
// =============================================================================


// =============================================================================
// Set here all functions that you want to get access from ngasp.
// Then, include this file in ngasp.
// =============================================================================

int samtools_main(int argc, char *argv[]);
int bam_index(int argc, char *argv[]);
int bam_idxstats_ngasp(int argc, char *argv[], char **names);
int main_samview(int argc, char *argv[]);
int faidx_main(int argc, char *argv[]);


#ifdef __cplusplus
}
#endif

#endif /* EXPORT_H */

