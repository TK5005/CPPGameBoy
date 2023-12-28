#ifndef GAMEBOY_MMU
#define GAMEBOY_MMU

#include <cstdint>

#include "GameboyBus.h"

class GameboyMMU
{
    public:
        GameboyMMU(GameboyBus& bus);
        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);
    private:
        GameboyBus& bus;
};

#endif