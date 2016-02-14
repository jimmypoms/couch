/*
 * trackmetadata.h
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#ifndef TRACKMETADATA_H_
#define TRACKMETADATA_H_

#include "albummetadata.h"

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT TrackMetadata : public AlbumMetadata
{
public:
    explicit TrackMetadata(QObject *parent = 0);
    virtual ~TrackMetadata() = default;
};

#endif /* TRACKMETADATA_H_ */
