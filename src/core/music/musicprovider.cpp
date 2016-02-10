/*
 * musicprovider.cpp
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#include "musicprovider.h"

MusicProvider::MusicProvider(QObject *parent, QString name) :
        QObject(parent), m_name(name)
{
}

const QString& MusicProvider::name() const
{
    return m_name;
}
