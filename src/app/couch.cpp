#include "couch.h"

#include "couch/couchactionlist.h"
#include "couch/couchitemlist.h"
#include "couch/couchplayer.h"
#include "couch/couchproviderlist.h"
#include "couch/couchsourcelist.h"
#include "couch/itemmetadata.h"
#include "couch/movie/movie.h"
#include "couch/movie/moviefilter.h"
#include "couch/movie/movienetworkprovider.h"
#include "couch/movie/movieprovider.h"
#include "couch/music/artist.h"
#include "couch/music/musicfilter.h"
#include "couch/music/musicnetworkprovider.h"
#include "couch/music/musicprovider.h"
#include "couch/source.h"

#include <qqml.h>

Couch::Couch(QObject *parent) :
        QObject(parent)
{
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
