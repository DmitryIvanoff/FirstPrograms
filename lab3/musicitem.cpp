#include "musicitem.h"

MusicItem::MusicItem()
{
    trackName="None";
    trackLink="";
    trackArtist="None";
    trackArtistLink="";
}

MusicItem::MusicItem(QString tN, QString tL, QString tA, QString tAL)
{
    trackName=tN;
    trackLink=tL;
    trackArtist=tA;
    trackArtistLink=tAL;
}

