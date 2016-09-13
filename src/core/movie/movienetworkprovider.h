/*
 * movienetworkprovider.h
 *
 *  Created on: 2 Jan 2016
 *      Author: jimmypoms
 */

#ifndef MOVIENETWORKPROVIDER_H_
#define MOVIENETWORKPROVIDER_H_

#include "movie.h"
#include "moviefilter.h"

#include "couch/networkprovider.h"

#include <qobjectdefs.h>
#include <qstring.h>

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
Q_PROPERTY(QString playIcon READ playIcon CONSTANT)

private:
    QString m_name;

public:
    MovieNetworkProvider(QObject *parent = 0, QString name = "");
    virtual ~MovieNetworkProvider() = default;

    const QString &name() const;
};

#endif /* MOVIENETWORKPROVIDER_H_ */
