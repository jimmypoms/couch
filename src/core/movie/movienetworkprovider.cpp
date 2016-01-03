/*
 * movienetworkprovider.cpp
 *
 *  Created on: 2 Jan 2016
 *      Author: jimmypoms
 */

#include "movienetworkprovider.h"

MovieNetworkProvider::MovieNetworkProvider(QObject *parent, QString name) :
        NetworkProvider(parent), m_name(name)
{
}

const QString& MovieNetworkProvider::name() const
{
    return m_name;
}
