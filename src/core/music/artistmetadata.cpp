/*
 * musicmetadata.cpp
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#include "artistmetadata.h"

ArtistMetadata::ArtistMetadata(QObject *parent) :
        ItemMetadata(parent)
{
}

const QString &ArtistMetadata::artist() const
{
    return ItemMetadata::name();
}

void ArtistMetadata::setArtist(const QString& artist)
{
    if (ItemMetadata::name() != artist) {
        ItemMetadata::setName(artist);
        Q_EMIT artistChanged();
    }
}

