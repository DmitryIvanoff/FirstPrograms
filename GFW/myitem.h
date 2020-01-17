#ifndef MYITEM_H
#define MYITEM_H
#define _USE_MATH_DEFINES

#include <QtGui>
#include <QRectF>
#include <QtCore>
#include <QGraphicsItem>
#include "rgbpixel.h"
#include <math.h>

enum LineCaps{FLAT,ROUND,SQUARE};
enum IntersectType {COLLINEAR,PARALLEL,SKEW,SKEW_CROSS,SKEW_NO_CROSS};
enum CLPointType {LEFT,RIGHT,BEYOND,BEHIND,BETWEEN,ORIGIN,DESTINATION};
enum EType {TOUCHING,CROSS_LEFT,CROSS_RIGHT,INESSENTIAL};
enum ObjectType{LINE,POLYGON,SPLINE,BEZIERCURVE};
class MyItem : public QGraphicsItem
{
public:

   MyItem(QRectF r);
   ~MyItem();
    void gfOnLMouseClick( int x, int y );
    void gfOnRMouseClick( int x, int y );
    void gfOnKeyDown(int key);
    QImage* picture;
    void SetLineCap(int);      //Задает тип законцовки линии
    void SetLineWidth(int);  //Задает ширину линии
    void SetColor(QColor col);  //Задает цвет для рисования
    void SavePicture();
    void SetDashes(int*,int);  //Задает Штриховку
    void SetObject(int);   //Задает тип текущего обЪекта
    void gfDrawExample(int);   //Рисуетзаданные примеры
 protected:
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
     QRectF boundingRect() const override ;
     void advance(int phase) override;

     void dragEnterEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
     void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
     void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
 private:
    void gfRedrawPicture();
    void gfSetPixel(int x,int y,RGBPIXEL color);
    void gfDrawLine(int x0, int y0, int x1, int y1, RGBPIXEL color);
    void gfDrawPolygon(int* X,int* Y,int n, RGBPIXEL color);
    bool IsConvex(int* X, int *Y, int n);
    bool IsComplex(int* X, int *Y, int n);
    bool PInPolygonEOMode(double x, double y, int* X, int* Y, int n);
    bool PInPolygonNZWMode(double x, double y, int* X, int* Y, int n);
    void gfFillPolygonEOMode(int* X, int* Y, int n, RGBPIXEL color);
    void gfFillPolygonNZWMode(int* X, int* Y, int n, RGBPIXEL color);
    void gfDrawCircle(int x0, int y0, double radius, RGBPIXEL color);
    void gfDrawDashedLine(int x0, int y0, int x1, int y1, RGBPIXEL color, int width, LineCaps captype,const QVector<int>& p);
    void gfDrawLine(int x0, int y0, int x1, int y1, RGBPIXEL color, int width, LineCaps captype);
    void gfDrawShell(int* X, int* Y, int n, RGBPIXEL color);
    void gfDrawBezierCurve(int* X, int* Y, int n, RGBPIXEL color); //здесь n это порядок кривой(не кол-во вершин многоугольника)
    void gfDrawCubicHermiteSpline(QVector2D* Vertexes, QVector2D* DirectVectors,int n,RGBPIXEL color);
    CLPointType Classify(double x1, double y1, double x2, double y2, double x, double y);
    IntersectType Intersect(double ax,double ay, double bx, double by,double cx,double cy,double dx, double dy,double* t) ;
    IntersectType Cross(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy, double* tab, double* tcd);
    EType EdgeType(double x0, double y0, double xd, double yd, double xa, double ya);
    ObjectType objtype=LINE;//Тип объекта по умолчанию LINE
    RGBPIXEL* color;  //chosen color in ColorDialog
    QVector<QPoint> *points;  //список точек заданных мышью
    QRectF* rect;//image's boundaries
    int mc=0;  //Amount of mouse's presses
    QVector<int> pixels; //Pixels for dashed line
    int width=0; //Line width
    LineCaps linecap=FLAT; //Законцовка линии
  //  QImage* picture;

};

#endif // MYITEM_H
