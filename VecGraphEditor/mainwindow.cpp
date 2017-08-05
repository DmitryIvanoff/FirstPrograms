#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    setMouseTracking(true);
    ui->setupUi(this);
    palitra=new QColorDialog(this);
    scene =new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(-350,-350,600,600);
    lbl_x =new QLabel(this);
    lbl_y =new QLabel(this);
    cursor=new QCursor();
    scene->addRect(scene->sceneRect(),QPen(Qt::red));
    ui->statusBar->addWidget(lbl_x);
    ui->statusBar->addWidget(lbl_y);
    currentItem=NULL;
    selectedItem=NULL;
    scene->installEventFilter(this);
    ui->graphicsView->installEventFilter(this);
    connect(palitra,SIGNAL(colorSelected(QColor)),this,SLOT(setColor(QColor)));
    connect(ui->lineEdit,SIGNAL(textEdited(QString)),this,SLOT(setY1(QString)));
    connect(ui->lineEdit_2,SIGNAL(textEdited(QString)),this,SLOT(setX1(QString)));
    connect(ui->lineEdit_3,SIGNAL(textEdited(QString)),this,SLOT(setX2(QString)));
    connect(ui->lineEdit_4,SIGNAL(textEdited(QString)),this,SLOT(setY2(QString)));
    connect(ui->lineEdit_6,SIGNAL(textEdited(QString)),this,SLOT(setW(QString)));
    connect(ui->lineEdit_7,SIGNAL(textEdited(QString)),this,SLOT(setH(QString)));


}


MainWindow::~MainWindow()
{
    delete ui;
    palitra->deleteLater();
    scene->deleteLater();
    lbl_x->deleteLater();
    lbl_y->deleteLater();
    delete cursor;
}

void MainWindow::mouseMoveEvent(QMouseEvent *me)
{
    lbl_x->setText("x=" + QString().setNum(me->x()-ui->graphicsView->pos().x()));
    lbl_y->setText("y=" + QString().setNum(me->y()-ui->graphicsView->pos().y()));
}

int i = 1;
QPointF p1=QPointF();
QPointF p2=QPointF();
float X1=0;
float X2=50;
float Y1=0;
float Y2=50;
float angle=0;
bool ok1;
bool ok2;
bool ok3;
bool ok4;
bool ok5;
bool rotSet=false;
float W=50;
float H=50;

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    if (obj == ui->graphicsView && event->type() == QEvent::MouseButtonPress)
    {
        if (currentItem!=NULL)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button()==Qt::LeftButton)
            {

                  if (currentItem->type()==MyLine::Type)
                   {

                      switch (i)
                      {
                        case 1:
                           {
                            p1=mouseEvent->pos();
                            i++;
                            break;
                           }
                        case 2:
                           {
                            p2=mouseEvent->pos();
                            line->setLine(p1.x(),p1.y(),p2.x(),p2.y());
                            angle=ui->lineEdit_5->text().toFloat(&ok5);

                            if (ok5)
                            {
                                line->setRotation(angle);
                                qreal dx=((1-cos(angle))*(pos().x()-line->boundingRect().center().x())+(pos().y()-line->boundingRect().center().y())*sin(angle));
                                qreal dy=((1-cos(angle))*(pos().y()-line->boundingRect().center().y())+(pos().x()-line->boundingRect().center().x())*sin(angle));

                              //  line->moveBy(dx,dy);
                            }
                            //connect(palitra,SIGNAL(colorSelected(QColor)),line,SLOT(setColor(QColor)));
                            connect(line,SIGNAL(sLine(QAbstractGraphicsShapeItem*)),this,SLOT(selectedGraphicsItem(QAbstractGraphicsShapeItem*)));
                            connect(line,SIGNAL(deleted(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                            scene->addItem(line);
                            i=i-1;
                           }
                      }
                   }
                  if (currentItem->type()==MyEllipse::Type)
                   {

                      W=ui->lineEdit_6->text().toFloat(&ok1);
                      H=ui->lineEdit_7->text().toFloat(&ok2);
                      angle=ui->lineEdit_5->text().toFloat(&ok5);
                      if (ok1&&ok2)
                      {
                          //ellipse = new MyEllipse();
                          ellipse->setRect(mouseEvent->pos().x(),mouseEvent->pos().y(),W,H);
                          if (ok5)
                           {
                             ellipse->setRotation(angle);
                             qreal dx=(1-cos(angle)*(pos().x()-ellipse->boundingRect().center().x())+(pos().y()-ellipse->boundingRect().center().y())*sin(angle));
                             qreal dy=(1-cos(angle)*(pos().y()-ellipse->boundingRect().center().y())+(pos().x()-ellipse->boundingRect().center().x())*sin(angle));
                          //   ellipse->moveBy(dx,dy);
                           }
                          scene->addItem(ellipse);

                          connect(ellipse,SIGNAL(sEllipse(QAbstractGraphicsShapeItem*)),this,SLOT(selectedGraphicsItem(QAbstractGraphicsShapeItem*)));
                          connect(ellipse,SIGNAL(deleted(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                          W=H=50;
                      }
                   }
                  if (currentItem->type()==MyRect::Type)
                   {

                      W=ui->lineEdit_6->text().toFloat(&ok1);
                      H=ui->lineEdit_7->text().toFloat(&ok2);
                      angle=ui->lineEdit_5->text().toFloat(&ok5);
                      if (ok1&&ok2)
                      {
                        // rec=new MyRect();
                         rec->setRect(mouseEvent->pos().x(),mouseEvent->pos().y(),W,H);
                         if (ok5)
                         {
                         rec->setRotation(angle);
                         qreal dx=(1-cos(angle)*(pos().x()-rec->boundingRect().center().x())+(pos().y()-rec->boundingRect().center().y())*sin(angle));
                         qreal dy=(1-cos(angle)*(pos().y()-rec->boundingRect().center().y())+(pos().x()-rec->boundingRect().center().x())*sin(angle));

                        // rec->moveBy(dx,dy);
                         }
                         connect(rec,SIGNAL(sRect(QAbstractGraphicsShapeItem*)),this,SLOT(selectedGraphicsItem(QAbstractGraphicsShapeItem*)));
                         connect(rec,SIGNAL(deleted(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                          scene->addItem(rec);
                          W=H=50;
                      }

                  }

              return true;
           }
           else
              return false;
         }
        return false;
     }
   if (obj == ui->widget&& event->type() == QEvent::MouseButtonPress)
    {
        selectedItem=NULL;
        QString str("");
        ui->lineEdit_2->setText(str);
        ui->lineEdit->setText(str);
        ui->lineEdit_3->setText(str);
        ui->lineEdit_4->setText(str);
        ui->lineEdit_6->setText(str);
        ui->lineEdit_7->setText(str);
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button()==Qt::LeftButton)
            {


            }
    }
    return false;
}



void MainWindow::selectedGraphicsItem(QAbstractGraphicsShapeItem *itm)
{

       selectedItem=itm;
       selectedItem->setActive(true);
       selectedItem->setSelected(true);
       QString str(QString::number(selectedItem->pos().x()));
       ui->lineEdit_2->setText(str);
       str=QString::number(selectedItem->pos().y());
       ui->lineEdit->setText(str);
       str=QString::number(selectedItem->boundingRect().bottomRight().x());
       ui->lineEdit_3->setText(str);
       str=QString::number(selectedItem->boundingRect().bottomRight().y());
       ui->lineEdit_4->setText(str);
       str=QString::number(selectedItem->boundingRect().width());
       ui->lineEdit_6->setText(str);
       str=QString::number(selectedItem->boundingRect().height());
       ui->lineEdit_7->setText(str);
}


void MainWindow::on_commandLinkButton_2_clicked()
{

    ellipse = new MyEllipse();
    currentItem=ellipse;
    X1=ui->lineEdit_2->text().toFloat(&ok1);
    X2=ui->lineEdit_3->text().toFloat(&ok2);
    Y1=ui->lineEdit->text().toFloat(&ok3);
    Y2=ui->lineEdit_4->text().toFloat(&ok4);
    angle=ui->lineEdit_5->text().toFloat(&ok5);
    if ((ok1)&&(ok2)&&(ok3)&&(ok4))
    {
       ellipse->setRect(X1,Y1,X2-X1,Y2-Y1);
       connect(ellipse,SIGNAL(sEllipse(QAbstractGraphicsShapeItem*)),this,SLOT(selectedGraphicsItem(QAbstractGraphicsShapeItem*)));
       connect(ellipse,SIGNAL(deleted(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
       if (ok5)
         {
            ellipse->setRotation(angle);
            qreal dx=((1-cos(angle))*(pos().x()-ellipse->boundingRect().center().x())+(pos().y()-ellipse->boundingRect().center().y())*sin(angle));
            qreal dy=((1-cos(angle))*(pos().y()-ellipse->boundingRect().center().y())+(pos().x()-ellipse->boundingRect().center().x())*sin(angle));

            //ellipse->moveBy(dx,dy);
         }
       scene->addItem(ellipse);
    }


}

void MainWindow::on_commandLinkButton_3_clicked()
{

    line= new MyLine();
    currentItem=line;
    X1=ui->lineEdit_2->text().toFloat(&ok1);
    X2=ui->lineEdit_3->text().toFloat(&ok2);
    Y1=ui->lineEdit->text().toFloat(&ok3);
    Y2=ui->lineEdit_4->text().toFloat(&ok4);
    angle=ui->lineEdit_5->text().toFloat(&ok5);
    if ((ok1)&&(ok2)&&(ok3)&&(ok4))
    {
       line->setLine(X1,Y1,X2,Y2);
       connect(line,SIGNAL(sLine(QAbstractGraphicsShapeItem*)),this,SLOT(selectedGraphicsItem(QAbstractGraphicsShapeItem*)));
       connect(line,SIGNAL(deleted(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
       if (ok5)
       {
           line->setRotation(angle);
           qreal dx=((1-cos(angle))*(pos().x()-line->boundingRect().center().x())+(pos().y()-line->boundingRect().center().y())*sin(angle));
           qreal dy=((1-cos(angle))*(pos().y()-line->boundingRect().center().y())+(pos().x()-line->boundingRect().center().x())*sin(angle));

          // line->moveBy(dx,dy);

       }
       scene->addItem(line);
    }




}

void MainWindow::on_commandLinkButton_4_clicked()
{
   palitra->show();

}

void MainWindow::on_commandLinkButton_clicked()
{
    rec = new MyRect();
    currentItem=rec;
    X1=ui->lineEdit_2->text().toFloat(&ok1);
    X2=ui->lineEdit_3->text().toFloat(&ok2);
    Y1=ui->lineEdit->text().toFloat(&ok3);
    Y2=ui->lineEdit_4->text().toFloat(&ok4);
    angle=ui->lineEdit_5->text().toFloat(&ok5);
    if ((ok1)&&(ok2)&&(ok3)&&(ok4))
    {
       rec->setRect(X1,Y1,X2-X1,Y2-Y1);
       connect(rec,SIGNAL(sRect(QAbstractGraphicsShapeItem*)),this,SLOT(selectedGraphicsItem(QAbstractGraphicsShapeItem*)));
       connect(rec,SIGNAL(deleted(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
       if (ok5)
       {
         rec->setRotation(angle);
         qreal dx=((1-cos(angle))*(pos().x()-rec->boundingRect().center().x())+(pos().y()-rec->boundingRect().center().y())*sin(angle));
         qreal dy=((1-cos(angle))*(pos().y()-rec->boundingRect().center().y())+(pos().x()-rec->boundingRect().center().x())*sin(angle));

        // rec->moveBy(dx,dy);
       }
       scene->addItem(rec);
    }

}

void MainWindow::deleteItem(QGraphicsItem *itm)
{
    scene->removeItem(itm);
    delete itm;
}


void MainWindow::on_commandLinkButton_5_clicked()
{
    scene->clear();
}

void MainWindow::setX1(QString str)
{
    float X1=str.toFloat(&ok1);
    if ((ok1)&&(selectedItem!=NULL))
    {
       selectedItem->setX(X1);
    }

}

void MainWindow::setY1(QString str)
{
    float Y1=str.toFloat(&ok1);
    if ((ok1)&&(selectedItem!=NULL))
    {
       selectedItem->setY(Y1);
    }
}

void MainWindow::setX2(QString str)
{

}

void MainWindow::setY2(QString str)
{

}

void MainWindow::setW(QString str)
{
}

void MainWindow::setH(QString str)
{

}

void MainWindow::setColor(QColor col)
{
   if(selectedItem!=NULL)
   {
     QPen p(Qt::black);
     QBrush b(col);
     selectedItem->setBrush(b);
    selectedItem->setPen(p);
   }
}



