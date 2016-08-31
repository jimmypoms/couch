/*
 * networkprovider.cpp
 *
 *  Created on: 28 Oct 2015
 *      Author: jimmypoms
 */

#include "networkprovider.h"

NetworkProviderImpl::NetworkProviderImpl(QObject* parent) :
        QObject(parent)
{
    connect(&m_signalMapper,
            static_cast<void (QSignalMapper::*)(const QString &)>(&QSignalMapper::mapped), this, &NetworkProviderImpl::onNetworkReply);
}

QNetworkReply *NetworkProviderImpl::sendRequest(QNetworkRequest &request,
        const CouchRequest &cRequest)
{
    request.setUrl(cRequest.url());
    switch (cRequest.operation()) {
        case QNetworkAccessManager::UnknownOperation:
        case QNetworkAccessManager::GetOperation:
            return m_nam.get(request);
        case QNetworkAccessManager::HeadOperation:
            return m_nam.head(request);
        case QNetworkAccessManager::PutOperation:
            return m_nam.put(request, cRequest.data());
        case QNetworkAccessManager::PostOperation:
            return m_nam.post(request, cRequest.data());
        case QNetworkAccessManager::DeleteOperation:
            return m_nam.deleteResource(request);
        case QNetworkAccessManager::CustomOperation:
            return m_nam.sendCustomRequest(request, cRequest.data());
    }
    return m_nam.get(request);
}

void NetworkProviderImpl::onNetworkReply(const QString &id)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(m_signalMapper.mapping(id));
    QList<Source*> sources = parseReply(reply);

    m_signalMapper.removeMappings(reply);
    reply->deleteLater();
    Q_EMIT sourcesReady(sources, id);
}
