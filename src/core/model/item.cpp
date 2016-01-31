#include "item.h"

#include <qlist.h>
#include <algorithm>

#include "service.h"
#include "source.h"

Item::Item(Service* service) :
        QObject(service), m_service(service), m_emptySourceList(new CouchSourceList())
{
    m_emptySourceList->setParent(this);
    for (const QObject *provider : service->providers()) {
        CouchSourceList *list = new CouchSourceList(provider);
        list->setParent(this);
        m_sources.insert(provider, list);
    }
}

const QString &Item::title() const
{
    return m_title;
}

void Item::setTitle(const QString &t)
{
    if (m_title != t) {
        m_title = t;
        Q_EMIT titleChanged();
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

bool Item::isLoaded(const QObject* provider) const
{
    if (m_loaded.contains(provider)) {
        return m_loaded[provider];
    }
    return false;
}

void Item::setLoaded(const QObject* provider, bool loaded)
{
    m_loaded.insert(provider, loaded);
}
