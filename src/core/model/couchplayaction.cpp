/*
 * couchplayaction.cpp
 *
 *  Created on: 27 Jan 2016
 *      Author: jimmypoms
 */

#include "couchplayaction.h"

#include "source.h"

CouchPlayAction::CouchPlayAction(Source *source, QObject *parent) :
        CouchAction(parent), m_source(source)
{
}

Source* CouchPlayAction::source() const
{
    return m_source;
}

void CouchPlayAction::setSource(Source* source)
{
    if (m_source != source) {
        m_source = source;
        Q_EMIT sourceChanged();
    }
}
