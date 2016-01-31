/*
 * couchaction.cpp
 *
 *  Created on: 23 Jan 2016
 *      Author: jimmypoms
 */

#include "couchaction.h"

CouchAction::CouchAction(QObject *parent) :
        QObject(parent), m_text(), m_enabled(true)
{
}

const QString& CouchAction::text() const
{
    return m_text;
}

void CouchAction::setText(const QString& text)
{
    if (m_text != text) {
        m_text = text;
        Q_EMIT textChanged();
    }
}

bool CouchAction::enabled() const
{
    return m_enabled;
}

void CouchAction::setEnabled(bool enabled)
{
    if (m_enabled != enabled) {
        m_enabled = enabled;
        Q_EMIT enabledChanged();
    }
}

void CouchAction::trigger()
{
    Q_EMIT triggered();
}
