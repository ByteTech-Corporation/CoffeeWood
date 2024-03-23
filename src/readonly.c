#include <ctype.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function prototypes
size_t strlen_wrapper(const char* str);
void setChrStr(char*, size_t, const char*, const char*);
void parseHexByte(const char**, size_t*, uint8_t*);

// Helper function implementation
size_t strlen_wrapper(const char* str) {
    return strlen(str);
}

// Helper function implementation
void setChrStr(char* strOriginal, size_t startIndex, const char* strReplace, const char* readOnlyString) {
    size_t replaceLen = strlen(strReplace);
    size_t srcLength = strlen_wrapper(strOriginal);
    size_t destLength = srcLength + replaceLen;

    if (startIndex >= srcLength) {
        fprintf(stderr, "Invalid index! Index should be less than the string length.\n");
        return;
    }

    char* dest = malloc(destLength + 1);

    memmove(dest, strOriginal, startIndex);
    memmove(dest + startIndex, strReplace, replaceLen + 1);
    memmove(dest + startIndex + replaceLen, strOriginal + startIndex, srcLength - startIndex);

    free(strOriginal);
    strcpy(strOriginal, dest);
    free(dest);
}

// Updated setChrStr function implementation
void setChrStr(char* strOriginal, size_t startIndex, ...) {
    va_list args;
    const char* strReplace = NULL;
    const char* readOnlyString = NULL;

    va_start(args, startIndex);
    strReplace = va_arg(args, const char*);

    if (va_arg(args, int) == READONLY) {
        readOnlyString = va_arg(args, const char*);
    }

    setChrStr(strOriginal, startIndex, strReplace);

    if (readOnlyString) {
        size_t len = strlen(readOnlyString) + 1;
        char* readOnlyCopy = malloc(len);
        strcpy(readOnlyCopy, readOnlyString);
        strcat(strOriginal, readOnlyCopy);
        free(readOnlyCopy);
    }

    va_end(args);
}

int main() {
    char myString[30] = "Hello World!";
    size_t idx = 6;

    printf("Enter the starting index: ");
    scanf("%ld", &idx);

    printf("Enter the text to set: ");
    char text[50];
    scanf("%s", text);

    printf("Is the string supposed to be read-only after modification? (y/n): ");
    char readOnlyAnswer;
    scanf("%c", &readOnlyAnswer);

    setChrStr(myString, idx, text, readOnlyAnswer == 'y' ? "READONLY" : NULL);

    printf("Modified String: %s\n", myString);

    return EXIT_SUCCESS;
}

// Define a macro to simplify the use of the readonly wrapper
#define readonly(str, idx, text) setCharStr(str, idx, text, #text)

int main() {
    char myString[30] = "Hello World!";
    size_t idx = 6;

    readonly(myString, idx, "PUT YOUR TEXT HERE");

    printf("Modified String: %s\n", myString);

    return EXIT_SUCCESS;
}