#include "bitvec8.h"
#include <stdio.h>
#include <stdint.h>
typedef uint8_t bitvec8;

// helpers
bitvec8 bitvec8_from_int(int x) { return (bitvec8)(x & 0xFF); }
int bitvec8_to_int(bitvec8 x) {
    if (x & 0x80) return -((int)(~x & 0xFF) + 1);
    else return (int)x;
}

int main(void) {
    printf("Testing bitvec8_add:\n");
    unsigned int add_cases[][2] = {
        {5,3}, {255,1}, {100,50}, {0,0}, {15,1}, {128,128}, {200,100}
    };
    int add_tests = sizeof(add_cases)/sizeof(add_cases[0]);
    for(int i=0;i<add_tests;i++){
        unsigned int x=add_cases[i][0], y=add_cases[i][1];
        unsigned int r = (unsigned int)bitvec8_add(bitvec8_from_int(x), bitvec8_from_int(y));
        unsigned int e = (x+y)&0xFF;
        printf("%u + %u = %u (expected %u) %s\n",x,y,r,e,r==e?"✓":"✗");
    }
    
    printf("\nTesting bitvec8_negate:\n");
    unsigned int neg_cases[] = {1,255,5,251,0,127,128,100,156};
    int neg_tests = sizeof(neg_cases)/sizeof(neg_cases[0]);
    for(int i=0;i<neg_tests;i++){
        unsigned int x=neg_cases[i];
        unsigned int r = (unsigned int)bitvec8_negate(bitvec8_from_int(x));
        unsigned int e = (256-x)&0xFF;
        printf("negate(%u) = %u (expected %u) %s\n",x,r,e,r==e?"✓":"✗");
    }
    
    printf("\nTesting bitvec8_mul:\n");
    unsigned int mul_cases[][2] = {
        {5,3},{0,10},{1,255},{15,15},{16,16},{255,255},{7,8},{10,20}
    };
    int mul_tests = sizeof(mul_cases)/sizeof(mul_cases[0]);
    for(int i=0;i<mul_tests;i++){
        unsigned int x=mul_cases[i][0], y=mul_cases[i][1];
        unsigned int r = (unsigned int)bitvec8_multiply(bitvec8_from_int(x), bitvec8_from_int(y));
        unsigned int e = (x*y)&0xFF;
        printf("%u * %u = %u (expected %u) %s\n",x,y,r,e,r==e?"✓":"✗");
    }
    
    return 0;
}
