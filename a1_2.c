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

bitvec8 bitvec8_negate(bitvec8 x) {
    bitvec8 notted = ~x;           // Flip all bits (bitwise NOT)
    bitvec8 one = 1;               // Constant 1
    return bitvec8_add(notted, one);  // Add 1 to get two's complement negation
}

// Test helper functions
bitvec8 bitvec8_from_int(int x) {
    return (bitvec8)(x & 0xFF);
}

int bitvec8_to_int(bitvec8 x) {
    // Convert from unsigned to signed (two's complement interpretation)
    if (x & 0x80) {
        // Negative number: convert from two's complement
        return -((int)(~x & 0xFF) + 1);
    } else {
        // Positive number
        return (int)x;
    }
}

// Test
#include <stdio.h>

int main() {
    printf("Testing bitvec8_negate:\n");
    
    int test_cases[] = {1, -1, 5, -5, 0, 127, -128, 100, -100};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int x = test_cases[i];
        bitvec8 bv = bitvec8_from_int(x);
        bitvec8 negated = bitvec8_negate(bv);
        int result = bitvec8_to_int(negated);
        int expected = -x;
        
        printf("negate(%d) = %d (expected %d) %s\n",
            x, result, expected,
            result == expected ? "✓" : "✗ MISMATCH");
    }
    
    return 0;
}

//Then negate(-128) will wrap around to -128, which is correct in 8-bit arithmetic.