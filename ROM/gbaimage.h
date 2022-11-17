#ifndef GBAIMAGE_H
#define GBAIMAGE_H

#include <QImage>
#include <QDebug>
#include <QByteArray>

class GBARom;
class GBAPalette;


class GBAImage
{
public:
    GBAImage(GBARom *rom, GBAPalette *palette, int offset);

    QImage toImage(int w, int h);


    QByteArray image_data;
    GBARom *rom = 0;
    GBAPalette *pal;
    int offset;
};

#endif // GBAIMAGE_H
