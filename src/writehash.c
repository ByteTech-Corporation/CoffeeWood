#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

int main() {
    unsigned char originalData[100]; // Change size according to your needs
    unsigned char calculatedMd5[MD5_DIGEST_LENGTH];
    unsigned char calculatedOtherHash[SHA256_DIGEST_SIZE]; // Change the digest size accordingly

    memcpy(originalData, "Your Data", sizeof("Your Data")); // Set your actual data here

    MD5((unsigned char *)originalData, strlen("Your Data"), calculatedMd5);

    const char *expectedMd5 = "Expected MD5 Hash";
    int md5Match = memcmp(calculatedMd5, (unsigned char*)expectedMd5, MD5_DIGEST_LENGTH);

    if (!md5Match) {
        puts("MD5 checksum matched.");
        // Generate other hash
        SHA256((unsigned char *)originalData, strlen("Your Data"), calculatedOtherHash);
        printf("Generating other hash:\n");
        printHexDigest(calculatedOtherHash, SHA256_DIGEST_SIZE);
    } else {
        puts("MD5 checksum did not match.");
    }

    return 0;
}

void printHexDigest(const unsigned char* buffer, size_t length) {
    int i;
    for (i = 0; i < length; ++i) {
        printf("%02x", buffer[i]);
    }
    putchar('\n');
}
