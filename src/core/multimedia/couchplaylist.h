/*
 * couchplaylist.h
 *
 *  Created on: 10 Sep 2016
 *      Author: jimmypoms
 */

#ifndef COUCHPLAYLIST_H_
#define COUCHPLAYLIST_H_

#include "couch/source.h"

#include <qlist.h>
#include <qobjectdefs.h>
#include <random>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT CouchPlaylist : public QObject
{
Q_OBJECT

Q_ENUMS(PlaybackStatus)
Q_ENUMS(SourceStatus)
Q_PROPERTY(RepeatMode repeatMode READ repeatMode NOTIFY repeatModeChanged)
Q_PROPERTY(ShuffleMode shuffleMode READ shuffleMode NOTIFY shuffleModeChanged)

public:
    enum RepeatMode
    {
        RepeatNone,
        RepeatAll
    };
    enum ShuffleMode
    {
        ShuffleNone,
        ShuffleAll
    };

Q_SIGNALS:
    void repeatModeChanged(RepeatMode mode);
    void shuffleModeChanged(ShuffleMode mode);

private:

    RepeatMode m_repeatMode;
    ShuffleMode m_shuffleMode;

    std::default_random_engine m_randomEngine;

    QList<Source*> m_sources;
    QList<int> m_indexMap;
    int m_currentMapIndex;

    void resetCurrentIndex(int oldCurrentIndex);

public:
    explicit CouchPlaylist(QObject *parent = 0);
    virtual ~CouchPlaylist() = default;

    void addSource(Source* source);
    void addSources(const QList<Source*> &sources);
    void clear();
    int currentIndex();

    Source* first();
    Source* next();
    bool hasNext() const;

    Source* previous();
    bool hasPrevious() const;

    RepeatMode repeatMode() const;
    void setRepeatMode(RepeatMode mode);

    ShuffleMode shuffleMode() const;
    void setShuffleMode(ShuffleMode mode);

    QList<Source*>::iterator begin();
    QList<Source*>::iterator end();

    QList<Source*>::const_iterator cbegin() const;
    QList<Source*>::const_iterator cend() const;
};

#endif /* COUCHPLAYLIST_H_ */
