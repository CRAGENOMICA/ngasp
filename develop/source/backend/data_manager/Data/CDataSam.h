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
 *  \brief     CDataSam.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      April 25, 2016
 *  \pre
 *  \bug
 *  \warning
 */

#ifndef DATA_MANAGER_DATA_CDATASAM_H_
#define	DATA_MANAGER_DATA_CDATASAM_H_

#include <string>
#include <string.h>  // memset

#include "../IDataValue.h"

//#include "../../../../contrib/htslib/htslib-1.3.1/install/include/htslib/sam.h"
//#include "../../../../contrib/htslib/htslib-1.3.1/install/include/htslib/cram.h"

#include <htslib/sam.h>
#include <htslib/faidx.h>
#include <htslib/kstring.h>
#include <htslib/khash.h>

/*
 * Example file:
@SQ	SN:c1	LN:10
s0a	0	c1	1	0	10M	*	0	0	AACCGCGGTT	**********
s0A	0	c1	1	0	3M4N3M	*	0	0	AACGTT	******
s0b	0	c1	2	0	1S8M1S	*	0	0	AACCGCGGTT	**********
s0B	0	c1	2	0	1H8M1H	*	0	0	ACCGCGGT	********
s0c	0	c1	3	0	2S6M2S	*	0	0	AACCGCGGTT	**********
s0c	0	c1	3	0	2S3M2I3M2S	*	0	0	AACCGNNCGGTT	************
s0C	0	c1	3	0	2H6M2H	*	0	0	CCGCGG	****** 
 */
class CDataSam : public IDataValue<std::string> {
 public:
  void set_value_string(std::string value) {
    set_value(value);
  } 
// public:
//  enum SamType {
//    SAM   = 1,  // S
//    BAM   = 2,  // b
//    D     = 4,  // D
//    CRAM  = 8   // C
//  };
//  
//  samFile *file_;
//  bam_hdr_t *header_;
//  SamType file_type_;
//  bool ignore_sam_error_;
  
 public:
  CDataSam() : IDataValue(KeyString::DATA_SAM, "") {
//    file_             = NULL;
//    header_           = NULL;
//    file_type_        = SamType::SAM;
//    ignore_sam_error_ = true;
  }
  
  virtual ~CDataSam() {}

  IData * clone() const { return new CDataSam(); /*clone*/ }
  
  // gcc -Isamtools -Ihtslib -Lsamtools -Lhtslib biostar151053.c htslib/libhts.a samtools/libbam.a -lz -lpthread
  // -L/home/jjene/NetBeansProjects/ngasp/contrib/htslib/htslib-1.3.1/install/lib -l:libhts.a -lz -lpthread
  
//  int f(void) {
//    std::string bam_file_name;
//    std::string region;
//    bam_file_name = "/home/jjene/NetBeansProjects/ngasp/contrib/htslib/htslib-1.3.1/test/xx#large_aux.sam";
//            
//    hts_itr_t *iter = NULL;
//    hts_idx_t *idx = NULL;
//    samFile *in = NULL;
//    bam1_t *b = NULL;
//    bam_hdr_t *header = NULL;
//
//    in = sam_open(bam_file_name.c_str(), "r");
//    if (in != NULL) {
//      if ((header = sam_hdr_read(in)) != 0) {
//        
//        bam1_t *aln = bam_init1();
//        uint8_t *p;
//        if (sam_read1(in, header, aln) >= 0) {
//          p = bam_aux_get(aln, "XA");
//        }
//        
//        idx = sam_index_load(in, bam_file_name.c_str());
//        if (idx != NULL) {
//          iter = sam_itr_querys(idx, header, region.c_str());
//          if (iter != NULL) {
//            b = bam_init1();
//            while (sam_itr_next(in, iter, b) >= 0) {
//              fputs("DO STUFF\n", stdout);
//            }
//            hts_itr_destroy(iter);
//            bam_destroy1(b);
//          }
//        }
//        bam_hdr_destroy(header);
//      }
//      
//      sam_close(in);
//    }
//    
//    return 0;
//  }    

  
//
//  
//  /**
//   * Usage: samview [-bSCSIB] [-N num_reads] [-l level] [-o option=value] [-Z hdr_nuls] <in.bam>|<in.sam>|<in.cram> [region]
//   * @return 
//   */
//  int Open(void) {
//    std::string sam_file = "/home/jjene/NetBeansProjects/ngasp/contrib/htslib/htslib-1.3.1/test/c1#clip.sam";
//    file_type_ |= SamType::SAM;
//    
//    
//    char *fn_ref = 0;
//    int flag = 0, c, clevel = -1, ignore_sam_err = 0;
//    char moder[8];
//    bam1_t *b;
//    htsFile *out;
//    char modew[800];
//    int r = 0, exit_code = 0;
//    hts_opt *in_opts = NULL, *out_opts = NULL;
//    int num_reads = 0;
//    int extra_hdr_nuls = 0;
//    int benchmark = 0;
//
//    
//    while ((c = getopt(argc, argv, "IbDCSl:t:i:o:N:BZ:")) >= 0) {
//        switch (c) {
//
//        case 'B': benchmark = 1; break;
//        case 'l': clevel = atoi(optarg); flag |= 2; break;
//        case 't': fn_ref = optarg; break;
//
//        case 'i': if (hts_opt_add(&in_opts,  optarg)) return 1; break;
//        case 'o': if (hts_opt_add(&out_opts, optarg)) return 1; break;
//
//        case 'Z': extra_hdr_nuls = atoi(optarg); break;
//        }
//    }
//    
//    strcpy(moder, "r");
//    if (flag&4) strcat(moder, "c");
//    else if ((flag&1) == 0) strcat(moder, "b");
//
//    file_ = sam_open(argv[optind], moder);
//    if (file_ == NULL) {
//        // Error opening file
//        return EXIT_FAILURE;
//    }
//    
//    header_ = sam_hdr_read(file_);
//    if (header_ == NULL) {
//        // Couldn't read header
//        return EXIT_FAILURE;
//    }
//    
//    header_->ignore_sam_err = (ignore_sam_error_)?1:0;
//    
//    if (extra_hdr_nuls) {
//        char *new_text = realloc(h->text, h->l_text + extra_hdr_nuls);
//        if (new_text == NULL) {
//            // Error reallocing header text
//            return EXIT_FAILURE;
//        }
//        header_->text = new_text;
//        memset(&header_->text[header_->l_text], 0, extra_hdr_nuls);
//        header_->l_text += extra_hdr_nuls;
//    }
//
////    b = bam_init1();
////
////    strcpy(modew, "w");
////    if (clevel >= 0 && clevel <= 9) sprintf(modew + 1, "%d", clevel);
////    if (flag&8) strcat(modew, "c");
////    else if (flag&2) strcat(modew, "b");
////    out = hts_open("-", modew);
////    if (out == NULL) {
////        fprintf(stderr, "Error opening standard output\n");
////        return EXIT_FAILURE;
////    }
////
////    /* CRAM output */
////    if (flag & 8) {
////        int ret;
////
////        // Parse input header and use for CRAM output
////        out->fp.cram->header = sam_hdr_parse_(h->text, h->l_text);
////
////        // Create CRAM references arrays
////        if (fn_ref)
////            ret = cram_set_option(out->fp.cram, CRAM_OPT_REFERENCE, fn_ref);
////        else
////            // Attempt to fill out a cram->refs[] array from @SQ headers
////            ret = cram_set_option(out->fp.cram, CRAM_OPT_REFERENCE, NULL);
////
////        if (ret != 0)
////            return EXIT_FAILURE;
////    }
////
////    // Process any options; currently cram only.
////    if (hts_opt_apply(file_, in_opts))
////        return EXIT_FAILURE;
////    hts_opt_free(in_opts);
////
////    if (hts_opt_apply(out, out_opts))
////        return EXIT_FAILURE;
////    hts_opt_free(out_opts);
////
////    if (!benchmark && sam_hdr_write(out, h) < 0) {
////        fprintf(stderr, "Error writing output header.\n");
////        exit_code = 1;
////    }
////    if (optind + 1 < argc && !(flag&1)) { // BAM input and has a region
////        int i;
////        hts_idx_t *idx;
////        if ((idx = sam_index_load(file_, argv[optind])) == 0) {
////            fprintf(stderr, "[E::%s] fail to load the BAM index\n", __func__);
////            return 1;
////        }
////        for (i = optind + 1; i < argc; ++i) {
////            hts_itr_t *iter;
////            if ((iter = sam_itr_querys(idx, h, argv[i])) == 0) {
////                fprintf(stderr, "[E::%s] fail to parse region '%s'\n", __func__, argv[i]);
////                continue;
////            }
////            while ((r = sam_itr_next(file_, iter, b)) >= 0) {
////                if (!benchmark && sam_write1(out, h, b) < 0) {
////                    fprintf(stderr, "Error writing output.\n");
////                    exit_code = 1;
////                    break;
////                }
////                if (num_reads && --num_reads == 0)
////                    break;
////            }
////            hts_itr_destroy(iter);
////        }
////        hts_idx_destroy(idx);
////    } else while ((r = sam_read1(file_, h, b)) >= 0) {
////        if (!benchmark && sam_write1(out, h, b) < 0) {
////            fprintf(stderr, "Error writing output.\n");
////            exit_code = 1;
////            break;
////        }
////        if (num_reads && --num_reads == 0)
////            break;
////    }
////
////    if (r < -1) {
////        fprintf(stderr, "Error parsing input.\n");
////        exit_code = 1;
////    }
////
////    r = sam_close(out);
////    if (r < 0) {
////        fprintf(stderr, "Error closing output.\n");
////        exit_code = 1;
////    }
////
////    bam_destroy1(b);
////    bam_hdr_destroy(h);
//
//    r = sam_close(file_);
//    if (r < 0) {
//        fprintf(stderr, "Error closing input.\n");
//        exit_code = 1;
//    }
//
//    return exit_code;
//  }
};

#endif  // DATA_MANAGER_DATA_CDATASAM_H_
