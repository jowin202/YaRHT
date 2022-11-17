#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QTreeWidgetItem>

#include "ROM/gbarom.h"
#include "ROM/gbaoffsetfinder.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void dragEnterEvent(QDragEnterEvent *e)
    {
        if (e->mimeData()->hasUrls())
            e->acceptProposedAction();
    }
    void dropEvent(QDropEvent *event);


private slots:

    void on_button_browse_clicked();

    void on_button_import_clicked();

    void on_map_tree_itemActivated(QTreeWidgetItem *item, int column);

    void on_button_find_map_names_clicked();

    void on_button_name_FR_LG_clicked();
    void on_button_find_bank_offsets_clicked();

    void on_map_tree_itemExpanded(QTreeWidgetItem *item);

    void on_button_find_pokemon_name_offset_clicked();

    void on_button_find_encounter_offset_clicked();

    void on_button_trainer_offset_clicked();

    void on_button_move_name_offset_clicked();

    void on_button_find_front_sprite_offset_clicked();

    void on_button_find_back_sprite_offset_clicked();

    void on_button_find_palette_clicked();

    void on_button_find_shiny_palette_clicked();

    void on_button_find_icon_offset_clicked();

    void on_button_find_icon_palette_offset_clicked();

    void on_button_find_footprint_offset_clicked();

    void on_button_find_base_stats_offset_clicked();

    void on_button_find_evolution_clicked();

    void on_button_find_all_offsets_clicked();


private:
    Ui::MainWindow *ui;
    GBARom rom;
    GBAOffsetFinder offset_finder;
};
#endif // MAINWINDOW_H
