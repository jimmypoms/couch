/*
 * album.cpp
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#include "album.h"

#include "artist.h"

Album::Album(Artist *parent) :
        QObject(parent)
{
}

QString Album::genreToString(Album::Genre genre)
{
    switch (genre) {
    case Genre::All:
        return "all";
    case Genre::Blues:
        return "blues";
    case Genre::Jazz:
        return "jazz";
    case Genre::Funk:
        return "funk";
    case Genre::Pop:
        return "pop";
    case Genre::Rock:
        return "rock";
    case Genre::Clasical:
        return "clasical";
    case Genre::Heavy:
        return "heavy";
    case Genre::Punk:
        return "punk";
    case Genre::Indie:
        return "indie";
    case Genre::Alternative:
        return "alternative";
    case Genre::Soul:
        return "soul";
    case Genre::RnB:
        return "r&b";
    case Genre::HipHop:
        return "hip-hop";
    case Genre::Rap:
        return "rap";
    case Genre::Country:
        return "country";
    case Genre::Folk:
        return "folk";
    case Genre::Latin:
        return "latin";
    case Genre::House:
        return "house";
    case Genre::Dance:
        return "dance";
    case Genre::Raggae:
        return "raggae";
    }
    return "unknown";
}