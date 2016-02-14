/*
 * artist.h
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#ifndef ARTIST_H_
#define ARTIST_H_

#include <qobjectdefs.h>

#include "../model/item.h"

class ArtistMetadata;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT Artist : public Item
{
Q_OBJECT

public:
    explicit Artist(Service *service);
    virtual ~Artist() = default;

    ArtistMetadata *metadata() const;
};

#endif /* ARTIST_H_ */
