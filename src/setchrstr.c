// Helper function prototypes
void setChrStr(char*, size_t, const char*, const char*);
void parseHexByte(const char**, size_t*, uint8_t*);

// Helper function implementation
void parseHexByte(const char** strPtr, size_t* bytesRead, uint8_t* hexByte) {
    size_t numBytes = 1;
    uint8_t b;

    *bytesRead = 0;

    // Parse the first hex digit
    sscanf(*strPtr++, "%2hhx%n", &b, bytesRead);

    // Ensure only one valid hex digit was parsed
    if ((*strPtr != ' ') && (*strPtr != '\0')) {
        // Invalid hex format, bail out
        fprintf(stderr, "Invalid hex format: Expected single hex byte but got '%.*s'\n", (int)*bytesRead, *strPtr);
        *hexByte = 0xFF;
        return;
    }

    *hexByte = b;
}

// Updated setChrStr function implementation
void setChrStr(char* strOriginal, size_t startIndex, ...) {
    va_list args;
    const char* strReplace = NULL;

    va_start(args, startIndex);
    strReplace = va_arg(args, const char*);

    size_t replaceLen = strlen(strReplace);
    size_t srcLength = strlen(strOriginal);

    if (startIndex >= srcLength) {
        fprintf(stderr, "Invalid index! Index should be less than the string length.\n");
        return;
    }

    // Replace the byte at the specified index with the hex byte
    uint8_t hexByte;
    size_t bytesParsed;
    parseHexByte(&(argv[0]), &bytesParsed, &hexByte);
    strOriginal[startIndex] = hexByte;

    memcpy(strOriginal + startIndex + 1, strReplace, replaceLen + 1);

    va_end(args);
}

int main() {
    char myString[30] = "Hello World!";
    size_t idx = 6;

    printf("Enter the hex byte value: ");
    char hexInput[3];
    scanf("%2s", hexInput);

    printf("Enter the starting index: ");
    scanf("%ld", &idx);

    setChrStr(myString, idx, "Hi There!", hexInput);

    printf("Modified String: %s\n", myString);

    return EXIT_SUCCESS;
}