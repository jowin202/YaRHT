#include "pokemonwidget.h"
#include "ui_pokemonwidget.h"

PokemonWidget::PokemonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PokemonWidget)
{
    ui->setupUi(this);
}

PokemonWidget::~PokemonWidget()
{
    delete ui;
}
