#include "trainerwidget.h"
#include "ui_trainerwidget.h"

#include "ROM/gbarom.h"
#include "ROM/gbatrainer.h"

TrainerWidget::TrainerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainerWidget)
{
    ui->setupUi(this);
}

TrainerWidget::~TrainerWidget()
{
    delete ui;
}

void TrainerWidget::set_rom(GBARom *rom)
{
    this->rom = rom;

    this->ui->list_trainers->clear();

    for (int i = 0; i < rom->trainers.length(); i++)
    {
        this->ui->list_trainers->addItem(QString("%1: %2").arg(i,3,10,QChar('0')).arg(rom->trainers.at(i)->get_full_name()));
    }
}
