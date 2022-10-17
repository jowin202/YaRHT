#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QTreeWidgetItem>

#include "ROM/gbarom.h"
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
    void on_button_find_offsets_clicked();

    void on_button_browse_clicked();

    void on_button_import_clicked();

    void on_map_tree_itemActivated(QTreeWidgetItem *item, int column);

    void on_button_find_map_names_clicked();

private:
    Ui::MainWindow *ui;
    GBARom rom;
};
#endif // MAINWINDOW_H
