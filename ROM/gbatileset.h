#ifndef GBATILESET_H
#define GBATILESET_H

#include <QColor>
#include <QImage>
#include <QPainter>
#include <QRect>
#include <QDebug>

class GBAPalette;
class GBARom;
class GBATileset
{
public:
    GBATileset(int offset1, int offset2, GBARom *rom);

    bool compressed1;
    int image_offset1;
    int palette_offset1;
    int blocks_offset1;
    int unknown_offset1;
    int block_metadata_offset1;

    bool compressed2;
    int image_offset2;
    int palette_offset2;
    int blocks_offset2;
    int unknown_offset2;
    int block_metadata_offset2;


    QList<GBAPalette*> palettes1;
    QList<GBAPalette*> palettes2;


    QByteArray image_data1;
    QByteArray image_data2;


    void generate_block_image();
    QList<QImage> block_images;
    QImage get_block_by_num(int n);



    void generate_tileset_image(GBARom *rom);
    QImage tileset_image;
    int tileset_tiles;
    QImage get_tile_by_num(int n);


    QImage get_palettes_as_image();

};

#endif // GBATILESET_H
