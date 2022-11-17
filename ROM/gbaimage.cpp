#include "gbaimage.h"
#include "gbarom.h"
#include "gbapalette.h"

GBAImage::GBAImage(GBARom *rom, GBAPalette *palette, int offset)
{
    this->rom = rom;
    this->offset = offset;
    this->pal = palette;
    this->image_data = rom->decompress(offset);
}


QImage GBAImage::toImage(int w, int h)
{
    QImage img(w,h, QImage::Format_ARGB32);

    int c = 0;

    for (int by = 0; by < 8; by++)
    {
        for (int bx = 0; bx < 8; bx++)
        {

            for (int y = 0; y < 8; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    int col1 = (this->image_data[c] & 0xF);
                    int col2 = (0xF & (this->image_data[c] >> 4));


                    //qDebug() << (quint8)this->image_data[c] <<  col1 << col2;

                    img.setPixelColor(8*bx + 2*x  ,8*by + y, pal->colors.at(col1));
                    img.setPixelColor(8*bx + 2*x+1,8*by + y, pal->colors.at(col2));
                    c++;
                }
            }

        }
    }




    return img;
}
