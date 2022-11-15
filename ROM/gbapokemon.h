#ifndef GBAPOKEMON_H
#define GBAPOKEMON_H

class GBARom;

class GBAPokemon
{
public:
    GBAPokemon(GBARom *rom);

    int front_sprite_offset;
    int back_sprite_offset;

    int pal_offset;
    int pal_shiny_offset;





    //stats
    int hp;
    int atk;
    int def;
    int speed;
    int sp_atk;
    int sp_def;
    int catch_rate;

    int type1; //TODO: enum
    int type2;

    int exp;

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

};

#endif // GBAPOKEMON_H
