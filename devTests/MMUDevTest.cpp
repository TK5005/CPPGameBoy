#include "../include/GameboyMMU.h"
#include "../include/GameboyBus.h"
#include "../include/ByteUtility.h"

int main()
{
    GameboyBus bus;
    GameboyMMU mmu(bus);

    Cartridge cart("../roms/tet.gb");
    mmu.setCartridge(&cart);

    uint8_t data = mmu.read(0x0000);

    ByteUtility::printByte(data);
    std::cout << std::endl;
    std::cout << std::endl;
    std::vector<uint8_t> d = mmu.getData(0x00, 0xFF);
    ByteUtility::printData(d);

    return 0;
}