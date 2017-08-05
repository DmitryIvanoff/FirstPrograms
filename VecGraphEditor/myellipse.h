#ifndef MYELLIPSE_H
#define MYELLIPSE_H
#include <QtGui>
#include <QtCore>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include "myfigure.h"
class MyEllipse: public QObject,public QGraphicsEllipseItem
{
   Q_OBJECT

public:
    MyEllipse(QGraphicsItem* parent=0);
    MyEllipse(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);
    MyEllipse(const QRectF & rect, QGraphicsItem * parent = 0);
    ~MyEllipse();
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event); 
    //void wheelEvent(QGraphicsSceneWheelEvent*);

signals:
    void deleted(QGraphicsItem*);
    void sEllipse(QAbstractGraphicsShapeItem*);

};

#endif // MYELLIPSE_H
