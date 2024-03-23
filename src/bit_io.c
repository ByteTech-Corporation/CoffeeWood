#define _CRT_SECURE_NO_WARNINGS
#define RESULT_LENGTH 16

typedef struct {
    uint16_t result[RESULT_LENGTH];
    uint16_t bit;
} BufferObject;

BufferObject bufferObj;

void multiply(uint16_t a, uint16_t b, uint16_t* result) {
    memset(bufferObj.result, 0, RESULT_LENGTH * sizeof(uint16_t));

    bufferObj.bit = a;
    for (size_t j = 0; j < RESULT_LENGTH; ++j) {
        for (size_t k = 0; k < BIT_SIZE; ++k) {
            if ((b >> k) & 1) {
                bufferObj.result[j] += bufferObj.bit;
            }
            bufferObj.bit <<= 1;
        }
    }

    *result = bufferObj.result[0];
}

void printResults(const uint16_t* results, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("%d ", results[i]);
    }
    printf("\n");
}

int main() {
    uint16_t num1 = 1011;       // Decimal value derived from binary number '111101101110'
    uint16_t num2 = 0xBEE;      // Hexadecimal value 'BE' converted to binary string '1011111011' followed by '11101110'
    uint16_t result;

    const char* binaryString = "11101110110110011101110011011101 111101101110110111110111 111111011111110111111111 111111101111111011111101 111111111111111111111111 011101100111011001110110 011101110111011101110111 011111001111110011111100";

    // Split binary string into two parts: dividend and divisor
    char divider[3][BIT_SIZE / 2 + 1];
    sscanf(binaryString, "%s%s", divider[0], divider[1]);

    // Parse binary strings to their decimal representation
    uint16_t dividend = strtoul(divider[0], NULL, 2);
    uint16_t divisor = strtoul(divider[1], NULL, 2);

    multiply(dividend, divisor, &result);

    printf("The product of %hu and %hX is %hu\n", dividend, divisor, result);

    printResults(bufferObj.result, RESULT_LENGTH);

    return EXIT_SUCCESS;
}