/*
 * track.h
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#ifndef TRACK_H_
#define TRACK_H_

#include <qobjectdefs.h>

#include "../model/item.h"

class Album;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT Track : public Item
{
Q_OBJECT

public:
    explicit Track(Album *parent = 0);
    virtual ~Track() = default;
};

#endif /* TRACK_H_ */
