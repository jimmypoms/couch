/*
 * couchitemlistsortproxy.cpp
 *
 *  Created on: 7 Aug 2016
 *      Author: jimmypoms
 */

#include "couchitemlistsortproxy.h"

#include "couchitemlist.h"
#include "item.h"

#include <qabstractitemmodel.h>
#include <qdebug.h>
#include <qlogging.h>
#include <qobject.h>
#include <memory>

CouchItemListSortProxy::CouchItemListSortProxy(QObject *parent) :
        QSortFilterProxyModel(parent)
{
    setSortRole(Qt::UserRole);
    setDynamicSortFilter(true);
}

bool CouchItemListSortProxy::loading() const
{
    CouchItemList* source = qobject_cast<CouchItemList*>(sourceModel());
    if (source) {
        return source->loading();
    }

    return false;
}

bool CouchItemListSortProxy::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    CouchItemList* source = qobject_cast<CouchItemList*>(sourceModel());
    if (!source) {
        return QSortFilterProxyModel::lessThan(left, right);
    }

    const std::shared_ptr<Item> leftData = source->itemAt(left.row());
    const std::shared_ptr<Item> rightData = source->itemAt(right.row());

    return *leftData < *rightData;
}

QHash<int, QByteArray> CouchItemListSortProxy::roleNames() const
{
    return sourceModel()->roleNames();
}

void CouchItemListSortProxy::setSourceModel(QAbstractItemModel* model)
{
    CouchItemList* source = qobject_cast<CouchItemList*>(model);
    CouchItemList* oldSource = qobject_cast<CouchItemList*>(sourceModel());

    if (oldSource) {
        disconnect(oldSource, &CouchItemList::loadingChanged, this,
                &CouchItemListSortProxy::loadingChanged);
        disconnect(oldSource, &CouchItemList::itemsChanged, this,
                &CouchItemListSortProxy::itemsChanged);
    }

    QSortFilterProxyModel::setSourceModel(model);

    if (source) {
        connect(source, &CouchItemList::loadingChanged, this,
                &CouchItemListSortProxy::loadingChanged);
        connect(source, &CouchItemList::itemsChanged, this, &CouchItemListSortProxy::itemsChanged);
    }

    invalidate();
}

void CouchItemListSortProxy::sort(Qt::SortOrder order)
{
    QSortFilterProxyModel::sort(0, order);
}
