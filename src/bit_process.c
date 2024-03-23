bool CheckIfStringStartsOrEndsWith(const char* str, const char* start, const char* end) {
    size_t len = strlen(str);
    size_t startLen = strlen(start);
    size_t endLen = strlen(end);

    if (len >= startLen && strncmp(str, start, startLen) == 0 ||
        len - startLen >= endLen && strncmp(&str[len - endLen], end, endLen) == 0) {
        return true;
    }
    return false;
}