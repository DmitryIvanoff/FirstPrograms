#include "myellipse.h"

MyEllipse::MyEllipse(QGraphicsItem* parent):QObject(),QGraphicsEllipseItem(parent=0)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);
    setFocus();


}

MyEllipse::MyEllipse(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent):QObject(),QGraphicsEllipseItem(x,y,width,height,parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);
    setFocus();


}

MyEllipse::MyEllipse(const QRectF &rect, QGraphicsItem *parent):QObject(),QGraphicsEllipseItem(rect,parent)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);
    setFocus();
}

MyEllipse::~MyEllipse()
{
}

void MyEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   painter->setPen(this->pen());
   painter->setBrush(this->brush());
    painter->setRenderHint(QPainter::Antialiasing);
   // painter->drawRect(boundingRect());
    painter->drawEllipse(boundingRect());

}

void MyEllipse::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

    if (this->isSelected())
    {
        emit sEllipse(this);
    }
    QGraphicsEllipseItem::mousePressEvent(event);
}

void MyEllipse::keyPressEvent(QKeyEvent *event)
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

/*void MyEllipse::wheelEvent(QGraphicsSceneWheelEvent *e)
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

