#include "connectionlabel.h"
#include "ROM/gbarom.h"
#include "ROM/gbamap.h"

ConnectionLabel::ConnectionLabel(QWidget *parent) : QLabel(parent)
{
}

void ConnectionLabel::setMap(int bank, int map_num, GBARom *rom)
{
    if (rom->maps.length() <= bank)
    {
        qDebug() << "Bank " << bank << " not available";
        return;
    }
    if (rom->maps.at(bank).length() <= map_num)
    {
        qDebug() << "Map " << map_num << " in bank " << bank << " not available";
        return;
    }


    this->rom = rom;
    this->maps.clear();
    this->teleporters.clear();
    GBAMap *map = rom->maps.at(bank).at(map_num);
    int max_up = 0;
    int max_down = 0;
    int max_left = 0;
    int max_right = 0;

    for (int i = 0; i < map->connections.length(); i++)
    {
        connection conn = map->connections.at(i);
        GBAMap *connected_map = rom->maps.at(conn.bank).at(conn.map);

        if (conn.direction == 1) //down
        {
            if (connected_map->height > max_down)
                max_down = connected_map->height;

            if (conn.offset < 0 && (-conn.offset) > max_left)
                max_left = -conn.offset;
            if (connected_map->width - map->width + conn.offset > max_right)
                max_right = connected_map->width - map->width + conn.offset;
        }
        if (conn.direction == 2) //up
        {
            if (connected_map->height > max_up)
                max_up = connected_map->height;


            if (conn.offset < 0 && (-conn.offset) > max_left)
                max_left = -conn.offset;
            if (connected_map->width - map->width + conn.offset > max_right)
                max_right = connected_map->width - map->width + conn.offset;
        }
        if (conn.direction == 3) //left
        {
            if (connected_map->width > max_left)
                max_left = connected_map->width;

            if (conn.offset < 0 && (-conn.offset) > max_up)
                max_up = -conn.offset;
            if (connected_map->height - map->height + conn.offset > max_down)
                max_down = connected_map->height - map->height + conn.offset;
        }
        if (conn.direction == 4) //right
        {
            if (connected_map->width > max_right)
                max_right = connected_map->width;

            if (conn.offset < 0 && (-conn.offset) > max_up)
                max_up = -conn.offset;
            if (connected_map->height - map->height + conn.offset > max_down)
                max_down = connected_map->height - map->height + conn.offset;
        }
    }

    QImage img(16*(map->width + max_left + max_right), 16*(map->height + max_up + max_down), QImage::Format_ARGB32);
    QPainter painter2(&img);
    painter2.fillRect(0,0,img.width(),img.height(), QColor(0,0,0));

    for (int i = 0; i < map->connections.length(); i++)
    {
        connection conn = map->connections.at(i);
        GBAMap *connected_map = rom->maps.at(conn.bank).at(conn.map);
        QRect map_rect;
        if (conn.direction == 1) //down
        {
            painter2.drawImage(16*(max_left + conn.offset),16*(max_up+map->height), connected_map->map_image);
            map_rect = QRect(QPoint(16*(max_left + conn.offset),16*(max_up+map->height)), connected_map->map_image.size());
        }
        else if (conn.direction == 2) //up
        {
            painter2.drawImage(16*(max_left + conn.offset),16*(max_up-connected_map->height), connected_map->map_image);
            map_rect = QRect(QPoint(16*(max_left + conn.offset),16*(max_up-connected_map->height)), connected_map->map_image.size());
        }
        else if (conn.direction == 3) //left
        {
            painter2.drawImage(16*(max_left-connected_map->width), 16*(max_up + conn.offset), connected_map->map_image);
            map_rect = QRect(QPoint(16*(max_left-connected_map->width), 16*(max_up + conn.offset)), connected_map->map_image.size());
        }
        else if (conn.direction == 4) //right
        {
            painter2.drawImage(16*(max_left+map->width), 16*(max_up + conn.offset), connected_map->map_image);
            map_rect = QRect(QPoint(16*(max_left+map->width), 16*(max_up + conn.offset)), connected_map->map_image.size());
        }
        maps.insert(QPair<int,int>(conn.bank,conn.map), map_rect);
    }



    painter2.drawImage(16*max_left, 16*max_up, map->map_image);
    painter2.setOpacity(0.5);
    for (int i = 0; i < map->warp_events.length(); i++)
    {
        warpEvent ev = map->warp_events.at(i);
        QRect warp_field = QRect(16*(ev.x + max_left), 16*(ev.y + max_up), 16, 16);
        if (i == this->target_warper)
            painter2.fillRect(warp_field, Qt::blue);
        else
            painter2.fillRect(warp_field, Qt::green);

        QVector<int> v;
        v.append(ev.target_bank);
        v.append(ev.target_map);
        v.append(ev.target_warp_no);

        this->teleporters.insert(v, warp_field);
    }

    this->target_warper = -1;

    //scroll to chosen map
    if (this->scroll_offset.x() >= 0 && this->scroll_offset.y() >= 0)
    {
        this->scroll_area->horizontalScrollBar()->setValue(16*max_left);
        this->scroll_area->verticalScrollBar()->setValue(16*max_up);
    }
    this->scroll_offset = QPoint(-1,-1);
    painter2.setOpacity(1);

    painter2.end();
    this->setPixmap(QPixmap::fromImage(img));
}

void ConnectionLabel::mousePressEvent(QMouseEvent *ev)
{
    int scroll_x = this->hscroll->value();
    int scroll_y = this->vscroll->value();

    QMapIterator<QVector<int>, QRect> i(teleporters);
    while (i.hasNext())
    {
        i.next();
        if (i.value().contains(ev->pos()))
        {
            this->target_warper = i.key().at(2);
            scroll_offset = QPoint(-1,-1); //avoid scrolling when warp
            this->setMap(i.key().at(0),i.key().at(1), this->rom);
            return;
        }
    }


    QMapIterator<QPair<int,int>, QRect> i2(maps);
    while (i2.hasNext())
    {
        i2.next();
        if (i2.value().contains(ev->pos()))
        {
            this->scroll_offset = QPoint(scroll_x,scroll_y) - i2.value().topLeft();
            qDebug() << this->scroll_offset;
            this->target_warper = -1; //got there by map and not by warper
            this->setMap(i2.key().first,i2.key().second, this->rom);
            return;
        }
    }

}
