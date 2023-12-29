#ifndef CARTRIDGE
#define CARTRIDGE

#include <vector>
#include <cstdint>
#include <string>
#include <limits>

class Cartridge
{
    public:
        Cartridge();
        Cartridge(std::vector<uint8_t> data);
        Cartridge(const std::string& filename);
        void printROMData(size_t start = 0, size_t end = std::numeric_limits<size_t>::max(), size_t bytesPerRow = 16);
    private:
        std::vector<uint8_t> romData;
        std::vector<uint8_t> entryPoint;
        std::vector<uint8_t> nintendoLogo;
        std::string title;
        uint32_t manufacturerCode;
        uint8_t cgbFlag;
        uint16_t newLicenseeCode;
        uint8_t sgbFlag;
        uint8_t cartridgeType;
        uint8_t romSize;
        uint8_t ramSize;
        uint8_t destinationCode;
        uint8_t oldLicenseeCode;
        uint8_t maskROMVersionNumber;
        uint8_t headerChecksum;
        uint16_t globalChecksum;
        std::vector<uint8_t> loadRom(const std::string& filename);
        void parseHeaderData();
};

#endif