/*
 * couchproviderlist.cpp
 *
 *  Created on: 3 Aug 2016
 *      Author: jimmypoms
 */

#include "couchproviderlist.h"

#include <qvariant.h>

CouchProviderList::CouchProviderList(QObject *parent) :
        QAbstractListModel(parent)
{
}

QHash<int, QByteArray> CouchProviderList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole] = "modelData";
    return roles;
}

int CouchProviderList::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_providers.count();
}

QVariant CouchProviderList::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_providers.count()) {
        return QVariant::Invalid;
    }
    if (Qt::UserRole == role) {
        QObject *item = m_providers[index.row()];
        return QVariant::fromValue(item);
    }
    return QVariant::Invalid;
}

void CouchProviderList::insert(int row, QObject* source)
{
    beginInsertRows(QModelIndex(), row, row);
    m_providers.insert(row, source);
    endInsertRows();
}

void CouchProviderList::append(QObject* provider)
{
    insert(rowCount(), provider);
}

QList<QObject*>::iterator CouchProviderList::begin()
{
    return m_providers.begin();
}

QList<QObject*>::iterator CouchProviderList::end()
{
    return m_providers.end();
}

QList<QObject*>::const_iterator CouchProviderList::cbegin() const
{
    return m_providers.cbegin();
}

QList<QObject*>::const_iterator CouchProviderList::cend() const
{
    return m_providers.cend();
}
