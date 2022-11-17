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

int GBAOffsetFinder::find_pokemon_name_offset(GBARom *rom)
{
    return rom->read_offset(0x144);
}

int GBAOffsetFinder::find_encounter_offset(GBARom *rom)
{
    for (int i = 0; i < rom->rom_data.length()-16; i++)
    {
        if (rom->rom_data.at(i) == 0x14
                && rom->rom_data.at(i+1) == ((char)0xD0) //minus
                && rom->rom_data.at(i+2) == 0x20
                && rom->rom_data.at(i+3) == 0x1C
                && rom->rom_data.at(i+4) == 0x13
                && rom->rom_data.at(i+5) == ((char)0xE0) //minus
                && rom->rom_data.at(i+6) == 0x00
                && rom->rom_data.at(i+7) == 0x00)
        {
            if (rom->rom_data.at(i+11) == 0x08)
            {
                return rom->read_offset(i+8);
            }
        }
    }
    return -1;
}

int GBAOffsetFinder::find_trainer_offset(GBARom *rom)
{
    return rom->read_offset(0x116c4);
}

int GBAOffsetFinder::find_move_name_offset(GBARom *rom)
{
    return rom->read_offset(0x148);
}

int GBAOffsetFinder::find_front_sprite_offset(GBARom *rom)
{
    return rom->read_offset(0x128);
}

int GBAOffsetFinder::find_back_sprite_offset(GBARom *rom)
{
    return rom->read_offset(0x12C);
}

int GBAOffsetFinder::find_pokemon_palette_offset(GBARom *rom)
{
    return rom->read_offset(0x130);
}

int GBAOffsetFinder::find_pokemon_shiny_palette_offset(GBARom *rom)
{
    return rom->read_offset(0x134);
}

int GBAOffsetFinder::find_pokemon_icon_offset(GBARom *rom)
{
    Q_UNUSED(rom);
    return -1;
}

int GBAOffsetFinder::find_pokemon_icon_palette_offset(GBARom *rom)
{
    Q_UNUSED(rom);
    return -1;
}

int GBAOffsetFinder::find_pokemon_footprint_offset(GBARom *rom)
{

    //TODO: make this better
    for (int i = 0; i < rom->rom_data.length()-16; i++)
    {
        if (rom->rom_data.at(i) == ((char)0xA1)
                && rom->rom_data.at(i+1) == ((char)0x46)
                && rom->rom_data.at(i+2) == ((char)0xAA)
                && rom->rom_data.at(i+3) == ((char)0x46)
                && rom->rom_data.at(i+4) == ((char)0xF0)
                && rom->rom_data.at(i+5) == ((char)0xBC)
                && rom->rom_data.at(i+6) == 0x01
                && rom->rom_data.at(i+7) == ((char)0xBC)
                && rom->rom_data.at(i+8) == 0x00
                && rom->rom_data.at(i+9) == 0x47
                && rom->rom_data.at(i+10) == 0x00
                && rom->rom_data.at(i+11) == 0x00)
        {
            if (rom->rom_data.at(i+15) == 0x08)
            {
                return rom->read_offset(i+12);
            }
        }
    }
    return -1;
}

int GBAOffsetFinder::find_pokemon_base_stat_offset(GBARom *rom)
{
    return rom->read_offset(0x1BC);
}

int GBAOffsetFinder::find_pokemon_evolution_offset(GBARom *rom)
{
    for (int i = 0; i < rom->rom_data.length()-16; i++)
    {
        if (rom->rom_data.at(i) == ((char)0xBE)
                && rom->rom_data.at(i+1) == 0x00
                && rom->rom_data.at(i+2) == 0x0A
                && rom->rom_data.at(i+3) == ((char)0xE1))
        {
            if (rom->rom_data.at(i+7) == 0x08)
            {
                return rom->read_offset(i+4);
            }
        }
    }
    return -1;
}
