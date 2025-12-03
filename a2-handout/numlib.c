#include "numlib.h"
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

//Task 2.4
#include <math.h>

void skipspaces(FILE *f) {
  while (1) {
    int c = fgetc(f);
    if (!isspace(c)) {
      if (c != EOF) {
        ungetc(c, f);
      }
      return;
    }
  }
}

int read_uint_ascii(FILE *f, uint32_t *out) {
  int read = 0;
  uint32_t num = 0;

  while (1) {
    int c = fgetc(f);

    if (c >= '0' && c <= '9') {
      num = num * 10 + (c - '0');
    } else {
      if (c != EOF) {
        ungetc(c, f);
      }
      if (read == 0) {
        if (c == EOF) {
          return EOF;
        } else {
          return 1;
        }
      } else {
        *out = num;
        return 0;
      }
    }
    read++;
  }
}

//Task 2.4
int read_double_ascii(FILE *f, double *out) {
  int sign = 1;
  int c = fgetc(f);

  //Handle Sign
  if (c == '-') {
    sign = -1;
  } else {
    if (c != EOF) ungetc(c, f);
  }

  //Read Integer Part
  uint32_t integer_part;
  int res_int = read_uint_ascii(f, &integer_part);
  if (res_int == EOF) return EOF; //End of file
  if (res_int != 0) return 1;     //Parsing error

  //Read Decimal Point
  c = fgetc(f);
  if (c != '.') {
    return 1; 
  }

  //Read Fractional Part
  //We need to count how many characters we read to know the divisor, but read_uint_ascii doesn't tell us digits count.
  //So, we manually read digits for precision.
  
  double fractional_part = 0.0;
  double divisor = 10.0;
  
  while (1) {
    c = fgetc(f);
    if (isdigit(c)) {
      fractional_part += (c - '0') / divisor;
      divisor *= 10.0;
    } else {
      if (c != EOF) ungetc(c, f); // ut back non-digit (space, newline, etc)
      break;
    }
  }

  //Combine and Write Output
  *out = sign * (integer_part + fractional_part);
  return 0;
}

int read_uint_le(FILE *f, uint32_t *out) {
  int b0, b1, b2, b3;
  b0 = fgetc(f);

  if (b0 == EOF) {
    return EOF;
  }

  b1 = fgetc(f);
  b2 = fgetc(f);
  b3 = fgetc(f);

  if (b1 == EOF || b2 == EOF || b3 == EOF) {
    return 1;
  }

  *out =
    ((uint32_t)b0)
    | ((uint32_t)b1 << 8)
    | ((uint32_t)b2 << 16)
    | ((uint32_t)b3 << 24);
  return 0;
}

//Task 2.1
int read_uint_be(FILE *f, uint32_t *out) {
  int b0, b1, b2, b3;
  b0 = fgetc(f);

  if (b0 == EOF) {
    return EOF;
  }

  b1 = fgetc(f);
  b2 = fgetc(f);
  b3 = fgetc(f);

  if (b1 == EOF || b2 == EOF || b3 == EOF) {
    return 1;
  }

  //Combine bytes: b0 is most significant (<< 24), b3 is least significant (<< 0)
  *out =
    ((uint32_t)b0 << 24)
    | ((uint32_t)b1 << 16)
    | ((uint32_t)b2 << 8)
    | ((uint32_t)b3);
  return 0;
}

//Task 2.2
int read_double_bin(FILE *f, double *out) {
  //Try to read 1 element of size 'sizeof(double)' from file 'f' into 'out'
  if (fread(out, sizeof(double), 1, f) != 1) {
    return EOF; //Return EOF if we couldn't read a full double
  }
  return 0; //Success
}

int write_uint_ascii(FILE *f, uint32_t x) {
  if (fprintf(f, "%u", x) < 0) {
    return 1;
  } else {
    return 0;
  }
}

//Task 2.3
int write_double_ascii(FILE *f, double x) {
  //Use "%.6f" to print standard decimal notation with 6 decimal places.
  //fprintf returns a negative number if an error occurs.
  if (fprintf(f, "%.6f", x) < 0) {
    return 1;
  }
  return 0;
}

int write_uint_le(FILE *f, uint32_t x) {
  fputc(x>>0,  f);
  fputc(x>>8,  f);
  fputc(x>>16, f);
  fputc(x>>24, f);
  return 0;
}

//Task 2.1
int write_uint_be(FILE *f, uint32_t x) {
  fputc(x >> 24, f);
  fputc(x >> 16, f);
  fputc(x >> 8,  f);
  fputc(x >> 0,  f);
  return 0;
}

//Task 2.2
int write_double_bin(FILE *f, double x) {
  //Try to write 1 element of size 'sizeof(double)' from variable 'x' to file 'f'
  if (fwrite(&x, sizeof(double), 1, f) != 1) {
    return 1; //Error
  }
  return 0; //Success
}
