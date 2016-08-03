#ifndef ITEM_H
#define ITEM_H

#include "couchsourcelist.h"

#include <qhash.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <memory>

class CouchProviderList;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT Item : public QObject
{
Q_OBJECT

Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
Q_PROPERTY(ItemMetadata* metadata READ metadata NOTIFY metadataChanged)

Q_SIGNALS:
    void nameChanged();
    void metadataChanged();
    void sourcesChanged();
    void providersChanged();

private:
    QString m_name;
    std::shared_ptr<ItemMetadata> m_metadata;
    QHash<const QObject*, CouchSourceList*> m_sources;
    CouchSourceList* m_emptySourceList;
    CouchProviderList* m_providers;

public:
    explicit Item(QObject* parent);
    virtual ~Item() = default;

    const QString &name() const;
    void setName(const QString &name);

    ItemMetadata *metadata() const;
    void setMetadata(std::shared_ptr<ItemMetadata> metadata);

    virtual void addSource(const QObject* provider, Source* source);

    bool operator==(const Item& other) noexcept
    {
        return *m_metadata == *(other.m_metadata);
    }

public Q_SLOTS:
    CouchSourceList *sources(QObject *provider);
    CouchProviderList* providers() const;

};

#endif // ITEM_H
