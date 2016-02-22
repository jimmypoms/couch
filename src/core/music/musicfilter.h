/*
 * musicfilter.h
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#ifndef MUSICFILTER_H_
#define MUSICFILTER_H_

#include "album.h"

#include <qobjectdefs.h>

#include "../model/filter.h"

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT MusicFilter : public Filter
{
Q_OBJECT

Q_PROPERTY(Album::Genre genre READ genre WRITE setGenre NOTIFY genreChanged)

Q_SIGNALS:
    void genreChanged();

private:
    Album::Genre m_genre;

public:
    explicit MusicFilter(QObject *parent = 0);
    virtual ~MusicFilter() = default;

    Album::Genre genre() const;
    void setGenre(Album::Genre m_genre);
};

#endif /* MUSICFILTER_H_ */
