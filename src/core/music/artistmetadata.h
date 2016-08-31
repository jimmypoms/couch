/*
 * musicmetadata.h
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#ifndef ARTISTMETADATA_H_
#define ARTISTMETADATA_H_

#include "couch/itemmetadata.h"

#include <qobject.h>
#include <qobjectdefs.h>
#include <qstring.h>

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

    virtual bool lessThan(const ItemMetadata *other) noexcept
    {
        const ArtistMetadata *artist = qobject_cast<const ArtistMetadata*>(other);
        if (artist) {
            return lessThan(artist);
        }

        return ItemMetadata::lessThan(other);
    }

    bool lessThan(const ArtistMetadata *other) noexcept
    {
        return artist() < other->artist();
    }
};

#endif /* ARTISTMETADATA_H_ */
