#ifndef ENCOUNTERWIDGET_H
#define ENCOUNTERWIDGET_H

#include <QWidget>
#include <QDebug>

class GBARom;

namespace Ui {
class EncounterWidget;
}

class EncounterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EncounterWidget(QWidget *parent = nullptr);
    ~EncounterWidget();

    void display_encounters(int bank, int map, GBARom *rom);
    QString pokemon_name(int n);

private:
    Ui::EncounterWidget *ui;
    GBARom *rom = 0;
};

#endif // ENCOUNTERWIDGET_H
