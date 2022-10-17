#include "gbamap.h"
#include "gbarom.h"
#include "gbatileset.h"

GBAMap::GBAMap(int offset, GBARom *rom)
{
    this->offset = offset;

    this->footer_offset = rom->read_offset(offset);
    this->event_offset = rom->read_offset(offset+4);
    this->script_offset = rom->read_offset(offset+8);
    this->connection_offset = rom->read_offset(offset+12);

    this->music_no = rom->read16bit(offset+16);


    this->width = rom->read32bit(this->footer_offset);
    this->height = rom->read32bit(this->footer_offset+4);

    this->border_offset = rom->read_offset(this->footer_offset+8);
    this->map_offset = rom->read_offset(this->footer_offset+12);

    this->tileset1_offset = rom->read_offset(this->footer_offset+16);
    this->tileset2_offset = rom->read_offset(this->footer_offset+20);


    rom->register_offset(this->footer_offset);
    rom->register_offset(this->event_offset);
    rom->register_offset(this->script_offset);
    rom->register_offset(this->connection_offset);
    rom->register_offset(this->border_offset);
    rom->register_offset(this->map_offset);
    rom->register_offset(this->tileset1_offset);
    rom->register_offset(this->tileset2_offset);


    //connections
    int num_connections = rom->read8bit(connection_offset);
    int connection_addr = rom->read_offset(connection_offset+4);
    for (int i = 0; i < num_connections; i++)
    {
        connection conn;
        conn.direction = rom->read8bit(connection_addr);
        conn.offset = rom->read8bit(connection_addr+4);
        conn.bank = rom->read8bit(connection_addr+8);
        conn.map = rom->read8bit(connection_addr+9);

        connection_addr += 12;
        this->connections.append(conn);
    }


    //tileset
    QPair<int,int> id(this->tileset1_offset,this->tileset2_offset);
    if (rom->tilesets.contains(id))
        this->tileset = rom->tilesets.value(id);
    else
    {
        this->tileset = new GBATileset(this->tileset1_offset, this->tileset2_offset, rom);
        rom->tilesets.insert(id,this->tileset);
    }

    this->generate_map_image(rom);
}

void GBAMap::generate_map_image(GBARom *rom)
{
    if (this->tileset->tileset_image.isNull())
        return; //

    this->passages.clear();

    int offset = this->map_offset;
    QImage img(16*this->width, 16*this->height, QImage::Format_ARGB32);
    QPainter painter(&img);

    for (int y = 0; y < this->height; y++)
    {
        for (int x = 0; x < this->width; x++)
        {
            int v = rom->read16bit(offset);
            offset += 2;
            this->passages.append(v >> 10);
            v = v & 0x3FF;
            QImage tile = this->tileset->get_tile_by_num(v);
            if (!tile.isNull())
                painter.drawImage(16*x,16*y,tile);
        }
    }

    painter.end();
    this->map_image = img;

}
