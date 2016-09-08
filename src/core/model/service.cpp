#include "service.h"

#include "couchplayaction.h"
#include "item.h"
#include "itemmetadata.h"
#include "source.h"

#include <multimedia/couchplayer.h>
#include <qdebug.h>
#include <qlogging.h>
#include <qobject.h>
#include <qurl.h>
#include <algorithm>

ServiceImpl::ServiceImpl(QObject *parent, const QString &name) :
        QObject(parent), m_name(name), m_maxItemCacheSize(500), m_player(nullptr)
{
}

const QString &ServiceImpl::name() const
{
    return m_name;
}

const QList<QObject*> &ServiceImpl::providers() const
{
    return m_providers;
}

void ServiceImpl::addProvider(QObject* provider)
{
    provider->setParent(this);
    m_providers.append(provider);
    Q_EMIT providersChanged();
}

const CouchPlayer* ServiceImpl::player() const
{
    return m_player;
}

void ServiceImpl::setPlayer(CouchPlayer* player)
{
    m_player = player;
}

void ServiceImpl::reduceSources()
{
    CouchSourceList* sourcesList = qobject_cast<CouchSourceList*>(sender());
    const QObject* provider = sourcesList->provider();
    QList<std::shared_ptr<Item> > list;
    m_mutex.lock();
    for (Source* source : sourcesList->sources()) {
        auto it = findItem(source);
        if (it == m_items.cend()) {
            if (!source->itemMetadata()) {
                qDebug() << "invalid source (missing metadata), url:" << source->url();
                continue;
            }
            auto item = createItem(source);
            item->addSource(provider, source);
            m_items.append(std::shared_ptr<Item>(item));
            if (m_items.size() > m_maxItemCacheSize) {
                m_items.pop_front();
            }
            list.append(m_items.last());
        } else {
            auto item = *it;
            item->addSource(provider, source);
            list.append(item);
        }
    }
    m_mutex.unlock();
    CouchItemList* itemList = qobject_cast<CouchItemList*>(sourcesList->parent());
    if (itemList) {
        QString id = itemList->id();
        Q_EMIT itemsReady(list, id);
    }
}

QList<std::shared_ptr<Item> >::const_iterator ServiceImpl::findItem(Source *source)
{
    return std::find_if(m_items.cbegin(), m_items.cend(),
            [source](std::shared_ptr<Item> item)->bool {
                return *(item->metadata()) == *(source->itemMetadata());
            });
}

void ServiceImpl::onActionTriggered()
{
    CouchAction* action = qobject_cast<CouchAction*>(sender());
    CouchPlayAction* playAction = qobject_cast<CouchPlayAction*>(action);
    if (playAction) {
        m_player->play(playAction->source());
        return;
    }
}
