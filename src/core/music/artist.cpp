/*
 * artist.cpp
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#include "artist.h"

#include "artistmetadata.h"

Artist::Artist(Service *service) :
        Item(service)
{
}

ArtistMetadata* Artist::metadata() const
{
    return static_cast<ArtistMetadata*>(Item::metadata());
}
