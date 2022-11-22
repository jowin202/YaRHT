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

void TrainerWidget::on_list_trainers_itemActivated(QListWidgetItem *item)
{
    Q_UNUSED(item);
    GBATrainer *current_trainer = rom->trainers.at(this->ui->list_trainers->currentRow());
    this->ui->line_name->setText(current_trainer->name);
    this->ui->line_class->setText(current_trainer->get_class_string());

    this->ui->text_party->clear();
    this->ui->text_party->appendPlainText(QString::number(current_trainer->party_offset,16));
    this->ui->text_party->appendPlainText(current_trainer->party_as_string());

}
