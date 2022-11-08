#include "gbamap.h"
#include "gbarom.h"
#include "gbatileset.h"

GBAMap::GBAMap(int offset, GBARom *rom)
{
    this->offset = offset;
    this->rom = rom;

    this->footer_offset = rom->read_offset(offset);
    this->event_offset = rom->read_offset(offset+4);
    this->script_offset = rom->read_offset(offset+8);
    this->connection_offset = rom->read_offset(offset+12);

    this->music_no = rom->read16bit(offset+16);
    this->name_index = rom->read8bit(offset+20);


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



    //events
    int num_person_events = rom->read8bit(event_offset);
    int num_warps = rom->read8bit(event_offset+1);
    int num_scripts = rom->read8bit(event_offset+2);
    int num_sign_posts = rom->read8bit(event_offset+3);

    int event_person_offset = rom->read_offset(event_offset+4);
    int event_warp_offset = rom->read_offset(event_offset+8);
    int event_script_offset = rom->read_offset(event_offset+12);
    int event_signpost_offset = rom->read_offset(event_offset+16);

    for (int i = 0; i < num_person_events; i++)
    {
        personEvent ev;
        ev.no = rom->read8bit(event_person_offset++);
        ev.pic_no = rom->read8bit(event_person_offset++);
        ev.unkonwn_param1 = rom->read16bit(event_person_offset);
        event_person_offset += 2;

        ev.x = rom->read16bit(event_person_offset);
        event_person_offset += 2;
        ev.y = rom->read16bit(event_person_offset);
        event_person_offset += 2;


        ev.talking_level = rom->read8bit(event_person_offset++);
        ev.movement_type = rom->read8bit(event_person_offset++);
        ev.movement = rom->read8bit(event_person_offset++);
        ev.unkonwn_param2 = rom->read8bit(event_person_offset++);
        ev.trainer = rom->read8bit(event_person_offset++);
        ev.unkonwn_param3 = rom->read8bit(event_person_offset++);

        ev.view_radius = rom->read16bit(event_person_offset);
        event_person_offset += 2;

        ev.script_offset = rom->read_offset(event_person_offset);
        event_person_offset += 4;

        ev.person_id = rom->read16bit(event_person_offset);
        event_person_offset += 2;

        ev.unkonwn_param4 = rom->read16bit(event_person_offset);
        event_person_offset += 2;


        this->person_events.append(ev);
    }
    for (int i = 0; i < num_warps; i++)
    {
        warpEvent ev;
        ev.x = rom->read16bit(event_warp_offset);
        event_warp_offset += 2;

        ev.y = rom->read16bit(event_warp_offset);
        event_warp_offset += 2;

        ev.talking_level = rom->read8bit(event_warp_offset++);

        ev.target_warp_no = rom->read8bit(event_warp_offset++);
        ev.target_map = rom->read8bit(event_warp_offset++);
        ev.target_bank = rom->read8bit(event_warp_offset++);

        this->warp_events.append(ev);
    }


    for (int i = 0; i < num_scripts; i++)
    {
        scriptEvent ev;
        ev.x = rom->read16bit(event_script_offset);
        event_script_offset += 2;

        ev.y = rom->read16bit(event_script_offset);
        event_script_offset += 2;

        ev.talking_level = rom->read8bit(event_script_offset++);
        ev.unknown1 = rom->read8bit(event_script_offset++);

        ev.var_num = rom->read16bit(event_script_offset);
        event_script_offset += 2;
        ev.var_value = rom->read16bit(event_script_offset);
        event_script_offset += 2;
        ev.unknown2 = rom->read16bit(event_script_offset);
        event_script_offset += 2;

        ev.script_offset = rom->read_offset(event_script_offset);
        event_script_offset += 4;

        this->script_events.append(ev);
    }

    for (int i = 0; i < num_sign_posts; i++)
    {
        signpostEvent ev;
        ev.x = rom->read16bit(event_signpost_offset);
        event_signpost_offset += 2;
        ev.y = rom->read16bit(event_signpost_offset);
        event_signpost_offset += 2;

        ev.talking_level = rom->read8bit(event_signpost_offset++);
        ev.signpost_type = rom->read8bit(event_signpost_offset++);
        ev.unknown = rom->read16bit(event_signpost_offset);
        event_signpost_offset += 2;

        if (ev.signpost_type >= 0 && ev.signpost_type <= 4) //script
        {
            ev.script_offset = rom->read_offset(event_signpost_offset);
            event_signpost_offset += 4;
        }
        else if (ev.signpost_type >= 5 && ev.signpost_type <= 7) //hidden item
        {
            ev.item_id = rom->read16bit(event_signpost_offset);
            event_signpost_offset += 2;
            ev.hidden_id = rom->read8bit(event_signpost_offset++);
            ev.amount = rom->read8bit(event_signpost_offset++);
        }



        this->signpost_events.append(ev);
    }


    //connections
    int num_connections = rom->read8bit(connection_offset);
    int connection_addr = rom->read_offset(connection_offset+4);
    for (int i = 0; i < num_connections; i++)
    {
        connection conn;
        conn.direction = rom->read8bit(connection_addr);
        conn.offset = rom->read32bit_signed(connection_addr+4);
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

QString GBAMap::get_name()
{
    if (this->rom != 0 && this->rom->place_names.length() >= 0 && this->rom->place_names.length() > this->name_index - this->rom->name_index)
    {
        return this->rom->place_names.at(this->name_index - this->rom->name_index);
    }

    return "";
}
