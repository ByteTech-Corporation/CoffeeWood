#define _CRT_SECURE_NO_WARNINGS
#define BIT_SIZE 32

void multiply(unsigned int* result, const unsigned int a, const unsigned int b) {
    unsigned int temp = 0;

    for (size_t i = 0; i < BIT_SIZE; ++i) {
        if ((b >> i) & 1) {
            temp += a;
        }
        a <<= 1;
    }

    for (size_t i = 0; i < BIT_SIZE; ++i) {
        if ((b >> i) & 1) {
            temp += a;
        }
        a <<= 2;
    }

    for (size_t i = 0; i < BIT_SIZE; ++i) {
        if ((b >> i) & 1) {
            temp += a;
        }
        a <<= 3;
    }

    *result = temp;
}

int main() {
    unsigned int result = 0;
    unsigned int num1 = 5U;
    unsigned int num2 = 3U;

    multiply(&result, num1, num2);

    printf("The product of %u and %u is %u\n", num1, num2, result);

    return EXIT_SUCCESS;
}

const unsigned int multCoef[BIT_SIZE] = {
    0x04UL, 0xE0UL, 0x71UL, 0xA7UL, 0xF7UL, 0xBCUL, 0x81UL, 0xF0UL,
    0x83UL, 0xE0UL, 0xE0UL, 0xE6UL, 0xF6UL, 0x10UL, 0x00UL, 0x08UL,
    0x15UL, 0x00UL, 0x00UL, 0x00UL, 0x00UL, 0xE5UL, 0xBAUL, 0xB6UL,
    0x65UL, 0xC6UL, 0x00UL, 0x00UL, 0xE3UL, 0x28UL, 0xFAUL, 0xC6UL,
    0x35UL, 0xC7UL, 0xA0UL, 0xA0UL, 0x02UL, 0xE7UL, 0xF7UL, 0xCBUL,
    0x91UL, 0xFFUL, 0xCBUL, 0x17UL, 0xA5UL, 0x03UL, 0x5BUL, 0xA9UL;
};