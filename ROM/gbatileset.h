#ifndef GBATILESET_H
#define GBATILESET_H

#include <QColor>
#include <QImage>
#include <QPainter>
#include <QRect>
#include <QDebug>

class GBARom;
class GBATileset
{
public:
    GBATileset(int offset1, int offset2, GBARom *rom);

    bool compressed1;
    int image_offset1;
    int pallette_offset1;
    int blocks_offset1;
    int unknown_offset1;
    int block_metadata_offset1;

    bool compressed2;
    int image_offset2;
    int pallette_offset2;
    int blocks_offset2;
    int unknown_offset2;
    int block_metadata_offset2;

    QList<QColor> colors1;
    QList<QColor> colors2;

    QByteArray image_data1;
    QByteArray image_data2;


    void generate_block_image();
    QList<QImage> block_images;
    QImage get_block_by_num(int n);



    void generate_tileset_image(GBARom *rom);
    QImage tileset_image;
    int tileset_tiles;
    QImage get_tile_by_num(int n);




    int bit_convert(int v)
    { return 255*v/31; }
    int get_red(int v)
    { return bit_convert((v >> 0) & 0x1F); }
    int get_green(int v)
    { return bit_convert((v >> 5) & 0x1F); }
    int get_blue(int v)
    { return bit_convert((v >> 10) & 0x1F); }

};

#endif // GBATILESET_H
