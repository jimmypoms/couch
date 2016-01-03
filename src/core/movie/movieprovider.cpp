/*
 * MovieProvider.cpp
 *
 *  Created on: 2 Jan 2016
 *      Author: jimmypoms
 */

#include "movieprovider.h"

MovieProvider::MovieProvider(QObject *parent, QString name) :
        QObject(parent), m_name(name)
{
}

const QString& MovieProvider::name() const
{
    return m_name;
}
