#include "couch.h"

#include "couch/couchactionlist.h"
#include "couch/couchitemlist.h"
#include "couch/couchplayer.h"
#include "couch/couchproviderlist.h"
#include "couch/couchsourcelist.h"
#include "couch/itemmetadata.h"
#include "couch/movie/movie.h"
#include "couch/movie/moviefilter.h"
#include "couch/music/artist.h"
#include "couch/music/musicfilter.h"
#include "couch/source.h"

#include <qqml.h>

Couch::Couch(QObject *parent) :
        QObject(parent)
{
    qmlRegisterType<Filter>("org.couch.filter", 1, 0, "Filter");
    qmlRegisterType<Source>("org.couch.source", 1, 0, "Source");
    qmlRegisterType<MovieFilter>("org.couch.filter.movie", 1, 0, "MovieFilter");
    qmlRegisterType<MusicFilter>("org.couch.filter.music", 1, 0, "MusicFilter");

    qmlRegisterUncreatableType<CouchItemList>("org.couch.itemlist", 1, 0, "CouchItemList",
            "impossible to create itemlist from qml");
    qmlRegisterUncreatableType<CouchSourceList>("org.couch.sourcelist", 1, 0, "CouchSourceList",
            "impossible to create sourcelist from qml");
    qmlRegisterUncreatableType<CouchProviderList>("org.couch.providerlist", 1, 0,
            "CouchProviderList", "impossible to create providerlist from qml");
    qmlRegisterUncreatableType<CouchActionList>("org.couch.actionlist", 1, 0, "CouchActionList",
            "impossible to create actionlist from qml");

    qmlRegisterUncreatableType<ItemMetadata>("org.couch.metadata", 1, 0, "Metadata",
            "impossible to create metadata from qml");
    qmlRegisterUncreatableType<Item>("org.couch.item", 1, 0, "Item",
            "impossible to create items from qml");
    qmlRegisterUncreatableType<Movie>("org.couch.item.movie", 1, 0, "Movie",
            "impossible to create movies from qml");
    qmlRegisterUncreatableType<Artist>("org.couch.item.artist", 1, 0, "Artist",
            "impossible to create artists from qml");

    qmlRegisterUncreatableType<CouchPlayer>("org.couch.player", 1, 0, "CouchPlayer",
            "impossible to create player form qml");
}

void Couch::addService(QObject* service)
{
    service->setParent(this);
    m_services.append(service);
}

const QList<QObject*>& Couch::services() const
{
    return m_services;
}
