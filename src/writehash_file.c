#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <stdlib.h>

int main() {
    unsigned char originalData[100]; // Change size according to your needs
    unsigned char calculatedMd5[MD5_DIGEST_LENGTH];
    unsigned char calculatedOtherHash[SHA256_DIGEST_SIZE]; // Change the digest size accordingly
    FILE *file;

    memcpy(originalData, "Your Data", sizeof("Your Data")); // Set your actual data here

    MD5((unsigned char *)originalData, strlen("Your Data"), calculatedMd5);

    const char *expectedMd5 = "Expected MD5 Hash";
    int md5Match = memcmp(calculatedMd5, (unsigned char*)expectedMd5, MD5_DIGEST_ Length);

    if (!md5Match) {
        puts("MD5 checksum matched.");
        // Generate other hash
        SHA256((unsigned char *)originalData, strlen("Your Data"), calculatedOtherHash);
        
        // Write hash results and input data to hash_result.txt
        file = fopen("hash_result.txt", "w+b");
        fprintf(file, "Input Data : ");
        fwrite(originalData, sizeof(originalData), 1, file);
        fseek(file, SEEK_CUR, sizeof(originalData));
        fprintf(file, "\nMD5 Hash  : ");
        fwrite(calculatedMd5, MD5_DIGEST_LENGTH, 1, file);
        fseek(file, SEEK_CUR, sizeof(calculatedMd5));
        fprintf(file, "\nOther Hash: ");
        fwrite(calculatedOtherHash, SHA256_DIGEST_SIZE, 1, file);
        fclose(file);

        printf("Writing hash and input data to hash_result.txt.\n");
    } else {
        puts("MD5 checksum did not match.");
    }

    return 0;
}

// Previous printHexDigest() implementation remains the same
