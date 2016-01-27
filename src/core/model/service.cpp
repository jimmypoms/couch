#include "service.h"

#include <qdebug.h>
#include <qlogging.h>
#include <qurl.h>
#include <algorithm>

#include "couchitemlist.h"
#include "couchsourcelist.h"
#include "item.h"
#include "itemmetadata.h"
#include "source.h"

#include "../multimedia/couchplayer.h"

Service::Service(QObject *parent, QString name) :
        QObject(parent), m_name(name), m_maxItemCacheSize(500)
{
}

const QString &Service::name() const
{
    return m_name;
}

const CouchPlayer* Service::player() const
{
    return m_player;
}

void Service::setPlayer(CouchPlayer* player)
{
    m_player = player;
}

const QList<QObject*> &Service::providers() const
{
    return m_providers;
}

void Service::addProvider(QObject* provider)
{
    provider->setParent(this);
    m_providers.append(provider);
    Q_EMIT providersChanged();
}

void Service::reduceSources()
{
    CouchSourceList* sourcesList = qobject_cast<CouchSourceList*>(sender());
    const QObject* provider = sourcesList->provider();
    QList<std::shared_ptr<Item> > list;
    for (Source* source : sourcesList->sources()) {
        auto it = std::find_if(m_items.cbegin(), m_items.cend(),
                [source](std::shared_ptr<Item> item)->bool {
                    return *(item->metadata()) == *(source->itemMetadata());
                });
        if (it == m_items.cend()) {
            if (!source->itemMetadata()) {
                qDebug() << "invalid source (missing metadata), url:" << source->url();
                continue;
            }
            auto item = createItem(source);
            m_items.append(std::shared_ptr<Item>(item));
            if (m_items.size() > m_maxItemCacheSize) {
                m_items.pop_front();
            }
            item->addSource(provider, source);
            list.append(m_items.last());
        } else {
            auto item = *it;
            item->addSource(provider, source);
            list.append(item);
        }
    }
    CouchItemList* itemList = qobject_cast<CouchItemList*>(sourcesList->parent());
    if (itemList) {
        QString id = itemList->id();
        Q_EMIT itemsReady(list, id);
    }
    delete sourcesList;
}

