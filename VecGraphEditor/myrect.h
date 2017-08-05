#ifndef MYRECT_H
#define MYRECT_H
#include <QtGui>
#include <QtCore>
#include <QGraphicsRectItem>
#include <QPen>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include "myfigure.h"

class MyRect:public QObject,public QGraphicsRectItem
{
   Q_OBJECT
public:
    MyRect(QGraphicsItem *parent=0);
    MyRect(const QRectF & rect, QGraphicsItem * parent = 0);
    MyRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void keyPressEvent(QKeyEvent *event);
    //void wheelEvent(QWheelEvent*);

signals:
    void deleted(QGraphicsItem*);
    void sRect(QAbstractGraphicsShapeItem*);


};

#endif // MYRECT_H
