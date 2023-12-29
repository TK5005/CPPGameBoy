#include "Cartridge.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>

Cartridge::Cartridge()
{
    std::cout << "Creating cartridge without data" << std::endl;
    std::cout << "Empty Cartridge Created" << std::endl;
}

Cartridge::Cartridge(std::vector<uint8_t> data) : romData(data)
{
    std::cout << "Creating cartridge with data" << std::endl;
    // TODO: Check to see if romData is valid
    std::cout << "ROM data loaded" << std::endl;
    parseHeaderData();
    std::cout << "Cartridge Created" << std::endl;
}

Cartridge::Cartridge(const std::string& filename)
{
    std::cout << "Creating cartridge from filename" << std::endl;
    romData = loadRom(filename);
    // TODO: Check to see if romData is valid
    std::cout << "ROM data loaded" << std::endl;
    parseHeaderData();
    printCartridgeData();
    std::cout << "Cartridge Created" << std::endl;
}

void Cartridge::parseHeaderData()
{
    std::cout << "Parsing Header Data" << std::endl;
    entryPoint = getROMData(0x100, 0x103);
    nintendoLogo = getROMData(0x104, 0x133);
    std::vector<uint8_t> titleData = getROMData(0x134, 0x143);
    title = std::string(titleData.begin(), titleData.end()+1);
    manufacturerCode = getROMData(0x13F, 0x142);
    cgbFlag = getROMData(0x143, 0x143)[0];
    newLicenseeCode = getROMData(0x144, 0x145);
    sgbFlag = getROMData(0x146, 0x146)[0];
    cartridgeType = static_cast<CartridgeType>(getROMData(0x147, 0x147)[0]);
    romSize = static_cast<ROMSize>(getROMData(0x148, 0x148)[0]);
    ramSize = static_cast<RAMSize>(getROMData(0x149, 0x149)[0]);
    destinationCode = static_cast<DestinationCode>(getROMData(0x14A, 0x14A)[0]);
    oldLicenseeCode = static_cast<OldLicenseeCode>(getROMData(0x14B, 0x14B)[0]);
    maskROMVersionNumber = getROMData(0x14C, 0x14C)[0];
    headerChecksum = getROMData(0x14D, 0x14D)[0];
    globalChecksum = getROMData(0x14E, 0x14F);
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

std::vector<uint8_t> Cartridge::getROMData(size_t start, size_t end)
{
    std::vector<uint8_t> data;

    if (start >= romData.size())
    {
        std::cerr << "Start index is out of bounds." << std::endl;
        return data;
    }

    if (end > romData.size())
    {
        end = romData.size();
    }

    for (size_t i = start; i <= end; ++i)
    {
        data.push_back(romData[i]);
    }

    return data;
}

void Cartridge::printROMData(std::vector<uint8_t> data, size_t bytesPerRow)
{
    int i = 0;
    for (auto byte : data)
    {
        printByte(data[i]);
        std::cout << " ";
        if ((i + 1) % bytesPerRow == 0)
        {
            std::cout << std::endl;
        }
        i++;
    }
}

bool Cartridge::passesHeaderChecksum()
{
    uint8_t checksum = 0;
    for (uint16_t address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - getROMData(address, address)[0] - 1;
    }
    return checksum == headerChecksum;
}

void Cartridge::printByte(uint8_t byte)
{
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << std::dec;
}

std::string cartridgeTypeToString(CartridgeType type)
{
    switch (type) {
        case ROM_ONLY: return "ROM_ONLY";
        case MBC1: return "MBC1";
        case MBC1_RAM: return "MBC1+RAM";
        case MBC1_RAM_BATTERY: return "MBC1+RAM+BATTERY";
        case MBC2: return "MBC2";
        case MBC2_BATTERY: return "MBC2+BATTERY";
        case ROM_RAM_1: return "ROM+RAM 1";
        case ROM_RAM_BATTERY_1: return "ROM+RAM+BATTERY 1";
        case MMM01: return "MMM01";
        case MMM01_RAM: return "MMM01+RAM";
        case MMM01_RAM_BATTERY: return "MMM01+RAM+BATTERY";
        case MBC3_TIMER_BATTERY: return "MBC3+TIMER+BATTERY";
        case MBC3_TIMER_RAM_BATTERY_2: return "MBC3+TIMER+RAM+BATTERY 2";
        case MBC3: return "MBC3";
        case MBC3_RAM_2: return "MBC3+RAM 2";
        case MBC3_RAM_BATTERY_2: return "MBC3+RAM+BATTERY 2";
        case MBC5: return "MBC5";
        case MBC5_RAM: return "MBC5+RAM";
        case MBC5_RAM_BATTERY: return "MBC5+RAM+BATTERY";
        case MBC5_RUMBLE: return "MBC5+RUMBLE";
        case MBC5_RUMBLE_RAM: return "MBC5+RUMBLE+RAM";
        case MBC5_RUMBLE_RAM_BATTERY: return "MBC5+RUMBLE+RAM+BATTERY";
        case MBC6: return "MBC6";
        case MBC7_SENSOR_RUMBLE_RAM_BATTERY: return "MBC7+SENSOR+RUMBLE+RAM+BATTERY";
        case POCKET_CAMERA: return "POCKET CAMERA";
        case BANDAI_TAMA5: return "BANDAI TAMA5";
        case HuC3: return "HuC3";
        case HuC1_RAM_BATTERY: return "HuC1+RAM+BATTERY";
        default: return "Unknown";
    }
}

std::string romSizeToString(ROMSize size) {
    switch (size) {
        case SIZE_32_KB: return "32 KiB (no banking)";
        case SIZE_64_KB: return "64 KiB (4 banks)";
        case SIZE_128_KB: return "128 KiB (8 banks)";
        case SIZE_256_KB: return "256 KiB (16 banks)";
        case SIZE_512_KB: return "512 KiB (32 banks)";
        case SIZE_1_MB: return "1 MiB (64 banks)";
        case SIZE_2_MB: return "2 MiB (128 banks)";
        case SIZE_4_MB: return "4 MiB (256 banks)";
        case SIZE_8_MB: return "8 MiB (512 banks)";
        case SIZE_1_1_MB: return "1.1 MiB (72 banks)";
        case SIZE_1_2_MB: return "1.2 MiB (80 banks)";
        case SIZE_1_5_MB: return "1.5 MiB (96 banks)";
        default: return "Unknown size";
    }
}

std::string ramSizeToString(RAMSize size) {
    switch (size) {
        case NO_RAM: return "No RAM";
        case RAM_2_KB: return "Unused";
        case RAM_8_KB: return "8 KiB (1 bank)";
        case RAM_32_KB: return "32 KiB (4 banks of 8 KiB each)";
        case RAM_128_KB: return "128 KiB (16 banks of 8 KiB each)";
        case RAM_64_KB: return "64 KiB (8 banks of 8 KiB each)";
        default: return "Unknown RAM size";
    }
}

std::string destinationCodeToString(DestinationCode code) {
    switch (code) {
        case JAPAN: return "Japan (and possibly overseas)";
        case OVERSEAS_ONLY: return "Overseas only";
        default: return "Unknown";
    }
}

std::string oldLicenseeCodeToString(OldLicenseeCode code) {
    switch (code) {
        case NONE: return "NONE";
        case NINTENDO: return "Nintendo";
        case CAPCOM: return "CAPCOM";
        case HOT_B: return "HOT B";
        case JALECO: return "JALECO";
        case COCONUTS_JAPAN: return "COCONUTS JAPAN";
        case ELITE_SYSTEMS: return "ELITE SYSTEMS";
        case EA_ELECTRONIC_ARTS: return "EA ELECTRONIC ARTS";
        case HUDSONSOFT: return "HUDSONSOFT";
        case ITC_ENTERTAINMENT: return "ITC ENTERTAINMENT";
        case YANOMAN: return "YANOMAN";
        case JAPAN_CLARY: return "JAPAN CLARY";
        case VIRGIN_INTERACTIVE: return "VIRGIN INTERACTIVE";
        case PCM_COMPLETE: return "PCM COMPLETE";
        case SAN_X: return "SAN X";
        case KOTOBUKI_SYSTEMS: return "KOTOBUKI SYSTEMS";
        case SETA: return "SETA";
        case INFOGRAMES: return "INFOGRAMES";
        case NINTENDO_2: return "NINTENDO 2";
        case BANDAI: return "BANDAI";
        case USE_NEW_LICENSEE_CODE: return "USE NEW LICENSEE CODE";
        case KONAMI: return "KONAMI";
        case HECTORSOFT: return "HECTORSOFT";
        case CAPCOM_2: return "CAPCOM 2";
        case BANPRESTO: return "BANPRESTO";
        case ENTERTAINMENT_I: return "ENTERTAINMENT I";
        case GREMLIN: return "GREMLIN";
        case UBISOFT: return "UBISOFT";
        case ATLUS: return "ATLUS";
        case MALIBU: return "MALIBU";
        case ANGEL: return "ANGEL";
        case SPECTRUM_HOLOBY: return "SPECTRUM HOLOBY";
        case IREM: return "IREM";
        case VIRGIN_INTERACTIVE_2: return "VIRGIN INTERACTIVE 2";
        case MALIBU_2: return "MALIBU 2";
        case US_GOLD: return "US GOLD";
        case ABSOLUTE: return "ABSOLUTE";
        case ACCLAIM: return "ACCLAIM";
        case ACTIVISION: return "ACTIVISION";
        case AMERICAN_SAMMY: return "AMERICAN SAMMY";
        case GAMETEK: return "GAMETEK";
        case PARK_PLACE: return "PARK PLACE";
        case LJN: return "LJN";
        case MATCHBOX: return "MATCHBOX";
        case MILTON_BRADLEY: return "MILTON BRADLEY";
        case MINDSCAPE: return "MINDSCAPE";
        case ROMSTAR: return "ROMSTAR";
        case NAXAT_SOFT: return "NAXAT SOFT";
        case TRADEWEST: return "TRADEWEST";
        case TITUS: return "TITUS";
        case VIRGIN_INTERACTIVE_3: return "VIRGIN INTERACTIVE 3";
        case OCEAN_INTERACTIVE: return "OCEAN INTERACTIVE";
        case EA_ELECTRONIC_ARTS_2: return "EA ELECTRONIC ARTS 2";
        case ELITE_SYSTEMS_2: return "ELITE SYSTEMS 2";
        case ELECTRO_BRAIN: return "ELECTRO BRAIN";
        case INFOGRAMES_2: return "INFOGRAMES 2";
        case INTERPLAY: return "INTERPLAY";
        case BRODERBUND: return "BRODERBUND";
        case SCULPTERED_SOFT: return "SCULPTERED SOFT";
        case THE_SALES_CURVE: return "THE SALES CURVE";
        case THQ: return "THQ";
        case ACCOLADE: return "ACCOLADE";
        case TRIFFIX_ENTERTAINMENT: return "TRIFFIX ENTERTAINMENT";
        case MICROPROSE: return "MICROPROSE";
        case KEMCO: return "KEMCO";
        case MISAWA_ENTERTAINMENT: return "MISAWA ENTERTAINMENT";
        case LOZC: return "LOZC";
        case TOKUMA_SHOTEN_INTERMEDIA: return "TOKUMA SHOTEN INTERMEDIA";
        case BULLET_PROOF_SOFTWARE: return "BULLET PROOF SOFTWARE";
        case VIC_TOKAI: return "VIC TOKAI";
        case APE: return "APE";
        case IMAX: return "IMAX";
        case CHUNSOFT_CO: return "CHUNSOFT CO";
        case VIDEO_SYSTEM: return "VIDEO SYSTEM";
        case TSUBARAYA_PRODUCTIONS_CO: return "TSUBARAYA PRODUCTIONS CO";
        case VARIE_CORPORATION: return "VARIE CORPORATION";
        case YONEZAWA_SPAL: return "YONEZAWA SPAL";
        case KANEKO: return "KANEKO";
        case ARC: return "ARC";
        case NIHON_BUSSAN: return "NIHON BUSSAN";
        case TECMO: return "TECMO";
        case IMAGINEER: return "IMAGINEER";
        case BANPRESTO_2: return "BANPRESTO 2";
        case NOVA: return "NOVA";
        case HORI_ELECTRIC: return "HORI ELECTRIC";
        case BANDAI_2: return "BANDAI 2";
        case KONAMI_2: return "KONAMI 2";
        case KAWADA: return "KAWADA";
        case TAKARA: return "TAKARA";
        case TECHNOS_JAPAN: return "TECHNOS JAPAN";
        case BRODERBUND_2: return "BRODERBUND 2";
        case TOEI_ANIMATION: return "TOEI ANIMATION";
        case TOHO: return "TOHO";
        case NAMCO: return "NAMCO";
        case ACCLAIM_2: return "ACCLAIM 2";
        case ASCII_OR_NEXSOFT: return "ASCII OR NEXSOFT";
        case BANDAI_3: return "BANDAI 3";
        case SQUARE_ENIX: return "SQUARE ENIX";
        case HAL_LABORATORY: return "HAL LABORATORY";
        case SNK: return "SNK";
        case PONY_CANYON: return "PONY CANYON";
        case CULTURE_BRAIN: return "CULTURE BRAIN";
        case SUNSOFT: return "SUNSOFT";
        case SONY_IMAGESOFT: return "SONY IMAGESOFT";
        case SAMMY: return "SAMMY";
        case TAITO: return "TAITO";
        case KEMCO_2: return "KEMCO 2";
        case SQUARESOFT: return "SQUARESOFT";
        case TOKUMA_SHOTEN_INTERMEDIA_2: return "TOKUMA SHOTEN INTERMEDIA 2";
        case DATA_EAST: return "DATA EAST";
        case TONKINHOUSE: return "TONKINHOUSE";
        case KOEI: return "KOEI";
        case UFL: return "UFL";
        case ULTRA: return "ULTRA";
        case VAP: return "VAP";
        case USE_CORPORATION: return "USE CORPORATION";
        case MELDAC: return "MELDAC";
        case PONY_CANYON_OR: return "PONY CANYON OR";
        case ANGEL_2: return "ANGEL 2";
        case TAITO_2: return "TAITO 2";
        case SOFEL: return "SOFEL";
        case QUEST: return "QUEST";
        case SIGMA_ENTERPRISES: return "SIGMA ENTERPRISES";
        case ASK_KODANSHA_CO: return "ASK KODANSHA CO";
        case NAXAT_SOFT_2: return "NAXAT SOFT 2";
        case COPYA_SYSTEM: return "COPYA SYSTEM";
        case BANPRESTO_3: return "BANPRESTO 3";
        case TOMY: return "TOMY";
        case LJN_2: return "LJN 2";
        case NCS: return "NCS";
        case HUMAN: return "HUMAN";
        case ALTRON: return "ALTRON";
        case JALECO_2: return "JALECO 2";
        case TOWA_CHIKI: return "TOWA CHIKI";
        case YUTAKA: return "YUTAKA";
        case VARIE: return "VARIE";
        case EPCOH: return "EPCOH";
        case ATHENA: return "ATHENA";
        case ASMIK_ACE_ENTERTAINMENT: return "ASMIK ACE ENTERTAINMENT";
        case NATSUME: return "NATSUME";
        case KING_RECORDS: return "KING RECORDS";
        case ATLUS_2: return "ATLUS 2";
        case EPIC_OR_SONY_RECORDS: return "EPIC OR SONY RECORDS";
        case IGS: return "IGS";
        case A_WAVE: return "A WAVE";
        case EXTREME_ENTERTAINMENT: return "EXTREME ENTERTAINMENT";
        case LJN_3: return "LJN 3";
        default: return "Unknown Licensee";
    }
}

void Cartridge::printCartridgeData()
{
    std::cout << "Entry Point: ";
    printROMData(entryPoint);
    std::cout << std::endl;
    std::cout << "Nintendo Logo:" << std::endl;
    printROMData(nintendoLogo);
    std::cout << "Title: " << title << std::endl;
    std::cout << "Manufacturer Code: ";
    printROMData(manufacturerCode);
    std::cout << std::endl;
    std::cout << "CGB Flag: ";
    printByte(cgbFlag);
    std::cout << std::endl;
    std::cout << "New Licensee Code: ";
    printROMData(newLicenseeCode);
    std::cout << std::endl;
    std::cout << "SGB Flag: ";
    printByte(sgbFlag);
    std::cout << std::endl;
    std::cout << "Cartridge Type: " << cartridgeTypeToString(cartridgeType) << std::endl;
    std::cout << "ROM Size: " << romSizeToString(romSize) << std::endl;
    std::cout << "RAM Size: " << ramSizeToString(ramSize) << std::endl;
    std::cout << "Destination Code: " << destinationCodeToString(destinationCode) << std::endl;
    std::cout << "Old Licensee Code: " << oldLicenseeCodeToString(oldLicenseeCode) << std::endl;
    std::cout << "Mask ROM version number: ";
    printByte(maskROMVersionNumber);
    std::cout << std::endl;
    std::cout << "Header Checksum: ";
    printByte(headerChecksum);
    std::cout << std::endl;
    std::cout << "Global Checksum: ";
    printROMData(globalChecksum);
    std::cout << std::endl;
    if(passesHeaderChecksum())
    {
        std::cout << "Header Checksum passed" << std::endl;
    } else {
        std::cout << "Header Checksum failed" << std::endl;
    }
}