#ifndef CARTRIDGE
#define CARTRIDGE

#include <vector>
#include <cstdint>
#include <string>

class Cartridge
{
    public:
        Cartridge();
        Cartridge(std::vector<uint8_t> data);
        void printROMData();
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
};

#endif