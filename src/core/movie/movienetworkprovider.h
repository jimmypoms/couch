/*
 * movienetworkprovider.h
 *
 *  Created on: 2 Jan 2016
 *      Author: jimmypoms
 */

#ifndef CORE_MOVIE_MOVIENETWORKPROVIDER_H_
#define CORE_MOVIE_MOVIENETWORKPROVIDER_H_

#include <qobjectdefs.h>
#include <qstring.h>

#include "../model/networkprovider.h"

#include "movie.h"
#include "moviefilter.h"

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT MovieNetworkProvider : public NetworkProvider<Movie, MovieFilter>
{
Q_OBJECT

Q_INTERFACES(MovieProviderInterface)

Q_PROPERTY(QString name READ name CONSTANT)

private:
    QString m_name;

public:
    MovieNetworkProvider(QObject *parent = 0, QString name = "");
    virtual ~MovieNetworkProvider() = default;

    const QString &name() const;
};

#endif /* CORE_MOVIE_MOVIENETWORKPROVIDER_H_ */
