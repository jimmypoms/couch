#include "filter.h"

#include "couchitemlist.h"

#include <qlist.h>

Filter::Filter(QObject *parent, int offset, int limit) :
                QObject(parent), m_order(Order::None), m_offset(offset), m_limit(limit),
                m_dirty(false), m_result(nullptr)
{
}

const QString &Filter::text() const
{
    return m_text;
}

void Filter::setText(const QString &text)
{
    if (m_text != text) {
        m_text = text;
        setDirty(true);
        Q_EMIT textChanged();
    }
}

Filter::Order Filter::order() const
{
    return m_order;
}

void Filter::setOrder(Filter::Order order)
{
    if (m_order != order) {
        m_order = order;
        setDirty(true);
        Q_EMIT orderChanged();
    }
}

int Filter::limit() const
{
    return m_limit;
}

void Filter::setLimit(int limit)
{
    if (m_limit != limit) {
        m_limit = limit;
        Q_EMIT limitChanged();
    }
}

int Filter::offset() const
{
    return m_offset;
}

void Filter::setOffset(int offset)
{
    if (m_offset != offset) {
        m_offset = offset;
        Q_EMIT offsetChanged();
    }
}

void Filter::setDirty(bool dirty)
{
    if (m_dirty != dirty) {
        m_dirty = dirty;
        Q_EMIT dirtyChanged();
    }
}

bool Filter::isDirty() const
{
    return m_dirty;
}

CouchItemList* Filter::result() const
{
    return m_result;
}

void Filter::setResult(CouchItemList* result)
{
    if (m_result != result) {
        delete m_result;
        result->setParent(this);
        m_result = result;
        Q_EMIT resultChanged();
    }
}

bool Filter::hasMore() const
{
    for (bool hasMore : m_hasMoreMap.values()) {
        if (hasMore) {
            return true;
        }
    }

    return false;
}

/** \brief Returns true if the filter expects more results for a given provider.
 *
 * We do assume that there are more results when a provider has never
 * returned any results.
 */
bool Filter::hasMore(const QObject* provider) const
{
    if (m_hasMoreMap.contains(provider)) {
        return m_hasMoreMap[provider];
    }

    return true;
}

void Filter::setHasMore(const QObject* provider, bool hasMore)
{
    if (!m_hasMoreMap.contains(provider)) {
        m_hasMoreMap.insert(provider, hasMore);
    } else {
        m_hasMoreMap[provider] = hasMore;
    }

    Q_EMIT hasMoreChanged();
}
