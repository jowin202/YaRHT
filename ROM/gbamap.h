#ifndef GBAMAP_H
#define GBAMAP_H

#include <QByteArray>
#include <QImage>
#include <QPainter>


class GBARom;
class GBATileset;

struct connection
{
    int bank;
    int map;
    int direction;
    int offset;
};

class GBAMap
{
public:
    GBAMap(int offset, GBARom *rom);

    void generate_map_image(GBARom *rom);
    QImage map_image;
    QList<int> passages;

    int offset;
    int footer_offset;
    int event_offset;
    int script_offset;
    int connection_offset;

    int music_no;
    int width;
    int height;

    int border_offset;
    int map_offset;

    int tileset1_offset;
    int tileset2_offset;

    GBATileset *tileset = 0;
    QList<connection> connections;
};

#endif // GBAMAP_H
