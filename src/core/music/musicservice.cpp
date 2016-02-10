/*
 * musicservice.cpp
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#include "musicservice.h"

#include "artist.h"

#include <model/couchactionlist.h>
#include <model/couchitemlist.h>
#include <model/provider.h>
#include <qdebug.h>
#include <qlogging.h>
#include <qobject.h>

MusicService::MusicService(QObject* parent) :
        Service(parent, "music"), m_metadataCache("music/metadata")
{
}

Item* MusicService::createItem(const Source* source)
{
    Artist *artist = new Artist(this);
    return artist;
}

CouchItemList* MusicService::load(MusicFilter* filter)
{
    CouchItemList *list = new CouchItemList(this);
    return list;
}

CouchItemList* MusicService::loadItem(Artist* artist)
{
    CouchItemList *list = new CouchItemList(this);
    return list;
}

CouchActionList* MusicService::actions(Artist* artist)
{
    CouchActionList *list = new CouchActionList(this);
    return list;
}
