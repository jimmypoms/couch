/*
 * couchrequest.cpp
 *
 *  Created on: 18 Oct 2015
 *      Author: jimmypoms
 */

#include "couchrequest.h"

CouchRequest::CouchRequest() :
        m_operation(QNetworkAccessManager::GetOperation)
{
}

const QByteArray& CouchRequest::data() const
{
    return m_data;
}

void CouchRequest::setData(const QByteArray& data)
{
    if (m_data != data) {
        m_data = data;
        Q_EMIT dataChanged();
    }
}

QNetworkAccessManager::Operation CouchRequest::operation() const
{
    return m_operation;
}

void CouchRequest::setOperation(QNetworkAccessManager::Operation operation)
{
    if (m_operation != operation) {
        m_operation = operation;
        Q_EMIT operationChanged();
    }
}

const QUrl& CouchRequest::url() const
{
    return m_url;
}

void CouchRequest::setUrl(const QUrl& url)
{
    if (m_url != url) {
        m_url = url;
        Q_EMIT urlChanged();
    }
}

