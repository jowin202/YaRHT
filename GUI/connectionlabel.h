#ifndef CONNECTIONLABEL_H
#define CONNECTIONLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>

#include <QScrollArea>
#include <QScrollBar>

class GBARom;
class ConnectionLabel : public QLabel
{
    Q_OBJECT
public:
    ConnectionLabel(QWidget *parent);

    void setMap(int bank, int map_num, GBARom *rom);
    void mousePressEvent(QMouseEvent *ev);

    QMap<QPair<int,int>,QRect> maps;
    QMultiMap<QVector<int>, QRect> teleporters;
    GBARom *rom;


    //marker for navigation through warpers
    int target_warper = -1;

    //scroll information for navigation through map connectors
    QPoint scroll_offset = QPoint(-1,-1);



    void set_scroll_area(QScrollArea *area) { this->scroll_area = area; this->hscroll = area->horizontalScrollBar(); this->vscroll = area->verticalScrollBar(); }
    QScrollArea *scroll_area;
    QScrollBar *hscroll;
    QScrollBar *vscroll;

};

#endif // CONNECTIONLABEL_H
