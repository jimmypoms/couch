#ifndef SERVICE_H
#define SERVICE_H

#include "couchaction.h"
#include "couchactionlist.h"
#include "couchitemlist.h"
#include "couchsourcelist.h"
#include "provider.h"

#include "couch/settings/settinglist.h"

#include <qlist.h>
#include <qmutex.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <memory>

class CouchPlayer;

class ServiceImpl : public QObject
{
Q_OBJECT

Q_PROPERTY(QString name READ name CONSTANT)
Q_PROPERTY(QList<QObject*> providers READ providers NOTIFY providersChanged)

Q_SIGNALS:
    void error(const QString &msg);
    void warning(const QString &msg);

    void providersChanged();
    void itemsReady(const QList<std::shared_ptr<Item> > &items, const QString &id);

private:
    QString m_name;
    int m_maxItemCacheSize;
    QMutex m_mutex;

    virtual Item* createItem(const Source *source) = 0;

protected:
    CouchPlayer* m_player;
    QList<QObject*> m_providers;
    QList<std::shared_ptr<Item> > m_items;

    virtual QList<std::shared_ptr<Item> >::const_iterator findItem(Source* source);

public Q_SLOTS:
    void reduceSources();
    void onActionTriggered();

public:
    explicit ServiceImpl(QObject *parent, const QString &name);
    virtual ~ServiceImpl() = default;

    const QString &name() const;

    void addProvider(QObject* provider);
    const QList<QObject*> &providers() const;

    const CouchPlayer* player() const;
    void setPlayer(CouchPlayer* player);

    virtual SettingList* buildSettings(const SettingList *parent = 0) = 0;
};

template<class Item, class Filter, class P = Provider<Item, Filter> >
class Service : public ServiceImpl
{
private:
    virtual Item* createItem(const Source *source) = 0;
    virtual CouchActionList* serviceActions(Item *item) = 0;

public:
    explicit Service(QObject *parent, const QString &name) :
            ServiceImpl(parent, name)
    {
    }
    virtual ~Service() = default;

    CouchItemList *load(Filter *filter);
    CouchItemList *load(Item *item);
    CouchActionList *actions(Item *item);

    SettingList* buildSettings(const SettingList *parent = 0);
};

template<class Item, class Filter, class P>
inline CouchItemList* Service<Item, Filter, P>::load(Filter *filter)
{
    CouchItemList* list = filter->result();
    if (!list) {
        list = new CouchItemList(providers().count());
        connect(this, &ServiceImpl::itemsReady, list, &CouchItemList::addItems);
    }
    if (filter->isDirty()) {
        for (CouchSourceList* sourceList : list->sourceLists()) {
            disconnect(sourceList, &CouchSourceList::sourcesLoaded, this,
                    &ServiceImpl::reduceSources);
        }
        filter->reset();
    }
    list->setLoadingCount(filter->hasMoreCount(providers()));
    for (const QObject *object : providers()) {
        if (!filter->hasMore(object)) {
            continue;
        }

        P* provider = qobject_cast<P*>(object);
        CouchSourceList* sourceList = provider->load(filter);
        list->addSourceList(sourceList);
        connect(sourceList, &CouchSourceList::sourcesLoaded, this, &ServiceImpl::reduceSources);

        if (!sourceList->loading()) {
            Q_EMIT sourceList->sourcesLoaded();
        }
    }
    filter->setResult(list);
    return list;
}

template<class Item, class Filter, class P>
inline CouchItemList* Service<Item, Filter, P>::load(Item *item)
{
    CouchItemList* list = new CouchItemList(providers().count());
    connect(this, &ServiceImpl::itemsReady, list, &CouchItemList::addItems);
    for (const QObject *object : providers()) {
        P* provider = qobject_cast<P*>(object);
        CouchSourceList* sourceList = provider->load(item);
        list->addSourceList(sourceList);
        connect(sourceList, &CouchSourceList::sourcesLoaded, this, &ServiceImpl::reduceSources);

        if (!sourceList->loading()) {
            Q_EMIT sourceList->sourcesLoaded();
        }
    }
    return list;
}

template<class Item, class Filter, class P>
inline CouchActionList* Service<Item, Filter, P>::actions(Item* item)
{
    CouchActionList* list = serviceActions(item);
    if (!list) {
        list = new CouchActionList(providers().count());
    }

    for (const std::shared_ptr<CouchAction>& action : list->actions()) {
        connect(action.get(), &CouchAction::triggered, this, &ServiceImpl::onActionTriggered);
    }
    return list;
}

template<class Item, class Filter, class P>
SettingList* Service<Item, Filter, P>::buildSettings(const SettingList* parent)
{
    SettingList* list = new SettingList(this, parent, name());

    for (QObject* object : m_providers) {
        Provider<Item, Filter>* provider = qobject_cast<Provider<Item, Filter>*>(object);
        if (provider) {
            SettingList* providerSettings = provider->buildSettings(list);
            if (providerSettings) {
                list->setSettingList(object, providerSettings);
            }
        }
    }

    return list;
}


#endif // SERVICE_H
