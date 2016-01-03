/*
 * couchlist.cpp
 *
 *  Created on: 15 Oct 2015
 *      Author: jimmypoms
 */

#include "couchitemlist.h"

#include <qglobal.h>
#include <quuid.h>
#include <qvariant.h>
#include <algorithm>

#include "item.h"
#include "service.h"

CouchItemList::CouchItemList(const Service *service, QString id) :
        m_id(id), m_loadingCount(service->providers().count()), m_loaded(0)
{
    if (m_id.isEmpty()) {
        m_id = QUuid::createUuid().toString();
    }
}

const QString &CouchItemList::id() const
{
    return m_id;
}

bool CouchItemList::loading() const
{
    return m_loadingCount > m_loaded;
}

QHash<int, QByteArray> CouchItemList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole] = "modelData";
    return roles;
}

int CouchItemList::rowCount(const QModelIndex& parent) const
        {
    Q_UNUSED(parent);
    return m_items.count();
}

QVariant CouchItemList::data(const QModelIndex& index, int role) const
        {
    if (index.row() < 0 || index.row() >= m_items.count()) {
        return QVariant();
    }
    if (Qt::UserRole == role) {
        QObject *item = m_items[index.row()].get();
        return QVariant::fromValue(item);
    }
    return QVariant();
}

void CouchItemList::addItems(const QList<std::shared_ptr<Item> > &items, const QString &id)
{
    if (!id.isEmpty() && id != m_id) {
        return;
    }

    bool added = false;
    for (const auto item : items) {
        auto it = std::find_if(m_items.cbegin(), m_items.cend(),
                [&item](std::shared_ptr<Item> i)->bool {
                    return *item == *i;
                });
        if (it == m_items.cend()) {
            added = true;
            append(item);
        }
    }
    Q_EMIT itemsLoaded();
    if (added) {
        Q_EMIT itemsChanged();
    }

    bool isLoading = loading();
    ++m_loaded;
    if (isLoading != loading()) {
        Q_EMIT loadingChanged();
    }
}

void CouchItemList::insert(int row, const std::shared_ptr<Item> &item)
{
    beginInsertRows(QModelIndex(), row, row);
    m_items.insert(row, item);
    endInsertRows();
}

void CouchItemList::append(const QList<std::shared_ptr<Item> >& items)
{
    if (items.isEmpty()) {
        return;
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + items.count() - 1);
    m_items.append(items);
    endInsertRows();
}

void CouchItemList::append(const std::shared_ptr<Item> &item)
{
    insert(rowCount(), item);
}
