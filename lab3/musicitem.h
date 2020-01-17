#ifndef MUSICITEM_H
#define MUSICITEM_H

#include <QtCore>

struct MusicItem
{
    MusicItem();
    MusicItem(QString tN,QString tL,QString tA,QString tAL);
    QString trackName;
    QString trackLink;
    QString trackArtist;
    QString trackArtistLink;

};

#endif // MUSICITEM_H
