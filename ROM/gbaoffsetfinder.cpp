#include "gbaoffsetfinder.h"
#include "gbarom.h"

GBAOffsetFinder::GBAOffsetFinder(QObject *parent) : QObject(parent)
{

}

int GBAOffsetFinder::find_bank_header_offset(GBARom *rom)
{
    for (int i = 0; i < rom->rom_data.length()-4; i++)
    {
        if (rom->rom_data.at(i) == 0x08
                && rom->rom_data.at(i+1) == 0x68
                && rom->rom_data.at(i+2) == 0x70
                && rom->rom_data.at(i+3) == 0x47)
        {
            if (rom->rom_data.at(i+7) == 0x08)
            {
                return rom->read_offset(i+4);
            }
        }
    }
    return -1;
}

int GBAOffsetFinder::find_name_offset_FR_LG(GBARom *rom)
{
    for (int i = 0; i < rom->rom_data.length()-16; i++)
    {
        if (rom->rom_data.at(i) == 0x44
                && rom->rom_data.at(i+1) == 0x40
                && rom->rom_data.at(i+2) == 0x46
                && rom->rom_data.at(i+3) == 0x42)
        {
            if (rom->rom_data.at(i+11) == 0x08)
            {
                return i+8;
            }
        }
    }
    return -1;
}
