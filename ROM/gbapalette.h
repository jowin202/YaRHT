#ifndef GBAPALETTE_H
#define GBAPALETTE_H

#include <QColor>
class GBARom;

class GBAPalette
{
public:
    GBAPalette(GBARom *rom, int offset, bool compressed = false);

    QList<QColor> colors;


    int bit_convert(int v)
    { return 255*v/31; }
    int get_red(int v)
    { return bit_convert((v >> 0) & 0x1F); }
    int get_green(int v)
    { return bit_convert((v >> 5) & 0x1F); }
    int get_blue(int v)
    { return bit_convert((v >> 10) & 0x1F); }

};

#endif // GBAPALETTE_H
