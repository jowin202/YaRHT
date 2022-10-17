#ifndef HEXSPIN_H
#define HEXSPIN_H

#include <QObject>
#include <QWidget>
#include <QSpinBox>

class HexSpin : public QSpinBox
{
    Q_OBJECT
public:
    HexSpin(QWidget *parent);


    unsigned int hexValue() const { return u(value()); }
    void setHexValue(unsigned int value) { setValue(i(value)); }
    bool fillField() const { return m_fillField; }
    void setFillField(bool fillFieldWidth) { m_fillField = fillFieldWidth; }

protected:
    QString textFromValue(int value) const;
    int valueFromText(const QString &text) const;
    QValidator::State validate(QString &input, int &pos) const;


private:
    unsigned int m_maxRange = 16777215;
    bool m_fillField = true;
    inline unsigned int u(int i) const { return *reinterpret_cast<unsigned int *>(&i); }
    inline int i(unsigned int u) const { return *reinterpret_cast<int *>(&u); }
};

#endif // HEXSPIN_H
