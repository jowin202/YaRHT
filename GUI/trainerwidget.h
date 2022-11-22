#ifndef TRAINERWIDGET_H
#define TRAINERWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

class GBARom;

namespace Ui {
class TrainerWidget;
}

class TrainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrainerWidget(QWidget *parent = nullptr);
    ~TrainerWidget();
    void set_rom(GBARom *rom);

private slots:
    void on_list_trainers_itemActivated(QListWidgetItem *item);

private:
    Ui::TrainerWidget *ui;
    GBARom *rom;
};

#endif // TRAINERWIDGET_H
