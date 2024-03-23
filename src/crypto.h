#ifndef CRYPTO_H
#define CRYPTO_H

#include <iostream>
#include <string>

class CryptoBit {
public:
    void init();
    bool testBit(uint32_t index);
    void setBit(uint32_t index, size_t bitIndex);
};

class crypto {
private:
    CryptoBit cryptobit;
public:
    crypto() : cryptobit{}

    void initializeAccount(std::string account);
};

extern void net_packet(char*, IPAddress, const char*);

#endif // CRYPTO_H