#include "gbaencounter.h"
#include "gbarom.h"

GBAEncounter::GBAEncounter(int grass_offset, int water_offset, int rocksmash_offset, int fishingrod_offset, GBARom *rom)
{
    this->rom = rom;

    if (grass_offset > 0)
    {
        this->grass_encounter_ratio = this->rom->read8bit(grass_offset);
        grass_offset = this->rom->read_offset(grass_offset+4);

        for (int i = 0; i < 12; i++)
        {
            encounter grass_enc;
            grass_enc.from_level = this->rom->read8bit(grass_offset++);
            grass_enc.to_level = this->rom->read8bit(grass_offset++);
            grass_enc.species = this->rom->read16bit(grass_offset);
            grass_offset += 2;
            this->grass_encounter.append(grass_enc);
        }
    }


    if (water_offset > 0)
    {
        this->water_encounter_ratio = this->rom->read8bit(water_offset);
        water_offset = this->rom->read_offset(water_offset+4);

        for (int i = 0; i < 5; i++)
        {
            encounter water_enc;
            water_enc.from_level = this->rom->read8bit(water_offset++);
            water_enc.to_level = this->rom->read8bit(water_offset++);
            water_enc.species = this->rom->read16bit(water_offset);
            water_offset += 2;
            this->water_encounter.append(water_enc);
        }
    }

    if (rocksmash_offset > 0)
    {
        this->rocksmash_encounter_ratio = this->rom->read8bit(rocksmash_offset);
        rocksmash_offset = this->rom->read_offset(rocksmash_offset+4);

        for (int i = 0; i < 5; i++)
        {
            encounter rocksmash_enc;
            rocksmash_enc.from_level = this->rom->read8bit(rocksmash_offset++);
            rocksmash_enc.to_level = this->rom->read8bit(rocksmash_offset++);
            rocksmash_enc.species = this->rom->read16bit(rocksmash_offset);
            rocksmash_offset += 2;
            this->rocksmash_encounter.append(rocksmash_enc);
        }
    }

    if (fishingrod_offset > 0)
    {
        this->fishingrod_encounter_ratio = this->rom->read8bit(fishingrod_offset);
        fishingrod_offset = this->rom->read_offset(fishingrod_offset+4);

        for (int i = 0; i < 10; i++)
        {
            encounter fishingrod_enc;
            fishingrod_enc.from_level = this->rom->read8bit(fishingrod_offset++);
            fishingrod_enc.to_level = this->rom->read8bit(fishingrod_offset++);
            fishingrod_enc.species = this->rom->read16bit(fishingrod_offset);
            fishingrod_offset += 2;
            this->fishingrod_encounter.append(fishingrod_enc);
        }
    }

}
