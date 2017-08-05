#include "myline.h"


MyLine::MyLine(QGraphicsItem * parent):QObject(),QAbstractGraphicsShapeItem(parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);
    setFocus();
    setPen(QPen(QBrush(Qt::black),3));
    l=new QLineF();
}

MyLine::MyLine(const QLineF &line, QGraphicsItem *parent):QObject(),QAbstractGraphicsShapeItem(parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);
    setFocus();
    setPen(QPen(QBrush(Qt::black),3));
    l=new QLineF(line);

}



MyLine::MyLine(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent):QObject(),QAbstractGraphicsShapeItem(parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);
    setFocus();
    setPen(QPen(QBrush(Qt::black),3));
    l=new QLineF(x1,y1,x2,y2);
}

void MyLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   painter->setPen(this->pen());
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawLine(*l);
    painter->drawRect(boundingRect());


}

QLineF MyLine::line() const
{
    return *l;
}


void MyLine::setLine(const QLineF &line)
{
    l->setLine(line.x1(),line.y1(),line.x2(),line.y2());
}

void MyLine::setLine(qreal x1, qreal y1, qreal x2, qreal y2)
{
    l->setLine(x1,y1,x2,y2);
}

MyLine::~MyLine()
{
    delete l;
}

QRectF MyLine::boundingRect() const
{
    return QRectF(l->p1(),l->p2());
}



void MyLine::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (this->isSelected())
    {
        emit sLine(this);
    }
    QGraphicsItem::mousePressEvent(event);
}

void MyLine::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Delete:
     {
        if (this->isSelected())
        {
            emit deleted(this);
        }
        break;
     }
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}

/*void MyLine::wheelEvent(QGraphicsSceneWheelEvent *e)
{
    if (this->isSelected())
    {
        setRotation(e->delta());
        float angle=e->delta();
        qreal dx=((1-cos(angle))*(pos().x()-boundingRect().center().x())+(pos().y()-boundingRect().center().y())*sin(angle));
        qreal dy=((1-cos(angle))*(pos().y()-boundingRect().center().y())+(pos().x()-boundingRect().center().x())*sin(angle));

        //moveBy(dx,dy);
    }
    QGraphicsItem::wheelEvent(e);
}*/

