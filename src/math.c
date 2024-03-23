#include "math.h"

void math_add(int num_1, int num_2, int* result) {
    *result = num_1 + num_2;
}

void math_subtract(int num_1, int num_2, int* difference) {
    *difference = num_1 - num_2;
}

void math_multiply(int num_1, int num_2, int* product) {
    *product = num_1 * num_2;
}

void math_divide(int num_1, int num_2, float* quotient) {
    *quotient = (float) num_1 / num_2;
}