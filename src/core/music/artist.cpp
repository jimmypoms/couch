/*
 * artist.cpp
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#include "artist.h"

#include "musicmetadata.h"

Artist::Artist(Service *service) :
        Item(service)
{
}

MusicMetadata* Artist::metadata() const
{
    return static_cast<MusicMetadata*>(Item::metadata());
}
