#include "gbapalette.h"
#include "gbarom.h"

GBAPalette::GBAPalette(GBARom *rom, int offset, bool compressed)
{

    QByteArray data;
    if (compressed)
    {
        data = rom->decompress(offset);
    }

    //first color is always transparent
    colors.append(QColor(0,0,0,0));

    for (int i = 1; i < 16; i++)
    {
        int v = (compressed ? (0xFF & data[2*i]) | (data[2*i+1] << 8) : rom->read16bit(offset + 2*i));
        colors.append(QColor(this->get_red(v),
                              this->get_green(v),
                              this->get_blue(v)));
    }
}
