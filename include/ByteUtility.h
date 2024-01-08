#ifndef BYTE_HELPER
#define BYTE_HELPER

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <vector>

class ByteUtility
{
    public:
        static void printByte(uint8_t byte);
        static void printData(std::vector<uint8_t> data, size_t bytesPerRow = 16);
};

#endif