/*
 * musicservice.cpp
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#include "musicservice.h"

MusicService::MusicService(QObject* parent) :
        Service(parent, "music"), m_metadataCache("music/metadata")
{
}

Artist* MusicService::createItem(const Source* source)
{
    Artist *artist = new Artist(this);
    return artist;
}

CouchActionList* MusicService::serviceActions(Artist* artist)
{
    return nullptr;
}
