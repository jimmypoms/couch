/*
 * couchplayaction.h
 *
 *  Created on: 27 Jan 2016
 *      Author: jimmypoms
 */

#ifndef COUCHPLAYACTION_H_
#define COUCHPLAYACTION_H_

#include "couchaction.h"

#include <qobjectdefs.h>

class Source;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT CouchPlayAction : public CouchAction
{
Q_OBJECT

Q_SIGNALS:
    void sourceChanged();

private:
    const Source* m_source;

public:
    CouchPlayAction(Source* source, QObject *parent = 0);
    virtual ~CouchPlayAction() = default;

    const Source* source() const;
    void setSource(const Source* source);
};

#endif /* COUCHPLAYACTION_H_ */
