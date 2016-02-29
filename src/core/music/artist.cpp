/*
 * artist.cpp
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#include "artist.h"

#include "artistmetadata.h"

Artist::Artist(QObject *parent) :
        Item(parent)
{
}

ArtistMetadata* Artist::metadata() const
{
    return static_cast<ArtistMetadata*>(Item::metadata());
}
