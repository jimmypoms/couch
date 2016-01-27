#ifndef MOVIE_H
#define MOVIE_H

#include <qobjectdefs.h>

#include "../model/item.h"

class MovieMetadata;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT Movie : public Item
{
Q_OBJECT

Q_ENUMS(Genre)

public:
    enum Genre
    {
        All,
        Action,
        Comedy,
        Drama,
        Romance,
        Fantasy,
        SciFi,
        Horror,
        Documentary
    };

    explicit Movie(Service* service);

    MovieMetadata *metadata() const;
    static QString genreToString(Movie::Genre genre);
};

#endif // MOVIE_H
