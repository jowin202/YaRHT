#ifndef GBAPOKEMON_H
#define GBAPOKEMON_H

#include <QString>
#include <QImage>

class GBARom;

class GBAPokemon
{
public:
    GBAPokemon(GBARom *rom);

    int set_base_stats(int offset);

    QString get_name();

    int front_sprite_offset;
    int back_sprite_offset;

    int pal_offset;
    int pal_shiny_offset;



    int name_index; //set in GBARom when created



    //stats
    int base_hp;
    int base_atk;
    int base_def;
    int base_speed;
    int sp_atk;
    int sp_def;

    int type1; //TODO: enum
    int type2;

    int catch_rate;

    int yield_exp;

    int ev_yield_hp;
    int ev_yield_atk;
    int ev_yield_def;
    int ev_yield_speed;
    int ev_yield_special_atk;
    int ev_yield_special_def;

    int item1, item2;

    int gender_ratio;
    int egg_cycles;
    int friendship;

    int growth_rate;
    int egg_group1;
    int egg_group2;

    //TODO
    int abilities1;
    int abilities2;

    int safari_zone_flee_rate;
    int body_color;
    int noflip; //turn left,right


    //Sprites
    QImage front_sprite;
    QImage back_sprite;
    QImage front_sprite_shiny;
    QImage back_sprite_shiny;


    GBARom *rom = 0;
};

#endif // GBAPOKEMON_H
