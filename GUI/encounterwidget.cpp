#include "encounterwidget.h"
#include "ui_encounterwidget.h"

#include "ROM/gbarom.h"
#include "ROM/gbaencounter.h"

EncounterWidget::EncounterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EncounterWidget)
{
    ui->setupUi(this);
}

EncounterWidget::~EncounterWidget()
{
    delete ui;
}

void EncounterWidget::display_encounters(int bank, int map, GBARom *rom)
{
    this->rom = rom;
    this->ui->plainTextEdit->clear();

    GBAEncounter *enc = this->rom->encounters.value(QPair<int,int>(bank,map), nullptr);
    if (enc == nullptr) return;

    this->ui->plainTextEdit->appendPlainText(QString("Grass Encounter Ratio: %1").arg(enc->grass_encounter_ratio));
    for (int i = 0; i < enc->grass_encounter.length(); i++)
    {
        this->ui->plainTextEdit->appendPlainText(QString("%1 %2: %3 (%4)").arg(enc->grass_encounter.at(i).from_level)
                                                 .arg(enc->grass_encounter.at(i).to_level)
                                                 .arg(enc->grass_encounter.at(i).species)
                                                 .arg(pokemon_name(enc->grass_encounter.at(i).species)));
    }

    this->ui->plainTextEdit->appendPlainText("\n\n\n");
    this->ui->plainTextEdit->appendPlainText(QString("Water Encounter Ratio: %1").arg(enc->water_encounter_ratio));
    for (int i = 0; i < enc->water_encounter.length(); i++)
    {
        this->ui->plainTextEdit->appendPlainText(QString("%1 %2: %3 (%4)").arg(enc->water_encounter.at(i).from_level)
                                                 .arg(enc->water_encounter.at(i).to_level)
                                                 .arg(enc->water_encounter.at(i).species)
                                                 .arg(pokemon_name(enc->water_encounter.at(i).species)));
    }


    this->ui->plainTextEdit->appendPlainText("\n\n\n");
    this->ui->plainTextEdit->appendPlainText(QString("Rocksmash Encounter Ratio: %1").arg(enc->rocksmash_encounter_ratio));
    for (int i = 0; i < enc->rocksmash_encounter.length(); i++)
    {
        this->ui->plainTextEdit->appendPlainText(QString("%1 %2: %3 (%4)").arg(enc->rocksmash_encounter.at(i).from_level)
                                                 .arg(enc->rocksmash_encounter.at(i).to_level)
                                                 .arg(enc->rocksmash_encounter.at(i).species)
                                                 .arg(pokemon_name(enc->rocksmash_encounter.at(i).species)));
    }

    this->ui->plainTextEdit->appendPlainText("\n\n\n");
    this->ui->plainTextEdit->appendPlainText(QString("Fishingrod Encounter Ratio: %1").arg(enc->fishingrod_encounter_ratio));
    for (int i = 0; i < enc->fishingrod_encounter.length(); i++)
    {
        this->ui->plainTextEdit->appendPlainText(QString("%1 %2: %3 (%4)").arg(enc->fishingrod_encounter.at(i).from_level)
                                                 .arg(enc->fishingrod_encounter.at(i).to_level)
                                                 .arg(enc->fishingrod_encounter.at(i).species)
                                                 .arg(pokemon_name(enc->fishingrod_encounter.at(i).species)));
    }

}

QString EncounterWidget::pokemon_name(int n)
{
    if (rom == 0) return "";
    if (n > 0 && n <= rom->pokemon_names.length())
        return rom->pokemon_names.at(n-1);
    return "";
}
