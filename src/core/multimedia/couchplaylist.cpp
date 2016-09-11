/*
 * couchplaylist.cpp
 *
 *  Created on: 10 Sep 2016
 *      Author: jimmypoms
 */

#include "couchplaylist.h"

#include <algorithm>

CouchPlaylist::CouchPlaylist(QObject *parent) :
        QObject(parent), m_repeatMode(RepeatNone), m_shuffleMode(ShuffleNone), m_currentMapIndex(0)
{
    m_randomEngine = std::default_random_engine{};
}

void CouchPlaylist::addSource(Source* source)
{
    m_indexMap.append(m_sources.size());
    m_sources.append(source);
}

void CouchPlaylist::addSources(const QList<Source*> &sources)
{
    for (Source *source : sources) {
        addSource(source);
    }
}

void CouchPlaylist::clear()
{
    m_sources.clear();
}

Source* CouchPlaylist::next()
{
    if (!hasNext()) {
        return nullptr;
    }
    int size = m_sources.size();
    ++m_currentMapIndex;
    m_currentMapIndex = m_currentMapIndex%size;
    return m_sources[m_indexMap[m_currentMapIndex]];
}

bool CouchPlaylist::hasNext() const
{
    if (m_repeatMode == RepeatAll) {
        return true;
    }
    return m_currentMapIndex < (m_sources.size() - 1);
}

Source* CouchPlaylist::previous()
{
    if (!hasPrevious()) {
        return nullptr;
    }
    int size = m_sources.size();
    --m_currentMapIndex;
    m_currentMapIndex = (m_currentMapIndex%size+size)%size;
    return m_sources[m_indexMap[m_currentMapIndex]];
}

bool CouchPlaylist::hasPrevious() const
{
    if (m_repeatMode == RepeatAll) {
        return true;
    }
    return m_currentMapIndex > 0;
}

CouchPlaylist::RepeatMode CouchPlaylist::repeatMode() const
{
    return m_repeatMode;
}

void CouchPlaylist::setRepeatMode(RepeatMode mode)
{
    if (m_repeatMode != mode) {
        m_repeatMode = mode;
        Q_EMIT repeatModeChanged(m_repeatMode);
    }
}

CouchPlaylist::ShuffleMode CouchPlaylist::shuffleMode() const
{
    return m_shuffleMode;
}

void CouchPlaylist::setShuffleMode(ShuffleMode mode)
{
    if (m_shuffleMode != mode) {
        m_shuffleMode = mode;
        int oldCurrentIndex = currentIndex();
        switch (mode) {
            case ShuffleAll:
                std::shuffle(m_indexMap.begin(), m_indexMap.end(), m_randomEngine);
                break;
            case ShuffleNone:
                std::sort(m_indexMap.begin(), m_indexMap.end());
                break;
        }
        resetCurrentIndex(oldCurrentIndex);
        Q_EMIT shuffleModeChanged(m_shuffleMode);
    }
}

QList<Source*>::iterator CouchPlaylist::begin()
{
    return m_sources.begin();
}

QList<Source*>::iterator CouchPlaylist::end()
{
    return m_sources.end();
}

QList<Source*>::const_iterator CouchPlaylist::cbegin() const
{
    return m_sources.cbegin();
}

void CouchPlaylist::resetCurrentIndex(int oldCurrentIndex)
{
    auto it = std::find(m_indexMap.begin(), m_indexMap.end(), oldCurrentIndex);
    switch (m_shuffleMode) {
        case ShuffleAll:
            std::iter_swap(it, m_indexMap.begin());
            m_currentMapIndex = 0;
            break;
        case ShuffleNone:
            m_currentMapIndex = it - m_indexMap.begin();
            break;
    }
}

int CouchPlaylist::currentIndex()
{
    return m_indexMap[m_currentMapIndex];
}

QList<Source*>::const_iterator CouchPlaylist::cend() const
{
    return m_sources.cend();
}
