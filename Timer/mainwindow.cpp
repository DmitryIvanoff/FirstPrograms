#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    icon(":/icons/Images/setwalls.ru-64409.jpg"),
    ui(new Ui::MainWindow)


{
    ui->setupUi(this);
    this->setWindowTitle("Таймер выключения компа");
    this->setWindowIcon(icon);
    time=new QTime();
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    connect(timer,SIGNAL(timeout()),ui->timeEdit,SLOT(update()));
    connect(ui->pushButton_2,SIGNAL(clicked()),timer,SLOT(stop()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete time;
    delete timer;
}

void MainWindow::StartCount()
{
    *time=ui->timeEdit->time();
    timer->start(1000);

}

void MainWindow::on_pushButton_clicked()
{
    StartCount();
}


void MainWindow::timeout()
{
    if (time->isValid())
    {

      *time=ui->timeEdit->time().addSecs(-1);
       ui->timeEdit->setTime(*time);
      if (*time==QTime(0,0,0))
      {
          timer->stop();
          system("SHUTDOWN /s");
          emit exit(0);

      }
    }
    else timer->stop();
}



void MainWindow::on_pushButton_3_clicked()
{
    timer->stop();
    ui->timeEdit->setTime(QTime(0,0,0));
    *time=QTime(0,0,0);
}
