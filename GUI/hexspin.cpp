#include "hexspin.h"

HexSpin::HexSpin(QWidget *parent) : QSpinBox(parent)
{
    this->setDisplayIntegerBase(16);
    this->setMaximum(m_maxRange);
    this->setMinimum(0);
}



QString HexSpin::textFromValue(int value) const
{
    int fillField = 0;
    if (m_fillField) {
        uint m = m_maxRange;
        while (m) {
            m >>= 4;
            ++fillField;
        }
    }
    return QString("%1").arg(u(value), fillField, 16, QLatin1Char('0')).toUpper();
}

int HexSpin::valueFromText(const QString &text) const
{
    return i(text.toUInt(nullptr, 16));
}

QValidator::State HexSpin::validate(QString &input, int &pos) const
{
    QString copy(input);
    QString pref = prefix();
    if (copy.startsWith(pref))
        copy.remove(pref);
    pos -= copy.size() - copy.trimmed().size();
    copy = copy.trimmed();
    if (copy.isEmpty())
        return QValidator::Intermediate;
    input = pref + copy.toUpper();
    bool okay;
    unsigned int val = copy.toUInt(&okay, 16);
    if (!okay || val > m_maxRange)
        return QValidator::Invalid;
    return QValidator::Acceptable;
}
