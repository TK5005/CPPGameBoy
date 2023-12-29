#ifndef CARTRIDGE
#define CARTRIDGE

#include <vector>
#include <cstdint>
#include <string>
#include <limits>

enum CartridgeType : uint8_t
{
    ROM_ONLY = 0x00,
    MBC1 = 0x01,
    MBC1_RAM = 0x02,
    MBC1_RAM_BATTERY = 0x03,
    MBC2 = 0x05,
    MBC2_BATTERY = 0x06,
    ROM_RAM_1 = 0x08,
    ROM_RAM_BATTERY_1 = 0x09,
    MMM01 = 0x0B,
    MMM01_RAM = 0x0C,
    MMM01_RAM_BATTERY = 0x0D,
    MBC3_TIMER_BATTERY = 0x0F,
    MBC3_TIMER_RAM_BATTERY_2 = 0x10,
    MBC3 = 0x11,
    MBC3_RAM_2 = 0x12,
    MBC3_RAM_BATTERY_2 = 0x13,
    MBC5 = 0x19,
    MBC5_RAM = 0x1A,
    MBC5_RAM_BATTERY = 0x1B,
    MBC5_RUMBLE = 0x1C,
    MBC5_RUMBLE_RAM = 0x1D,
    MBC5_RUMBLE_RAM_BATTERY = 0x1E,
    MBC6 = 0x20,
    MBC7_SENSOR_RUMBLE_RAM_BATTERY = 0x22,
    POCKET_CAMERA = 0xFC,
    BANDAI_TAMA5 = 0xFD,
    HuC3 = 0xFE,
    HuC1_RAM_BATTERY = 0xFF
};

enum ROMSize : uint8_t
{
    SIZE_32_KB = 0x00,
    SIZE_64_KB = 0x01,
    SIZE_128_KB = 0x02,
    SIZE_256_KB = 0x03,
    SIZE_512_KB = 0x04,
    SIZE_1_MB = 0x05,
    SIZE_2_MB = 0x06,
    SIZE_4_MB = 0x07,
    SIZE_8_MB = 0x08,
    SIZE_1_1_MB = 0x52,
    SIZE_1_2_MB = 0x53,
    SIZE_1_5_MB = 0x54
};

enum RAMSize : uint8_t
{
    NO_RAM = 0x00,
    RAM_2_KB = 0x01,
    RAM_8_KB = 0x02,
    RAM_32_KB = 0x03,
    RAM_128_KB = 0x04,
    RAM_64_KB = 0x05
};

enum DestinationCode : uint8_t
{
    JAPAN = 0x00,
    OVERSEAS_ONLY = 0x01
};

enum OldLicenseeCode : uint8_t
{
    NONE = 0x00,
    NINTENDO = 0x01,
    CAPCOM = 0x08,
    HOT_B = 0x09,
    JALECO = 0x0A,
    COCONUTS_JAPAN = 0x0B,
    ELITE_SYSTEMS = 0x0C,
    EA_ELECTRONIC_ARTS = 0x13,
    HUDSONSOFT = 0x18,
    ITC_ENTERTAINMENT = 0x19,
    YANOMAN = 0x1A,
    JAPAN_CLARY = 0x1D,
    VIRGIN_INTERACTIVE = 0x1F,
    PCM_COMPLETE = 0x24,
    SAN_X = 0x25,
    KOTOBUKI_SYSTEMS = 0x28,
    SETA = 0x29,
    INFOGRAMES = 0x30,
    NINTENDO_2 = 0x31,
    BANDAI = 0x32,
    USE_NEW_LICENSEE_CODE = 0x33,
    KONAMI = 0x34,
    HECTORSOFT = 0x35,
    CAPCOM_2 = 0x38,
    BANPRESTO = 0x39,
    ENTERTAINMENT_I = 0x3C,
    GREMLIN = 0x3E,
    UBISOFT = 0x41,
    ATLUS = 0x42,
    MALIBU = 0x44,
    ANGEL = 0x46,
    SPECTRUM_HOLOBY = 0x47,
    IREM = 0x49,
    VIRGIN_INTERACTIVE_2 = 0x4A,
    MALIBU_2 = 0x4D,
    US_GOLD = 0x4F,
    ABSOLUTE = 0x50,
    ACCLAIM = 0x51,
    ACTIVISION = 0x52,
    AMERICAN_SAMMY = 0x53,
    GAMETEK = 0x54,
    PARK_PLACE = 0x55,
    LJN = 0x56,
    MATCHBOX = 0x57,
    MILTON_BRADLEY = 0x59,
    MINDSCAPE = 0x5A,
    ROMSTAR = 0x5B,
    NAXAT_SOFT = 0x5C,
    TRADEWEST = 0x5D,
    TITUS = 0x60,
    VIRGIN_INTERACTIVE_3 = 0x61,
    OCEAN_INTERACTIVE = 0x67,
    EA_ELECTRONIC_ARTS_2 = 0x69,
    ELITE_SYSTEMS_2 = 0x6E,
    ELECTRO_BRAIN = 0x6F,
    INFOGRAMES_2 = 0x70,
    INTERPLAY = 0x71,
    BRODERBUND = 0x72,
    SCULPTERED_SOFT = 0x73,
    THE_SALES_CURVE = 0x75,
    THQ = 0x78,
    ACCOLADE = 0x79,
    TRIFFIX_ENTERTAINMENT = 0x7A,
    MICROPROSE = 0x7C,
    KEMCO = 0x7F,
    MISAWA_ENTERTAINMENT = 0x80,
    LOZC = 0x83,
    TOKUMA_SHOTEN_INTERMEDIA = 0x86,
    BULLET_PROOF_SOFTWARE = 0x8B,
    VIC_TOKAI = 0x8C,
    APE = 0x8E,
    IMAX = 0x8F,
    CHUNSOFT_CO = 0x91,
    VIDEO_SYSTEM = 0x92,
    TSUBARAYA_PRODUCTIONS_CO = 0x93,
    VARIE_CORPORATION = 0x95,
    YONEZAWA_SPAL = 0x96,
    KANEKO = 0x97,
    ARC = 0x99,
    NIHON_BUSSAN = 0x9A,
    TECMO = 0x9B,
    IMAGINEER = 0x9C,
    BANPRESTO_2 = 0x9D,
    NOVA = 0x9F,
    HORI_ELECTRIC = 0xA1,
    BANDAI_2 = 0xA2,
    KONAMI_2 = 0xA4,
    KAWADA = 0xA6,
    TAKARA = 0xA7,
    TECHNOS_JAPAN = 0xA9,
    BRODERBUND_2 = 0xAA,
    TOEI_ANIMATION = 0xAC,
    TOHO = 0xAD,
    NAMCO = 0xAF,
    ACCLAIM_2 = 0xB0,
    ASCII_OR_NEXSOFT = 0xB1,
    BANDAI_3 = 0xB2,
    SQUARE_ENIX = 0xB4,
    HAL_LABORATORY = 0xB6,
    SNK = 0xB7,
    PONY_CANYON = 0xB9,
    CULTURE_BRAIN = 0xBA,
    SUNSOFT = 0xBB,
    SONY_IMAGESOFT = 0xBD,
    SAMMY = 0xBF,
    TAITO = 0xC0,
    KEMCO_2 = 0xC2,
    SQUARESOFT = 0xC3,
    TOKUMA_SHOTEN_INTERMEDIA_2 = 0xC4,
    DATA_EAST = 0xC5,
    TONKINHOUSE = 0xC6,
    KOEI = 0xC8,
    UFL = 0xC9,
    ULTRA = 0xCA,
    VAP = 0xCB,
    USE_CORPORATION = 0xCC,
    MELDAC = 0xCD,
    PONY_CANYON_OR = 0xCE,
    ANGEL_2 = 0xCF,
    TAITO_2 = 0xD0,
    SOFEL = 0xD1,
    QUEST = 0xD2,
    SIGMA_ENTERPRISES = 0xD3,
    ASK_KODANSHA_CO = 0xD4,
    NAXAT_SOFT_2 = 0xD6,
    COPYA_SYSTEM = 0xD7,
    BANPRESTO_3 = 0xD9,
    TOMY = 0xDA,
    LJN_2 = 0xDB,
    NCS = 0xDD,
    HUMAN = 0xDE,
    ALTRON = 0xDF,
    JALECO_2 = 0xE0,
    TOWA_CHIKI = 0xE1,
    YUTAKA = 0xE2,
    VARIE = 0xE3,
    EPCOH = 0xE5,
    ATHENA = 0xE7,
    ASMIK_ACE_ENTERTAINMENT = 0xE8,
    NATSUME = 0xE9,
    KING_RECORDS = 0xEA,
    ATLUS_2 = 0xEB,
    EPIC_OR_SONY_RECORDS = 0xEC,
    IGS = 0xEE,
    A_WAVE = 0xF0,
    EXTREME_ENTERTAINMENT = 0xF3,
    LJN_3 = 0xFF,
};

class Cartridge
{
    public:
        Cartridge();
        Cartridge(std::vector<uint8_t> data);
        Cartridge(const std::string& filename);
        void printCartridgeData();
        void printROMData(std::vector<uint8_t> data, size_t bytesPerRow = 16);
        std::vector<uint8_t> getROMData(size_t start = 0, size_t end = std::numeric_limits<size_t>::max());
    private:
        std::vector<uint8_t> romData;
        std::vector<uint8_t> entryPoint;
        std::vector<uint8_t> nintendoLogo;
        std::string title;
        std::vector<uint8_t> manufacturerCode;
        uint8_t cgbFlag;
        std::vector<uint8_t> newLicenseeCode;
        uint8_t sgbFlag;
        CartridgeType cartridgeType;
        ROMSize romSize;
        RAMSize ramSize;
        DestinationCode destinationCode;
        OldLicenseeCode oldLicenseeCode;
        uint8_t maskROMVersionNumber;
        uint8_t headerChecksum;
        std::vector<uint8_t> globalChecksum;
        std::vector<uint8_t> loadRom(const std::string& filename);
        void parseHeaderData();
        void printByte(uint8_t byte);
        bool passesHeaderChecksum();
};

#endif