#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int FileExists(const char* filename) {
    struct stat sb;
    return stat(filename, &sb) >= 0;
}

size_t ReadAllBytes(const char* filename, void* buffer, size_t size) {
    int fd = open(filename, O_RDONLY);
    ssize_t bytesRead;

    if (fd < 0) {
        perror("Error opening file");
        return 0;
    }

    bytesRead = read(fd, buffer, size);
    close(fd);

    if (bytesRead <= 0) {
        perror("Error reading file");
        return 0;
    }

    return bytesRead;
}

char** FindFilesRecursively(const char* startDir, const char* pattern) {
    DIR* dir;
    struct dirent* entry;
    size_t capacity = 64, length = 0;
    char** files = malloc(capacity * sizeof(char*));

    dir = opendir(startDir);
    if (!dir) {
        perror("Error opening directory");
        free(files);
        return NULL;
    }

    while ((entry = readdir(dir))) {
        char fullPath[PATH_MAX];
        snprintf(fullPath, PATH_MAX, "%s/%s", startDir, entry->d_name);

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (isdir(fullPath)) {
            files = realloc(files, (length + capacity) * sizeof(char*));
            files[length++] = FindFilesRecursively(fullPath, pattern);
        }
        else {
            size_t filenameLength = strlen(entry->d_name);
            size_t extensionLength = strlen(".cwpl");
            if (filenameLength > extensionLength && strcmp(entry->d_name + filenameLength - extensionLength, ".cwpl") == 0) {
                files = realloc(files, (length + 1) * sizeof(char*));
                files[length++] = strdup(fullPath);
            }
        }
    }

    closedir(dir);

    files = realloc(files, (length + 1) * sizeof(char*));
    files[length] = NULL;

    return files;
}

void ImportStatement(const char* statement) {
    size_t pos = 0;
    char packageName[256], zipFileName[512];
    memset(packageName, '\0', 256);
    memset(zipFileName, '\0', 512);

    // Parse the import statement: "import <package>.<zip_file>"
    while (isspace(statement[pos])) ++pos;
    memcpy(packageName, statement + pos, strcspn(statement + pos, ": ") - pos);
    pos += strcspn(statement + pos, ": ");

    memcpy(zipFileName, statement + pos, strcspn(statement + pos, "\n") - pos);

    XmlNode* packageRoot = ParsePackageXml(ReadAllBytes(packageName, nullptr, 0));
    if (!packageRoot) {
        printf("Warning: Invalid package %s\n", packageName);
        return;
    }

    const char* codeSrcPath = packageRoot->first_node("files")->value;
    char codeSrcFilename[256];
    strcpy(codeSrcFilename, codeSrcPath);
    size_t codeSrcPathLen = strlen(codeSrcFilename);

    if (codeSrcPathLen > 0 && codeSrcPath[codeSrcPathLen - 1] != '/') {
        codeSrcFilename[codeSrcPathLen] = '/';
        ++codeSrcPathLen;
    }

    strcat(codeSrcFilename, "/codesrc/");
    strcat(codeSrcFilename, packageName);
    strcat(codeSrcFilename, ".cwpl");

    if (!FileExists(codeSrcFilename)) {
        printf("Warning: Missing file %s\n", codeSrcFilename);
        return;
    }

    char* content = mmap(NULL, READ_SIZE, PROT_READ, MAP_PRIVATE, open(codeSrcFilename, O_RDONLY), 0);
    if (content == MAP_FAILED) {
        perror("mmap failed");
        return;
    }

    // Now process the content of the imported file
    Interpreter interp;
    interp.ExecuteCode(content);
    munmap(content, READ_SIZE);
}

#define XML_PARSE_NOBLANK_TEXT 1
#define XML_PARSE_COMPACT      1
#include <rapidxml.hpp>
using namespace rapidxml;

XmlNode* ParsePackageXml(const char* xmlData) {
    xmlChar* data = xmlStrdup((xmlChar*)xmlData);
    document doc;
    doc.parse<0>(reinterpret_cast<memoryBuffer*>(data));
    xmlFree(data);

    XmlNode* root = doc.first_node("cwpl_package");
    return root;
}