/*
 * musicnetworkprovider.h
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#ifndef MUSICNETWORKPROVIDER_H_
#define MUSICNETWORKPROVIDER_H_

#include "artist.h"
#include "musicfilter.h"

#include <qobjectdefs.h>
#include <qstring.h>

#include "../model/networkprovider.h"

class MusicNetworkProvider : public NetworkProvider<Artist, MusicFilter>
{
Q_OBJECT

Q_INTERFACES(MusicProviderInterface)

Q_PROPERTY(QString name READ name CONSTANT)

private:
    QString m_name;

public:
    MusicNetworkProvider(QObject *parent = 0, QString name = "");
    virtual ~MusicNetworkProvider() = default;

    const QString &name() const;
};

#endif /* MUSICNETWORKPROVIDER_H_ */
