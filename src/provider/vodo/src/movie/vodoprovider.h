/*
 * vodoprovider.h
 *
 *  Created on: 28 Oct 2015
 *      Author: jimmypoms
 */

#ifndef VODOPROVIDER_H_
#define VODOPROVIDER_H_

#include <qlist.h>
#include <qobjectdefs.h>

#include "couch/movie/moviefilter.h"
#include "couch/movie/movienetworkprovider.h"
#include "couch/source.h"

class VodoProvider : public MovieNetworkProvider
{
Q_OBJECT

Q_PLUGIN_METADATA(IID "org.couch.provider.movie")
Q_INTERFACES(MovieProviderInterface)

public:
    explicit VodoProvider(QObject* parent = 0);
    virtual ~VodoProvider() = default;

    QString orderToString(MovieFilter::Order order) const;

public Q_SLOTS:
    void buildRequest(CouchRequest *request, const MovieFilter *filter) const;
    void buildRequest(CouchRequest *request, const Movie *item) const;
    QList<Source*> parseReply(QNetworkReply* reply) const;
};

#endif /* VODOPROVIDER_H_ */
