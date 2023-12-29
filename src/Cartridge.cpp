#include "Cartridge.h"
#include <iostream>

Cartridge::Cartridge()
{
    std::cout << "Creating cartridge without data" << std::endl;
}

Cartridge::Cartridge(std::vector<uint8_t> data)
{
    std::cout << "Creating cartridge with data" << std::endl;
}

void Cartridge::printROMData()
{
    std::cout << "Printing ROM Data" << std::endl;
}