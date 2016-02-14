/*
 * album.h
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#ifndef ALBUM_H_
#define ALBUM_H_

#include <qobject.h>
#include <qobjectdefs.h>

class Artist;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT Album : public QObject
{
Q_OBJECT

public:
    explicit Album(Artist *parent);
    virtual ~Album() = default;
};

#endif /* ALBUM_H_ */
