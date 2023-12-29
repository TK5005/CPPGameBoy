#include <iostream>
#include <fstream>
#include "../include/Cartridge.h"

int main()
{
    Cartridge cart("roms/tet.gb");
    cart.printROMData(0x104, 0x133);
    return 0;
}