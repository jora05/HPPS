#include <stdint.h>

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
    carry = (old_sum & carry) << 1;
    
    // Iteration 2
    old_sum = sum;
    sum = sum ^ carry;
    carry = (old_sum & carry) << 1;
    
    // Iteration 3
    old_sum = sum;
    sum = sum ^ carry;
    carry = (old_sum & carry) << 1;
    
    // Iteration 4
    old_sum = sum;
    sum = sum ^ carry;
    carry = (old_sum & carry) << 1;
    
    // Iteration 5
    old_sum = sum;
    sum = sum ^ carry;
    carry = (old_sum & carry) << 1;
    
    // Iteration 6
    old_sum = sum;
    sum = sum ^ carry;
    carry = (old_sum & carry) << 1;
    
    // Iteration 7
    old_sum = sum;
    sum = sum ^ carry;
    carry = (old_sum & carry) << 1;
    
    // Iteration 8
    old_sum = sum;
    sum = sum ^ carry;
    carry = (old_sum & carry) << 1;
    
    return sum;
}
// Negation using two's complement: flip bits and add 1
bitvec8 bitvec8_negate(bitvec8 x) {
    bitvec8 notted = ~x;           // Flip all bits (bitwise NOT)
    bitvec8 one = 1;               // Constant 1
    return bitvec8_add(notted, one);  // Add 1 to get two's complement negation
}

// Multiplication
bitvec8 bitvec8_mul(bitvec8 x, bitvec8 y) {
    bitvec8 product = 0;
    
    // For each bit position i in y (0 to 7)
    // If bit i of y is 1, add x shifted left by i to the product
    
    // Bit 0
    if ((y & (1 << 0)) != 0) {
        product = bitvec8_add(product, x << 0);
    }
    
    // Bit 1
    if ((y & (1 << 1)) != 0) {
        product = bitvec8_add(product, x << 1);
    }
    
    // Bit 2
    if ((y & (1 << 2)) != 0) {
        product = bitvec8_add(product, x << 2);
    }
    
    // Bit 3
    if ((y & (1 << 3)) != 0) {
        product = bitvec8_add(product, x << 3);
    }
    
    // Bit 4
    if ((y & (1 << 4)) != 0) {
        product = bitvec8_add(product, x << 4);
    }
    
    // Bit 5
    if ((y & (1 << 5)) != 0) {
        product = bitvec8_add(product, x << 5);
    }
    
    // Bit 6
    if ((y & (1 << 6)) != 0) {
        product = bitvec8_add(product, x << 6);
    }
    
    // Bit 7
    if ((y & (1 << 7)) != 0) {
        product = bitvec8_add(product, x << 7);
    }
    
    return product;
}

// Test helper functions
bitvec8 bitvec8_from_int(unsigned int x) {
    return (bitvec8)(x & 0xFF);
}

unsigned int bitvec8_to_int(bitvec8 x) {
    return (unsigned int)x;
}

// Test
#include <stdio.h>

int main() {
    printf("Testing bitvec8_mul:\n");
    
    unsigned int test_cases[][2] = {
        {5, 3},
        {0, 10},
        {1, 255},
        {15, 15},
        {16, 16},
        {255, 255},
        {7, 8},
        {10, 20}
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        unsigned int x = test_cases[i][0];
        unsigned int y = test_cases[i][1];
        
        unsigned int our_result = bitvec8_to_int(
            bitvec8_mul(bitvec8_from_int(x), bitvec8_from_int(y))
        );
        unsigned int expected = (x * y) & 0xFF;
        
        printf("%u * %u = %u (expected %u) %s\n",
            x, y, our_result, expected,
            our_result == expected ? "✓" : "✗ MISMATCH");
    }
    
    return 0;
}