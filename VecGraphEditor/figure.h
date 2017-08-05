#ifndef FIGURE_H
#define FIGURE_H
#include <QtCore>
#include <QtGui>
#include <QGraphicsObject>

class figure:public QGraphicsObject
{
public:
    figure();
    ~figure();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // FIGURE_H
