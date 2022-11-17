#ifndef POKEMONWIDGET_H
#define POKEMONWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QDebug>

class GBARom;

namespace Ui {
class PokemonWidget;
}

class PokemonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PokemonWidget(QWidget *parent = nullptr);
    ~PokemonWidget();

    void set_rom(GBARom *rom);

private slots:
    void on_list_pokemon_itemActivated(QListWidgetItem *item);

private:
    Ui::PokemonWidget *ui;
    GBARom *rom = 0;
};

#endif // POKEMONWIDGET_H
