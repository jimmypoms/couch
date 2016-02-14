#include "movieservice.h"

#include "movie.h"

#include <qlist.h>
#include <qobject.h>
#include <memory>
#include <unordered_map>

#include "../model/couchactionlist.h"
#include "../model/couchitemlist.h"
#include "../model/couchplayaction.h"
#include "../model/couchsourcelist.h"
#include "../model/provider.h"
#include "../model/source.h"

MovieService::MovieService(QObject *parent) :
        Service(parent, "movies"), m_metadataCache("movies/metadata")
{
}

Item* MovieService::createItem(const Source *source)
{
    Movie *movie = new Movie(this);
    movie->setName(source->itemMetadata()->name());
    QString key = source->itemMetadata()->name()
            + QString::number(source->itemMetadata()->year());
    auto i = m_metadataCache.find(key);
    if (i != m_metadataCache.end()) {
        movie->setMetadata(i->second);
    } else {
        movie->setMetadata(m_metadataCache.insert(key, new MovieMetadata()));
    }
    return movie;
}

CouchItemList* MovieService::load(MovieFilter *filter)
{
    CouchItemList* list = new CouchItemList(this);
    connect(this, &Service::itemsReady, list, &CouchItemList::addItems);
    for (const QObject *object : providers()) {
        MovieProviderInterface *provider = qobject_cast<MovieProviderInterface*>(object);

        CouchSourceList* sourceList = provider->load(filter);
        sourceList->setParent(list);

        connect(sourceList, &CouchSourceList::sourcesLoaded, this, &Service::reduceSources);
    }
    return list;
}

CouchItemList* MovieService::loadItem(Movie *movie)
{
    CouchItemList* list = new CouchItemList(this);
    connect(this, &Service::itemsReady, list, &CouchItemList::addItems);
    for (const QObject *object : providers()) {
        MovieProviderInterface *provider = qobject_cast<MovieProviderInterface*>(object);

        CouchSourceList* sourceList = provider->load(movie);
        sourceList->setParent(list);

        connect(sourceList, &CouchSourceList::sourcesLoaded, this, &Service::reduceSources);
    }
    return list;
}

CouchActionList* MovieService::actions(Movie* movie)
{
    CouchActionList* list = new CouchActionList(this);
    QList<std::shared_ptr<CouchAction> > actions;
    if (!movie->metadata()->trailer().isEmpty()) {
        Source* trailer = movie->trailerSource();
        if (trailer) {
            CouchPlayAction* action = new CouchPlayAction(trailer);
            action->setText("trailer");
            connect(action, &CouchAction::triggered, this, &Service::onActionTriggered);
            action->setParent(list);
            actions.append(std::shared_ptr<CouchAction>(action));
        }
    }
    list->addActions(actions);
    return list;
}
