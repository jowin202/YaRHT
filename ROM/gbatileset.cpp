#include "gbatileset.h"
#include "gbarom.h"

GBATileset::GBATileset(int offset1, int offset2, GBARom *rom)
{
    this->compressed1 = rom->read8bit(offset1) > 0;
    this->image_offset1 = rom->read_offset(offset1+4);
    this->pallette_offset1 = rom->read_offset(offset1+8);
    this->blocks_offset1 = rom->read_offset(offset1+12);
    this->unknown_offset1 = rom->read_offset(offset1+16);
    this->block_metadata_offset1 = rom->read_offset(offset1+20);


    this->compressed2 = rom->read8bit(offset2) > 0;
    this->image_offset2 = rom->read_offset(offset2+4);
    this->pallette_offset2 = rom->read_offset(offset2+8);
    this->blocks_offset2 = rom->read_offset(offset2+12);
    this->unknown_offset2 = rom->read_offset(offset2+16);
    this->block_metadata_offset2 = rom->read_offset(offset2+20);

    rom->register_offset(this->image_offset1);
    rom->register_offset(this->image_offset2);
    rom->register_offset(this->pallette_offset1);
    rom->register_offset(this->pallette_offset2);
    rom->register_offset(this->blocks_offset1);
    rom->register_offset(this->blocks_offset2);
    rom->register_offset(this->unknown_offset1);
    rom->register_offset(this->unknown_offset2);
    rom->register_offset(this->block_metadata_offset1);
    rom->register_offset(this->block_metadata_offset2);

    for (int i = 0; i < 256; i++)
    {
        if (i%16 == 0)
        {
            //first color is always transparent
            colors1.append(QColor(0,0,0,0));
            colors2.append(QColor(0,0,0,0));
            continue;
        }
        int v = rom->read16bit(this->pallette_offset1 + 2*i);
        colors1.append(QColor(this->get_red(v),
                              this->get_green(v),
                              this->get_blue(v)));

        v = rom->read16bit(this->pallette_offset2 + 2*i);
        colors2.append(QColor(this->get_red(v),
                              this->get_green(v),
                              this->get_blue(v)));
    }



    for (int i = 0; i < 16; i++)
    {
        if (colors1.at(16*i+1) == colors1.at(16*i+2)
                && colors1.at(16*i+2) == colors1.at(16*i+3)
                && colors1.at(16*i+3) == colors1.at(16*i+4)
                && colors1.at(16*i+4) == colors1.at(16*i+5))
        {
            for (int c = 0; c < 16; c++)
            {
                colors1.removeAt(16*i + c);
                colors1.insert(16*i + c, colors2.at(16*i + c));
            }
        }
    }


    if (compressed1)
        this->image_data1 = rom->decompress(this->image_offset1);
    else
        this->image_data1 = rom->rom_data.mid(this->image_offset1, rom->bytes_to_next_offset(this->image_offset1));

    if (compressed2)
        this->image_data2 = rom->decompress(this->image_offset2);
    else
        this->image_data2 = rom->rom_data.mid(this->image_offset2, rom->bytes_to_next_offset(this->image_offset2));

    this->generate_block_image();
    this->generate_tileset_image(rom);
}

void GBATileset::generate_block_image()
{
    for (int pal = 0; pal < 16; pal++)
    {
        int rows = ((image_data1.length()-1)/(16*32)+1); //ceiling
        int rows2 = ((image_data2.length()-1)/(16*32)+1);

        QImage img(16*8, 16*(rows+rows2), QImage::Format_ARGB32);

        for (int y = 0; y < rows+rows2; y++)
        {
            for (int x = 0; x < 16; x++)
            {
                QByteArray block;
                if (y < rows)
                    block = this->image_data1.mid(32*(16*y+x), 32);
                else
                    block = this->image_data2.mid(32*(16*(y-rows)+x), 32);
                if (block.length() != 32) continue;

                for (int yb = 0; yb < 8; yb++)
                {
                    for (int xb = 0; xb < 4; xb++)
                    {
                        QColor c1;
                        QColor c2;
                        if (y < rows)
                        {
                            c1 = colors1.at(16*pal + ((block[4*yb+xb] >> 4) & 0xF));
                            c2 = colors1.at(16*pal + (block[4*yb+xb] & 0xF));
                        }
                        else
                        {
                            c1 = colors2.at(16*pal + ((block[4*yb+xb] >> 4) & 0xF));
                            c2 = colors2.at(16*pal + (block[4*yb+xb] & 0xF));
                        }

                        img.setPixelColor(8*x + 2*xb+1,8*y + yb, c1);
                        img.setPixelColor(8*x + 2*xb  ,8*y + yb, c2);
                    }
                }

            }
        }


        this->block_images.append(img);
    }
}

QImage GBATileset::get_block_by_num(int n)
{
    int pallette = n>>12;
    bool xflip = (n & 0x400) > 0;
    bool yflip = (n & 0x800) > 0;

    n = n & 0x3FF;

    int x = n % 16;
    int y = n / 16;

    QImage block = this->block_images[pallette].copy(8*x,8*y,8,8);

    block = block.mirrored(xflip,yflip);

    return block;
}

void GBATileset::generate_tileset_image(GBARom *rom)
{
    tileset_tiles = 0;
    int tileset1_tiles = rom->bytes_to_next_offset(blocks_offset1)/16;
    int tileset2_tiles = rom->bytes_to_next_offset(blocks_offset2)/16;


    int tileset1_rows = (tileset1_tiles-1)/8+1;
    int tileset2_rows = (tileset2_tiles-1)/8+1;


    tileset_tiles = tileset1_tiles+tileset2_tiles;

    int b1,b2,b3,b4;
    int offset;

    QImage img = QImage(128, 16*(tileset1_rows + tileset2_rows), QImage::Format_ARGB32);
    QPainter painter(&img);
    for (int y = 0; y < tileset1_rows + tileset2_rows; y++)
    {
        if (y < tileset1_rows) offset = this->blocks_offset1;
        else offset = this->blocks_offset2 - tileset1_rows*8*16;

        for (int x = 0; x < 8; x++)
        {
            b1 = rom->read16bit(offset+16*(8*y+x) + 0);
            b2 = rom->read16bit(offset+16*(8*y+x) + 2);
            b3 = rom->read16bit(offset+16*(8*y+x) + 4);
            b4 = rom->read16bit(offset+16*(8*y+x) + 6);
            painter.drawImage(QRect(16*x+0,16*y+0,8,8), this->get_block_by_num(b1));
            painter.drawImage(QRect(16*x+8,16*y+0,8,8), this->get_block_by_num(b2));
            painter.drawImage(QRect(16*x+0,16*y+8,8,8), this->get_block_by_num(b3));
            painter.drawImage(QRect(16*x+8,16*y+8,8,8), this->get_block_by_num(b4));
            b1 = rom->read16bit(offset+16*(8*y+x) + 8);
            b2 = rom->read16bit(offset+16*(8*y+x) + 10);
            b3 = rom->read16bit(offset+16*(8*y+x) + 12);
            b4 = rom->read16bit(offset+16*(8*y+x) + 14);
            painter.drawImage(QRect(16*x+0,16*y+0,8,8), this->get_block_by_num(b1));
            painter.drawImage(QRect(16*x+8,16*y+0,8,8), this->get_block_by_num(b2));
            painter.drawImage(QRect(16*x+0,16*y+8,8,8), this->get_block_by_num(b3));
            painter.drawImage(QRect(16*x+8,16*y+8,8,8), this->get_block_by_num(b4));
        }
    }

    painter.end();
    this->tileset_image = img;
}

QImage GBATileset::get_tile_by_num(int n)
{
    return this->tileset_image.copy((n%8)*16,(n/8)*16,16,16);
}
