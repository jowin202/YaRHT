#include "textbrowserdialog.h"
#include "ui_textbrowserdialog.h"

#include "ROM/gbarom.h"

TextBrowserDialog::TextBrowserDialog(GBARom *rom, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextBrowserDialog)
{
    ui->setupUi(this);
    this->rom = rom;
}

TextBrowserDialog::~TextBrowserDialog()
{
    delete ui;
}


void TextBrowserDialog::on_button_max_text_clicked()
{
    int start = this->rom->find_start_of_text(this->ui->spin_offset->value());
    int end = this->rom->find_end_of_text(this->ui->spin_offset->value()
                                          + this->ui->spin_bytes->value());
    int len = end-start;

    this->ui->spin_offset->setValue(start);
    this->ui->spin_bytes->setValue(len);
}

void TextBrowserDialog::on_spin_offset_valueChanged(int arg1)
{
    QString text = this->rom->readText(arg1, this->ui->spin_bytes->value());
    this->ui->plainTextEdit->setPlainText(text);
}

void TextBrowserDialog::on_spin_bytes_valueChanged(int arg1)
{
    QString text = this->rom->readText(this->ui->spin_offset->value(), arg1);
    this->ui->plainTextEdit->setPlainText(text);
}
