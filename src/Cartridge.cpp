#include "Cartridge.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>

Cartridge::Cartridge()
{
    std::cout << "Creating cartridge without data" << std::endl;
}

Cartridge::Cartridge(std::vector<uint8_t> data) : romData(data)
{
    std::cout << "Creating cartridge with data" << std::endl;
}

Cartridge::Cartridge(const std::string& filename)
{
    std::cout << "Creating cartridge from filename" << std::endl;
    romData = loadRom(filename);
}

std::vector<uint8_t> Cartridge::loadRom(const std::string& filename)
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

void Cartridge::printROMData(size_t start, size_t end, size_t bytesPerRow)
{
    if (start >= romData.size())
    {
        std::cerr << "Start index is out of bounds." << std::endl;
        return;
    }

    if (end > romData.size())
    {
        end = romData.size();
    }

    for (size_t i = start; i <= end; ++i)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(romData[i]) << " ";
        if ((i - start + 1) % bytesPerRow == 0)
        {
            std::cout << std::endl;
        }
    }

    std::cout << std::dec << std::endl; // Switch back to decimal for any future output
}