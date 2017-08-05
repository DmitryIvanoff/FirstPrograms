#ifndef MYFIGURE_H
#define MYFIGURE_H
#include <QGraphicsItem>
#include <QtCore>
#include <QtGui>
#include <QGraphicsSceneWheelEvent>



class MyFigure:public QObject
{
    Q_OBJECT
public:
    MyFigure();
    QPen* myPen;
    QBrush* myBrush;
    ~MyFigure();
public slots:
    void setPen(QPen *);
    void setBrush(QBrush*);


};
class MyItem:public MyFigure,public QGraphicsItem
{
public:
    MyItem();


};

#endif // MYFIGURE_H
