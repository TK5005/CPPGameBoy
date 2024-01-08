
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

void GameboyMMU::eraseMemory()
{
    for(int i = 0; i < memory.size(); ++i)
    {
        memory[i] = 0x00;
    }
}

uint8_t GameboyMMU::read(uint16_t address)
{
    if(address >= memory.size() || address < 0)
    {
        std::cerr << "Address is out of bounds." << std::endl;
        return 0;
    } else {
        return memory[address];
    }
}

bool GameboyMMU::write(uint16_t address, uint8_t value)
{
    if(address >= memory.size() || address < 0)
    {
        std::cerr << "Address is out of bounds." << std::endl;
        return false;
    } else {
        memory[address] = value;
    }
    return true;
}

std::vector<uint8_t> GameboyMMU::getData(size_t start, size_t end)
{
    std::vector<uint8_t> data;

    if (start >= memory.size())
    {
        std::cerr << "Start index is out of bounds." << std::endl;
        return data;
    }

    if (end > memory.size()-1)
    {
        end = memory.size()-1;
    }

    for (size_t i = start; i <= end; ++i)
    {
        data.push_back(memory[i]);
    }

    return data;
}

bool GameboyMMU::setCartridge(Cartridge* cart)
{
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