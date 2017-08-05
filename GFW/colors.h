#ifndef COLORS
#define COLORS
#include <QtGui>
#include <QtCore>
class RGBPIXEL
{
    RGBPIXEL()
        {}

        RGBPIXEL( BYTE r, BYTE g, BYTE b ) : QRgb
        {}

        RGBPIXEL( const RGBPIXEL& c ) :
        blue(c.blue), green(c.green), red(c.red), reserved(c.reserved)
        {}

        RGBPIXEL& operator=( const RGBPIXEL& c )
        {
            blue = c.blue; green = c.green; red = c.red;
            return (*this);
        }

        void Set( BYTE r, BYTE g, BYTE b )
        {
            blue = b; green = g; red = r;
        }
};
#endif // COLORS

