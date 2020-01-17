#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    installEventFilter(this);
    scene =new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(ui->graphicsView->rect());
    scene->addRect(scene->sceneRect(),QPen(Qt::red),QBrush(Qt::black));
    scene->installEventFilter(this);
    timer=new QTimer();
    ui->graphicsView->installEventFilter(this);
    SavePicture=new QAction(this);
    ui->comboBox->addItem("Line");
    ui->comboBox->addItem("Polygon");
    ui->comboBox->addItem("Spline");
    ui->comboBox->addItem("Bezier curve");
    ui->comboBox_3->addItem("Flat");
    ui->comboBox_3->addItem("Round");
    ui->comboBox_4->addItem("Star");
    ui->comboBox_4->addItem("Complex polygon");
    palitra=new QColorDialog(this);
    gfInitScene();
    connect(palitra,SIGNAL(colorSelected(QColor)),this,SLOT(setColor(QColor)));
    connect(timer,SIGNAL(timeout()),scene,SLOT(advance()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    timer->stop();
    delete timer;
    delete SavePicture;
    delete item;
    delete scene;
    delete palitra;
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    if (obj == ui->graphicsView)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            gfOnKeyDown(keyEvent->key());
            return true;
        }
        else if (event->type() == QEvent::MouseButtonPress)
        {
             QMouseEvent *mEvent = static_cast<QMouseEvent*>(event);
             switch (mEvent->button())
             {
                case Qt::LeftButton:
                     p=(ui->graphicsView->mapToScene(mEvent->x(),mEvent->y()));
                     gfOnLMouseClick(p.x(),p.y());
                     return true;
                     break;
                case Qt::RightButton:
                   p=(ui->graphicsView->mapToScene(mEvent->x(),mEvent->y()));
                   gfOnRMouseClick(p.x(),p.y());
                 return true;
                 break;
             }
        }
        /*else if (event->type() == QEvent::MouseMove)
        {
            QMouseEvent *mEvent = static_cast<QMouseEvent*>(event);
            p=(ui->graphicsView->mapToScene(mEvent->x(),mEvent->y()));
            gfOnMouseMove(p.x(),p.y());
            return true;
        }*/
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *mEvent = static_cast<QMouseEvent*>(event);
            switch (mEvent->button())
            {
               case Qt::LeftButton:
                p=(ui->graphicsView->mapToScene(mEvent->x(),mEvent->y()));
                gfOnLMouseRelease(p.x(),p.y());
                return true;
                break;
            }

        }
        else
        {
            return false;
        }
    }
    else
    {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(obj, event);
    }
}

void MainWindow::gfCleanupScene()
{
    scene->removeItem(item);
    delete item;
    scene->update();
    gfInitScene();
}

void MainWindow::gfOnLMouseClick(int x, int y)
{
   item->gfOnLMouseClick(x,y);

}

void MainWindow::gfOnMouseMove(int x, int y)
{
    /*switch (objtype)
     {
     case LINE:
        //gfCleanupScene();
        //item->gfDrawLine(points->at(0).x(),points->at(0).y(),x,y,RGBPIXEL::Blue());

        break;
     case POLYGON:

        break;
     case SPLINE:

        break;
     default:
        k=0;
        break;
    }*/
  // item->gfOnMouseMove(x,y);
}


void MainWindow::gfOnRMouseClick(int x, int y)
{
    item->gfOnRMouseClick(x,y);

}


void MainWindow::gfOnLMouseRelease(int x, int y)
{

}

void MainWindow::gfOnKeyDown(int key)
{
    if (key == Qt::Key_Delete)
    {
        gfCleanupScene();
        return;
    }
    item->gfOnKeyDown(key);
}

bool MainWindow::gfInitScene()
{
    item=new MyItem(scene->sceneRect());
    scene->addItem(item);
    return true;
}



void MainWindow::on_actionSave_triggered()
{
     item->SavePicture();
}



void MainWindow::on_comboBox_4_activated(int index)
{
   item->gfDrawExample(index);
}

void MainWindow::on_comboBox_activated(int index)
{
    item->SetObject(index);
    switch (index)
    {
      case 0:
         ui->lineEdit->setEnabled(true);
         ui->comboBox_3->setEnabled(true);
         break;
      case 1:
         ui->lineEdit->setEnabled(false);
         ui->comboBox_3->setEnabled(false);
         break;
      case 2:
        ui->lineEdit->setEnabled(false);
        ui->comboBox_3->setEnabled(false);
         break;
      default:
        ui->lineEdit->setEnabled(false);
        ui->comboBox_3->setEnabled(false);
         break;
    }
}
void MainWindow::setColor(QColor col)
{
   item->SetColor(col);

}


void MainWindow::on_commandLinkButton_clicked()
{
    palitra->show();
}


void MainWindow::on_lineEdit_editingFinished()
{
    QString str;
    QString buffer;
    QVector<int> numbers;
    str=ui->lineEdit->text();
    int i=0;
    while ((i<str.length()))
     {
        if (str[i]==':')
        {
            bool* ok;
            int number=buffer.toInt(ok);
            if (*ok)
            {
               numbers.append(number);
            }
             buffer.clear();
        }
        else
        {
           buffer+=str[i];

        }
              ++i;
      }
   if (!numbers.isEmpty())
   {
    int* pixels=new int[numbers.size()];
    for (int i=0;i<numbers.size();++i)
    {
       pixels[i]=numbers.at(i);
    }
    item->SetDashes(pixels,numbers.size());
   }
}
