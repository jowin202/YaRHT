#include "gbapalette.h"
#include "gbarom.h"

GBAPalette::GBAPalette(GBARom *rom, int offset)
{

    //first color is always transparent
    colors.append(QColor(0,0,0,0));

    for (int i = 1; i < 16; i++)
    {
        int v = rom->read16bit(offset + 2*i);
        colors.append(QColor(this->get_red(v),
                              this->get_green(v),
                              this->get_blue(v)));
    }
}
