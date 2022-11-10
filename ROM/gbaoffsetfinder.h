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
signals:

};

#endif // GBAOFFSETFINDER_H
