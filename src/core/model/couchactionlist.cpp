/*
 * couchactionlist.cpp
 *
 *  Created on: 23 Jan 2016
 *      Author: jimmypoms
 */

#include "couchactionlist.h"

#include "couchaction.h"
#include "service.h"

#include <qglobal.h>
#include <quuid.h>
#include <qvariant.h>

CouchActionList::CouchActionList(const Service* service, QString id) :
        m_id(id), m_loadingCount(service->providers().count()), m_loaded(0)
{
    if (m_id.isEmpty()) {
        m_id = QUuid::createUuid().toString();
    }
}

const QString& CouchActionList::id() const
{
    return m_id;
}

bool CouchActionList::loading() const
{
    return m_loadingCount > m_loaded;
}

QHash<int, QByteArray> CouchActionList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole] = "modelData";
    return roles;
}

int CouchActionList::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_actions.count();
}

QVariant CouchActionList::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_actions.count()) {
        return QVariant();
    }
    if (Qt::UserRole == role) {
        QObject *action = m_actions[index.row()].get();
        return QVariant::fromValue(action);
    }
    return QVariant();
}

void CouchActionList::addActions(const QList<std::shared_ptr<CouchAction> >& actions,
        const QString& id)
{
    if (!id.isEmpty() && id != m_id) {
        return;
    }

    for (const auto action : actions) {
        append(action);
    }
    Q_EMIT actionsLoaded();
    Q_EMIT actionsChanged();

    bool isLoading = loading();
    ++m_loaded;
    if (isLoading != loading()) {
        Q_EMIT loadingChanged();
    }
}

void CouchActionList::insert(int row, const std::shared_ptr<CouchAction>& action)
{
    beginInsertRows(QModelIndex(), row, row);
    m_actions.insert(row, action);
    endInsertRows();
}

void CouchActionList::append(const QList<std::shared_ptr<CouchAction> >& actions)
{
    if (actions.isEmpty()) {
        return;
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + actions.count() - 1);
    m_actions.append(actions);
    endInsertRows();
}

void CouchActionList::append(const std::shared_ptr<CouchAction>& action)
{
    insert(rowCount(), action);
}
