#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef struct _PcxHeader
{
  BYTE	Identifier;        /* PCX Id Number (Always 0x0A) */
  BYTE	Version;           /* Version Number */
  BYTE	Encoding;          /* Encoding Format */
  BYTE	BitsPerPixel;      /* Bits per Pixel */
  WORD	XStart;            /* Left of image */
  WORD	YStart;            /* Top of Image */
  WORD	XEnd;              /* Right of Image */
  WORD	YEnd;              /* Bottom of image */
  WORD	HorzRes;           /* Horizontal Resolution */
  WORD	VertRes;           /* Vertical Resolution */
  BYTE	Palette[48];       /* 16-Color EGA Palette */
  BYTE	Reserved1;         /* Reserved (Always 0) */
  BYTE	NumBitPlanes;      /* Number of Bit Planes */
  WORD	BytesPerLine;      /* Bytes per Scan-line */
  WORD	PaletteType;       /* Palette Type */
  WORD	HorzScreenSize;    /* Horizontal Screen Size */
  WORD	VertScreenSize;    /* Vertical Screen Size */
  BYTE	Reserved2[54];     /* Reserved (Always 0) */
} PCXHEAD;
int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    PCXHEAD header;
    ifstream fg;
    fg.open("RGB.pcx",ios_base::in|ios_base::binary);
    if (!fg.is_open())
    {
        cout<<"ERROR: that file does not exist!";
        return 0;

     }
    fg.read((char*)&header,128);
    cout<<"Identifier: "<<header.Identifier<<"\n";
    cout<<"Version: "<<header.Version<<"\n";
    cout<<"Encoding: "<<header.Encoding<<"\n";
    cout<<"BitsPerPixel: "<<header.BitsPerPixel<<"\n";
    cout<<"XStart: "<<header.XStart<<"\n";
    cout<<"YStart: "<<header.YStart<<"\n";
    cout<<"XEnd: "<<header.XEnd<<"\n";
    cout<<"YEnd: "<<header.YEnd<<"\n";
    cout<<"HorzRes: "<<header.HorzRes<<"\n";
    cout<<"VertRes: "<<header.VertRes<<"\n";
    cout<<"BytesPerLine: "<<header.BytesPerLine<<"\n";
    cout<<"HorzScreenSize: "<<header.HorzScreenSize<<"\n";
    cout<<"VertScreenSize: "<<header.VertScreenSize<<"\n";
    fg.close();
    system("PAUSE");
    return 0;
}
