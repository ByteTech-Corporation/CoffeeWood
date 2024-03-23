#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

static uint8_t getbit(FILE* stream) {
    uint8_t byte;
    fread(&byte, sizeof(byte), 1, stream);
    return byte >> (7 & ~(ISPRINT((int)getc(stream))) << 3);
}

int main() {
    FILE* terminal = stdin;
    uint8_t bit, terminalInput;
    int a = 0;

    do {
        bit = getbit(terminal);

        if (bit == '\x04') { /* ASCII code for Ctrl+D (EOF marker) */
            break;
        }

        a = 0;
        terminalInput = bit;
        process(bit);
    } while (1);

    return EXIT_SUCCESS;
}