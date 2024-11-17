// <one line to give the program's name and a brief idea of what it does.>
// SPDX-FileCopyrightText: 2024 <copyright holder> <email>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "data.h"

Data::Data(uint8_t value, uint8_t minimum, uint8_t maximum)
{
    setRange(minimum, maximum);
    setValue(value);
}

uint8_t Data::value() const
{
    return m_value;
}

void Data::setValue(uint8_t& value)
{
    if (value < m_minimum) value = m_minimum;
    if (value > m_maximum) value = m_maximum;

    if (m_value == value) {
        return;
    }

    m_value = value;
    emit valueChanged(m_value);
}

uint8_t Data::maximum() const
{
    return m_maximum;
}

void Data::setMaximum(uint8_t& maximum)
{
    if (maximum > 99) maximum = 99;

    if (m_maximum == maximum) {
        return;
    }

    m_maximum = maximum;
}

uint8_t Data::minimum() const
{
    return m_minimum;
}

void Data::setMinimum(uint8_t& minimum)
{
    if (minimum < 0) minimum = 0;

    if (m_minimum == minimum) {
        return;
    }

    m_minimum = minimum;
}

void Data::setRange(uint8_t& minimum, uint8_t& maximum)
{
    setMinimum(minimum);
    setMaximum(maximum);
}

Data& Data::operator=(uint8_t& value)
{
    setValue(value);

    return *this;
}
