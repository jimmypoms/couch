/*
 * couchproviderlist.cpp
 *
 *  Created on: 3 Aug 2016
 *      Author: jimmypoms
 */

#include "couchproviderlist.h"

CouchProviderList::CouchProviderList(QObject *parent) : QAbstractListModel(parent)
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
    Q_UNUSED(parent);
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
    return QVariant();
}

void CouchProviderList::insert(int row, QObject* source)
{
    beginInsertRows(QModelIndex(), row, row);
    m_providers.insert(row, source);
    endInsertRows();
}

void CouchProviderList::append(const QList<QObject*>& providers)
{
    if (providers.isEmpty()) {
        return;
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + providers.count() - 1);
    m_providers.append(providers);
    endInsertRows();
}

void CouchProviderList::append(QObject* provider)
{
    m_providers.append(provider);
}
