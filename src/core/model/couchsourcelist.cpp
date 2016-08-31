/*
 * couchsourcelist.cpp
 *
 *  Created on: 18 Oct 2015
 *      Author: jimmypoms
 */

#include "couchsourcelist.h"

#include <qglobal.h>
#include <quuid.h>
#include <qvariant.h>
#include <algorithm>

CouchSourceList::CouchSourceList(const QObject* provider, QString id) :
        m_id(id), m_loading(false), m_provider(provider)
{
    if (m_id.isEmpty()) {
        m_id = QUuid::createUuid().toString();
    }

}

const QString& CouchSourceList::id() const
{
    return m_id;
}

bool CouchSourceList::loading() const
{
    return m_loading;
}

const QObject* CouchSourceList::provider() const
{
    return m_provider;
}

const QList<Source*> CouchSourceList::sources() const
{
    return m_sources;
}

QHash<int, QByteArray> CouchSourceList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole] = "modelData";
    return roles;
}

int CouchSourceList::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_sources.count();
}

QVariant CouchSourceList::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_sources.count()) {
        return QVariant();
    }
    if (Qt::UserRole == role) {
        QObject *item = m_sources[index.row()];
        return QVariant::fromValue(item);
    }
    return QVariant();
}

void CouchSourceList::addSources(const QList<Source*>& sources, const QString& id)
{
    if (!id.isEmpty() && id != m_id) {
        return;
    }

    QList<Source*> added;
    for (const auto source : sources) {
        auto it = std::find_if(m_sources.cbegin(), m_sources.cend(), [source](Source* s)->bool {
            return *source == *s;
        });
        if (it == m_sources.cend()) {
            added.append(source);
        }
    }
    append(added);
    Q_EMIT sourcesLoaded();
    if (!added.isEmpty()) {
        Q_EMIT sourcesChanged();
    }

    bool isLoading = loading();
    m_loading = false;
    if (isLoading != loading()) {
        Q_EMIT loadingChanged();
    }
}

void CouchSourceList::insert(int row, Source* source)
{
    beginInsertRows(QModelIndex(), row, row);
    m_sources.insert(row, source);
    endInsertRows();
}

void CouchSourceList::append(const QList<Source*>& sources)
{
    if (sources.isEmpty()) {
        return;
    }
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + sources.count() - 1);
    m_sources.append(sources);
    endInsertRows();
}

QList<Source*>::const_iterator CouchSourceList::cbegin() const
{
    return m_sources.cbegin();
}

QList<Source*>::const_iterator CouchSourceList::cend() const
{
    return m_sources.cend();
}

void CouchSourceList::append(Source* source)
{
    m_sources.append(source);
}
