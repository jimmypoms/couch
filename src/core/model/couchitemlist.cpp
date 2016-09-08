/*
 * couchlist.cpp
 *
 *  Created on: 15 Oct 2015
 *      Author: jimmypoms
 */

#include "couchitemlist.h"

#include "item.h"
#include "itemmetadata.h"

#include <qalgorithms.h>
#include <qglobal.h>
#include <quuid.h>
#include <qvariant.h>
#include <algorithm>

CouchItemList::CouchItemList(int loadingCount, QString id) :
        m_id(id), m_loadingCount(loadingCount), m_loaded(0)
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

const std::shared_ptr<Item> &CouchItemList::itemAt(int index) const
{
    return m_items.at(index);
}

QHash<int, QByteArray> CouchItemList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole] = "modelData";
    return roles;
}

int CouchItemList::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_items.count();
}

QVariant CouchItemList::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count()) {
        return QVariant::Invalid;
    }
    if (Qt::UserRole == role) {
        QObject *item = m_items[index.row()].get();
        return QVariant::fromValue(item);
    }
    return QVariant::Invalid;
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

void CouchItemList::append(const std::shared_ptr<Item> &item)
{
    insert(rowCount(), item);
}

QList<std::shared_ptr<Item> >::const_iterator CouchItemList::cbegin()
{
    return m_items.cbegin();
}

QList<std::shared_ptr<Item> >::const_iterator CouchItemList::cend()
{
    return m_items.cend();
}

SortedCouchItemList::SortedCouchItemList(int loadingCount, QString id, Qt::SortOrder order) :
        CouchItemList(loadingCount, id), m_order(order)
{
}

void SortedCouchItemList::insert(int row, const std::shared_ptr<Item>& item)
{
    Q_UNUSED(row);
    QList<std::shared_ptr<Item> >::const_iterator i;
    auto lessThan = [item](const std::shared_ptr<Item>& left, const std::shared_ptr<Item>& right) -> bool {
        return left->metadata()->lessThan(right->metadata());
    };
    if (m_order == Qt::AscendingOrder) {
        i = qLowerBound(m_items.cbegin(), m_items.cend(), item, lessThan);
    } else {
        i = qUpperBound(m_items.cbegin(), m_items.cend(), item, lessThan);
    }
    int index = i - m_items.cbegin();
    beginInsertRows(QModelIndex(), index, index);
    m_items.insert(index, item);
    endInsertRows();
}
