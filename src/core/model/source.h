#ifndef SOURCE_H
#define SOURCE_H

#include "itemmetadata.h"

#include <qobjectdefs.h>
#include <qstring.h>
#include <qurl.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT Source : public SerializableClass
{
Q_OBJECT

Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
Q_PROPERTY(QString quality READ quality WRITE setQuality NOTIFY qualityChanged)
Q_PROPERTY(int sizeBytes READ sizeBytes WRITE setSizeBytes NOTIFY sizeBytesChanged)
Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)

Q_SIGNALS:
    void itemMetadataChanged();
    void nameChanged();
    void qualityChanged();
    void sizeBytesChanged();
    void urlChanged();

private:
    ItemMetadata *m_itemMetadata;

    QString m_name;
    QString m_quality;
    int m_sizeBytes;
    QUrl m_url;

public:
    explicit Source(QObject *parent = 0, QString name = "") :
            SerializableClass(parent), m_itemMetadata(nullptr), m_name(name),
                    m_quality("undefined"), m_sizeBytes(0), m_url()
    {
    }
    bool operator==(const Source &s)
    {
        return m_url == s.url();
    }

    void setItemMetadata(ItemMetadata* metadata)
    {
        if (metadata != m_itemMetadata) {
            delete m_itemMetadata;
            metadata->setParent(this);
            m_itemMetadata = metadata;
            Q_EMIT itemMetadataChanged();
        }
    }
    ItemMetadata* itemMetadata() const
    {
        return m_itemMetadata;
    }

    const QString& name() const
    {
        if (!m_name.isEmpty()) {
            return m_name;
        }
        if (m_itemMetadata) {
            return m_itemMetadata->title();
        }
        return m_name;
    }

    void setName(const QString& name)
    {
        if (m_name != name) {
            m_name = name;
            Q_EMIT nameChanged();
        }
    }

    const QString& quality() const
    {
        return m_quality;
    }

    void setQuality(const QString& quality)
    {
        if (quality != m_quality) {
            m_quality = quality;
            Q_EMIT qualityChanged();
        }
    }

    int sizeBytes() const
    {
        return m_sizeBytes;
    }

    void setSizeBytes(int sizeBytes)
    {
        if (sizeBytes != m_sizeBytes) {
            m_sizeBytes = sizeBytes;
            Q_EMIT sizeBytesChanged();
        }
    }

    const QUrl& url() const
    {
        return m_url;
    }

    void setUrl(const QUrl& url)
    {
        if (url != m_url) {
            m_url = url;
            Q_EMIT urlChanged();
        }
    }
};

#endif // SOURCE_H
