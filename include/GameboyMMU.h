#ifndef GAMEBOY_MMU
#define GAMEBOY_MMU

#include <cstdint>
#include <vector>
#include <iostream>

#include "GameboyBus.h"
#include "Cartridge.h"

class GameboyMMU
{
    public:
        GameboyMMU(GameboyBus& bus);
        uint8_t read(uint16_t address);
        bool write(uint16_t address, uint8_t value);
        bool setCartridge(Cartridge* cart);
        std::vector<uint8_t> getData(size_t start = 0, size_t end = std::numeric_limits<size_t>::max());
    private:
        GameboyBus& bus;
        Cartridge* cart;
        std::vector<uint8_t> memory;
        void eraseMemory();
};

#endif