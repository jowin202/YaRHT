#ifndef GBAROM_H
#define GBAROM_H

#include <QObject>
#include <QHash>

class GBATileset;
class GBAMap;
class GBAEncounter;
class GBATrainer;
class GBAPokemon;

class GBARom
{
public:
    GBARom();
    void set_path(QString path);
    int read_offset(int pos);
    int read8bit(int pos);
    int read16bit(int pos);
    int read24bit(int pos);
    int read32bit(int pos);
    int read32bit_signed(int pos);
    QByteArray decompress(int offset);
    QString readText(int pos, int len);
    QString readText_until_FF(int pos, int *expected_length);
    int find_start_of_text(int pos);
    int find_end_of_text(int pos);
    int find_next_text(int pos);

    QString path;
    QByteArray rom_data;

    //Maps and Banks
    void find_banks(int offset);
    void find_maps();
    QList<int> bank_offsets;
    int map_bank_header_offset;
    QList< QList<GBAMap*> > maps;

    QHash<QPair<int,int>,GBATileset*> tilesets;


    //Map Part Names
    void find_place_names(int offset);
    QStringList place_names;
    int name_index = 0;
    int num_names = 0;

    //Encounters
    void find_encounters(int offset);
    QHash< QPair<int,int>, GBAEncounter*> encounters;



    //Pokemon Data
    void find_pokemon_names(int offset);
    void find_pokemon_base_stats(int offset);
    void find_pokemon_sprites(int front_offset, int back_offset, int icon_offset, int footprint_offset, int pal_offset, int pal_shiny_offset, int pal_icon);
    QStringList pokemon_names;
    QList<GBAPokemon*> pokemons;

    //Trainers
    void find_trainers(int offset);
    void find_trainer_class_names(int offset);
    QList<GBATrainer*> trainers;
    QStringList trainerClassNames;


    //move names
    void find_move_names(int offset);
    QStringList move_names;





    void register_offset(int offset);
    int bytes_to_next_offset(int offset);
    QList<int> offsets;
};

#endif // GBAROM_H
