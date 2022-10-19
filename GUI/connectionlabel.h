#ifndef CONNECTIONLABEL_H
#define CONNECTIONLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>

class GBARom;
class ConnectionLabel : public QLabel
{
    Q_OBJECT
public:
    ConnectionLabel(QWidget *parent);

    void setMap(int bank, int map_num, GBARom *rom);
    void mousePressEvent(QMouseEvent *ev);

    QMap<QPair<int,int>,QRect> maps;
    GBARom *rom;

};

#endif // CONNECTIONLABEL_H
