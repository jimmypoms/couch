/*
 * album.h
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#ifndef ALBUM_H_
#define ALBUM_H_

#include <qobject.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <qurl.h>

class Artist;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT Album : public QObject
{
Q_OBJECT

Q_ENUMS(Genre)
Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
Q_PROPERTY(QUrl cover READ cover WRITE setCover NOTIFY coverChanged)

Q_SIGNALS:
    void titleChanged();
    void coverChanged();

private:
    QString m_title;
    QUrl m_cover;

public:
    enum Genre
    {
        All,
        Blues,
        Jazz,
        Funk,
        Pop,
        Rock,
        Clasical,
        Heavy,
        Punk,
        Indie,
        Alternative,
        Soul,
        RnB,
        HipHop,
        Rap,
        Country,
        Folk,
        Latin,
        House,
        Dance,
        Raggae,
    };

    explicit Album(Artist *parent);
    virtual ~Album() = default;

    const QString title() const;
    void setTitle(const QString &title);

    const QUrl cover() const;
    void setCover(const QUrl &cover);

    static QString genreToString(Album::Genre genre);
};

#endif /* ALBUM_H_ */
