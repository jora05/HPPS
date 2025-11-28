#include <stdint.h>
#include "bitvec8.h"

typedef uint8_t bitvec8;

struct add_result {
    bitvec8 s;  // partial sum
    bitvec8 c;  // carry (shifted left by 1)
};

// Modified half-adder: computes partial sum and repositioned carry
struct add_result sum_and_carry(bitvec8 x, bitvec8 y) {
    struct add_result result;
    result.s = x ^ y;           // Partial sum using XOR
    result.c = (x & y) << 1;    // Carry using AND, shifted left by 1
    return result;
}

bitvec8 bitvec8_add(bitvec8 x, bitvec8 y) {
    struct add_result r = sum_and_carry(x, y);
    bitvec8 sum = r.s;
    bitvec8 carry = r.c;
    
    // Ripple iterations
    // Iteration 1
    bitvec8 old_sum = sum;
    sum = sum ^ carry;
    carry = ((old_sum & carry) << 1) & 0xFF;
    
    // Iteration 2
    old_sum = sum;
    sum = sum ^ carry;
    carry = ((old_sum & carry) << 1) & 0xFF;
    
    // Iteration 3
    old_sum = sum;
    sum = sum ^ carry;
    carry = ((old_sum & carry) << 1) & 0xFF;
    
    // Iteration 4
    old_sum = sum;
    sum = sum ^ carry;
    carry = ((old_sum & carry) << 1) & 0xFF;
    
    // Iteration 5
    old_sum = sum;
    sum = sum ^ carry;
    carry = ((old_sum & carry) << 1) & 0xFF;
    
    // Iteration 6
    old_sum = sum;
    sum = sum ^ carry;
    carry = ((old_sum & carry) << 1) & 0xFF;
    
    // Iteration 7
    old_sum = sum;
    sum = sum ^ carry;
    carry = ((old_sum & carry) << 1) & 0xFF;
    
    return sum & 0xFF;
}


bitvec8 bitvec8_negate(bitvec8 x) {
    // Step 1: Flip all bits using XOR with 0xFF (all 1s)
    bitvec8 flipped = x ^ 0xFF;
    
    // Step 2: Increment by 1 using bitvec8_add
    bitvec8 negated = bitvec8_add(flipped, 1);
    
    // Ensure result is masked to 8 bits
    return negated & 0xFF;
}

bitvec8 bitvec8_multiply(bitvec8 x, bitvec8 y) {
    bitvec8 product = 0;
    
    // We will use x as the multiplicand (shifted left) and y as the multiplier (shifted right).
    
    // 1. Get the LSB of the multiplier y
    bitvec8 bit0 = y & 1;
    // 2. Create the mask: 0x00 if bit is 0, 0xFF if bit is 1.
    // Negate(0) = 0x00. Negate(1) = 0xFF (two's complement -1).
    bitvec8 mask0 = bitvec8_negate(bit0);
    // 3. Conditional value to add: x if bit is 1, 0 if bit is 0.
    bitvec8 add_val0 = mask0 & x;
    // 4. Add to the product
    product = bitvec8_add(product, add_val0);
    // 5. Prepare for next iteration: shift multiplicand x left, shift multiplier y right
    x = x << 1;
    y = y >> 1;
    
    bitvec8 bit1 = y & 1;
    bitvec8 mask1 = bitvec8_negate(bit1);
    bitvec8 add_val1 = mask1 & x;
    product = bitvec8_add(product, add_val1);
    x = x << 1;
    y = y >> 1;
    
    bitvec8 bit2 = y & 1;
    bitvec8 mask2 = bitvec8_negate(bit2);
    bitvec8 add_val2 = mask2 & x;
    product = bitvec8_add(product, add_val2);
    x = x << 1;
    y = y >> 1;
    
    bitvec8 bit3 = y & 1;
    bitvec8 mask3 = bitvec8_negate(bit3);
    bitvec8 add_val3 = mask3 & x;
    product = bitvec8_add(product, add_val3);
    x = x << 1;
    y = y >> 1;
    
    bitvec8 bit4 = y & 1;
    bitvec8 mask4 = bitvec8_negate(bit4);
    bitvec8 add_val4 = mask4 & x;
    product = bitvec8_add(product, add_val4);
    x = x << 1;
    y = y >> 1;
    
    bitvec8 bit5 = y & 1;
    bitvec8 mask5 = bitvec8_negate(bit5);
    bitvec8 add_val5 = mask5 & x;
    product = bitvec8_add(product, add_val5);
    x = x << 1;
    y = y >> 1;
    
    bitvec8 bit6 = y & 1;
    bitvec8 mask6 = bitvec8_negate(bit6);
    bitvec8 add_val6 = mask6 & x;
    product = bitvec8_add(product, add_val6);
    x = x << 1;
    y = y >> 1;
    
    bitvec8 bit7 = y & 1;
    bitvec8 mask7 = bitvec8_negate(bit7);
    bitvec8 add_val7 = mask7 & x;
    product = bitvec8_add(product, add_val7);
    
    return product&0xFF;
}


