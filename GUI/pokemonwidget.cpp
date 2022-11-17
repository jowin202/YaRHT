#include "pokemonwidget.h"
#include "ui_pokemonwidget.h"

#include "ROM/gbarom.h"
#include "ROM/gbapokemon.h"

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

void PokemonWidget::set_rom(GBARom *rom)
{
    this->rom = rom;
    this->ui->list_pokemon->clear();

    for (int i = 1; i < rom->pokemons.length(); i++)
    {
        this->ui->list_pokemon->addItem(QString("%1: ").arg(i,3,10, QChar('0')) + rom->pokemons.at(i)->get_name());
    }

}

void PokemonWidget::on_list_pokemon_itemActivated(QListWidgetItem *item)
{
    Q_UNUSED(item);

    if (rom == 0) return;

    int n = this->ui->list_pokemon->currentRow()+1;

    if (n >= rom->pokemons.length()) return;
    GBAPokemon *pokemon = rom->pokemons.at(n);

    this->ui->label_sprite_front->setPixmap(QPixmap::fromImage(pokemon->front_sprite));
    this->ui->label_sprite_back->setPixmap(QPixmap::fromImage(pokemon->back_sprite));
    this->ui->label_sprite_front_shiny->setPixmap(QPixmap::fromImage(pokemon->front_sprite_shiny));
    this->ui->label_sprite_back_shiny->setPixmap(QPixmap::fromImage(pokemon->back_sprite_shiny));

    this->ui->line_hp->setText(QString::number(pokemon->base_hp));
    this->ui->line_atk->setText(QString::number(pokemon->base_atk));
    this->ui->line_def->setText(QString::number(pokemon->base_def));
    this->ui->line_speed->setText(QString::number(pokemon->base_speed));


    this->ui->line_sp_atk->setText(QString::number(pokemon->sp_atk));
    this->ui->line_sp_def->setText(QString::number(pokemon->sp_def));
    this->ui->line_catch_rate->setText(QString::number(pokemon->catch_rate));
    this->ui->line_exp->setText(QString::number(pokemon->yield_exp));


    this->ui->line_type_1->setText(QString::number(pokemon->type1));
    this->ui->line_egg_group_1->setText(QString::number(pokemon->egg_group1));
    this->ui->line_egg_steps->setText(QString::number(pokemon->egg_cycles));

    this->ui->line_type_2->setText(QString::number(pokemon->type2));
    this->ui->line_egg_group_2->setText(QString::number(pokemon->egg_group2));
    this->ui->line_gender_ratio->setText(QString::number(pokemon->gender_ratio));

}
