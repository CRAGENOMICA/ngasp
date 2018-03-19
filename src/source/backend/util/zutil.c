#include "zutil.h"

void init_gzip_structure(SGZip *z) {
  (*z).bytes_read = 0;
  (*z).have = 0;
  (*z).pointer = 0;
  (*z).first_time = 1;
  (*z).file_compressed = 1;
  (*z).strm.avail_out = CHUNK;
  (*z).reading = 1;
  (*z).strm.next_in = 0;
  (*z).strm.avail_in = 0;
  (*z).strm.total_in = 0;
  (*z).strm.next_out = 0;
  (*z).strm.avail_out = 0;
  (*z).strm.total_out = 0;
  (*z).strm.msg = 0;
  (*z).strm.state = 0;
  (*z).strm.zalloc = 0;
  (*z).strm.zfree = 0;
  (*z).strm.opaque = 0;
  (*z).strm.data_type = 0;
  (*z).strm.adler = 0;
  (*z).strm.reserved = 0;
}

/*
- initialize data (Only first call)
- read data
- uncompress a piece of data into a buffer
- return one char of the buffer
Next calls to this funcion:
- If there are chars inside the buffer, return one
- Else uncompress another piece of data
- But if there are not more piece of data to uncompress then read from file
 */
/* return unsigned char = int */
long int num_chars = 0;

int fzgetc(FILE * file_handle, SGZip *z) {
  int ret;

  (*z).reading = 1;
  if ((*z).file_compressed == 0) {
    /* The file is not compressed */
    ret = fgetc(file_handle);
    num_chars++;
  } else {
    /* The file is compressed */
    if ((*z).first_time == 1) {
      /* This is the first read of the input file. Let's initialize some variables */
      (*z).strm.zalloc = Z_NULL;
      (*z).strm.zfree = Z_NULL;
      (*z).strm.opaque = Z_NULL;
      (*z).strm.next_in = (*z).in;
      (*z).strm.avail_in = 0;

      CALL_ZLIB(inflateInit2(&((*z).strm), windowBits | ENABLE_ZLIB_GZIP));
    }

    if (((*z).have > 0) && ((*z).pointer < (*z).have)) {
      /* The buffer has uncompressed chars */
    } else {
      if (((*z).strm.avail_out == 0) && ((*z).first_time == 0)) {
        /* The buffer of uncompressed chars is empty but
           It exists read data that can be uncompressed */
      } else {
        /* The buffer of uncompressed chars is empty and
           It does not exist read data that could be uncompressed, so
           Read data from the compressed input file */
        (*z).strm.next_in = (*z).in;
        (*z).bytes_read = fread((*z).in, sizeof (unsigned char), sizeof ((*z).in), file_handle);
        (*z).strm.avail_in = (*z).bytes_read;
      }

      if ((*z).bytes_read > 0) {
        /* Uncompress the data */
        (*z).strm.avail_out = CHUNK;
        (*z).strm.next_out = (*z).out;
        CALL_ZLIB(inflate(&((*z).strm), Z_NO_FLUSH));
        (*z).have = CHUNK - (*z).strm.avail_out;
        (*z).first_time = 0;

        num_chars += (*z).have;
      }

      /* The next char to be returned will be the first one in the buffer */
      (*z).pointer = 0;
    }


    if ((*z).bytes_read == 0) {
      inflateEnd(& ((*z).strm));
      ret = -1;
    } else {
      /* Return the current char */
      ret = (*z).out[(*z).pointer];

      /* Increment the pointer for the next call to this function */
      (*z).pointer++;
    }
  }

  return ret;
}

int fzprintf(FILE * file_handle, const char *message, SGZip *z) {
  int ret = 0;

  (*z).reading = 0;
  if ((*z).file_compressed == 0) {
    /* The file is not compressed */
    ret = fprintf(file_handle, message);
  } else {
    /* if ((*z).first_time == 1) { */
    /* This is the first write of the output file. Let's initialize some variables */
    (*z).first_time = 0;
    (*z).strm.zalloc = Z_NULL;
    (*z).strm.zfree = Z_NULL;
    (*z).strm.opaque = Z_NULL;
    deflateInit2(&((*z).strm), Z_DEFAULT_COMPRESSION, Z_DEFLATED,
            windowBits | GZIP_ENCODING, 8,
            Z_DEFAULT_STRATEGY);
    /*}*/

    (*z).strm.next_in = (unsigned char *) message;
    (*z).strm.avail_in = strlen(message);
    do {
      (*z).strm.avail_out = CHUNK;
      (*z).strm.next_out = (*z).out;
      deflate(&((*z).strm), Z_FINISH);
      (*z).have = CHUNK - (*z).strm.avail_out;
      fwrite((*z).out, sizeof (char), (*z).have, file_handle);
    } while ((*z).strm.avail_out == 0);
  }
  return ret;
}

int fzeof(FILE * file_handle, SGZip *z) {
  int ret = feof(file_handle);

  if ((*z).file_compressed == 1) {
    if ((ret = ((ret) && /* Reached the end of the file and */
            ((*z).strm.avail_out != 0) && /* there is no more input data to uncompress and */
            ((*z).pointer >= (*z).have))) == 1) { /* there is no more chars in the buffer */
      inflateEnd(&((*z).strm));

      /* Initialize first time to true */
      (*z).first_time = 1;
    }
  }

  return ret;
}

void fzclose(FILE * file_handle, SGZip *z) {
  if (((*z).file_compressed == 0) || ((*z).reading == 1)) {
    fclose(file_handle);
  } else {
    deflateEnd(&((*z).strm));
  }
}

int memory_deflate(char *file_name, char *start_address, char *end_address) {
  int ret = 0;
  FILE *file_handle = NULL;

  if ((file_handle = fopen(file_name, "wb+")) != NULL) {
    SGZip z;
    z.first_time = 0;
    z.strm.zalloc = Z_NULL;
    z.strm.zfree = Z_NULL;
    z.strm.opaque = Z_NULL;
    deflateInit2(&(z.strm), Z_DEFAULT_COMPRESSION, Z_DEFLATED,
            windowBits | GZIP_ENCODING, 8,
            Z_DEFAULT_STRATEGY);


    z.strm.next_in = (unsigned char *) start_address;
    z.strm.avail_in = end_address - start_address;
    do {
      z.strm.avail_out = CHUNK;
      z.strm.next_out = z.out;
      deflate(&(z.strm), Z_FINISH);
      z.have = CHUNK - z.strm.avail_out;
      fwrite(z.out, sizeof (char), z.have, file_handle);
    } while (z.strm.avail_out == 0);
  } else {
    ret = 1;
  }

  return ret;
}

int uncompress_file(const char * compressed_file_name, const char * uncompressed_file_name) {
  int ret = 0;

  gzFile compressed_file;
  FILE * uncompressed_file;

  unsigned char buffer[CHUNK];

  compressed_file = gzopen(compressed_file_name, "rb");
  if (compressed_file != NULL) {
    uncompressed_file = fopen(uncompressed_file_name, "wb+");
    if (uncompressed_file != NULL) {
      //.................................................................
      int bytes_read;

      while (!gzeof(compressed_file)) {
        memset(buffer, '\x0', sizeof (buffer));
        bytes_read = gzread(compressed_file, buffer, CHUNK - 1);
        fwrite(buffer, sizeof (unsigned char), bytes_read, uncompressed_file);
      }

      //.................................................................
      fclose(uncompressed_file);
    } else {
      ret = 1;
    }

    gzclose(compressed_file);
  } else {
    ret = 1;
  }

  return ret;
}

int compress_file(const char * uncompressed_file_name, const char * compressed_file_name) {
  int ret = 0;

  FILE * uncompressed_file;
  gzFile compressed_file;

  char buffer[CHUNK];

  uncompressed_file = fopen(uncompressed_file_name, "rb");
  if (uncompressed_file != NULL) {
    compressed_file = gzopen(compressed_file_name, "wb");
    if (compressed_file != NULL) {
      //.................................................................
      while (!feof(uncompressed_file)) {
        unsigned int bytes_read = 0;
        memset(buffer, '\x0', sizeof (buffer));
        bytes_read = fread(buffer, sizeof (char), sizeof (buffer), uncompressed_file);

        if (bytes_read > 0) {
          gzwrite(compressed_file, buffer, strlen(buffer));
        }
      }
      //.................................................................
      gzclose(compressed_file);
    } else {
      ret = 1;
    }

    fclose(uncompressed_file);
  } else {
    ret = 1;
  }

  return ret;
}

int test(const char * uncompressed_file_name, const char * compressed_file_name) {
  int ret = 0;

  SGZip input_gz;
  init_gzip_structure(&input_gz);
  input_gz.file_compressed = 1;

  FILE *hn = fopen(uncompressed_file_name, "r");
  if (hn != NULL) {
    FILE *hz = fopen(compressed_file_name, "r");
    if (hz != NULL) {
      int cn;
      int cz;
      char ccn;
      char ccz;

      long int numchars = 0;
      while (!feof(hn)) {
        cn = fgetc(hn);
        cz = fzgetc(hz, &input_gz);
        ccn = (char) cn;
        ccz = (char) cz;
        if ((cn != cz) || (ccn != ccz)) {
          printf("KO.");
        }
        numchars++;
      }
      fzclose(hz, &input_gz);
    } else {
      ret = 1;
    }
    fclose(hn);
  } else {
    ret = 1;
  }

  return ret;
}
