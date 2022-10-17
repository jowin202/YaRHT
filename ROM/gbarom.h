#ifndef GBAROM_H
#define GBAROM_H

#include <QObject>
#include <QHash>

class GBATileset;
class GBAMap;
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
    QByteArray decompress(int offset);
    QString readText(int pos, int len);
    int find_start_of_text(int pos);
    int find_end_of_text(int pos);

    QString path;
    QByteArray rom_data;

    int find_bank_header_offset();
    void find_banks(int offset);
    void find_maps();
    QList<int> bank_offsets;
    int map_bank_header_offset;
    QList< QList<GBAMap*> > maps;

    QHash<QPair<int,int>,GBATileset*> tilesets;



    void register_offset(int offset);
    int bytes_to_next_offset(int offset);
    QList<int> offsets;
};

#endif // GBAROM_H
