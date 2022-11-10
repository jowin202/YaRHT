#ifndef GBAENCOUNTER_H
#define GBAENCOUNTER_H

class GBARom;

#include <QList>

struct encounter {
    int from_level;
    int to_level;
    int species;
};

class GBAEncounter
{
public:
    GBAEncounter(int grass_offset, int water_offset, int rocksmash_offset, int fishingrod_offset, GBARom *rom);

    int grass_encounter_ratio;
    int water_encounter_ratio;
    int rocksmash_encounter_ratio;
    int fishingrod_encounter_ratio;
    QList<encounter> grass_encounter;
    QList<encounter> water_encounter;
    QList<encounter> rocksmash_encounter;
    QList<encounter> fishingrod_encounter;



    GBARom *rom;
};

#endif // GBAENCOUNTER_H
