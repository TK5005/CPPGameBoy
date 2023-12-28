#include <iostream>

#include "GameboyMMU.h"

GameboyMMU::GameboyMMU(GameboyBus& bus) : bus(bus)
{
    std::cout << "Gameboy MMU Created" << std::endl;
}

uint8_t GameboyMMU::read(uint16_t address)
{
    return 0;
}

void GameboyMMU::write(uint16_t address, uint8_t value)
{

}