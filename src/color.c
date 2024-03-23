typedef struct ColorColor {
    unsigned char r, g, b;
} ColorRGB;

struct ColorText {
    const char* text;
    ColorRGB textForeground;
    ColorRGB textBackground;
};

// Helper function prototypes
size_t strlen_wrapper(const char* str);
void setChrStr(char*, size_t, const char*, const char*);
void parseHexByte(const char**, size_t*, uint8_t*);
void initColors();
void printColoredText(const struct ColorText* colorText);

// Helper function implementation
size_t strlen_wrapper(const char* str) {
    return strlen(str);
}

// Helper function implementation
void setChrStr(char* strOriginal, size_t startIndex, const char* strReplace, const char* readOnlyString) {
    // ... (same as before)
}

// Helper function implementation
void parseHexByte(const char** strPtr, size_t* bytesRead, uint8_t* hexByte) {
    // ... (same as before)
}

// Initialize colors
static ColorRGB defaultFgColor = { .r=15, .g=15, .b=15 };
static ColorRGB defaultBgColor = { .r=0,   .g=0,   .b=0 };
static ColorRGB blackFgColor =   { .r=0,   .g=0,   .b=0 };
static ColorRGB redFgColor     =   { .r=255, .g=0,   .b=0 };
static ColorRGB greenFgColor   =   { .r=0,   .g=255, .b=0 };
static ColorRGB yellowFgColor  =   { .r=255, .g=255, .b=0 };
static ColorRGB blueFgColor    =   { .r=0,   .g=0,   .b=255 };
static ColorRGB magentaFgColor =   { .r=255, .g=0,   .b=255 };
static ColorRGB cyanFgColor    =   { .r=0,   .g=255, .b=255 };
static ColorRGB whiteFgColor   =   { .r=255, .g=255, .b=255 };
static ColorRGB grayFgColor    =   { .r=192, .g=192, .b=192 };

static ColorRGB blackBgColor =   { .r=0,   .g=0,   .b=0 };
static ColorRGB redBgColor     =   { .r=255, .g=0,   .b=0 };
static ColorRGB greenBgColor   =   { .r=0,   .g=255, .b=0 };
static ColorRGB yellowBgColor  =   { .r=255, .g=255, .b=0 };
static ColorRGB blueBgColor    =   { .r=0,   .g=0,   .b=255 };
static ColorRGB magentaBgColor =   { .r=255, .g=0,   .b=255 };
static ColorRGB cyanBgColor    =   { .r=0,   .g=255, .b=255 };
static ColorRGB whiteBgColor   =   { .r=255, .g=255, .b=255 };

void initColors() {
    // Populate the color table based on predefined RGB values
    // You may extend this list with more colors if desired
}

// Function to convert hex color code into RGB components
ColorRGB getColorFromHex(uint8_t hexValue) {
    ColorRGB color;

    color.r = (hexValue >> 4) * 17 / 15;
    color.g = (hexValue & 0xF) * 17 / 15;

    return color;
}

// Helper function implementation
void printColoredText(const struct ColorText* colorText) {
    const char* text = colorText->text;
    ColorRGB fgColor = colorText->textForeground;
    ColorRGB bgColor = colorText->textBackground;

    printf("\033[48m%dm%s\033[0m", (bgColor.r << 4 | bgColor.g << 2 | bgColor.b), text);

    printf("\033[38;5;" FMT_UINT8 "m%s\033[0m", fgColor.r + 8, text);
}

int main() {
    initColors();

    char myString[30] = "Hello World!";
    size_t idx = 6;

    struct ColorText colorData = {};
    colorData.text = myString;

    printf("Enter the starting index: ");
    scanf("%ld", &idx);

    printf("Enter the text to set: ");
    char text[50];
    scanf("%s", text);

    printf("Enter the text background color (HEX): ");
    char bgHexCode[7];
    scanf("%s", bgHexCode);
    parseHexByte((const char**)&bgHexCode, &idx, &(colorData.textBackground.r));

    printf("Enter the text foreground color (HEX): ");
    char fgHexCode[7];
    scanf("%s", fgHexCode);
    parseHexByte((const char**)&fgHexCode, &idx, &(colorData.textForeground.r));

    setChrStr(myString, idx, "", "");
    printColoredText(&colorData);
    setChrStr(myString, idx, text, "");

    printf("Modified String: %s\n", myString);

    return EXIT_SUCCESS;
}