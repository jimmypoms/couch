#ifndef MOVIEFILTER_H
#define MOVIEFILTER_H

#include "movie.h"

#include <qobjectdefs.h>

#include "../model/filter.h"

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT MovieFilter : public Filter
{
Q_OBJECT

Q_PROPERTY(Movie::Genre genre READ genre WRITE setGenre NOTIFY genreChanged)

Q_SIGNALS:
    void genreChanged();

private:
    Movie::Genre m_genre;

public:
    explicit MovieFilter(QObject *parent = 0);
    virtual ~MovieFilter() = default;

    Movie::Genre genre() const;
    void setGenre(Movie::Genre m_genre);
};

#endif // MOVIEFILTER_H
