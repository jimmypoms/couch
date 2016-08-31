#include "item.h"

#include "couchproviderlist.h"
#include "source.h"

#include <qlist.h>
#include <algorithm>

Item::Item(QObject* parent) :
                QObject(parent), m_emptySourceList(new CouchSourceList()),
                m_providers(new CouchProviderList())
{
    m_emptySourceList->setParent(this);
    m_providers->setParent(this);
}

const QString &Item::name() const
{
    return m_name;
}

void Item::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        Q_EMIT nameChanged();
    }
}

ItemMetadata *Item::metadata() const
{
    return m_metadata.get();
}

void Item::setMetadata(std::shared_ptr<ItemMetadata> metadata)
{
    if (metadata && m_metadata != metadata) {
        m_metadata = metadata;
        Q_EMIT metadataChanged();
    }
}

void Item::addSource(const QObject* provider, Source* source)
{
    source->setParent(this);
    if (!m_sources.contains(provider)) {
        CouchSourceList *list = new CouchSourceList(provider);
        list->setParent(this);
        m_sources.insert(provider, list);
        m_providers->append(const_cast<QObject*>(provider));
    }

    auto it = std::find_if(m_sources[provider]->cbegin(), m_sources[provider]->cend(),
            [source](Source* s) {
                return *source == *s;
            });
    if (it == m_sources[provider]->cend()) {
        m_sources[provider]->append(source);
        m_metadata->merge(source->itemMetadata());
        Q_EMIT sourcesChanged();
    }
}

CouchSourceList *Item::sources(QObject* provider)
{
    if (m_sources.contains(provider)) {
        return m_sources[provider];
    } else {
        return m_emptySourceList;
    }
}

CouchProviderList *Item::providers() const
{
    return m_providers;
}
