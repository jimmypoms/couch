#ifndef COUCH_H
#define COUCH_H

#include <qlist.h>
#include <qobjectdefs.h>
#include <qqmllist.h>

#include "couch/service.h"

class Couch : public QObject
{
Q_OBJECT

Q_PROPERTY(QQmlListProperty<Service> services READ qmlServices CONSTANT)

private:
    QList<Service*> m_services;

public:
    explicit Couch(QObject *parent = 0);
    virtual ~Couch() = default;

    const QList<Service*> &services() const;
    QQmlListProperty<Service> qmlServices();
    void addService(Service *service);
};

#endif // COUCH_H
