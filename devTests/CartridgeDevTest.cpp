#include <iostream>
#include <fstream>
#include "../include/Cartridge.h"

std::vector<uint8_t> loadRom(const std::string& filename)
{
    // Open the ROM file
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open ROM file.");
    }

    // Determine the size of the file
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read the file into a buffer
    std::vector<uint8_t> buffer(size);
    file.read(reinterpret_cast<char*>(buffer.data()), size);

    // Close the file
    file.close();

    return buffer;
}

int main()
{
    std::vector<uint8_t> romData = loadRom("roms/tet.gb");
    std::cout << "ROM Loaded" << std::endl;
    Cartridge cart(romData);
    cart.printROMData();
    return 0;
}