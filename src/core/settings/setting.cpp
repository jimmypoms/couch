/*
 * setting.cpp
 *
 *  Created on: 19 Mar 2017
 *      Author: jimmypoms
 */

#include "setting.h"

#include <stdexcept>

Setting::Setting(QObject *parent, Type type, QString key, QVariant defaultValue,
        QString title, QString description) :
                QObject(parent), m_type(type), m_key(key), m_defaultValue(defaultValue),
                m_title(title), m_description(description)
{
}

Setting::Type Setting::type() const
{
    return m_type;
}

const QString &Setting::key() const
{
    return m_key;
}

const QString &Setting::title() const
{
    return m_title;
}

const QString &Setting::description() const
{
    return m_description;
}

const QVariant &Setting::defaultValue() const
{
    return m_defaultValue;
}

const QVariant &Setting::value() const
{
    return m_value;
}

void Setting::setValue(const QVariant &value)
{
    if (!isValid(value)) {
        throw std::invalid_argument(QString("invalid type %1: %2")
                .arg(value.typeName())
                .arg(value.toString())
                .toStdString());
    }
    if (m_value != value) {
        m_value = value;
        valueChanged();
    }
}
