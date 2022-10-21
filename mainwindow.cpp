#include <QFileDialog>

#include "GUI/textbrowserdialog.h"

#include "ROM/gbamap.h"
#include "ROM/gbatileset.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::dropEvent(QDropEvent *event)
{
const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();

        if (urlList.length() == 1)
        {
            this->ui->line_path->setText(urlList.first().toLocalFile());
            this->on_button_find_offsets_clicked();
        }
    }
}

void MainWindow::on_button_find_offsets_clicked()
{
    rom.set_path(this->ui->line_path->text());
    int offset = rom.find_bank_header_offset();
    this->ui->spin_map_bank_header_offset->setValue(offset);
}

void MainWindow::on_button_browse_clicked()
{
    this->ui->line_path->setText(QFileDialog::getOpenFileName(this, "Choose ROM", QDir::homePath(), "*.gba"));
}

void MainWindow::on_button_import_clicked()
{
    this->rom.find_banks(this->ui->spin_map_bank_header_offset->value());
    this->rom.find_maps();


    QTreeWidgetItem *banks = new QTreeWidgetItem(QStringList("Banks"));
    this->ui->map_tree->addTopLevelItem(banks);
    for (int i = 0; i < this->rom.maps.length(); i++)
    {
        QTreeWidgetItem *bank = new QTreeWidgetItem(QStringList(QString::number(i)));
        for (int j = 0; j < this->rom.maps.at(i).length(); j++)
        {
            bank->addChild(new QTreeWidgetItem(QStringList(QString::number(j))));
        }
        banks->addChild(bank);
    }

    /*
    for (int i = 0; i < rom.maps.at(3).at(3)->person_events.length(); i++)
    {
        qDebug() << QString::number(rom.maps.at(3).at(3)->person_events.at(i).script_offset,16);
    }
    */

    /*
    for (int i = 0; i < rom.maps.at(3).at(3)->warp_events.length(); i++)
    {
        qDebug() << QString("(%1,%2) to warp: %3, bank: %4, map: %5")
                    .arg(rom.maps.at(3).at(3)->warp_events.at(i).x,0,16)
                    .arg(rom.maps.at(3).at(3)->warp_events.at(i).y,0,16)
                    .arg(rom.maps.at(3).at(3)->warp_events.at(i).target_warp_no,0,16)
                    .arg(rom.maps.at(3).at(3)->warp_events.at(i).target_bank,0,16)
                    .arg(rom.maps.at(3).at(3)->warp_events.at(i).target_map,0,16);
    }
    */
    /*
    for (int i = 0; i < rom.maps.at(3).at(3)->script_events.length(); i++)
    {
        qDebug() << QString::number(rom.maps.at(3).at(3)->script_events.at(i).script_offset,16);
    }
    */


    /*
    for (int i = 0; i < rom.maps.at(3).at(3)->signpost_events.length(); i++)
    {
        if (rom.maps.at(3).at(3)->signpost_events.at(i).signpost_type >= 0 &&
                rom.maps.at(3).at(3)->signpost_events.at(i).signpost_type <= 4)
            qDebug() << QString("(%1,%2)").arg(rom.maps.at(3).at(3)->signpost_events.at(i).x,0,16).arg(rom.maps.at(3).at(3)->signpost_events.at(i).y,0,16) +
                    QString::number(rom.maps.at(3).at(3)->signpost_events.at(i).script_offset,16);
        else
            qDebug() << QString("(%1,%2) ").arg(rom.maps.at(3).at(3)->signpost_events.at(i).x,0,16).arg(rom.maps.at(3).at(3)->signpost_events.at(i).y,0,16) +
                    QString::number(rom.maps.at(3).at(3)->signpost_events.at(i).item_id,16) + " " +
                        QString::number(rom.maps.at(3).at(3)->signpost_events.at(i).hidden_id,16) + " " +
                        QString::number(rom.maps.at(3).at(3)->signpost_events.at(i).amount,16);
    }
    */


}

void MainWindow::on_map_tree_itemActivated(QTreeWidgetItem *item, int column)
{
    if (column < 0) return;
    if (item->parent() == 0) return;
    if (item->parent()->parent() == 0) return;

    int m = item->text(0).toInt();
    int bank = item->parent()->text(0).toInt();
    GBAMap *map = rom.maps.at(bank).at(m);

    //Tileset
    this->ui->tileset_label->setPixmap(QPixmap::fromImage(map->tileset->tileset_image));

    //Map Tab1
    this->ui->map_label->setPixmap(QPixmap::fromImage(map->map_image));

    //Passages Tab2
    QImage passages = map->map_image.copy();
    QPainter painter(&passages);
    int i = 0;
    for (int y = 0; y < passages.height()/16; y++)
    {
        for (int x = 0; x < passages.width()/16; x++)
        {
            int pvalue = map->passages.at(i++);
            painter.setOpacity(0.6);
            QColor col(0,0,255);
            col.setHsl(360/64*pvalue,col.saturation(),col.lightness());
            painter.fillRect(QRect(16*x,16*y,16,16), col);
            painter.setOpacity(1);
            painter.drawText(QRect(16*x,16*y,16,16),Qt::AlignHCenter | Qt::AlignVCenter, QString::number(pvalue,16));
        }
    }
    painter.end();
    this->ui->passages_label->setPixmap(QPixmap::fromImage(passages));



    //Connections Tab3
    this->ui->connections_label->setMap(bank, m, &rom);

}

void MainWindow::on_button_find_map_names_clicked()
{
    TextBrowserDialog *dialog = new TextBrowserDialog(&this->rom);
    dialog->show();
}
