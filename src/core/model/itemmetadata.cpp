#include "itemmetadata.h"

#include <qmetaobject.h>
#include <qvariant.h>

ItemMetadata::ItemMetadata(QObject *parent) :
        SerializableClass(parent), m_popularity(0), m_rating(0), m_year(0)
{
}

const QString& ItemMetadata::description() const
{
    return m_description;
}

void ItemMetadata::setDescription(const QString& description)
{
    if (m_description != description) {
        m_description = description;
        Q_EMIT descriptionChanged();
    }
}

const QString& ItemMetadata::id() const
{
    return m_id;
}

void ItemMetadata::setId(const QString& id)
{
    if (m_id != id) {
        m_id = id;
        Q_EMIT idChanged();
    }
}

const QUrl& ItemMetadata::image() const
{
    return m_image;
}

void ItemMetadata::setImage(const QUrl& image)
{
    if (m_image != image) {
        m_image = image;
        Q_EMIT imageChanged();
    }
}

const QUrl& ItemMetadata::link() const
{
    return m_link;
}

void ItemMetadata::setLink(const QUrl& link)
{
    if (m_link != link) {
        m_link = link;
        Q_EMIT linkChanged();
    }
}

const QUrl& ItemMetadata::poster() const
{
    return m_poster;
}

void ItemMetadata::setPoster(const QUrl& poster)
{
    if (m_poster != poster) {
        m_poster = poster;
        Q_EMIT posterChanged();
    }
}

double ItemMetadata::rating() const
{
    return m_rating;
}

void ItemMetadata::setRating(double rating)
{
    if (m_rating != rating) {
        m_rating = rating;
        Q_EMIT ratingChanged();
    }
}

const QString& ItemMetadata::title() const
{
    return m_title;
}

void ItemMetadata::setTitle(const QString& title)
{
    if (m_title != title) {
        m_title = title;
        Q_EMIT titleChanged();
    }
}

int ItemMetadata::year() const
{
    return m_year;
}

void ItemMetadata::setYear(int year)
{
    if (m_year != year) {
        m_year = year;
        Q_EMIT yearChanged();
    }
}

double ItemMetadata::popularity() const
{
    return m_popularity;
}

void ItemMetadata::setPopularity(double popularity)
{
    if (m_popularity != popularity) {
        m_popularity = popularity;
        Q_EMIT popularityChanged();
    }
}

void ItemMetadata::merge(const ItemMetadata* metadata)
{
    QVariant var;
    QVariant metadataVar;
    for (int i = 0; i < metaObject()->propertyCount(); ++i) {
        if (metaObject()->property(i).isStored(this)) {
            var = metaObject()->property(i).read(this);
            metadataVar = metadata->property(metaObject()->property(i).name());
            if (metadataVar.isValid() && metadataVar != var) {
                metaObject()->property(i).write(this, metadataVar);
            }
        }
    }
    Q_EMIT merged();
}
