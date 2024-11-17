// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef DATA_H
#define DATA_H

#include <QObject>
#include <cstdint>

/**
 * @todo write docs
 */
class Data : public QObject
{
    Q_OBJECT
//    Q_PROPERTY( value READ value WRITE setValue NOTIFY valueChanged)
//    Q_PROPERTY( maximum READ maximum WRITE setMaximum)
//    Q_PROPERTY( minimum READ minimum WRITE setMinimum)

public:

    Data(uint8_t value, uint8_t minimum = 0, uint8_t maximum = 99);
    uint8_t value() const;
    uint8_t minimum() const;
    uint8_t maximum() const;
    void setMaximum(uint8_t& );
    void setMinimum(uint8_t& );
    void setRange(uint8_t& , uint8_t& );
    Data& operator=(uint8_t& );

public Q_SLOTS:
    void setValue(uint8_t& );

Q_SIGNALS:
    void valueChanged(uint8_t& );

private:
     uint8_t m_value;
     uint8_t m_maximum;
     uint8_t m_minimum;
};

#endif // DATA_H
