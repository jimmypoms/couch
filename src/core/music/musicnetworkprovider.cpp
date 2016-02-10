/*
 * musicnetworkprovider.cpp
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#include "musicnetworkprovider.h"

MusicNetworkProvider::MusicNetworkProvider(QObject *parent, QString name) :
        NetworkProvider(parent), m_name(name)
{
}

const QString& MusicNetworkProvider::name() const
{
    return m_name;
}
