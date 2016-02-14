#ifndef ITEMMETADATA_H
#define ITEMMETADATA_H

#include <qobjectdefs.h>
#include <qstring.h>
#include <qurl.h>

#include "../couch/serializableclass.h"

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT ItemMetadata : public SerializableClass
{
Q_OBJECT

Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
Q_PROPERTY(double popularity READ popularity WRITE setPopularity NOTIFY popularityChanged)
Q_PROPERTY(QUrl image READ image WRITE setImage NOTIFY imageChanged)
Q_PROPERTY(QUrl poster READ poster WRITE setPoster NOTIFY posterChanged)
Q_PROPERTY(QUrl backdrop READ backdrop NOTIFY posterChanged)
Q_PROPERTY(double rating READ rating WRITE setRating NOTIFY ratingChanged)
Q_PROPERTY(int year READ year WRITE setYear NOTIFY yearChanged)

Q_SIGNALS:
    void titleChanged();
    void descriptionChanged();
    void popularityChanged();
    void imageChanged();
    void posterChanged();
    void ratingChanged();
    void yearChanged();
    void merged();

private:
    QString m_title;
    QString m_description;
    double m_popularity;
    QUrl m_image;
    QUrl m_poster;
    double m_rating;
    int m_year;

public:
    explicit ItemMetadata(QObject *parent = 0);
    virtual ~ItemMetadata() = default;

    const QString& title() const;
    void setTitle(const QString& title);

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

    void merge(const ItemMetadata *metadata);

    bool operator==(const ItemMetadata& other) noexcept
    {
        return m_year == other.m_year && m_title == other.m_title;
    }
};

#endif // ITEMMETADATA_H
