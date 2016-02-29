#ifndef COUCH_H
#define COUCH_H

#include <qlist.h>
#include <qobject.h>
#include <qobjectdefs.h>

class Couch : public QObject
{
Q_OBJECT

Q_PROPERTY(QList<QObject*> services READ services CONSTANT)

private:
    QList<QObject*> m_services;

public:
    explicit Couch(QObject *parent = 0);
    virtual ~Couch() = default;

    const QList<QObject*> &services() const;
    void addService(QObject *service);
};

#endif // COUCH_H
