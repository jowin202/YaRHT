#ifndef GBAOFFSETFINDER_H
#define GBAOFFSETFINDER_H

#include <QObject>

class GBARom;

class GBAOffsetFinder : public QObject
{
    Q_OBJECT
public:
    explicit GBAOffsetFinder(QObject *parent = nullptr);

    int find_bank_header_offset(GBARom *rom);
    int find_name_offset_FR_LG(GBARom *rom);
    int find_pokemon_name_offset(GBARom *rom);
    int find_encounter_offset(GBARom *rom);
    int find_trainer_offset(GBARom *rom);
    int find_trainer_class_name_offset(GBARom *rom);
    int find_move_name_offset(GBARom *rom);

    int find_front_sprite_offset(GBARom * rom);
    int find_back_sprite_offset(GBARom * rom);
    int find_pokemon_palette_offset(GBARom *rom);
    int find_pokemon_shiny_palette_offset(GBARom *rom);
    int find_pokemon_icon_offset(GBARom *rom);
    int find_pokemon_icon_palette_offset(GBARom *rom);
    int find_pokemon_footprint_offset(GBARom *rom);
    int find_pokemon_base_stat_offset(GBARom *rom);
    int find_pokemon_evolution_offset(GBARom *rom);

signals:

};

#endif // GBAOFFSETFINDER_H
