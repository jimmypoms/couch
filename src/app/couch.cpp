#include "couch.h"

#include <qqml.h>

#include "couch/couchitemlist.h"
#include "couch/couchsourcelist.h"
#include "couch/itemmetadata.h"
#include "couch/movie/movie.h"
#include "couch/movie/moviefilter.h"
#include "couch/source.h"

#include "player/couchplayer.h"

Couch::Couch(QObject *parent) :
        QObject(parent)
{
    qmlRegisterType<Filter>("org.couch.filter", 1, 0, "Filter");
    qmlRegisterType<Source>("org.couch.source", 1, 0, "Source");
    qmlRegisterType<MovieFilter>("org.couch.filter.movie", 1, 0, "MovieFilter");

    qmlRegisterUncreatableType<CouchItemList>("org.couch.itemlist", 1, 0, "CouchItemList",
            "impossible to create itemlist from qml");
    qmlRegisterUncreatableType<CouchSourceList>("org.couch.sourcelist", 1, 0, "CouchSourceList",
            "impossible to create sourcelist from qml");

    qmlRegisterUncreatableType<ItemMetadata>("org.couch.metadata", 1, 0, "Metadata",
            "impossible to create metadata from qml");
    qmlRegisterUncreatableType<Item>("org.couch.item", 1, 0, "Item",
            "impossible to create items from qml");
    qmlRegisterUncreatableType<Movie>("org.couch.item.movie", 1, 0, "Movie",
            "impossible to create movies from qml");

    qmlRegisterUncreatableType<Service>("org.couch.service", 1, 0, "Service",
            "impossible to create service form qml");
    qmlRegisterUncreatableType<CouchPlayer>("org.couch.player", 1, 0, "CouchPlayer",
            "impossible to create player form qml");
}

void Couch::addService(Service* service)
{
    service->setParent(this);
    m_services.append(service);
}

const QList<Service*>& Couch::services() const
{
    return m_services;
}

QQmlListProperty<Service> Couch::qmlServices()
{
    return QQmlListProperty<Service>(this, m_services);
}

