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
    printf("Testing bitvec8_add:\n");
    
    unsigned int test_cases[][2] = {
        {5, 3},
        {255, 1},
        {100, 50},
        {0, 0},
        {15, 1},
        {128, 128},
        {200, 100}
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        unsigned int x = test_cases[i][0];
        unsigned int y = test_cases[i][1];
        
        unsigned int our_result = bitvec8_to_int(
            bitvec8_add(bitvec8_from_int(x), bitvec8_from_int(y))
        );
        unsigned int expected = (x + y) & 0xFF;
        
        printf("%u + %u = %u (expected %u) %s\n",
            x, y, our_result, expected,
            our_result == expected ? "✓" : "✗ MISMATCH");
    }
    
    return 0;
}