#ifndef BAM_PLCMD_H
#define BAM_PLCMD_H

#include <config.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <getopt.h>
#include <htslib/sam.h>
#include <htslib/faidx.h>
#include <htslib/kstring.h>
#include <htslib/khash_str2int.h>
#include "sam_header.h"
#include "samtools.h"
#include "sam_opts.h"

#include <assert.h>
#include "bam2bcf.h"
#include "sample.h"

//!jeneje changed to "static" both functions:
static inline int printw(int c, FILE *fp);
static inline void pileup_seq(FILE *fp, const bam_pileup1_t *p, int pos, int ref_len, const char *ref);


#define MPLP_BCF        1
#define MPLP_VCF        (1<<1)
#define MPLP_NO_COMP    (1<<2)
#define MPLP_NO_ORPHAN  (1<<3)
#define MPLP_REALN      (1<<4)
#define MPLP_NO_INDEL   (1<<5)
#define MPLP_REDO_BAQ   (1<<6)
#define MPLP_ILLUMINA13 (1<<7)
#define MPLP_IGNORE_RG  (1<<8)
#define MPLP_PRINT_POS  (1<<9)
#define MPLP_PRINT_MAPQ (1<<10)
#define MPLP_PER_SAMPLE (1<<11)
#define MPLP_SMART_OVERLAPS (1<<12)

void *bed_read(const char *fn);
void bed_destroy(void *_h);
int bed_overlap(const void *_h, const char *chr, int beg, int end);

typedef struct {
    int min_mq, flag, min_baseQ, capQ_thres, max_depth, max_indel_depth, fmt_flag;
    int rflag_require, rflag_filter;
    int openQ, extQ, tandemQ, min_support; // for indels
    double min_frac; // for indels
    char *reg, *pl_list, *fai_fname, *output_fname;
    faidx_t *fai;
    void *bed, *rghash;
    int argc;
    char **argv;
    sam_global_args ga;
} mplp_conf_t;

typedef struct {
    char *ref[2];
    int ref_id[2];
    int ref_len[2];
} mplp_ref_t;


#define MPLP_REF_INIT {{NULL,NULL},{-1,-1},{0,0}}

typedef struct {
    samFile *fp;
    hts_itr_t *iter;
    bam_hdr_t *h;
    mplp_ref_t *ref;
    const mplp_conf_t *conf;
} mplp_aux_t;

typedef struct {
    int n;
    int *n_plp, *m_plp;
    bam_pileup1_t **plp;
} mplp_pileup_t;


//static 
int mplp_get_ref(mplp_aux_t *ma, int tid,  char **ref, int *ref_len);
//static 
int mplp_func(void *data, bam1_t *b);
//static 
void group_smpl(mplp_pileup_t *m, bam_sample_t *sm, kstring_t *buf,
                       int n, char *const*fn, int *n_plp, const bam_pileup1_t **plp, int ignore_rg);
//static 
#ifdef __cplusplus
extern "C" {
#endif
int mpileup(mplp_conf_t *conf, int n, char **fn);
#ifdef __cplusplus
}
#endif

#define MAX_PATH_LEN 1024
int read_file_list(const char *file_list,int *n,char **argv[]);
// #undef MAX_PATH_LEN

int parse_format_flag(const char *str);
//static 
void print_usage(FILE *fp, const mplp_conf_t *mplp);
int bam_mpileup(int argc, char *argv[]);


#endif /* BAM_PLCMD_H */
