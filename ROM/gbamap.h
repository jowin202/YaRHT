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


struct personEvent
{
    int no;
    int pic_no;
    int unkonwn_param1;
    int x;
    int y;
    int talking_level;
    int movement_type;
    int movement;
    int unkonwn_param2;
    int trainer;
    int unkonwn_param3;
    int view_radius;
    int script_offset;
    int person_id;
    int unkonwn_param4;
};

struct warpEvent
{
    int x;
    int y;
    int talking_level;
    int target_warp_no;
    int target_map;
    int target_bank;
};

struct scriptEvent
{
    int x;
    int y;
    int talking_level;
    int unknown1;
    int var_num;
    int var_value;
    int unknown2;
    int script_offset;
};

struct signpostEvent
{
    int x;
    int y;
    int talking_level;
    int signpost_type;
    int unknown;

    //signpost type = 0 .. 4
    int script_offset;
    //signpost type = 5 ..7
    int item_id;
    int hidden_id;
    int amount;

};

class GBAMap
{
public:
    GBAMap(int offset, GBARom *rom);
    GBARom *rom = 0;

    void generate_map_image(GBARom *rom);
    QString get_name();
    QImage map_image;
    QList<int> passages;

    int offset;
    int footer_offset;
    int event_offset;
    int script_offset;
    int connection_offset;

    int music_no;
    int name_index;

    int width;
    int height;

    int border_offset;
    int map_offset;

    int tileset1_offset;
    int tileset2_offset;


    GBATileset *tileset = 0;
    QList<connection> connections;
    QList<personEvent> person_events;
    QList<warpEvent> warp_events;
    QList<scriptEvent> script_events;
    QList<signpostEvent> signpost_events;
};

#endif // GBAMAP_H
