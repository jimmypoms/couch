/*
 * musicfilter.h
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#ifndef MUSICFILTER_H_
#define MUSICFILTER_H_

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

public:
    explicit MusicFilter(QObject *parent = 0);
    virtual ~MusicFilter() = default;
};

#endif /* MUSICFILTER_H_ */
