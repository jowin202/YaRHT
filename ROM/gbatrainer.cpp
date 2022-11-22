#include "gbatrainer.h"
#include "gbarom.h"

GBATrainer::GBATrainer(GBARom *rom)
{
    this->rom = rom;
}

void GBATrainer::load_party()
{
    int offset = party_offset;

    if (this->partyFlags == 3)
    {
        //custom moveset and custom items
        for (int i = 0; i < partySize; i++)
        {
            party[i].EV = rom->read16bit(offset);
            offset += 2;
            party[i].level = rom->read16bit(offset);
            offset += 2;
            party[i].species = rom->read16bit(offset);
            offset += 2;
            party[i].item = rom->read16bit(offset);
            offset += 2;
            party->moves[0] = rom->read16bit(offset);
            offset += 2;
            party->moves[1] = rom->read16bit(offset);
            offset += 2;
            party->moves[2] = rom->read16bit(offset);
            offset += 2;
            party->moves[3] = rom->read16bit(offset);
            offset += 2;
        }

    }
    else if (this->partyFlags == 1)
    {
        //custom moveset
        for (int i = 0; i < partySize; i++)
        {
            party[i].EV = rom->read16bit(offset);
            offset += 2;
            party[i].level = rom->read16bit(offset);
            offset += 2;
            party[i].species = rom->read16bit(offset);
            offset += 2;
            party->moves[0] = rom->read16bit(offset);
            offset += 2;
            party->moves[1] = rom->read16bit(offset);
            offset += 2;
            party->moves[2] = rom->read16bit(offset);
            offset += 2;
            party->moves[3] = rom->read16bit(offset);
            offset += 2;

            offset += 2; //skip item
        }

    }
    else if (this->partyFlags == 2)
    {
        //custom items
        for (int i = 0; i < partySize; i++)
        {
            party[i].EV = rom->read16bit(offset);
            offset += 2;
            party[i].level = rom->read16bit(offset);
            offset += 2;
            party[i].species = rom->read16bit(offset);
            offset += 2;
            party[i].item = rom->read16bit(offset);
            offset += 2;
            party->moves[0] = rom->read16bit(offset);
            offset += 2;
            party->moves[1] = rom->read16bit(offset);
            offset += 2;
            party->moves[2] = rom->read16bit(offset);
            offset += 2;
            party->moves[3] = rom->read16bit(offset);
            offset += 2;
        }

    }
    else //if (partsflags == 0)
    {
        //no items, no custom moves
        for (int i = 0; i < partySize; i++)
        {
            party[i].EV = rom->read16bit(offset);
            offset += 2;
            party[i].level = rom->read16bit(offset);
            offset += 2;
            party[i].species = rom->read16bit(offset);
            offset += 2;
            offset += 2; //skip this
        }

    }
}

QString GBATrainer::get_full_name()
{
    if (rom->trainerClassNames.length() <= this->trainerClass) return QString();
    else
        return rom->trainerClassNames.at(this->trainerClass) + " " + this->name;
}

QString GBATrainer::get_class_string()
{
    if (rom->trainerClassNames.length() <= this->trainerClass) return QString();
    else
        return rom->trainerClassNames.at(this->trainerClass);
}

QString GBATrainer::party_as_string()
{
    this->load_party();
    QString str;

    for (int i = 0; i < partySize; i++)
    {
        QString pkmn_name;
        if (rom->pokemon_names.length() > party[i].species)
            pkmn_name = rom->pokemon_names.at(party[i].species);
        str += pkmn_name + QString("(lv: %1, ev: %2)").arg(party[i].level).arg(party[i].EV) + ", ";
    }
    return str;
}
