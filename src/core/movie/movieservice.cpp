#include "movieservice.h"

#include "../model/couchactionlist.h"
#include "../model/couchplayaction.h"
#include "../model/source.h"

#include <qlist.h>
#include <memory>
#include <unordered_map>

MovieService::MovieService(QObject *parent) :
        Service(parent, "movies"), m_metadataCache("movies/metadata")
{
}

Movie* MovieService::createItem(const Source *source)
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

CouchActionList* MovieService::serviceActions(Movie* movie)
{
    CouchActionList* list = new CouchActionList(providers().count());
    QList<std::shared_ptr<CouchAction> > actions;
    if (!movie->metadata()->trailer().isEmpty()) {
        Source* trailer = movie->trailerSource();
        if (trailer) {
            CouchPlayAction* action = new CouchPlayAction(trailer);
            action->setText("trailer");
            action->setParent(list);
            actions.append(std::shared_ptr<CouchAction>(action));
        }
    }
    list->addActions(actions);
    return list;
}
