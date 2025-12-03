#include <stdio.h>
#include <stdlib.h>
#include "numlib.h"

//Task 2.5
int main(void) {
    double sum = 0.0;
    double current_val;
    long count = 0;

    while (read_double_bin(stdin, &current_val) != EOF) {
        sum += current_val;
        count++;
    }

    //Calculate average
    double average;
    if (count > 0) {
        average = sum / count;
    } else {
        average = 0.0; //Handle empty input 
    }

    //Print the result as ASCII followed by a newline
    if (write_double_ascii(stdout, average) != 0) {
        return 1; //Error writing output
    }
    printf("\n");

    return 0;
}