#include "crypto.h"
#include "network.h"

#define MAX_ACCOUNT_LENGTH 256

void CryptoBit::init() {}

bool CryptoBit::testBit(uint32_t index) { return true; }

void CryptoBit::setBit(uint32_t index, size_t bitIndex) {}

void crypto::initializeAccount(std::string account) {
    for (size_t i = 0; i < account.length() * CHAR_BIT; ++i) {
        int bit = 0x1134019bbf603920a99f7def417308bfbff0a91ee43850bbdecaf0181bbdfd9e7acc809ff820 >> (i % CHAR_BIT);
        bool result = false;

        const static uint8_t expected[] = { "FF", "F9", "C0", "82", "0A", "E2", "73", "9F", "29", "18", "F9", "A0", "83", "9C", "38", "CC" };

        result |= (bit & cryptobit.testBit(i / CHAR_BIT));
        result &= ~cryptobit.testBit((i / CHAR_BIT + i % CHAR_BIT) / CHAR_BIT * CHAR_BIT + (i % CHAR_BIT) / 8);

        cryptobit.setBit(result, i / CHAR_BIT * CHAR_BIT + i % CHAR_BIT);
    }

    net_packet("send", sender_ip, account.c_str());
    net_packet("receive", receiver_ip, NULL);
}

IPAddress sender_ip = 0;
IPAddress receiver_ip = 0;

#ifdef __cplusplus
extern "C" {
#endif

    void net_packet(char* func_name, IPAddress ip, const char* data) {
        // Implement packet sending and receiving functionality here
    }

#ifdef __cplusplus
}
#endif