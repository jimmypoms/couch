/*
 * musicmetadata.h
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#ifndef MUSICMETADATA_H_
#define MUSICMETADATA_H_

#include "../model/itemmetadata.h"

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT MusicMetadata : public ItemMetadata
{
public:
    explicit MusicMetadata(QObject *parent = 0);
    virtual ~MusicMetadata() = default;
};

#endif /* MUSICMETADATA_H_ */
