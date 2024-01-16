
#include <iomanip>
#include "GameboyMMU.h"

/*
Start   End     Description                     Notes
0000	3FFF	16 KiB ROM bank 00	            From cartridge, usually a fixed bank
4000	7FFF	16 KiB ROM Bank 01~NN	        From cartridge, switchable bank via mapper (if any)
8000	9FFF	8 KiB Video RAM (VRAM)	        In CGB mode, switchable bank 0/1
A000	BFFF	8 KiB External RAM	            From cartridge, switchable bank if any
C000	CFFF	4 KiB Work RAM (WRAM)	
D000	DFFF	4 KiB Work RAM (WRAM)	        In CGB mode, switchable bank 1~7
E000	FDFF	Mirror of C000~DDFF (ECHO RAM)	Nintendo says use of this area is prohibited.
FE00	FE9F	Object attribute memory (OAM)	
FEA0	FEFF	Not Usable	                    Nintendo says use of this area is prohibited
FF00	FF7F	I/O Registers	
FF80	FFFE	High RAM (HRAM)	
FFFF	FFFF	Interrupt Enable register (IE)
*/

GameboyMMU::GameboyMMU(GameboyBus& bus) : bus(bus), memory(65536)
{
    std::cout << "Gameboy MMU Created" << std::endl;
    std::cout << "Memory Size: " << memory.size() << std::endl;
    eraseMemory();
    bus.setMMU(this);
}

bool GameboyMMU::write(uint16_t address, uint8_t data)
{
    if (address >= memory.size())
    {
        std::cerr << "Address is out of bounds." << std::endl;
        return false;
    }

    memory[address] = data;

    // If address is in the range of C000 - DDFF, write to E000 - FDFF as well
    if (address >= 0xC000 && address <= 0xDDFF)
    {
        memory[address + 0x2000] = data;
        return true;
    }

    // If address is in the range of E000 - FDFF, write to C000 - DDFF as well
    if (address >= 0xE000 && address <= 0xFDFF)
    {
        memory[address - 0x2000] = data;
        return true;
    }

    return true;
}

uint8_t GameboyMMU::read(uint16_t address)
{
    if (address >= memory.size())
    {
        std::cerr << "Address is out of bounds." << std::endl;
        return 0x00;
    }

    return memory[address];
}

void GameboyMMU::eraseMemory()
{
    for (size_t i = 0; i < memory.size(); ++i)
    {
        memory[i] = 0x00;
    }
}

std::vector<uint8_t> GameboyMMU::getData(size_t start, size_t end)
{
    try
    {
        // Check bounds
        memory.at(start);
        if (end >= memory.size())
        {
            end = memory.size() - 1;
        }
        memory.at(end);

        // Create data vector and insert range from memory
        std::vector<uint8_t> data;
        data.insert(data.end(), memory.begin() + start, memory.begin() + end + 1);

        return data;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Index is out of bounds: " << e.what() << std::endl;
        return std::vector<uint8_t>();
    }
}

bool GameboyMMU::setCartridge(Cartridge* cart)
{
    if (cart == nullptr)
    {
        std::cerr << "Invalid cartridge." << std::endl;
        return false;
    }

    this->cart = cart;
    std::cout << "Loading cartridge " << cart->getTitle() << " into memory management unit." << std::endl;

    std::vector<uint8_t> romData = cart->getROMData();
    uint16_t address = 0x0000;  

    for (uint8_t i : romData)
    {
        write(address, i);
        address ++;
    }

    return true;
}