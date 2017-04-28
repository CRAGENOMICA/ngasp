/*
 * mstatspop, Statistical Analysis using Multiple Populations for Genomic Data.
 */
/**
 *  \brief     zutil.h
 *  \details
 *  \author    Joan Jené
 *  \version   1.0
 *  \date      Oct 11, 2016
 *  \pre
 *  \bug
 *  \warning
 *  \copyright
 */

#ifndef ZUTIL_H
#define ZUTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <zlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK             0x4000
#define windowBits        15
#define ENABLE_ZLIB_GZIP  32
#define GZIP_ENCODING     16

#define CALL_ZLIB(x) {                                                  \
        int status;                                                     \
        status = x;                                                     \
        if (status < 0) {                                               \
            fprintf (stderr,                                            \
                     "%s:%d: %s returned a bad status of %d.\n",        \
                     __FILE__, __LINE__, #x, status);                   \
            exit (EXIT_FAILURE);                                        \
        }                                                               \
    }

    typedef struct {
        unsigned char in[CHUNK];
        unsigned char out[CHUNK];
        int bytes_read;
        unsigned have;
        unsigned pointer;
        z_stream strm;
        int first_time; /* 1:yes / 0:no */
        int file_compressed; /* 1:yes / 0:no */
        int reading; /* 1:reading / 0:writing */
    } SGZip;


    /**
     * This function itilializes the SGZip structure.
     * 
     * For example:
     * main() {
     *   SGZip input_gz;
     *   init_gzip_structure(&input_gz);
     *   input_gz.file_compressed = 0;
     * 
     * @param z is the SGZip structure to be initialized.
     */
    void init_gzip_structure(SGZip *z);
    
    /**
     * Use this function for getting characters from a file.
     * 
     * @param file_handle is the open file.
     * @param z is the initialized SGZip structure.
     * 
     * @return the character or -1 if the end of file is reached.
     */
    int fzgetc(FILE * file_handle, SGZip *z);

    /**
     * Use this function for writing strings to a file.
     * 
     * @param file_handle is the open file.
     * @param message is the string to be sent to the file.
     * @param z is the initialized SGZip structure.
     * 
     * @return 0 if OK.
     */
    int fzprintf(FILE * file_handle, const char *message, SGZip *z);
    
    /**
     * This function checks for the end of file.
     * 
     * @param file_handle is the open file.
     * @param z is the initialized SGZip structure.
     * 
     * @return 1 if the end of file is reached. Else 0.
     */
    int fzeof(FILE * file_handle, SGZip *z);
    
    /**
     * This function closes the file.
     * 
     * @param file_handle is the open file.
     * @param z is the initialized SGZip structure.
     */
    void fzclose(FILE * file_handle, SGZip *z);
    
    /**
     * This function compresses a block of data in memory to a file.
     * 
     * @param file_name is the output file name.
     * @param start_address is the starting position of the data in memory.
     * @param end_address is the ending position of the data in memory.
     * 
     * @return 0 if OK.
     */
    int memory_deflate(char *file_name, char *start_address, char *end_address);
    
    /**
     * This function uncompresses a disk file into new disk file.
     * 
     * @param compressed_file_name is the file name of the compressed input file.
     * @param uncompressed_file_name is the file name of the uncompressed output file.
     * 
     * @return 0 if OK. 
     */
    int uncompress_file(const char * compressed_file_name, const char * uncompressed_file_name);
    
    /**
     * 
     * @param uncompressed_file_name is the file name of the uncompressed input file.
     * @param compressed_file_name is the file name of the compressed output file.
     * 
     * @return  0 if OK.
     */
    int compress_file(const char * uncompressed_file_name, const char * compressed_file_name);
    
    /**
     * This function tests that two files: one compressed and the other not compressed
     * are equal.
     */
    int test(const char * uncompressed_file_name, const char * compressed_file_name);

#ifdef __cplusplus
}
#endif

#endif /* ZUTIL_H */
