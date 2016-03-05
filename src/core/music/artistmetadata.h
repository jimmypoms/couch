/*
 * musicmetadata.h
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#ifndef ARTISTMETADATA_H_
#define ARTISTMETADATA_H_

#include "../model/itemmetadata.h"

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT ArtistMetadata : public ItemMetadata
{
Q_OBJECT

Q_PROPERTY(QString artist READ artist WRITE setArtist NOTIFY artistChanged)

Q_SIGNALS:
    void artistChanged();

public:
    explicit ArtistMetadata(QObject *parent = 0);
    virtual ~ArtistMetadata() = default;

    const QString &artist() const;
    void setArtist(const QString& artist);
};

#endif /* ARTISTMETADATA_H_ */
