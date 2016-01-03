/*
 * networkprovider.h
 *
 *  Created on: 28 Oct 2015
 *      Author: jimmypoms
 */

#ifndef NETWORKPROVIDER_H_
#define NETWORKPROVIDER_H_

#include <qdebug.h>
#include <qlist.h>
#include <qlogging.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qsignalmapper.h>
#include <qstring.h>
#include <qurl.h>

#include "couchrequest.h"
#include "couchsourcelist.h"
#include "provider.h"
#include "source.h"

class NetworkProviderImpl : public QObject
{
Q_OBJECT

protected:
    QNetworkAccessManager m_nam;
    QSignalMapper m_signalMapper;

Q_SIGNALS:
    void sourcesReady(const QList<Source*> &sources, const QString &id);

private Q_SLOTS:
    void onNetworkReply(const QString &id);

private:
    virtual QList<Source*> parseReply(QNetworkReply* reply) const = 0;

protected:
    QNetworkReply *sendRequest(QNetworkRequest &request, const CouchRequest &cRequest);

public:
    explicit NetworkProviderImpl(QObject* parent = 0);
    virtual ~NetworkProviderImpl() = default;
};

template<class Item, class Filter>
class NetworkProvider : public Provider<Item, Filter>, public NetworkProviderImpl
{
private:
    virtual void buildRequest(CouchRequest *request, const Filter *filter) const = 0;
    virtual void buildRequest(CouchRequest *request, const Item *item) const = 0;

public:
    explicit NetworkProvider(QObject *parent = 0) :
            NetworkProviderImpl(parent)
    {
    }
    virtual ~NetworkProvider() = default;

    virtual const QString &name() const = 0;

    CouchSourceList* load(Filter *filter);
    CouchSourceList* load(Item* item);
};

template<class Item, class Filter>
inline CouchSourceList* NetworkProvider<Item, Filter>::load(Filter* filter)
{
    CouchSourceList* list = new CouchSourceList(this);

    QNetworkRequest request;
    CouchRequest cRequest;
    request.setOriginatingObject(this);
    buildRequest(&cRequest, filter);
    QNetworkReply *reply = sendRequest(request, cRequest);

    qDebug() << "loading provider" << name() << ":" << reply->url().toString();
    m_signalMapper.setMapping(reply, list->id());
    connect(reply, &QNetworkReply::finished, &m_signalMapper,
            static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));;

    connect(this, &NetworkProviderImpl::sourcesReady, list, &CouchSourceList::addSources);
    return list;
}

template<class Item, class Filter>
inline CouchSourceList* NetworkProvider<Item, Filter>::load(Item* item)
{
    CouchSourceList* list = new CouchSourceList(this);

    QNetworkRequest request;
    CouchRequest cRequest;
    request.setOriginatingObject(this);
    buildRequest(&cRequest, item);
    QNetworkReply *reply = sendRequest(request, cRequest);

    qDebug() << "loading provider" << name() << ":" << reply->url().toString();
    m_signalMapper.setMapping(reply, list->id());
    connect(reply, &QNetworkReply::finished, &m_signalMapper,
            static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));;

    connect(this, &NetworkProviderImpl::sourcesReady, list, &CouchSourceList::addSources);
    return list;
}

#endif /* NETWORKPROVIDER_H_ */
