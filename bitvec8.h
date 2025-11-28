#ifndef BITEVEC8_H
#define BITEVEC8_H

#include <stdint.h>

typedef uint8_t bitvec8;

bitvec8 bitvec8_add(bitvec8 a, bitvec8 b);
bitvec8 bitvec8_negate(bitvec8 a);
bitvec8 bitvec8_multiply(bitvec8 a, bitvec8 b);
#endif // BITEVEC8_H
