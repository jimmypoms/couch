/*
 * albummetadata.h
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#ifndef ALBUMMETADATA_H_
#define ALBUMMETADATA_H_

#include "artistmetadata.h"

#include <qobjectdefs.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class AlbumMetadata : public ArtistMetadata
{
Q_OBJECT

public:
    explicit AlbumMetadata(QObject *parent = 0);
    virtual ~AlbumMetadata() = default;
};

#endif /* ALBUMMETADATA_H_ */
