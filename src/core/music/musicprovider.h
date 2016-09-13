/*
 * musicprovider.h
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#ifndef MUSICPROVIDER_H_
#define MUSICPROVIDER_H_

#include "couch/provider.h"

#include <qobject.h>
#include <qobjectdefs.h>
#include <qstring.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT MusicProvider : public QObject, public MusicProviderInterface
{
Q_OBJECT

Q_INTERFACES(MusicProviderInterface)

Q_PROPERTY(QString name READ name CONSTANT)
Q_PROPERTY(QString playIcon READ playIcon CONSTANT)

private:
    QString m_name;

public:
    MusicProvider(QObject *parent = 0, QString name = "");
    virtual ~MusicProvider() = default;

    const QString &name() const;
};

#endif /* MUSICPROVIDER_H_ */
