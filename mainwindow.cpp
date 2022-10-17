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
            bank->addChild(new QTreeWidgetItem(QStringList(QString::number(j))));
        banks->addChild(bank);
    }

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
    //TODO Fix it
    int max_up = 0;
    int max_down = 0;
    int max_left = 0;
    int max_right = 0;
    for (int i = 0; i < map->connections.length(); i++)
    {
        connection conn = map->connections.at(i);
        if (conn.direction == 1) //down
        {
            if (rom.maps.at(conn.bank).at(conn.map)->height > max_down)
                max_down = rom.maps.at(conn.bank).at(conn.map)->height;
        }
        if (conn.direction == 2) //up
        {
            if (rom.maps.at(conn.bank).at(conn.map)->height > max_up)
                max_up = rom.maps.at(conn.bank).at(conn.map)->height;
        }
        if (conn.direction == 3) //left
        {
            if (rom.maps.at(conn.bank).at(conn.map)->width > max_left)
                max_left = rom.maps.at(conn.bank).at(conn.map)->width;
        }
        if (conn.direction == 4) //right
        {
            if (rom.maps.at(conn.bank).at(conn.map)->width > max_right)
                max_right = rom.maps.at(conn.bank).at(conn.map)->width;
        }
    }

    QImage img(16*(map->width + max_left + max_right), 16*(map->height + max_up + max_down), QImage::Format_ARGB32);
    QPainter painter2(&img);
    painter2.fillRect(0,0,img.width(),img.height(), QColor(0,0,0));

    for (int i = 0; i < map->connections.length(); i++)
    {
        connection conn = map->connections.at(i);
        qDebug() << conn.direction << conn.bank << conn.map;
        if (conn.direction == 1) //down
            painter2.drawImage(16*(max_left + conn.offset),16*(max_up+map->height), rom.maps.at(conn.bank).at(conn.map)->map_image);
        else if (conn.direction == 2) //up
            painter2.drawImage(16*(max_left + conn.offset),16*(max_up-rom.maps.at(conn.bank).at(conn.map)->height), rom.maps.at(conn.bank).at(conn.map)->map_image);
        else if (conn.direction == 3) //left
            painter2.drawImage(16*(max_left-rom.maps.at(conn.bank).at(conn.map)->width), 16*(max_up + conn.offset), rom.maps.at(conn.bank).at(conn.map)->map_image);
        else if (conn.direction == 4) //right
            painter2.drawImage(16*(max_left+map->width), 16*(max_up + conn.offset), rom.maps.at(conn.bank).at(conn.map)->map_image);
    }

    painter2.drawImage(16*max_left, 16*max_up, map->map_image);
    painter2.end();
    this->ui->connections_label->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::on_button_find_map_names_clicked()
{
    TextBrowserDialog *dialog = new TextBrowserDialog(&this->rom);
    dialog->show();
}
