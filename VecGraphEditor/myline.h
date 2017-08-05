#ifndef MYLINE_H
#define MYLINE_H
#include <QtGui>
#include <QtCore>
#include <QGraphicsLineItem>
#include <QPen>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include "myfigure.h"

class MyLine:public QObject,public QAbstractGraphicsShapeItem
{
 Q_OBJECT

public:
    MyLine(QGraphicsItem * parent = 0);
    MyLine(const QLineF & line, QGraphicsItem * parent = 0);
    MyLine(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem * parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QLineF	line() const;
    void	setLine(const QLineF & line);
    void	setLine(qreal x1, qreal y1, qreal x2, qreal y2);
    ~MyLine();
    QRectF boundingRect() const;
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void keyPressEvent(QKeyEvent *event);
protected:
    //void wheelEvent(QGraphicsSceneWheelEvent*);

signals:
    void deleted(QGraphicsItem*);
    void sLine(QAbstractGraphicsShapeItem*);
private:
    QLineF* l;
};

#endif // MYLINE_H
