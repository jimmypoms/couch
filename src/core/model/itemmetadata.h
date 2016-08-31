#ifndef ITEMMETADATA_H
#define ITEMMETADATA_H

#include "couch/serializableclass.h"

#include <qdatetime.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <qurl.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT ItemMetadata : public SerializableClass
{
Q_OBJECT

Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
Q_PROPERTY(double popularity READ popularity WRITE setPopularity NOTIFY popularityChanged)
Q_PROPERTY(QUrl image READ image WRITE setImage NOTIFY imageChanged)
Q_PROPERTY(QUrl poster READ poster WRITE setPoster NOTIFY posterChanged)
Q_PROPERTY(QUrl backdrop READ backdrop NOTIFY posterChanged)
Q_PROPERTY(double rating READ rating WRITE setRating NOTIFY ratingChanged)
Q_PROPERTY(int year READ year WRITE setYear NOTIFY yearChanged)
Q_PROPERTY(QDateTime addedAt READ addedAt WRITE setAddedAt NOTIFY addedAtChanged)

Q_SIGNALS:
    void nameChanged();
    void descriptionChanged();
    void popularityChanged();
    void imageChanged();
    void posterChanged();
    void ratingChanged();
    void yearChanged();
    void addedAtChanged();
    void merged();

private:
    QString m_name;
    QString m_description;
    double m_popularity;
    QUrl m_image;
    QUrl m_poster;
    double m_rating;
    int m_year;
    QDateTime m_addedAt;

public:
    explicit ItemMetadata(QObject *parent = 0);
    virtual ~ItemMetadata() = default;

    const QString& name() const;
    void setName(const QString& name);

    const QString& description() const;
    void setDescription(const QString& description);

    double popularity() const;
    void setPopularity(double popularity);

    const QUrl& image() const;
    void setImage(const QUrl& image);

    const QUrl& poster() const;
    void setPoster(const QUrl& poster);

    const QUrl& backdrop() const;

    double rating() const;
    void setRating(double rating);

    int year() const;
    void setYear(int year);

    const QDateTime& addedAt() const;
    void setAddedAt(const QDateTime& addedAt);

    void merge(const ItemMetadata *metadata);
    bool operator==(const ItemMetadata& other) noexcept;

    bool operator<(const ItemMetadata& other) noexcept
    {
        return lessThan(&other);
    }

    virtual bool lessThan(const ItemMetadata* other) noexcept
    {
        return name() < other->name();
    }
};

#endif // ITEMMETADATA_H
