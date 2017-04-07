/*
 * couchqmlplugin.h
 *
 *  Created on: 26 Dec 2016
 *      Author: jimmypoms
 */

#ifndef COUCHQMLPLUGIN_H_
#define COUCHQMLPLUGIN_H_

#include "couch/couchactionlist.h"
#include "couch/couchitemlist.h"
#include "couch/couchplayer.h"
#include "couch/couchproviderlist.h"
#include "couch/couchsourcelist.h"
#include "couch/movie/movie.h"
#include "couch/movie/moviefilter.h"
#include "couch/music/album.h"
#include "couch/music/artist.h"
#include "couch/music/musicfilter.h"
#include "couch/music/track.h"
#include "couch/music/trackmetadata.h"
#include "couch/settings/settinglist.h"
#include "couch/source.h"

#include <qmetatype.h>
#include <qobjectdefs.h>
#include <qqml.h>
#include <qqmlextensionplugin.h>
#include <qqmllist.h>
#include <memory>

class QmlArtist : public Artist
{
Q_OBJECT

Q_PROPERTY(QQmlListProperty<Item> items READ qmlItems)
Q_CLASSINFO("DefaultProperty", "items")

public:
    QQmlListProperty<Item> qmlItems()
    {
        return QQmlListProperty<Item>(this, childItems(),
                [](QQmlListProperty<Item> *list, Item *item)->void {
                    static_cast<CouchItemList*>(list->data)->append(std::shared_ptr<Item>(item));
                }, [](QQmlListProperty<Item> *list)->int {
                    return static_cast<CouchItemList*>(list->data)->rowCount();
                }, [](QQmlListProperty<Item> *list, int index)->Item* {
                    return static_cast<Item*>(static_cast<CouchItemList*>(list->data)->itemAt(index).get());
                }, [](QQmlListProperty<Item> *list)->void {
                    static_cast<CouchItemList*>(list->data)->clear();
                });
    }
};

class QmlAlbum : public Album
{
Q_OBJECT

Q_PROPERTY(QQmlListProperty<Item> items READ qmlItems)
Q_CLASSINFO("DefaultProperty", "items")

public:
    QQmlListProperty<Item> qmlItems()
    {
        return QQmlListProperty<Item>(this, childItems(),
                [](QQmlListProperty<Item> *list, Item *item)->void {
                    static_cast<CouchItemList*>(list->data)->append(std::shared_ptr<Item>(item));
                }, [](QQmlListProperty<Item> *list)->int {
                    return static_cast<CouchItemList*>(list->data)->rowCount();
                }, [](QQmlListProperty<Item> *list, int index)->Item* {
                    return static_cast<Item*>(static_cast<CouchItemList*>(list->data)->itemAt(index).get());
                }, [](QQmlListProperty<Item> *list)->void {
                    static_cast<CouchItemList*>(list->data)->clear();
                });
    }
};

class CouchQmlPlugin : public QQmlExtensionPlugin
{
Q_OBJECT

Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri)
    {
        qmlRegisterType<Filter>("Couch", 1, 0, "Filter");
        qmlRegisterType<Source>("Couch", 1, 0, "Source");
        qmlRegisterType<ItemMetadata>("Couch", 1, 0, "Metadata");

        qmlRegisterType<CouchItemList>("Couch", 1, 0, "ItemList");
        qmlRegisterType<CouchSourceList>("Couch", 1, 0, "SourceList");
        qmlRegisterType<CouchProviderList>("Couch", 1, 0, "ProviderList");
        qmlRegisterType<CouchActionList>("Couch", 1, 0, "ActionList");

        qmlRegisterUncreatableType<Item>("Couch", 1, 0, "ItemPrivate",
                "impossible to create item form qml");
        qmlRegisterUncreatableType<CouchPlayer>("Couch", 1, 0, "Player",
                "impossible to create player form qml");
        qmlRegisterUncreatableType<SettingList>("Couch", 1, 0, "SettingList",
                "impossible to create setting list form qml");

        qmlRegisterType<MovieFilter>("Couch", 1, 0, "MovieFilter");
        qmlRegisterType<Movie>("Couch", 1, 0, "Movie");

        qmlRegisterType<MusicFilter>("Couch", 1, 0, "MusicFilter");
        qmlRegisterType<Track>("Couch", 1, 0, "Track");
        qmlRegisterType<TrackMetadata>("Couch", 1, 0, "TrackMetadata");
        qmlRegisterType<QmlAlbum>("Couch", 1, 0, "Album");
        qmlRegisterType<AlbumMetadata>("Couch", 1, 0, "AlbumMetadata");
        qmlRegisterType<QmlArtist>("Couch", 1, 0, "Artist");
        qmlRegisterType<ArtistMetadata>("Couch", 1, 0, "ArtistMetadata");
    }
};

Q_DECLARE_SMART_POINTER_METATYPE(std::shared_ptr)
#endif /* COUCHQMLPLUGIN_H_ */
