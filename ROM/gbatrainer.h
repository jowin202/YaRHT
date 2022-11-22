#ifndef GBATRAINER_H
#define GBATRAINER_H

#include <QObject>
#include <QDebug>

class GBARom;

struct trainer_pokemon{
    int EV;
    int level;
    int species;
    int moves[4];
    int item;
};

class GBATrainer
{
public:
    GBATrainer(GBARom *rom);
    void load_party();

    QString get_full_name();
    QString get_class_string();

    QString party_as_string(); //for debugging


    int partyFlags;
    int trainerClass;
    int encounterMusic;
    int trainerPic;
    QString name;
    //items
    bool double_battle;
    int partySize;
    int party_offset;

    trainer_pokemon party[6];



    GBARom *rom;

signals:

};

#endif // GBATRAINER_H
