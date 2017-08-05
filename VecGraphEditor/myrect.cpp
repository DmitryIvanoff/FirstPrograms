#include "myrect.h"

MyRect::MyRect(QGraphicsItem* parent):QObject(),QGraphicsRectItem(parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);
    setFocus();
}

MyRect::MyRect(const QRectF &rect, QGraphicsItem *parent):QObject(),QGraphicsRectItem(rect,parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);
    setFocus();

}

MyRect::MyRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent):	QObject(),QGraphicsRectItem(x,y,width,height,parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);
    setFocus();
}


void MyRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->drawRect(boundingRect());
}


void MyRect::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

    if (this->isSelected())
    {
        emit sRect(this);
    }
    QGraphicsRectItem::mousePressEvent(event);
}

void MyRect::keyPressEvent(QKeyEvent *event)
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

/*void MyRect::wheelEvent(QGraphicsSceneWheelEvent *e)
{
    if (this->isSelected())
    {
        setRotation(e->delta()/120);
        float angle=e->delta()/120;
        qreal dx=((1-cos(angle))*(pos().x()-boundingRect().center().x())+(pos().y()-boundingRect().center().y())*sin(angle));
        qreal dy=((1-cos(angle))*(pos().y()-boundingRect().center().y())+(pos().x()-boundingRect().center().x())*sin(angle));

        //moveBy(dx,dy);
    }
    QGraphicsItem::wheelEvent(e);
}*/



