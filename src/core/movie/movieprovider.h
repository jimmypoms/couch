/*
 * MovieProvider.h
 *
 *  Created on: 2 Jan 2016
 *      Author: jimmypoms
 */

#ifndef MOVIEPROVIDER_H_
#define MOVIEPROVIDER_H_

#include "couch/provider.h"

#include <qobject.h>
#include <qobjectdefs.h>
#include <qstring.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT MovieProvider : public QObject, public MovieProviderInterface
{
Q_OBJECT

Q_INTERFACES(MovieProviderInterface)

Q_PROPERTY(QString name READ name CONSTANT)

private:
    QString m_name;

public:
    MovieProvider(QObject *parent = 0, QString name = "");
    virtual ~MovieProvider() = default;

    const QString &name() const;
};

#endif /* MOVIEPROVIDER_H_ */
