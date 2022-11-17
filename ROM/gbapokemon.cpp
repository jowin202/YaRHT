#include "gbapokemon.h"
#include "gbarom.h"
#include "gbapalette.h"

GBAPokemon::GBAPokemon(GBARom *rom)
{
    this->rom = rom;
}

int GBAPokemon::set_base_stats(int offset)
{
    int offset_begin = offset;

    this->base_hp = this->rom->read8bit(offset++);
    this->base_atk= this->rom->read8bit(offset++);
    this->base_def = this->rom->read8bit(offset++);
    this->base_speed = this->rom->read8bit(offset++);
    this->sp_atk= this->rom->read8bit(offset++);
    this->sp_def = this->rom->read8bit(offset++);

    this->type1 = this->rom->read8bit(offset++);
    this->type2 = this->rom->read8bit(offset++);

    this->catch_rate = this->rom->read8bit(offset++);
    this->yield_exp = this->rom->read8bit(offset++);
    offset++; //skip
    offset++; //skip

    this->item1 = this->rom->read16bit(offset);
    offset+=2;
    this->item2 = this->rom->read16bit(offset);
    offset+=2;


    this->gender_ratio = this->rom->read8bit(offset++);
    this->egg_cycles = this->rom->read8bit(offset++);
    this->friendship = this->rom->read8bit(offset++);
    this->growth_rate = this->rom->read8bit(offset++);

    this->egg_group1 = this->rom->read8bit(offset++);
    this->egg_group2 = this->rom->read8bit(offset++);
    this->abilities1 = this->rom->read8bit(offset++);
    this->abilities2 = this->rom->read8bit(offset++);

    this->safari_zone_flee_rate = this->rom->read8bit(offset++);
    this->body_color = this->rom->read8bit(offset++);
    this->noflip = this->rom->read8bit(offset++);

    offset++; //last byte skip

    return offset-offset_begin;
}

QString GBAPokemon::get_name()
{
    if (this->rom != 0 && this->rom->pokemon_names.length() >= 0 && this->rom->pokemon_names.length() > this->name_index && name_index > 0)
    {
        return this->rom->pokemon_names.at(this->name_index-1);
    }

    return "";
}
