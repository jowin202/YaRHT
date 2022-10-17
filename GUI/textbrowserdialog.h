#ifndef TEXTBROWSERDIALOG_H
#define TEXTBROWSERDIALOG_H

#include <QWidget>

namespace Ui {
class TextBrowserDialog;
}

class GBARom;
class TextBrowserDialog : public QWidget
{
    Q_OBJECT

public:
    explicit TextBrowserDialog(GBARom *rom, QWidget *parent = nullptr);
    ~TextBrowserDialog();


private slots:
    void on_button_max_text_clicked();
    void on_spin_offset_valueChanged(int arg1);
    void on_spin_bytes_valueChanged(int arg1);

private:
    Ui::TextBrowserDialog *ui;
    GBARom *rom;
};

#endif // TEXTBROWSERDIALOG_H
