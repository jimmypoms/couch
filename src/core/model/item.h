#ifndef ITEM_H
#define ITEM_H

#include "couchsourcelist.h"
#include "itemmetadata.h"

#include <qhash.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <memory>

class Service;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT Item : public QObject
{
Q_OBJECT

Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
Q_PROPERTY(ItemMetadata* metadata READ metadata NOTIFY metadataChanged)

Q_SIGNALS:
    void titleChanged();
    void metadataChanged();
    void sourcesChanged();

private:
    Service* m_service;

    QString m_title;
    std::shared_ptr<ItemMetadata> m_metadata;
    CouchSourceList* m_emptySourceList;
    QHash<const QObject*, CouchSourceList*> m_sources;
    QHash<const QObject*, bool> m_loaded;

public:
    explicit Item(Service* service);
    virtual ~Item() = default;

    const QString &title() const;
    void setTitle(const QString &title);

    bool isLoaded(const QObject* provider) const;
    void setLoaded(const QObject* provider, bool loaded);

    ItemMetadata *metadata() const;
    void setMetadata(std::shared_ptr<ItemMetadata> metadata);

    void addSource(const QObject* provider, Source* source);

    bool operator==(const Item& other) noexcept
    {
        return *m_metadata == *(other.m_metadata);
    }

public Q_SLOTS:
    CouchSourceList *sources(QObject *provider);

};

#endif // ITEM_H
