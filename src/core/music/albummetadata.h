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

Q_PROPERTY(QStringList genres READ genres WRITE setGenres NOTIFY genresChanged)

Q_SIGNALS:
    void genresChanged();

private:
    QStringList m_genres;

public:
    explicit AlbumMetadata(QObject *parent = 0);
    virtual ~AlbumMetadata() = default;

    const QStringList& genres() const;
    void setGenres(const QStringList& genres);
    void addGenre(const QString& genre);
};

#endif /* ALBUMMETADATA_H_ */
