#include <QFile>
#include <QDebug>
#include <QPair>
#include "gbarom.h"
#include "gbamap.h"
#include "gbatileset.h"

GBARom::GBARom()
{
}

void GBARom::set_path(QString path)
{
    this->path = path;
    QFile f(path);
    f.open(QIODevice::ReadOnly);
    this->rom_data = f.readAll();
    f.close();
}

int GBARom::read_offset(int pos)
{
    int num = 0xFF & rom_data.at(pos);
    num |= ((0xFF & rom_data.at(pos+1)) << 8);
    num |= ((0xFF &rom_data.at(pos+2)) << 16);

    if (rom_data.at(pos+3) != 0x08)
        return -1;

    return num;
}

int GBARom::read8bit(int pos)
{
    int num = 0xFF & rom_data.at(pos);
    return num;
}

int GBARom::read16bit(int pos)
{
    int num = 0xFF & rom_data.at(pos);
    num |= ((0xFF & rom_data.at(pos+1)) << 8);

    return num;
}

int GBARom::read24bit(int pos)
{
    int num = 0xFF & rom_data.at(pos);
    num |= ((0xFF & rom_data.at(pos+1)) << 8);
    num |= ((0xFF &rom_data.at(pos+2)) << 16);

    return num;
}

int GBARom::read32bit(int pos)
{
    int num = 0xFF & rom_data.at(pos);
    num |= ((0xFF & rom_data.at(pos+1)) << 8);
    num |= ((0xFF &rom_data.at(pos+2)) << 16);
    num |= ((0xFF &rom_data.at(pos+3)) << 24);

    return num;
}

int GBARom::read32bit_signed(int pos)
{
    int num = 0xFF & rom_data.at(pos);
    num |= ((0xFF & rom_data.at(pos+1)) << 8);
    num |= ((0xFF &rom_data.at(pos+2)) << 16);
    num |= ((0xFF &rom_data.at(pos+3)) << 24);

    if ((0xFF &rom_data.at(pos+3) >> 3) > 0)
    {
        num ^= 0xFFFFFFFF;
        num += 1;
        num = -num;
    }
    return num;
}

QByteArray GBARom::decompress(int offset)
{
    int length = this->read24bit(offset+1);
    QByteArray result(length, '\0');
    int dest_pos = 0;
    offset += 4;

    while (true)
    {
        int flags = this->read8bit(offset); offset++;

        for (int i = 0; i < 8; i++)
        {
            if ((flags & 0x80) != 0)
            {
                int v1 = this->read8bit(offset); offset++;
                int v2 = this->read8bit(offset); offset++;

                int size = (v1 >> 4) + 3;
                int dist = ((v1 & 0xF) << 8 | v2) + 1;

                int pos = dest_pos - dist;

                if (dest_pos + size > length)
                {
                    //should not happen
                    size = length - dest_pos;
                }

                if (pos < 0)
                {
                    qDebug() << "TODO: compression error";
                    exit(1);
                }

                for (int j = 0; j < size; j++)
                {
                    result[dest_pos] = result[pos+j];
                    dest_pos++;
                }
            }
            else
            {
                result[dest_pos] = this->read8bit(offset); offset++;
                dest_pos++;
            }
            flags <<= 1;
            if (dest_pos == length)
                return result;
        }
    }


}

QString GBARom::readText(int pos, int len)
{
    QString result = "";
    for (int i = 0; i < len; i++)
    {
        int c = this->read8bit(pos++);
        if (c >= 0xbb && c <= 0xd4)
            result += QChar(c - 0xbb + 'A');
        else if (c >= 0xd5 && c <= 0xef)
            result += QChar(c - 0xd5 + 'a');
        else if (c >= 0xa1 && c <= 0xaa)
            result += QChar(c - 0xa1 + '0');
        else if (c == 0xfe)
            result += "\n";
        else if (c == 0xb8)
            result += ",";
        else if (c == 0x1b)
            result += "é"; //pokemon e
        else if (c == 0xad)
            result += ".";
        else if (c == 0xae)
            result += "-";
        else if (c == 0xb3 || c == 0xb4)
            result += "\'";
        else if (c == 0x00)
            result += " ";
        else if (c == 0xFF)
            result += "\n-----------\n"; //TODO: readArray where 0xFF is separator
    }

    return result;
}

QString GBARom::readText_until_FF(int pos)
{
    int i = 0;
    while (this->read8bit(pos+i) != 0xFF)
        i++;
    return this->readText(pos,i);
}

int GBARom::find_start_of_text(int pos)
{
    int c;
    do
    {
        c = this->rom_data[pos--] & 0xFF;
    } while((c >= 0xbb && c <= 0xef) || (c >= 0xa1 && c <= 0xaa) ||
            c == 0x00 || c == 0xFF || c == 0xFE || c == 0x1B
            || c == 0xB8 || c == 0xAD || c == 0xAE || c == 0xB4 || c == 0xB3);
    qDebug() << "start: " << QString::number(c,16);
    return pos;
}

int GBARom::find_end_of_text(int pos)
{

    int c;
    do
    {
        c = this->rom_data[pos++]  & 0xFF;
    } while((c >= 0xbb && c <= 0xef) || (c >= 0xa1 && c <= 0xaa) ||
            c == 0x00 || c == 0xFF || c == 0xFE || c == 0x1B
            || c == 0xB8 || c == 0xAD || c == 0xAE || c == 0xB4 || c == 0xB3);
    qDebug() << "end: " << QString::number(c,16);
    return pos;
}

void GBARom::find_banks(int offset)
{
    this->register_offset(offset);
    this->map_bank_header_offset = offset;
    if (offset > 0)
    {
        int addr;
        while ((addr = this->read_offset(offset)) != -1)
        {
            this->register_offset(addr);
            this->bank_offsets.append(addr);
            offset += 4;
        }
    }
}

void GBARom::find_maps()
{
    int min = 255;
    int max = 0;
    for (int i = 0; i < bank_offsets.length(); i++)
    {
        QList<GBAMap*> list;
        int offset = bank_offsets.at(i);
        //TODO
        while (offset != this->map_bank_header_offset
               && offset != (i+1 < bank_offsets.length() ? bank_offsets[i+1] : 16777216)
               && this->read_offset(offset) != -1) //break if invalid offset
        {
            GBAMap *map = new GBAMap(this->read_offset(offset), this);
            list.append(map);
            offset += 4;
            if (map->name_index < min) min = map->name_index;
            if (map->name_index > max) max = map->name_index;
        }
        maps.append(list);
    }
    this->name_index = min;
    this->num_names = max-min;
}

void GBARom::find_names(int offset)
{
    if (num_names <= 0) return;
    for (int i = 0; i < num_names; i++)
    {
        int name_offset = this->read_offset(offset);
        place_names << this->readText_until_FF(name_offset);
        offset += 4;
    }
}

void GBARom::register_offset(int offset)
{
    if (offsets.length() == 0) offsets.append(offset);
    if (offsets.contains(offset)) return;

    for (int i = 0; i < offsets.length(); i++)
    {
        if (offsets.at(i) > offset)
        {
            offsets.insert(i,offset);
            return;
        }
    }
    offsets.append(offset); //if reached, its on last position
}

int GBARom::bytes_to_next_offset(int offset)
{
    for (int i = 0; i < offsets.length(); i++)
    {
        if (offsets.at(i) > offset)
            return offsets.at(i)-offset;
    }
    return 0;
}


