#include "filter.h"

Filter::Filter(QObject *parent) :
        QObject(parent), m_order(Order::None), m_limit(20), m_offset(0)
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
