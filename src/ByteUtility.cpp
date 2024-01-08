#include "ByteUtility.h"

void ByteUtility::printByte(uint8_t byte)
{
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << std::dec;
}

void ByteUtility::printData(std::vector<uint8_t> data, size_t bytesPerRow)
{
    int i = 0;
    for (auto byte : data)
    {
        ByteUtility::printByte(data[i]);
        std::cout << " ";
        if ((i + 1) % bytesPerRow == 0)
        {
            std::cout << std::endl;
        }
        i++;
    }
}