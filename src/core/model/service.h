#ifndef SERVICE_H
#define SERVICE_H

#include <qlist.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <memory>

class Item;
class Source;

class Service : public QObject
{
Q_OBJECT

Q_PROPERTY(QString name READ name CONSTANT)
Q_PROPERTY(QList<QObject*> providers READ providers NOTIFY providersChanged)

Q_SIGNALS:
    void error(const QString &msg);
    void warning(const QString &msg);

    void providersChanged();

    void itemsReady(const QList<std::shared_ptr<Item> > &items, const QString &id);

private:
    QString m_name;
    QList<QObject*> m_providers;
    QList<std::shared_ptr<Item> > m_items;

    virtual Item* createItem(const Source *source) = 0;

public Q_SLOTS:
    void reduceSources();

public:
    explicit Service(QObject *parent, QString name);
    virtual ~Service() = default;

    const QString &name() const;

    void addProvider(QObject* provider);
    const QList<QObject*> &providers() const;
};

#endif // SERVICE_H
