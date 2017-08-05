#include "myfigure.h"


MyFigure::MyFigure()
{
   myBrush=new QBrush();
   myPen=new QPen();
}

void MyFigure::setPen(QPen *p)
{
    myPen=p;
}

void MyFigure::setBrush(QBrush *b)
{
    myBrush=b;
}

MyFigure::~MyFigure()
{
    delete myPen;
    delete myBrush;
}
MyItem::MyItem():MyFigure(),QGraphicsItem()
{

}



