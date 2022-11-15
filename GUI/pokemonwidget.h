#ifndef POKEMONWIDGET_H
#define POKEMONWIDGET_H

#include <QWidget>

namespace Ui {
class PokemonWidget;
}

class PokemonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PokemonWidget(QWidget *parent = nullptr);
    ~PokemonWidget();

private:
    Ui::PokemonWidget *ui;
};

#endif // POKEMONWIDGET_H
